//
// Created by Maxwell Babey on 11/2/22.
//

#ifndef LAB1TEMPLATE_CITY_HPP
#define LAB1TEMPLATE_CITY_HPP

#include <utility>
#include <iosfwd>

using namespace std;

/**
 * City
 * <p>
 * A City. Possesses x and y coordinates and a unique ID number.
 * </p>
 */
class City
{
public:
    
    /**
     * Constructor
     * <p>
     * Create a City with a unique ID and random coordinates in the range [0, MAP_BOUNDARY)
     * </p>
     */
    City() : id(city_count++), coords()
    {
        coords.first  = generate_rand_coord();
        coords.second = generate_rand_coord();
    }
    
    /**
     * Destructor.
     * <p>
     * Destroy this City.
     * </p>
     */
    ~City() = default;
    
    /**
     * get_distance_from
     * <p>
     * Get the distance of this City from another City by using Pythagoras' big ol' brain.
     * </p>
     * @param other - the city to compare coordinates with
     * @return - the distance
     */
    double get_distance_from(City *other) const;
    
    /**
     * overloaded operator==
     * <p>
     * Check the equality of two this City and another. Two cities are equal if they share an ID.
     * </p>
     * @param other - the City against which to compare
     * @return whether the Cities are equal
     */
    bool operator==(const City &other) const;

    /**
     * operator<<
     * <p>
     * Print the ID number of this city.
     * </p>
     * @param os - the ostream upon which to print
     * @param c - the city to print
     * @return a reference to the ostream printed upon
     */
    friend ostream &operator<<(ostream &os, const City &c);
    
private:
    
    /**
     * Count of the total number of Cities that have been created. Used as the unique ID of each City.
     */
    static int city_count;
    
    /**
     * The unique identifier of this City.
     */
    int id;
    
    /**
     * The (x, y) coordinates of this City. First is x, second is y.
     */
    pair<double, double> coords;
    
    /**
     * generate_rand_coord
     * <p>
     * Generate a random coordinate between 0 and MAP_BOUNDARY
     * </p>
     * @return the randomly generated coordinate
     */
    static double generate_rand_coord();
    
};

#endif //LAB1TEMPLATE_CITY_HPP
