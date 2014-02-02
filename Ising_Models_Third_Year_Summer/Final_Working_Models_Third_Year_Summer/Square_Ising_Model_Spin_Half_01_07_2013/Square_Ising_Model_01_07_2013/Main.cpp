#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include "System.h"
#include "Particle.h"

using namespace std;


int main (void)
{

	srand(time(NULL));
	
	ofstream Output1("OutputMagnetisation.txt");
	
	if (!Output1.is_open())
	{
		cout << "Error: output file 1 cannot be opened." << endl;
		system("pause");
		return 1;
	}
	else
	{
		cout << "Output 1 file opened successfully." << endl;
	}

	System Square_Lattice;

	Output1 << Square_Lattice.Return_Temp() << "\t" << Square_Lattice.Return_Magnetism() << endl;

	for(double Temperature=0; Temperature<10; Temperature=Temperature+0.01)
	{
		Square_Lattice.Set_Temp(Temperature);
		double Tally = 0;
		for(int i=0; i<100; i++)
		{
            Square_Lattice.Peturb_Lattice_One();
			Square_Lattice.Peturb_Lattice_Two();
			Tally = Tally + Square_Lattice.Return_Magnetism();

		}
		
		Output1 << Temperature << "\t" << Tally/(double)100 << endl;
	}

	system("pause");
	return 0;
}