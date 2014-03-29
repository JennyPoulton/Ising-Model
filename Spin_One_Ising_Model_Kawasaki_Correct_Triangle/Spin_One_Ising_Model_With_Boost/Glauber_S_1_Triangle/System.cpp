#include <cmath>
#include <stdlib.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "Particle.h"
#include "System.h"
using namespace std;
boost::random::mt19937 gen;

System::System()
{

	
	for(int y=0; y<ISINGSIZE; y++)
	{
		for(int x=0; x<ISINGSIZE; x++)
		{

			if(x%3==y%3)
			{
				Lattice[x][y].Set_Lattice(0);
				Lattice[x][y].Set_Spin(1);
			}
			else if(((x+1)%3)==y%3)
			{
				Lattice[x][y].Set_Lattice(1);
				Lattice[x][y].Set_Spin(-1);
			}
			else if(((x+2)%3)==y%3)
			{
				Lattice[x][y].Set_Lattice(2);
				Lattice[x][y].Set_Spin(0);
			}


			One[x][y]=&Lattice[x][(y+1)%(ISINGSIZE)];
			Two[x][y]=&Lattice[(x+1)%(ISINGSIZE)][y];
			Three[x][y]=&Lattice[(x+1)%(ISINGSIZE)][(y-1+ISINGSIZE)%(ISINGSIZE)];
			Four[x][y]=&Lattice[x][(y-1+ISINGSIZE)%(ISINGSIZE)];
			Five[x][y]=&Lattice[(x-1+ISINGSIZE)%(ISINGSIZE)][y];
			Six[x][y]=&Lattice[(x-1+ISINGSIZE)%(ISINGSIZE)][(y+1)%(ISINGSIZE)];


		}
	}

	Find_Total_Energy();
	Get_Initial_Probability();
	Set_Up_Magnetism();

	Current_Column_One=0;
	Current_Row_One=0;

	Current_Column_Two=0;
	Current_Row_Two=0;

	Set_Temp(0);

	return;

}

float System::Generate_Random_Number()
{
	boost::random::uniform_int_distribution<> dist(1, 4096);
	return (double)dist(gen)/(double)4096;
}

