//
// Created by Maxwell Babey on 11/2/22.
//

#include "../include/Tour.hpp"
#include "../include/settings.hpp"
#include "../include/Population.hpp"
#include <random>
#include <iostream>

/**
 * swap_cities
 * <p>
 * Swap the City at first_index in the tour with the City at second_index in the tour.
 * </p>
 * @param tour - the tour within which to swap
 * @param first_index - the index of the first City
 * @param second_index - the index of the second City
 */
void swap_cities(vector<City *> &tour, size_t first_index, size_t second_index);

size_t Tour::tour_size = DEF_CITIES_IN_TOUR;

double Tour::get_tour_distance() const
{
    double dist{0};
    
    auto route_end   = this->tour.end();
    auto route_begin = this->tour.begin();
    
    while (route_begin < route_end - 1)
    {
        // The distance between what route_begin is pointing and at what route_begin + 1 is pointing at. Increment route_begin.
        dist += (*route_begin)->get_distance_from(*(++route_begin));
    }
    
    return dist;
}

double Tour::determine_fitness() const
{
    double fitness;
    
    fitness = get_tour_distance() / static_cast<double>(tour_size);
    
    return fitness;
}

Tour *Tour::mutate() // Returns a pointer for convenience
{
    const size_t min_index = 0;
    const size_t max_index = tour_size - 1;
    
    random_device r;
    mt19937       gen(r());
    
    // Get a random number between 1 and tour_size of Cities to choose.
    uniform_int_distribution<> dist(1, static_cast<int>(tour_size));
    int                        num_cities{dist(gen)};
    
    // For each City to choose, randomly select indices. Do not select the first NUM_ELITES Cities.
    set<size_t> swap_indices{get_bounds(num_cities,
                                        static_cast<int>(min_index), static_cast<int>(max_index))};
    
    uniform_int_distribution<> pick_neighbour(0, 1);
    
    int         r_neighbour;
    for (size_t index : swap_indices)  // For each selected index, swap the City at that index with one of the left or right Cities.
    {
        if (index <= min_index) // If the index is the min_index, swap the City at that index with the right City.
        {
            swap_cities(tour, min_index, min_index + 1);
        } else if (index >= max_index) // If the index is the max_index, swap the City at that index with the left City.
        {
            swap_cities(tour, max_index, max_index - 1);
        } else
        {
            r_neighbour = pick_neighbour(gen); // Pick a neighbour.
            if (r_neighbour)
            {
                swap_cities(tour, index, index + 1); // Swap with the right.
            } else
            {
                swap_cities(tour, index, index - 1); // Swap with the left.
            }
        }
    }
    
    return this;
}

set<size_t> get_bounds(size_t num_bounds, int low_lim, int up_lim)
{
    set<size_t> bounds;
    
    random_device              r;
    mt19937                    gen(r());
    uniform_int_distribution<> dist(low_lim, up_lim);
    
    while (bounds.size() < num_bounds) // For each parent except the last, get a bounding index.
    {
        bounds.insert(dist(gen));
    }
    
    return bounds;
}

void swap_cities(vector<City *> &tour, size_t first_index, size_t second_index)
{
    City *temp = tour[first_index];
    tour[first_index]  = tour[second_index];
    tour[second_index] = temp;
}

bool Tour::operator<(const Tour &other) const
{
    return (this->determine_fitness() < other.determine_fitness());
}

ostream &operator<<(ostream &os, const Tour &t)
{
    for (size_t i = 0; i < Tour::tour_size - 1; ++i)
    {
        os << *t.tour[i] << " --> ";
    }
    os << *t.tour[Tour::tour_size - 1];
    
    return os;
}

void Tour::set_options(const int *options)
{
    if (*options != -1) // Number of Cities in a Tour
    {
        tour_size = *options;
    }
}
