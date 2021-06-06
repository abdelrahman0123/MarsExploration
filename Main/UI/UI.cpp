#pragma once
#include "UI.h"

UI::UI()
{
}
char UI::selectMode()
{
	char c;
	cout << "**************************************************" << endl;
	cout << "*                                                *" << endl;
	cout << "*          ~~~~~MARS EXPLORATION~~~~~            *" << endl;
	cout << "*                                                *" << endl;
	cout << "**************************************************" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Enter 'i' for simulation in the Interactive Mode |" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Enter 's' for the Step-By-Step Mode              |" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Enter 't' for the Silent Mode                    |" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "--> ";
	cin >> c;
	cout << "\n\n";
	return c;

}

bool UI::interactiveMode()
{
	char c;
	cout << "~~Press ENTER to display the output of the next day.\n\n";
	cin.sync();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return true;
	/*--Enter
	cin.sync();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	*/
}
void UI::stepByStepMode() {
	
}

void UI::silentMode()
{
	cout << "Silent Mode\nSimulation Starts...\nSimulation ends, Output file created\n";
}
void UI::printCurrentDay(int day)
{
	cout << "Current Day: " << day << endl << endl;
}

void UI::printWaitingMissions(PriQ<EmergencyMission*>& emrgncy, LinkedList<MountainousMission*>& mount, Queue<PolarMission*>& polar, int E, int M, int P)
{
	cout << E + M + P << " Waiting Missions: ";
	PriQ<EmergencyMission*> Etemp = emrgncy;
	LinkedList<MountainousMission*> Mtemp = mount;
	Queue<PolarMission*> Ptemp = polar;
	if (E != 0)
	{
		cout << "[";
		EmergencyMission* x;
		while (!Etemp.isEmpty())
		{
			Etemp.dequeue(x);
			cout << x->GetId();
			if (!Etemp.isEmpty())
				cout << ',';
		}
		cout << "] ";
	}

	if (P != 0)
	{
		cout << '(';
		PolarMission* x;
		while (!Ptemp.isEmpty())
		{
			Ptemp.dequeue(x);
			cout << x->GetId();
			if (!Ptemp.isEmpty())
				cout << ',';
		}
		cout << ") ";
	}

	for (int i = 1; i <= M; i++)
	{
		if (i == 1)
			cout << '{';
		int x = Mtemp.getEntry(i)->GetId();
		cout << x;
		if (i < M)
			cout << ',';
		if (i == M)
			cout << "} ";
	}

	cout << endl << "-------------------------------------------------------" << endl;
}

void UI::printInExecution(PriQ<Mission*>& missions)
{
	PriQ<Mission*> ExecTemp = missions;
	Queue<EmergencyMission*> Emrgncylist;		Queue<MountainousMission*> Mountlist;		Queue<PolarMission*> Polarlist;
	EmergencyMission* Emrgncy;					MountainousMission* Mount;					PolarMission* Polar;
	Mission* temp;
	int count{ 0 };

	while (!ExecTemp.isEmpty())
	{
		ExecTemp.dequeue(temp);
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

void UI::printAvailableRovers(int num, PriQ<Rover*>& emrgncy, PriQ<Rover*>& mount, PriQ<Rover*>& polar)
{
	cout << num << " Available Rovers: ";

	Rover* tmp;
	PriQ<Rover*> Etemp = emrgncy;
	PriQ<Rover*> Mtemp = mount;
	PriQ<Rover*> Ptemp = polar;
	if (!Etemp.isEmpty())
	{
		cout << '[';
		while (!Etemp.isEmpty())
		{
			Etemp.dequeue(tmp);
			cout << tmp->getRoverID();
			if (!Etemp.isEmpty())
				cout << ", ";
		}
		cout << "] ";
	}

	if (!Ptemp.isEmpty())
	{
		cout << '(';
		while (!Ptemp.isEmpty())
		{
			Ptemp.dequeue(tmp);
			cout << tmp->getRoverID();
			if (!Ptemp.isEmpty())
				cout << ", ";
		}
		cout << ") ";
	}

	if (!Mtemp.isEmpty())
	{
		cout << '{';
		while (!Mtemp.isEmpty())
		{
			Mtemp.dequeue(tmp);
			cout << tmp->getRoverID();
			if (!Mtemp.isEmpty())
				cout << ", ";
		}
		cout << "} ";
	}

	cout << endl << "-------------------------------------------------------" << endl;

}

void UI::printInCheckup(int num, PriQ<Rover*>& rovers)
{
	cout << num << "  In-Checkup Rovers: ";

	PriQ<Rover*> Check = rovers;
	Queue<int> e, p, m;
	Rover* tmp;
	char c;

	while (Check.dequeue(tmp))
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

void UI::printCompletedMissions(int num, Queue<Mission*>& Completed)
{
	cout << num << "  Completed Missions: ";

	Queue<Mission*> Comp = Completed;
	Queue<EmergencyMission*> Emrgncylist;		Queue<MountainousMission*> Mountlist;		Queue<PolarMission*> Polarlist;
	EmergencyMission* Emrgncy;					MountainousMission* Mount;					PolarMission* Polar;
	Mission* temp;

	while (!Comp.isEmpty())
	{
		Comp.dequeue(temp);
		Emrgncy = dynamic_cast<EmergencyMission*>(temp);
		if (Emrgncy)
		{
			Emrgncylist.enqueue(Emrgncy);
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

	cout << "\n\n************************************************************************************************************************\n\n";
}

void UI::printEnd()
{
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||THE END||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
