#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

class Particle
{

	public:
	int spin;
	int lattice;
	int max_spin;

	Particle();
	void Flip_Spin_Up();
	void Flip_Spin_Down();
	int Return_Spin();
	int Return_Max_Spin();
	void Set_Lattice(int Current_Lattice);
	int Return_Lattice();
	void Set_Spin(int Input_Spin);
};

#endif