#include "simulation.h"

using namespace std;

unsigned int find_Name(const string &instruct, const string *Name, const int len)
{
    for (int i = 0; i < len; i ++)
    {
        if (*Name == instruct)
            return i;
        Name ++;
    }
    return len;
}

bool checkBound(point_t location, unsigned int height, unsigned int width)
{
    if (location.r < (int) height && location.c < (int) width)
    {
        if (location.r >= 0 && location.c >= 0)
            return true;
    }
    return false;
}

string printCreature(const creature_t &creature)
{
    string creat = "Creature (" + (*creature.species).name + " " + directName[creature.direction];
    creat = creat + " " + to_string(creature.location.r) + " " + to_string(creature.location.c) + ")";
    return creat;
}

void initWorld(world_t &world, const string &speciesFile, const string &worldFile)
{
    unsigned int speciesNum = 0, creatureNum = 0;
    int h = 0, w = 0;
    string spdir, speciesdir, spline;
    ifstream spFile, cFile, wFile;

    //Part I
    //  get information from species file
    spFile.open(speciesFile);

    //  Error message 3
    if (! spFile)
        throw speciesFile;

    getline(spFile, spdir);
    istringstream specdir(spdir);
    specdir >> speciesdir;

    //  get numSpecies, Species.name from speciesFile
    while (spFile)
    {
        spFile >> spline;

        //Error message 4: species number exceeds
        if (speciesNum > MAXSPECIES)
            throw MAXSPECIES;

        if (spline == "")
            break;
        else
        {  
            world.species[speciesNum].name = spline;
            speciesNum ++;
        }
    }
    world.numSpecies = speciesNum;
    spFile.close();
    
    //Part 2
    //  get information from files named with species name
    for (unsigned int i = 0; i < speciesNum; i ++)
    {
        string fileDir = speciesdir + "/" + world.species[i].name;
        cFile.open(fileDir);
        //  Error message 3
        if (! cFile)
            throw fileDir;

        //  get species.programSize, species.program
        unsigned int programNum = 0;
        string instructLine, preinstructLine;
        while (cFile)
        { 
            getline(cFile, instructLine);
            if (preinstructLine != instructLine)
                preinstructLine = instructLine;
            else break;

            //Error message 5: insturction number exceeds
            if (programNum > MAXPROGRAM)
                throw world.species[i];

            string pinstruction;
            if (instructLine != "" && instructLine.length() != 0)
            {
                unsigned int instructTemp;
                istringstream in(instructLine);
                in >> pinstruction;
                instructTemp = find_Name(pinstruction, &opName[0], OP_SIZE); 

                //  Error message 6:
                if (instructTemp == OP_SIZE)
                {
                    cout << "Error: Instruction " << pinstruction << " is not recognized!\n";
                    throw 6;
                }

                world.species[i].program[programNum].op = opcode_t(instructTemp);
                if (instructTemp > 3)
                    in >> world.species[i].program[programNum].address;
                programNum ++;
            }
            else break;
        }
        world.species[i].programSize = programNum;
        cFile.close();
    }
    
    //Part 3
    //  get information from worldFile
    string worldLine, preworldLine;
    wFile.open(worldFile);
    
    //  Error message 3
    if (! wFile)
        throw worldFile;
  
    //  get grid.height, grid.width
    getline(wFile, worldLine);
    istringstream ih(worldLine);
    ih >> h;

    //  Error message 7: illegal height
    if (h > (int) MAXHEIGHT || h < 1)
    {
        cout << "Error: The grid height is illegal!\n";
        throw 7;
    }

    getline(wFile, worldLine);
    istringstream iw(worldLine);
    iw >> w;
    //Error message 8:  illegal width
    if (w > (int) MAXWIDTH || w < 1)
    {
        cout << "Error: The grid width is illegal!\n";
        throw 8;
    }
    //  get grid.terrian
    for (int i = 0; i < h; i ++)
    {
        string tline;
        getline(wFile, tline);
        for (int j = 0; j < w; j ++)
        {
            string terrain_Name = tline.substr(j, 1);
            unsigned int terrainTemp = find_Name(terrain_Name, &terrainShortName[0], TERRAIN_SIZE);
            if (terrainTemp >= DIRECT_SIZE)
           {
                cout << "Error: Terrian square (" << terrain_Name << " " << i << " " << j << ") is invalid!\n";
                throw 9;
            }
            world.grid.terrain[i][j] = terrain_t(terrainTemp);
        }
    }
 
    //  prepare for getting *creature.species
    string creatureName[speciesNum];
    for (unsigned int i = 0; i < speciesNum; i++)
        creatureName[i] = world.species[i].name;

    while (wFile)
    {
        string creatName, direct, abilities;
        string abi[2];

        //Error message 10: creature number exceeds
        if (creatureNum > MAXCREATURES)
            throw MAXCREATURES;

        getline(wFile, worldLine);
        if (worldLine != preworldLine)
            preworldLine = worldLine;
        else break;

        if (worldLine != "")
        {
            istringstream iw(worldLine);
            iw >> creatName >> direct >> world.creatures[creatureNum].location.r
                >> world.creatures[creatureNum].location.c;
            
            //get *creature.species
            unsigned int creatInd = find_Name(creatName, &creatureName[0], speciesNum);
    
            //Error message 11: unknown species
            if (creatInd >= speciesNum)
            {   
                cout << "Error: Species " << creatName << " not found!\n";
                throw 11;
            }
            world.creatures[creatureNum].species = & world.species[creatInd];
            world.creatures[creatureNum].programID = 1;
            //get creature.direction
            if (direct != "")
            {     
                unsigned int dir = find_Name(direct, &directName[0], DIRECT_SIZE);
                //Error message 12: unknown direction
                if (dir >= DIRECT_SIZE)
                {
                    cout << "Error: Direction " << direct << " is not recognized!\n";
                    throw 12;
                }
                world.creatures[creatureNum].direction = direction_t(dir);
            }
            //get creature.location

            //Error message 13: creature out of bound
            if (! checkBound(world.creatures[creatureNum].location, h, w))
            {
                cout << "Error: " << printCreature(world.creatures[creatureNum]) << " is out of bound!\n";
                cout << "The grid size is " << h << "-by-" << w << ".\n";
                throw 13;
            }
            world.grid.height = h;
            world.grid.width = w;
            //get creature.ability
            world.creatures[creatureNum].ability[FLY] = false;
            world.creatures[creatureNum].ability[ARCH] = false;
            while (iw)
            {
                iw >> abilities;
                if (abilities != "")
                {
                    unsigned int ab =find_Name(abilities, &abilityShortName[0], ABILITY_SIZE);
                    if (ab >= ABILITY_SIZE)
                    {//Error message 14
                        cout << "Error: " << printCreature(world.creatures[creatureNum]) <<" has an invalid ability ";
                        cout << abilities << "!\n";
                        throw 14;
                    }
                    else
                        world.creatures[creatureNum].ability[ability_t(ab)] = true;
                }
                else break;
            }
            creatureNum ++;
        }
        else break;
    }
    world.numCreatures = creatureNum;
    wFile.close();

    //Part 4
    //  get creature.hill
    for (unsigned int i = 0; i < creatureNum; i++)
    {
        int gr = world.creatures[i].location.r;
        int gc = world.creatures[i].location.c;
        if (! getCreature(world.grid, {gr, gc}))
        {
            terrain_t t = world.grid.terrain[gr][gc];
            world.grid.squares[gr][gc] = &world.creatures[i];
            if (t == HILL)
                world.creatures[i].hillActive = true;
            else
            {
                world.creatures[i].hillActive = false;

                //Error message 16: cannot fly but in lake
                if (t == LAKE && !world.creatures[i].ability[FLY])
                {
                    cout << "Error: " << printCreature(world.creatures[i]) << " is in a lake square!\n";
                    cout << "The creature cannot fly!\n";
                    throw 16;
                }
            }
        }
        else
        {//Error message 15:  overlaps
            cout << "Error: " << printCreature(world.creatures[i]) << " overlaps with creature (";
            cout << (*(*world.grid.squares[gr][gc]).species).name << " ";
            cout << directName[(*world.grid.squares[gr][gc]).direction] << " ";
            cout << (*world.grid.squares[gr][gc]).location.r << " ";
            cout << (*world.grid.squares[gr][gc]).location.c << ")!\n";
            throw 15;
        }
    }
}

