#include "MarsStation.h"

MarsStation::MarsStation()
{
	
}

void MarsStation::Simulate()
{
	char x = UserInterface->selectMode();
	switch (x)
	{
	case('i'): {
		simulateInteractive();
		break; }
	case('s'): {
		simulateStepByStep();
		break; }
	case('t'): {
		simulateSilent();
		break;
	}
	}
	/*while (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions())
	{
		UpdateMissions();
		//UserInterface->InputMode();
		ExecuteEvent();
		MoveRoverFromBusyToAvailable();
		MoveRoverFromCheckupToAvailable();
		AssignEmergencyMission();
		AssignPolarMission();
		AssignMountainousMission();
		//UserInterface->print();
		IncrementCurrentDay();
	}*/
}

void MarsStation::ReadInput()
{
	// Opening input file
	ipFile.open("Input.txt", ios::in);

	// Reading Rovers Data
	readRovers();

	// Setting the auto promotion limit
	ipFile >> AutoPromotionLimit;

	// Reading the number of events
	int n;
	ipFile >> n;

	// Reading the events Data
	for (int i = 0; i < n; i++)
	{
		createEventsList();
	}
}

void MarsStation::readRovers()
{
	if (ipFile.is_open())
	{
		int x, y, z, temp;

		//Getting rovers no.
		ipFile >> x >> y >> z;

		mountRCount = x;		polarRCount = y;		emrgncyRCount = z;
		roversCount = mountRCount + polarRCount + emrgncyRCount;

		//Getting max no. of rovers
		(x > y) ? temp = x : temp = y;
		(temp > z) ? temp = temp : temp = z;

		//Getting rovers' speeds and creating them
		Rover* tempRover;

		for (int i = 0; i < temp; i++)
			for (int i = 0; i < 3; i++)
			{
				ipFile >> x;
				tempRover = new Rover(); // Non-default
				tempRover->setRoverSpeed(x);

				if (x != -1)
				{
					switch (i)
					{
					case 0:
						AddToMountainousRovers(tempRover, x);
						break;
					case 1:
						AddToPolarRovers(tempRover, x);
						break;
					case 2:
						AddToEmergencyRovers(tempRover, x);
						break;
					}
				}
			}
	}
}

void MarsStation::createEventsList()
{
	//Getting the event type
	char eventType, Mtype;
	ipFile >> eventType;

	//Event day and mission ID are necessary no matter what type of event
	//ipFile >> ED;
	//ipFile >> ID;

	if (eventType == 'F')		//Formulation Event case
	{
		ipFile >> Mtype;		//Getting type of the mission to be formulated
		setMtype(Mtype);
		ipFile >> ED;
		ipFile >> ID;
		ipFile >> TLOC;
		ipFile >> MissionDur;
		ipFile >> SIG;
		Event* evptr = new FormulationEvent(this, getMtype(), ED, ID, TLOC, MissionDur, SIG);
		AddToEvents(evptr);
	}
	else
	{
		if (eventType == 'X')	//Cancelation Event case
		{
			ipFile >> ED;
			ipFile >> ID;
			Event* evptr = new CancelEvent(this, ED, ID);
			AddToEvents(evptr);
		}
		else					//Promotion Event case
		{
			ipFile >> ED;
			ipFile >> ID;
			Event* evptr = new PromoteEvent(this, ED, ID);
			AddToEvents(evptr);
		}
	}
}

void MarsStation::setMtype(char M)
{
	switch (M)
	{
	case 'E':
		Mtype = Emergency;
		break;
	case 'M':
		Mtype = Mountainous;
		break;
	case 'P':
		Mtype = Polar;
		break;
	}
}

MissionType MarsStation::getMtype()
{
	return Mtype;
}

void MarsStation::IncrementCurrentDay() {
	currentDay++;
}

