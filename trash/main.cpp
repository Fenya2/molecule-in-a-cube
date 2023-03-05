#include <iostream>
#include "./vector3/vector3.h"
#include <limits>

vector3 movePoint(vector3 startPos, vector3 velocity, double time)
{
	return add(startPos, mul_scalar(velocity ,time));
}

class plane
{
	public:
		double A;
		double B;
		double C;
		double D;
		vector3 n;
		plane(double A, double B, double C, double D, vector3 n)
		{
			this->A = A;
			this->B = B;
			this->C = C;
			this->D = D;
			this->n = n;
		}
		void print()
		{
			std::cout << "(" << A << ")" << "x"
			<< "+" << "(" << B << ")" << "y"
			<< "+" << "(" << C << ")" << "z"
			<< "+" << "(" << D << ")=0" << std::endl;
			print_vector3(n);
			return;
		}
};

bool isParalel(vector3 vec, plane p)
{
	if(p.A*vec.x + p.B*vec.y + p.C*vec.z < std::numeric_limits<double>::epsilon())
		return true;
	return false;
}

bool velocityIsCodirectional(vector3 sp, vector3 v, plane p)
{
	if (-(p.A*sp.x + p.B*sp.y + p.C*sp.z + p.D)/(p.A*v.x + p.B*v.y + p.C*v.z) < 0)
		return false;
	return true;
}

vector3 getCollisionPoint(vector3 sp, vector3 v, plane p)
{
	double t = -(p.A*sp.x + p.B*sp.y + p.C*sp.z + p.D)/(p.A*v.x + p.B*v.y + p.C*v.z);
	double x = sp.x + v.x*t;
	double y = sp.y + v.y*t;
	double z = sp.z + v.z*t;
	return vector3(x,y,z);
}

double getTimeToCollision(vector3 sp, vector3 v, plane p)
{
	double vL = length_of_vector3(v);
	vector3 colPoint = getCollisionPoint(sp, v, p);
	vector3 s = add(colPoint, mul_scalar(sp, -1));
	double sL = length_of_vector3(s);
	return sL/vL;
}

int main()
{
	double x;
	double y;
	double z;
	double t;

	std::cout << "start position: ";
	std::cin >> x >> y >> z;
	if(x <= 0 || x >= 1)
	{
		std::cout << "error input." << std::endl;
		return 1;
	}
	if(y <= 0 || y >= 1)
	{
		std::cout << "error input." << std::endl;
		return 1;
	}
	if(z <= 0 || z >= 1)
	{
		std::cout << "error input." << std::endl;
		return 1;
	}
	vector3 pos = vector3(x, y, z);
	std::cout << "start velocity: ";
	std::cin >> x >> y >> z;
	vector3 velocity = vector3(x, y, z);
	std::cout << "time: "; std::cin >> t;
	if(t <= 0)
	{
		std::cout << "error input" << std::endl;
		return 1;
	}


	plane cube[] = 
	{
		plane(1,0,0,0, vector3(1,0,0)), 
		plane(0,1,0,0, vector3(0,1,0)),
		plane(0,0,1,0, vector3(0,0,1)),
		plane(1,0,0,-1, vector3(-1,0,0)),
		plane(0,1,0,-1, vector3(0,-1,0)),
		plane(0,0,1,-1, vector3(0,0,-1))
	};
	double tMin;
	double tCur;
	int bound;
	int debug;
	while(t > std::numeric_limits<double>::epsilon())
	{
		tMin = std::numeric_limits<double>::max();
		for(int i = 0; i < 6; ++i)
		{
			if(!isParalel(velocity, cube[i]) && velocityIsCodirectional(pos, velocity, cube[i]))
			{
				tCur = getTimeToCollision(pos, velocity, cube[i]);
				if(tCur < std::numeric_limits<double>::epsilon())
					continue;
				std::cout << "tCur=" << tCur << std::endl;
				if(tCur < tMin)
				{
					tMin = tCur;
					bound = i;
				}
			}
		}
		if(t < tMin) // here
		{
			pos = movePoint(pos, velocity, t);
			t=0;
			continue;
		}
		t-=tMin;
		velocity = reflect(velocity, cube[bound].n);
		std::cout << "bound:" << std::endl;
		print_vector3(pos);
		std::cout << "time: " << t << std::endl;
		print_vector3(velocity);
	}
	std::cout << "s(t):" << std::endl;
	print_vector3(pos);
}
