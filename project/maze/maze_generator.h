#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <ctime>
#include <algorithm>
using std::unordered_set;
using std::vector;
using std::pair;

// generates maze of n x m size. Returns generated maze as vector of horizontal walls and
// vector of vertical walls respectively.
pair<vector<int>, vector<int>> MazeGenerator(int n, int m);

// helper function for MazeGenerator
void joinSets(unordered_set<int>* A, unordered_set<int>* B);

// helper function for MazeGenerator
int getBottomCount(vector<int> h_walls, unordered_set<int>* sets, int row, int column, int size);

