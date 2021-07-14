#pragma once
#include "Rover.h"
Rover::Rover() {
	
	checkupDuration = 0;
	speed = 0;
	missionsBeforeCheckup = 0;
	missionLeft = 0;
	roverType = 'U';
	MissionExecutionDays = 0;
}

Rover::Rover(int id, int c, float s, int x,char t): MissionExecutionDays(0) {
	ID = id;
	checkupDuration = c;
	speed = s;
	missionsBeforeCheckup = x;
	missionLeft = x;
	roverType = t;
}

void Rover::setcheckupDuration(int c) {
	checkupDuration = c;
}

void Rover::setRoverSpeed(float s) {
	speed = s;
}

void Rover::setMissionsBeforeCheckup(int x) {
	missionsBeforeCheckup = x;
}

void Rover::setRoverType(char t) {
	roverType = t;
}

void Rover::setLastCheckupDay(int day)
{
	LastCheckupDay = day + checkupDuration; // Current Day + The number of days rover should be in checkup
}

void Rover::setRoverID(int id)
{
	ID = id;
}

void Rover::setExecutionDays(int d)
{
	MissionExecutionDays = d;
}

void Rover::setMissionsLeft(int m)
{
	missionLeft = m;
}

int Rover::getcheckupDuration() {
	return checkupDuration;
}

float Rover::getRoverSpeed() {
	return speed;
}

int Rover::getMissionsBeforeCheckUp() {
	return missionsBeforeCheckup;
}

void Rover::DecrementMissionsLeft() {
	missionLeft--;
}

void Rover::DecrementExecutionDays()
{
	MissionExecutionDays--;
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

int Rover::getExecutionDays()
{
	return MissionExecutionDays;
}

void Rover::operator =(const Rover& r) {

	checkupDuration = r.checkupDuration;
	speed = r.speed;
}

Rover::~Rover() {

}
