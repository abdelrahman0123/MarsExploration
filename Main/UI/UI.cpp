#pragma once
#include "UI.h"

UI::UI()
{
}
char UI::selectMode()
{
	char c;
	cout << "Enter i for INTERACTIVE MODE\n Or s for STEP-BY-STEP MODE\n or t for SILENT MODE:\n";
	cin >> c;
	return c;

}

bool UI::interactiveMode()
{
	char c;
	cout << "Press ENTER to start\n";
	cin >> c;
	if (c == 0x0A)
		return true;
	else
		return 0;

	/*while (cin >> c) {
		if (c == 0x0A) {

			  printCurrentDay(int day);
			  printWaitingMissions(PriQ<EmergencyMission*> emrgncy, LinkedList<MountainousMission*> mount, Queue<PolarMission*> polar, int E, int M, int P);
			  printInExecution(PriQ<Mission*> missions);
			  printAvailableRovers(int availableRvrs, PriQ<Rover*> emrgncy, PriQ<Rover*> mount, PriQ<Rover*> polar);
			  printInCheckup(int checkup, PriQ<Rover*> rovers);
			  printCompletedMissions(int completedCount, Queue<Mission*> Completed);

		}

	}*/



}
void UI::stepByStepMode() {

}

void UI::silentMode()
{
	cout << " Silent Mode\n Simulation Starts...\n Simulation ends, Output file created\n";
}
void UI::printCurrentDay(int day)
{
	cout << "Current Day: " << day << endl;
}

void UI::printWaitingMissions(PriQ<EmergencyMission*> emrgncy, LinkedList<MountainousMission*> mount, Queue<PolarMission*> polar, int E, int M, int P)
{
	cout << E + M + P << " Waiting Missions: ";

	if (E != 0)
	{
		cout << "[";
		EmergencyMission* x;
		while (!emrgncy.isEmpty())
		{
			emrgncy.dequeue(x);
			cout << x->GetId();
			if (!emrgncy.isEmpty())
				cout << ',';
		}
		cout << "] ";
	}

	if (P != 0)
	{
		cout << '(';
		PolarMission* x;
		while (!polar.isEmpty())
		{
			polar.dequeue(x);
			cout << x->GetId();
			if (!polar.isEmpty())
				cout << ',';
		}
		cout << ") ";
	}

	for (int i = 1; i <= M; i++)
	{
		if (i == 1)
			cout << '{';
		int x = mount.getEntry(i)->GetId();
		cout << x;
		if (i < M)
			cout << ',';
		if (i == M)
			cout << "} ";
	}

	cout << endl << "-------------------------------------------------------" << endl;
}

void UI::printInExecution(PriQ<Mission*> missions)
{
	Queue<EmergencyMission*> Emrgncylist;		Queue<MountainousMission*> Mountlist;		Queue<PolarMission*> Polarlist;
	EmergencyMission* Emrgncy;					MountainousMission* Mount;					PolarMission* Polar;
	Mission* temp;
	int count{ 0 };

	while (!missions.isEmpty())
	{
		missions.dequeue(temp);
		Emrgncy = dynamic_cast<EmergencyMission*>(temp);
		if (Emrgncy)
		{
			Emrgncylist.enqueue(Emrgncy);
			count++;
			continue;
		}
		Mount = dynamic_cast<MountainousMission*>(temp);
		if (Mount)
		{
			Mountlist.enqueue(Mount);
			count++;
			continue;
		}
		Polar = dynamic_cast<PolarMission*>(temp);
		count++;
		Polarlist.enqueue(Polar);
	}

	cout << count << " In-Execution Missions/Rovers: ";

	if (!Emrgncylist.isEmpty())
	{
		cout << '[';
		while (!Emrgncylist.isEmpty())
		{
			Emrgncylist.dequeue(Emrgncy);
			cout << Emrgncy->GetId() << '/';
			cout << Emrgncy->getAssociated()->getRoverID();
			if (!Emrgncylist.isEmpty())
				cout << ", ";
		}
		cout << "] ";
	}

	if (!Polarlist.isEmpty())
	{
		cout << '(';
		while (!Polarlist.isEmpty())
		{
			Polarlist.dequeue(Polar);
			cout << Polar->GetId() << '/';
			cout << Polar->getAssociated()->getRoverID();
			if (!Polarlist.isEmpty())
				cout << ", ";
		}
		cout << ") ";
	}

	if (!Mountlist.isEmpty())
	{
		cout << '{';
		while (!Mountlist.isEmpty())
		{
			Mountlist.dequeue(Mount);
			cout << Mount->GetId() << '/';
			cout << Mount->getAssociated()->getRoverID();
			if (!Mountlist.isEmpty())
				cout << ", ";
		}
		cout << "} ";
	}

	cout << endl << "-------------------------------------------------------" << endl;
}

