//
// Created by Maxwell Babey on 11/2/22.
//

#ifndef LAB1TEMPLATE_SETTINGS_HPP
#define LAB1TEMPLATE_SETTINGS_HPP

/**
 * The upper limit of the X and Y coordinates of a City.
 */
#define MAP_BOUNDARY (double) 1000

/**
 * The default number of Cities in a tour. User may alter.
 */
#define DEF_CITIES_IN_TOUR 32

/**
 * The default number of Tours in a Population. User may alter.
 */
#define DEF_POPULATION_SIZE 32

/**
 * The number of times Cities can be swapped when creating a Tour.
 */
#define SHUFFLES 64

/**
 * The number of algorithm iterations.
 */
#define ITERATIONS 1000

/**
 * The number of parent Tours used to generate each offspring Tour
 */
#define DEF_NUMBER_OF_PARENTS 2

/**
 * The number of parents randomly selected from a population when selecting a parent; the fittest is made the parent.
 */
#define PARENT_POOL_SIZE 5

/**
 * The default number Tours to be selected as best-fit Tours per iteration; these Tours are not changed in the
 * next iteration. User may alter.
 */
#define DEF_NUMBER_OF_ELITES 1

/**
 * The percent chance a City in a Tour is swapped with one of it's neighbouring Cities.
 */
#define MUTATION_RATE (double) 0.25

/**
 * Improvement required for the algorithm to be considered complete. The measure is based on
 * the difference between the distance generated in the initial sample and the most recent elite Tour.
 */
#define IMPROVEMENT_FACTOR (double) 0.10


#endif //LAB1TEMPLATE_SETTINGS_HPP
