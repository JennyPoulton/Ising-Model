#define ISINGSIZE 30 //must be a multiple of 3
#define MAXSPIN 2

#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include "Particle.h"

class System
{
	private:
		Particle Lattice[ISINGSIZE][ISINGSIZE];
		Particle* Up[ISINGSIZE][ISINGSIZE];
		Particle* Down[ISINGSIZE][ISINGSIZE];
		Particle* Left[ISINGSIZE][ISINGSIZE];
		Particle* Right[ISINGSIZE][ISINGSIZE];

		int Current_Column;
		int Current_Row;
		
		int Probability[MAXSPIN+1];  

		double Energy;
		double Temp;
		double One_Over_Temp;
		int Anti_or_Ferro;
		int Number_of_Lattices;
		int Magnetism[2];
		
		float Generate_Random_Number();
		
	public:
		System();
		void Choose_Particle();		
		void Peturb_Particle();
	
		int Return_Local_Energy();
		void Find_Total_Energy();
		void Update_Energy(int Energy_Difference);
		int Return_Energy();
		
		void Set_Temp(double Temperature);
		double Return_Temp();

		void Get_Initial_Probability();
		void Update_Probability(int Spin_Initial, int Spin_Final);	

		int Return_Probability_One();
		int Return_Probability_Zero();
		int Return_Probability_Minus_One();

		void Set_Up_Magnetism();
		
		void Update_Magnetism(int Magnetism_Change);
				
		int Return_Magnetism_One();
		int Return_Magnetism_Two();
		
};

#endif