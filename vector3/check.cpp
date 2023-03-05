#include "vector3.h"
#include <iostream>
#include <limits>

int main()
{
	Vector3 a = Vector3(1,2,3);
	Vector3* b = new Vector3(4,5,6);
	std::cout << a.toString() << std::endl;
	std::cout << (*b).toString() << std::endl;
	delete b;
	return 0;
}
