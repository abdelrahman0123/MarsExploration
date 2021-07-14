#include "MarsStation.h"

MarsStation::MarsStation()
{
	
}

void MarsStation::Simulate()
{
	char x = UserInterface->selectMode();

	if (roversCount == 0)		//Case of no rovers in input file
	{
		switch (x)
		{
		case('t'):
			while (!Events.isEmpty())
			{
				ExecuteEvent();
				IncrementCurrentDay();
			}
			UserInterface->silentMode();
			break;
		default:
			while (!Events.isEmpty())
			{
				ExecuteEvent();
				IncrementCurrentDay();
			}
			print();
			break;
		}
		return;
	}
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
			if (NotValid())
				break;
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
		if (NotValid())
			break;
		simulateG(1);
	}
	UserInterface->printEnd();
}

void MarsStation::simulateSilent()
{
	while (!Events.isEmpty() || !InExecutionMissions.isEmpty() || !CheckWaitingMissions() || !RoversCheckup.isEmpty())
	{
		if (NotValid())
			break;
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
	case(0): //Interactive
		print();
		break;
	case(1): //StepByStep
		print();
		sleep_for(seconds(1));
		break;
	default: //Silent
		break;
	}
	IncrementCurrentDay();
}

bool MarsStation::NotValid()
{
	//Check Polar Mission not having any available polar rover
	if (Events.isEmpty() && InExecutionMissions.isEmpty() && RoversCheckup.isEmpty() &&
		!PolarMissions.isEmpty() && PolarRovers.isEmpty())
	{
		return true;
	}
	//Check Mountainous Mission not having any available mountainous/emergency rover
	else if (Events.isEmpty() && InExecutionMissions.isEmpty() && RoversCheckup.isEmpty() &&
		!MountainousMissions.isEmpty() && EmergencyRovers.isEmpty() && MountainousRovers.isEmpty())
	{
		return true;
	}
	//Valid
	return false;
}

void MarsStation::ReadInput(string Input)
{
	// Opening input file
	ipFile.open(Input, ios::in);

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
		roversCount = mountRCount + polarRCount + emrgncyRCount;
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
			tempRover = new Rover(ID, CM, Mspeeds[z], beforeCheck, 'M');
			AddToMountainousRovers(tempRover, Mspeeds[z]);
			z++;
			ID++;
		}

		//Creating Polar rovers
		z = 0;
		while (Pspeeds[z] != -1 && z != max)
		{
			tempRover = new Rover(ID, CP, Pspeeds[z], beforeCheck, 'P');
			AddToPolarRovers(tempRover, (float)Pspeeds[z]);
			z++;
			ID++;
		}

		//Creating Emergency rovers
		z = 0;
		while (Espeeds[z] != -1 && z != max)
		{
			tempRover = new Rover(ID, CE, Espeeds[z], beforeCheck, 'E');
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
	//Update Waiting Emergency
	EmergencyMission* EM;
	PriQ<EmergencyMission*>EMQtemp;
	while (!EmergencyMissions.isEmpty())
	{
		EmergencyMissions.dequeue(EM);
		EM->IncrementWaitingDays();
		EM->SetCompletionDay();
		EMQtemp.enqueue(EM,EM->GetPriority());
	}
	ExchangeEMissions(EMQtemp, EmergencyMissions);

	//Update Waiting Polar
	PolarMission* PM;
	Queue<PolarMission*>PMQtemp;
	while (!PolarMissions.isEmpty())
	{
		PolarMissions.dequeue(PM);
		PM->IncrementWaitingDays();
		PM->SetCompletionDay();
		PMQtemp.enqueue(PM);
	}
	ExchangeQueues(PMQtemp, PolarMissions);

	//Update Waiting Mountainous
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
			if (MM->GetAutoPromotion() == 0)	//Auto-Promotion
			{
				MM->setAutoP();
				autoPCount++;
				int ID = MM->GetId();
				PromoteMission(ID);
				i--;
			}
		}
		i++;
	}
	//Update InExecution Missions
	Mission* M;
	Rover* R;
	PriQ<Mission*> InExecutionTemp;
	PriQ<Rover*> InExecutionRov;
	while (!InExecutionMissions.isEmpty())
	{
		InExecutionMissions.dequeue(M);
		InExecutionRovers.dequeue(R);
		M->DecrementInexecutionDays();
		R->DecrementExecutionDays();
		InExecutionRov.enqueue(R, (-1) * R->getExecutionDays());
		InExecutionTemp.enqueue(M, (-1) * M->GetExecutionDays());
	}
	ExchangeExecMissions(InExecutionTemp, InExecutionMissions);
	ExchangeExecRovers(InExecutionRov, InExecutionRovers);

	//Check if there are any complete missions and add them to the completed list
	HandleMission();
}

