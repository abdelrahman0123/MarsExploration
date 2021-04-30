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
	int getid(){ return ID; }
	int gettarloc(){ return TLOC; }
	int getmissdur(){ return MDUR; }
	int getsig(){ return SIG; }
	int getformday(){ return FD; }
	int getwaitdays(){ return WD; }
	int getexecdays(){ return ED; }
	int getcompleteday(){ return CD; }


	int getavgwaiting(int num)
	{
		return WD / num;
	}
	int getavgexec(int num)
	{
		return ED / num;
	}
	//setters
	void setid(int i){ ID = (i> 0) ? i : 0; }
	void settarloc(int l){ TLOC = (l > 0) ? l : 0; }
	void setmissdur(int i){ MDUR = (i > 0) ? i : 0; }
	void setsig(int i){ SIG = (i > 0) ? i : 0; }
	void setformday(int i){ FD = (i > 0) ? i : 0; }
	void incrwaitingdays(){ WD++; }//waiting each mission

	void setexecdays(int speed)
	{
		int way = (TLOC / speed) / 25;
		ED = 2 * way + MDUR;
	}
	void setcompleteday()
	{
		CD = FD + WD + ED;
	}
	//print format
	void printmission()
	{
		cout << CD << "\t" << ID << "\t" << FD << "\t" << WD << "\t" << ED << endl;
	}
};