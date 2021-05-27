#include "UI.h"
//
///*UI::UI()
//{
//	ipFile.open("Input.txt", ios::in);
//	emergencyRovers = new Queue<int>;
//	polarRovers = new Queue<int>;
//	mountRovers = new Queue<int>;
//}*/
///*UI::UI(int p, int em, int m) {
//	setPolarRoversNum(p);
//	setEmergencyRoversNum(em);
//	setMountainousRoversNum(m);
//	polarList = new int[polarRoversNum];
//	emergencyList = new int[emergencyRoversNum];
//	mountainousList = new int[mountainousRoversNum];
//}
//void UI::setEmergencyRoversNum(int s) {
//	emergencyRoversNum = s;
//}
//void UI::setPolarRoversNum(int s) {
//	polarRoversNum = s;
//}
//void UI::setMountainousRoversNum(int s) {
//	mountainousRoversNum = s;
//}
//int UI::getEmergencyRoversNum() {
//	return emergencyRoversNum;
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
//	cout << "\n-------------------------------------------------------------------------\n";
//}*/
//void UI:: addAvPolar(int n){
//	avPolar.enqueue(n);
//	avPolarRoversnum++;
//}
//
//void UI:: addAvEmergency(int n){
//	avEmergency.enqueue(n);
//	avEmergencyRoversnum++;
//}
//void UI:: addAvMountainous(int n){
//	avMountainous.enqueue(n);
//	avMountainounsRoversnum++;
//}
//void UI:: addCheckupPolar(int n){
//	checkupPolar.enqueue(n);
//	checkupPolarRoversnum++;
//
//}
//void UI:: addCheckupEmemergnecy(int n){
//	checkupEmemergnecy.enqueue(n);
//	checkupEmergencyRoversnum++;
//}
//void UI:: addCheckupMountainous(int n){
//checkupMountainous.enqueue(n);
//checkupMountainousRoversnum++;
//}
//void UI:: addWaitingMissionsPolar(int n){
//	waitingMissionsPolar.enqueue(n);
//	waitingPolarMissionsnum++;
//}
//void UI:: addWaitingMissionsEmergency(int n){
//waitingMissionsEmergency.enqueue(n);
//waitingEmergemcyMissionsnum++;
//}
//void UI:: addWaitingMissionsMountainous(int n){
//waitingMissionsMountainous.enqueue(n);
//waitingMountainousMissionsnum++;
//}
//void UI:: addInExecutionPolar(int n){
//inExecutionPolar.enqueue(n);
//inExecutionPolarMissionsnum++;
//}
//void UI:: addInExecutionEmergency(int n){
//inExecutionEmergency.enqueue(n);
//inExecutiomEmergencyMissionsnum++;
//}
//void UI:: addInExecutionMountainous(int n){
//inExecutionMountainous.enqueue(n);
//inExecutionMountainousMissionsnum++;
//
//}
//void UI:: addCompletedPolarMissions(int n){
//completedPolarMissions.enqueue(n);
//compPolarMissionsnum++;
//}
//void UI:: addCompletedEmergencyMisisons(int n){
//completedEmergencyMisisons.enqueue(n);
//compEmergencyMissionsnum++;
//}
//void UI:: addCompletedMountainousMissions(int n){
//completedMountainousMissions.enqueue(n);
//comMountainousMissionsnum++;
//}
//
//
//void UI::removeAvEmergency(  ) { int n;
//	avEmergency.dequeue(n);
//	avEmergencyRoversnum--;
//}
//void UI::removeAvMountainous(  ) { int n;
//	avMountainous.dequeue(n);
//	avMountainounsRoversnum--;
//}
//void UI::removeCheckupPolar(  ) { int n;
//	checkupPolar.dequeue(n);
//	checkupPolarRoversnum--;
//
//}
//void UI::removeCheckupEmemergnecy(  ) { int n;
//	checkupEmemergnecy.dequeue(n);
//	checkupEmergencyRoversnum--;
//}
//void UI::removeCheckupMountainous(  ) { int n;
//	checkupMountainous.dequeue(n);
//	checkupMountainousRoversnum--;
//}
//void UI::removeWaitingMissionsPolar(  ) { int n;
//	waitingMissionsPolar.dequeue(n);
//	waitingPolarMissionsnum--;
//}
//void UI::removeWaitingMissionsEmergency(  ) { int n;
//	waitingMissionsEmergency.dequeue(n);
//	waitingEmergemcyMissionsnum--;
//}
//void UI::removeWaitingMissionsMountainous(  ) { int n;
//	waitingMissionsMountainous.dequeue(n);
//	waitingMountainousMissionsnum--;
//}
//void UI::removeInExecutionPolar(  ) { int n;
//	inExecutionPolar.dequeue(n);
//	inExecutionPolarMissionsnum--;
//}
//void UI::removeInExecutionEmergency(  ) { int n;
//	inExecutionEmergency.dequeue(n);
//	inExecutiomEmergencyMissionsnum--;
//}
//void UI::removeInExecutionMountainous(  ) { int n;
//	inExecutionMountainous.dequeue(n);
//	inExecutionMountainousMissionsnum--;
//
//}
//void UI::removeCompletedPolarMissions(  ) { int n;
//	completedPolarMissions.dequeue(n);
//	compPolarMissionsnum--;
//}
//void UI::removeCompletedEmergencyMisisons(  ) { int n;
//	completedEmergencyMisisons.dequeue(n);
//	compEmergencyMissionsnum--;
//}
//void UI::removeCompletedMountainousMissions(  ) { int n;
//	completedMountainousMissions.dequeue(n);
//	comMountainousMissionsnum--;
//}