#include "../include/GeneticTSM.hpp"
#include "../include/settings.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>

/**
 * The number of options.
 */
#define NUM_OPTS 4

/**
 * 100%
 */
#define PERCENT static_cast<double>(100)

/**
 * Ratio of metres to kilometres.
 */
#define M_TO_KM static_cast<int>(1000)

using namespace std;

/**
 * get_improvement_factor
 * <p>
 * Check improvement ratio over baseline against IMPROVEMENT_FACTOR. Return true if the improvement ratio exceeds the
 * IMPROVEMENT_FACTOR, and false otherwise.
 * </p>
 * @param baseline - the baseline to compare against
 * @param fitness - the iteration to compare against the baseline
 * @return true if IMPROVEMENT_FACTOR has been met, false otherwise.
 */
inline double get_improvement_factor(double baseline, double fitness);

/**
 * shuffle
 * <p>
 * Shuffle the Cities in a vector of Cities.
 * </p>
 * @param map - the vector to shuffle.
 */
void shuffle(vector<City *> &map);

/**
 * print_iteration_data
 * <p>
 * Print information about each iteration of the genetic algorithm to the specified output stream.
 * </p>
 * @param os - the output stream
 * @param population - the population being manipulated by the genetic algortihm
 * @param iteration - the iteration number
 * @param iter_fitness - the fitness of the current iteration
 * @param prev_iter_fitness - the fitness of the previous iteration
 */
void print_iteration_data(ostream &os, Population *population, int iteration,
                          double baseline, double iter_fitness, double prev_iter_fitness);

/**
 * print_run_data
 * <p>
 * Print information about the final state of the genetic algorithm to the specified output stream.
 * </p>
 * @param os - the output stream
 * @param base_tour - the most elite tour before the algorithm began
 * @param final_tour - the most elite tour after the algorithm finished
 * @param iteration - the final number of iterations
 * @param baseline - the baseline fitness
 * @param iter_fitness - the fitness of the current iteration
 */
void print_run_data(ostream &os, Tour *base_tour, Tour *final_tour, int iteration,
                    double baseline, double iter_fitness);

/**
 * clean_cin
 * <p>
 * Clean the input buffer.
 * </p>
 */
inline void clean_cin();

/**
 * set_options
 * <p>
 * Get settings input from a file if it exists or user input otherwise. The user may decide to use the default settings
 * or to input settings themselves. Settings that are mutable include:
 * <ul>
 * <li>Number of Tours in the Population,</li>
 * <li>Number of Cities in a Tour,</li>
 * <li>Number of parent Tours crossed when creating child Tours in each iteration, and</li>
 * <li>Number of Tours considered to be 'elite' in each iteration.</li>
 * </ul>
 * </p>
 * @param argc - the number of command line arguments
 * @param argv - the command line arguments
 */
void set_options(int argc, char *argv[]);

/**
 * get_file_input
 * <p>
 * Get input for options from a file. Scan the file line by line, then word by word on each line. When an integer is
 * found, store it at the address pointed to by options, then increment the address.
 * </p>
 * @param options - array storing options values
 */
void get_file_input(int *options, const char *filename);

/**
 * get_user_input
 * <p>
 * Get input for options from a user. The user may decide to use the defaults or they may decide to enter each
 * option individually.
 * </p>
 * @param options - array storing options values
 */
void get_user_input(int *options);

GeneticTSM *GeneticTSM::get_instance()
{
    static GeneticTSM sf;
    return &sf;
}

void GeneticTSM::run_genetic_tsm(int argc, char *argv[])
{
    set_options(argc, argv);
    create_population();
    
    const double baseline{population->get_best_fitness()}; // This will sort the population.
    Tour         *base_tour = new Tour(*population->get_tour_at_index(0));
    double       iter_fitness{baseline};
    double       prev_iter_fitness;
    
    int iteration = 0;
    for (; get_improvement_factor(baseline, iter_fitness) < IMPROVEMENT_FACTOR
           && iteration < ITERATIONS; ++iteration)
    {
        prev_iter_fitness = iter_fitness;
        
        population->crossover();
        
        population->mutate();
        
        iter_fitness = population->get_best_fitness(); // This will sort the population.
        
        print_iteration_data(cout, population, iteration, baseline, iter_fitness, prev_iter_fitness);
    }
    
    print_run_data(cout, base_tour, population->get_tour_at_index(0), iteration, baseline, iter_fitness);
    
    delete population;
}

