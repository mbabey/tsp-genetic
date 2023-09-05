//
// Created by Maxwell Babey on 11/2/22.
//

#include "../include/Population.hpp"
#include "../include/settings.hpp"
#include <random>

using namespace std;

/**
 * deref_compare
 * <p>
 * Dereference two Tour pointers and compare their values. Used as comparator for sorting a Population's population.
 * Tours are compared based on their fitness.
 * </p>
 * @param t1 - the first Tour *
 * @param t2 - the second Tour *
 * @return - true if *t1 is less than *t2. False otherwise.
 */
bool deref_compare(Tour *t1, Tour *t2);

size_t Population::population_size = DEF_POPULATION_SIZE;

size_t Population::num_parents = DEF_NUMBER_OF_PARENTS;

size_t Population::num_elites = DEF_NUMBER_OF_ELITES;


void Population::sort_population()
{
//    struct deref_compare
//    {
//        bool operator()(Tour *t1, Tour *t2)
//        {
//            return (*t1 < *t2);
//        }
//    };
//    struct deref_compare dc;
//    sort(this->population.begin(), this->population.end(), dc);
    
    sort(this->population.begin(), this->population.end(),
         [](Tour *t1, Tour *t2) -> bool
         {
             return (*t1 < *t2);
         });
//    sort(this->population.begin(), this->population.end(), deref_compare);
}

//bool deref_compare(Tour *t1, Tour *t2)
//{
//    return (*t1 < *t2);
//}

set<Tour *> Population::select_parent_candidates()
{
    set<Tour *> parent_set;
    
    random_device              r;
    mt19937                    gen(r());
    uniform_int_distribution<> dist(static_cast<int>(num_elites),
                                    static_cast<int>(population_size) - 1);
    int                        rand;
    
    while (parent_set.size() < PARENT_POOL_SIZE)
    {
        rand = dist(gen);
        parent_set.insert(this->population[rand]);
    }
    
    return parent_set;
}

vector<Tour *> Population::select_parents(list<set<Tour *>> &parent_candidates)
{
    vector<Tour *> selected_parents;
    
    for (set<Tour *> parent_set : parent_candidates)
    {
        // A set is ordered, so the best-fit parent will always be first.
        selected_parents.push_back(*parent_set.begin());
    }
    
    return selected_parents;
}

Tour *Population::mate_parents(vector<Tour *> &parents)
{
    vector<City *> child_route;
    
    City   *c_curr;
    Tour   *p_current;
    size_t p_curr_index;
    size_t prev_bound;
    bool   can_insert;
    int    p_index;
    
    // Get number of parents bounds. The last bound will be the last index of a tour.
    set<size_t> cross_bounds{get_bounds(num_parents - 1,
                                        0, static_cast<int>(Tour::get_tour_size() - 1))};
    cross_bounds.insert(Tour::get_tour_size());
    
    // For each bound, iterate in the current parent up to that bound
    p_index    = 0;
    prev_bound = 0;
    for (size_t bound : cross_bounds)
    {
        p_current    = parents[p_index];
        p_curr_index = 0;
        for (size_t b_index = prev_bound; b_index < bound;) // For every index in the child route
        {
            can_insert = true;
            c_curr     = p_current->get_city(p_curr_index++); // Not b_index, must be independent index
            
            // Compare each insertion attempt with each element in the child_route
            for (City *c_child : child_route) // O(n^3), yikes
            {
                if (*c_curr == *c_child) // If there is a collision, increment to the next City in the parent.
                {
                    can_insert = false;
                    break;
                }
            }
            
            if (can_insert)
            {
                child_route.push_back(c_curr); // if there is no collision, insert into the child route
                ++b_index;
            }
        }
        
        prev_bound = bound;
    }
    return new Tour(child_route);
}

void Population::crossover()
{
    vector<Tour *> child_tours;
    
    // Cross Tours in the population to generate child Tours.
    for (size_t i = num_elites; i < population_size; ++i)
    {
        list<set<Tour *> > parent_sets;
        vector<Tour *>     parents;
        
        for (size_t parent = 0; parent < num_parents; ++parent)
        {
            parent_sets.push_back(select_parent_candidates());
        }
        parents = select_parents(parent_sets);
        
        child_tours.push_back(mate_parents(parents));
    }
    
    // Replace the old Tours with the child tours.
    for (size_t i = num_elites; i < population_size; ++i)
    {
        Tour *old_tour = population[i];
        population[i] = child_tours[i - num_elites];
        delete old_tour;
    }
}

void Population::mutate()
{
    random_device                     rand;
    mt19937                           gen(rand());
    uniform_real_distribution<double> dist(0, 1);
    
    double prob;
    
    for (size_t i = num_elites; i < population_size; ++i)
    {
        prob = dist(gen);
        if (prob < MUTATION_RATE)
        {
            population[i]->mutate();
        }
    }
}

void Population::set_options(const int *options)
{
    if (*options != -1)
    {
        population_size = *options;
    }
    ++options;
    
    if (*options != -1) // Number of parents to be crossed
    {
        num_parents = *options;
    }
    ++options;
    
    if (*options != -1) // Number of parents to be crossed
    {
        num_elites = *options;
    }
    
}
