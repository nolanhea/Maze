#ifndef CAVITYGENERATOR_H
#define CAVITYGENERATOR_H
#include <vector>
#include <cstdlib>
#include <ctime>
class CavityGenerator
{
public:
    CavityGenerator() = delete;
    CavityGenerator(int size, int birthLimit, int deathLimit);
    bool nextStep(); // returns false if nextStep() does not change state of cavity
    int getCell(int index);
    int getSize();
    int getBirthLimit();
    int getDeathLimit();

private:
    int liveDeadNeighboursCount(int cell);
    int size;
    int birthLimit;
    int deathLimit;
    std::vector<int> cavity;
};

#endif // CAVITYGENERATOR_H
