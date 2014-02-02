#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include "System.h"
#include <stdlib.h>
#include "Particle.h"

using namespace std;

int main (void)
{

	double Set_Heating_or_Cooling = 1; //heating = 1, cooling = -1
	double Set_Initial_Temp = 0.01;
	double Set_Final_Temp = 10;
	double Set_Interval = 0.01;
	int Number_Runs = 100*ISINGSIZE*ISINGSIZE;
	int Thermalisor = 100*ISINGSIZE*ISINGSIZE;

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

	int No_Particles_Lattice_One = Square_Lattice.Set_Up_Magnetism_One();
	int No_Particles_Lattice_Two = Square_Lattice.Set_Up_Magnetism_Two();

	if(Set_Heating_or_Cooling==1)
	{			 
		double Entropy=0;

		for(double Temperature=Set_Initial_Temp; Temperature<Set_Final_Temp; Temperature=Temperature+Set_Interval)
		{
			Square_Lattice.Set_Temp(Temperature);
			double Magnetism_One_Cumulant = 0;
			double Magnetism_One_Pow_Four_Cumulant=0;
			double Magnetism_One_Pow_Two_Cumulant=0;
			double Magnetism_Two_Cumulant = 0;
			double Magnetism_Two_Pow_Four_Cumulant=0;
			double Magnetism_Two_Pow_Two_Cumulant=0;
			double Energy_Cumulant=0;
			double Energy_Pow_Two_Cumulant=0;
			double Prob1_Cumulant=0;
			double Prob0_Cumulant=0;
			double Prob_neg1_Cumulant=0;
			double Magnetism_Pow_Two_One_Cumulant=0;
			double Magnetism_Pow_Two_Two_Cumulant = 0;

			for(int i=0; i<Thermalisor; i++)
			{
				Square_Lattice.Choose_Particle();
				Square_Lattice.Peturb_Particle();
			}


			for(int i=0; i<Number_Runs; i++)
			{
				Square_Lattice.Choose_Particle();
				Square_Lattice.Peturb_Particle();
				
				Energy_Pow_Two_Cumulant = Energy_Pow_Two_Cumulant + pow(Square_Lattice.Return_Energy(),2);
				Energy_Cumulant = Energy_Cumulant + Square_Lattice.Return_Energy();

				Prob1_Cumulant = Prob1_Cumulant + (double)(Square_Lattice.Return_Probability_One())/(double)(ISINGSIZE*ISINGSIZE);
				Prob0_Cumulant = Prob0_Cumulant + (double)(Square_Lattice.Return_Probability_Zero())/(double)(ISINGSIZE*ISINGSIZE);
				Prob_neg1_Cumulant = Prob_neg1_Cumulant + (double)(Square_Lattice.Return_Probability_Minus_One())/(double)(ISINGSIZE*ISINGSIZE);

				Magnetism_One_Cumulant = Magnetism_One_Cumulant + (double)(Square_Lattice.Return_Magnetism_One())/(double)No_Particles_Lattice_One;
				Magnetism_Two_Cumulant = Magnetism_Two_Cumulant + (double)(Square_Lattice.Return_Magnetism_Two())/(double)No_Particles_Lattice_Two;
			
				Magnetism_Pow_Two_One_Cumulant = Magnetism_Pow_Two_One_Cumulant + (double)(Square_Lattice.Return_Magnetism_One()*Square_Lattice.Return_Magnetism_One())/((double)No_Particles_Lattice_One*No_Particles_Lattice_One);
				Magnetism_Pow_Two_Two_Cumulant = Magnetism_Pow_Two_Two_Cumulant + (double)(Square_Lattice.Return_Magnetism_Two()*Square_Lattice.Return_Magnetism_Two())/((double)No_Particles_Lattice_Two*No_Particles_Lattice_Two);
			}


			double Energy_Pow_Two = Energy_Pow_Two_Cumulant/(double)Number_Runs;
			double Energy = Energy_Cumulant/(double)Number_Runs;

			double Heat_Capacity = ((Energy_Pow_Two)-pow(Energy,2))/(Temperature*Temperature);
			double Heat_Capacity_Over_Temp = Heat_Capacity/(double)Temperature;

			double Prob1 = Prob1_Cumulant/(double)Number_Runs;
			double Prob0 = Prob0_Cumulant/(double)Number_Runs;
			double Prob_neg1 = Prob_neg1_Cumulant/(double)Number_Runs;

			double Magnetism_One = Magnetism_One_Cumulant/(double)Number_Runs;
			double Magnetism_Two = Magnetism_Two_Cumulant/(double)Number_Runs;

			double Magnetism_Pow_Two_One = Magnetism_Pow_Two_One_Cumulant/(double)Number_Runs;
			double Magnetism_Pow_Two_Two = Magnetism_Pow_Two_Two_Cumulant/(double)Number_Runs;

			double Susceptibility_One = (Magnetism_Pow_Two_One - Magnetism_One*Magnetism_One)/Temperature;
			double Susceptibility_Two = (Magnetism_Pow_Two_Two - Magnetism_Two*Magnetism_Two)/Temperature;

			Output1 << Temperature << "\t" << Magnetism_One << "\t" << Magnetism_Two << "\t" << Susceptibility_One << "\t" << Susceptibility_Two << "\t" << Energy << "\t"<< Heat_Capacity << "\t"<<  Heat_Capacity_Over_Temp << "\t" << Entropy/(double)(ISINGSIZE*ISINGSIZE) << "\t" << Prob1 << "\t" << Prob0 << "\t" << Prob_neg1 << endl;

			Entropy = Entropy + (Heat_Capacity_Over_Temp*Set_Interval);
		}

		cout << "Entropy is" << "\t" << Entropy/(double)(ISINGSIZE*ISINGSIZE) << endl;
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
				Square_Lattice.Choose_Particle();
				Square_Lattice.Peturb_Particle();
				
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


	system("pause");
	return 0;

}