#include "./vector3/vector3.h"
#include <limits>
#include <string>
#include <iostream>

struct plane
{
	double A;
	double B;
	double C;
	double D;
	Vector3 n;
	plane(double, double, double, double, Vector3);
	bool pointBelongs(Vector3 p);
	std::string toString();
};

struct straight
{
	plane* f1;
	plane* f2;
	Vector3 n;
	straight(plane*, plane*);
	bool pointBelongs(Vector3);
};

struct vertex
{
	plane* f1;
	plane* f2;
	plane* f3;
	Vector3 n;
	vertex(plane*, plane*, plane*);
	bool pointBelongs(Vector3 p);
};

Vector3 movePoint(Vector3, Vector3, double);
bool isParallel(Vector3, plane);
void makeInput(Vector3&, Vector3&, double&);
double getT(Vector3, Vector3, plane);
Vector3 getCollisionPoint(Vector3, Vector3, plane);

int main()
{
	plane cubeFaces[6] = 
	{
		plane(1,0,0,0, Vector3(1,0,0)),		// x = 0	[0] 
		plane(0,1,0,0, Vector3(0,1,0)),		// y = 0	[1]
		plane(0,0,1,0, Vector3(0,0,1)),		// z = 0	[2]
		plane(1,0,0,-1, Vector3(-1,0,0)),	// x-1 = 0	[3]
		plane(0,1,0,-1, Vector3(0,-1,0)),	// y-1 = 0	[4]
		plane(0,0,1,-1, Vector3(0,0,-1))	// z-1 = 0	[5]
	};
	
	straight cubeStraights[12] = 
	{
		straight(&cubeFaces[0], &cubeFaces[5]),
		straight(&cubeFaces[1], &cubeFaces[5]),
		straight(&cubeFaces[3], &cubeFaces[5]),
		straight(&cubeFaces[4], &cubeFaces[5]),
		straight(&cubeFaces[0], &cubeFaces[1]),
		straight(&cubeFaces[1], &cubeFaces[3]),
		straight(&cubeFaces[3], &cubeFaces[4]),
		straight(&cubeFaces[0], &cubeFaces[4]),
		straight(&cubeFaces[0], &cubeFaces[2]),
		straight(&cubeFaces[2], &cubeFaces[4]),
		straight(&cubeFaces[2], &cubeFaces[3]),
		straight(&cubeFaces[1], &cubeFaces[2])
	};
	
	vertex cubeVertices[8] = 
	{
		vertex(&cubeFaces[3], &cubeFaces[4], &cubeFaces[5]),
		vertex(&cubeFaces[2], &cubeFaces[3], &cubeFaces[4]),
		vertex(&cubeFaces[0], &cubeFaces[2], &cubeFaces[4]),
		vertex(&cubeFaces[0], &cubeFaces[4], &cubeFaces[5]),
		vertex(&cubeFaces[1], &cubeFaces[2], &cubeFaces[3]),
		vertex(&cubeFaces[1], &cubeFaces[3], &cubeFaces[5]),
		vertex(&cubeFaces[0], &cubeFaces[1], &cubeFaces[2]),
		vertex(&cubeFaces[0], &cubeFaces[1], &cubeFaces[5])
	};

	Vector3 pos;
	Vector3 velocity;
	double time;
	makeInput(pos, velocity, time);
	const double speed = velocity.length();
	int boundNum;
	double dtime;
	int boundCnt = 0;
	bool bound;
	
	while(1)
	{
		dtime=std::numeric_limits<double>::max();
		for(int i = 0; i < 6; ++i)
		{
			if(isParallel(velocity, cubeFaces[i]))
				continue;
			double ttm = getT(pos, velocity, cubeFaces[i]);
			if(ttm < 0)
				continue;
			if(std::abs(ttm) < std::numeric_limits<double>::epsilon())
				continue;
			if(ttm < dtime)
			{
				dtime = ttm;
				boundNum = i;
			}
		}
		if(time <= dtime)
		{
			pos = movePoint(pos, velocity, time);
			time = 0;
			break;
		}
		pos = movePoint(pos, velocity, dtime);
		bound = false;
		if(!bound)
		{
			for(int i = 0; i < 8; ++i)
			{
				if(cubeVertices[i].pointBelongs(pos))
				{
					velocity = Vector3::Reflect(velocity, cubeVertices[i].n);
					bound = true;
					break;
				}
			}
		}
		if(!bound)
		{
			for(int i = 0; i < 12; ++i)
			{
				if(cubeStraights[i].pointBelongs(pos))
				{
					velocity = Vector3::Reflect(velocity, cubeStraights[i].n);
					bound = true;
					break;
				}
			}
		}
		if(!bound)
			velocity = Vector3::Reflect(velocity, cubeFaces[boundNum].n);
		time-=dtime;
	}
	std::cout << pos.toString() << std::endl;
	return 0;
}

