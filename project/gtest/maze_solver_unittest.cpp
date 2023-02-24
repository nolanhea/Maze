#ifndef MAZE_SOLVER_UNITTEST
#define MAZE_SOLVER_UNITTEST


#include "../maze/mazesolver.h"
#include "../maze/maze_generator.h"

#include <limits.h>
#include "gtest/gtest.h"

TEST(MazeSolverTest, MazeSolver) {
  auto maze = MazeGenerator(10, 10);
  EXPECT_EQ(maze.first.size(), 10 * 10);
  EXPECT_EQ(maze.second.size(), 10 * 10);

  MazeSolver solver(maze.first, maze.second, 10);
  auto solution = solver.solve(MyPoint(0, 0), MyPoint(5, 5));
  EXPECT_TRUE(solution.size() != 0);
}

 // namespace

#endif  // MAZE_SOLVER_UNITTEST