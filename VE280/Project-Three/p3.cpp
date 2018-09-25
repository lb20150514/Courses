#include "simulation.h"

using namespace std;

int main (int argc, char * argv[])
{
    bool verbose = false;

    //Part I: File Input
    //  Error message 1: Missing arguments
    try
    {
        if (argc < 4)
            throw 1;
    }
    catch (int i)
    {
        cout << "Error: Missing arguments!\n";
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]\n";
        return 0;
    }

    string speciesFile = argv[1];
    string worldFile = argv[2];
    int rounds = atoi(argv[3]);
    int simulateRound = 1;

    //Error message 2: Negative rounds
    try
    {
        if (rounds < 0)
            throw 2;
    }
    catch (int i)
    {
        cout << "Error: Number of simulation rounds is negative!\n";
        return 0;
    }

    //  Initialize verbose
    if (argc >= 5)
    {
        string temp = argv[4];
        verbose = (temp=="v" || temp == "verbose");
    }

    world_t world;

    for (unsigned int i = 0; i < MAXCREATURES; i ++)
    {
        world.creatures[i].species = NULL;
    }
    for (unsigned int i = 0; i < MAXHEIGHT; i ++)
    {
        for (unsigned int j = 0; j < MAXWIDTH; j++)
            world.grid.squares[i][j] = NULL;
    }

    //  Initialize world and check errors
    try
    {
        initWorld(world, speciesFile, worldFile);
    }
    catch (string name)
    {
        cout << "Error: Cannot open file " << name <<"!\n";
        return 0;
    }
    catch (unsigned int ui)
    {
        switch (ui)
        {
            case MAXSPECIES: //Error message 4
            {
                cout << "Error: Too many species!\n";
                cout << "Maximal number of species is " << MAXSPECIES << ".\n";
                break;
            }
            case MAXCREATURES: //Error message 10
            {
                cout << "Error: Too many creatures!\n";
                cout << "Maximal number of creatures is " << MAXCREATURES << ".\n";
                break;
            }
            default: break;
        }
        return 0;
    }
    catch (int i)
    {
        return 0;
    }
    catch (species_t spec) //Error message 5
    {
        cout << "Error: Too many instructions for species " << spec.name << "!\n";
        cout << "Maximal number of instructions is " << MAXPROGRAM << ".\n";
        return 0;
    }

   unsigned int skip[MAXCREATURES] = {0}; 
    
   //  initial state of the world
    cout << "Initial state\n";
    printGrid(world.grid);

    //  simulation
    while (simulateRound <= rounds)
    {
        unsigned int num = 0;
        cout << "Round " << simulateRound << "\n";
        for (unsigned int creatNum = 0; creatNum < world.numCreatures; creatNum ++)
        {
            if (skip[creatNum] == 0 && world.creatures[creatNum].hillActive == true && !world.creatures[creatNum].ability[FLY])
            {
                skip[creatNum] = 1;
                num ++;
            }
            else
            {
                cout << printCreature(world.creatures[creatNum]) << " takes action:";
                simulateCreature(world.creatures[creatNum], world.grid, verbose);
                skip[creatNum] = 0;
                if (world.grid.terrain[world.creatures[creatNum].location.r][world.creatures[creatNum].location.c] == HILL)
                    world.creatures[creatNum].hillActive = true;
                else world.creatures[creatNum].hillActive = false;
            }
        }
        if (! verbose || num == world.numCreatures)
            printGrid(world.grid);
        simulateRound ++;
    }
    return 0;
}
