#include <cmath>
#include "Particle.h"
using namespace std;

Particle::Particle()
{
	int spin=1;
	return;
}

int Particle::Return_Spin()
{
	return spin;
}

void Particle::Set_Spin(int Input_Spin)
{
	spin = Input_Spin;
	return;
}

void Particle::Flip_Spin_Up()
{
	spin = spin + 1;
	return;
}

void Particle::Flip_Spin_Down()
{
	spin = spin - 1;
	return;
}

int Particle::Check_Up()
{
	if(spin==1)
	{
		return 0;
	}
	
	return 1;
}

int Particle::Check_Down()
{
	if(spin==-1)
	{
		return 0;
	}
	
	return 1;
}
