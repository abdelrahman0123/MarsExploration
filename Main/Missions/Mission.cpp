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

int Mission::GetExecutionPeriod()
{
	return Eperiod;
}

bool Mission::AutoPromoted()
{
	return isAutoP;
}
Rover* Mission::getAssociated()
{
	return associated;
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
{ED--;}

void Mission::SetExecutionDays(float speed)//set the num of execution days 
{
	float x=TLOC/speed;
	float way =x / 25;
	way = ceil(2*way);
	ED =  way + MDUR;
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

void Mission::setAutoP()
{
	isAutoP = true;
}

void Mission::setAssociated(Rover* rvr)
{
	associated = rvr;
}