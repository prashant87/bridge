
#include "task_imu.h"
#include "i2c.h"
#include "bno055.h"
#include "cmsis_os.h"

static void bno055Init( void );
static void bno055_delay( uint32_t msec );
static int8_t bno055_bus_read_i2c( uint8_t dev_addr, uint8_t reg_addr, uint8_t * reg_data, uint8_t qty );
static int8_t bno055_bus_write_i2c( uint8_t dev_addr, uint8_t reg_addr, uint8_t * reg_data, uint8_t qty );
static struct bno055_t bno055_inst;

static void vTaskImu( void * p );

osThreadDef(imuTask, vTaskImu, osPriorityAboveNormal, 0, 512);
void taskImuInit( void )
{
	bno055_inst.bus_write  = bno055_bus_write_i2c;
	bno055_inst.bus_read   = bno055_bus_read_i2c;
	bno055_inst.delay_msec = bno055_delay;
	bno055_inst.dev_addr   = BNO055_I2C_ADDR1 << 1;

	// Initialize I2C peripherial.
	MX_I2C2_Init();
	// Create reading thread.
	osThreadCreate(osThread(imuTask), NULL);
}

static void quatNormalize( float * q );
static void quatCopy( float * qFrom, float * qTo );
static float sqrtn( float a );
static void quat2Mat( float * q, float * * R );
static void quatRel( float * qa, float * qb, float * qr );
static void moveFloatToInt( float * fa, int * ia );
static void moveResult( int * adj );

static float angScale = 16.0;
static float angFloat[2] = { 0.0f, 0.0f };
static int   angInt[2] = { 0, 0 };

static void vTaskImu( void * p )
{
	struct bno055_quaternion_t qq;
	float q[4], qPrev[4], qRel[4];
	float R[3][3];
	float axisX[3] = {1.0f, 0.0f, 0.0f};
	float axisZ[3] = {0.0f, 0.0f, 1.0f};
	int   angIntBuf[2];
	int comres;
	int doInit = 1;
	// Allow IMU boot up.
	vTaskDelay( 1000 );
	// Initialize BNO055.
	bno055Init();
	// read data in infinite loop.
	for (;;)
	{
		vTaskDelay( 10 );
		comres = bno055_read_quaternion_wxyz( &bno055_inst, &qq );
		if ( comres != 0 )
			continue;
	    //comres  = bno055_read_quaternion_w( &(qq.w) );
	    //comres += bno055_read_quaternion_x( &(qq.x) );
	    //comres += bno055_read_quaternion_y( &(qq.y) );
	    //comres += bno055_read_quaternion_z( &(qq.z) );
		q[0] = qq.w;
		q[1] = qq.x;
		q[2] = qq.y;
		q[3] = qq.z;
		quatNormalize( q );
		if ( doInit )
		{
			doInit = 0;
			quatCopy( q, qPrev );
		}
		quatRel( qPrev, q, qRel );
		quat2Mat( qPrev, R );
		axisX[0] = R[0][0];
		axisX[1] = R[1][0];
		axisX[2] = R[2][0];
		const float angZ = 2.0f * qRel[3] * angScale;
		const float angX = 2.0f * (qRel[1]*axisX[0] + qRel[2]*axisX[1] + qRel[3]*axisX[2]) * angScale;
		angFloat[0] += angX;
		angFloat[1] += angZ;
		angIntBuf[0] = 0;
		angIntBuf[1] = 0;
		moveFloatToInt( angFloat, angIntBuf );


		quatCopy( q, qPrev );
	}
}

static void quatNormalize( float * q )
{
	float l = q[0]*q[0] + q[1]*q[1] + q[2]*q[2];
	l = 1.0 / sqrtn( l );
	q[0] *= l;
	q[1] *= l;
	q[2] *= l;
	q[3] *= l;
}

static void quatCopy( float * qFrom, float * qTo )
{
	qTo[0] = qFrom[0];
	qTo[1] = qFrom[1];
	qTo[2] = qFrom[2];
	qTo[3] = qFrom[3];
}

