#include "Mission.h"


Mission::Mission() :WD(0), ED(0), CD(0),Eperiod(0),MissionStatus(Waiting){}//default constructor

Mission::Mission(int a, int b, int c, int d, int e) : ID(a), TLOC(b), MDUR(c), SIG(d), FD(e)//non default constructor
{
	WD = 0; ED = 0; CD = 0; Eperiod = 0; MissionStatus = Waiting;
}

Mission::~Mission(){}//destructor

int Mission::GetId()//get the id
{ return ID; }

int Mission::GetTargetLocation()//get the target location
{ return TLOC; }

int Mission::GetMissDuration()//get the mission duration
{ return MDUR; }

int Mission::GetSignificance()//get the significance of the mission
{ return SIG; }

int Mission::GetFormulationDay()//get the formulation day
{ return FD; }

int Mission::GetWaitingDays()//get the days the mission was in the waiting list
{ return WD; }

int Mission::GetExecutionDays()//get the num of days of execution
{ return ED; }

int Mission::GetCompletionDay()//get the day the mission is competed
{ return CD; }


int Mission::GetAvgWaitingdays(int num)//get the avreage of the waiting period
{
	return WD / num;
}
int Mission::GetAvgExecutiondays(int num)//get the avreage of the execution period
{
	return ED / num;
}
//setters
void Mission::SetId(int i)//set the id
{ ID = (i> 0) ? i : 0; }

void Mission::SetTargetLocation(int l)//set the target location
{ TLOC = (l > 0) ? l : 0; }

void Mission::SetMissionDuration(int i)//set the mission duration
{ MDUR = (i > 0) ? i : 0; }

void Mission::SetSignificance(int i)//set the significance
{ SIG = (i > 0) ? i : 0; }

void Mission::SetFormulationDay(int i)//set the formulation day
{ FD = (i > 0) ? i : 0; }

void Mission::IncrementWaitingDays()//inrement the number of waiting days of the mission
{ WD++; }

void Mission::DecrementInexecutionDays()
{Eperiod--;}

void Mission::SetExecutionDays(int speed)//set the num of execution days 
{
	int way = (TLOC / speed) / 25;
	ED = 2 * way + MDUR;
	Eperiod = ED;
}
void Mission::SetCompletionDay()//set the day the mission was completed
{
	CD = FD + WD + ED;
}

void Mission::PrintMission()//print format
{
	cout << CD << "\t" << ID << "\t" << FD << "\t" << WD << "\t" << ED << endl;
}

void Mission::UpdateToExecution()
{
	MissionStatus = Inexecution;
}
void Mission::UpdateToCompleted()
{
	MissionStatus = completed;
}