#define ISINGSIZE 30 //must be a multiple of 3

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
		
		int Probability[2];
		
		double Energy;
		double Temp;
		double One_Over_Temp;
		int Anti_or_Ferro;

		int Magnetism_Lattice_One;
		int Magnetism_Lattice_Two;
		int Magnetism_Lattice_Three;

		float Generate_Random_Number();
		
	public:
		System();
		void Choose_Particle();		
		void Peturb_Particle();
	
		double Return_Local_Energy();
		void Find_Total_Energy();
		void Update_Energy(double Energy_Difference);
		double Return_Energy();
		
		void Set_Temp(double Temperature);
		double Return_Temp();

		void Get_Probability();

		void Update_Probability(int Spin_Initial, int Spin_Final);	

		int Return_Probability_One();
		int Return_Probability_Zero();
		int Return_Probability_Minus_One();

		int Set_Up_Magnetism_One();
		int Set_Up_Magnetism_Two();
		
		int Get_Lattice();

		void Update_Magnetism_One(int Magnetism_Change);
		void Update_Magnetism_Two(int Magnetism_Change);
		
		int Return_Magnetism_One();
		int Return_Magnetism_Two();
		
		void Set_A_or_F(int A_or_F);

};



#endif