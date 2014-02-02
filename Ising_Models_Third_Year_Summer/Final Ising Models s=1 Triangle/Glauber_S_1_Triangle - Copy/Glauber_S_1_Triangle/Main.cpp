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
	double Set_Initial_Temp = 0.001;
	double Set_Final_Temp = 10;
	double Set_Interval = 0.001;
	int Set_Anti_or_Ferro = 1; //anti = 1, ferro = 1
	int Number_Runs = 1000*ISINGSIZE*ISINGSIZE;
	int Thermalisor = 1000*ISINGSIZE*ISINGSIZE;
	double Diviser = 1/(double)(ISINGSIZE*ISINGSIZE);
	srand(time(NULL));

	ofstream Output_Cool("OutputMagnetisation_Cool.txt");

	if (!Output_Cool.is_open())
	{
		cout << "Error: output file 1 cannot be opened." << endl;
		system("pause");
		return 1;
	}
	else
	{
		cout << "Output 1 file opened successfully." << endl;
	}

	ofstream Output_Heat("OutputMagnetisation_Heat.txt");

	if (!Output_Heat.is_open())
	{
		cout << "Error: output file 2 cannot be opened." << endl;
		system("pause");
		return 1;
	}
	else
	{
		cout << "Output 2 file opened successfully." << endl;
	}

	System Triangle_Lattice;

	int No_Particles_Lattice_One = Triangle_Lattice.Set_Up_Magnetism_One();
	int No_Particles_Lattice_Two =Triangle_Lattice.Set_Up_Magnetism_Two();
	int No_Particles_Lattice_Three =Triangle_Lattice.Set_Up_Magnetism_Three();

			 
		double Entropy=0;
		Triangle_Lattice.Set_Temp(10);
		
		for(int i=0; i<10000*ISINGSIZE*ISINGSIZE; i++)
			{
				Triangle_Lattice.Choose_Particle();
				Triangle_Lattice.Peturb_Particle();
			}

		for(double Temperature=Set_Final_Temp; Temperature>Set_Initial_Temp; Temperature=Temperature-Set_Interval)
		{
			Triangle_Lattice.Set_Temp(Temperature);
			double Magnetism_One_Cumulant = 0;
			double Magnetism_One_Pow_Four_Cumulant=0;
			double Magnetism_One_Pow_Two_Cumulant=0;
			double Magnetism_Two_Cumulant = 0;
			double Magnetism_Two_Pow_Four_Cumulant=0;
			double Magnetism_Two_Pow_Two_Cumulant=0;
			double Magnetism_Three_Cumulant = 0;
			double Magnetism_Three_Pow_Four_Cumulant=0;
			double Magnetism_Three_Pow_Two_Cumulant=0;
			double Energy_Cumulant=0;
			double Energy_Pow_Two_Cumulant=0;
			double Prob1_Cumulant=0;
			double Prob0_Cumulant=0;
			double Prob_neg1_Cumulant=0;
			double Magnetism_Pow_Two_One_Cumulant=0;
			double Magnetism_Pow_Two_Two_Cumulant = 0;
			double Magnetism_Pow_Two_Three_Cumulant = 0;

			for(int i=0; i<Thermalisor; i++)
			{
				Triangle_Lattice.Choose_Particle();
				Triangle_Lattice.Peturb_Particle();
			}

			for(int i=0; i<Number_Runs; i++)
			{
				Triangle_Lattice.Choose_Particle();
				Triangle_Lattice.Peturb_Particle();
				
				Energy_Pow_Two_Cumulant = Energy_Pow_Two_Cumulant + Triangle_Lattice.Return_Energy()*Triangle_Lattice.Return_Energy();
				Energy_Cumulant = Energy_Cumulant + Triangle_Lattice.Return_Energy();

				Prob1_Cumulant = Prob1_Cumulant + (double)(Triangle_Lattice.Return_Probability_One())*Diviser;
				Prob0_Cumulant = Prob0_Cumulant + (double)(Triangle_Lattice.Return_Probability_Zero())*Diviser;
				Prob_neg1_Cumulant = Prob_neg1_Cumulant + (double)(Triangle_Lattice.Return_Probability_Minus_One())*Diviser;

				Magnetism_One_Cumulant = Magnetism_One_Cumulant + (double)(Triangle_Lattice.Return_Magnetism_One())/(double)No_Particles_Lattice_One;
				Magnetism_Two_Cumulant = Magnetism_Two_Cumulant + (double)(Triangle_Lattice.Return_Magnetism_Two())/(double)No_Particles_Lattice_Two;
				Magnetism_Three_Cumulant = Magnetism_Three_Cumulant + (double)(Triangle_Lattice.Return_Magnetism_Three())/(double)No_Particles_Lattice_Three;
			
				Magnetism_Pow_Two_One_Cumulant = Magnetism_Pow_Two_One_Cumulant + (double)(Triangle_Lattice.Return_Magnetism_One()*Triangle_Lattice.Return_Magnetism_One())/((double)No_Particles_Lattice_One*No_Particles_Lattice_One);
				Magnetism_Pow_Two_Two_Cumulant = Magnetism_Pow_Two_Two_Cumulant + (double)(Triangle_Lattice.Return_Magnetism_Two()*Triangle_Lattice.Return_Magnetism_Two())/((double)No_Particles_Lattice_Two*No_Particles_Lattice_Two);
				Magnetism_Pow_Two_Three_Cumulant = Magnetism_Pow_Two_Three_Cumulant + (double)(Triangle_Lattice.Return_Magnetism_Three()*Triangle_Lattice.Return_Magnetism_Three())/((double)No_Particles_Lattice_Three*No_Particles_Lattice_Three);
				
			}


			double Energy_Pow_Two = Energy_Pow_Two_Cumulant/(double)Number_Runs;
			double Energy = Energy_Cumulant/(double)Number_Runs;

			double Heat_Capacity = ((Energy_Pow_Two)-pow(Energy,2))/(Temperature*Temperature);
			double Heat_Capacity_Over_Temp = Heat_Capacity/(double)Temperature;

			double Prob1 = Prob1_Cumulant/(double)Number_Runs;
			double Prob0 = Prob_neg1_Cumulant/(double)Number_Runs;
			double Prob_neg1 = Prob0_Cumulant/(double)Number_Runs;

			double Magnetism_One = Magnetism_One_Cumulant/(double)Number_Runs;
			double Magnetism_Two = Magnetism_Two_Cumulant/(double)Number_Runs;
			double Magnetism_Three = Magnetism_Three_Cumulant/(double)Number_Runs;

			double Magnetism_Pow_Two_One = Magnetism_Pow_Two_One_Cumulant/(double)Number_Runs;
			double Magnetism_Pow_Two_Two = Magnetism_Pow_Two_Two_Cumulant/(double)Number_Runs;
			double Magnetism_Pow_Two_Three = Magnetism_Pow_Two_Three_Cumulant/(double)Number_Runs;

			double Susceptibility_One = (Magnetism_Pow_Two_One - Magnetism_One*Magnetism_One)/Temperature;
			double Susceptibility_Two = (Magnetism_Pow_Two_Two - Magnetism_Two*Magnetism_Two)/Temperature;
			double Susceptibility_Three = (Magnetism_Pow_Two_Three - Magnetism_Three*Magnetism_Three)/Temperature;

			Output_Cool << Temperature << "\t" << Magnetism_One << "\t" << Magnetism_Two << "\t" << Magnetism_Three << "\t" << Susceptibility_One << "\t" << Susceptibility_Two << "\t" << Susceptibility_Three << "\t" << Energy << "\t"<< Heat_Capacity << "\t"<<  Heat_Capacity_Over_Temp << "\t" << 1.0986-(Entropy*Diviser) << "\t" << Prob1 << "\t" << Prob0 << "\t" << Prob_neg1 << endl;

			Entropy = Entropy + (Heat_Capacity_Over_Temp*Set_Interval);
		}
	
	system("pause");
	return 0;

}