static float sqrtn( float a )
{
	float x;
	x = a;
	for ( int i=0; i<8; i++ )
		x = 0.5f*(x + a/x);
	return x;
}

static void quat2Mat( float * q, float * * R )
{
    const float w = q[0];
    const float x = q[1];
    const float y = q[2];
    const float z = q[3];

    const float sqw = w*w;
    const float sqx = x*x;
    const float sqy = y*y;
    const float sqz = z*z;

    // invs (inverse square length) is only required if quaternion is not already normalised
    const float invs = 1.0f / (sqx + sqy + sqz + sqw);
    R[0][0] = ( sqx - sqy - sqz + sqw)*invs; // since sqw + sqx + sqy + sqz =1/invs*invs
    R[1][1] = (-sqx + sqy - sqz + sqw)*invs;
    R[2][2] = (-sqx - sqy + sqz + sqw)*invs;

    float tmp1 = x*y;
    float tmp2 = z*w;
    R[1][0] = 2.0 * (tmp1 + tmp2)*invs;
    R[0][1] = 2.0 * (tmp1 - tmp2)*invs;

    tmp1 = x*z;
    tmp2 = y*w;
    R[2][0] = 2.0 * (tmp1 - tmp2)*invs;
    R[0][2] = 2.0 * (tmp1 + tmp2)*invs;
    tmp1 = y*z;
    tmp2 = x*w;
    R[2][1] = 2.0 * (tmp1 + tmp2)*invs;
    R[1][2] = 2.0 * (tmp1 - tmp2)*invs;
}

static void quatRel( float * qa, float * qb, float * qr )
{
	const float a =  qa[0];
	const float b = -qa[1];
	const float c = -qa[2];
	const float d = -qa[3];

	const float e =  qb[0];
	const float f =  qb[1];
	const float g =  qb[2];
	const float h =  qb[3];

	qr[0] = a*e - b*f - c*g - d*h;
	qr[1] = b*e + a*f + c*h - d*g;
	qr[2] = a*g - b*h + c*e + d*f;
	qr[3] = a*h + b*g - c*f + d*e;
}

static void moveFloatToInt( float * fa, int * ia )
{
	for ( int i=0; i<2; i++ )
	{
		if ( fa[0] >= 1.0f )
		{
			while ( fa[0] >= 1.0f )
			{
				fa[0] -= 1.0f;
				ia[0]   += 1;
			}
		}
		else if ( fa[0] <= -1.0f )
		{
			while ( fa[0] <= -1.0f )
			{
				fa[0] += 1.0f;
				ia[0]   -= 1;
			}
		}
	}
}

static void moveResult( int * adj )
{
	angInt[0] += adj[0];
	angInt[1] += adj[1];
}

static void bno055Init( void )
{
	s32 comres = BNO055_ERROR;
	comres = bno055_init(&bno055_inst);
	u8 power_mode = BNO055_POWER_MODE_NORMAL;
	// set the power mode as NORMAL
	comres += bno055_set_power_mode( &bno055_inst, power_mode );
	comres += bno055_set_operation_mode( &bno055_inst, BNO055_OPERATION_MODE_NDOF );
}

static void bno055_delay( uint32_t msec )
{
	vTaskDelay( msec );
}

extern I2C_HandleTypeDef hi2c2;

#define I2C_TIMEOUT 168000000
static int8_t bno055_bus_read_i2c( uint8_t dev_addr, uint8_t reg_addr, uint8_t * reg_data, uint8_t qty )
{
	HAL_StatusTypeDef res = HAL_I2C_Mem_Read( &hi2c2, dev_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, qty, I2C_TIMEOUT );
	int8_t result = ( res == HAL_OK ) ? 0 : 1;
	return result;
}

static int8_t bno055_bus_write_i2c( uint8_t dev_addr, uint8_t reg_addr, uint8_t * reg_data, uint8_t qty )
{
	HAL_StatusTypeDef res = HAL_I2C_Mem_Write( &hi2c2, dev_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, qty, I2C_TIMEOUT );
	int8_t result = ( res == HAL_OK ) ? 0 : 1;
	return result;
}



