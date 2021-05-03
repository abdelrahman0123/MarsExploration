#include "MarsStation.h"

MarsStation::MarsStation()
{
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
			int id = M_Mission->GetId();
			int TLOC = M_Mission->GetTargetLocation();
			int MDUR = M_Mission->GetMissDuration();
			int SIG = M_Mission->GetSignificance();
			int FD = M_Mission->GetFormulationDay();
			MountainousMissions.dequeue(M_Mission); // delete it from the list if found
			EmergencyMission* EM = new EmergencyMission(id, TLOC, MDUR, SIG, FD); // Create a new E.Mission and give it the same info of the M.Mission in the constructor
			EmergencyMissions.enqueue(EM, EM->GetPriority()); // Add the new mission to the emergency missions list
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

MarsStation::~MarsStation()
{
}


