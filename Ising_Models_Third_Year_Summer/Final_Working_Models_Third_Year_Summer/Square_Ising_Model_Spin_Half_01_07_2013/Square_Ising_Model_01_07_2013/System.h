#define ISINGSIZE 15

#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include "Particle.h"

class System
{
	private:
		Particle Particles[ISINGSIZE][ISINGSIZE];
		int Current_Column;
		int Current_Row;
		int Up_Row;
		int Down_Row;
		int Left_Column;
		int Right_Column;
		void Find_Neighbours();

		double Energy;
		double Magnetism;
		double Temp;

	public:
		System();
		void Peturb_Lattice_One();
		void Peturb_Lattice_Two();
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
};





#endif