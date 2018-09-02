/*
 * Evlog.h
 *
 *  Created on: 2015/06/07
 *      Author: shikama
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef EVLOG_H_
#define EVLOG_H_

#include "ev3api.h"
#include "Clock.h"
//#include "ColorSensor.h"
//#include "ColorLightSensor.h"
#include "SonarSensor.h"
#include "GyroSensor.h"
#include "MotorControl.h"
#include "RunPattern.h"
#include "Location.h"
#include "HSV.h"

#define MAX 100

struct log_data {
	int time;
	int sonar;
	int gyro;
	int arm;
	int tail;
	int lmtr;
	int rmtr;
	int pwm_L;
	int pwm_R;
	int color;
	int RAW_R;
	int RAW_G;
	int RAW_B;
	int hue;
	int saturation;
	int value;
	int bright;
	int distance;
	int x[4];
};

class EvLog {
private:
	struct log_data data[MAX];
	int wcount;			/* total number of stored bytes */
	int rcount;
	int total_count;
	int full;
	int iiflag;
	int ioflag;
	int eflag;
	int start_time;
	FILE* fp;
	char fname[32];
	ev3api::Clock*			mClock;
	// ev3api::ColorSensor* 	mColorSensor;
	// ColorLight*				mColorLight;
	// ev3api::SonarSensor*	mSonarSensor;
	ev3api::GyroSensor*		mGyroSensor;
	MotorControl*			mMotorControl;
	RunPattern*				mRunPattern;
	HSV*					mHSV;
	RoboLoc* 				mRloc;
	int mMaxRecord;
public:
	EvLog(ev3api::Clock*, /*ev3api::SonarSensor*,*/ ev3api::GyroSensor*, MotorControl*, RunPattern*, HSV*, RoboLoc*, int max_record);
	void input(int x1, int x2, int x3, int x4);
	void input(int cflag, int x1, int x2, int x3, int x4);
	void output(int eflag);
	//int log_queue(void) { return (wcount - rcount); }
	//int get_time(void) { return((int) mClock->now() - start_time); }
	//void set_start_time(void) { start_time = (int) mClock->now(); }
};

#endif /* EVLOG_H_ */

#ifdef __cplusplus
}
#endif
