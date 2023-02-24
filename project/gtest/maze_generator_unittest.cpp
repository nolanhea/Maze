#ifndef MAZE_GENERATOR_UNITTEST
#define MAZE_GENERATOR_UNITTEST


#include "../maze/maze_generator.h"

#include <limits.h>
#include "gtest/gtest.h"

TEST(MazeGeneratorTest, MazeGeneration_1) {
  auto maze = MazeGenerator(10, 10);
  EXPECT_EQ(maze.first.size(), 10 * 10);
  EXPECT_EQ(maze.second.size(), 10 * 10);
}

TEST(MazeGeneratorTest, MazeGeneration_2) {
  auto maze = MazeGenerator(30, 30);
  EXPECT_EQ(maze.first.size(), 30 * 30);
  EXPECT_EQ(maze.second.size(), 30 * 30);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
 // namespace

#endif  // MAZE_GENERATOR_UNITTEST
