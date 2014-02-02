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

int Particle::Flip_Spin_Up()
{
	int new_spin = spin+1;
	spin = new_spin;
	return 1;
}

int Particle::Flip_Spin_Down()
{
	int new_spin = spin-1;
	spin = new_spin;
	return -1;
}
void Particle::Set_Spin(int Input_Spin)
{
	spin = Input_Spin;
	return;
}
	
