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
	for(int i=0; i<ISINGSIZE; i=i+2)
	{
		for(int j=0; j<ISINGSIZE; j=j+2)
		{
			Current_Column = i;
			Current_Row = j;
			Peturb_Particle();
		}
	}
	
	for(int i=1; i<ISINGSIZE; i=i+2)
	{
		for(int j=1; j<ISINGSIZE; j=j+2)
		{
			Current_Column = i;
			Current_Row = j;
			Peturb_Particle();
		}
	}

	Find_Total_Energy();
	Find_Magnetism();
	
	return;
}

void System::Peturb_Lattice_Two()
{
	for(int i=1; i<ISINGSIZE; i=i+2)
	{
		for(int j=0; j<ISINGSIZE; j=j+2)
		{
			Current_Column = i;
			Current_Row = j;
			Peturb_Particle();
		}
	}
	
	for(int i=0; i<ISINGSIZE; i=i+2)
	{
		for(int j=1; j<ISINGSIZE; j=j+2)
		{
			Current_Column = i;
			Current_Row = j;
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
	Up_Row = Current_Row-1;
	Down_Row = Current_Row+1;

	Left_Column = Current_Column-1;
	Right_Column = Current_Column+1;

	if(Current_Row==0)
	{
		Up_Row = ISINGSIZE-1;
	}
	if(Current_Row==ISINGSIZE-1)
	{
		Down_Row = 0;
	}

	if(Current_Column==0)
	{
		Left_Column = ISINGSIZE-1;
	}

	if(Current_Column==ISINGSIZE-1)
	{
		Right_Column = 0;
	}

	return;
}

double System::Return_Local_Energy()
{
	Find_Neighbours();

	double Energy = -Particles[Current_Row][Current_Column].Return_Spin()*Particles[Up_Row][Current_Column].Return_Spin()
		-    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Down_Row][Current_Column].Return_Spin()
		-	Particles[Current_Row][Current_Column].Return_Spin()*Particles[Current_Row][Left_Column].Return_Spin()
		-    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Current_Row][Right_Column].Return_Spin();

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