int MarsStation::getCurrentDay() {
	return currentDay;
}
void MarsStation::UpdateMissions()
{
	//emergency
	EmergencyMission* EM;
	PriQ<EmergencyMission*>EMQtemp;
	while (!EmergencyMissions.isEmpty())
	{
		EmergencyMissions.dequeue(EM);
		EM->IncrementWaitingDays();
		EM->SetCompletionDay();
		EMQtemp.enqueue(EM,EM->GetPriority());
	}
	//EmergencyMissions = EMQtemp;
	ExchangeEMissions(EMQtemp, EmergencyMissions);
	//polar
	PolarMission* PM;
	Queue<PolarMission*>PMQtemp;
	while (!PolarMissions.isEmpty())
	{
		PolarMissions.dequeue(PM);
		PM->IncrementWaitingDays();
		PM->SetCompletionDay();
		PMQtemp.enqueue(PM);
	}
	//PolarMissions = PMQtemp;
	ExchangeQueues(PMQtemp, PolarMissions);
	//Mountainous
	MountainousMission* MM;
	int i = 1;
	while (!MountainousMissions.isEmpty())
	{
		MM = MountainousMissions.getEntry(i);
		MM->IncrementWaitingDays();
		MM->SetCompletionDay();
		MM->DecrementAutoPromotion();
		if (MM->GetAutoPromotion() == 0)
		{
			int a, b, c, d, e;
			a = MM->GetId();
			b = MM->GetTargetLocation();
			c = MM->GetMissDuration();
			d = MM->GetSignificance();
			e = MM->GetFormulationDay();
			EmergencyMission* EM = new EmergencyMission(a, b, c, d, e);
			AddToEmergencyMissions(EM, EM->GetPriority());
			delete MM;
		}
		i++;
	}
	//inexecution
	Mission*mission;
	PriQ<Mission*>InExecutionTemp;
	while (!InExecutionMissions.isEmpty())
	{
		InExecutionMissions.dequeue(mission);
		mission->DecrementInexecutionDays();
		InExecutionTemp.enqueue(mission,(-1) * mission->GetExecutionDays());
	}
	//InExecutionMissions = InExecutionTemp;
	ExchangeExecMissions(InExecutionTemp, InExecutionMissions);
	//assign to rover
	HandleMission();

}
void MarsStation::HandleMission()
{
	Mission*Temp;
	//CALL ASSIGN TO ROVER(la hena la fo2)
	
	while (!InExecutionMissions.isEmpty())
	{
		InExecutionMissions.peek(Temp);
		if (Temp->GetExecutionDays() == 0)
		{
			Temp=RemoveFromInExecutionMissions();
			
			Temp->UpdateToCompleted();
			AddToCompletedMissions(Temp);
			
			/////EL ROVER BETA3 SARA $$$$$$$$$$$$$
		}
		else break;//$$$
	}

}
void MarsStation::AddToEmergencyMissions(EmergencyMission* EM, int pri)
{
	EmergencyMissions.enqueue(EM, pri);
	emrgncyMCount++;
}

void MarsStation::AddToMountainousMissions(MountainousMission* MM)
{
	MountainousMissions.insert(++mountMCount, MM);
}

void MarsStation::AddToPolarMissions(PolarMission* PM)
{
	PolarMissions.enqueue(PM);
	polarMCount++;
}

void MarsStation::AddToEmergencyRovers(Rover* ER, float speed)
{
	EmergencyRovers.enqueue(ER, speed);
	ER->setAvailability(1);
}

void MarsStation::AddToMountainousRovers(Rover* MR, float speed)
{
	MountainousRovers.enqueue(MR, speed);
	MR->setAvailability(1);
}

void MarsStation::AddToPolarRovers(Rover* PR, float speed)
{
	PolarRovers.enqueue(PR, speed);
	PR->setAvailability(1);
}

void MarsStation::AddToInExecutionMissions(Mission* M, int n)
{
	InExecutionMissions.enqueue(M, n);

}

void MarsStation::AddToInExecutionRovers(Rover* R, int n)
{
	InExecutionRovers.enqueue(R, n);
	R->setAvailability(0);
}

void MarsStation::AddToRoversCheckup(Rover* R, int n)
{
	RoversCheckup.enqueue(R, n);
	R->setAvailability(0);
	R->setMaintenanceStatus(1);
	checkUpCount++;
}

