#include "RunPattern.h"
#include <stdlib.h>
extern int wait_event(void);

//using namespace ev3api;

RunPattern::RunPattern(/*ev3api::SonarSensor* sonarSensor,*/
					MotorControl* motorControl,
					HSV* HSV,
					RoboLoc* rLoc)
	:	/*mSonarSensor(sonarSensor),*/
		mMotorControl(motorControl),
		mHSV(HSV),
		mRloc(rLoc) {
		forward = 0;
		turn = 0;
		pwm_R = 0;
		pwm_L = 0;
		mPid.set_params(0.5, 0.05, 0.1);	// 0.5, 0.05, 0.1
		count = 0;
		eye = 0;
		sonar_distance = 255;
		flag_NEO = 0;
		av_angle = 10000;
		ring_count = 0;
        same_ring_count = 0;
		mClock = new ev3api::Clock();
}

void RunPattern::move(int forward_value, int turn){
	forward = forward_value;
	if (forward > 0) {
		pwm_L = mMotorControl->pwm_limit(forward + turn);
		pwm_R = mMotorControl->pwm_limit(forward - turn);
//		mMotorControl->arm_hold(0);
		mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
	} else {
		pwm_L = mMotorControl->pwm_limit(forward + turn);
		pwm_R = mMotorControl->pwm_limit(forward - turn);
//		mMotorControl->arm_hold(0);
		mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
	}
	if (wait_event())	ext_tsk();
}

void RunPattern::move(int forward_value, int turn, int distance){
	forward = forward_value;
	int start_dist = mRloc->distance;
	if (forward_value > 0) {
		while ((mRloc->distance - start_dist) < distance) {
			pwm_L = mMotorControl->pwm_limit(forward + turn);
			pwm_R = mMotorControl->pwm_limit(forward - turn);
//			mMotorControl->arm_hold(0);
			mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
			if (wait_event())	ext_tsk();
		}
	} else {
		while ((start_dist - mRloc->distance) < distance) {
			pwm_L = mMotorControl->pwm_limit(forward + turn);
			pwm_R = mMotorControl->pwm_limit(forward - turn);
//			mMotorControl->arm_hold(0);
			mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
			if (wait_event())	ext_tsk();
		}
	}
}

void RunPattern::run_onoff(int forward_value){
	forward = forward_value;
	if(flag_NEO == true)
		if (mHSV->GetValue() >= (LIGHT_WOOD + LIGHT_BLACK)/2) { //木なら
			turn = 5;  /* 右旋回命令 */
		} else {
			turn = -5; /* 左旋回命令 */
		}
	else {
		if (mHSV->GetValue() >= (LIGHT_WHITE + LIGHT_BLACK)/2) { //白なら
			turn = 5;  /* 右旋回命令 */
		} else {
			turn = -5; /* 左旋回命令 */
		}
	}
	pwm_L = mMotorControl->pwm_limit(forward + turn);
	pwm_R = mMotorControl->pwm_limit(forward - turn);
//	mMotorControl->arm_hold(0);
	mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
	if (wait_event())	ext_tsk();
}

void RunPattern::run_onoff_r(int forward_value){
	forward = forward_value;
	if(flag_NEO == true)
		if (mHSV->GetValue() >= (LIGHT_WOOD + LIGHT_BLACK)/2) { //木なら
			turn = -3;  /* 右旋回命令 */
		} else {
			turn = 3; /* 左旋回命令 */
		}
	else {
		if (mHSV->GetValue() >= (LIGHT_WHITE + LIGHT_BLACK)/2) { //白なら
			turn = -3;  /* 右旋回命令 */
		} else {
			turn = 3; /* 左旋回命令 */
		}
	}
	pwm_L = mMotorControl->pwm_limit(forward + turn);
	pwm_R = mMotorControl->pwm_limit(forward - turn);
//	mMotorControl->arm_hold(0);
	mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
	if (wait_event())	ext_tsk();
}

