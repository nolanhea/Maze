#include "maze_generator.h"
void joinSets(unordered_set<int> *A, unordered_set<int> *B) {
    for (auto i:*B) {
        A -> insert(i);
    }
}

int getBottomCount(vector<int> h_walls, unordered_set<int> *sets, int row, int column, int size) {
    int count = 1;
    for (auto i:*sets) {
        if (i > row * size + column && i < row * (size + 1)) {
            count++;
        }
    }
    for (int i = row * size; i < row * size + column; i++) {
        if (sets -> find(i) != sets -> end() && h_walls[i] == 0) {
            count++;
        }
    }
    return count;
}

pair<vector<int>, vector<int> > MazeGenerator(int n, int m) {
    srand((unsigned) time(0));
    unordered_set<int>** ptr_matrix = new unordered_set<int>*[n * m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ptr_matrix[i * m + j] = new unordered_set<int>;
            ptr_matrix[i * m + j] -> insert(i*m + j);
        }
    }

    vector<int> v_walls;
    vector<int> h_walls;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ptr_matrix[i * m + j] -> find(i * m + j + 1) != ptr_matrix[i * m + j] -> end()) {
                v_walls.push_back(1);
                continue;
            }

            int r = rand() % 2;
            if (j == m - 1) {
                v_walls.push_back(1);
                continue;
            } else if (r == 1) {
                v_walls.push_back(1);
                continue;
            } else {
                for (auto k:*ptr_matrix[i*m + j + 1]) {
                    if (k != i*m + j + 1) {
                        ptr_matrix[k] = ptr_matrix[i*m + j];
                    }
                }
                joinSets(ptr_matrix[i*m + j], ptr_matrix[i*m + j + 1]);
                delete ptr_matrix[i*m + j + 1];
                ptr_matrix[i*m + j + 1] = ptr_matrix[i*m + j];
                v_walls.push_back(0);
            }
        }

        for (int j = 0; j < m; j++) {
            int r = rand() % 2;
            if (ptr_matrix[i*m + j] -> size() == 1) {
                if (i != n - 1) {
                    joinSets(ptr_matrix[(i)*m + j], ptr_matrix[(i + 1)*m + j]);
                    delete ptr_matrix[(i + 1) * m + j];
                    ptr_matrix[(i + 1) * m + j] = ptr_matrix[i * m + j];
                }

                h_walls.push_back(0);
                continue;
            }
            int count = getBottomCount(h_walls, ptr_matrix[i*m + j], i, j, m);
            if (count == 1) {
                if (i != n - 1) {
                    joinSets(ptr_matrix[(i)*m + j], ptr_matrix[(i + 1)*m + j]);
                    delete ptr_matrix[(i + 1) * m + j];
                    ptr_matrix[(i + 1) * m + j] = ptr_matrix[i * m + j];
                }

                h_walls.push_back(0);
                continue;
            }
            h_walls.push_back(r);
            if (r == 0) {
                if (i != n - 1) {
                    joinSets(ptr_matrix[(i)*m + j], ptr_matrix[(i + 1)*m + j]);
                    delete ptr_matrix[(i + 1) * m + j];
                    ptr_matrix[(i + 1) * m + j] = ptr_matrix[i * m + j];
                }
            }
        }
        if (i == n - 1) {
            for (int j = 0; j < m - 1; j++) {
                if (ptr_matrix[i * m + j] -> find(i * m + j + 1) == ptr_matrix[i * m + j] -> end()) {
                    for (auto k:*ptr_matrix[i*m + j + 1]) {
                        if (k != i*m + j + 1) {
                            ptr_matrix[k] = ptr_matrix[i*m + j];
                        }
                    }
                    joinSets(ptr_matrix[i*m + j], ptr_matrix[i*m + j + 1]);
                    delete ptr_matrix[i*m + j + 1];
                    ptr_matrix[i*m + j + 1] = ptr_matrix[i*m + j];
                    v_walls[i * m + j] = 0;
                }
            }
        }

    }
    return pair<vector<int>, vector<int>>(v_walls, h_walls);
}
