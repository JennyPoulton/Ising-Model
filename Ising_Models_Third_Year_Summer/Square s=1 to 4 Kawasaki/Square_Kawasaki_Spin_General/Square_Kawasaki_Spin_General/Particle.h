#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

class Particle
{
private:
	int spin;
public:
	Particle();
	void Flip_Spin_Up();
	int Check_Up();
	void Flip_Spin_Down();
	int Check_Down();
	int Return_Spin();
	void Set_Spin(int Input_Spin);
};

#endif