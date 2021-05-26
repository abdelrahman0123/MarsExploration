#include <iostream>
using namespace std;
#include "MarsStation/MarsStation.h"

int main()
{
	MarsStation MStation;
	MStation.ReadInput();
	MStation.Simulate();
	//MStation->GenerateOutputFile();
}