void MarsStation::HandleMission()
{
	Mission* Temp;
	
	while (!InExecutionMissions.isEmpty())
	{
		InExecutionMissions.peek(Temp);
		if (Temp->GetExecutionDays() == 0)
		{
			Temp=RemoveFromInExecutionMissions();
			Temp->UpdateToCompleted();
			AddToCompletedMissions(Temp);
		}
		else break;
	}

}

void MarsStation::AddToEmergencyMissions(EmergencyMission* EM, int pri)
{
	EM->SetPriority();
	pri = EM->GetPriority();
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
	if (roversCount < maxRoversCount)		// Checking condition to not increase the actual available rovers count more than their max
	{
		roversCount++;
		emrgncyRCount++;
	}
	EmergencyRovers.enqueue(ER, speed);
}

void MarsStation::AddToMountainousRovers(Rover* MR, float speed)
{
	if (roversCount < maxRoversCount)		// Checking condition to not increase the actual available rovers count more than their max
	{
		roversCount++;
		mountRCount++;
	}
	MountainousRovers.enqueue(MR, speed);
}

void MarsStation::AddToPolarRovers(Rover* PR, float speed)
{
	if (roversCount < maxRoversCount)		// Checking condition to not increase the actual available rovers count more than their max
	{
		roversCount++;
		polarRCount++;
	}
	PolarRovers.enqueue(PR, speed);
}

void MarsStation::AddToInExecutionMissions(Mission* M, int n)
{
	InExecutionMissions.enqueue(M, n);
}

void MarsStation::AddToInExecutionRovers(Rover* R, int n)
{
	InExecutionRovers.enqueue(R, n);
}

void MarsStation::AddToRoversCheckup(Rover* R, int n)
{
	RoversCheckup.enqueue(R, n);
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
	if (MM)
	{
		MountainousMissions.remove(i);
		mountMCount--;
	}
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
	return MR;
}

Rover* MarsStation::RemoveFromPolarRovers()
{
	Rover* PR = NULL;
	roversCount--;
	polarRCount--;
	PolarRovers.dequeue(PR);
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
		if (!CheckAvailableRover(R, 'E')) //Check for emergency first
			if (!CheckAvailableRover(R, 'M')) //If not, check for mountainous
				if (!CheckAvailableRover(R, 'P')) //Finally, check for polar if all of the above are false
					break; //No available rover-->Do not assign
		EM->SetExecutionDays(R->getRoverSpeed());
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
		if (!CheckAvailableRover(R, 'M')) //Check for mountainous rover first
			if (!CheckAvailableRover(R, 'E')) //If not, check for emergency
				break; //No available E/M rover-->Do not assign
		MM->SetExecutionDays(R->getRoverSpeed());
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
		if (!CheckAvailableRover(R, 'P')) //Check for polar rover only
			break; //No available P rover-->Do not assign
		PM->SetExecutionDays(R->getRoverSpeed());
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
	while (MountainousMissions.getEntry(i))
	{
		MountainousMission* M_Mission = MountainousMissions.getEntry(i);
		int MissionID = M_Mission->GetId();
		if (MissionID == ID)
		{
			if (!M_Mission->AutoPromoted())
				promotedCount++;
			int TLOC = M_Mission->GetTargetLocation();
			int MDUR = M_Mission->GetMissDuration();
			int SIG = M_Mission->GetSignificance();
			int FD = M_Mission->GetFormulationDay();
			int WD = M_Mission->GetWaitingDays();
			RemoveFromMountainousMissions(i);
			EmergencyMission* EM = new EmergencyMission(MissionID, TLOC, MDUR, SIG, FD);
			EM->SetWaitingDays(WD);
			AddToEmergencyMissions(EM, EM->GetPriority());
			break;
		}
		i++;
	}
}

