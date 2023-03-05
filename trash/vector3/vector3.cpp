#define PI 3.141592653589793

#include "vector3.h"
#include <math.h>
#include <iostream>
#include <limits>

vector3::vector3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vector3::vector3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

vector3 add(vector3 a, vector3 b)
{
    vector3 sum; 
    sum.x = a.x+b.x;
    sum.y = a.y+b.y;
    sum.z = a.z+b.z;
    return sum;
}

vector3 mul_scalar(vector3 a, double s)
{
    vector3 res;
    res.x = s * a.x;
    res.y = s * a.y;
    res.z = s * a.z;
    return res;
}

vector3 opposite_vector3(vector3 vec)
{
	return mul_scalar(vec, -1);
}

vector3 reflect(vector3 vec, vector3 n)
{
	return add(mul_scalar(normalize_vector3(n), 2*scalar_multiplication_of(vec, n)), opposite_vector3(vec));
}

double scalar_multiplication_of(vector3 a, vector3 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

double length_of_vector3(vector3 vec)
{
    return pow(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z, 0.5);
}

vector3 normalize_vector3(vector3 vec)
{
    double length = length_of_vector3(vec);
    if(length < std::numeric_limits<double>::epsilon())
        return vector3();
    vector3 res = vector3(vec.x/length, vec.y/length, vec.z/length);
    return res;
}

vector3 vector3_multiplication_of(vector3 a, vector3 b)
{
    if(length_of_vector3(a) * length_of_vector3(b) < std::numeric_limits<double>::epsilon())
        return vector3();
    vector3 res;
    res.x = a.y*b.z - b.y*a.z;
    res.y = -(a.x*b.z - b.x*a.z);
    res.z = a.x*b.y - b.x*a.y;
    return res;
}

vector3 normal_for(vector3 a, vector3 b)
{
    return normalize_vector3(vector3_multiplication_of(a,b));
}

vector3 rotate_vector3_to(vector3 a, vector3 b, double p)
{
	vector3 n = normalize_vector3(vector3_multiplication_of(a,b));
    if(length_of_vector3(a) * length_of_vector3(b) * length_of_vector3(n) < std::numeric_limits<double>::epsilon())
		return vector3(0,0,0);
	while(p < 0)
		p+=2*PI;
	while(p > 2*PI)
		p-=2*PI;
	double x = n.x;
	double y = n.y;
	double z = n.z;
	double a11 = cos(p) + (1-cos(p))*x*x;
	double a12 = (1-cos(p))*x*y - sin(p)*z;
	double a13 = (1-cos(p))*x*z + sin(p)*y;
	double a21 = (1-cos(p))*y*x + sin(p)*z;
	double a22 = cos(p) + (1-cos(p))*y*y;
	double a23 = (1-cos(p))*y*z - sin(p)*x;
	double a31 = (1-cos(p))*z*x - sin(p)*y; 
	double a32 = (1-cos(p))*z*y + sin(p)*x;
	double a33 = cos(p) + (1-cos(p))*z*z;

	double res_x = a11*a.x + a12*a.y + a13*a.z;
	double res_y = a21*a.x + a22*a.y + a23*a.z;
	double res_z = a31*a.x + a32*a.y + a33*a.z;

	return vector3(res_x, res_y, res_z);	
}

double mixed_multiplication_of(vector3 a, vector3 b, vector3 c)
{
    return scalar_multiplication_of(vector3_multiplication_of(a,b), c);
}

void print_vector3(vector3 vec)
{
    std::cout << 
    "(" 
    << vec.x << ", " 
    << vec.y << ", " 
    << vec.z << 
    ")" 
    << std::endl;
    return;
}
