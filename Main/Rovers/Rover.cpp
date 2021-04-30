#pragma once
#include "Rover.h"
Rover::Rover() {
	roverType = 'U';
	checkUpDuration = 0;
	speed = 0;
	assignedMission = nullptr;
	status = "Avaliable";
}
Rover::Rover(char r, int c, int s, Mission* m, string st) {
	roverType = r;
	checkUpDuration = c;
	speed = s;
	assignedMission = m;
	status = st;
}

void Rover::setRoverType(char t) {
	roverType = t;
}

void Rover::setCheckUpDuration(int c) {
	checkUpDuration = c;
}

void Rover::setRoverSpeed(int s) {
	speed = s;
}

void Rover::setAssignedMission(Mission* m) {
	assignedMission = m;
}

void Rover::setStatus(string st) {
	status = st;
}

char Rover::getRoverType() {
	return roverType;
}

int Rover::getCheckUpDuration() {
	return checkUpDuration;
}

int Rover::getRoverSpeed() {
	return speed;
}

void Rover::operator =(const Rover& r) {
	roverType = r.roverType;
	checkUpDuration = r.checkUpDuration;
	speed = r.speed;
}

Mission* Rover::getAssignedMission() {
	return assignedMission;
}

bool Rover::getStatus() {
	if (status == "Avaliable")
		return true;
	else 
		return false;
}
Rover::~Rover() {

}
