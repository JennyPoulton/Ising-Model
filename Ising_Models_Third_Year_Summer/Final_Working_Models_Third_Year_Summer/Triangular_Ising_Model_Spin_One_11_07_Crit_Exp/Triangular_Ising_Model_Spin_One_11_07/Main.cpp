#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include "System.h"
#include "Particle.h"


using namespace std;

int main (void)
{

	double Crit_Temp = 2.3;
	double Set_Heating_or_Cooling = 1; //heating = 1, cooling = -1
	double Set_Initial_Temp = 0.005;
	double Set_Final_Temp = Crit_Temp-0.5;
	double Set_Interval = 0.005;
	int Set_Anti_or_Ferro = -1; //anti = 1, ferro = -1
	int Number_Runs = 1000;

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

	System Triangle_Lattice;

	Triangle_Lattice.Set_A_or_F(Set_Anti_or_Ferro);

	if(Set_Heating_or_Cooling==1)
	{			 
		double Previous_Log_Magnetism = 0;
		double Previous_Log_Temps = 0;

		for(double Temperature=Set_Initial_Temp; Temperature<Set_Final_Temp; Temperature=Temperature+Set_Interval)
		{
			Triangle_Lattice.Set_Temp(Temperature);
			double Tally_M = 0;
				

			for(int i=0; i<Number_Runs; i++)
			{
				Triangle_Lattice.Peturb_Lattice_One();
				Triangle_Lattice.Peturb_Lattice_Two();
				Triangle_Lattice.Peturb_Lattice_Three();
				
				Tally_M = Tally_M + Triangle_Lattice.Return_Magnetism();		
			}

			double Magnetism = Tally_M/(double)Number_Runs;
			double Magnetism_Crit_Exp = log(fabs((double)(Temperature-Crit_Temp)/Crit_Temp));
			double Log_Magnetism = log(fabs(Magnetism));
			double Gradient = (Log_Magnetism - Previous_Log_Magnetism)/(Magnetism_Crit_Exp-Previous_Log_Temps);

			Previous_Log_Magnetism = Log_Magnetism;
			Previous_Log_Temps = Magnetism_Crit_Exp;
			
			Output1 << Log_Magnetism << "\t" << Magnetism_Crit_Exp << "\t" << Gradient << endl;

			}
	
	}
	else if(Set_Heating_or_Cooling==-1)
	{

		
		for(double Temperature=Set_Initial_Temp; Temperature<Set_Final_Temp; Temperature=Temperature-Set_Interval)
		{
			Triangle_Lattice.Set_Temp(Temperature);
			double Tally = 0;
			double Tally_Power_Four=0;
			double Tally_Power_Two=0;
			for(int i=0; i<Number_Runs; i++)
			{
				Triangle_Lattice.Peturb_Lattice_One();
				Triangle_Lattice.Peturb_Lattice_Two();
				Triangle_Lattice.Peturb_Lattice_Three();
				
				Tally = Tally + Triangle_Lattice.Return_Magnetism();
				
				Tally_Power_Four = Tally_Power_Four + pow(Triangle_Lattice.Return_Magnetism(),4);
				Tally_Power_Two = Tally_Power_Two + pow(Triangle_Lattice.Return_Magnetism(),2);

			}

			double Magnetism = Tally/(double)Number_Runs;
			double Binder_Cumulant = 1 - (Tally_Power_Four/(double)Number_Runs)/(3*pow((Tally_Power_Two/(double)Number_Runs),2));

			Output1 << Temperature << "\t" << Magnetism << "\t" << Binder_Cumulant << endl;

		}
	}
	system("pause");
	return 0;
}