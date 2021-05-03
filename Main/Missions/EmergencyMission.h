#pragma once
#include "Mission.h"
class EmergencyMission : public Mission
{
private:
	float priority;//3ashan law 5alyna fy esma
public:
	EmergencyMission();
	EmergencyMission(int a, int b, int c, int d, int e);
	//destuctor
	~EmergencyMission();
	void SetPriority();//find the priority based on 1-FD 2-MTLOC 3-DUR 4-SIG
	float GetPriority();//return priority

};
	
