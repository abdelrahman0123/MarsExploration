#include "MarsStation.h"

MarsStation::MarsStation()
{
	
}

void MarsStation::Simulate()
{
	char x = UserInterface->selectMode();
	switch (x)
	{
	case('i'):
		simulateInteractive();
		break;
	case('s'):
		simulateStepByStep();
		break;
	case('t'):
		simulateSilent();
		break;
	}
}

void MarsStation::simulateInteractive()
{
	while (UserInterface->interactiveMode()) {
		if (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions() || !RoversCheckup.isEmpty())
		{
			simulateG(0);
		}
		else
			break;
	}
	UserInterface->printEnd();
}

void MarsStation::simulateStepByStep()
{
	while (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions() || !RoversCheckup.isEmpty())
	{
		simulateG(1);
	}
	UserInterface->printEnd();
}

void MarsStation::simulateSilent()
{
	while (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions() || !RoversCheckup.isEmpty())
	{
		simulateG(2);
	}
	UserInterface->silentMode();
}

void MarsStation::simulateG(int x)
{

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
	case(0):
		print();
		break;
	case(1): 
		print();
		sleep_for(seconds(2));
		break;
	default:
		break;
	}
	IncrementCurrentDay();
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
		int x, y, z;
		int max = 0;
		int beforeCheck, CM, CP, CE;

		//Getting rovers no.
		ipFile >> x >> y >> z;

		mountRCount = x;		polarRCount = y;		emrgncyRCount = z;
		inputFileERcount = z; inputFileMRcount = x;
		inputFilePRcount = y;
		//roversCount = mountRCount + polarRCount + emrgncyRCount;
		inputFileRcount = roversCount;
		maxRoversCount = roversCount;
		//Getting max no. of rovers
		max = getmax(x, y, z);


		//Getting rovers speeds
		int* Mspeeds = new int[max];  int* Pspeeds = new int[max];  int* Espeeds = new int[max];


		for (int j = 0; j < max; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				ipFile >> x;	//reads a speed
				switch (i)
				{
				case 0:
					Mspeeds[j] = x;
					break;
				case 1:
					Pspeeds[j] = x;
					break;
				case 2:
					Espeeds[j] = x;
					break;
				}
			}
		}

		ipFile >> beforeCheck;		//Number of missions completed before performing a checkup
		ipFile >> CM;				//Checkup Duration for mount Rovers
		ipFile >> CP;				//Checkup Duration for polar Rovers
		ipFile >> CE;				//Checkup Duration for emergency Rovers

		///Creating Rovers///
		Rover* tempRover;

		//Creating mountainous rovers
		z = 0;

		int ID = 1;
		while (Mspeeds[z] != -1 && z != max)
		{
			tempRover = new Rover(ID, CM, Mspeeds[z], true, beforeCheck, 'M');
			AddToMountainousRovers(tempRover, Mspeeds[z]);
			z++;
			ID++;
		}

		//Creating Polar rovers
		z = 0;
		while (Pspeeds[z] != -1 && z != max)
		{
			tempRover = new Rover(ID, CP, Pspeeds[z], true, beforeCheck, 'P');
			AddToPolarRovers(tempRover, (float)Pspeeds[z]);
			z++;
			ID++;
		}

		//Creating Emergency rovers
		z = 0;
		while (Espeeds[z] != -1 && z != max)
		{
			tempRover = new Rover(ID, CE, Espeeds[z], true, beforeCheck, 'E');
			AddToEmergencyRovers(tempRover, Espeeds[z]);
			z++;
			ID++;
		}

	}
}

int MarsStation::getmax(int x, int y, int z)
{
	int tmp;
	(x > y) ? tmp = x : tmp = y;
	(tmp > z) ? tmp = tmp : tmp = z;
	return tmp;
}

