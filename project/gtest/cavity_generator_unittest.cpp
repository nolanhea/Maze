#ifndef CAVITY_GENERATOR_UNITTEST
#define CAVITY_GENERATOR_UNITTEST


#include "../cavity/cavitygenerator.h"

#include <limits.h>
#include "gtest/gtest.h"

TEST(CavityGeneratorTest, Constructor) {
  CavityGenerator cg(10, 2, 2);
  EXPECT_EQ(cg.getSize(), 10);
  EXPECT_EQ(cg.getBirthLimit(), 2);
  EXPECT_EQ(cg.getDeathLimit(), 2);
}

TEST(CavityGeneratorTest, NextStep) {
  CavityGenerator cg(50, 2, 2);
  EXPECT_EQ(cg.nextStep(), 1);
}

TEST(CavityGeneratorTest, Getters) {
  CavityGenerator cg(50, 2, 3);
  EXPECT_EQ(cg.getBirthLimit(), 2);
  EXPECT_EQ(cg.getDeathLimit(), 3);
  EXPECT_EQ(cg.getSize(), 50);
}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
 // namespace

#endif  // CAVITY_GENERATOR_UNITTEST
