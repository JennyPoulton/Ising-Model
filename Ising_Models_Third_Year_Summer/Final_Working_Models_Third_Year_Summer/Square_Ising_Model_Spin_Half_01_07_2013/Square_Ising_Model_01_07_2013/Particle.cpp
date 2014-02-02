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

void Particle::Flip_Spin()
{
	int new_spin = spin*(-1);
	spin = new_spin;
	return;
}

void Particle::Set_Spin(int Input_Spin)
{
	spin = Input_Spin;
	return;
}
	
