/*********************************************************************
*   2017-07-19
*   Yuki Ando
*********************************************************************/

#include "MotorControl.h"

MotorControl::MotorControl(ev3api::Motor* armMotor,
						ev3api::Motor* tailMotor,
						ev3api::Motor* leftWheel,
						ev3api::Motor* rightWheel)
    :	mArmMotor(armMotor),
    	mTailMotor(tailMotor),
		mLeftWheel(leftWheel),
		mRightWheel(rightWheel){
}

int8_t MotorControl::pwm_limit(int8_t pwm_value){
	if (pwm_value > 100) return 100;
	else if (pwm_value < -100) return -100;
	else return pwm_value;
}

void MotorControl::wheels_stop(void){
	mRightWheel->stop();
	mLeftWheel->stop();
}

void MotorControl::wheels_reset(void){
	mRightWheel->reset();
	mLeftWheel->reset();
}

void MotorControl::set_wheels_PWM(int32_t pwm_R, int32_t pwm_L){
	mRightWheel->setPWM(pwm_R);
	mLeftWheel->setPWM(pwm_L);
}

void MotorControl::arm_init_zero(void){
	int current_angle;
	int max = mArmMotor->getCount();
	int count = 0;
	while (1) {
		mArmMotor->setPWM(30);
		tslp_tsk(10);
		current_angle = mArmMotor->getCount();
		if (current_angle > max) {
			count = 0;
			max = current_angle;
		}
		else {
			if (++count == 10) break;
		}
	}
	int min = mArmMotor->getCount();
	count = 0;
	while (1) {
		mArmMotor->setPWM(-30);
		tslp_tsk(10);
		current_angle = mArmMotor->getCount();
		if (current_angle < min) {
			count = 0;
			min = current_angle;
		}
		else {
			if (++count == 10) break;
		}
	}
	while (mArmMotor->getCount() < (min + 30)) {
		mArmMotor->setPWM(10);
		tslp_tsk(10);
	}
}

void MotorControl::arm_reset(){
	// mArm_angle = 0;
	mArmMotor->reset();
}

void MotorControl::arm_hold(int32_t pwm_Arm){
	if (pwm_Arm == 0)	{
		mArmMotor->stop();
	} else {
		mArmMotor->setPWM(pwm_Arm);
	}
// mArm_angle = angle;
 //    pwm_Arm = (float)(mArm_angle - mArmMotor->getCount()) * P_GAIN; /* 比例制御 */
 //    /* PWM出力飽和処理 */
 //    if (pwm_Arm > PWM_ABS_MAX)
 //    {
 //        pwm_Arm = PWM_ABS_MAX;
 //    }
 //    else if (pwm_Arm < -PWM_ABS_MAX)
 //    {
 //        pwm_Arm = -PWM_ABS_MAX;
 //    }
 //    mArmMotor->setPWM(pwm_Arm);
}

void MotorControl::tail_reset(){
	mTailMotor->reset();
}

void MotorControl::tail_hold(int32_t pwm_Tail){
	if (pwm_Tail == 0)	{
		mTailMotor->stop();
	} else {
		mTailMotor->setPWM(pwm_Tail);
	}
}

void MotorControl::tail_spin(int32_t pwm_Tail){
	int tail_deg = mTailMotor->getCount() % 360;
	if(pwm_Tail == 0) {
		mTailMotor->setPWM(-30);
		// 尻尾を初期位置に戻したら抜ける
		while (tail_deg > 1) {
			tail_deg = mTailMotor->getCount() % 360;
		}
		mTailMotor->reset();
	}
	mTailMotor->setPWM(pwm_Tail);
}