void print_iteration_data(ostream &os, Population *population, int iteration,
                          double baseline, double iter_fitness, double prev_iter_fitness)
{
    os << "--- Iteration: " << (iteration + 1) << " ---" << endl
       << "Best fitness this iteration: " << iter_fitness << endl
       << "Improvement above baseline: "
       << get_improvement_factor(baseline, iter_fitness) * PERCENT << "%" << endl;
    
    if (iter_fitness != prev_iter_fitness) // If the fitness has changed since the last iteration.
    {
        os << "New elite found!" << endl;
        for (size_t i = 0; i < Population::get_num_elites(); ++i)
        {
            os << "Elite tour " << (i + 1) << " distance: "
               << population->get_tour_at_index(i)->get_tour_distance() / M_TO_KM << " km" << endl;
        }
    } else
    {
        os << "No new elite found." << endl;
        for (size_t i = 0; i < Population::get_num_elites(); ++i)
        {
            os << "Elite tour " << (i + 1) << " distance: "
               << population->get_tour_at_index(i)->get_tour_distance() / M_TO_KM << " km" << endl;
        }
        os << "Best non-elite tour distance: "
           << population->get_tour_at_index(Population::get_num_elites())->get_tour_distance() / M_TO_KM << " km" << endl;
    }
    
    os << endl;
}

void print_run_data(ostream &os, Tour *base_tour, Tour *final_tour, int iteration,
                    double baseline, double iter_fitness)
{
    double improvement{get_improvement_factor(baseline, iter_fitness)};
    
    os << "---- Algorithm finished after " << iteration << " iterations ----" << endl
    << "Baseline fitness: " << baseline << endl
    << "Baseline route: " << *base_tour << endl
    << "Baseline route distance: " << base_tour->get_tour_distance() / M_TO_KM << " km" << endl
    << "Final fitness: " << iter_fitness << endl
    << "Final route: " << *final_tour << endl
    << "Final route distance " << final_tour->get_tour_distance() / M_TO_KM << " km" <<  endl
    << "Improvement over baseline: " << improvement * PERCENT << "%" << endl
    << "Improvement factor " << ((improvement > IMPROVEMENT_FACTOR) ? "exceeded!" : "not exceeded.") << endl;
}

inline double get_improvement_factor(double baseline, double fitness)
{
    return (abs((fitness - baseline) / baseline));
}

void GeneticTSM::create_map()
{
    for (size_t i = 0; i < Tour::get_tour_size(); ++i)
    {
        map.push_back(new City());
    }
}

void GeneticTSM::create_population()
{
    vector<Tour *> population_vector;
    
    create_map();
    
    for (size_t i = 0; i < Population::get_population_size(); ++i)
    {
        shuffle(map);
        Tour *new_tour{new Tour(map)};
        population_vector.push_back(new_tour);
    }
    
    population = new Population(population_vector);
}

void shuffle(vector<City *> &map)
{
    random_device              rand;
    mt19937                    gen(rand());
    uniform_int_distribution<> dist(0, static_cast<int>(Tour::get_tour_size() - 1));
    
    for (int i = 0; i < SHUFFLES; ++i)
    {
        // Get two random indices.
        size_t index1{static_cast<size_t>(dist(gen))};
        size_t index2{static_cast<size_t>(dist(gen))};
        
        // Swap the cities at those indices.
        City *temp{map[index1]};
        map[index1] = map[index2];
        map[index2] = temp;
    }
}

inline void clean_cin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void set_options(int argc, char *argv[])
{
    int      *options = new int[NUM_OPTS];
    for (int i        = 0; i < NUM_OPTS; ++i)
    {
        *(options + i) = -1;
    }
    
    if (argc > 1)
    {
        get_file_input(options, argv[1]);
    } else
    {
        get_user_input(options);
    }
    
    Tour::set_options(options);
    Population::set_options(options + 1);
    
    delete[] options;
}

void get_file_input(int *options, const char *filename)
{
    ifstream     file{filename};
    string       line;
    string       word;
    stringstream line_parse;
    
    while (getline(file, line))
    {
        line_parse << line;
        while (!line_parse.eof())
        {
            line_parse >> word;
            if (stringstream(word) >> *options)
            {
                ++options;
                break;
            }
        }
        line_parse.clear();
    }
}

void get_user_input(int *options)
{
    string input;
    
    cout << "Would you like to use the default settings? (y/n):";
    cin >> input;
    clean_cin();
    
    if (input == "y")
    {
        return;
    }
    
    cout << "Enter number of cities in a tour: ";
    cin >> *options++;
    clean_cin();
    
    cout << "Enter number of tours in the population: ";
    cin >> *options++;
    clean_cin();
    
    cout << "Enter number of tours to be saved as 'elites' in each iteration: ";
    cin >> *options++;
    clean_cin();
    
    cout << "Enter number of parents to be crossed in each iteration: ";
    cin >> *options;
    clean_cin();
}
