#pragma once
#include<iostream>
using namespace std;

class Rover
{
	int checkupDuration; //The number of days a rover spends in maintenance. 
	float speed; //The speed of each rover. 
	int missionsBeforeCheckup; //The number of missions a rover finishes before getting checked up (input from the txt file)
	int missionLeft; //The number of missions a rover has ACTUALLY finished (CHANGES throughout the simulation)
	char roverType; //Rover Type (E/M/P)
	int LastCheckupDay; //The day where the rover finishes checkup
	int ID; //Rover ID
	int MissionExecutionDays; //Number of days in Execution
public:

	Rover(); //Default constructor.

	Rover(int id, int c, float s, int x,char t); //User defined constructor
	 
	//SETTERS
	void setcheckupDuration(int c);
	
	void setRoverSpeed(float s);
	
	void setMissionsBeforeCheckup(int x);//The input from the txt file
	
	void setRoverType(char t);

	void setLastCheckupDay(int day);

	void setRoverID(int id);

	void setExecutionDays(int d);

	void setMissionsLeft(int m);

	//GETTERS
	int getcheckupDuration();
	
	float getRoverSpeed();
	
	int getMissionsBeforeCheckUp();
	
	int getMissionsLeft();
    
	void DecrementMissionsLeft();//Decrements the ACTUAL number of missions left before checkup

	void DecrementExecutionDays();

	char getRoverType();
	
	int getLastCheckupDay();

	int getRoverID();

	int getExecutionDays();

	void operator =(const Rover& r);

	~Rover();

};

