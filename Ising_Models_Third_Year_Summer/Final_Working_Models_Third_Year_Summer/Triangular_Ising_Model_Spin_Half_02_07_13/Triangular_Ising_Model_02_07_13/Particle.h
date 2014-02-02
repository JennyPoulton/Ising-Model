#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

class Particle
{
private:
	int spin;
public:
	Particle();
	void Flip_Spin();
	int Return_Spin();
	void Set_Spin(int Input_Spin);
};

#endif