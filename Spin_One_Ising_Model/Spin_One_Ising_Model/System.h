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
		
		int Particle_One_Row;
		int Particle_Two_Row;
		int Particle_Three_Row;
		int Particle_Four_Row;
		int Particle_Five_Row;
		int Particle_Six_Row;
		
		int Particle_One_Column;
		int Particle_Two_Column;
		int Particle_Three_Column;
		int Particle_Four_Column;	
		int Particle_Five_Column;
		int Particle_Six_Column;
		
		void Find_Neighbours();

		int Current_Column2;
		int Current_Row2;
		
		int Particle_One_Row2;
		int Particle_Two_Row2;
		int Particle_Three_Row2;
		int Particle_Four_Row2;
		int Particle_Five_Row2;
		int Particle_Six_Row2;
		
		int Particle_One_Column2;
		int Particle_Two_Column2;
		int Particle_Three_Column2;
		int Particle_Four_Column2;
		int Particle_Five_Column2;
		int Particle_Six_Column2;
		
		void Find_Neighbours2();

		int Probability_One;
		int Probability_Zero;
		int Probability_Minus_One;

		double Energy;
		double Temp;
		int Anti_or_Ferro;

		int Magnetism_Lattice_One;
		int Magnetism_Lattice_Two;
		int Magnetism_Lattice_Three;

		float Generate_Random_Number();
		
	public:
		System();
		void Choose_Particle();
		void Choose_Particle2();

		void Peturb_Particle();
	
		double Return_Local_Energy();
		void Find_Total_Energy();
		void Update_Energy(double Energy_Difference);
		double Return_Energy();
		
		void Set_Temp(double Temperature);
		double Return_Temp();

		void Get_Probability();

		void Update_Probability_One(int delta_Prob);
		void Update_Probability_Zero(int delta_Prob);
		void Update_Probability_Minus_One(int delta_Prob);

		int Return_Probability_One();
		int Return_Probability_Zero();
		int Return_Probability_Minus_One();

		int Set_Up_Magnetism_One();
		int Set_Up_Magnetism_Two();
		int Set_Up_Magnetism_Three();

		int Get_Lattice();

		void Update_Magnetism_One(int Magnetism_Change);
		void Update_Magnetism_Two(int Magnetism_Change);
		void Update_Magnetism_Three(int Magnetism_Change);

		int Return_Magnetism_One();
		int Return_Magnetism_Two();
		int Return_Magnetism_Three();

		void Set_A_or_F(int A_or_F);

};



#endif