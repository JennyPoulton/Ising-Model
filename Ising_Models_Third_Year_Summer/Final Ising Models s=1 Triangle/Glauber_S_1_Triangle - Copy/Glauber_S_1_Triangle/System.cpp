#include <cmath>
#include <stdlib.h>
#include "Particle.h"
#include "System.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
using namespace std;

boost::random::mt19937 gen;

System::System()
{
	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			if(i%3==j%3)
			{
				Particles[i][j].Set_Spin(0);
			}
			else if(((i+1)%3)==j%3)
			{
				Particles[i][j].Set_Spin(1);
			}
			else if(((i+2)%3)==j%3)
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

float System::Generate_Random_Number()
{
	boost::random::uniform_int_distribution<> dist(1, 4096);
	return (double)dist(gen)/(double)4096;
}

void System::Choose_Particle()
{
	Current_Row=rand()%ISINGSIZE;
	Current_Column=rand()%ISINGSIZE;
	Find_Neighbours();
	Choose_Particle2();
	return;
}

void System::Choose_Particle2()
{
	int Rand=rand()%6;

	if(Rand==0)
	{
		Current_Column2=Particle_One_Column;
		Current_Row2 = Particle_One_Row;
	}
	else if(Rand==1)										 
	{														 
		Current_Column2=Particle_Two_Column;				 
		Current_Row2 = Particle_Two_Row;					 
	}														 
	else if(Rand==2)										 
	{														 
		Current_Column2=Particle_Three_Column;				 
		Current_Row2 = Particle_Three_Row;				 
	}														 
	else if(Rand==3)										 
	{														 
		Current_Column2=Particle_Four_Column;				 
		Current_Row2 = Particle_Four_Row;				 
	}
	else if(Rand==4)										 
	{														 
		Current_Column2=Particle_Five_Column;				 
		Current_Row2 = Particle_Five_Row;				 
	}	
	else if(Rand==5)										 
	{														 
		Current_Column2=Particle_Six_Column;				 
		Current_Row2 = Particle_Six_Row;				 
	}	

	Find_Neighbours2();
	return;
}

void System::Peturb_Particle()
{
	int i=Particles[Current_Row][Current_Column].Return_Spin();
	int j=Particles[Current_Row2][Current_Column2].Return_Spin();

	if(i==0&&j==0)
	{
		if(rand()/(double)RAND_MAX>0.5)
		{
			double Initial_Energy = Return_Local_Energy();
			Particles[Current_Row][Current_Column].Set_Spin(1);
 			Particles[Current_Row2][Current_Column2].Set_Spin(-1);
			double Final_Energy = Return_Local_Energy();

			double Energy_Change = Final_Energy-Initial_Energy;

			if(Energy_Change>0)
			{
				double Monte_Carlo = exp(-Energy_Change/Temp);

				if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
				{
					Particles[Current_Row][Current_Column].Set_Spin(0);
					Particles[Current_Row2][Current_Column2].Set_Spin(0);
					return;
				}			

			}

			Update_Energy(Energy_Change);
			Update_Probability_One(1);
			Update_Probability_Zero(-2);
			Update_Probability_Minus_One(1);

			int Lattice1 = Get_Lattice();

			if(Lattice1==1)
			{
				Update_Magnetism_One(1);
			}
			else if(Lattice1==2)
			{
				Update_Magnetism_Two(1);
			}
			else if(Lattice1==3)
			{
				Update_Magnetism_Three(1);
			}

			Current_Column=Current_Column2;
			Current_Row=Current_Row2;

			int Lattice2 = Get_Lattice();

			if(Lattice2==1)
			{
				Update_Magnetism_One(-1);
			}
			else if(Lattice2==2)
			{
				Update_Magnetism_Two(-1);
			}
			else if(Lattice2==3)
			{
				Update_Magnetism_Three(-1);
			}

			return;

		}
		else
		{
			double Initial_Energy = Return_Local_Energy();
			Particles[Current_Row][Current_Column].Set_Spin(-1);
			Particles[Current_Row2][Current_Column2].Set_Spin(1);
			double Final_Energy = Return_Local_Energy();

			double Energy_Change = Final_Energy-Initial_Energy;

			if(Energy_Change>0)
			{
				double Monte_Carlo = exp(-Energy_Change/Temp);

				if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
				{
					Particles[Current_Row][Current_Column].Set_Spin(0);
					Particles[Current_Row2][Current_Column2].Set_Spin(0);
					return;
				}
			}

			Update_Energy(Energy_Change);
			Update_Probability_One(1);
			Update_Probability_Zero(-2);
			Update_Probability_Minus_One(1);
			int Lattice1 = Get_Lattice();

			if(Lattice1==1)
			{
				Update_Magnetism_One(-1);
			}
			else if(Lattice1==2)
			{
				Update_Magnetism_Two(-1);
			}
			else if(Lattice1==3)
			{
				Update_Magnetism_Three(-1);
			}

			Current_Column=Current_Column2;
			Current_Row=Current_Row2;

			int Lattice2 = Get_Lattice();

			if(Lattice2==1)
			{
				Update_Magnetism_One(1);
			}
			else if(Lattice2==2)
			{
				Update_Magnetism_Two(1);
			}
			else if(Lattice2==3)
			{
				Update_Magnetism_Three(1);
			}
			return;
		}


	}
	else if(i==0&&j==1)
	{
		if(rand()/(double)RAND_MAX>0.5)
		{
			return;
		}

		double Initial_Energy = Return_Local_Energy();
		Particles[Current_Row][Current_Column].Set_Spin(1);
		Particles[Current_Row2][Current_Column2].Set_Spin(0);
		double Final_Energy = Return_Local_Energy();

		double Energy_Change = Final_Energy-Initial_Energy;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-Energy_Change/Temp);

			if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
			{
				Particles[Current_Row][Current_Column].Set_Spin(0);
				Particles[Current_Row2][Current_Column2].Set_Spin(1);
				return;
			}
		}

		Update_Energy(Energy_Change);
		int Lattice1 = Get_Lattice();

		if(Lattice1==1)
		{
			Update_Magnetism_One(1);
		}
		else if(Lattice1==2)
		{
			Update_Magnetism_Two(1);
		}
		else if(Lattice1==3)
		{
			Update_Magnetism_Three(1);
		}

		Current_Column=Current_Column2;
		Current_Row=Current_Row2;

		int Lattice2 = Get_Lattice();

		if(Lattice2==1)
		{
			Update_Magnetism_One(-1);
		}
		else if(Lattice2==2)
		{
			Update_Magnetism_Two(-1);
		}
		else if(Lattice2==3)
		{
			Update_Magnetism_Three(-1);
		}

		return;
	}
	else if(i==1&&j==0)
	{
		if(rand()/(double)RAND_MAX>0.5)
		{
			return;
		}

		double Initial_Energy = Return_Local_Energy();
		Particles[Current_Row][Current_Column].Set_Spin(0);
		Particles[Current_Row2][Current_Column2].Set_Spin(1);
		double Final_Energy = Return_Local_Energy();

		double Energy_Change = Final_Energy-Initial_Energy;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-Energy_Change/Temp);

			if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
			{
				Particles[Current_Row][Current_Column].Set_Spin(1);
				Particles[Current_Row2][Current_Column2].Set_Spin(0);
				return;
			}
		}

		Update_Energy(Energy_Change);
		int Lattice1 = Get_Lattice();

		if(Lattice1==1)
		{
			Update_Magnetism_One(-1);
		}
		else if(Lattice1==2)
		{
			Update_Magnetism_Two(-1);
		}
		else if(Lattice1==3)
		{
			Update_Magnetism_Three(-1);
		}

		Current_Column=Current_Column2;
		Current_Row=Current_Row2;

		int Lattice2 = Get_Lattice();

		if(Lattice2==1)
		{
			Update_Magnetism_One(1);
		}
		else if(Lattice2==2)
		{
			Update_Magnetism_Two(1);
		}
		else if(Lattice2==3)
		{
			Update_Magnetism_Three(1);
		}
		return;
	}
	else if(i==1&&j==1)
	{
		return;
	}
	else if(i==0&&j==-1)
	{
		if(rand()/(double)RAND_MAX>0.5)
		{
			return;
		}

		double Initial_Energy = Return_Local_Energy();
		Particles[Current_Row][Current_Column].Set_Spin(-1);
		Particles[Current_Row2][Current_Column2].Set_Spin(0);
		double Final_Energy = Return_Local_Energy();

		double Energy_Change = Final_Energy-Initial_Energy;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-Energy_Change/Temp);

			if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
			{
				Particles[Current_Row][Current_Column].Set_Spin(0);
				Particles[Current_Row2][Current_Column2].Set_Spin(-1);
				return;
			}
		}

		Update_Energy(Energy_Change);
		int Lattice1 = Get_Lattice();

		if(Lattice1==1)
		{
			Update_Magnetism_One(-1);
		}
		else if(Lattice1==2)
		{
			Update_Magnetism_Two(-1);
		}
		else if(Lattice1==3)
		{
			Update_Magnetism_Three(-1);
		}

		Current_Column=Current_Column2;
		Current_Row=Current_Row2;

		int Lattice2 = Get_Lattice();

		if(Lattice2==1)
		{
			Update_Magnetism_One(1);
		}
		else if(Lattice2==2)
		{
			Update_Magnetism_Two(1);
		}
		else if(Lattice2==3)
		{
			Update_Magnetism_Three(1);
		}
		return;
	}
	else if(i==-1&&j==0)
	{
		if(rand()/(double)RAND_MAX>0.5)
		{
			return;
		}

		double Initial_Energy = Return_Local_Energy();
		Particles[Current_Row][Current_Column].Set_Spin(0);
		Particles[Current_Row2][Current_Column2].Set_Spin(-1);
		double Final_Energy = Return_Local_Energy();

		double Energy_Change = Final_Energy-Initial_Energy;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-Energy_Change/Temp);

			if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
			{
				Particles[Current_Row][Current_Column].Set_Spin(-1);
				Particles[Current_Row2][Current_Column2].Set_Spin(0);
				return;
			}
		}

		Update_Energy(Energy_Change);
		int Lattice1 = Get_Lattice();

		if(Lattice1==1)
		{
			Update_Magnetism_One(1);
		}
		else if(Lattice1==2)
		{
			Update_Magnetism_Two(1);
		}
		else if(Lattice1==3)
		{
			Update_Magnetism_Three(1);
		}

		Current_Column=Current_Column2;
		Current_Row=Current_Row2;

		int Lattice2 = Get_Lattice();

		if(Lattice2==1)
		{
			Update_Magnetism_One(-1);
		}
		else if(Lattice2==2)
		{
			Update_Magnetism_Two(-1);
		}
		else if(Lattice2==3)
		{
			Update_Magnetism_Three(-1);
		}
		return;
	}
	else if(i==-1&&j==1)
	{
		if(rand()/(double)RAND_MAX>0.5)
		{
			return;
		}

		double Initial_Energy = Return_Local_Energy();
		Particles[Current_Row][Current_Column].Set_Spin(0);
		Particles[Current_Row2][Current_Column2].Set_Spin(0);
		double Final_Energy = Return_Local_Energy();

		double Energy_Change = Final_Energy-Initial_Energy;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-Energy_Change/Temp);

			if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
			{
				Particles[Current_Row][Current_Column].Set_Spin(-1);
				Particles[Current_Row2][Current_Column2].Set_Spin(1);
				return;
			}
		}

		Update_Energy(Energy_Change);
		Update_Probability_One(-1);
		Update_Probability_Zero(2);
		Update_Probability_Minus_One(-1);
		int Lattice1 = Get_Lattice();

		if(Lattice1==1)
		{
			Update_Magnetism_One(1);
		}
		else if(Lattice1==2)
		{
			Update_Magnetism_Two(1);
		}
		else if(Lattice1==3)
		{
			Update_Magnetism_Three(1);
		}

		Current_Column=Current_Column2;
		Current_Row=Current_Row2;

		int Lattice2 = Get_Lattice();

		if(Lattice2==1)
		{
			Update_Magnetism_One(-1);
		}
		else if(Lattice2==2)
		{
			Update_Magnetism_Two(-1);
		}
		else if(Lattice2==3)
		{
			Update_Magnetism_Three(-1);
		}
		return;
	}
	else if(i==1&&j==-1)
	{
		if(rand()/(double)RAND_MAX>0.5)
		{
			return;
		}

		double Initial_Energy = Return_Local_Energy();
		Particles[Current_Row][Current_Column].Set_Spin(0);
		Particles[Current_Row2][Current_Column2].Set_Spin(0);
		double Final_Energy = Return_Local_Energy();

		double Energy_Change = Final_Energy-Initial_Energy;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-Energy_Change/Temp);

			if(Monte_Carlo<((double)rand()/(double)RAND_MAX))
			{
				Particles[Current_Row][Current_Column].Set_Spin(1);
				Particles[Current_Row2][Current_Column2].Set_Spin(-1);
				return;
			}
		}

		Update_Energy(Energy_Change);
		Update_Probability_One(-1);
		Update_Probability_Zero(2);
		Update_Probability_Minus_One(-1);

		int Lattice1 = Get_Lattice();

		if(Lattice1==1)
		{
			Update_Magnetism_One(-1);
		}
		else if(Lattice1==2)
		{
			Update_Magnetism_Two(-1);
		}
		else if(Lattice1==3)
		{
			Update_Magnetism_Three(-1);
		}

		Current_Column=Current_Column2;
		Current_Row=Current_Row2;

		int Lattice2 = Get_Lattice();

		if(Lattice2==1)
		{
			Update_Magnetism_One(1);
		}
		else if(Lattice2==2)
		{
			Update_Magnetism_Two(1);
		}
		else if(Lattice2==3)
		{
			Update_Magnetism_Three(1);
		}
		return;
	}
	else if(i==-1&&j==-1)
	{
		return;
	}

	system("pause");
	return;
}

