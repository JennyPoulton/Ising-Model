#define ISINGSIZE 18 //must be a multiple of 3 and 2
#include<cmath>
#include "System.h"

System::System()
{

	//int* Up[ISINGSIZE][ISINGSIZE];		// define the up lattice to hold 
	//int* Down[ISINGSIZE][ISINGSIZE];		// the values up from those in 
	//int* Left[ISINGSIZE][ISINGSIZE];		// the respective position in lattice
	//int* Right[ISINGSIZE][ISINGSIZE];

	int Lattice[ISINGSIZE][ISINGSIZE]; //define the main lattice

	for(int x=0; x<(ISINGSIZE); x++)
		for(int y=0; y<(ISINGSIZE); y++)
		{
			{
				System.Lattice[x][y].Set_Spin((int)(pow(-1,(float)x))*(int)(pow(-1,(float)y))); //set the main values
			}
		}


		for(int y=0; y<ISINGSIZE; y++)
		{
			for(int x=0; x<ISINGSIZE; x++)
			{

				System.Up[x][y].spin = &System.Lattice[x][(ISINGSIZE+y-1)%(ISINGSIZE)].spin;		//set the surrounding lattice values 
				System.Down[x][y].spin = &System.Lattice[x][(ISINGSIZE+y+1)%(ISINGSIZE)].spin;	// equal to those in correct positions
				System.Left[x][y].spin = &System.Lattice[(ISINGSIZE+x-1)%(ISINGSIZE)][y].spin;			// in lattice
				System.Right[x][y].spin = &System.Lattice[(ISINGSIZE+x+1)%(ISINGSIZE)][y].spin;

			}
		}

	Find_Total_Energy();
	Get_Probability();
	
	Current_Column=0;
	Current_Row=0;

	Set_Temp(0);

		return;

}