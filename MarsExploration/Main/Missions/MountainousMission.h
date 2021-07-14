#pragma once
#include "Mission.h"
class MountainousMission : public Mission
{
private:
	int AutoPromote;
public:
	MountainousMission(); // Default Constructor
	MountainousMission(int a, int b, int c, int d, int e, int f); // Initializing Constructor
	//Auto-Promotion
	void DecrementAutoPromotion(); //Decrement the rest of auto-promotion days (on each day)
	//Get
	int GetAutoPromotion();
	//Set
	void SetAutoPromotion(int f);
	//Destructor
	~MountainousMission();
};

