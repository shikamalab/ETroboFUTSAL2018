#ifdef __cplusplus
extern "C" {
#endif

#ifndef SCENARIO_H_
#define SCENARIO_H_

#include "ev3api.h"
//#include "RunMethod.h"
#include "RunPattern.h"
#include "Block.h"

class Scenario
{
private:
	RunPattern* mRP;
	RoboLoc* mRloc;
	Block_area*     mBArea;
	int block_ptn;
public:
	Scenario(RunPattern*, RoboLoc*, Block_area*);
	void R(void);
	void L(void);
	void RGB2HSV(void);
	void TEST(void);
	void TEST2(void);
	void DoPuzzle(void);
	int Block(void);
	void L_SHORT(void);
};

#endif

#ifdef __cplusplus
}
#endif