void UI::printAvailableRovers(int num, PriQ<Rover*> emrgncy, PriQ<Rover*> mount, PriQ<Rover*> polar)
{
	cout << num << " Available Rovers: ";

	Rover* tmp;

	if (!emrgncy.isEmpty())
	{
		cout << '[';
		while (!emrgncy.isEmpty())
		{
			emrgncy.dequeue(tmp);
			cout << tmp->getRoverID();
			if (!emrgncy.isEmpty())
				cout << ", ";
		}
		cout << "] ";
	}

	if (!polar.isEmpty())
	{
		cout << '(';
		while (!polar.isEmpty())
		{
			polar.dequeue(tmp);
			cout << tmp->getRoverID();
			if (!polar.isEmpty())
				cout << ", ";
		}
		cout << ") ";
	}

	if (!mount.isEmpty())
	{
		cout << '{';
		while (!mount.isEmpty())
		{
			mount.dequeue(tmp);
			cout << tmp->getRoverID();
			if (!mount.isEmpty())
				cout << ", ";
		}
		cout << "} ";
	}

	cout << endl << "-------------------------------------------------------" << endl;

}

void UI::printInCheckup(int num, PriQ<Rover*> rovers)
{
	cout << num << "  In-Checkup Rovers: ";

	Queue<int> e, p, m;
	Rover* tmp;
	char c;

	while (rovers.dequeue(tmp))
	{
		c = tmp->getRoverType();
		switch (c)
		{
		case 'E':
			e.enqueue(tmp->getRoverID());
			break;
		case 'P':
			p.enqueue(tmp->getRoverID());
			break;
		case 'M':
			m.enqueue(tmp->getRoverID());
			break;
		}
	}

	int x;

	if (!e.isEmpty())
	{
		cout << '[';
		while (e.dequeue(x))
		{
			cout << x;
			if (!e.isEmpty())
				cout << ',';
		}
		cout << "] ";
	}

	if (!p.isEmpty())
	{
		cout << '(';
		while (p.dequeue(x))
		{
			cout << x;
			if (!p.isEmpty())
				cout << ',';
		}
		cout << ") ";
	}

	if (!m.isEmpty())
	{
		cout << '{';
		while (m.dequeue(x))
		{
			cout << x;
			if (!m.isEmpty())
				cout << ',';
		}
		cout << "} ";
	}

	cout << endl << "-------------------------------------------------------" << endl;

}

void UI::printCompletedMissions(int num, Queue<Mission*> Completed)
{
	cout << num << "  Completed Missions: ";

	Queue<EmergencyMission*> Emrgncylist;		Queue<MountainousMission*> Mountlist;		Queue<PolarMission*> Polarlist;
	EmergencyMission* Emrgncy;					MountainousMission* Mount;					PolarMission* Polar;
	Mission* temp;

	while (!Completed.isEmpty())
	{
		Completed.dequeue(temp);
		Emrgncy = dynamic_cast<EmergencyMission*>(temp);
		if (Emrgncy)
		{
			Completed.enqueue(Emrgncy);
			continue;
		}

		Mount = dynamic_cast<MountainousMission*>(temp);
		if (Mount)
		{
			Mountlist.enqueue(Mount);
			continue;
		}

		Polar = dynamic_cast<PolarMission*>(temp);
		Polarlist.enqueue(Polar);
	}


	if (!Emrgncylist.isEmpty())
	{
		cout << '[';
		while (Emrgncylist.dequeue(Emrgncy))
		{

			cout << Emrgncy->GetId();
			if (!Emrgncylist.isEmpty())
				cout << ", ";
		}
		cout << "] ";
	}

	if (!Polarlist.isEmpty())
	{
		cout << '(';
		while (Polarlist.dequeue(Polar))
		{
			cout << Polar->GetId();
			if (!Polarlist.isEmpty())
				cout << ", ";
		}
		cout << ") ";
	}

	if (!Mountlist.isEmpty())
	{
		cout << '{';
		while (Mountlist.dequeue(Mount))
		{
			cout << Mount->GetId();
			if (!Mountlist.isEmpty())
				cout << ", ";
		}
		cout << "} ";
	}

	cout << endl << "-------------------------------------------------------" << endl;
}
