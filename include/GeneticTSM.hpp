//
// Created by Maxwell Babey on 11/12/22.
//

#ifndef LAB1TEMPLATE_GENETICTSM_HPP
#define LAB1TEMPLATE_GENETICTSM_HPP

#include "../include/Population.hpp"

/**
 * GeneticTSM
 * <p>
 * A singleton facade class to hide the complexity of running a genetic algorithm to find a solution to the travelling
 * salesman problem. Only a single instance of GeneticTSM may exist. A GeneticTSM may run the genetic travelling
 * salesperson algorithm, which will create a map of Cities, create a Population of Tours from that map, then run a
 * genetic algorithm on that Population.
 * </p>
 */
class GeneticTSM // Singleton Facade
{
private:
    
    /**
     * The set of Cities used in this GeneticTSM.
     */
    vector<City *> map;
    
    /**
     * Pointer to the population used in this GeneticTSM.
     */
    Population *population;
    
    /**
     * create_map
     * <p>
     * Create the set of Cities used in this GeneticTSM.
     * </p>
     */
    void create_map();
    
    /**
     * create_population
     * <p>
     * Create a Population based on a map of Cities. Create num_tours Tours. For each tour in a population: shuffle
     * the Cities in the map, create a Tour with the map, then add the Tour to a vector.
     * This vector will be used to create the Population for this GeneticTSM.
     * </p>
     */
    void create_population();
    
    /**
     * Constructor.
     * <p>
     * Create a GeneticTSM.
     * </p>
     */
    GeneticTSM() : map(), population(nullptr)
    {}
    
public:
    
    /**
     * get_instance
     * <p>
     * Get the instance of this object. If an instance does not yet exist, create one.
     * </p>
     * @return
     */
    static GeneticTSM *get_instance(); // Singleton
    
    /**
     * run_genetic_tsm
     * <p>
     * Run the genetic algorithm to find a solution to the travelling salesman problem.
     * </p>
     */
    void run_genetic_tsm(int argc, char *argv[]); // Facade

    /**
     * Destructor.
     * <p>
     * Destroy each City in this GeneticTSM's map, then destroy this GeneticTSM.
     * </p>
     */
    ~GeneticTSM()
    {
        for (City *c : map)
        {
            delete c;
        }
    }
};

#endif //LAB1TEMPLATE_GENETICTSM_HPP