static bool validStep(point_t location, const grid_t &grid)
//EFFECTS: Return true if "location" is not out of bound and no creature is in the square,
//  else return false.
{
    if (grid.terrain[location.r][location.c] == FOREST)
        return false;
    return (checkBound(location, grid.height, grid.width) && !getCreature(grid, location));
}

static bool compareSpecies(const creature_t &creature, const grid_t &grid, point_t location)
//REQUIREMENT: location is in the bound.
//EFFECTS: If the species of "creature" and that of the creature at "location", return true.
//  Else return false.
{
    if (! getCreature(grid, location))
        return false;
    return ((*creature.species).name == (*(*grid.squares[location.r][location.c]).species).name);
}

static void go(creature_t &creature, instruction_t instruction)
//EFFECTS: jump to step n
{
    creature.programID = instruction.address;
}

static void infect(creature_t &creature, grid_t grid, point_t location)
//REQUIREMENTS: "location" is in boundary
//EFFECTS: infect a creature, chage the species it points to, and programID    
{
    (*grid.squares[location.r][location.c]).species = creature.species;
    (*grid.squares[location.r][location.c]).programID = 1;
}
void simulateCreature(creature_t &creature, grid_t &grid, bool verbose)
{
    instruction_t instruction = getInstruction(creature);
    while (instruction.op != HOP && instruction.op != LEFT 
            && instruction.op != RIGHT && instruction.op != INFECT)
    {
        point_t newLocation = adjacentPoint(creature.location, creature.direction);
        unsigned int pID  = creature.programID;
        switch (instruction.op) 
        {
            case IFEMPTY: 
            {
                if (validStep(newLocation, grid))
                    go(creature, instruction);
                else creature.programID++;
                break;
            }
            case IFENEMY:
            {
                if (!checkBound(newLocation, grid.height, grid.width))
                    creature.programID ++; 
                else if (getCreature(grid, newLocation) && !compareSpecies(creature, grid, newLocation)
                    && grid.terrain[newLocation.r][newLocation.c] != FOREST)
                    go(creature, instruction);
                else creature.programID++;
                break;
            }
            case IFSAME:
            {
                if (!checkBound(newLocation, grid.height, grid.width))
                    creature.programID ++;
                else if (getCreature(grid, newLocation) && compareSpecies(creature, grid, newLocation)
                    && grid.terrain[newLocation.r][newLocation.c] != FOREST)
                    go(creature, instruction);
                else creature.programID++;
                break;
            }
            case IFWALL:
            {
                if ( !checkBound(newLocation, grid.height, grid.width)) 
                    go(creature, instruction);
                else if ((grid.terrain[newLocation.r][newLocation.c] == LAKE) && !creature.ability[FLY])
                    go(creature, instruction);
                else creature.programID++;
                break;
            }
            case GO:
                go(creature, instruction);
                break;
            default: break;
        }
        if (verbose)
        {
            cout << "\nInstruction " << pID << ": " << opName[instruction.op];
            if (instruction.address != 0)
                cout << " " << instruction.address;
        }
        instruction = getInstruction(creature);
    }
    switch (instruction.op)
    {
        case HOP:
        {
            point_t newLocation = adjacentPoint(creature.location, creature.direction);
            if (checkBound(newLocation, grid.height, grid.width))
            {
                if (!getCreature(grid, newLocation) 
                    && (creature.ability[FLY] || (grid.terrain[newLocation.r][newLocation.c] != LAKE)))
                {
                    grid.squares[creature.location.r][creature.location.c] = grid.squares[newLocation.r][newLocation.c];
                    grid.squares[newLocation.r][newLocation.c] = &creature;
                    creature.location = newLocation;
                }
            }
            break;
        }
        case LEFT:
            creature.direction = leftFrom(creature.direction);
            break;
        case RIGHT:
            creature.direction = rightFrom(creature.direction);
            break;
        case INFECT:
        {
            point_t newLocation = adjacentPoint(creature.location, creature.direction);
            if (!creature.ability[ARCH] && checkBound(newLocation, grid.height, grid.width))
            {
                if (grid.terrain[newLocation.r][newLocation.c] != FOREST && 
                    getCreature(grid, newLocation) && !compareSpecies(creature, grid, newLocation))
                {
                    infect(creature, grid, newLocation);
                }
            }
            else if (creature.ability[ARCH])
            {
                while (checkBound(newLocation, grid.height, grid.width))
                {
                    if (getCreature(grid, newLocation) && ! compareSpecies(creature, grid, newLocation))
                    {
                        infect(creature, grid, newLocation);
                        break;
                    }
                    newLocation = adjacentPoint(newLocation, creature.direction);
                }
            }
            break;
        }
        default: break;
    }
    if (! verbose)
        cout << " " << opName[instruction.op] << "\n";
    else
    {
        cout << "\nInstruction " << creature.programID << ": " << opName[instruction.op];
        if (instruction.address != 0)
            cout << " " << instruction.address;
        cout << "\n";
        printGrid(grid);
    }
    creature.programID ++;
}