void MarsStation::AddToCompletedMissions(Mission* M)
{
	CompletedMissions.enqueue(M);
	completedMcount++;
}

void MarsStation::AddToEvents(Event* newEvent)
{
	Events.enqueue(newEvent);
}

Event* MarsStation::RemoveFromEvents()
{
	Event* E = NULL;
	Events.dequeue(E);
	return E;
}

EmergencyMission* MarsStation::RemoveFromEmergencyMissions()
{
	EmergencyMission* EM = NULL;
	EmergencyMissions.dequeue(EM);
	emrgncyMCount--;
	return EM;
}

MountainousMission* MarsStation::RemoveFromMountainousMissions(int i)
{
	MountainousMission* MM = MountainousMissions.getEntry(i);
	MountainousMissions.remove(i);
	mountMCount--;
	return MM;
}

PolarMission* MarsStation::RemoveFromPolarMissions()
{
	PolarMission* PM = NULL;
	PolarMissions.dequeue(PM);
	polarMCount--;
	return PM;
}

Rover* MarsStation::RemoveFromEmergencyRovers()
{
	Rover* ER = NULL;
	EmergencyRovers.dequeue(ER);
	ER->setAvailability(0);
	roversCount--;
	return ER;
}

Rover* MarsStation::RemoveFromMountainousRovers()
{
	Rover* MR = NULL;
	roversCount--;
	MountainousRovers.dequeue(MR);
	MR->setAvailability(0);
	return MR;
}

Rover* MarsStation::RemoveFromPolarRovers()
{
	Rover* PR = NULL;
	roversCount--;
	PolarRovers.dequeue(PR);
	PR->setAvailability(0);
	return PR;
}

Mission* MarsStation::RemoveFromInExecutionMissions()
{
	Mission* M = NULL;
	InExecutionMissions.dequeue(M);
	return M;
}

Rover* MarsStation::RemoveFromInExecutionRovers()
{
	Rover* R = NULL;
	InExecutionRovers.dequeue(R);
	return R;
}

Rover* MarsStation::RemoveFromRoversCheckup()
{
	checkUpCount--;
	Rover* R = NULL;
	RoversCheckup.dequeue(R);
	R->setAvailability(1);
	R->setMaintenanceStatus(0);
	return R;
}

Mission* MarsStation::RemoveFromCompletedMissions()
{
	Mission* M = NULL;
	completedMcount--;
	CompletedMissions.dequeue(M);
	return M;
}

bool MarsStation::CheckWaitingMissions()
{
	if (EmergencyMissions.isEmpty() && MountainousMissions.isEmpty() && PolarMissions.isEmpty())
		return true;
	return false;
}

void MarsStation::ExecuteEvent()
{
	Event* E;
	while (Events.peek(E))
	{
		if (E->getEventDay() == currentDay)
		{
			E->Execute();
			RemoveFromEvents();
		}
		else
			break;
	}
}

void MarsStation::AssignEmergencyMission()
{
	EmergencyMission* EM = NULL;
	while (EmergencyMissions.peek(EM))
	{
		Rover* R = NULL;
		if (!CheckAvailableRover(R, 'E'))
			if (!CheckAvailableRover(R, 'M'))
				if (!CheckAvailableRover(R, 'P'))
					break;
		EM->SetExecutionDays(R->getRoverSpeed()); // new
		EM->SetCompletionDay();
		RemoveFromEmergencyMissions();
		AddToInExecutionMissions(EM, (-1) * EM->GetExecutionDays());
		EM->UpdateToExecution();
		AssignRoverToMission(R, EM);
		MoveRoverFromAvailabeToBusy(R);
	}
}