void RunPattern::run_onoff(int forward_value, int distance_mm){
	forward = forward_value;
	int start_dist = mRloc->distance;
	while ((mRloc->distance - start_dist) < distance_mm) {
	if(flag_NEO == true)
		if (mHSV->GetValue() >= (LIGHT_WOOD + LIGHT_BLACK)/2) { //木なら
			turn = 5;  /* 右旋回命令 */
		} else {
			turn = -5; /* 左旋回命令 */
		}
	else {
		if (mHSV->GetValue() >= (LIGHT_WHITE + LIGHT_BLACK)/2) { //白なら
			turn = 5;  /* 右旋回命令 */
		} else {
			turn = -5; /* 左旋回命令 */
		}
	}
		pwm_L = mMotorControl->pwm_limit(forward + turn);
		pwm_R = mMotorControl->pwm_limit(forward - turn);
//		mMotorControl->arm_hold(0);
		mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
		if (wait_event()) {
			ext_tsk();
		}
	}
}

void RunPattern::run_onoff_r(int forward_value, int distance_mm){
	forward = forward_value;
	int start_dist = mRloc->distance;
	while ((mRloc->distance - start_dist) < distance_mm) {
	if(flag_NEO == true)
		if (mHSV->GetValue() >= (LIGHT_WOOD + LIGHT_BLACK)/2) { //木なら
			turn = -7;  /* 右旋回命令 */
		} else {
			turn = 7; /* 左旋回命令 */
		}
	else {
		if (mHSV->GetValue() >= (LIGHT_WHITE + LIGHT_BLACK)/2) { //白なら
			turn = -7;  /* 右旋回命令 */
		} else {
			turn = 7; /* 左旋回命令 */
		}
	}
		pwm_L = mMotorControl->pwm_limit(forward + turn);
		pwm_R = mMotorControl->pwm_limit(forward - turn);
//		mMotorControl->arm_hold(0);
		mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
		if (wait_event()) {
			ext_tsk();
		}
	}
}

void RunPattern::set_pid_params(float p, float i, float d){
	mPid.set_params(p, i, d);
}

void RunPattern::reset_pid_params(){
	mPid.reset();
}

void RunPattern::run_pid(int forward_value){
	forward = forward_value;
	int err = mHSV->GetValue() - (LIGHT_WHITE + LIGHT_BLACK)/2;
	turn = mPid.input(err);
	pwm_L = mMotorControl->pwm_limit(forward + turn);
	pwm_R = mMotorControl->pwm_limit(forward - turn);
//	mMotorControl->arm_hold(0);
	mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
	if (wait_event()) {
		ext_tsk();
	}
}

void RunPattern::run_pid(int edge, int forward_value){
	forward = forward_value;
	int err = mHSV->GetValue() - (LIGHT_WHITE + LIGHT_BLACK)/2;
	if (edge & 0b00000010) {err = mHSV->GetValue() - (LIGHT_GRAY + LIGHT_BLACK)/2;}		//これじゃなくて
	// if (edge & 0b00000010) {err = mHSV->GetValue() - (LIGHT_GRAY + LIGHT_WHITE)/2;}	//これにしたい
	if (edge & 0b00000100) {err = mHSV->GetValue() - (LIGHT_WOOD + LIGHT_BLACK)/2;}
	if (edge & 0b00001000) {err = mHSV->GetValue() - (LIGHT_WHITE_BLOCK + LIGHT_BLACK)/2;}
	if (edge & 0b00010000) {err = mHSV->GetValue() - (LIGHT_WHITE_BLOCK + LIGHT_GRAY_BLOCK)/2;}
	turn = mPid.input(err);
	if (edge & 0b0001) { turn = -turn; } /* 1bit目が1なら右エッジ */
	pwm_L = mMotorControl->pwm_limit(forward + turn);
	pwm_R = mMotorControl->pwm_limit(forward - turn);
//	mMotorControl->arm_hold(0);
	mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
	if (wait_event()) {
		ext_tsk();
	}
}

// void RunPattern::run_pid(int edge, int forward_value){
// 	forward = forward_value;
// 	int err = mHSV->GetValue() - (LIGHT_WHITE + LIGHT_BLACK)/2;
// 	if(edge == 2) {err = mHSV->GetValue() - (LIGHT_GRAY + LIGHT_BLACK)/2;}
// 	if(edge == 3) {err = mHSV->GetValue() - (LIGHT_WOOD + LIGHT_BLACK)/2;}
// 	turn = mPid.input(err);
// 	if (edge == 1 || edge == 2) { turn = -turn; } /* edge == 1 -> right edge */
// 	pwm_L = mMotorControl->pwm_limit(forward + turn);
// 	pwm_R = mMotorControl->pwm_limit(forward - turn);
// //	mMotorControl->arm_hold(0);
// 	mMotorControl->set_wheels_PWM(pwm_R, pwm_L);
// 	if (wait_event()) {
// 		ext_tsk();
// 	}
// }

