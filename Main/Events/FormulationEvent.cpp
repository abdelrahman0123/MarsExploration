#include "FormulationEvent.h"

FormulationEvent::FormulationEvent(MissionType Type, int day, int ID) : Event(day, ID), MType(Type)
{
}

void FormulationEvent::Execute()
{
	
}
