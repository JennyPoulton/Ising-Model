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
			if((i%2==1&&j%2==1)||(i%2==0&&j%2==0))
			{
				Particles[i][j].Set_Spin(1);
			}
			else
			{			
				Particles[i][j].Set_Spin(-1);
			}
		}
	}


	Find_Total_Energy();
	Get_Probability();

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
			Current_Column=i;
			Current_Row=j;
			Peturb_Particle();
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+2)
	{
		for(int j=1; j<ISINGSIZE; j=j+2)
		{
			Current_Column=i;
			Current_Row=j;
			Peturb_Particle();
		}
	}
	return;
}

void System::Peturb_Lattice_Two()
{
	for(int i=1; i<ISINGSIZE; i=i+2)
	{
		for(int j=0; j<ISINGSIZE; j=j+2)
		{
			Current_Column=i;
			Current_Row=j;
			Peturb_Particle();
		}
	}

	for(int i=0; i<ISINGSIZE; i=i+2)
	{
		for(int j=1; j<ISINGSIZE; j=j+2)
		{
			Current_Column=i;
			Current_Row=j;
			Peturb_Particle();
		}
	}
	return;
}

void System::Peturb_Particle()
{
	int i=Particles[Current_Row][Current_Column].Return_Spin();
	
	if(i==0)
	{
		if(rand()/(double)RAND_MAX>0.5)
		{
			double Initial_Energy = Return_Local_Energy();
			Particles[Current_Row][Current_Column].Set_Spin(1);
			double Final_Energy = Return_Local_Energy();

			double Energy_Change = Final_Energy-Initial_Energy;

			if(Energy_Change>0)
			{
				double Monte_Carlo = exp(-Energy_Change/Temp);

				if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
				{
					Particles[Current_Row][Current_Column].Set_Spin(0);
					return;
				}			
				
			}

			Update_Energy(Energy_Change);
			Update_Probability_One(1);
			Update_Probability_Zero(-1);
			return;
		}
		else
		{
			double Initial_Energy = Return_Local_Energy();
			Particles[Current_Row][Current_Column].Set_Spin(-1);
			double Final_Energy = Return_Local_Energy();

			double Energy_Change = Final_Energy-Initial_Energy;

			if(Energy_Change>0)
			{
				double Monte_Carlo = exp(-Energy_Change/Temp);

				if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
				{
					Particles[Current_Row][Current_Column].Set_Spin(0);
					return;
				}
			}
			
			Update_Energy(Energy_Change);
			Update_Probability_Minus_One(1);
			Update_Probability_Zero(-1);
			return;
		}
	}
	else if(i==1)
	{
		
			double Initial_Energy = Return_Local_Energy();
			Particles[Current_Row][Current_Column].Set_Spin(0);
			double Final_Energy = Return_Local_Energy();

			double Energy_Change = Final_Energy-Initial_Energy;

			if(Energy_Change>0)
			{
				double Monte_Carlo = exp(-Energy_Change/Temp);

				if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
				{
					Particles[Current_Row][Current_Column].Set_Spin(1);
					return;
				}			
				
			}

			Update_Energy(Energy_Change);
			Update_Probability_One(-1);
			Update_Probability_Zero(1);
			return;
		
	}
	else if(i==-1)
	{
		
			double Initial_Energy = Return_Local_Energy();
			Particles[Current_Row][Current_Column].Set_Spin(0);
			double Final_Energy = Return_Local_Energy();

			double Energy_Change = Final_Energy-Initial_Energy;

			if(Energy_Change>0)
			{
				double Monte_Carlo = exp(-Energy_Change/Temp);

				if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
				{
					Particles[Current_Row][Current_Column].Set_Spin(-1);
					return;
				}			
				
			}

			Update_Energy(Energy_Change);
			Update_Probability_Minus_One(-1);
			Update_Probability_Zero(1);
			return;
		
	}
	return;
}

void System::Find_Neighbours()
{
	Particle_One_Column = Current_Column;
	Particle_One_Row = Current_Row+1;

	Particle_Two_Column = Current_Column+1;
	Particle_Two_Row = Current_Row;

	Particle_Three_Column = Current_Column;
	Particle_Three_Row = Current_Row-1;

	Particle_Four_Column = Current_Column-1;
	Particle_Four_Row = Current_Row;

	if(Current_Row==0)
	{
		Particle_Three_Row=ISINGSIZE-1;
	}
	else if(Current_Row==ISINGSIZE-1)
	{
		Particle_One_Row = 0;
	}

	if(Current_Column==0)
	{
		Particle_Four_Column = ISINGSIZE-1;
	}
	else if(Current_Column==ISINGSIZE-1)
	{
		Particle_Two_Column = 0;
	}

	return;
}

double System::Return_Local_Energy()
{
	Find_Neighbours();
	
	double Energy1 = Particles[Current_Row][Current_Column].Return_Spin()*(	Particles[Particle_One_Row][Particle_One_Column].Return_Spin()
		+																	Particles[Particle_Two_Row][Particle_Two_Column].Return_Spin()
		+																	Particles[Particle_Three_Row][Particle_Three_Column].Return_Spin()
		+																	Particles[Particle_Four_Row][Particle_Four_Column].Return_Spin());	

	return Energy1;
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
			Find_Neighbours();

			Energy_Placeholder = Energy_Placeholder + (Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_One_Column][Particle_One_Row].Return_Spin()
				+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Two_Column][Particle_Two_Row].Return_Spin()
				+	Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Three_Column][Particle_Three_Row].Return_Spin()
				+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Four_Column][Particle_Four_Row].Return_Spin());

		}
	}

	Energy = Energy_Placeholder/(double)2;
	return;
}

double System::Return_Energy()
{
	return Energy;
}

void System::Update_Energy(double Energy_Difference)
{
	Energy = Energy + Energy_Difference;
	return;
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

void System::Get_Probability()
{
	Probability_One=0;
	Probability_Zero=0;
	Probability_Minus_One=0;

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			if(Particles[i][j].Return_Spin()==1)
			{
				Probability_One++;
			}
			if(Particles[i][j].Return_Spin()==0)
			{
				Probability_Zero++;
			}
			if(Particles[i][j].Return_Spin()==-1)
			{
				Probability_Minus_One++;
			}
		}
	}

	return;
}

void System::Update_Probability_One(int delta_P)
{
	Probability_One=Probability_One+delta_P;
	return;
}

void System::Update_Probability_Zero(int delta_P)
{
	Probability_Zero=Probability_Zero+delta_P;
	return;
}

void System::Update_Probability_Minus_One(int delta_P)
{
	Probability_Minus_One=Probability_Minus_One+delta_P;
	return;
}

int System::Return_Probability_One()
{
	return Probability_One;
}

int System::Return_Probability_Zero()
{
	return Probability_Zero;
}

int System::Return_Probability_Minus_One()
{
	return Probability_Minus_One;
}
