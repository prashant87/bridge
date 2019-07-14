
#include "task_imu.h"
#include "i2c.h"
#include "bno055.h"
#include "cmsis_os.h"
#include "task_led.h"

#include "math.h"

#define BTN_LEFT       GPIO_PIN_0
#define BTN_RIGHT      GPIO_PIN_1
#define BTN_SET_ORIGIN GPIO_PIN_2

typedef struct DataStruct_
{
	float Qadj[4];
	float Qorigin[4];
	float Qprev[4];
	float Q[4];
	float Qrel[4];

	float angles[2];
	int   anglesInt[2];
	unsigned char btn1, btn2;

	float margin;
	float coefSpeed;
	float coefPos;

	int doInit;
} DataStruct;

DataStruct g_data;

static void dataInit( DataStruct * d );
static void dataPushQ( DataStruct * d, float * q );
static void dataSetOrigin( DataStruct * d );
static void dataComputeDisplacement( DataStruct * d );
static void dataComputeVelocity( DataStruct * d );

static int btnState( int btn );
//HAL_GPIO_ReadPin

static void bno055Init( void );
static void bno055_delay( uint32_t msec );
static int8_t bno055_bus_read_i2c( uint8_t dev_addr, uint8_t reg_addr, uint8_t * reg_data, uint8_t qty );
static int8_t bno055_bus_write_i2c( uint8_t dev_addr, uint8_t reg_addr, uint8_t * reg_data, uint8_t qty );
static struct bno055_t bno055_inst;

static void vTaskImu( void * p );

static osMutexDef_t mutex;
static osMutexId    mutexId;
//osThreadDef(imuTask, vTaskImu, osPriorityAboveNormal, 0, 512);
osThreadDef(imuTask, vTaskImu, osPriorityRealtime, 0, 512);

void taskImuInit( void )
{
	bno055_inst.bus_write  = bno055_bus_write_i2c;
	bno055_inst.bus_read   = bno055_bus_read_i2c;
	bno055_inst.delay_msec = bno055_delay;
	bno055_inst.dev_addr   = BNO055_I2C_ADDR1 << 1;

	dataInit( &g_data );

	mutexId = osMutexCreate( &mutex );
	// Create reading thread.
	osThreadCreate(osThread(imuTask), NULL);
}

static void quatNormalize( float * q );
static void quatCopy( float * qFrom, float * qTo );
static float sqrtn( float a );
static void quat2Mat( float * q, float * * R );
static void quatRel( float * qa, float * qb, float * qr );
static void quatMult( float * qa, float * qb, float * qr );
static void quatRotateVector( float * q, float * v, float * vr );
static void moveFloatToInt( float * fa, int * ia );
static void moveResult( int * adj );

//static float angScale = 1600.0;
//static float angFloat[2] = { 0.0f, 0.0f };
//static int   angInt[2] = { 0, 0 };

uint8_t adjustMouse( int8_t * x, int8_t * y )
{
	uint8_t res = 0;
	osMutexWait( mutexId, osWaitForever );
		if ( g_data.anglesInt[0] > 0 )
		{
			int max_dx = 127 - (*x);
			int dx = ( g_data.anglesInt[0] < max_dx ) ? g_data.anglesInt[0] : max_dx;
			res = res + ( (dx != 0) ? 1 : 0 );
			*x += dx;
			g_data.anglesInt[0] -= dx;
		}
		else if ( g_data.anglesInt[0] < 0 )
		{
			int min_dx = -127 - (*x);
			int dx = (g_data.anglesInt[0] > min_dx) ? g_data.anglesInt[0] : min_dx;
			res = res + ( (dx != 0) ? 1 : 0 );
			*x += dx;
			g_data.anglesInt[0] -= dx;
		}

		if ( g_data.anglesInt[1] > 0 )
		{
			int max_dy = 127 - (*y);
			int dy = ( g_data.anglesInt[1] < max_dy ) ? g_data.anglesInt[1] : max_dy;
			res = res + ( (dy != 0) ? 1 : 0 );
			*y += dy;
			g_data.anglesInt[1] -= dy;
		}
		else if ( g_data.anglesInt[1] < 0 )
		{
			int min_dy = -127 - (*y);
			int dy = (g_data.anglesInt[1] > min_dy) ? g_data.anglesInt[1] : min_dy;
			res = res + ( (dy != 0) ? 1 : 0 );
			*y += dy;
			g_data.anglesInt[1] -= dy;
		}
	osMutexRelease( mutexId );

	return res;
}

