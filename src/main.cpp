#include "../include/GeneticTSM.hpp"
#include <cstdlib>

int main(int argc, char *argv[])
{
    GeneticTSM *genetic_tsm = GeneticTSM::get_instance();
    genetic_tsm->run_genetic_tsm(argc, argv);
    
    return EXIT_SUCCESS;
}
