#include <string>

class Vector3
{
	public:
		Vector3(double, double, double);
		//Vector3(Vector3);
		Vector3();
		static Vector3 Add(Vector3, Vector3); // addition
		static Vector3 Substract(Vector3, Vector3);
		static Vector3 Cross(Vector3, Vector3); // vector mul
		static double Distance(Vector3, Vector3);
		static Vector3 Divide(Vector3, double);
		static Vector3 Multiply(Vector3, double); //сделать умножение для вектора.
		static double Dot(Vector3, Vector3); // scalar mul
		static Vector3 Reflect(Vector3, Vector3);
		static bool Equality(Vector3, Vector3);
		static Vector3 Rotate122(Vector3, Vector3, double);
		double x();
		double y();
		double z();
		double length();
		Vector3 Opposite();
		Vector3 Normalize();
		Vector3 Positive();
		bool Equals(Vector3);
		std::string toString();
	private:
		double _x;
		double _y;
		double _z;
};