unsigned char buttonStates( void )
{
	unsigned char v = ( (btnState(BTN_LEFT)) ? 1 : 0 ) ||
			          ( (btnState(BTN_RIGHT)) ? 1 : 0 );
	return v;
}

static void vTaskImu( void * p )
{
	static int comres;
	static struct bno055_quaternion_t qq;
	static float q[4];//, qPrev[4], qRel[4];
	//static float R[3][3];
	//static float axisX[3] = {1.0f, 0.0f, 0.0f};
	//static int   angIntBuf[2];
	//static int doInit = 1;
	// Allow IMU boot up.
	vTaskDelay( 1000 );
	// Initialize BNO055.
	bno055Init();
	// Initialize current time variable.
	static TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	// read data in infinite loop.
	for (;;)
	{
		toggleLed( 2 );

		vTaskDelayUntil( &xLastWakeTime, 10 );
		// Read sensor.
		comres = bno055_read_quaternion_wxyz( &bno055_inst, &qq );
		if ( comres != 0 )
			continue;
		q[0] = qq.w;
		q[1] = qq.x;
		q[2] = qq.y;
		q[3] = qq.z;
		quatNormalize( q );


		/*if ( doInit )
		{
			doInit = 0;
			quatCopy( q, qPrev );
		}
		quatRel( qPrev, q, qRel );
		//quat2Mat( qPrev, R );
		axisX[0] = 1.0; //R[0][0];
		axisX[1] = 0.0; //R[1][0];
		axisX[2] = 0.0; //R[2][0];
		float angZ = -2.0f * qRel[3] * angScale;
		float angX = -2.0f * (qRel[1]*axisX[0] + qRel[2]*axisX[1] + qRel[3]*axisX[2]) * angScale;
		angFloat[0] += angZ;
		angFloat[1] += angX;
		angIntBuf[0] = 0;
		angIntBuf[1] = 0;
		moveFloatToInt( angFloat, angIntBuf );
		moveResult( angIntBuf );

		quatCopy( q, qPrev );*/

		dataPushQ( &g_data, q );
	}
}

