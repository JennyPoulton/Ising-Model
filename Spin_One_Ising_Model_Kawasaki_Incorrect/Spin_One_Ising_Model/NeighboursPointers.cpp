#include<cmath>
#include "System.h"

System::System()
{

	for(int i=0; i<ISINGSIZE; i++)
	{
		for(int j=0; j<ISINGSIZE; j++)
		{
			if(i%2==j%2)
			{
				Lattice[i][j].Set_Spin(1);
			}
			else
			{
				Lattice[i][j].Set_Spin(-1);
			}			
		}
	}

	for(int y=0; y<ISINGSIZE; y++)
	{
		for(int x=0; x<ISINGSIZE; x++)
		{

			if(x%2==y%2)
			{
				Lattice[x][y].Set_Lattice(0);
			}
			else
			{
				Lattice[x][y].Set_Lattice(1);
			}

			Up[x][y]=&Lattice[x][(ISINGSIZE+y-1)%(ISINGSIZE)];		//set the surrounding lattice values 
			Down[x][y]=&Lattice[x][((y+1)%(ISINGSIZE))];	// equal to those in correct positions
			Left[x][y]=&Lattice[(ISINGSIZE+x-1)%(ISINGSIZE)][y];			// in lattice
			Right[x][y]=&Lattice[((x+1)%(ISINGSIZE))][y];


		}
	}

	Find_Total_Energy();
	Get_Initial_Probability();
	Set_Up_Magnetism();

	Current_Column=0;
	Current_Row=0;

	Set_Temp(0);

	return;

}