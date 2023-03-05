#define PI 3.141592653589793
#include "vector3.h"
#include <limits>
#include <math.h>
#include <string>

Vector3::Vector3(double x, double y, double z)
{
	_x=x;
	_y=y;
	_z=z;
}

Vector3::Vector3()
{
	_x=0;
	_y=0;
	_z=0;
}

double Vector3::x()
{
	return _x;
}

double Vector3::y()
{
	return _y;
}

double Vector3::z()
{
	return _z;
}

double Vector3::length()
{
    return pow(_x*_x+_y*_y+_z*_z, 0.5);
}

Vector3 Vector3::Add(Vector3 a, Vector3 b) // addition
{
	return Vector3(a.x()+b.x(),a.y()+b.y(),a.z()+b.z());
}

Vector3 Vector3::Substract(Vector3 a, Vector3 b)
{
	return Vector3::Add(a, b.Opposite());
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
    double x = a.y()*b.z() - b.y()*a.z();
    double y = -(a.x()*b.z() - b.x()*a.z());
    double z = a.x()*b.y() - b.x()*a.y();
    return Vector3(x,y,z);
}

double Vector3::Distance(Vector3 a, Vector3 b)
{
	Vector3 s = Vector3::Substract(b, a);
	return s.length();
}

Vector3 Vector3::Multiply(Vector3 a, double t)
{
	return Vector3(a.x()*t, a.y()*t, a.z()*t);
}

Vector3 Vector3::Divide(Vector3 a, double t)
{
	if(std::abs(t) < std::numeric_limits<double>::epsilon()) // тут нужно сравнить с 0?
		throw "Division by zero!";
	return Vector3::Multiply(a, 1/t);
}
double Vector3::Dot(Vector3 a, Vector3 b)
{
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

Vector3 Vector3::Reflect(Vector3 a, Vector3 n)
{
	return Vector3::Substract(a, Vector3::Multiply(n.Normalize(), 2*Vector3::Dot(a,n.Normalize())));
}

bool Vector3::Equality(Vector3 a, Vector3 b)
{
	if(Vector3::Substract(a,b).length() < std::numeric_limits<double>::epsilon())
		return true;
	else return false;
}

Vector3 Vector3::Rotate122(Vector3 a, Vector3 b, double p)
{
	Vector3 n = Vector3::Cross(a,b).Normalize();
    if(a.length() * b.length() * n.length() < std::numeric_limits<double>::epsilon())
		return Vector3(0,0,0);
	while(p < 0)
		p+=2*PI;
	while(p > 2*PI)
		p-=2*PI;
	double x = n.x();
	double y = n.y();
	double z = n.z();
	double a11 = cos(p) + (1-cos(p))*x*x;
	double a12 = (1-cos(p))*x*y - sin(p)*z;
	double a13 = (1-cos(p))*x*z + sin(p)*y;
	double a21 = (1-cos(p))*y*x + sin(p)*z;
	double a22 = cos(p) + (1-cos(p))*y*y;
	double a23 = (1-cos(p))*y*z - sin(p)*x;
	double a31 = (1-cos(p))*z*x - sin(p)*y; 
	double a32 = (1-cos(p))*z*y + sin(p)*x;
	double a33 = cos(p) + (1-cos(p))*z*z;

	double res_x = a11*a.x() + a12*a.y() + a13*a.z();
	double res_y = a21*a.x() + a22*a.y() + a23*a.z();
	double res_z = a31*a.x() + a32*a.y() + a33*a.z();

	return Vector3(res_x, res_y, res_z);
}

bool Vector3::Equals(Vector3 vec)
{
	if((Vector3::x()-vec.x())+(Vector3::y()-vec.y())+(Vector3::z()-vec.z()) < std::numeric_limits<double>::epsilon())
		return true;
	else return false;
}

Vector3 Vector3::Opposite()
{
	return Vector3(-Vector3::x(), -Vector3::y(), -Vector3::z());
}

Vector3 Vector3::Normalize()
{
	if(Vector3::length() < std::numeric_limits<double>::epsilon())
		throw "Normalizing of zero vector!";
	return Vector3(Vector3::x()/Vector3::length(), Vector3::y()/Vector3::length(), Vector3::z()/Vector3::length()); // как правильно через Divide??
}

Vector3 Vector3::Positive()
{
	return Vector3(std::abs(Vector3::x()), std::abs(Vector3::y()), std::abs(Vector3::z()));
}

std::string Vector3::toString()
{
	return "("+std::to_string(Vector3::x())+", "+std::to_string(Vector3::y())+", "+std::to_string(Vector3::z())+")";
}
