#include "MountainousMission.h"

MountainousMission::MountainousMission() {}//default constructor


MountainousMission::MountainousMission(int a, int b, int c, int d, int e) :Mission(a, b, c, d, e), AutoPromote(0)//non default constructor
{}


MountainousMission::~MountainousMission(){}//destructor


void MountainousMission::DecrementAutoPromotion()
{
	AutoPromote--;
}

bool  MountainousMission::EndOfAutopromote()//check in the beginig of each day in mas station
{
	if (AutoPromote == 0)return true;
	return false;
}

int MountainousMission::GetAutoPromotion()
{
	return AutoPromote;
}