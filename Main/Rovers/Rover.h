#pragma once
#include<iostream>
using namespace std;
#include"..\Missions\Mission.h"
class Rover
{
	int checkupDuration; //The number of days a rover spends in maintenance. 
	float speed; //The speed of each rover. 
	Mission* assignedMission; //A mission pointer to the mission assigned to the rover
	bool available; //Checks whether the rover is available or not (not available if in maintenance or on a mission)
	int missionsBeforeCheckup;//The number of missions a rover finishes before getting checked up (input from the txt file)
	int missionLeft;//The number of missions a rover has ACTUALLY finished (CHANGES throughout the simulation)
	bool maintenanceStatus;//If true, the rover is held in maintenance.
public:

	Rover(); //Default constructor.
	         //Sets every data member to 0, and pointers to NULL;

	Rover(int c, float s, Mission* m, bool av, int x); //User defined constructor
	 
	//SETTERS
	void setcheckupDuration(int c);
	
	void setRoverSpeed(float s);
	
	void setAssignedMission(Mission *);
	
	void setAvailability(bool av);
	
	void setMissionsBeforeCheckup(int x);//The input from the txt file
		
	void setMaintenanceStatus(bool m);

	//GETTERS
	int getcheckupDuration();
	
	float getRoverSpeed();
	
	Mission* getAssignedMission();
	
	bool inMaintenance();

	bool isAvailable();
	
	int getMissionsBeforeCheckUp();
	
	int getMissionsLeft();
    
	void DecrementMissionsLeft();//Decrements the ACTUAL number of missions left before checkup
	
	void operator =(const Rover& r);//Overloaded = operator

	virtual ~Rover();

};

