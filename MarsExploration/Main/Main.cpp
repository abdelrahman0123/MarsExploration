#include <iostream>
using namespace std;
#include "MarsStation/MarsStation.h"

int main()
{
	MarsStation* MStation = new MarsStation();
	string Input;
	cout << "\t\t\t\t\t\tTestCase:\n\t\t\t\t\t\t   ";
	cin >> Input;
	MStation->ReadInput(Input);
	MStation->Simulate();
	MStation->PrintOutput();
	delete MStation;
}