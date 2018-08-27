/*
 * pid.cpp
 *
 *      Author: shikama
 */

#include "Pid.h"

Pid::Pid(void) {
	delta_t = DELTA_T;
	integral = 0;
	diff[1] = 0;
}

float Pid::input(int error)
{
	float turn;

	diff[0] = diff[1];
	diff[1] = error;						// 偏差
	integral += ((diff[1] + diff[0])/ 2.0) * delta_t;

	p = kp * diff[1]; 						// 比例計算	P
	i = ki * integral;						// 積分		I
	d = kd * (diff[1] - diff[0]) / delta_t;	// 微分		D

	turn = p + i + d;						// 操作量

	/* 上下限値チェック */
	if (turn > 100.) turn = 100.;
	else if (turn < -100.) turn = -100.;

	return turn;							// 偏差から得られた操作量を返す
}

void Pid::set_params(float p, float i, float d) {
	kp = p;
	ki = i;
	kd = d;
}

void Pid::reset() {
	diff[0] = 0;
	diff[1] = 0;
	integral = 0;
}