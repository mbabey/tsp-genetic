//
// Created by Maxwell Babey on 11/2/22.
//

#ifndef LAB1TEMPLATE_TOUR_HPP
#define LAB1TEMPLATE_TOUR_HPP

#include "City.hpp"
#include <vector>
#include <set>

using namespace std;

/**
 * Tour
 * <p>
 * A Tour of Cities. Contains functions to retrieve the total distance traveled, specific Cities in the route, and the
 * fitness of the Tour. A Tour may be mutated, which will randomly swap the Cities within. Tours are compared by their
 * fitness, which is the normalized distance of the Tour (distance / number of Cities).
 * </p>
 */
class Tour
{
public:

    /**
     * Constructor
     * <p>
     * Create a Tour with a list of Cities.
     * </p>
     * @param route - the list of Cities on this Tour.
     */
    explicit Tour(vector<City *> route) : tour(std::move(route))
    {}
    
    /**
     * Copy constructor.
     * <p>
     * Copy a Tour to create a new Tour.
     * </p>
     * @param t the tour to be copied
     */
    Tour(Tour &t) = default;
    
    /**
     * Destructor
     * <p>
     * Destroy this Tour.
     * </p>
     */
    ~Tour() = default;
    
    /**
     * get_tour_distance
     * <p>
     * Get the total distance traveled in this Tour from the first City on the tour to the last City on the tour.
     * </p>
     * @return the distance traveled
     */
    double get_tour_distance() const; // NOLINT : can discard
    
    /**
     * get_city
     * <p>
     * Get a pointer to the City at an index.
     * </p>
     * @param index - index of the City to get
     * @return the City pointer
     */
    City *get_city(size_t index)
    {
        return tour[index];
    }
    
    /**
     * determine_fitness
     * <p>
     * Determine the fitness of this Tour. Fitness is calculated as distance traveled / number of cities in this Tour.
     * </p>
     * @return
     */
    double determine_fitness() const; // NOLINT : can discard
    
    /**
     * mutate
     * <p>
     * Randomly choose a number of Cities randomly to be swapped with a random adjacent City. so random XD
     * </p>
     * @return a pointer to this mutated Tour
     */
    Tour *mutate();
    
    /**
     * operator<
     * <p>
     * Overloaded less-than operator: compare this Tour and another based on their fitness.
     * </p>
     * @param other - the Tour against which to compare this Tour.
     * @return - True if this Tour's fitness is less than other Tour's fitness, false otherwise.
     */
    bool operator<(const Tour &other) const;
    
    /**
     * operator<<
     * <p>
     * Print the sequence in which Cities are visited in this Tour.
     * </p>
     * @param os - the ostream on which to output
     * @param t - the Tour from which to print the Cities
     * @return a reference to the ostream.
     */
    friend ostream &operator<<(ostream &os, const Tour &t);
    
    /**
     * set_options
     * <p>
     * Override the default options for all Tours. Options include the size of a Tour, the number of parents crossed
     * when making a child Tour, and the number of elites saved in each Tour in each iteration.
     * </p>
     * @param options - pointer to an array containing options values.
     */
    static void set_options(const int *options);
    
    /**
     * get_tour_size
     * <p>
     * Get the size of a Tour.
     * </p>
     * @return the size of a Tour
     */
    static size_t get_tour_size()
    {
        return tour_size;
    }
    
private:
    
    /**
     * The path taken on this Tour.
     */
    vector<City *> tour;
    
    /**
     * The size of a tour.
     */
    static size_t tour_size;
};

/**
 * get_bounds
 * <p>
 * Randomly select num_bounds unique unsigned integers between low_lim and up_lim. Return the set of those values.
 * Used by Tour and Population, so available to both, here.
 * </p>
 * @param num_bounds - the number of bounds to generate
 * @param low_lim - the minimum for the random bounds
 * @param up_lim - the maximum for the random bounds
 * @return - a set of unsigned integer bounds
 */
set<size_t> get_bounds(size_t num_bounds, int low_lim, int up_lim);

#endif //LAB1TEMPLATE_TOUR_HPP