void makeInput(Vector3& pos, Vector3& velocity, double& t)
{
	double x;
	double y;
	double z;

	std::cout << "start position: "; std::cin >> x >> y >> z;
	if(x <= 0 || x >= 1)
		throw "Error input.";
	if(y <= 0 || y >= 1)
		throw "Error input.";
	if(z <= 0 || z >= 1)
		throw "Error input.";
	pos = Vector3(x, y, z);
	std::cout << "start velocity: "; std::cin >> x >> y >> z;
	if(x == 0 && y == 0 && z==0)
		throw "Error input.";
	velocity = Vector3(x, y, z);
	std::cout << "time: "; std::cin >> t;
	if(t <= 0)
		throw "Error input.";
}

Vector3 movePoint(Vector3 spos, Vector3 v, double t)
{
	return Vector3::Add(spos, Vector3::Multiply(v, t));
}

bool isParallel(Vector3 v, plane p)
{
	if(std::abs(Vector3::Dot(p.n, v)) < std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}

double getT(Vector3 pos, Vector3 v, plane p)
{
	double M = p.A*pos.x() + p.B*pos.y() + p.C*pos.z() + p.D;
	double R = p.A*v.x() + p.B*v.y() + p.C*v.z();
	return -M/R;
}

Vector3 getCollisionPoint(Vector3 pos, Vector3 v, plane p)
{
	double t = getT(pos, v, p);
	double x = pos.x() + v.x()*t;
	double y = pos.y() + v.y()*t;
	double z = pos.z() + v.z()*t;
	return Vector3(x,y,z);
}

plane::plane(double A1, double B1, double C1, double D1, Vector3 n1)
{
	A = A1;
	B = B1;
	C = C1;
	D = D1;
	n = n1;
}

bool plane::pointBelongs(Vector3 p)
{
	if(std::abs(A*p.x()+B*p.y()+C*p.z()+D) < std::numeric_limits<double>::epsilon())
		return true;
	else 
		return false;
}

std::string plane::toString()
{
	return "(" + std::to_string(A) + ")" + "x"
	+ "+" + "(" + std::to_string(B) + ")" + "y"
	+ "+" + "(" + std::to_string(C) + ")" + "z"
	+ "+" + "(" + std::to_string(D) + ")=0";
}

straight::straight(plane* p1, plane* p2)
{
	f1 = p1;
	f2 = p2;
	Vector3 sum = Vector3::Add((*p1).n, (*p2).n);
	n = sum.Normalize();
}

bool straight::pointBelongs(Vector3 p)
{
	if
	(
		std::abs((*f1).A*p.x()+(*f1).B*p.y()+(*f1).C*p.z()+(*f1).D) < std::numeric_limits<double>::epsilon() &&
		std::abs((*f2).A*p.x()+(*f2).B*p.y()+(*f2).C*p.z()+(*f2).D) < std::numeric_limits<double>::epsilon()
	)
	return true;
	else return false;
}

vertex::vertex(plane* p1, plane* p2, plane* p3)
{
	f1 = p1;
	f2 = p2;
	f3 = p3;
	Vector3 sum = Vector3::Add((*p1).n, Vector3::Add((*p2).n, (*p3).n));
	n = sum.Normalize();
}

bool vertex::pointBelongs(Vector3 p)
{
	if
	(
		std::abs((*f1).A*p.x()+(*f1).B*p.y()+(*f1).C*p.z()+(*f1).D) < std::numeric_limits<double>::epsilon() &&
		std::abs((*f2).A*p.x()+(*f2).B*p.y()+(*f2).C*p.z()+(*f2).D) < std::numeric_limits<double>::epsilon() &&
		std::abs((*f3).A*p.x()+(*f3).B*p.y()+(*f3).C*p.z()+(*f3).D) < std::numeric_limits<double>::epsilon()
	)
	return true;
	else return false;
}
