#include <cmath>
#include "Particle.h"
using namespace std;

Particle::Particle()
{
	spin=1;
	lattice=0;
	return;
}

int Particle::Return_Spin()
{
	return spin;
}

void Particle::Set_Spin(int Input)
{
	spin=Input;
	return;
}

void Particle::Flip_Spin_Up()
{
	if(spin==MAXSPIN)
	{
		spin=spin*(-1);
		return;
	}
	else
	{
		spin=spin+1;
		return;
	}

}

void Particle::Flip_Spin_Down()
{
	if(spin==-MAXSPIN)
	{
		spin=spin*(-1);
		return;
	}
	else
	{
		spin=spin-1;
		return;
	}

}

int Particle::Return_Lattice()
{
	return lattice;
}

void Particle::Set_Lattice(int Current_Lattice)
{
	lattice = Current_Lattice;
	return;
}