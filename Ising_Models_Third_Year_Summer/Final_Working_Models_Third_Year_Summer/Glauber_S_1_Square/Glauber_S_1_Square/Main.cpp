#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include <stdlib.h>
#include<cmath>
#include "System.h"
#include "Particle.h"

using namespace std;

int main (void)
{

	double Set_Heating_or_Cooling = 1; //heating = 1, cooling = -1
	double Set_Initial_Temp = 0.2;
	double Set_Final_Temp = 10;
	double Set_Interval = 0.001;
	int Number_Runs = 1000;
	int Thermalisor = 100;

	double Number_Particles_Divider = 1/(double)(ISINGSIZE*ISINGSIZE);

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


	if(Set_Heating_or_Cooling==1)
	{			 
		double Entropy=0;

		for(double Temperature=Set_Initial_Temp; Temperature<Set_Final_Temp; Temperature=Temperature+Set_Interval)
		{
			Square_Lattice.Set_Temp(Temperature);
			double Magnetism_Cumulant = 0;
			double Magnetism_Pow_Four_Cumulant=0;
			double Magnetism_Pow_Two_Cumulant=0;
			double Energy_Cumulant=0;
			double Energy_Pow_Two_Cumulant=0;
			double Prob1_Cumulant=0;
			double Prob0_Cumulant=0;
			double Prob_neg1_Cumulant=0;


			for(int i=0; i<Thermalisor; i++)
			{
				Square_Lattice.Peturb_Lattice_One();
				Square_Lattice.Peturb_Lattice_Two();
			}
			for(int i=0; i<Number_Runs; i++)
			{
				Square_Lattice.Peturb_Lattice_One();
				Square_Lattice.Peturb_Lattice_Two();
				
				Energy_Pow_Two_Cumulant = Energy_Pow_Two_Cumulant + Square_Lattice.Return_Energy()*Square_Lattice.Return_Energy();
				Energy_Cumulant = Energy_Cumulant + Square_Lattice.Return_Energy();

				Prob1_Cumulant = Prob1_Cumulant + (double)(Square_Lattice.Return_Probability_One())*Number_Particles_Divider;
				Prob0_Cumulant = Prob0_Cumulant + (double)(Square_Lattice.Return_Probability_Zero())*Number_Particles_Divider;
				Prob_neg1_Cumulant = Prob_neg1_Cumulant + (double)(Square_Lattice.Return_Probability_Minus_One())*Number_Particles_Divider;

			}

			double Energy_Pow_Two = Energy_Pow_Two_Cumulant/(double)Number_Runs;
			double Energy = Energy_Cumulant/(double)Number_Runs;

			double Heat_Capacity = ((Energy_Pow_Two)-Energy*Energy)/(Temperature*Temperature);
			double Heat_Capacity_Over_Temp = Heat_Capacity/Temperature;

			double Prob1 = Prob1_Cumulant/(double)Number_Runs;
			double Prob0 = Prob_neg1_Cumulant/(double)Number_Runs;
			double Prob_neg1 = Prob0_Cumulant/(double)Number_Runs;

			Output1 << Temperature << "\t" << Energy << "\t"<< Heat_Capacity << "\t"<<  Heat_Capacity_Over_Temp << "\t" << Entropy*Number_Particles_Divider << "\t" << Prob1 << "\t" << Prob0 << "\t" << Prob_neg1 << endl;

			Entropy = Entropy + (double)(Heat_Capacity_Over_Temp*Set_Interval);
		}

		cout << "Entropy is" << "\t" << Entropy*Number_Particles_Divider << endl;
	}
	else
	{
		double Entropy=0;

		for(double Temperature=Set_Initial_Temp; Temperature>Set_Final_Temp; Temperature=Temperature-Set_Interval)
		{
			Square_Lattice.Set_Temp(Temperature);
			double Magnetism_Cumulant = 0;
			double Magnetism_Pow_Four_Cumulant=0;
			double Magnetism_Pow_Two_Cumulant=0;
			double Energy_Cumulant=0;
			double Energy_Pow_Two_Cumulant=0;
			double Prob1_Cumulant=0;
			double Prob0_Cumulant=0;
			double Prob_neg1_Cumulant=0;


			for(int i=0; i<Number_Runs; i++)
			{
				Square_Lattice.Peturb_Lattice_One();
				Square_Lattice.Peturb_Lattice_Two();
				
				Energy_Pow_Two_Cumulant = Energy_Pow_Two_Cumulant + pow(Square_Lattice.Return_Energy(),2);
				Energy_Cumulant = Energy_Cumulant + Square_Lattice.Return_Energy();

				Prob1_Cumulant = Prob1_Cumulant + (double)(Square_Lattice.Return_Probability_One())/(double)(ISINGSIZE*ISINGSIZE);
				Prob0_Cumulant = Prob0_Cumulant + (double)(Square_Lattice.Return_Probability_Zero())/(double)(ISINGSIZE*ISINGSIZE);
				Prob_neg1_Cumulant = Prob_neg1_Cumulant + (double)(Square_Lattice.Return_Probability_Minus_One())/(double)(ISINGSIZE*ISINGSIZE);

			}

			double Energy_Pow_Two = Energy_Pow_Two_Cumulant/(double)Number_Runs;
			double Energy = Energy_Cumulant/(double)Number_Runs;

			double Heat_Capacity = ((Energy_Pow_Two)-pow(Energy,2))/(Temperature*Temperature);
			double Heat_Capacity_Over_Temp = Heat_Capacity/(double)Number_Runs*Temperature;

			double Prob1 = Prob1_Cumulant/(double)Number_Runs;
			double Prob0 = Prob_neg1_Cumulant/(double)Number_Runs;
			double Prob_neg1 = Prob0_Cumulant/(double)Number_Runs;

			Output1 << Temperature << "\t" << Energy << "\t"<< Heat_Capacity << "\t"<<  Heat_Capacity_Over_Temp << "\t" << Entropy << "\t" << Prob1 << "\t" << Prob0 << "\t" << Prob_neg1 << endl;

			Entropy = Entropy + (Heat_Capacity_Over_Temp*Set_Interval);
		}

		cout << "Entropy is" << "\t" << Entropy << endl;		
	}


	return 0;

}