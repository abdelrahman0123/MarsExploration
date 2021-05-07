#pragma once
#include<iostream>
using namespace std;
enum status { Waiting, Inexecution, completed };
class Mission
{
private:
	int ID, TLOC, MDUR, SIG, FD, WD, ED, CD;
	// id  location, duration,  significance, formulation day,waiting days,execution days,completion days
	status MissionStatus;
public:
	//constuctor
	Mission();
	Mission(int a, int b, int c, int d, int e);
	//destuctor
	~Mission();
	
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
	

	//print format
	void PrintMission();
};