void System::Find_Neighbours()
{
	Particle_One_Column = Current_Column;
	Particle_One_Row = Current_Row+1;

	Particle_Two_Column = Current_Column+1;
	Particle_Two_Row = Current_Row;

	Particle_Three_Column = Current_Column+1;
	Particle_Three_Row = Current_Row-1;

	Particle_Four_Column = Current_Column;
	Particle_Four_Row = Current_Row-1;

	Particle_Five_Column = Current_Column-1;
	Particle_Five_Row = Current_Row;

	Particle_Six_Column = Current_Column-1;
	Particle_Six_Row = Current_Row+1;

	if(Current_Row==0)
	{
		Particle_Three_Row = ISINGSIZE-1;
		Particle_Four_Row = ISINGSIZE-1;
	}
	else if(Current_Row==ISINGSIZE-1)
	{
		Particle_Six_Row = 0;
		Particle_One_Row = 0;
	}

	if(Current_Column==0)
	{
		Particle_Five_Column = ISINGSIZE-1;
		Particle_Six_Column = ISINGSIZE-1;
	}
	else if(Current_Column==ISINGSIZE-1)
	{
		Particle_Two_Column = 0;
		Particle_Three_Column = 0;
	}

	return;
}

void System::Find_Neighbours2()
{
	Particle_One_Column2 = Current_Column2;
	Particle_One_Row2 = Current_Row2+1;

	Particle_Two_Column2 = Current_Column2+1;
	Particle_Two_Row2 = Current_Row2;

	Particle_Three_Column2 = Current_Column2+1;
	Particle_Three_Row2 = Current_Row2-1;

	Particle_Four_Column2 = Current_Column2;
	Particle_Four_Row2 = Current_Row2-1;

	Particle_Five_Column2 = Current_Column2-1;
	Particle_Five_Row2 = Current_Row2;

	Particle_Six_Column2 = Current_Column2-1;
	Particle_Six_Row2 = Current_Row2+1;

	if(Current_Row2==0)
	{
		Particle_Three_Row2 = ISINGSIZE-1;
		Particle_Four_Row2 = ISINGSIZE-1;
	}
	else if(Current_Row2==ISINGSIZE-1)
	{
		Particle_Six_Row2 = 0;
		Particle_One_Row2 = 0;
	}

	if(Current_Column2==0)
	{
		Particle_Five_Column2 = ISINGSIZE-1;
		Particle_Six_Column2 = ISINGSIZE-1;
	}
	else if(Current_Column2==ISINGSIZE-1)
	{
		Particle_Two_Column2 = 0;
		Particle_Three_Column2 = 0;
	}

	return;
}

