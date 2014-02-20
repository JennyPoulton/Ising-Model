#include<cmath>
#include "System.h"

System::System()
{

	//int* Up[ISINGSIZE][ISINGSIZE];		// define the up lattice to hold 
	//int* Down[ISINGSIZE][ISINGSIZE];		// the values up from those in 
	//int* Left[ISINGSIZE][ISINGSIZE];		// the respective position in lattice
	//int* Right[ISINGSIZE][ISINGSIZE];

	//int Lattice[ISINGSIZE][ISINGSIZE]; //define the main lattice

	Number_of_Lattices = 2;

	for(int x=0; x<(ISINGSIZE); x++)
		for(int y=0; y<(ISINGSIZE); y++)
		{
			{
				Lattice[x][y].Set_Spin((int)(pow(-1,(float)x))*(int)(pow(-1,(float)y))); //set the main values
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

				Up[x][y]=&Lattice[x][(ISINGSIZE+y-1)%(ISINGSIZE-1)];		//set the surrounding lattice values 
				Down[x][y]=&Lattice[x][(y+1)%(ISINGSIZE-1)];	// equal to those in correct positions
				Left[x][y]=&Lattice[(ISINGSIZE+x-1)%(ISINGSIZE-1)][y];			// in lattice
				Right[x][y]=&Lattice[(x+1)%(ISINGSIZE-1)][y];

			}
		}

		Find_Total_Energy();
		Get_Initial_Probability();

		Current_Column=0;
		Current_Row=0;

		Set_Temp(0);

		return;

}