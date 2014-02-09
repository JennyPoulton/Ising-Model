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
