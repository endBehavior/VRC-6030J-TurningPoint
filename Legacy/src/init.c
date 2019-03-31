/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
    taskCreate(slewControlTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT - 1);

    rightDriveEncoder = encoderInit(RIGHT_DRIVE_ENCODER_TOP, RIGHT_DRIVE_ENCODER_BOT, false);
    leftDriveEncoder = encoderInit(LEFT_DRIVE_ENCODER_TOP, LEFT_DRIVE_ENCODER_BOT, true);
    backDriveEncoder = encoderInit(BACK_DRIVE_ENCODER_TOP, BACK_DRIVE_ENCODER_BOT, false);
    flyWheelEncoder = encoderInit(FLYWHEEL_ENCODER_TOP, FLYWHEEL_ENCODER_BOT, true);
    gyro = gyroInit(GYRO_PORT, 0);
    /*
    analogCalibrate(ACCEL_X_AXIS);
    analogCalibrate(ACCEL_Y_AXIS);
    analogCalibrate(ACCEL_Z_AXIS);*/
}