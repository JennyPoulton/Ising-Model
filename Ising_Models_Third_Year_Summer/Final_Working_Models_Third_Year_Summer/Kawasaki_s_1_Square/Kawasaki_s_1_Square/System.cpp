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
			Particles[i][j].Set_Spin(0);			
		}
	}


	Find_Total_Energy();
	Get_Probability();

	Current_Column=0;
	Current_Row=0;

	Set_Temp(0);

	return;
}

void System::Choose_Particle()
{
	Current_Row=(int)(((double)rand()*(double)ISINGSIZE)/(double)(RAND_MAX+1));
	Current_Column=(int)(((double)rand()*(double)ISINGSIZE)/(double)(RAND_MAX+1));
	Find_Neighbours();
	Choose_Particle2();
	return;
}

void System::Choose_Particle2()
{
	int Rand=(int)(4*rand()/(double)(RAND_MAX+1));

	if(Rand==1)
	{
		Current_Column2=Particle_One_Column;
		Current_Row2 = Particle_One_Row;
	}
	else if(Rand==2)										 
	{														 
		Current_Column2=Particle_Two_Column;				 
		Current_Row2 = Particle_Two_Row;					 
	}														 
	else if(Rand==3)										 
	{														 
		Current_Column2=Particle_Three_Column;				 
		Current_Row2 = Particle_Three_Row;				 
	}														 
	else if(Rand==0)										 
	{														 
		Current_Column2=Particle_Four_Column;				 
		Current_Row2 = Particle_Four_Row;				 
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
			return;
		}


	}
	else if(i==0&&j==1)
	{
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
		return;
	}
	else if(i==1&&j==0)
	{
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
		return;
	}
	else if(i==1&&j==1)
	{
		return;
	}
	else if(i==0&&j==-1)
	{
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
		return;
	}
	else if(i==-1&&j==0)
	{
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
		return;
	}
	else if(i==-1&&j==1)
	{
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

		return;
	}
	else if(i==1&&j==-1)
	{
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

void System::Find_Neighbours2()
{
	Particle_One_Column2 = Current_Column2;
	Particle_One_Row2 = Current_Row2+1;

	Particle_Two_Column2 = Current_Column2+1;
	Particle_Two_Row2 = Current_Row2;

	Particle_Three_Column2 = Current_Column2;
	Particle_Three_Row2 = Current_Row2-1;

	Particle_Four_Column2 = Current_Column2-1;
	Particle_Four_Row2 = Current_Row2;

	if(Current_Row2==0)
	{
		Particle_Three_Row2=ISINGSIZE-1;
	}
	else if(Current_Row2==ISINGSIZE-1)
	{
		Particle_One_Row2 = 0;
	}

	if(Current_Column2==0)
	{
		Particle_Four_Column2 = ISINGSIZE-1;
	}
	else if(Current_Column2==ISINGSIZE-1)
	{
		Particle_Two_Column2 = 0;
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
		+    Particles[Current_Row][Current_Column].Return_Spin()*Particles[Particle_Four_Row][Particle_Four_Column].Return_Spin());

	double Energy2 = (Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_One_Row2][Particle_One_Column2].Return_Spin()
		+    Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_Two_Row2][Particle_Two_Column2].Return_Spin()
		+	Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_Three_Row2][Particle_Three_Column2].Return_Spin()
		+    Particles[Current_Row2][Current_Column2].Return_Spin()*Particles[Particle_Four_Row2][Particle_Four_Column2].Return_Spin());

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