double System::Return_Local_Energy()
{
	Find_Neighbours();
	Find_Neighbours2();

	double Energy1 = (Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_One_Row][Particle_One_Column].Return_Spin()
		+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Two_Row][Particle_Two_Column].Return_Spin()
		+	Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Three_Row][Particle_Three_Column].Return_Spin()
		+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Four_Row][Particle_Four_Column].Return_Spin()
		+	Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Five_Row][Particle_Five_Column].Return_Spin()
		+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Six_Row][Particle_Six_Column].Return_Spin());

	double Energy2 = (Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_One_Row2][Particle_One_Column2].Return_Spin()
		+    Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_Two_Row2][Particle_Two_Column2].Return_Spin()
		+	Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_Three_Row2][Particle_Three_Column2].Return_Spin()
		+    Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_Four_Row2][Particle_Four_Column2].Return_Spin()
		+	Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_Five_Row2][Particle_Five_Column2].Return_Spin()
		+    Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_Six_Row2][Particle_Six_Column2].Return_Spin());

	double Energy = Energy1 + Energy2 - Particles[Current_Row][Current_Column].Return_Spin()*Particles[Current_Row2][Current_Column2].Return_Spin();

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
			Find_Neighbours();

			Energy_Placeholder = Energy_Placeholder + (Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_One_Row][Particle_One_Column].Return_Spin()
				+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Two_Row][Particle_Two_Column].Return_Spin()
				+	Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Three_Row][Particle_Three_Column].Return_Spin()
				+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Four_Row][Particle_Four_Column].Return_Spin()
				+	Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Five_Row][Particle_Five_Column].Return_Spin()
				+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Six_Row][Particle_Six_Column].Return_Spin());

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

