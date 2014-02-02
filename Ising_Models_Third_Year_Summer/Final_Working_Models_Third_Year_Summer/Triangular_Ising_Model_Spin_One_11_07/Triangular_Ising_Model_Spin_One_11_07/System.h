#define ISINGSIZE 12 //must be a multiple of 3

#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include "Particle.h"

struct Probability
{
	double Prob1;
	double Prob0;
	double Prob_neg1;
};

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
		int Particle_Five_Row;
		int Particle_Six_Row;

		int Particle_One_Column;
		int Particle_Two_Column;
		int Particle_Three_Column;
		int Particle_Four_Column;
		int Particle_Five_Column;
		int Particle_Six_Column;
		
		void Find_Neighbours();

		double Energy;
		double Magnetism;
		double Temp;
		int Anti_or_Ferro;

	public:
		System();
		void Peturb_Lattice_One();
		void Peturb_Lattice_Two();
		void Peturb_Lattice_Three();
		void Peturb_Particle();
	
		double Return_Local_Energy();
		void Find_Total_Energy();
		void Update_Energy(double Energy_Difference);
		double Return_Energy();

		void Find_Magnetism();
		void Update_Magnetism();
		double Return_Magnetism();

		void Set_Temp(double Temperature);
		double Return_Temp();

		struct Probability Get_Probability();

		void Set_A_or_F(int A_or_F);

};

#endif