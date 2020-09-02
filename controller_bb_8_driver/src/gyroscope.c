#include <gyroscope.h>


static bool isInitialized   = false;

/**
 * @brief   Initialize gyroscope
 */
void gyroscopeInit(void)
{
    if(isInitialized)
        return;

    uint8_t initbuf[5];
    initbuf[0] = GYRO_CTRL1_REG;            // Start from ctrl1 register
    initbuf[1] = 0x0F;                      // Normal mode, each axis enable, freq settings ignored
    initbuf[2] = 0x00;                      // High pass filter default configuration
    initbuf[3] = 0x00;                      // Too smart for me
    initbuf[4] = 0x30;                      // 2000dps

    i2cSimpleWrite(GYRO_ADDR, initbuf, 5, 1000);


    isInitialized = true;
}

/**
 * @brief   Read gyroscope axis values in XYZ order
 *
 * @param
 *          *axis_values         Array where to store read data
 */
msg_t readGyroscope(int16_t *axis_values)
{
    uint8_t gyro_temp[6] = {0, 0, 0, 0, 0, 0};
    msg_t msg = i2cRegisterRead(GYRO_ADDR, GYRO_DATA_REG, gyro_temp, 6, 10000);

    uint8_t i = 0;
    for(i = 0; i < 3; i++)
    {
        axis_values[i] = (int16_t)((uint16_t)(gyro_temp[i * 2]) | ((uint16_t)(gyro_temp[(i * 2) + 1]) << 8));
    }
    return msg;
}

/**
 * @brief   Read gyroscope and represent values as int16
 *
 * @param
 *          *axis_speed         Array where to store axial rotational speed values
 */
msg_t readGyroSpeed(float *axis_speed)
{
    int16_t gyro_axis_values[3] = {0, 0, 0};
    uint8_t i = 0;
    msg_t msg = readGyroscope(gyro_axis_values);
    for(i = 0; i < 3; i++)
    {
        axis_speed[i] = (float)gyro_axis_values[i] * 0.07;
    }
    return msg;
}


/**
 * @brief   Calculate static error
 * @details Calculates average value of each axis data over ten readings
 *
 * @param
 *          *axis_speed         Array where to store static error values
 */
msg_t calculateGyroError(float *buf)
{
    msg_t msg = MSG_OK;
    int16_t temp_buf[10][3] = {{0}};
    int16_t super_temp[3] = {0, 0, 0};
    uint8_t i, j;
    float x_mean = 0, y_mean = 0, z_mean = 0;
    for(i = 0; i < 10; i++)
    {
        msg = readGyroscope(super_temp);
        for(j = 0; j < 3; j++)
        {
            temp_buf[i][j] = super_temp[j];
        }
    }


    for(i = 0; i < 10; i++)
    {
        x_mean += temp_buf[i][0];
        y_mean += temp_buf[i][1];
        z_mean += temp_buf[i][2];
    }

    buf[0] = (x_mean / 10) * 0.07;
    buf[1] = (y_mean / 10) * 0.07;
    buf[2] = (z_mean / 10) * 0.07;

    return msg;
}
