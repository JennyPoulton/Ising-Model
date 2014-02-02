#define ISINGSIZE 30 //must be a multiple of 3 and 2

#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include "Particle.h"

class System
{
	private:
		Particle Particles[ISINGSIZE][ISINGSIZE];
		int Current_Column;
		int Current_Row;
		
		int Particle_One_Row;
		int Particle_Two_Row;
		int Particle_Three_Row;
		int Particle_Four_Row;
		
		
		int Particle_One_Column;
		int Particle_Two_Column;
		int Particle_Three_Column;
		int Particle_Four_Column;
		
		
		void Find_Neighbours();

		int Probability_One;
		int Probability_Zero;
		int Probability_Minus_One;

		int Magnetism_Lattice_One;
		int Magnetism_Lattice_Two;
		

		double Energy;
		double Magnetism;
		double Temp;
		int Anti_or_Ferro;

		float Generate_Random_Number();

		
	public:
		System();
		void Peturb_Lattice_One();
		void Peturb_Lattice_Two();
		
		
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
		

		int Get_Lattice();

		void Update_Magnetism_One(int Magnetism_Change);
		void Update_Magnetism_Two(int Magnetism_Change);
		

		int Return_Magnetism_One();
		int Return_Magnetism_Two();
		

		void Set_A_or_F(int A_or_F);

};

#endif