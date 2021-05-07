#include "MarsStation.h"

MarsStation::MarsStation()
{
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
	Queue<MountainousMission*>MMQtemp;
	while (!MountainousMissions.isEmpty())
	{
		MountainousMissions.dequeue(MM);
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
			EmergencyMission*M = new EmergencyMission(a, b, c, d, e);
			AddToEmergencyMissions(M, MM->GetSignificance());
			delete MM;
		}

		else MMQtemp.enqueue(MM);
	}
	MountainousMissions = MMQtemp;
	//inexecution
	Mission*mission;
	PriQ<Mission*>InExecutionTemp;
	while (!InExecutionMissions.isEmpty())
	{
		InExecutionMissions.dequeue(mission);
		mission->DecrementInexecutionDays();
		InExecutionTemp.enqueue(mission,mission->GetCompletionDay());
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
void MarsStation::AddToEmergencyMissions(EmergencyMission* EM, int sig)
{
	EmergencyMissions.enqueue(EM, sig);
}

void MarsStation::AddToMountainousMissions(MountainousMission* MM)
{
	MountainousMissions.enqueue(MM);
}

void MarsStation::AddToPolarMissions(PolarMission* PM)
{
	PolarMissions.enqueue(PM);
}

void MarsStation::AddToEmergencyRovers(EmergencyRover* ER, int speed)
{
	EmergencyRovers.enqueue(ER, speed);
}

void MarsStation::AddToMountainousRovers(MountainousRover* MR, int speed)
{
	MountainousRovers.enqueue(MR, speed);
}

void MarsStation::AddToPolarRovers(PolarRover* PR, int speed)
{
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

void MarsStation::AddToMaintenanceRovers(Rover* R, int n)
{
	MaintenanceRovers.enqueue(R, n);
}

void MarsStation::AddToCompletedMissions(Mission* M)
{
	CompletedMissions.enqueue(M);
}

EmergencyMission* MarsStation::RemoveFromEmergencyMissions()
{
	EmergencyMission* EM = NULL;
	EmergencyMissions.dequeue(EM);
	return EM;
}

MountainousMission* MarsStation::RemoveFromMountainousMissions()
{
	MountainousMission* MM = NULL;
	MountainousMissions.dequeue(MM);
	return MM;
}

PolarMission* MarsStation::RemoveFromPolarMissions()
{
	PolarMission* PM = NULL;
	PolarMissions.dequeue(PM);
	return PM;
}

EmergencyRover* MarsStation::RemoveFromEmergencyRovers()
{
	EmergencyRover* ER = NULL;
	EmergencyRovers.dequeue(ER);
	return ER;
}

MountainousRover* MarsStation::RemoveFromMountainousRovers()
{
	MountainousRover* MR = NULL;
	MountainousRovers.dequeue(MR);
	return MR;
}

PolarRover* MarsStation::RemoveFromPolarRovers()
{
	PolarRover* PR = NULL;
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

Rover* MarsStation::RemoveFromMaintenanceRovers()
{
	Rover* R = NULL;
	MaintenanceRovers.dequeue(R);
	return R;
}

Mission* MarsStation::RemoveFromCompletedMissions()
{
	Mission* M = NULL;
	CompletedMissions.dequeue(M);
	return M;
}

void MarsStation::CancelMission(int ID)
{
	MountainousMission* M_Mission = NULL; // Represents the first mission entered in the mountainous missions queue
	Queue<MountainousMission*> temp; // Temp queue to store all mountainous missions except the one to be cancelled
	while (!MountainousMissions.isEmpty())
	{
		MountainousMissions.peek(M_Mission); // Get the first mission
		if (M_Mission->GetId() == ID)
		{
			MountainousMissions.dequeue(M_Mission); // delete it from the list if found
		}
		else
		{
			MountainousMissions.dequeue(M_Mission);
			temp.enqueue(M_Mission);
			// If not found, remove mission and add it to the temp queue
		}
	}
	MountainousMissions = temp; // Equate both queues
}

void MarsStation::PromoteMission(int ID)
{
	MountainousMission* M_Mission = NULL; // Represents the first mission entered in the mountainous missions queue
	Queue<MountainousMission*> temp; // Temp queue to store all mountainous missions except the one to be promoted to emergency
	while (!MountainousMissions.isEmpty())
	{
		MountainousMissions.peek(M_Mission); // Get the first mission using peek function
		if (M_Mission->GetId() == ID)
		{
			MountainousMissions.dequeue(M_Mission); // delete it from the list if found
			EmergencyMission* EM = new EmergencyMission(); // Create a new E.Mission and give it the same info of the M.Mission in the constructor
			EmergencyMissions.enqueue(EM, M_Mission->GetSignificance()); // Add the new mission to the emergency missions list
		}
		else
		{
			MountainousMissions.dequeue(M_Mission);
			temp.enqueue(M_Mission);
			// If not found, remove mission and add it to the temp queue
		}
	}
	MountainousMissions = temp; // Equate both queues
}

void MarsStation::MoveRoverFromAvailabeToBusy(Rover*r) {

	char type = r->getRoverType();

	switch (type) {
	case('M') : {

		r = RemoveFromMountainousRovers();
		AddToInExecutionRovers(r, r->getAssignedMission()->GetExecutionDays());

	}
				break;
	case('E') : {
		r = RemoveFromEmergencyRovers();
		AddToInExecutionRovers(r, r->getAssignedMission()->GetExecutionDays());

	}
				break;
	case('P') : {
		r = RemoveFromPolarRovers();
		AddToInExecutionRovers(r, r->getAssignedMission()->GetExecutionDays());
	}
				break;

	}
}

void MarsStation::MoveRoverFromBusyToAvailable() {
	while (!InExecutionRovers.isEmpty()) {
		Rover* r = nullptr;
		InExecutionRovers.peek(r);
		if (r->getAssignedMission()->GetCompletionDay() == currentDay) {
			char type = r->getRoverType();

			switch (type) {
			case('M') : {

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
			case('E') : {

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
			case('P') : {

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

	while (!RoversCheckup.isEmpty()){
		Rover* r = nullptr;
		RoversCheckup.peek(r);
		if (!r->inMaintenance())//if r->getLastCheckUpDay==currentday
		{
			r = RemoveFromRoversCheckup();
			char type = r->getRoverType();
			switch (type)
			{
			case('M') :
				AddToMountainousRovers(r, r->getRoverSpeed());
				break;
			case('E') :
				AddToEmergencyRovers(r, r->getRoverSpeed());
				break;
			case('P') :
				AddToPolarRovers(r, r->getRoverSpeed());

			}
		}

	}

}
MarsStation::~MarsStation()
{
}