int System::Set_Up_Magnetism_One()
{
	int count = 0;
	int Magnetism_Placeholder=0;

	for(int i=0; i<ISINGSIZE; i=i+3)
	{
		for(int j=0; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+3)
	{
		for(int j=1; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	for(int i=2; i<ISINGSIZE; i=i+3)
	{
		for(int j=2; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	Magnetism_Lattice_One = Magnetism_Placeholder;
	return count;
}

int System::Set_Up_Magnetism_Two()
{
	int count = 0;
	int Magnetism_Placeholder=0;

	for(int i=0; i<ISINGSIZE; i=i+3)
	{
		for(int j=1; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+3)
	{
		for(int j=2; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	for(int i=2; i<ISINGSIZE; i=i+3)
	{
		for(int j=0; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	Magnetism_Lattice_Two = Magnetism_Placeholder;
	return count;
}

int System::Set_Up_Magnetism_Three()
{
	int count = 0;
	int Magnetism_Placeholder=0;

	for(int i=0; i<ISINGSIZE; i=i+3)
	{
		for(int j=2; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+3)
	{
		for(int j=0; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	for(int i=2; i<ISINGSIZE; i=i+3)
	{
		for(int j=1; j<ISINGSIZE; j=j+3)
		{
			Magnetism_Placeholder = Magnetism_Placeholder + Particles[i][j].Return_Spin();
			count = count + 1;
		}
	}

	Magnetism_Lattice_Three = Magnetism_Placeholder;
	return count;
}

int System::Get_Lattice()
{	
		
	if(Current_Row%3==Current_Column%3)
	{
		return 1;
	}
	else if(((Current_Row+1)%3)==Current_Column%3)
	{
		return 2;
	}
	else if(((Current_Row+2)%3)==Current_Column%3)
	{
		return 3;
	}

}

void System::Update_Magnetism_One(int Magnetism_Change)
{
	Magnetism_Lattice_One = Magnetism_Lattice_One + Magnetism_Change;
	return;
}

void System::Update_Magnetism_Two(int Magnetism_Change)
{
	Magnetism_Lattice_Two = Magnetism_Lattice_Two + Magnetism_Change;
	return;
}

void System::Update_Magnetism_Three(int Magnetism_Change)
{
	Magnetism_Lattice_Three = Magnetism_Lattice_Three + Magnetism_Change;
	return;
}

int System::Return_Magnetism_One()
{
	return Magnetism_Lattice_One;
}

int System::Return_Magnetism_Two()
{
	return Magnetism_Lattice_Two;
}

int System::Return_Magnetism_Three()
{
	return Magnetism_Lattice_Three;
}