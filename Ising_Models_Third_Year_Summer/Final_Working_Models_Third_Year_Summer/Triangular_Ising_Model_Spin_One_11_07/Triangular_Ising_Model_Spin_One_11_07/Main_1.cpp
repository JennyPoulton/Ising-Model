#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include "System.h"
#include "Particle.h"

using namespace std;

int main (void)
{

	double Set_Heating_or_Cooling = -1; //heating = 1, cooling = -1
	double Set_Initial_Temp = 100;
	double Set_Final_Temp = 0.01;
	double Set_Interval = 0.01;
	int Set_Anti_or_Ferro = -1; //anti = 1, ferro = -1
	int Number_Runs = 10000;

	srand(time(NULL));

	ofstream Output1("OutputMagnetisation.txt");

	if (!Output1.is_open())
	{
		cout << "Error: output file 1 cannot be opened." << endl;
		system("pause");
		return 1;
	}
	else
	{
		cout << "Output 1 file opened successfully." << endl;
	}

	System Triangle_Lattice;

	Triangle_Lattice.Set_A_or_F(Set_Anti_or_Ferro);

	if(Set_Heating_or_Cooling==1)
	{			 
		double Entropy=0;

		for(double Temperature=Set_Initial_Temp; Temperature<Set_Final_Temp; Temperature=Temperature+Set_Interval)
		{
			Triangle_Lattice.Set_Temp(Temperature);
			double Tally_M = 0;
			double Tally_Power_Four=0;
			double Tally_Power_Two=0;
			double Tally_E=0;
			double Tally_Energy_Two=0;


			for(int i=0; i<Number_Runs; i++)
			{
				Triangle_Lattice.Peturb_Lattice_One();
				Triangle_Lattice.Peturb_Lattice_Two();
				Triangle_Lattice.Peturb_Lattice_Three();

				Tally_M = Tally_M + Triangle_Lattice.Return_Magnetism();
				Tally_Power_Four = Tally_Power_Four + pow(Triangle_Lattice.Return_Magnetism(),4);
				Tally_Power_Two = Tally_Power_Two + pow(Triangle_Lattice.Return_Magnetism(),2);
				Tally_Energy_Two = Tally_Energy_Two + pow(Triangle_Lattice.Return_Energy(),2);
				Tally_E = Tally_E + Triangle_Lattice.Return_Energy();

			}

			double Magnetism = Tally_M/(double)Number_Runs;
			double Binder_Cumulant = 1 - (Tally_Power_Four/Number_Runs)/(3*pow((Tally_Power_Two/Number_Runs),2));
			double Energy = Tally_E/(double)Number_Runs;
			double Heat_Capacity = (((Tally_Energy_Two/(double)Number_Runs)-pow((Tally_E/(double)Number_Runs),2))/((double)Number_Runs*Temperature*Temperature));
			double Heat_Capacity_Over_Temp = (((Tally_Energy_Two/(double)Number_Runs)-pow((Tally_E/(double)Number_Runs),2))/((double)Number_Runs*Temperature*Temperature*Temperature));
			double Susceptibility = ((Tally_Power_Two/(double)Number_Runs) - pow((Tally_M/(double)Number_Runs),2))/((double)Number_Runs*Temperature);

			Output1 << Temperature << "\t" << Magnetism << "\t" << Binder_Cumulant << "\t" << Energy << "\t"<< Heat_Capacity << "\t"<< Susceptibility << "\t"<<  Heat_Capacity_Over_Temp << "\t" << Entropy << endl;

			Entropy = Entropy+(Heat_Capacity_Over_Temp*Set_Interval);
		}

		cout << "Entropy is" << "\t" << Entropy << endl;
	}
	else if(Set_Heating_or_Cooling==-1)
	{
		double Entropy=0;

		for(double Temperature=Set_Initial_Temp; Temperature<Set_Final_Temp; Temperature=Temperature-Set_Interval)
		{
			Triangle_Lattice.Set_Temp(Temperature);
			double Tally_M = 0;
			double Tally_Power_Four=0;
			double Tally_Power_Two=0;
			double Tally_E=0;
			double Tally_Energy_Two=0;

			if(Temperature<0.02)
			{

				for(int i=0; i<100000000000; i++)
				{
					if(Magnetism==0)
					{
						cout << i << endl;
						return i;
					}
					else
					{
						for(int i=0; i<Number_Runs; i++)
						{
							Triangle_Lattice.Peturb_Lattice_One();
							Triangle_Lattice.Peturb_Lattice_Two();
							Triangle_Lattice.Peturb_Lattice_Three();

							Tally_M = Tally_M + Triangle_Lattice.Return_Magnetism();
							Tally_Power_Four = Tally_Power_Four + pow(Triangle_Lattice.Return_Magnetism(),4);
							Tally_Power_Two = Tally_Power_Two + pow(Triangle_Lattice.Return_Magnetism(),2);
							Tally_Energy_Two = Tally_Energy_Two + pow(Triangle_Lattice.Return_Energy(),2);
							Tally_E = Tally_E + Triangle_Lattice.Return_Energy();

						}

						double Magnetism = Tally_M/(double)Number_Runs;
						double Binder_Cumulant = 1 - (Tally_Power_Four/Number_Runs)/(3*pow((Tally_Power_Two/Number_Runs),2));
						double Energy = Tally_E/(double)Number_Runs;
						double Heat_Capacity = (((Tally_Energy_Two/(double)Number_Runs)-pow((Tally_E/(double)Number_Runs),2))/((double)Number_Runs*Temperature*Temperature));
						double Heat_Capacity_Over_Temp = (((Tally_Energy_Two/(double)Number_Runs)-pow((Tally_E/(double)Number_Runs),2))/((double)Number_Runs*Temperature*Temperature*Temperature));
						double Susceptibility = ((Tally_Power_Two/(double)Number_Runs) - pow((Tally_M/(double)Number_Runs),2))/((double)Number_Runs*Temperature);

						Output1 << Temperature << "\t" << Magnetism << "\t" << Binder_Cumulant << "\t" << Energy << "\t"<< Heat_Capacity << "\t"<< Susceptibility << "\t"<<  Heat_Capacity_Over_Temp << "\t" << Entropy << endl;
					}

				}

			}



			for(int i=0; i<Number_Runs; i++)
			{
				Triangle_Lattice.Peturb_Lattice_One();
				Triangle_Lattice.Peturb_Lattice_Two();
				Triangle_Lattice.Peturb_Lattice_Three();

				Tally_M = Tally_M + Triangle_Lattice.Return_Magnetism();
				Tally_Power_Four = Tally_Power_Four + pow(Triangle_Lattice.Return_Magnetism(),4);
				Tally_Power_Two = Tally_Power_Two + pow(Triangle_Lattice.Return_Magnetism(),2);
				Tally_Energy_Two = Tally_Energy_Two + pow(Triangle_Lattice.Return_Energy(),2);
				Tally_E = Tally_E + Triangle_Lattice.Return_Energy();

			}

			double Magnetism = Tally_M/(double)Number_Runs;
			double Binder_Cumulant = 1 - (Tally_Power_Four/Number_Runs)/(3*pow((Tally_Power_Two/Number_Runs),2));
			double Energy = Tally_E/(double)Number_Runs;
			double Heat_Capacity = (((Tally_Energy_Two/(double)Number_Runs)-pow((Tally_E/(double)Number_Runs),2))/((double)Number_Runs*Temperature*Temperature));
			double Heat_Capacity_Over_Temp = (((Tally_Energy_Two/(double)Number_Runs)-pow((Tally_E/(double)Number_Runs),2))/((double)Number_Runs*Temperature*Temperature*Temperature));
			double Susceptibility = ((Tally_Power_Two/(double)Number_Runs) - pow((Tally_M/(double)Number_Runs),2))/((double)Number_Runs*Temperature);

			Output1 << Temperature << "\t" << Magnetism << "\t" << Binder_Cumulant << "\t" << Energy << "\t"<< Heat_Capacity << "\t"<< Susceptibility << "\t"<<  Heat_Capacity_Over_Temp << "\t" << Entropy << endl;

			Entropy = Entropy+(Heat_Capacity_Over_Temp*Set_Interval);

		}


		cout << "Entropy is" << "\t" << Entropy << endl;	
	}
	system("pause");
	return 0;
}