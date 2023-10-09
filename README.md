### About
A genetic algorithm solution to the traveling salesperson problem.

The population size, number of cities, number of parents, and number of elites are modifiable by either: modifying the settings.txt file and passing it as a command line argument; or passing no command line arguments and entering the values as prompted.

## Explanation
The algorithm creates a number of Cities, then creates a number of Tours from those Cities. The Tours make up the Population and are sorted by their 'fitness', which is the total distance of the Tour divided by the number of Cities in a Tour; a lower fitness is a better fitness. The Tour with the best fitness is declared an 'Elite.' All Tours that are not Elite are candidates to be 'Parent Tours.' Parent Tours are crossed to produce offspring, which replace all non-elite Tours in the population. Next, the offspring Tours are randomly mutated by swapping the order of the Cities within. Elite Tours will not be involved in the crossing and mutating steps. Once an improvement threshold or an iteration limit is reached, the algorithm stops and prints the resulting best fit Tour.
