#include "UI.h"

UI::UI()
{
	ipFile.open("Input.txt", ios::in);
	emergencyRovers = new Queue<int>;
	polarRovers = new Queue<int>;
	mountRovers = new Queue<int>;
}

void UI::readRovers()
{
	if (ipFile.is_open())
	{
		int x, y, z, temp;
		//Getting rovers no.
		ipFile >> x >> y >> z;
		//Getting max no. of rovers
		(x > y) ? temp = x : temp = y;
		(temp > z) ? temp = temp : temp = z;
		//Getting rovers' speeds
		for (int i = 0; i < temp; i++)
			for (int i = 0; i < 3; i++)
			{
				ipFile >> x;
				if (x != -1)
				{
					switch (i)
					{
					case 0:
						mountRovers->enqueue(x);
						break;
					case 1:
						polarRovers->enqueue(y);
						break;
					case 2:
						emergencyRovers->enqueue(z);
						break;
					}
				}
			}
	}
}

int UI::getAutoP()
{
	int autoP;
	ipFile >> autoP;
	return autoP;
}

int UI::getNumofEvents()
{
	int temp;
	ipFile >> temp;
	return temp;
}

Queue<int>* UI::getEvent()
{
	eventData = new Queue<int>;
	int temp;
	//Getting the event type
	char eventType, Mtype;
	ipFile >> eventType;
	setEtype(eventType);

	if (eventType == 'F')
	{
		ipFile >> Mtype;		//Getting type of the mission to be formulated
		setMtype(Mtype);
		for (int i = 0; i < 5; i++)
		{
			ipFile >> temp;
			eventData->enqueue(temp);
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			ipFile >> temp;
			eventData->enqueue(temp);
		}
	}

	return eventData;
}

UI::~UI()
{

}

Queue<int>* UI::getEmRovers()
{
	return emergencyRovers;
}

Queue<int>* UI::getPolarRovers()
{
	return polarRovers;
}

Queue<int>* UI::getMountRovers()
{
	return mountRovers;
}

void UI::setEtype(char E)
{
	switch (E)
	{
	case 'F':
		ET = Formulation;
		break;
	case 'X':
		ET = Cancel;
		break;
	case 'P':
		ET = Promote;
		break;
	}
}

EventType UI::getET()
{
	return ET;
}

void UI::setMtype(char M)
{
	switch (M)
	{
	case 'E':
		MT = Emergency;
		break;
	case 'M':
		MT = Mountainous;
		break;
	case 'P':
		MT = Polar;
		break;
		
	}
}

MissionType UI::getMT()
{
	return MT;
}

/*
Queue<int>* UI::getEventData()
{
	return eventData;
}
*/