void System::Peturb_Lattice_One()
{

	for(int i=0; i<ISINGSIZE; i=i+2)
	{
		for(int j=0; j<ISINGSIZE; j=j+2)
		{
			Current_Column_One=i;
			Current_Row_One=j;
			Choose_Neighbour();
			Peturb_Particle();
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+2)
	{
		for(int j=1; j<ISINGSIZE; j=j+2)
		{
			Current_Column_One=i;
			Current_Row_One=j;
			Choose_Neighbour();
			Peturb_Particle();
		}
	}
	return;
}

void System::Peturb_Lattice_Two()
{

	for(int i=0; i<ISINGSIZE; i=i+2)
	{
		for(int j=1; j<ISINGSIZE; j=j+2)
		{
			Current_Column_One=i;
			Current_Row_One=j;
			Choose_Neighbour();
			Peturb_Particle();
		}
	}

	for(int i=1; i<ISINGSIZE; i=i+2)
	{
		for(int j=0; j<ISINGSIZE; j=j+2)
		{
			Current_Column_One=i;
			Current_Row_One=j;
			Choose_Neighbour();
			Peturb_Particle();
		}
	}
	return;
}

void System::Choose_Neighbour()
{
	int Rand = rand()%6;

	if(Rand==0)
	{
		Current_Column_Two = (Current_Column_One + 1)%ISINGSIZE;
		Current_Row_Two = Current_Row_One;
	}
	else if(Rand==1)
	{
		Current_Column_Two = (Current_Column_One - 1 + ISINGSIZE)%ISINGSIZE;
		Current_Row_Two = Current_Row_One;
	}
	else if(Rand==2)
	{
		Current_Column_Two = Current_Column_One;
		Current_Row_Two = (Current_Row_One + 1)%ISINGSIZE;
	}
	else if(Rand==3)
	{
		Current_Column_Two = Current_Column_One;
		Current_Row_Two = (Current_Row_One - 1 +ISINGSIZE)%ISINGSIZE;
	}
	else if(Rand==4)
	{
		Current_Column_Two = (Current_Column_One+1)%ISINGSIZE;
		Current_Row_Two = (Current_Row_One - 1 +ISINGSIZE)%ISINGSIZE;
	}
	else if(Rand==5)
	{
		Current_Column_Two = (Current_Column_One-1+ISINGSIZE)%ISINGSIZE;
		Current_Row_Two = (Current_Row_One+1)%ISINGSIZE;
	}

}

void System::Peturb_Particle()
{
	double rand = Generate_Random_Number();
	//double random = rand()/(double)RAND_MAX;

	if(rand>0.5)
	{
		int Initial_Energy = Return_Local_Energy();
		int Initial_Spin_One = Lattice[Current_Row_One][Current_Column_One].Return_Spin();
		int Initial_Spin_Two = Lattice[Current_Row_Two][Current_Column_Two].Return_Spin();

		Lattice[Current_Row_One][Current_Column_One].Flip_Spin_Up();
		Lattice[Current_Row_Two][Current_Column_Two].Flip_Spin_Down();

		int Final_Energy = Return_Local_Energy();
		int Final_Spin_One = Lattice[Current_Row_One][Current_Column_One].Return_Spin();
		int Final_Spin_Two = Lattice[Current_Row_Two][Current_Column_Two].Return_Spin();


		int Energy_Change = Final_Energy-Initial_Energy;
		int Spin_One_Change = Final_Spin_One-Initial_Spin_One;
		int Spin_Two_Change = Final_Spin_Two-Initial_Spin_Two;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-(double)Energy_Change/Temp);

			//if(Monte_Carlo<(rand()/(double)RAND_MAX))
			if(Monte_Carlo<Generate_Random_Number())			
			{
				Lattice[Current_Row_One][Current_Column_One].Flip_Spin_Down();
				Lattice[Current_Row_Two][Current_Column_Two].Flip_Spin_Up();
				return;
			}
		}

		Update_Probability(Initial_Spin_One, Initial_Spin_Two, Final_Spin_One, Final_Spin_Two);
		Update_Energy(Energy_Change);
		Update_Magnetism(Spin_One_Change, Spin_Two_Change);

	}
	else
	{
		int Initial_Energy = Return_Local_Energy();
		int Initial_Spin_One = Lattice[Current_Row_One][Current_Column_One].Return_Spin();
		int Initial_Spin_Two = Lattice[Current_Row_Two][Current_Column_Two].Return_Spin();

		Lattice[Current_Row_One][Current_Column_One].Flip_Spin_Down();
		Lattice[Current_Row_Two][Current_Column_Two].Flip_Spin_Up();

		int Final_Energy = Return_Local_Energy();
		int Final_Spin_One = Lattice[Current_Row_One][Current_Column_One].Return_Spin();
		int Final_Spin_Two = Lattice[Current_Row_Two][Current_Column_Two].Return_Spin();


		int Energy_Change = Final_Energy-Initial_Energy;
		int Spin_One_Change = Final_Spin_One-Initial_Spin_One;
		int Spin_Two_Change = Final_Spin_Two-Initial_Spin_Two;

		if(Energy_Change>0)
		{
			double Monte_Carlo = exp(-(double)Energy_Change/Temp);

			//if(Monte_Carlo<(rand()/(double)RAND_MAX))
			if(Monte_Carlo<Generate_Random_Number())			
			{
				Lattice[Current_Row_One][Current_Column_One].Flip_Spin_Up();
				Lattice[Current_Row_Two][Current_Column_Two].Flip_Spin_Down();
				return;
			}
		}

		Update_Probability(Initial_Spin_One, Initial_Spin_Two, Final_Spin_One, Final_Spin_Two);
		Update_Energy(Energy_Change);
		Update_Magnetism(Spin_One_Change, Spin_Two_Change);
	}
}