void RunPattern::run_pid(int edge, int forward_value, int distance_mm){
	int start_dist = mRloc->distance;
	while ((mRloc->distance - start_dist) < distance_mm) {
		run_pid(edge, forward_value);
	}
}

// void RunPattern::TurnR(int angle){
// 	//angle = angle * 95 / 90;	//誤差調整
// 	int startAngle = mRloc->omega_d + 90;
// 	while(1){
// 		move(3, 7, 3);
// 		if((startAngle - mRloc->omega_d) <= 0 ){
// 			break;
// 		}
// 	}
// }

void RunPattern::TurnR90(){
	int startAngle = mRloc->omega_d;
	while(1){
		move(4, 25);//3,17 or 4,25
		if((mRloc->omega_d - startAngle) >= 94 ){	//93yoyu-
			break;
		}
	}
}

void RunPattern::TurnL90(){
	int startAngle = mRloc->omega_d - 95;	// 誤差調整
	while(1){
		move(-4, -25);//-3,-17 or -4,-25
		if((mRloc->omega_d - startAngle) <= 0 ){
			break;
		}
	}
}

void RunPattern::TurnL80(){
	int startAngle = mRloc->omega_d - 83;	// 誤差調整
	while(1){
		move(-4, -25);//-3,-17 or -4,-25
		if((mRloc->omega_d - startAngle) <= 0 ){
			break;
		}
	}
}

void RunPattern::TurnR180(){
	int startAngle = mRloc->omega_d;
	while(1){
		move(4, 25);//3,17 or 4,25
		if((mRloc->omega_d - startAngle) >= 188 ){	//93yoyu-
			break;
		}
	}
}

void RunPattern::TurnL180(){
	int startAngle = mRloc->omega_d - 189;	// 誤差調整
	while(1){
		move(-4, -25);//-3,-17 or -4,-25
		if((mRloc->omega_d - startAngle) <= 0 ){
			break;
		}
	}
}

void RunPattern::TurnR(int angle){
	int startAngle = mRloc->omega_d;
	// angle = angle * 1.1;	//誤差調整1.10
	switch(angle){
		case 30:
			angle = 25;	//31
			break;
		case 45:
			angle = 40;	//46
			break;
		case 60:
			angle = 56;	//62
			break;
		case 90:
			angle = 88;	//93
			break;
		case 120:
			angle = 120;	//124
			break;
		case 135:
			angle = 137;	//137
			break;
		case 150:
			angle = 155;	//155
			break;
		case 180:
			angle = 188;	//188
			break;
		default:
			angle = angle * 89 / 90;
	}
	
	while(1){
		move(-4, 25);	//forward, turn, -2, 18
		if((mRloc->omega_d - startAngle) >= angle ){
			break;
		}
	}
}


void RunPattern::TurnRWithBlock(int angle){
	int startAngle = mRloc->omega_d;
	// angle = angle * 1.1;	//誤差調整1.10
	switch(angle){
		case 30:
			angle = 25;
			break;
		case 45:
			angle = 40;
			break;
		case 60:
			angle = 56;
			break;
		case 90:
			angle = 88;
			break;
		case 120:
			angle = 120;
			break;
		case 135:
			angle = 137;
			break;
		case 150:
			angle = 155;
			break;
		case 180:
			angle = 187;
			break;
		default:
			angle = angle * 93 / 90;
	}

	while(1){
		move(-2, 9);	//forward, turn, 2, 13
		if((mRloc->omega_d - startAngle) >= angle ){
			break;
		}
	}
}


