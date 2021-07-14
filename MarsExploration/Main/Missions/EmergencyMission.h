#pragma once
#include "Mission.h"
class EmergencyMission : public Mission
{
private:
	float priority; //Emergency Mission Priority
public:
	EmergencyMission();
	EmergencyMission(int a, int b, int c, int d, int e);

	void SetPriority(); //Find the priority based on 1-FD 2-MTLOC 3-DUR 4-SIG (Priority Equation)
	float GetPriority(); //Return Priority

	//Destuctor
	~EmergencyMission();
};
	
