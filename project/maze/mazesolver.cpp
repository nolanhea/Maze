#include "mazesolver.h"


MyPoint::MyPoint(int h, int v) {
    vCoord = v;
    hCoord = h;
}

bool MyPoint::operator ==(MyPoint other) {
    if (vCoord == other.vCoord && hCoord == other.hCoord) {
        return true;
    }
    return false;
}

MazeSolver::MazeSolver(std::vector<int> hw, std::vector<int> vw, int sz) {
    size = sz;
    h_walls = hw;
    v_walls = vw;
}

std::vector<int> MazeSolver::solve(MyPoint start, MyPoint finish) {
    std::vector<bool> isVisited(size * size);
    std::vector<int> prev(size * size);
    std::vector<int> cost(size * size);
    for (auto& i:cost) {
        i = 1000000000;
    }
    std::queue<int> q;
    int source = start.vCoord + start.hCoord * size;
    int final = finish.vCoord + finish.hCoord * size;
    q.push(source);
    cost[source] = 0;
    while(!q.empty()) {
        int cell = q.front();
        q.pop();
        auto nbs = neighbours(cell);
        for (auto nb:nbs) {
            if (!isVisited[nb]) {
                if (cost[nb] > cost[cell] + 1) {
                    cost[nb] = cost[cell] + 1;
                    prev[nb] = cell;
                    q.push(nb);
                }

            }
        }
        isVisited[cell] = true;
    }
    std::vector<int> answer;
    while(true) {
        answer.push_back(final);
        final = prev[final];
        if(final == source) {
            answer.push_back(final);
            break;
        }
    }
    return answer;
}

std::vector<int> MazeSolver::neighbours(int cell) {
    std::vector<int> ret;
    if (cell % size != size - 1 && v_walls[cell] != 1) {
        ret.push_back(cell + 1);
    }
    if (cell % size != 0 && v_walls[cell - 1] != 1) {
        ret.push_back(cell - 1);
    }
    if (cell >= size && h_walls[cell - size] != 1) {
        ret.push_back(cell - size);
    }
    if (cell < size * (size - 1) && h_walls[cell] != 1) {
        ret.push_back(cell + size);
    }
    return ret;
}
