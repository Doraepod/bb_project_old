#ifndef INCLUDE_TESTS_H_
#define INCLUDE_TESTS_H_

#include <common.h>

/*============================================================================*/
/* Motors Control Tests                                                       */
/*============================================================================*/

/*
 * @brief   Test motor direction control 
 * @note    Duty cycle is constant 
 */
void testRawMotorDirectionControlRoutine( void );

/*
 * @brief   Test raw motor control 
 * @note    Duty cycle could be changed [0, 20000]
 *          Stable for incorrect value of duty cycle 
 *          Direction is controlled via defines
 *          MOTOR_FORWARD || MOTOR_BACKWARD 
 */
void testRawMotorControlRoutine( void );

/*
 * @brief   Test motor control in percents  
 * @note    Duty cycle could be changed [-100, 100]
 *          Stable for incorrect value of duty cycle 
 *          >= 0        FORWARD     
 *           < 0        BACKWARD
 */
void testMotorControlRoutine( void );

/*============================================================================*/
/* Encoder Tests                                                              */
/*============================================================================*/

/**
 * @brief   Test common encoder routine 
 * @note    Print number of ticks, (int)revs and state of direction
 *          0   - clockwise 
 *          1   - counterclockwise  
 */
void testEncoderRoutine( void );

/*============================================================================*/
/* Odometry Tests                                                             */
/*============================================================================*/

/*
 * @brief   Test motor speed 
 */
void testMotorSpeed( void );

#endif /* INCLUDE_TESTS_H_ */
