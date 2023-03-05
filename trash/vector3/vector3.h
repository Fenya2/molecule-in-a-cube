struct vector3
{
    double x;
    double y;
    double z;
    vector3();
    vector3(double, double, double);
};
vector3 add(vector3, vector3);
vector3 mul_scalar(vector3, double);
vector3 normalize_vector3(vector3);
vector3 vector3_multiplication_of(vector3, vector3);
vector3 normal_for(vector3, vector3);
vector3 rotate_vector3_to(vector3, vector3, double); 
vector3 opposite_vector3(vector3);
vector3 reflect(vector3, vector3); 
double scalar_multiplication_of(vector3, vector3);
double length_of_vector3(vector3);
double mixed_multiplication_of(vector3, vector3, vector3);
void print_vector3(vector3);