void printGrid(const grid_t &grid)
{
    for (unsigned int i = 0; i < grid.height; i ++)
    {
        for (unsigned int j = 0; j < grid.width; j ++)
        {
            if (! grid.squares[i][j])
                cout << "____ ";
            else
            {
                creature_t cre = *grid.squares[i][j];
                species_t temp = *cre.species;
                cout << temp.name.substr(0, 2) << "_" << directShortName[cre.direction] << " ";
            }
        }
        cout << "\n";
    }
}

point_t adjacentPoint(point_t pt, direction_t dir)
{
    switch (dir)
    {
        case EAST:
            pt.c ++;
            break;
        case SOUTH:
            pt.r ++;
            break;
        case WEST: 
            pt.c --;
            break;
        case NORTH: 
            pt.r --;
            break;
        default: break;
    }
    return pt;
}

direction_t leftFrom(direction_t dir)
{
    switch (dir)
    {
        case EAST: return NORTH;
        case SOUTH: return EAST;
        case WEST: return SOUTH;
        case NORTH: return WEST;
        default: return dir;
    }
}

direction_t rightFrom(direction_t dir)
{
    switch (dir)
    {
        case EAST: return SOUTH;
        case SOUTH: return WEST;
        case WEST: return NORTH;
        case NORTH: return EAST;
        default: return dir;
    }
}

instruction_t getInstruction(const creature_t &creature)
{
    return (*creature.species).program[creature.programID - 1];
}

creature_t *getCreature(const grid_t &grid, point_t location)
{
    return grid.squares[location.r][location.c];
}
