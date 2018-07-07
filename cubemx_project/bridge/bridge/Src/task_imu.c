
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

static void vTaskImu( void * p )
{
	struct bno055_quaternion_t qq;
	float q[4];
	int comres;
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
	}
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



