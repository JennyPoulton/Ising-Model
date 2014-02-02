#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

class Particle
{
private:
	int spin;
public:
	Particle();
	int Return_Spin();
	void Set_Spin(int Input_Spin);
};

#endif