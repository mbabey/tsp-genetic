//
// Created by Maxwell Babey on 11/2/22.
//

#include "../include/City.hpp"
#include "../include/settings.hpp"
#include <random>
#include <ostream>

int City::city_count = 0;

double City::generate_rand_coord()
{
    double num;
    
    random_device r;
    mt19937 gen(r());
    uniform_real_distribution<double> dist(0, MAP_BOUNDARY);
    
    num = dist(gen);
    
    return num;
}

double City::get_distance_from(City *other) const
{
    double dist_x;
    double dist_y;
    double dist_actual;
    
    dist_x = abs(this->coords.first - other->coords.first);
    dist_y = abs(this->coords.second - other->coords.second);
    
    dist_actual = sqrt((dist_x * dist_x) + (dist_y * dist_y)); // Pythagorean theorem
    
    return dist_actual;
}

bool City::operator==(const City &other) const
{
    return (this->id == other.id);
}

ostream &operator<<(ostream &os, const City &c)
{
    os << "City " << c.id;
    
    return os;
}
