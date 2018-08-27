/*
 * Location.h
 *
 *  Created on: 2012/03/05
 *      Author: shikama
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include <math.h>
#define M 100				// 1区間のログデータ数

class RoboLoc {
private:
	double pthr;
	double pthl;
	double thr;
	double thl;
	double tr;
	double tl;
	double w;
	double d;
	double R;
	int n;
public:
	RoboLoc(double rad, double width, double gratio);	// dia: 車輪の半径、width: 車輪間隔の1/2、ギア比
	void input(int n6, int n7);
	unsigned char flag;
	double D;
	double GR;
	double x;				//　走行体のx座標
	double y;				//　走行体のy座標
	double omega;			//　走行体の角度(rad)
	double omega_d;			//　走行体の角度（度）
	double distance;		//　走行体の総走行距離
	double raw_w(void) { return w; }
};

#endif /* LOCATION_H_ */
