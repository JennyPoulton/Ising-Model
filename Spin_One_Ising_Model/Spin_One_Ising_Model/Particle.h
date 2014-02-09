#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

class Particle
{

	public:
	int spin;
	int max_spin;

	Particle();
	void Flip_Spin_Up();
	void Flip_Spin_Down();
	int Return_Spin();
	void Set_Spin(int Input_Spin);
};

#endif