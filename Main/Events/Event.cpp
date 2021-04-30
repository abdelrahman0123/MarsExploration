#include "Event.h"

Event::Event(int day, int ID) : EventDay(day), MissionID(ID)
{
}

void Event::setEventDay(int day)
{
	EventDay = day;
}

int Event::getEventDay()
{
	return EventDay;
}

void Event::setMissionID(int ID)
{
	MissionID = ID;
}

int Event::getMissionID()
{
	return MissionID;
}