void MarsStation::AssignMountainousMission()
{
	MountainousMission* MM = NULL;
	while (!MountainousMissions.isEmpty())
	{
		MM = MountainousMissions.getEntry(1);
		Rover* R = NULL;
		if (!CheckAvailableRover(R, 'M'))
			if (!CheckAvailableRover(R, 'E'))
				break;
		MM->SetExecutionDays(R->getRoverSpeed()); // new
		MM->SetCompletionDay();
		RemoveFromMountainousMissions();
		AddToInExecutionMissions(MM, (-1) * MM->GetExecutionDays());
		MM->UpdateToExecution();
		AssignRoverToMission(R, MM);
		MoveRoverFromAvailabeToBusy(R);
	}
}

void MarsStation::AssignPolarMission()
{
	PolarMission* PM = NULL;
	while (PolarMissions.peek(PM))
	{
		Rover* R = NULL;
		if (!CheckAvailableRover(R, 'P'))
			break;
		PM->SetExecutionDays(R->getRoverSpeed()); // new
		PM->SetCompletionDay();
		RemoveFromPolarMissions();
		AddToInExecutionMissions(PM, (-1) * PM->GetExecutionDays());
		PM->UpdateToExecution();
		AssignRoverToMission(R, PM);
		MoveRoverFromAvailabeToBusy(R);
	}
}

bool MarsStation::CheckAvailableRover(Rover* &R, char Type)
{
	if (Type == 'E')
	{
		EmergencyRovers.peek(R);
		if (R)
			return true;
		return false;
	}
	else if (Type == 'M')
	{
		MountainousRovers.peek(R);
		if (R)
			return true;
		return false;
	}
	else
	{
		PolarRovers.peek(R);
		if (R)
			return true;
		return false;
	}
	return false;
}

void MarsStation::AssignRoverToMission(Rover* R, Mission* M)
{
	R->setExecutionDays(M->GetExecutionDays());
	R->setCompletionDay(M->GetCompletionDay());
	R->DecrementMissionsLeft();
	M->setAssociated(R);
}

int MarsStation::getAutoP()
{
	return AutoPromotionLimit;
}

void MarsStation::CancelMission(int ID)
{
	int i = 1;
	while (!MountainousMissions.isEmpty())
	{
		int MissionID = (MountainousMissions.getEntry(i))->GetId();
		if (MissionID == ID)
		{
			RemoveFromMountainousMissions(i);
			break;
		}
		i++;
	}
}

void MarsStation::PromoteMission(int ID)
{
	int i = 1;
	while (!MountainousMissions.isEmpty())
	{
		MountainousMission* M_Mission = MountainousMissions.getEntry(i);
		int MissionID = M_Mission->GetId();
		if (MissionID == ID)
		{
			int TLOC = M_Mission->GetTargetLocation();
			int MDUR = M_Mission->GetMissDuration();
			int SIG = M_Mission->GetSignificance();
			int FD = M_Mission->GetFormulationDay();
			RemoveFromMountainousMissions(i);
			EmergencyMission* EM = new EmergencyMission(MissionID, TLOC, MDUR, SIG, FD);
			AddToEmergencyMissions(EM, EM->GetPriority());
			break;
		}
		i++;
	}
}

void MarsStation::MoveRoverFromAvailabeToBusy(Rover*r) {

	char type=r->getRoverType();

	switch (type) {
	case('M'): {
		
		r = RemoveFromMountainousRovers();
		AddToInExecutionRovers(r, r->getExecutionDays());

	}
			 break;
	case('E'): {
		r = RemoveFromEmergencyRovers();
		AddToInExecutionRovers(r, r->getExecutionDays());

	}
			 break;
	case('P'): {
		r = RemoveFromPolarRovers();
		AddToInExecutionRovers(r, r->getExecutionDays());
	}
			 break;
	}
}

