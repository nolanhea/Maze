#ifndef MAZESOLVER_H
#define MAZESOLVER_H
#include <vector>
#include <queue>

struct MyPoint {
    int vCoord;
    int hCoord;
    MyPoint(int h, int v);
    bool operator ==(MyPoint other);
};

class MazeSolver
{
public:
    MazeSolver();
    MazeSolver(std::vector<int> hw, std::vector<int> vw,  int sz);

    // finds path from start to finish using BSF.
    // returns vector of indexes of cells on that path.
    std::vector<int> solve(MyPoint start, MyPoint finish);

private:
    std::vector<int> neighbours(int cell);

    std::vector<int> h_walls;
    std::vector<int> v_walls;
    int size;
};

#endif // MAZESOLVER_H
