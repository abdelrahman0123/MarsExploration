#pragma once
#include "Mission.h"
class MountainousMission : public Mission
{
private:
	int AutoPromote;
	int count;
public:
	MountainousMission();
	MountainousMission(int a, int b, int c, int d, int e);
	void DecrementAutoPromotion();//decrement the rest of auto promotion days (each day)
	bool EndOfAutopromote();//check at the beging of each day
	~MountainousMission();
};

