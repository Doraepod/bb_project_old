#ifndef INCLUDE_ROBOT_ODOMETRY_H_
#define INCLUDE_ROBOT_ODOMETRY_H_

#include "wheel_control.h"

#define VT_PERIOD_MS      10

/**
 * @brief       Initialization of robot odometry unit
 */
void robotOdometryInit( void );

/**
 * @brief       Set reference value of v_x [m/s]
 *              (linear speed x-axis)
 */
void robotOdometrySetVx( float v_x );

/**
 * @brief       Set reference value of v_y [m/s]
 *              (linear speed y-axis)
 */
void robotOdometrySetVy( float v_y );

/**
 * @brief       Set reference value of w [rad/s]
 *              (angular speed)
 */
void robotOdometrySetW( float w );

#endif /* INCLUDE_ROBOT_ODOMETRY_H_ */