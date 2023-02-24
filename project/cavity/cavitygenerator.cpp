#include "cavitygenerator.h"


CavityGenerator::CavityGenerator(int size, int birthLimit, int deathLimit): size(size), birthLimit(birthLimit), deathLimit(deathLimit) {
    std::srand(std::time(0));
    for (int i  = 0; i < size * size; ++i) {
        int random = std::rand() % 2;
        cavity.push_back(random);
    }
}

bool CavityGenerator::nextStep() {
    std::vector<int> newCavity;
    bool isChanged = false;
    for (int i = 0; i < size * size; i++) {
        int liveCount = liveDeadNeighboursCount(i);


        if (cavity[i] == 0) {
            if (liveCount > birthLimit) {
                newCavity.push_back(1);
                isChanged = true;
            } else {
                newCavity.push_back(0);
            }
        } else {
            if(liveCount < deathLimit) {
                newCavity.push_back(0);
                isChanged = true;
            } else {
                newCavity.push_back(1);
            }

        }
    }
    cavity = newCavity;
    return isChanged;
}

// return number of alive cells around given cell
int CavityGenerator::liveDeadNeighboursCount(int cell) {
    int liveCount = 0;
    int deadCount = 0;
    if (cell >= size && cell % size != 0) {
        if (cavity[cell - size - 1] == 1) {
            liveCount++;
        } else {
            deadCount++;
        }
    }
    if (cell >= size) {
        if (cavity[cell - size] == 1) {
            liveCount++;
        } else {
            deadCount++;
        }
    }

    if (cell >= size && cell % size != size - 1) {
        if (cavity[cell - size + 1] == 1) {
            liveCount++;
        } else {
            deadCount++;
        }
    }
    if (cell % size != 0) {
        if (cavity[cell - 1] == 1) {
            liveCount++;
        } else {
            deadCount++;
        }
    }
    if (cell % size != size - 1) {
        if (cavity[cell + 1] == 1) {
            liveCount++;
        } else {
            deadCount++;
        }
    }
    if (cell < size * (size - 1) && cell % size != 0) {
        if (cavity[cell + size - 1] == 1) {
            liveCount++;
        } else {
            deadCount++;
        }
    }
    if (cell < size * (size - 1)) {
        if (cavity[cell + size] == 1) {
            liveCount++;
        } else {
            deadCount++;
        }
    }
    if (cell < size * (size - 1) && cell % size != size - 1) {
        if (cavity[cell + size + 1] == 1) {
            liveCount++;
        } else {
            deadCount++;
        }
    }
    return liveCount;
}

int CavityGenerator::getSize() {
    return size;
}

int CavityGenerator::getCell(int index) {
    return cavity[index];
}

int CavityGenerator::getBirthLimit() {
    return birthLimit;
}

int CavityGenerator::getDeathLimit() {
    return deathLimit;
}
