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