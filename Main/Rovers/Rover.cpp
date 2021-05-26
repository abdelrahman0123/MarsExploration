#pragma once
#include "Rover.h"
Rover::Rover() {
	
	checkupDuration = 0;
	speed = 0;
	assignedMission = nullptr;
	available =1;
	missionsBeforeCheckup = 0;
	missionLeft = 0;
	maintenanceStatus = 0;
	roverType = 'U';
}

Rover::Rover(int c, float s, Mission* m, bool av,int x,char t) {

	checkupDuration = c;
	speed = s;
	assignedMission = m;
	available = av;
	missionsBeforeCheckup = x;
	missionLeft = x;
	maintenanceStatus = 0;
	roverType = t;
}

void Rover::setcheckupDuration(int c) {
	checkupDuration = c;
}

void Rover::setRoverSpeed(float s) {
	speed = s;
}

void Rover::setAssignedMission(Mission* m) {
	assignedMission = m;
}

void Rover::setAvailability(bool av) {
	available = av;
}

void Rover::setMissionsBeforeCheckup(int x) {
	missionsBeforeCheckup = x;
}

void Rover::setMaintenanceStatus(bool m) {
	maintenanceStatus = m;
	setAvailability(!m);
}

void Rover::setRoverType(char t) {
	roverType = t;
}

void Rover::setLastCheckupDay(int day)
{
	LastCheckupDay = day + checkupDuration;
}

void Rover::setRoverID(int id)
{
	ID = id;
}

int Rover::getcheckupDuration() {
	return checkupDuration;
}

float Rover::getRoverSpeed() {
	return speed;
}

Mission* Rover::getAssignedMission() {
	return assignedMission;
}

bool Rover::inMaintenance() {
	return maintenanceStatus;
}

bool Rover::isAvailable() {
	return available;
}

int Rover::getMissionsBeforeCheckUp() {
	return missionLeft;
}

void Rover::DecrementMissionsLeft() {
	missionLeft--;
}

int Rover::getMissionsLeft() {
	return missionLeft;
}

char Rover::getRoverType() {
	return roverType;
}

int Rover::getLastCheckupDay()
{
	return LastCheckupDay;
}

int Rover::getRoverID()
{
	return ID;
}

void Rover::operator =(const Rover& r) {

	checkupDuration = r.checkupDuration;
	speed = r.speed;
}

Rover::~Rover() {

}