void MarsStation::MoveRoverFromBusyToAvailable() {
	while (!InExecutionRovers.isEmpty()) {
		Rover* r=nullptr;
		InExecutionRovers.peek(r);
		if (r->getCompletionDay() == currentDay) {
			char type = r->getRoverType();

			switch (type) {
			case('M'): {
				
				r=RemoveFromInExecutionRovers();

				if (r->getMissionsLeft() == 0)
				{ 
					MoveRoverFromBusyToCheckup(r);
				}
				else {
					AddToMountainousRovers(r,r->getRoverSpeed());
				}
			}
					 break;
			case('E'): {

				r = RemoveFromInExecutionRovers();

				if (r->getMissionsLeft() == 0)
				{ 
					MoveRoverFromBusyToCheckup(r);
				}
				else {
					AddToEmergencyRovers(r, r->getRoverSpeed());
				}

			}
					 break;
			case('P'): {

				r = RemoveFromInExecutionRovers();

				if (r->getMissionsLeft() == 0)
				{
					MoveRoverFromBusyToCheckup(r);
					break;
				}
				else {
					AddToPolarRovers(r, r->getRoverSpeed());
				}

			}
					 break;

			}
		} //#### ELSE, A FUNCTION TO DECREMENT ALL DAYS LEFT SHOULD BE ADDED ####
	}
}

void MarsStation::MoveRoverFromBusyToCheckup(Rover* r) {
	r->setMissionsLeft(r->getMissionsBeforeCheckUp());
	r->setLastCheckupDay(currentDay + r->getcheckupDuration());
	AddToRoversCheckup(r, r->getLastCheckupDay());
}

void MarsStation::MoveRoverFromCheckupToAvailable() {
	
	while(!RoversCheckup.isEmpty()){
		Rover* r = nullptr;
		RoversCheckup.peek(r);
		if (r->getLastCheckupDay() == currentDay)//if r->getLastCheckUpDay==currentday
		{
			r=RemoveFromRoversCheckup();
			char type = r->getRoverType();
			switch (type)
			{
			case('M'):
				AddToMountainousRovers(r, r->getRoverSpeed());
				break;
			case('E'):
				AddToEmergencyRovers(r, r->getRoverSpeed());
				break;
			case('P'):
				AddToPolarRovers(r, r->getRoverSpeed());

			}
		}

	}

}

void MarsStation::PrintOutput()
{
	//Opening the output file
	opFile.open("Output.txt", ios::out);

	//Setting the file
	opFile << "CD    ID    FD    WD    ED\n";

	//Collecting statistics and printing the data
	getStatistics();

}

void MarsStation::getStatistics()
{
	int missionCount{ 0 }, mountCount{ 0 }, polarCount{ 0 }, emergencyCount{ 0 }, autoPcount{ 0 };
	float waitDays{ 0 }, exeDays{ 0 }, avgWaiting, avgExecution;
	char ch;

	Mission* Finished;
	while (!CompletedMissions.isEmpty())
	{
		CompletedMissions.dequeue(Finished);
		missionCount++;					//Counting the total number of missions
		ch = getMissionType(Finished);
		switch (ch)						//Counting the number of missions of each type
		{
		case 'M':
			mountCount++;
			break;
		case 'P':
			polarCount++;
			break;
		case 'E':
			emergencyCount++;
			if (Finished->AutoPromoted())
				autoPcount++;
			break;
		}
		waitDays = waitDays + Finished->GetWaitingDays();		//Counting the total waiting days
		exeDays = exeDays + Finished->GetExecutionPeriod();		//Counting the total execution days

		//Printing the mission details
		opFile << Finished->GetCompletionDay() << "    ";
		opFile << Finished->GetId() << "    ";
		opFile << Finished->GetFormulationDay() << "    ";
		opFile << Finished->GetWaitingDays() << "    ";
		opFile << Finished->GetExecutionPeriod() << "\n";
	}

	avgWaiting = waitDays / missionCount;
	avgExecution = exeDays / missionCount;

	//Printing the statistics results
	opFile << "Missions: " << missionCount << " [M: " << mountCount << ", P: " << polarCount << ", E: " << emergencyCount << "]\n";
	printRoversData();
	opFile << "Avg Wait = " << avgWaiting << ", Avg Exec = " << avgExecution << "\n";
	opFile << "Auto-promoted: " << (float)autoPcount * 100 / (float)missionCount << '%';
}

