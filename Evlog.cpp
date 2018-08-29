/*
 * Evlog.cpp
 *
 *  Created on: 2015/06/07
 *      Author: shikama
 */
#include "Evlog.h"
#include <stdio.h>
#include <string.h>

EvLog::EvLog(ev3api::Clock* clock,
			 // ev3api::ColorSensor* colorSensor,
			 // ev3api::SonarSensor* sonarSensor,
			 ev3api::GyroSensor*	gyroSensor,
			 MotorControl* motorControl,
			 RunPattern* RunPattern,
			 HSV* HSV,
			 RoboLoc* rLoc,
			 int max_record)
	: mClock(clock),
	  // mColorSensor(colorSensor),
	  // mSonarSensor(sonarSensor),
	  mGyroSensor(gyroSensor),
	  mMotorControl(motorControl),
	  mRunPattern(RunPattern),
	  mHSV(HSV),
	  mRloc(rLoc),
	  mMaxRecord(max_record) {
	wcount = 0;
	rcount = 0;
	full = 0;
	iiflag = 1;
	ioflag = 1;
	total_count = 0;
	//mMaxRecord = 100000;

	char str[32] = "";
	char str1[] = "evlog_";
	char str2[] = ".csv";
	char s[16];
	int n = 0;
	FILE* ffp;

	if ((ffp = fopen("File_no.txt", "r")) == NULL){}
	else {
		fscanf(ffp, "%d", &n);
		fclose(ffp);
	}
	printf("n = %d\n", n);
	if ((ffp = fopen("File_no.txt", "w")) == NULL){
		fprintf(stderr, "Cant Open File!!\n");
	}
	n++;
	fprintf(ffp, "%d", n);
	sprintf(s, "%d", n);

	strcat(str, str1);
	strcat(str, s);
	strcat(str, str2);
	strcpy(fname, str);
	fclose(ffp);
}

void EvLog::input(int x1, int x2, int x3, int x4)
{
	if (iiflag) {
		start_time = (int) mClock->now();		// 書き込み開始時間初期化
		iiflag = 0;
	}
	if (full == 1) return;
	if (wcount - rcount > MAX) {
		full = 1;
		return;
	}
	int n = wcount % MAX;
	data[n].time = (int) mClock->now() - start_time;
	data[n].sonar = (int) mRunPattern->GetSonarDistance();
	data[n].gyro = (int) mGyroSensor->getAnglerVelocity();
	data[n].arm = (int) mMotorControl->GetArmCount();
	data[n].tail = (int) mMotorControl->GetTailCount();
	data[n].lmtr = (int) mMotorControl->GetLeftWheelCount();
	data[n].rmtr = (int) mMotorControl->GetRightWheelCount();
	data[n].pwm_L = (int) mRunPattern->GetPWM_L();
	data[n].pwm_R = (int) mRunPattern->GetPWM_R();
	data[n].color = (int) mHSV->GetColorNumber();
	// data[n].color = (int) mHSV->getColorNumber();
	data[n].RAW_R = (int) mHSV->GetRAW_R();
	data[n].RAW_G = (int) mHSV->GetRAW_G();
	data[n].RAW_B = (int) mHSV->GetRAW_B();
	data[n].hue = (int) mHSV->GetHue();
	data[n].saturation = (int) mHSV->GetSaturation();
	data[n].value = (int) mHSV->GetValue();
	// data[n].bright = (int) mHSV->getBrightness();
	data[n].bright = 0;
	data[n].distance = (int) mRloc->distance;
	data[n].x[0] = x1;
	data[n].x[1] = x2;
	data[n].x[2] = x3;
	data[n].x[3] = x4;
	++wcount;
}

void EvLog::input(int cflag, int x1, int x2, int x3, int x4)
{
	if (iiflag) {
		start_time = (int) mClock->now();
		iiflag = 0;
	}
	if (full == 1) return;
	if (wcount - rcount > MAX) {
		full = 1;
		return;
	}
	int n = wcount % MAX;
	data[n].time = (int) mClock->now() - start_time;
	data[n].sonar = (int) mRunPattern->GetSonarDistance();
	data[n].gyro = (int) mGyroSensor->getAnglerVelocity();
	data[n].arm = (int) mMotorControl->GetArmCount();
	data[n].tail = (int) mMotorControl->GetTailCount();
	data[n].lmtr = (int) mMotorControl->GetLeftWheelCount();
	data[n].rmtr = (int) mMotorControl->GetRightWheelCount();
	data[n].pwm_L = (int) mRunPattern->GetPWM_L();
	data[n].pwm_R = (int) mRunPattern->GetPWM_R();
	data[n].color = (int) mHSV->GetColorNumber();
	// data[n].color = (int) mHSV->getColorNumber();
	data[n].RAW_R = (int) mHSV->GetRAW_R();
	data[n].RAW_G = (int) mHSV->GetRAW_G();
	data[n].RAW_B = (int) mHSV->GetRAW_B();
	data[n].hue = (int) mHSV->GetHue();
	data[n].saturation = (int) mHSV->GetSaturation();
	data[n].value = (int) mHSV->GetValue();
	// data[n].bright = (int) mHSV->getBrightness();
	data[n].bright = 0;
	data[n].distance = (int) mRloc->distance;
	data[n].x[0] = x1;
	data[n].x[1] = x2;
	data[n].x[2] = x3;
	data[n].x[3] = x4;
	++wcount;
}

void EvLog::output(int eflag)
{
	int i;
	if (total_count == mMaxRecord) { return; }
	if (ioflag == 1) {
		fp = fopen(fname, "w");
		fprintf(fp,"time, arm, tail, sonar, gyro, lmtr, rmtr, pwm_L, pwm_R, color, RAW_R, RAW_G, RAW_B, hue, saturation, value, bright, distance, x1, x2, x3, x4\n");
		ioflag = 0;
	}
	while (wcount != rcount) {
		i = rcount % MAX;
		fprintf(fp,"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
				data[i].time, data[i].arm, data[i].tail, data[i].sonar, data[i].gyro, data[i].lmtr, data[i].rmtr,
				data[i].pwm_L, data[i].pwm_R, data[i].color, data[i].RAW_R, data[i].RAW_G, data[i].RAW_B,
				data[i].hue, data[i].saturation, data[i].value, data[i].bright, data[i].distance,
				data[i].x[0], data[i].x[1], data[i].x[2], data[i].x[3]);
		++rcount;
		++total_count;
	}
	if (eflag == 1) fclose(fp);
}