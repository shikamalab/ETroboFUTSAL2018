/*********************************************************************
*   2017-07-19
*   Yuki Ando
*********************************************************************/

#ifndef EV3_UNIT_MOTORCONTROL_H_
#define EV3_UNIT_MOTORCONTROL_H_

#include "Motor.h"

// #define P_GAIN          2.5F
// #define PWM_ABS_MAX 	60

class MotorControl {
private:
	ev3api::Motor* 		mArmMotor;
	ev3api::Motor* 		mTailMotor;
	ev3api::Motor* 		mLeftWheel;
	ev3api::Motor* 		mRightWheel;
public:
    MotorControl(ev3api::Motor*, ev3api::Motor*, ev3api::Motor*, ev3api::Motor*);
    int8_t pwm_limit(int8_t);
    void wheels_stop(void);
    void wheels_reset(void);
    void set_wheels_PWM(int32_t pwm_R, int32_t pwm_L);
    void arm_init_zero(void);
    void arm_reset(void);
    void arm_hold(int32_t pwm_Arm);
    void tail_reset(void);
    void tail_hold(int32_t pwm_Tail);
    void tail_spin(int32_t pwm_Tail);
    int GetArmCount(void) {return mArmMotor->getCount();};
    int GetTailCount(void) {return mTailMotor->getCount();};
    int GetLeftWheelCount(void) {return mLeftWheel->getCount();};
    int GetRightWheelCount(void) {return mRightWheel->getCount();};
};

#endif