int System::Return_Local_Energy()
{
	int Local_Energy = ((*One[Current_Row_One][Current_Column_One]).Return_Spin() +
		(*Two[Current_Row_One][Current_Column_One]).Return_Spin() +
		(*Three[Current_Row_One][Current_Column_One]).Return_Spin() +
		(*Four[Current_Row_One][Current_Column_One]).Return_Spin() +
		(*Five[Current_Row_One][Current_Column_One]).Return_Spin() +
		(*Six[Current_Row_One][Current_Column_One]).Return_Spin())*Lattice[Current_Row_One][Current_Column_One].Return_Spin()

		+((*One[Current_Row_Two][Current_Column_Two]).Return_Spin() +
		(*Two[Current_Row_Two][Current_Column_Two]).Return_Spin() +
		(*Three[Current_Row_Two][Current_Column_Two]).Return_Spin() +
		(*Four[Current_Row_Two][Current_Column_Two]).Return_Spin() +
		(*Five[Current_Row_Two][Current_Column_Two]).Return_Spin() +
		(*Six[Current_Row_Two][Current_Column_Two]).Return_Spin())*Lattice[Current_Row_Two][Current_Column_Two].Return_Spin()

		-(Lattice[Current_Row_One][Current_Column_One].Return_Spin()*Lattice[Current_Row_Two][Current_Column_Two].Return_Spin());

	return Local_Energy;
}

void System::Find_Total_Energy()
{
	int Total=0;

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			Current_Row_One=i;
			Current_Column_One=j;

			Total = Total + ((*One[Current_Row_One][Current_Column_One]).Return_Spin() +
				(*Two[Current_Row_One][Current_Column_One]).Return_Spin() +
				(*Three[Current_Row_One][Current_Column_One]).Return_Spin() +
				(*Four[Current_Row_One][Current_Column_One]).Return_Spin() +
				(*Five[Current_Row_One][Current_Column_One]).Return_Spin() +
				(*Six[Current_Row_One][Current_Column_One]).Return_Spin())*Lattice[Current_Row_One][Current_Column_One].Return_Spin();
		}
	}

	Energy = (double)Total*(double)0.5;
	return;
}

double System::Return_Energy()
{
	return (double)Energy;
}

void System::Update_Energy(int Energy_Difference)
{
	Energy = Energy + Energy_Difference;
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
	for(int i=0; i<SPINMODES; i++)
	{
		Probability[i]=0;
	}

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{

			Probability[Lattice[i][j].Return_Spin()+MAXSPIN]++;

		}
	}
}

void System::Update_Probability(int InitialSpinOne, int FinalSpinOne, int InitialSpinTwo, int FinalSpinTwo)
{
	Probability[InitialSpinOne+MAXSPIN]--;
	Probability[FinalSpinOne+MAXSPIN]++;
	Probability[InitialSpinTwo+MAXSPIN]--;
	Probability[FinalSpinTwo+MAXSPIN]++;
	return;
}

int System::Return_Probability_One()
{
	return Probability[1+MAXSPIN];
}

int System::Return_Probability_Zero()
{
	return Probability[0+MAXSPIN];
}

int System::Return_Probability_Minus_One()
{
	return Probability[-1+MAXSPIN];
}

void System::Set_Up_Magnetism()
{
	for(int i=0; i<LATTICE_NO; i++)
	{
		Magnetism[i]=0;
	}

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			Magnetism[Lattice[i][j].Return_Lattice()]=Magnetism[Lattice[i][j].Return_Lattice()]+Lattice[i][j].Return_Spin();
		}
	}
	return;
}

void System::Update_Magnetism(int Magnetism_Change_One, int Magnetism_Change_Two)
{
	Magnetism[Lattice[Current_Row_One][Current_Column_One].Return_Lattice()] = Magnetism[Lattice[Current_Row_One][Current_Column_One].Return_Lattice()] + Magnetism_Change_One;
	Magnetism[Lattice[Current_Row_Two][Current_Column_Two].Return_Lattice()] = Magnetism[Lattice[Current_Row_Two][Current_Column_Two].Return_Lattice()] + Magnetism_Change_Two;
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

int System::Return_Magnetism_Three()
{
	return Magnetism[2];
}