//左回転でAngleは減少
void RunPattern::TurnL(int angle){
 	switch(angle){
 		//若干少なめかと思われ
 		//用変更
 		//75do
		case 30:
			angle = 20;	//31
			break;
		case 45:
			angle = 35;	//46
			break;
		case 60:
			angle = 51;	//62
			break;
		case 90:
			angle = 82;	//92
			break;
		case 120:
			angle = 117;	//123
			break;
		case 135:
			angle = 134;	//137
			break;
		case 150:
			angle = 152;	//155
			break;
		case 180:
			angle = 186;	//186
			break;
		default:
			angle = angle * 89 / 90;
	}
	int startAngle = mRloc->omega_d - angle;
	while(1){
		move(5, -22);	//4,-24
		if((mRloc->omega_d - startAngle) <= 0 ){
			break;
		}
	}
}


void RunPattern::TurnLWithBlock(int angle){
	switch(angle){
 		//若干少なめかと思われ
 		//用変更
 		//75do
		case 30:
			angle = 20;
			break;
		case 45:
			angle = 35;
			break;
		case 60:
			angle = 51;
			break;
		case 90:
			angle = 82;
			break;
		case 120:
			angle = 117;
			break;
		case 135:
			angle = 134;
			break;
		case 150:
			angle = 152;
			break;
		case 180:
			angle = 186;
			break;
		default:
			angle = angle * 93 / 90;
	}
	int startAngle = mRloc->omega_d - angle;
	while(1){
		if (angle < 100)
			move(3, -9);	//3,-10
		else
			move(1, -8);
		if((mRloc->omega_d - startAngle) <= 0 ){
			break;
		}
	}
}

void RunPattern::Turn(int angle){
	double err;
	double start_dist = mRloc->distance;
	double dist = (angle > 0) ? 63 : 66;	//sasetunara

	while((mRloc->distance - start_dist) <= dist){//68
		err = mRloc->omega_d - m_sum_angle;
		if (err > 0) move(25, -2);//15
		else move(25, 2);//15
	}
	if (angle > 0){
		TurnL(angle);
	} else if (angle < 0) {
		TurnR(-angle);
	}
}

void RunPattern::TurnWithBlock(int angle){
	double err;
	double start_dist = mRloc->distance;
	double dist = (angle > 0) ? 63 : 68;

	while((mRloc->distance - start_dist) <= dist){//70
		err = mRloc->omega_d - m_sum_angle;
		if (err > 0) move(25, -2);//15
		else move(25, 2);//15
	}

	if (angle == -180)
		TurnLWithBlock(-angle);
	else if (angle > 0)
		TurnLWithBlock(angle);
	else if (angle < 0)
		TurnRWithBlock(-angle);


}

void RunPattern::ColorDetect(int line){
	int state = 0;
	int count = 0;
	int color;
	// double start_dist = mRloc->distance;

	run_pid(9, 30, 68);	//edge, forward, distance (9,30,65) (9,35,82)
	m_sum_angle = mRloc->omega_d;
	while (1) {
		if (state == 0) {
			line == 1 ? move(30, 0) : run_pid(9, 30);//20
			//run_onoff_r(19);//20
			color = mHSV->GetColorNumber();
			//100mm手前に来るまで色を読まない
			switch (color) {
				case 0:
				case 1:
					count = 0;
					break;
				case 2:	// RED
				case 3: // GREEN
				case 4: // BLUE
				case 5: // YELLOW
				case 6:	//WOOD
					if (++count == 8) {//8
						state = 1;
					}
					break;
				default:
					count = 0;
					break;
			}
			m_sum_angle = 0.05 * mRloc->omega_d + 0.95 * m_sum_angle;
		}
		else {
			break;
		}
		if (wait_event())	ext_tsk();
	}
}

void RunPattern::Release(int line){	//1ならラインなし
	double err;
	double start_dist = mRloc->distance;

	while (1) {
		err = mRloc->omega_d - m_sum_angle;
		if (err > 0) move(-15, -2);//15
		else move(-15, 2);//15
		if (mRloc->distance - start_dist <= -80){
			TurnR(180);
			break;

		}
		if (wait_event())	ext_tsk();
	}
	line ? ColorDetect(1) : ColorDetect(0);
}

void RunPattern::Chusya(){
	int startAngle = mRloc->omega_d - 90;
	while(1){
		move(30, -20);//15
		//mMotorControl->set_wheels_PWM(70, 20);	//R, L
		if((mRloc->omega_d - startAngle) <= 0 ){
			break;
		}
	}
	int start_dist = mRloc->distance;
	while(mRloc->distance - start_dist <= 50){
		move(30, 0);
	}	
	startAngle = mRloc->omega_d - 90;
	while(1){
		move(20, -20);//15
		//mMotorControl->set_wheels_PWM(70, 0);
		if((mRloc->omega_d - startAngle) <= 0 ){
			break;
		}
		//if (wait_event())	ext_tsk();
	}
}

