#include <tests.h>
#include "lld_control.h"
#include "odometry.h"



static const SerialConfig sdcfg = {
  .speed = 115200,
  .cr1 = 0, .cr2 = 0, .cr3 = 0
};

/**
 * @brief   Find out the correct frequency for motors
 */
void testMatlabFrequency( void )
{
    lldControlInit( );
    odometryInit( );
//    debug_stream_init( );

    sdStart( &SD6, &sdcfg );
    palSetPadMode( GPIOG, 14, PAL_MODE_ALTERNATE(8) );   // TX
    palSetPadMode( GPIOG, 9,  PAL_MODE_ALTERNATE(8) );   // RX

    lldControlValue_t   test_duty1_prc      = 0;
    lldControlValue_t   test_delta_prc      = 10;
    float               test_motor1_speed   = 0;
    int16_t             matlab_motor1_speed = 0;
    uint8_t             matlab_start_flag   = 0;

    systime_t   time = chVTGetSystemTimeX( );
    while( true )
    {
        char rc_data         = sdGetTimeout( &SD6, TIME_IMMEDIATE );

        switch( rc_data )
        {
            case 's':   // start
                palSetLine( LINE_LED2 );
                matlab_start_flag = 1;
                break;

            case 'f':   // increase duty cycle
                test_duty1_prc += test_delta_prc;
                break;

            case 'd':   // decrease duty cycle
                test_duty1_prc -= test_delta_prc;
                break;


            default:
                break;
        }

        test_duty1_prc = CLIP_VALUE( test_duty1_prc, 0, 80 );
        lldControlSetMotorPower( 1, test_duty1_prc );

        test_motor1_speed    = odometryGetEncoderSpeed( 1, REVS_PER_SEC );

        if( matlab_start_flag )
        {
            palSetLine( LINE_LED3 );
            matlab_motor1_speed = (int)test_motor1_speed;
            sdWrite(&SD6, (uint8_t*) &matlab_motor1_speed, 2);
        }

        time = chThdSleepUntilWindowed( time, time + MS2ST( 10 ) );
    }

}
