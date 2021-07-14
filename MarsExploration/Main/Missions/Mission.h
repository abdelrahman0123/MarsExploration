#pragma once
#include<iostream>
#include "../Rovers/Rover.h"
using namespace std;
enum status { Waiting, Inexecution, completed };
class Mission
{
private:
	int ID, TLOC, MDUR, SIG, FD, WD, ED, CD,Eperiod;
	// ID  Location, Duration,  Significance, Formulation day, Waiting days, Execution days, Completion days, Fixed Execution period
	status MissionStatus;
	Rover* associated{ nullptr };
	bool isAutoP{ false };
public:
	//Constuctor
	Mission();
	Mission(int a, int b, int c, int d, int e);
	
	//Getters
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
	int GetExecutionPeriod();

	bool AutoPromoted();
	Rover* getAssociated();

	//Setters
	void SetId(int i);
	void SetWaitingDays(int d);
	void SetTargetLocation(int l);
	void SetMissionDuration(int i);
	void SetSignificance(int i);
	void SetFormulationDay(int i);
    void SetExecutionDays(float speed);
	void SetCompletionDay();

	void IncrementWaitingDays();
	void DecrementInexecutionDays();
	
	//Update MissionStatus
	void UpdateToExecution();
	void UpdateToCompleted();

	void setAutoP(); //Set AtuoP to 1
	void setAssociated(Rover* rvr); //To set the associated rover when in execution

	//Print Format
	void PrintMission();

	//Destuctor
	virtual ~Mission();
};