void RunPattern::ShortCut(){
	int count = 0;
	//int omegaCount = 0;
	int start_dist = mRloc->distance;
	float err;
	//StartUp
	while(mRloc->distance - start_dist <= 50){
		run_pid(0, 25);
	}
	float sum_angle = mRloc->omega_d;
	while(mRloc->distance - start_dist <= 450){
		run_pid(0, 25);
		//sum_angle += mRloc->omega_d;
		//omegaCount++;
		sum_angle = 0.05 * mRloc->omega_d + 0.95 * sum_angle;
	}

	//sum_angle = sum_angle / omegaCount;
	// err = mRloc->omega_d - sum_angle;
	// if (err > 0) move(25, -2);//15
	// else move(25, 2);//15

	while(1){	//usetu
		err = mRloc->omega_d - sum_angle;
		move(55, 45);//3,17 or 4,25
		if(err >= 90 ){	//93yoyu-
			break;
		}
	}
	start_dist = mRloc->distance;
	while(mRloc->distance - start_dist <= 300){
		err = mRloc->omega_d - sum_angle;
		if(err > 90 )	move(90, -10);
		else 			move(90, 10);
	}

	while(1){	//sasetu
		err = mRloc->omega_d - sum_angle;
		move(75, -25);//3,17 or 4,25
		if(err <= -4 ){	//93yoyu-
			break;
		}
	}
	start_dist = mRloc->distance;
	while(mRloc->distance - start_dist <= 1350){
		err = mRloc->omega_d - sum_angle;
		if(err > 0 )	move(90, -10);
		else 			move(90, 10);
	}
	count = 100;
	while(--count > 0){
		move(count, 0);
	}
	//Back Start

	while(++count <= 160){
		move(-count / 2, 0);
	}
	count = 100;

	int startAngle = mRloc->omega_d;
	while(1){
		move(-75, -25);//3,17 or 4,25
		if((mRloc->omega_d - startAngle) <= -92 ){	//93yoyu-
			break;
		}
	}

	start_dist = mRloc->distance;
	while(mRloc->distance - start_dist >= -2400){
		move(-100, 0);
	}

	TurnL(89);
	LineDetect(0);
	/*

	while(1){
		move(-70, -30);
		if((mRloc->omega_d - startAngle - 9) <= 0){
			break;
		}
	}
	start_dist = mRloc->distance;
	while(mRloc->distance - start_dist >= -1450){
		move(-100, 0);
	}
	start_dist = mRloc->distance;
	while(--count > 0){
		move(-count, 0);
	}

	//gate1 in

	count = 0;
	start_dist = mRloc->distance;
	while(mRloc->distance - start_dist <= 700){
		if (++count >= 100) count = 100;
		move(count, 0);
	}
	startAngle = mRloc->omega_d - 92;
	while(1){
		move(70, -30);//3,17 or 4,25
		if(mRloc->omega_d - startAngle <= 0){
			break;
		}
	}
	start_dist = mRloc->distance;
	while(mRloc->distance - start_dist <= 2550){
		move(100, 1);
	}
	while(--count > 0){
		move(count, 0);
	}

	TurnR(89);
	LineDetect();
	run_onoff_r(19, 1000);
	*/
    //banzai();
}