void MarsStation::MoveRoverFromAvailabeToBusy(Rover*r)
{

	char type = r->getRoverType();
	
	switch (type) {
	case('M'):
		r = RemoveFromMountainousRovers();
		AddToInExecutionRovers(r, (-1) * r->getExecutionDays());
		break;
	case('E'):
		r = RemoveFromEmergencyRovers();
		AddToInExecutionRovers(r, (-1) * r->getExecutionDays());
		break;
	case('P'):
		r = RemoveFromPolarRovers();
		AddToInExecutionRovers(r, (-1) * r->getExecutionDays());
		break;
	}
}

void MarsStation::MoveRoverFromBusyToAvailable() 
{
	while (!InExecutionRovers.isEmpty()) {
		Rover* r = nullptr;
		InExecutionRovers.peek(r);
		if (r && r->getExecutionDays() == 0) {
			char type = r->getRoverType();

			switch (type) {
			case('M'):
				r = RemoveFromInExecutionRovers();

				if (r->getMissionsLeft() == 0)
				{
					MoveRoverFromBusyToCheckup(r);
				}
				else {
					AddToMountainousRovers(r, r->getRoverSpeed());
				}
				break;

			case('E'):
				r = RemoveFromInExecutionRovers();

				if (r->getMissionsLeft() == 0)
				{
					MoveRoverFromBusyToCheckup(r);
				}
				else {
					AddToEmergencyRovers(r, r->getRoverSpeed());
				}
				break;
			case('P'):
				r = RemoveFromInExecutionRovers();

				if (r->getMissionsLeft() == 0)
				{
					MoveRoverFromBusyToCheckup(r);
					break;
				}
				else {
					AddToPolarRovers(r, r->getRoverSpeed());
				}
				break;
			}
		}
		else
			break;
	}
}

void MarsStation::MoveRoverFromBusyToCheckup(Rover* r) 
{
	r->setMissionsLeft(r->getMissionsBeforeCheckUp());
	r->setLastCheckupDay(currentDay);
	AddToRoversCheckup(r, (-1) * r->getLastCheckupDay());
}

void MarsStation::MoveRoverFromCheckupToAvailable() 
{
	
	while(!RoversCheckup.isEmpty()){
		Rover* r = nullptr;
		RoversCheckup.peek(r);
		if (r && r->getLastCheckupDay() == currentDay)
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
				break;
			}
		}
		else
			break;
	}

}

void MarsStation::PrintOutput()
{
	//Opening the output file
	opFile.open("Output.txt", ios::out);

	//Setting the file
	opFile << "CD\tID\tFD\tWD\tED\n";

	//Collecting statistics and printing the data
	getStatistics();

}

void MarsStation::getStatistics()
{
	int missionCount{ 0 }, mountCount{ 0 }, polarCount{ 0 }, emergencyCount{ 0 };
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
			break;
		}
		waitDays = waitDays + Finished->GetWaitingDays();		//Counting the total waiting days
		exeDays = exeDays + Finished->GetExecutionPeriod();		//Counting the total execution days

		//Printing the mission details
		opFile << Finished->GetCompletionDay() << "\t";
		opFile << Finished->GetId() << "\t";
		opFile << Finished->GetFormulationDay() << "\t";
		opFile << Finished->GetWaitingDays() << "\t";
		opFile << Finished->GetExecutionPeriod() << "\n";
	}

	if (missionCount == 0)
	{
		avgWaiting = 0;
		avgExecution = 0;
	}
	else
	{
		avgWaiting = waitDays / missionCount;
		avgExecution = exeDays / missionCount;
	}

	//Printing the statistics results
	opFile << "Missions: " << missionCount << " [M: " << mountCount << ", P: " << polarCount << ", E: " << emergencyCount << "]\n";
	printRoversData();
	opFile << "Avg Wait = " << avgWaiting << ", Avg Exec = " << avgExecution << "\n";
	if (autoPCount > 0)
		opFile << "Auto-promoted: " << (float)autoPCount * 100 / (float) (autoPCount + mountCount + promotedCount) << '%';
	else
		opFile << "Auto-promoted: " << "0 %";
}

void MarsStation::printRoversData()
{
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

void MarsStation::ExchangeExecRovers(PriQ<Rover*>& Q1, PriQ<Rover*>& Q2)
{
	Rover* temp;
	while (!Q1.isEmpty())
	{
		Q1.dequeue(temp);
		Q2.enqueue(temp, (-1) * temp->getExecutionDays());
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