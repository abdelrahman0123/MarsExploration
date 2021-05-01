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

void MarsStation::CancelMountainousMission(MountainousMission* MM)
{
}

void MarsStation::PromoteMountainousMission(MountainousMission* MM)
{
}

MarsStation::~MarsStation()
{
}