void RunPattern::LineDetect(int mode){
	int turn_value = -17;
	if (mode == 1) turn_value = -turn_value;	//右折
	int state = 0;
	int count = 0;
	int color;
	int start_dist = mRloc->distance;
	while (1) {
		if (state == 0) {
			move(25, 0);	//forward, turn, distance
			//run_onoff_r(19);//20
			color = mHSV->GetColorNumber();
			//100mm手前に来るまで色を読まない
			switch (color) {
				case 0:
					count = 0;
					break;
				case 1:
					if (++count == 3) {//7
						move(20, 0, 30);
						count = 0;
						state = 1;
					}
					break;
				case 2:	// RED
				case 3: // GREEN
				case 4: // BLUE
				case 5: // YELLOW
				case 6:	//WOOD
				default:
					count = 0;
					break;
			}
			if ((mRloc->distance - start_dist) >= 50000000) break;//tekito-
		}
		else if (state == 1) {
			move(-2, turn_value);
			color = mHSV->GetColorNumber();
			//100mm手前に来るまで色を読まない
			switch (color) {
				case 0:
					count = 0;
					break;
				case 1:
					if (++count == 3) {//7
						state = 2;
						count = 0;
					}
					break;
				case 2:	// RED
				case 3: // GREEN
				case 4: // BLUE
				case 5: // YELLOW
				case 6:	//WOOD
				default:
					count = 0;
					break;
			}
		}
		else if (state == 2){
			move(-2, turn_value);
			color = mHSV->GetColorNumber();
			//100mm手前に来るまで色を読まない
			switch (color) {
				case 0:
				case 7:
					if (++count == 3) {//7
						state = 3;
						count = 0;
					}
					break;
				case 1:
				case 2:	// RED
				case 3: // GREEN
				case 4: // BLUE
				case 5: // YELLOW
				case 6:	//WOOD
				default:
					count = 0;
					break;
			}
		}
		else {
			break;
		}
		if (wait_event())	ext_tsk();
	}
}

void RunPattern::eyesight(int sonar_distance_cm){
	target_distance = sonar_distance_cm;
	ev3_led_set_color(LED_ORANGE);
	mMotorControl->wheels_stop();
//	mMotorControl->arm_hold(0);
	mMotorControl->tail_spin(30);
	int state = 0;
	// int current_time;
	char sonar[20];
	char time[30];
	count = 0;
	while (1) {
		// 40ms毎に超音波測距
		// if (count++ % 8 == 0) {
		// 	sonar_distance = mSonarSensor->getDistance();
		// }
		switch (state) {
			// 新幹線待機
			case 0:
				// current_time = ((mClock->now() - start_time)/1000) % 10;
				if (sonar_distance < target_distance /* || (current_time >= 4 && current_time <= 6 && eye == 1)*/) {
				// if (sonar_distance < target_distance) {
						start_time = mClock->now();
						state = 1;
						eye = 1;
				}
				break;
			// 新幹線通過後抜ける
			case 1:
				if (sonar_distance > target_distance || mClock->now() - start_time > 2500) {
					state = 2;
					mMotorControl->tail_spin(0);
					ev3_led_set_color(LED_GREEN);
					tslp_tsk(2000);	// 念の為待機
				}
				break;
			default:break;
		}
		// LCD表示
		sprintf(sonar,"state %d:%3d cm", state, sonar_distance);
		sprintf(time,"time  %10ld s", (mClock->now() - start_time)/1000);
		ev3_lcd_draw_string(sonar,0,40);
		ev3_lcd_draw_string(time,0,60);

		if (wait_event())	ext_tsk();
		if (state == 2)	break;
	}
	ev3_lcd_fill_rect(0,0,EV3_LCD_WIDTH,EV3_LCD_HEIGHT,EV3_LCD_WHITE);
	sonar_distance = 255;
}

int RunPattern::RingDetect(){
	int state = 0;
	int state_1 = 0;
	int kmrt = 0;
	int count = 0;
	int color = 0;
	float err;
	float sum_angle = mRloc->omega_d;
	int start_dist = mRloc->distance;

	run_onoff(10,70);
	while (1) {
		// リング検知
		if (state == 0) {
			run_onoff(8);
			color = mHSV->GetColorNumber();
			switch (color) {
				case 2: // RED
				case 3: // GREEN
				case 4: // BLUE
				case 5: // YELLOW
					if (++count == 6) {
						state = 1;
						start_dist = mRloc->distance;
					}
					break;
				default:
					count = 0;
					break;
			}
			sum_angle = 0.05 * mRloc->omega_d + 0.95 * sum_angle;
		}
		// 動作判定
		else if (state == 1) {
			if (state_1 == 0) {
				// 色を読むか
				if (same_ring_count < SAME_COLOR_RING_AND_BLOCK && SAME_COLOR_RING_AND_BLOCK != 8) {
					state_1 = 1;
				}
				// 違う色のみが残っている
				else if (SAME_COLOR_RING_AND_BLOCK - same_ring_count >= 8 - ring_count) {
					kmrt = 2;	// 色を読まず寄切
					ring_count++;
					same_ring_count++;
					state_1 = 2;
				}
				// 同一色のみが残っている
				else {
					kmrt = 1;	// 色を読まず押出
					ring_count++;
					state_1 = 3;
				}
			}

			err = mRloc->omega_d - sum_angle;
			if (err > 0) move(-8, -2);
			else move(-8, 2);

			// 色を読まず押出の時は下がらない
			if (state_1 == 3 || (mRloc->distance - start_dist) <= -18) {
				mMotorControl->wheels_stop();
				state = state_1 == 1 ? 2:3;
			}
		}
		// ブロックとリング色比較
		else if (state == 2) {
			if (NEO[ring_count++] == GetBlockColor()) {
				same_ring_count++;
				kmrt = 3;	// 寄切
			}
			else {
				kmrt = 0;	// 押出
			}
			state = 3;
		}
		else break;
	}
	return kmrt;	// 決まり手を返す
}

