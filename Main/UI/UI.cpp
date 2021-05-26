#pragma once
#include "UI.h"
#include<iostream>
using namespace std;

//
//UI::UI()
//{
//	ipFile.open("Input.txt", ios::in);
//	emergencyRovers = new Queue<int>;
//	polarRovers = new Queue<int>;
//	mountRovers = new Queue<int>;
//}
//
//void UI::readRovers()
//{
//	if (ipFile.is_open())
//	{
//		int x, y, z, temp;
//		//Getting rovers no.
//		ipFile >> x >> y >> z;
//		//Getting max no. of rovers
//		(x > y) ? temp = x : temp = y;
//		(temp > z) ? temp = temp : temp = z;
//		//Getting rovers' speeds
//		for (int i = 0; i < temp; i++)
//			for (int i = 0; i < 3; i++)
//			{
//				ipFile >> x;
//				if (x != -1)
//				{
//					switch (i)
//					{
//					case 0:
//					{ 
//						mountRovers->enqueue(x);
//					     
//					}
//						break;
//					case 1:
//						polarRovers->enqueue(y);
//						break;
//					case 2:
//						emergencyRovers->enqueue(z);
//						break;
//					}
//				}
//			}
//	}
//}
//
//int UI::getAutoP()
//{
//	int autoP;
//	ipFile >> autoP;
//	return autoP;
//}
//
//int UI::getNumofEvents()
//{
//	int temp;
//	ipFile >> temp;
//	return temp;
//}
//
//Queue<int>* UI::getEvent()
//{
//	eventData = new Queue<int>;
//	int temp;
//	//Getting the event type
//	char eventType, Mtype;
//	ipFile >> eventType;
//	setEtype(eventType);
//
//	if (eventType == 'F')
//	{
//		ipFile >> Mtype;		//Getting type of the mission to be formulated
//		setMtype(Mtype);
//		for (int i = 0; i < 5; i++)
//		{
//			ipFile >> temp;
//			eventData->enqueue(temp);
//		}
//	}
//	else
//	{
//		for (int i = 0; i < 2; i++)
//		{
//			ipFile >> temp;
//			eventData->enqueue(temp);
//		}
//	}
//
//	return eventData;
//}
//
//UI::~UI()
//{
//
//}
//
//Queue<int>* UI::getEmRovers()
//{
//	return emergencyRovers;
//}
//
//Queue<int>* UI::getPolarRovers()
//{
//	return polarRovers;
//}
//
//Queue<int>* UI::getMountRovers()
//{
//	return mountRovers;
//}
//
//void UI::setEtype(char E)
//{
//	switch (E)
//	{
//	case 'F':
//		ET = Formulation;
//		break;
//	case 'X':
//		ET = Cancel;
//		break;
//	case 'P':
//		ET = Promote;
//		break;
//	}
//}
//
//EventType UI::getET()
//{
//	return ET;
//}
//
//void UI::setMtype(char M)
//{
//	switch (M)
//	{
//	case 'E':
//		MT = Emergency;
//		break;
//	case 'M':
//		MT = Mountainous;
//		break;
//	case 'P':
//		MT = Polar;
//		break;
//		
//	}
//}
//
//MissionType UI::getMT()
//{
//	return MT;
//}
//
///*
//Queue<int>* UI::getEventData()
//{
//	return eventData;
//}
//*/
UI::UI() {
	polarCheckupNum = 0;
	emergencyCheckupNum = 0;
	mountainousCheckupNum = 0;
}
UI::UI(int p, int em, int m) {
	setPolarRoversNum(p);
	setEmergencyRoversNum(em);
	setMountainousRoversNum(m);
	polarList = new int[polarRoversNum];
	emergencyList = new int[emergencyRoversNum];
	mountainousList = new int[mountainousRoversNum];
}
void UI::setEmergencyRoversNum(int s) {
	emergencyRoversNum = s;
}
void UI::setPolarRoversNum(int s) {
	polarRoversNum = s;
}
void UI::setMountainousRoversNum(int s) {
	mountainousRoversNum = s;
}
int UI::getEmergencyRoversNum() {
	return emergencyRoversNum;
}
int UI::getPolarRoversNum() {
	return polarRoversNum;
}
int UI::getMountainousRoversNum() {
	return mountainousRoversNum;
}

void UI::setPolarList(int* pList) {
	for (int i = 0; i < polarRoversNum; i++) {
		polarList[i] = pList[i];
	}
}
void UI::setEmergencyList(int* sList) {
	for (int i = 0; i < emergencyRoversNum; i++) {
		emergencyList[i] = sList[i];
	}
}
void UI::setMountainousList(int* mList) {
	for (int i = 0; i < mountainousRoversNum; i++) {
		mountainousList[i] = mList[i];
	}
}
void UI::printAvailabeRovers() {
	int totalNum = polarRoversNum + mountainousRoversNum + emergencyRoversNum;

	cout << totalNum << ' ' << "Available Rovers: ";
	if (!emergencyRoversNum) {
		cout << '[';
		for (int i = 0; i < emergencyRoversNum; i++) {
			cout << emergencyList[i];
			if (i != emergencyRoversNum - 1)
				cout << ', ';
		}
		cout << "] ";
	}
	if (!polarRoversNum) {

		cout << '(';
		for (int i = 0; i < polarRoversNum; i++) {
			cout << polarList[i];
			if (i != polarRoversNum - 1)
				cout << ', ';
		}
		cout << ") ";
	}
	if (!mountainousRoversNum) {
		cout << '{';
		for (int i = 0; i < mountainousRoversNum; i++) {
			cout << mountainousList[i];
			if (i != mountainousRoversNum - 1)
				cout << ', ';
		}
		cout << "} ";
	}
	cout << "\n-------------------------------------------------------------------------\n";
}

void UI::setPolarCheckupList(int* pList) {
	for (int i = 0; i < polarCheckupNum; i++) {
		polarCheckup[i] = pList[i];
	}
}
void UI::setEmergencyCheckupList(int* emList) {
	for (int i = 0; i < emergencyCheckupNum; i++) {
		emergencyCheckup[i] = emList[i];
	}
}
void UI::setMountainousCheckupList(int* mList) {
	for (int i = 0; i < mountainousCheckupNum; i++) {
		mountainousCheckup[i] = mList[i];
	}
}
void UI::printInCheckupRovers() {
	int totalNum = polarCheckupNum + emergencyCheckupNum + mountainousCheckupNum;
	cout << totalNum << ' ' << "In-Checkup Rovers: ";
	if (!emergencyCheckupNum) {
		cout << '[';
		for (int i = 0; i < emergencyCheckupNum; i++) {
			cout << emergencyCheckup[i];
			if (i != emergencyCheckupNum - 1)
				cout << ', ';
		}
		cout << "] ";
	}
	if (!polarCheckupNum) {
		cout << '(';
		for (int i = 0; i < polarCheckupNum; i++) {
			cout << polarCheckup[i];
			if (i != polarCheckupNum - 1)
				cout << ', ';
		}
		cout << ") ";
	}
	if (!mountainousCheckupNum) {
		cout << '{';
		for (int i = 0; i < mountainousCheckupNum; i++) {
			cout << mountainousCheckup[i];
			if (i != mountainousCheckupNum - 1)
				cout << ', ';
		}
		cout << "} ";
	}

	cout << "\n-------------------------------------------------------------------------\n";
}