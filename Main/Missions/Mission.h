#pragma once
#include<iostream>
#include "../Rovers/Rover.h"
using namespace std;
enum status { Waiting, Inexecution, completed };
class Mission
{
private:
	int ID, TLOC, MDUR, SIG, FD, WD, ED, CD,Eperiod;
	// id  location, duration,  significance, formulation day,waiting days,execution days,completion days
	Rover* associated{ nullptr };
	status MissionStatus;
	bool isAutoP{ false };
public:
	//constuctor
	Mission();
	Mission(int a, int b, int c, int d, int e);
	//destuctor
	virtual ~Mission();
	
	//getters
	int GetId();
	int GetTargetLocation();
	int GetMissDuration();
	int GetSignificance();
	int GetFormulationDay();
	int GetWaitingDays();
	int GetExecutionDays();
	int GetCompletionDay();
	int GetAvgWaitingdays(int num);
	int GetAvgExecutiondays(int num);

	bool AutoPromoted();
	Rover* getAssociated();

	//setters
	void SetId(int i);
	void SetTargetLocation(int l);
	void SetMissionDuration(int i);
	void SetSignificance(int i);
	void SetFormulationDay(int i);
	void IncrementWaitingDays();
	void DecrementInexecutionDays();
    void SetExecutionDays(int speed);
	void SetCompletionDay();
	void UpdateToExecution();
	void UpdateToCompleted();
	
	void setAutoP();
	void setAssociated(Rover* rvr);		//To set the associated rover when in execution

	//print format
	void PrintMission();
};