static void quatNormalize( float * q )
{
	/*float l = q[0]*q[0] + q[1]*q[1] + q[2]*q[2];
	l = 1.0 / sqrtn( l );
	q[0] *= l;
	q[1] *= l;
	q[2] *= l;
	q[3] *= l;*/

	static const float l = 1.0 / 16384.0;
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

static void quatMult( float * qa, float * qb, float * qr )
{
	const float a =  qa[0];
	const float b =  qa[1];
	const float c =  qa[2];
	const float d =  qa[3];

	const float e =  qb[0];
	const float f =  qb[1];
	const float g =  qb[2];
	const float h =  qb[3];

	qr[0] = a*e - b*f - c*g - d*h;
	qr[1] = b*e + a*f + c*h - d*g;
	qr[2] = a*g - b*h + c*e + d*f;
	qr[3] = a*h + b*g - c*f + d*e;
}

static void quatRotateVector( float * q, float * v, float * vr )
{
	float qv[4];
	qv[0] = 0.0;
	qv[1] = v[0];
	qv[2] = v[1];
	qv[3] = v[3];

	quatMult( q, qv, qv );

	float iq[4];
	iq[0] =  q[0];
	iq[1] = -q[1];
	iq[2] = -q[2];
	iq[3] = -q[3];

	quatMult( qv, iq, qv );

	vr[0] = qv[1];
	vr[1] = qv[2];
	vr[2] = qv[3];
}

static void moveFloatToInt( float * fa, int * ia )
{
	for ( int i=0; i<2; i++ )
	{
		ia[i] = 0;
		if ( fa[i] >= 1.0f )
		{
			while ( fa[i] >= 1.0f )
			{
				fa[i] -= 1.0f;
				ia[i]   += 1;
			}
		}
		else if ( fa[i] <= -1.0f )
		{
			while ( fa[i] <= -1.0f )
			{
				fa[i] += 1.0f;
				ia[i]   -= 1;
			}
		}
	}
}

static void moveResult( int * adj )
{
	osMutexWait( mutexId, osWaitForever );
		g_data.anglesInt[0] += adj[0];
		g_data.anglesInt[1] += adj[1];
	osMutexRelease( mutexId );
}


static void dataInit( DataStruct * d )
{
	d->Qadj[0] = 1.0;
	d->Qadj[1] = 0.0;
	d->Qadj[2] = 0.0;
	d->Qadj[3] = 0.0;

	d->Qorigin[0] = 1.0;
	d->Qorigin[1] = 0.0;
	d->Qorigin[2] = 0.0;
	d->Qorigin[3] = 0.0;

	d->Qprev[0]   = 1.0;
	d->Qprev[1]   = 0.0;
	d->Qprev[2]   = 0.0;
	d->Qprev[3]   = 0.0;

	d->Q[0]       = 1.0;
	d->Q[1]       = 0.0;
	d->Q[2]       = 0.0;
	d->Q[3]       = 0.0;

	d->angles[0]  = 0.0;
	d->angles[1]  = 0.0;

	d->anglesInt[0] = 0;
	d->anglesInt[1] = 0;

	d->btn1 = 0;
	d->btn2 = 0;

	d->margin       = 3.1415 / 8.0;

	d->coefSpeed    = 1600.0;
	d->coefPos      = 100.0;

	d->doInit = 1;
}

static void dataPushQ( DataStruct * d, float * q )
{
	quatCopy( q, d->Q );
	if ( d->doInit )
	{
		d->doInit = 0;
		quatCopy( d->Q, d->Qprev );
		quatCopy( d->Q, d->Qorigin );
		return;
	}

	int needSetOrigin = btnState( BTN_SET_ORIGIN );
	if ( needSetOrigin )
	{
		dataSetOrigin( d );
		return;
	}

	dataComputeDisplacement( d );
	dataComputeVelocity( d );

	moveFloatToInt( d->angles, d->anglesInt );
	moveResult( d->anglesInt );

	quatCopy( d->Q, d->Qprev );
}

static void dataSetOrigin( DataStruct * d )
{
	quatCopy( d->Q, d->Qorigin );
}

static void dataComputeDisplacement( DataStruct * d )
{
	quatRel( d->Qprev, d->Q, d->Qrel );
	const float angZ = -2.0f * d->Qrel[3] * d->coefSpeed;
	const float angX = -2.0f * d->Qrel[1] * d->coefSpeed;
	d->angles[0] += angZ;
	d->angles[1] += angX;
}

static void dataComputeVelocity( DataStruct * d )
{
	quatRel( d->Qorigin, d->Q, d->Qrel );
	float vy[3];
	vy[0] = 0.0;
	vy[1] = 1.0;
	vy[2] = 0.0;
	quatRotateVector( d->Qrel, vy, vy );
	const float ang = atan2( -vy[0], vy[1] );

	if ( ang > d->margin )
	{
		const float a = (ang - d->margin)*d->coefSpeed;
		d->angles[0] += a;
		return;
	}

	if ( ang < -d->margin )
	{
		const float a = (ang - d->margin)*d->coefSpeed;
		d->angles[0] += a;
	}
}

static int btnState( int btn )
{
	GPIO_PinState state = HAL_GPIO_ReadPin( GPIOB, btn );
	int res = ( state == GPIO_PIN_RESET ) ? 1 : 0;
	return res;
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

extern I2C_HandleTypeDef hi2c1;

#define I2C_TIMEOUT 168000000
static int8_t bno055_bus_read_i2c( uint8_t dev_addr, uint8_t reg_addr, uint8_t * reg_data, uint8_t qty )
{
	HAL_StatusTypeDef res = HAL_I2C_Mem_Read( &hi2c1, dev_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, qty, I2C_TIMEOUT );
	int8_t result = ( res == HAL_OK ) ? 0 : 1;
	return result;
}

static int8_t bno055_bus_write_i2c( uint8_t dev_addr, uint8_t reg_addr, uint8_t * reg_data, uint8_t qty )
{
	HAL_StatusTypeDef res = HAL_I2C_Mem_Write( &hi2c1, dev_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, qty, I2C_TIMEOUT );
	int8_t result = ( res == HAL_OK ) ? 0 : 1;
	return result;
}



