#include "EmergencyMission.h"


EmergencyMission::EmergencyMission() {}//default constructor


EmergencyMission::EmergencyMission(int a, int b, int c, int d, int e)  :Mission(a,b,c,d,e), priority(0)//non default constructor
{}


EmergencyMission::~EmergencyMission(){}//destructor



void EmergencyMission::SetPriority()//find the priority based on 1-FD 2-MTLOC 3-DUR 4-SIG
{
	priority = 10 * GetSignificance() - 5 * GetFormulationDay() - GetMissDuration() + 0.01 * GetTargetLocation(); //maslan ya3ny
}

float EmergencyMission::GetPriority()
{

	return priority;
}
