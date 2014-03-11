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

	double Set_Initial_Temp = 0.05;
	double Set_Final_Temp = 20;
	double Set_Interval = 0.01;
	int Number_Runs = 1000;
	int Thermalisor = 1000;
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
	
	double Entropy=0;
	double Lattice_Diviser = 1/(double)(ISINGSIZE*ISINGSIZE);
	double Runs_Diviser = 1/(double)Number_Runs;

	
	for(double Temperature=Set_Initial_Temp; Temperature<Set_Final_Temp; Temperature=Temperature+Set_Interval)
	{
		Square_Lattice.Set_Temp(Temperature);
		/*double Magnetism_One_Cumulant = 0;
		double Magnetism_One_Pow_Four_Cumulant=0;
		double Magnetism_One_Pow_Two_Cumulant=0;
		double Magnetism_Two_Cumulant=0;
		double Magnetism_Two_Pow_Four_Cumulant=0;
		double Magnetism_Two_Pow_Two_Cumulant=0;*/
		double Energy_Cumulant=0;
		double Energy_Pow_Two_Cumulant=0;
		/*double Prob3_Cumulant=0;
		double Prob2_Cumulant=0;
		double Prob1_Cumulant=0;
		double Prob0_Cumulant=0;
		double Prob_neg1_Cumulant=0;
		double Prob_neg2_Cumulant=0;
		double Prob_neg3_Cumulant=0;
		double Magnetism_Pow_Two_One_Cumulant=0;
		double Magnetism_Pow_Two_Two_Cumulant=0;*/

		for(int i=0; i<Thermalisor; i++)
		{
			Square_Lattice.Peturb_Lattice_One();
			Square_Lattice.Peturb_Lattice_Two();
		}


		for(int i=0; i<Number_Runs; i++)
		{
			Square_Lattice.Peturb_Lattice_One();
			Square_Lattice.Peturb_Lattice_Two();

			Energy_Pow_Two_Cumulant = Energy_Pow_Two_Cumulant + (Square_Lattice.Return_Energy()*Square_Lattice.Return_Energy());
			Energy_Cumulant = Energy_Cumulant + Square_Lattice.Return_Energy();


			/*Prob1_Cumulant = Prob1_Cumulant + (double)(Square_Lattice.Return_Probability_One())*Lattice_Diviser;
			Prob0_Cumulant = Prob0_Cumulant + (double)(Square_Lattice.Return_Probability_Zero())*Lattice_Diviser;
			Prob_neg1_Cumulant = Prob_neg1_Cumulant + (double)(Square_Lattice.Return_Probability_Minus_One())*Lattice_Diviser;


			Magnetism_One_Cumulant = Magnetism_One_Cumulant + (double)(Square_Lattice.Return_Magnetism_One())*0.5*Lattice_Diviser;
			Magnetism_Two_Cumulant = Magnetism_Two_Cumulant + (double)(Square_Lattice.Return_Magnetism_Two())*0.5*Lattice_Diviser;

			Magnetism_Pow_Two_One_Cumulant = Magnetism_Pow_Two_One_Cumulant + (double)(Square_Lattice.Return_Magnetism_One()*Square_Lattice.Return_Magnetism_One())*0.5*Lattice_Diviser;
			Magnetism_Pow_Two_Two_Cumulant = Magnetism_Pow_Two_Two_Cumulant + (double)(Square_Lattice.Return_Magnetism_Two()*Square_Lattice.Return_Magnetism_Two())*0.5*Lattice_Diviser;*/
		}


		double Energy_Pow_Two = Energy_Pow_Two_Cumulant/(double)Number_Runs;
		double Energy = Energy_Cumulant/(double)Number_Runs;

		double Heat_Capacity = ((Energy_Pow_Two)-(Energy*Energy))/(Temperature*Temperature);
		double Heat_Capacity_Over_Temp = Heat_Capacity/Temperature;

		/*double Prob3 = Prob3_Cumulant*Runs_Diviser;
		double Prob2 = Prob2_Cumulant*Runs_Diviser;
		double Prob1 = Prob1_Cumulant*Runs_Diviser;
		double Prob0 = Prob0_Cumulant*Runs_Diviser;
		double Prob_neg1 = Prob_neg1_Cumulant*Runs_Diviser;
		double Prob_neg2 = Prob_neg2_Cumulant*Runs_Diviser;
		double Prob_neg3 = Prob_neg3_Cumulant*Runs_Diviser;

		double Magnetism_One = Magnetism_One_Cumulant*Runs_Diviser;
		double Magnetism_Two = Magnetism_Two_Cumulant*Runs_Diviser;

		double Magnetism_Pow_Two_One = Magnetism_Pow_Two_One_Cumulant*Runs_Diviser;
		double Magnetism_Pow_Two_Two = Magnetism_Pow_Two_Two_Cumulant*Runs_Diviser;

		double Susceptibility_One = (Magnetism_Pow_Two_One - Magnetism_One*Magnetism_One)/Temperature;
		double Susceptibility_Two = (Magnetism_Pow_Two_Two - Magnetism_Two*Magnetism_Two)/Temperature;*/

		Output1 << Temperature << "\t" << 1/(Temperature*Temperature) << "\t" << Entropy/(double)(ISINGSIZE*ISINGSIZE) << endl;
		//Output1 << Temperature << "\t" << 1/(Temperature*Temperature) << "\t" << Magnetism_One << "\t" << Magnetism_Two << "\t" << Susceptibility_One << "\t" << Susceptibility_Two << "\t" << Energy << "\t"<< Heat_Capacity << "\t"<<  Heat_Capacity_Over_Temp << "\t" << Entropy/(double)(ISINGSIZE*ISINGSIZE) << "\t" << Prob3 << "\t" << Prob2 << "\t" << Prob1 << "\t" << Prob0 << "\t" << Prob_neg1 << "\t" << Prob_neg2 << "\t" << Prob_neg3  << endl;

		Entropy = Entropy + (Heat_Capacity_Over_Temp*Set_Interval);		
	}

	system("pause");
	return 0;

}