void MarsStation::createEventsList()
{
	//Getting the event type
	char eventType, Mtype;
	ipFile >> eventType;

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
	while (MountainousMissions.getEntry(i))
	{
		MM = MountainousMissions.getEntry(i);
		if (MM)
		{
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
			//	e = currentDay;
				e = MM->GetFormulationDay();
				EmergencyMission* EM = new EmergencyMission(a, b, c, d, e);
				AddToEmergencyMissions(EM, EM->GetPriority());
				RemoveFromMountainousMissions(i);
			}
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
			MoveRoverFromBusyToAvailable();
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
	if (roversCount < maxRoversCount)
	{
		roversCount++;
		emrgncyRCount++;
	}
	EmergencyRovers.enqueue(ER, speed);
	ER->setAvailability(1);
}

void MarsStation::AddToMountainousRovers(Rover* MR, float speed)
{
	if (roversCount < maxRoversCount)
	{
		roversCount++;
		mountRCount++;
	}
	MountainousRovers.enqueue(MR, speed);
	MR->setAvailability(1);
}

void MarsStation::AddToPolarRovers(Rover* PR, float speed)
{
	if (roversCount < maxRoversCount)
	{
		roversCount++;
		polarRCount++;
	}
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
	emrgncyRCount--;
	return ER;
}

Rover* MarsStation::RemoveFromMountainousRovers()
{
	Rover* MR = NULL;
	roversCount--;
	mountRCount--;
	MountainousRovers.dequeue(MR);
	MR->setAvailability(0);
	return MR;
}

Rover* MarsStation::RemoveFromPolarRovers()
{
	Rover* PR = NULL;
	roversCount--;
	polarRCount--;
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
	while (MountainousMissions.getEntry(i))
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
		AddToInExecutionRovers(r, (-1) * r->getExecutionDays());

	}
			 break;
	case('E'): {
		r = RemoveFromEmergencyRovers();
		AddToInExecutionRovers(r, (-1) * r->getExecutionDays());

	}
			 break;
	case('P'): {
		r = RemoveFromPolarRovers();
		AddToInExecutionRovers(r, (-1) * r->getExecutionDays());
	}
			 break;
	}
}

void MarsStation::MoveRoverFromBusyToAvailable() {
	while (!InExecutionRovers.isEmpty()) {
		Rover* r=nullptr;
		InExecutionRovers.peek(r);
		if (r && r->getCompletionDay() == currentDay) {
			char type = r->getRoverType();

			switch (type) {
			case('M'): {

				r = RemoveFromInExecutionRovers();
				
				if (r->getMissionsLeft() == 0)
				{
					MoveRoverFromBusyToCheckup(r);
				}
				else {
					AddToMountainousRovers(r, r->getRoverSpeed());
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
		else
			break;
	}
}

void MarsStation::MoveRoverFromBusyToCheckup(Rover* r) {
	r->setMissionsLeft(r->getMissionsBeforeCheckUp());
	r->setLastCheckupDay(currentDay);
	AddToRoversCheckup(r, (-1) * r->getLastCheckupDay());
}

void MarsStation::MoveRoverFromCheckupToAvailable() {
	
	while(!RoversCheckup.isEmpty()){
		Rover* r = nullptr;
		RoversCheckup.peek(r);
		if (r && r->getLastCheckupDay() == currentDay)//if r->getLastCheckUpDay==currentday
		{
			r = RemoveFromRoversCheckup();
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
		else
			break;
	}

}

bool MarsStation::CheckRoverMaintenance(Rover* R)
{
	if (R->getExecutionDays() >= 10)
	{
		R->setMaintenanceStatus(1);
		return true;
	}
	return false;
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
		opFile << Finished->GetCompletionDay() << "      ";
		opFile << Finished->GetId() << "     ";
		opFile << Finished->GetFormulationDay() << "    ";
		opFile << Finished->GetWaitingDays() << "      ";
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

	//Printing rovers data
	opFile << "Rovers: " << inputFileRcount << " [M: " << inputFileMRcount << ", P: " << inputFilePRcount << ", E: " << inputFileERcount << "]\n";
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

void MarsStation::print()
{
	UserInterface->printCurrentDay(currentDay);
	UserInterface->printWaitingMissions(EmergencyMissions, MountainousMissions, PolarMissions, emrgncyMCount, mountMCount, polarMCount);
	UserInterface->printInExecution(InExecutionMissions);
	UserInterface->printAvailableRovers(roversCount, EmergencyRovers, MountainousRovers, PolarRovers);
	UserInterface->printInCheckup(checkUpCount, RoversCheckup);
	UserInterface->printCompletedMissions(completedMcount, CompletedMissions);
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


