#include <cmath>
#include "Particle.h"
using namespace std;

Particle::Particle()
{
	spin=1;
	max_spin=1;
	return;
}

int Particle::Return_Spin()
{
	return spin;
}

int Particle::Return_Max_Spin()
{
	return max_spin;
}

void Particle::Set_Spin(int Input)
{
	spin=Input;
	return;
}

void Particle::Flip_Spin_Up()
{
	if(spin==max_spin)
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
	if(spin==-max_spin)
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