#ifdef __cplusplus
extern "C" {
#endif

#ifndef RUNPATTERN_H_
#define RUNPATTERN_H_


#define LIGHT_WHITE_BLOCK	25
#define LIGHT_GRAY_BLOCK	15
// これにしたい
#define LIGHT_WHITE		24
#define LIGHT_GRAY		12
// 下はマジックナンバーなんやけど・・・
// #define LIGHT_WHITE		24
// #define LIGHT_GRAY		32
#define LIGHT_WOOD		7
#define LIGHT_BLACK 	0

// ET相撲NEO土俵情報用
#define SAME_COLOR_RING_AND_BLOCK 4
#define _RED_ 2
#define _GREEN_ 3
#define _BLUE_ 4
#define _YELLOW_ 5

#define CENTER_DISTANCE 100

#include "ev3api.h"
#include "Clock.h"
#include "SonarSensor.h"
#include "MotorControl.h"
#include "Pid.h"
#include "Location.h"
#include "HSV.h"

class RunPattern
{
private:
	// ev3api::SonarSensor*	mSonarSensor;
	ev3api::Clock*			mClock;
	MotorControl*			mMotorControl;
	HSV* 					mHSV;
	RoboLoc* 				mRloc;
	Pid mPid;
	int forward;
	int turn;
	int pwm_L;
	int pwm_R;
	int count;
	int eye;
	int start_time;
	double target_distance;
	float av_angle;
	double m_sum_angle;

    // ET相撲NEO土俵情報
	int NEO[8] = {_BLUE_,_RED_,_YELLOW_,_GREEN_,_BLUE_,_RED_,_YELLOW_,_GREEN_};
	int ring_count;
	int same_ring_count;
public:
	RunPattern(/*ev3api::SonarSensor*,*/ MotorControl*, HSV*, RoboLoc*);
	void move(int forward_value, int turn);
	void move(int forward_value, int turn, int distance);
	void run_onoff(int forward_value);
	void run_onoff_r(int);
	void run_onoff(int forward_value, int distance_mm);
	void run_onoff_r(int, int);
	void set_pid_params(float p, float i, float d);
	void reset_pid_params();
	void run_pid(int forward_value);
	void run_pid(int edge, int forward_value);
	void run_pid(int edge, int forward_value, int distance_mm);
	void TurnR90(void);
	void TurnL90(void);
	void TurnL80(void);
	void TurnR180(void);
	void TurnL180(void);
	void TurnR(int);
	void TurnRWithBlock(int);
	void TurnL(int);
	void TurnLWithBlock(int);
	void Turn(int);
	void TurnWithBlock(int);
	void TurnCheck(void);
	void ColorDetect(int);
	void Release(int);
	void Chusya();
	void ShortCut();
	void LineDetect(int);
	void LineDetectAI(void);
	void setStartTime() {start_time = mClock->now();};
	void eyesight(int sonar_distance_cm);
	int RingDetect();
	int GetBlockColor();
	void AcrossTheLine(int area, int dist);
	void DigitalAns(void);
	void AnalogAns(void);
	void AnalogSep(void);
	void banzai(void);
	void SetArmAngle(int pwm_Arm, int32_t angle);
	void SetTailAngle(int pwm_Tail, int angel);
	int RunInBlack(int);
	int RGB2HSV(void);
	void run_hsv(void);
	int GetSonarDistance(void) {return sonar_distance;};
	int GetPWM_R(void) {return pwm_R;};
	int GetPWM_L(void) {return pwm_L;};
	void RailDetect(int area, int dist);
	void KenShow(void);
	bool flag_NEO;
	int sonar_distance;
	int colorflag;
	int Digital = 5;
	int Analog = 6;
	int White[9] = {0};
	int Black[9] = {0};
	int box_i = 0;
};

#endif

#ifdef __cplusplus
}
#endif
