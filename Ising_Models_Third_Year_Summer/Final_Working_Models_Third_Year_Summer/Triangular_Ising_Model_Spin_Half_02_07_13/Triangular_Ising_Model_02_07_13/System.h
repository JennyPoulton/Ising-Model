#define ISINGSIZE 12 //must be a multiple of 3

#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include "Particle.h"

class System
{
	private:
		Particle Particles[ISINGSIZE][ISINGSIZE];
		int Current_Column;
		int Current_Row;
		
		int Neighbour_One_Row;
		int Neighbour_Two_Row;
		int Neighbour_Three_Row;
		int Neighbour_Four_Row;
		int Neighbour_Five_Row;
		int Neighbour_Six_Row;

		int Neighbour_One_Column;
		int Neighbour_Two_Column;
		int Neighbour_Three_Column;
		int Neighbour_Four_Column;
		int Neighbour_Five_Column;
		int Neighbour_Six_Column;
		
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

};

#endif