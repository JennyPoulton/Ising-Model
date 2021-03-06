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

		int Current_Column_One;
		int Current_Row_One;

		int Current_Column_Two;
		int Current_Row_Two;
		
		int Probability[SPINMODES];  

		double Energy;
		double Temp;
		int Magnetism[LATTICE_NO];
		
		float Generate_Random_Number();
		
	public:
		System();
		
		void Peturb_Lattice_One();
		void Peturb_Lattice_Two();

		void Choose_Neighbour();
		void Peturb_Particle();
	
		int Return_Local_Energy();
		void Find_Total_Energy();
		void Update_Energy(int Energy_Difference);
		double Return_Energy();
		
		void Set_Temp(double Temperature);
		double Return_Temp();

		void Get_Initial_Probability();
		void Update_Probability(int InitialSpinOne, int FinalSpinOne, int InitialSpinTwo, int FinalSpinTwo);

		int Return_Probability_One();
		int Return_Probability_Zero();
		int Return_Probability_Minus_One();

		void Set_Up_Magnetism();
		
		void Update_Magnetism(int Magnetism_Change_One, int Magnetism_Change_Two);
				
		int Return_Magnetism_One();
		int Return_Magnetism_Two();
		
};

#endif