int RunPattern::GetBlockColor(){
	int state = 0;
	int color = 0;
	count = 0;
	target_distance = mRloc->distance;

	while (1){
		if (state == 0) {
			SetArmAngle(20, 45);
			state = 1;
		}
		else if (state == 1) {
			if (++count == 50) {
				state = 2;
				count = 0;
				color = mHSV->GetColorNumber();
			}
		}
		else if (state == 2) {
			if (color == mHSV->GetColorNumber()) {
				if (++count >= 10) {
					state = 3;
					count = 0;
					mHSV->Disp();
				}
			}
			else {
				color = mHSV->GetColorNumber();
				count = 0;
			}
		}
		else if (state == 3) {
			ev3_speaker_play_tone(NOTE_A4, 300);
			SetArmAngle(20, -45);
			color = color == 1 ? 3:color;
			return color;
		}
		if (wait_event())	ext_tsk();
	}
}

void RunPattern::AcrossTheLine(int area, int dist){
	int state = 0;
	int count = 0;
	int color;
	int start_dist = mRloc->distance;

	while (1) {
		if (state == 0) {
			switch(area){
				case 0:
					run_pid(1,25);
					break;
				case 1:
					run_onoff(19);
					break;
				default:
					// run_onoff(25);
					move(25, 0.0);
					break;
			}
			color = mHSV->GetColorNumber();
			//100mm手前に来るまで色を読まない
			switch (color) {
				case 0:
				case 1:
				case 2:	// RED
				case 3: // GREEN
					count = 0;
					break;
				case 4: // BLUE
					if (++count == 3) {//7
						start_dist = mRloc->distance;
						move(60, 0, 150);
						state = 1;
					}
					break;
				case 5: // YELLOW
				case 6:	//WOOD
				default:
					count = 0;
					break;
			}
			if ((mRloc->distance - start_dist) >= 50000) break;//tekito-
		}
		else if (state == 1){
			switch(area){
				case 0:
					run_pid(3, 40);
					break;
				case 1:
					// move(35, -0.45);
					run_onoff(20);
					break;
				default:
					move(25, -1.4);
					// run_onoff(20);
					break;
			}
			state = 2;
		}
		else {
			move(18, 0);//
			if ((mRloc->distance - start_dist) >= dist){
				break;
			}
		}
		if (wait_event())	ext_tsk();
	}
}

void RunPattern::banzai(){
	mMotorControl->wheels_reset();
	while (count++ < 100){
		if (wait_event())	ext_tsk();
	}
	SetArmAngle(20, 60);
	count = 0;
	while (count++ < 600){
		if (wait_event())	ext_tsk();
	}
	ev3_speaker_play_tone(NOTE_A4, 300);
}

