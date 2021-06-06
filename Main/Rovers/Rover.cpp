#pragma once
#include "Rover.h"
Rover::Rover() {
	
	checkupDuration = 0;
	speed = 0;
	available =1;
	missionsBeforeCheckup = 0;
	missionLeft = 0;
	maintenanceStatus = 0;
	roverType = 'U';
	MissionExecutionDays = 0;
	MissionCompletionDay = 0;
}

Rover::Rover(int id, int c, float s, bool av,int x,char t): MissionExecutionDays(0), MissionCompletionDay(0) {
	ID = id;
	checkupDuration = c;
	speed = s;
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

void Rover::setExecutionDays(int d)
{
	MissionExecutionDays = d;
}

void Rover::setCompletionDay(int d)
{
	MissionCompletionDay = d;
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

bool Rover::inMaintenance() {
	return maintenanceStatus;
}

bool Rover::isAvailable() {
	return available;
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

int Rover::getCompletionDay()
{
	return MissionCompletionDay;
}

void Rover::operator =(const Rover& r) {

	checkupDuration = r.checkupDuration;
	speed = r.speed;
}

Rover::~Rover() {

}
