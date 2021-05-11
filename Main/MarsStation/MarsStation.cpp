#include "MarsStation.h"

MarsStation::MarsStation()
{
	
}

void MarsStation::ReadInput()
{
	////////// Reading Rovers Data //////////
	interact.readRovers();
	Queue<int>* er = interact.getEmRovers();
	Queue<int>* pr = interact.getPolarRovers();
	Queue<int>* mr = interact.getMountRovers();

	int speed;
	EmergencyRover* tempEmergency;
	while (!er->isEmpty())
	{
		tempEmergency = new EmergencyRover();	//**SARAH**//Edit the non-default constructor /// Make the speed first
		er->dequeue(speed);
		AddToEmergencyRovers(tempEmergency, speed);
	}

	PolarRover* tempPolar;
	while (!pr->isEmpty())
	{
		tempPolar = new PolarRover();
		pr->dequeue(speed);
		AddToPolarRovers(tempPolar, speed);
	}

	MountainousRover* tempMount;
	while (!mr->isEmpty())
	{
		tempMount = new MountainousRover();
		mr->dequeue(speed);
		AddToMountainousRovers(tempMount, speed);
	}

	// Setting the auto promotion limit
	int AutoP = interact.getAutoP();

	//Reading the events Data
	int n = interact.getNumofEvents();
	Queue<int>* eventNumbers;
	int ED, ID, TLOC, MissionDur, SIG;
	for (int i = 0; i < n; i++)
	{
		eventNumbers = interact.getEvent();
		eventNumbers->dequeue(ED);
		eventNumbers->dequeue(ID);
		if (!eventNumbers->isEmpty())
		{
			eventNumbers->dequeue(TLOC);
			eventNumbers->dequeue(MissionDur);
			eventNumbers->dequeue(SIG);

			Event* evptr = new FormulationEvent(interact.getMT(), ED, ID, TLOC, MissionDur, SIG);
			AddToEvents(evptr);
		}
		else
		{
			EventType ET = interact.getET();
			if (ET == Cancel)
			{
				Event* evptr = new CancelEvent(ED, ID);
				AddToEvents(evptr);
			}
			else
			{
				Event* evptr = new PromoteEvent(ED, ID);
				AddToEvents(evptr);
			}
		}
		
	}
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
		EMQtemp.enqueue(EM,EM->GetPriority());
	}
	EmergencyMissions = EMQtemp;
	//polar
	PolarMission* PM;
	Queue<PolarMission*>PMQtemp;
	while (!PolarMissions.isEmpty())
	{
		PolarMissions.dequeue(PM);
		PM->IncrementWaitingDays();
		PMQtemp.enqueue(PM);
	}
	PolarMissions = PMQtemp;
	//Mountainous
	MountainousMission* MM;
	int i = 1;
	while (!MountainousMissions.isEmpty())
	{
		MM = MountainousMissions.getEntry(i);
		MM->IncrementWaitingDays();
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
		InExecutionTemp.enqueue(mission,mission->GetExecutionDays());
	}
	InExecutionMissions = InExecutionTemp;
	//assign to rover
	HandleMission();

}
void MarsStation::HandleMission()
{
	Mission*Temp;
	//CALL ASSIGN TO ROVER(la hena la fo2 
	
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
}

void MarsStation::AddToMountainousMissions(MountainousMission* MM)
{
	MountainousMissions.insert(++MountMissionsCount, MM);
}

void MarsStation::AddToPolarMissions(PolarMission* PM)
{
	PolarMissions.enqueue(PM);
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
	R->DecrementMissionsLeft();
}

void MarsStation::AddToRoversCheckup(Rover* R, int n)
{
	RoversCheckup.enqueue(R, n);
	R->setAvailability(0);
}

void MarsStation::AddToCompletedMissions(Mission* M)
{
	CompletedMissions.enqueue(M);
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
	return EM;
}

MountainousMission* MarsStation::RemoveFromMountainousMissions(int i)
{
	MountainousMission* MM = MountainousMissions.getEntry(i);
	MountainousMissions.remove(i);
	MountMissionsCount--;
	return MM;
}

PolarMission* MarsStation::RemoveFromPolarMissions()
{
	PolarMission* PM = NULL;
	PolarMissions.dequeue(PM);
	return PM;
}

Rover* MarsStation::RemoveFromEmergencyRovers()
{
	Rover* ER = NULL;
	EmergencyRovers.dequeue(ER);
	ER->setAvailability(0);
	return ER;
}

Rover* MarsStation::RemoveFromMountainousRovers()
{
	Rover* MR = NULL;
	MountainousRovers.dequeue(MR);
	MR->setAvailability(0);
	return MR;
}

Rover* MarsStation::RemoveFromPolarRovers()
{
	Rover* PR = NULL;
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
	R->setAvailability(1);
	return R;
}

Rover* MarsStation::RemoveFromRoversCheckup()
{
	Rover* R = NULL;
	RoversCheckup.dequeue(R);
	R->setAvailability(1);

	return R;
}

Mission* MarsStation::RemoveFromCompletedMissions()
{
	Mission* M = NULL;
	CompletedMissions.dequeue(M);
	return M;
}

int MarsStation::getMountMissionsCount()
{
	return MountMissionsCount;
}

void MarsStation::IncrementMountMissionsCount()
{
	MountMissionsCount++;
}

void MarsStation::DecrementMountMissionsCount()
{
	MountMissionsCount--;
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
		AddToInExecutionRovers(r, r->getAssignedMission()->GetExecutionDays());

	}
			 break;
	case('E'): {
		r = RemoveFromEmergencyRovers();
		AddToInExecutionRovers(r, r->getAssignedMission()->GetExecutionDays());

	}
			 break;
	case('P'): {
		r = RemoveFromPolarRovers();
		AddToInExecutionRovers(r, r->getAssignedMission()->GetExecutionDays());
	}
			 break;

	}
}

void MarsStation::MoveRoverFromBusyToAvailable() {
	while (!InExecutionRovers.isEmpty()) {
		Rover* r=nullptr;
		InExecutionRovers.peek(r);
		if (r->getAssignedMission()->GetCompletionDay() == currentDay) {
			char type = r->getRoverType();

			switch (type) {
			case('M'): {
				
				r=RemoveFromInExecutionRovers();

				if (r->getMissionsLeft() == 0)
				{ 
					MoveRoverFromAvailableToCheckup(r);
				
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
					MoveRoverFromAvailableToCheckup(r);
					
				}
				else {
					AddToMountainousRovers(r, r->getRoverSpeed());
				}

			}
					 break;
			case('P'): {

				r = RemoveFromInExecutionRovers();

				if (r->getMissionsLeft() == 0)
				{
					MoveRoverFromAvailableToCheckup(r);
					break;
				}
				else {
					AddToMountainousRovers(r, r->getRoverSpeed());
				}

			}
					 break;

			}
		} //#### ELSE, A FUNCTION TO DECREMENT ALL DAYS LEFT SHOULD BE ADDED ####
	}
}

void MarsStation::MoveRoverFromAvailableToCheckup(Rover* r) {
	
	AddToRoversCheckup(r, r->getcheckupDuration());
		r->setAvailability(0);
		r->setMaintenanceStatus(1);
	
}

void MarsStation::MoveRoverFromCheckupToAvailable() {
	
	while(!RoversCheckup.isEmpty()){
		Rover* r = nullptr;
		RoversCheckup.peek(r);
		if (!r->inMaintenance())//if r->getLastCheckUpDay==currentday
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

MarsStation::~MarsStation()
{
}