//=============================================
//アームを指定した角度分動かす関数
//絶対角ではなく現在の角度からの相対角なので注意
//正方向で上げ、負方向で下げる。
//=============================================
void RunPattern::SetArmAngle(int pwm_Arm, int32_t angle){
	int startAngle = mMotorControl->GetArmCount();
	if (angle > 0){
		while(mMotorControl->GetArmCount() - startAngle < angle){
			mMotorControl->arm_hold(pwm_Arm);
			if (wait_event())	ext_tsk();
		}
	} else {
		while(mMotorControl->GetArmCount() - startAngle > angle){
			mMotorControl->arm_hold(-pwm_Arm);
			if (wait_event())	ext_tsk();
		}
	}
	mMotorControl->arm_hold(0);	//終了後アーム固定
	// int32_t startAngle = mMotorControl->GetArmCount();
	// if (angle > 0){
	// 	while (mMotorControl->GetArmCount() - startAngle < angle){
	// 		mMotorControl->set_arm_PWM(40);
	// 		if (wait_event())	ext_tsk();
	// 	}
	// } else {
	// 	while (startAngle - mMotorControl->GetArmCount() < angle){
	// 		mMotorControl->set_arm_PWM(-40);
	// 		if (wait_event())	ext_tsk();
	// 	}
	// }
}

void RunPattern::SetTailAngle(int pwm_Tail, int angle){
		int startAngle = mMotorControl->GetTailCount();
	if (angle > 0){
		while(mMotorControl->GetTailCount() - startAngle < angle){
			mMotorControl->tail_hold(pwm_Tail);
			if (wait_event())	ext_tsk();
		}
	} else {
		while(mMotorControl->GetTailCount() - startAngle > angle){
			mMotorControl->tail_hold(-pwm_Tail);
			if (wait_event())	ext_tsk();
		}
	}
	mMotorControl->tail_hold(0);
}

int RunPattern::RunInBlack(int forward)
{
	int color;
	int bcount = 0;
	int state = 0;
	float err;
	float sum = mRloc->omega_d;
	target_distance = mRloc->distance;
	while (1) {
		if (state == 0) {
			run_onoff(10);
//			mRm->onoff_1(0, 15, 5);
			if ((mRloc->distance - target_distance) >= 90) {
				state = 1;
				av_angle = sum;
			}
			sum = 0.05 * mRloc->omega_d + 0.95 * sum;
		}
		else if (state == 1) {
			move(forward, -3);
			if (mHSV->GetColorNumber() == 1) { //==BLACK
				if (++bcount == 25) {
					state = 2;
					bcount = 0;
				}
			}
			else bcount = 0;
		}
		else if (state == 2) {
			err = mRloc->omega_d - sum;
			if (err > 0) move(forward, -2);
			else move(forward, 2);

			color = mHSV->GetColorNumber();
			if (color == 2 || color == 3 || \
				color == 4 || color == 5) {
				if (++bcount == 10) return color;
			}
			else bcount = 0;
		}
	}
}

int RunPattern::RGB2HSV(void){
	while(1){
		mHSV->Disp();
		if (wait_event()) {
			ext_tsk();
		}
	}
	return mHSV->GetColorNumber();
}

void RunPattern::RailDetect(int area, int dist){
	int state = 0;
	int count = 0;
	target_distance = dist;
	int color;
	int start_dist = mRloc->distance;
	//////////
	SetArmAngle(30, -20);


	while (1) {
		if (state == 0) {
			move(25, 0);	//forward, turn, distance
			//run_onoff_r(19);//20
			color = mHSV->GetColorNumber();
			//100mm手前に来るまで色を読まない
			switch (color) {
				case 0:
				case 1:
				case 2:	// RED
				case 3: // GREEN
					count = 0;
					break;
				case 4: // BLUE
					if (++count == 3) {//7
						start_dist = mRloc->distance;
						SetArmAngle(50, 85);
						move(25, 0, 60);
						state = 1;
					}
					break;
				case 5: // YELLOW
				case 6:	//WOOD
				default:
					count = 0;
					break;
			}
			if ((mRloc->distance - start_dist) >= 50000) break;//tekito-
		}
		else if (state == 1){
			switch(area){
				case 0:
					move(100, 0, 20);
					move(-100, 0, 35);
					break;
				case 1:
					move(-75, 0, 20);
					break;
				default:
					move(-100, 0, 5);
					break;
			}
			state = 2;
		}
		else {
			move(18, 0);//
			if ((mRloc->distance - start_dist) >= dist){
				SetArmAngle(50, -65);
				break;
			}
		}
		if (wait_event())	ext_tsk();
	}
}

void RunPattern::KenShow(void) {
	// int state = 0;
	// int count = 0;
	// float err;
	// int color;
	// int start_dist = mRloc->distance;

	// run_pid(1,-10,200);
}