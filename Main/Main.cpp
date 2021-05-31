#include <iostream>
using namespace std;
#include "MarsStation/MarsStation.h"

int main()
{
	MarsStation* MStation = new MarsStation();
	MStation->ReadInput();
	MStation->Simulate();
	MStation->PrintOutput();
	delete MStation;
}