#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

#define ISINGSIZE 12 //must be a multiple of 3
#define MAXSPIN 1
#define LATTICE_NO 2
#define SPINMODES 3

class Particle
{

	public:
	int spin;
	int lattice;
	
	Particle();
	void Flip_Spin_Up();
	void Flip_Spin_Down();
	int Return_Spin();
	void Set_Lattice(int Current_Lattice);
	int Return_Lattice();
	void Set_Spin(int Input_Spin);
};

#endif