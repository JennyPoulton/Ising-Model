#include <cmath>
#include <stdlib.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "Particle.h"
#include "System.h"
using namespace std;
boost::random::mt19937 gen;

void System::Choose_Particle()
{
	Current_Row = Generate_Random_Number()*ISINGSIZE;
	Current_Row = Generate_Random_Number()*ISINGSIZE;

	return;
}

void System::Peturb_Particle()
{
	float rand = Generate_Random_Number();
	if(rand>0.5)
	{
		int Initial_Energy = Return_Local_Energy();
		int Initial_Spin = Lattice[Current_Row][Current_Column].Return_Spin();
		Lattice[Current_Row][Current_Column].Flip_Spin_Up();
		int Final_Energy = Return_Local_Energy();
		int Final_Spin = Lattice[Current_Row][Current_Column].Return_Spin();

		int Energy_Change = Initial_Energy-Final_Energy;
		int Spin_Change = Initial_Spin-Final_Spin;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-Energy_Change*One_Over_Temp);

			if(Monte_Carlo<Generate_Random_Number())
			{
				Lattice[Current_Row][Current_Column].Flip_Spin_Down();

				return;
			}
		}

		Update_Probability(Initial_Spin, Final_Spin);
		Update_Energy(Energy_Change);

		if(Current_Row%2==Current_Column%2)
		{
			Update_Magnetism_One(Spin_Change);
		}
		else
		{
			Update_Magnetism_Two(Spin_Change);
		}
	}
	else
	{
		int Initial_Energy = Return_Local_Energy();
		int Initial_Spin = Lattice[Current_Row][Current_Column].Return_Spin();
		Lattice[Current_Row][Current_Column].Flip_Spin_Down();
		int Final_Energy = Return_Local_Energy();
		int Final_Spin = Lattice[Current_Row][Current_Column].Return_Spin();

		int Energy_Change = Initial_Energy-Final_Energy;
		int Spin_Change = Initial_Spin-Final_Spin;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-Energy_Change*One_Over_Temp);

			if(Monte_Carlo<Generate_Random_Number())
			{
				Lattice[Current_Row][Current_Column].Flip_Spin_Up();

				return;
			}
		}
		
		Update_Probability(Initial_Spin, Final_Spin);
		Update_Energy(Energy_Change);

		if(Current_Row%2==Current_Column%2)
		{
			Update_Magnetism_One(Spin_Change);
		}
		else
		{
			Update_Magnetism_Two(Spin_Change);
		}
	}
}

int System::Return_Local_Energy()
{
		int Local_Energy = ((*Up[Current_Column][Current_Row]).Return_Spin() +
							(*Down[Current_Column][Current_Row]).Return_Spin() +
							(*Left[Current_Column][Current_Row]).Return_Spin() +
							(*Right[Current_Column][Current_Row]).Return_Spin())*Lattice[Current_Column][Current_Row].Return_Spin();

		return Local_Energy;
}

void System::Find_Total_Energy()
{
	int Total;

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			Current_Row=i;
			Current_Column=j;

			Total = Total + Return_Local_Energy();
		}
	}

	Energy = Total*0.5;
	return;
}

int System::Return_Energy()
{
	return Energy;
}

void System::Update_Energy(int Energy_Difference)
{
	Energy=Energy+Energy_Difference;
	return;
}

void System::Set_Temp(double Temperature)
{
	Temp=Temperature;
	return;
}

double System::Return_Temp()
{
	return Temp;
}

void System::Get_Initial_Probability()
{
	for(int i=0; i<Lattice[0][0].Return_Max_Spin(); i++)
	{
		Probability[i]=0;
	}
	
	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			
			Probability[Lattice[i][j].Return_Spin()+Lattice[i][j].Return_Max_Spin()]++;

		}
	}
}

void System::Update_Probability(int Initial_Spin, int Final_Spin)
{
	Probability[Initial_Spin+Lattice[0][0].Return_Max_Spin()]--;
	Probability[Final_Spin+Lattice[0][0].Return_Max_Spin()]++;
	return;
}

int System::Return_Probability_One()
{
	return Probability[1+Lattice[0][0].Return_Max_Spin()];
}

int System::Return_Probability_Zero()
{
	return Probability[0+Lattice[0][0].Return_Max_Spin()];
}

int System::Return_Probability_Minus_One()
{
	return Probability[-1+Lattice[0][0].Return_Max_Spin()];
}

void System::Set_Up_Magnetism()
{
	for(int i=0; i<Number_of_Lattices; i++)
	{
		Magnetism[i]=0;
	}

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			Magnetism[Lattice[i][j].Return_Lattice()]++;
		}
	}
	return;
}

void System::Update_Magnetism(int Magnetism_Change)
{
	Magnetism[Lattice[Current_Column][Current_Row].Return_Lattice()] = Magnetism[Lattice[Current_Column][Current_Row].Return_Lattice()] + Magnetism_Change;
	return;
}

int System::Return_Magnetism_One()
{
	return Magnetism[0];
}

int System::Return_Magnetism_Two()
{
	return Magnetism[1];
}

