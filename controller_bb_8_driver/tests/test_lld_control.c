#include <tests.h>
#include <lld_control.h>

/*
 * @brief   Test motor direction control 
 * @note    Duty cycle is constant 
 */
void testRawMotorDirectionControlRoutine( void )
{
    debug_stream_init( ); 
    lldControlInit( );

    lldMotorDirection_t test_dir    = FORWARD; 
    uint32_t            test_duty   = 5000;  

    systime_t   time = chVTGetSystemTimeX( );
    while( true )
    {
        char rcv_data   = sdGetTimeout( &SD3, TIME_IMMEDIATE ); 
        switch( rcv_data )
        {
            case 'a':
                test_dir = FORWARD; 
                break; 

            case 's':
                test_dir = BACKWARD; 
                break; 
            
            default:
                break;
        }
        lldControlSetRawMotorPower(1, test_duty, test_dir );
        dbgprintf( "DIR: (%d)\n\r", test_dir ); 

        time = chThdSleepUntilWindowed( time, time + MS2ST( 500 ) );
    }
}

// #define MOTOR_FORWARD
#define MOTOR_BACKWARD

/*
 * @brief   Test raw motor control 
 * @note    Duty cycle could be changed [0, 20000]
 *          Stable for incorrect value of duty cycle 
 *          Direction is controled via defines 
 *          MOTOR_FORWARD || MOTOR_BACKWARD 
 */
void testRawMotorControlRoutine( void )
{
    debug_stream_init( ); 
    lldControlInit( );

    uint32_t test_duty  = 0; 
    uint32_t test_duty_delta = 500;

    systime_t   time = chVTGetSystemTimeX( );
    while( true )
    {
        char rcv_data   = sdGetTimeout( &SD3, TIME_IMMEDIATE ); 
        switch( rcv_data )
        {
            case 'a':
                test_duty += test_duty_delta; 
                break; 

            case 's':
                test_duty -= test_duty_delta;
                break; 

            case ' ':
                test_duty = 0; 
                break;
            
            default:
                break;
        }
        test_duty = CLIP_VALUE( test_duty, 0, 20000 );
#ifdef MOTOR_FORWARD
        lldControlSetRawMotorPower( 1, test_duty, FORWARD );
        dbgprintf("FORWARD DS: (%d)\n\r", test_duty);
#endif 

#ifdef MOTOR_BACKWARD
        lldControlSetRawMotorPower( 1, test_duty, BACKWARD );
        dbgprintf("BACKWARD DS: (%d)\n\r", test_duty);
#endif 
 
        time = chThdSleepUntilWindowed( time, time + MS2ST( 300 ) );
    }
}

/*
 * @brief   Test motor control in percents  
 * @note    Duty cycle could be changed [-100, 100]
 *          Stable for incorrect value of duty cycle 
 *          >= 0        FORWARD     
 *           < 0        BACKWARD
 */
void testMotorControlRoutine( void )
{
    debug_stream_init( ); 
    lldControlInit( );

    lldControlValue_t   test_duty_prc   = 0; 
    lldControlValue_t   test_delta_prc  = 10;

    systime_t   time = chVTGetSystemTimeX( );
    while( true )
    {
        char rcv_data   = sdGetTimeout( &SD3, TIME_IMMEDIATE ); 

        switch( rcv_data )
        {
            case 'a':
                test_duty_prc += test_delta_prc;
                break; 
            
            case 's':
                test_duty_prc -= test_delta_prc;
                break;

            case ' ':
                test_duty_prc = 0;
                break; 
            
            default:
                break; 
        }
        test_duty_prc = CLIP_VALUE( test_duty_prc, LLD_MOTOR_MIN_PRC, LLD_MOTOR_MAX_PRC ); 
        lldControlSetMotorPower( 1, test_duty_prc );
        dbgprintf( "POWER: (%d)\n\r", test_duty_prc );

        time = chThdSleepUntilWindowed( time, time + MS2ST( 300 ) );
    }
}