#include "EmergencyMission.h"


EmergencyMission::EmergencyMission() {}//default constructor


EmergencyMission::EmergencyMission(int a, int b, int c, int d, int e)  :Mission(a,b,c,d,e)//non default constructor
{}


EmergencyMission::~EmergencyMission(){}//destructor



void EmergencyMission::SetPriority()//find the priority based on 1-FD 2-MTLOC 3-DUR 4-SIG
{
	//priority = 10 * SIG + FD + DUR + 0.01*MTLOC;maslan ya3ny
}

float EmergencyMission::GetPriority()
{

	return priority;
}