void MarsStation::printRoversData()
{
	/*
	int roversCount{ 0 }, mountCount{ 0 }, polarCount{ 0 }, emrgncyCount{ 0 };
	Rover* temp;

	///////Checking for available rovers/////////
	while (!EmergencyRovers.isEmpty())
	{
		EmergencyRovers.dequeue(temp);
		roversCount++;
		emrgncyCount++;
	}

	while (!PolarRovers.isEmpty())
	{
		PolarRovers.dequeue(temp);
		roversCount++;
		polarCount++;
	}

	while (!MountainousRovers.isEmpty())
	{
		MountainousRovers.dequeue(temp);
		roversCount++;
		mountCount++;
	}

	///////Checking for rovers in checkup
	char r;
	while (!RoversCheckup.isEmpty())
	{
		RoversCheckup.dequeue(temp);
		roversCount++;
		r = temp->getRoverType();

		switch (r)
		{
		case 'E':
			emrgncyCount++;
			break;
		case 'P':
			polarCount++;
			break;
		case 'M':
			mountCount++;
			break;
		}
	}
	*/
	//Printing rovers data
	opFile << "Rovers: " << roversCount << " [M: " << mountRCount << ", P: " << polarRCount << ", E: " << emrgncyRCount << "]\n";
}

char MarsStation::getMissionType(Mission* base)
{
	char c;
	MountainousMission* mount{ nullptr };
	PolarMission* polar{ nullptr };
	EmergencyMission* emrgncy{ nullptr };

	mount = dynamic_cast<MountainousMission*>(base);
	polar = dynamic_cast<PolarMission*>(base);
	emrgncy = dynamic_cast<EmergencyMission*>(base);

	if (mount) c = 'M';
	else if (polar) c = 'P';
	else if (emrgncy) c = 'E';

	return c;
}

void MarsStation::ExchangeEMissions(PriQ<EmergencyMission*>& Q1, PriQ<EmergencyMission*>& Q2)
{
	EmergencyMission* temp;
	while (!Q1.isEmpty())
	{
		Q1.dequeue(temp);
		Q2.enqueue(temp, temp->GetPriority());
	}
}

void MarsStation::ExchangeExecMissions(PriQ<Mission*>& Q1, PriQ<Mission*>& Q2)
{
	Mission* temp;
	while (!Q1.isEmpty())
	{
		Q1.dequeue(temp);
		Q2.enqueue(temp, (-1) * temp->GetExecutionDays());
	}
}

void MarsStation::simulateInteractive() {
	if (currentDay == 1) {
		if (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions())
		{
			simulateG(0);
		}


	}
	while (UserInterface->interactiveMode()) {
		if (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions())
		{
			simulateG(0);
		}
		else {
			break;
		}
	}

}

void MarsStation::simulateStepByStep()
{
	while (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions())
	{
		simulateG(1);
	}

}

void MarsStation::simulateSilent() {
	while (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions())
	{
		simulateG(2);
	}
	UserInterface->silentMode();
}

void MarsStation::simulateG(int x) {

	UpdateMissions();
	///////////////
	ExecuteEvent();
	MoveRoverFromBusyToAvailable();
	MoveRoverFromCheckupToAvailable();
	AssignEmergencyMission();
	AssignPolarMission();
	AssignMountainousMission();
	switch (x)
	{
	case(0): {
		//UserInterface->printInteractive&Step(all parameters);
		break;

	}
	case(1): {
		//UserInterface->printInteractive&Step(all parameters);
		sleep_for(seconds(1));
		break;
	}
	}
	//UserInterface->printInteractive&Step(all parameters);
	IncrementCurrentDay();
}

MarsStation::~MarsStation()
{
	Events.~Queue();
	CompletedMissions.~Queue();
	InExecutionMissions.~PriQ();
	EmergencyMissions.~PriQ();
	MountainousMissions.~LinkedList();
	PolarMissions.~Queue();
	InExecutionRovers.~PriQ();
	EmergencyRovers.~PriQ();
	MountainousRovers.~PriQ();
	PolarRovers.~PriQ();
	delete UserInterface;
}


