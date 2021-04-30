#pragma once
#include<iostream>
using namespace std;
class Mission
{
private:
	int ID, TLOC, MDUR, SIG, FD, WD, ED, CD;
	// id  location, duration,  significance, formulation day,waiting days,execution days,completion days
public:
	Mission() :WD(0), ED(0), CD(0){}
	Mission(int a, int b, int c, int d, int e) :ID(a), TLOC(b), MDUR(c), SIG(d), FD(e)
	{
		WD = 0; ED = 0; CD = 0;
	}
	//getters
	int GetId(){ return ID; }
	int GetTarLoc(){ return TLOC; }
	int GetMissDur(){ return MDUR; }
	int GetSig(){ return SIG; }
	int GetFormDay(){ return FD; }
	int GetWaitDays(){ return WD; }
	int GetExecDays(){ return ED; }
	int GetCompleteDay(){ return CD; }


	int GetAvgWaiting(int num)
	{
		return WD / num;
	}
	int GetAvgExec(int num)
	{
		return ED / num;
	}
	//setters
	void SetId(int i){ ID = (i> 0) ? i : 0; }
	void SetTarLoc(int l){ TLOC = (l > 0) ? l : 0; }
	void SetMissDur(int i){ MDUR = (i > 0) ? i : 0; }
	void SetSig(int i){ SIG = (i > 0) ? i : 0; }
	void SetFormDay(int i){ FD = (i > 0) ? i : 0; }
	void IncrWaitingDays(){ WD++; }//waiting each mission

	void SetExecDays(int speed)
	{
		int way = (TLOC / speed) / 25;
		ED = 2 * way + MDUR;
	}
	void SetCompleteDay()
	{
		CD = FD + WD + ED;
	}
	//print format
	void PrintMission()
	{
		cout << CD << "\t" << ID << "\t" << FD << "\t" << WD << "\t" << ED << endl;
	}
};