#include "MountainousMission.h"

MountainousMission::MountainousMission(): AutoPromote(0) {}


MountainousMission::MountainousMission(int a, int b, int c, int d, int e,int f) : Mission(a, b, c, d, e), AutoPromote(f)
{

}

void MountainousMission::DecrementAutoPromotion()
{
	AutoPromote--;
}

int MountainousMission::GetAutoPromotion()
{
	return AutoPromote;
}

void MountainousMission::SetAutoPromotion(int f)
{
	AutoPromote = f;
}

MountainousMission::~MountainousMission() {}