#define ISINGSIZE 18 //must be a multiple of 3 and 2
#include<cmath>

int main (void)
{

	int Up[ISINGSIZE*ISINGSIZE];		// define the up lattice to hold 
	int Down[ISINGSIZE*ISINGSIZE];		// the values up from those in 
	int Left[ISINGSIZE*ISINGSIZE];		// the respective position in lattice
	int Right[ISINGSIZE*ISINGSIZE];

	int *Lattice[ISINGSIZE*ISINGSIZE]; //define the main lattice

	for(float x=0; x<(ISINGSIZE*ISINGSIZE); x++)
	{
		Lattice[x] = (int)(pow(-1,x)); //set the main values
	}


	for(int x=0; x<(ISINGSIZE*ISINGSIZE); x++)
	{

		&Up[x]=*Lattice[((ISINGSIZE*ISINGSIZE)+x-ISINGSIZE)%(ISINGSIZE*ISINGSIZE)];		//set the surrounding lattice values 
		&Down[x]=*Lattice[((ISINGSIZE*ISINGSIZE)+x+ISINGSIZE)%(ISINGSIZE*ISINGSIZE)];	// equal to those in correct positions
		&Left[x]=*Lattice[((ISINGSIZE*ISINGSIZE)+x-1)%(ISINGSIZE*ISINGSIZE)];			// in lattice
		&Right[x]=*Lattice[((ISINGSIZE*ISINGSIZE)+x+1)%(ISINGSIZE*ISINGSIZE)];

	}

	return 0;

}