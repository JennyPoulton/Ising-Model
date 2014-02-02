#include <cmath>
#include <stdlib.h>
#include "Particle.h"
#include "System.h"
using namespace std;

System::System()
{
	
	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			Particles[i][j].Set_Spin(1);
		}
	}
	
	
	Find_Total_Energy();
	Find_Magnetism();

	Current_Column=0;
	Current_Row=0;

	Set_Temp(0);

	return;
}

void System::Peturb_Lattice_One()
{
	for(int i=0; i<ISINGSIZE; i=i+3)
	{
		for(int j=0; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+3)
	{
		for(int j=1; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}

	for(int i=2; i<ISINGSIZE; i=i+3)
	{
		for(int j=2; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}


	Find_Total_Energy();
	Find_Magnetism();

	return;
}

void System::Peturb_Lattice_Two()
{
	for(int i=0; i<ISINGSIZE; i=i+3)
	{
		for(int j=1; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+3)
	{
		for(int j=2; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}

	for(int i=2; i<ISINGSIZE; i=i+3)
	{
		for(int j=0; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}

	Find_Total_Energy();
	Find_Magnetism();

	return;

}

void System::Peturb_Lattice_Three()
{
	for(int i=0; i<ISINGSIZE; i=i+3)
	{
		for(int j=2; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+3)
	{
		for(int j=0; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}

	for(int i=2; i<ISINGSIZE; i=i+3)
	{
		for(int j=1; j<ISINGSIZE; j=j+3)
		{
			Current_Row = i;
			Current_Column = j;
			Peturb_Particle();
		}
	}

	Find_Total_Energy();
	Find_Magnetism();

	return;

}

void System::Peturb_Particle()
{
	double Initial_Energy = Return_Local_Energy();
	Particles[Current_Row][Current_Column].Flip_Spin();
	double Final_Energy = Return_Local_Energy();

	double Energy_Change = Final_Energy-Initial_Energy;


	if(Energy_Change>0)
	{
		double Monte_Carlo = exp(-Energy_Change/Temp);

		if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
		{
			Particles[Current_Row][Current_Column].Flip_Spin();
			return;
		}
	}

	return;

}

void System::Find_Neighbours()
{
	Neighbour_One_Row = Current_Row+1;
	Neighbour_One_Column = Current_Column-1;

	Neighbour_Two_Row = Current_Row+1;
	Neighbour_Two_Column = Current_Column;

	Neighbour_Three_Row = Current_Row;
	Neighbour_Three_Column = Current_Column+1;

	Neighbour_Four_Row = Current_Row-1;
	Neighbour_Four_Column = Current_Column+1;

	Neighbour_Five_Row = Current_Row-1;
	Neighbour_Five_Column = Current_Column;

	Neighbour_Six_Row = Current_Row-1;
	Neighbour_Six_Column = Current_Column;
	

	if(Current_Row==0)
	{
		Neighbour_One_Row = ISINGSIZE-1;
		Neighbour_Two_Row = ISINGSIZE-1;
		
	}
	if(Current_Row==ISINGSIZE-1)
	{
		Neighbour_Four_Row = 0;
		Neighbour_Five_Row = 0;
	}

	if(Current_Column==0)
	{
		Neighbour_One_Column = ISINGSIZE-1;
		Neighbour_Five_Column = ISINGSIZE-1;
		Neighbour_Six_Column = ISINGSIZE-1;

	}

	if(Current_Column==ISINGSIZE-1)
	{
		Neighbour_Two_Column = 0;
		Neighbour_Three_Column = 0;
		Neighbour_Four_Column = 0;
	}

	return;
}

double System::Return_Local_Energy()
{
	Find_Neighbours();

	double Energy = (Particles[Current_Row][Current_Column].Return_Spin()*Particles[Neighbour_One_Column][Neighbour_One_Row].Return_Spin()
		+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Neighbour_Two_Column][Neighbour_Two_Row].Return_Spin()
		+	Particles[Current_Row][Current_Column].Return_Spin()*Particles[Neighbour_Three_Column][Neighbour_Three_Row].Return_Spin()
		+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Neighbour_Four_Column][Neighbour_Four_Row].Return_Spin()
		+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Neighbour_Five_Column][Neighbour_Five_Row].Return_Spin()
		+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Neighbour_Six_Column][Neighbour_Six_Row].Return_Spin())*Anti_or_Ferro;

	return Energy;
}

void System::Find_Total_Energy()
{
	double Energy_Placeholder=0;

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			
			Current_Row=i;
			Current_Column=j;

			Energy_Placeholder = Energy_Placeholder + Return_Local_Energy();
		}
	}

	Energy = Energy_Placeholder/(double)2;
	return;
}

double System::Return_Energy()
{
	return Energy;
}

void System::Find_Magnetism()
{
	double Magnetism_Placeholder=0;

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
		}
	}

	Magnetism = abs(Magnetism_Placeholder/((double)ISINGSIZE*(double)ISINGSIZE));
	return;
}

double System::Return_Magnetism()
{
	return Magnetism;
}

void System::Set_Temp(double Temperature)
{
	Temp = Temperature;
	return;
}

double System::Return_Temp()
{
	return Temp;
}

void System::Set_A_or_F(int A_or_F)
{
	Anti_or_Ferro = A_or_F;
	return;
}

