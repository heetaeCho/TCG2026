#include "gtest/gtest.h"

// Declaration of the function under test
int GetProcessorCount();

TEST(GetProcessorCountTest_156, ReturnsPositiveValue_156) {
  int count = GetProcessorCount();
  EXPECT_GT(count, 0) << "Processor count should be at least 1";
}

TEST(GetProcessorCountTest_156, ReturnsConsistentResults_156) {
  int count1 = GetProcessorCount();
  int count2 = GetProcessorCount();
  EXPECT_EQ(count1, count2) << "Multiple calls should return the same value";
}

TEST(GetProcessorCountTest_156, ReturnsReasonableValue_156) {
  int count = GetProcessorCount();
  // A reasonable upper bound: no system should report more than 100000 cores
  EXPECT_LE(count, 100000) << "Processor count seems unreasonably high";
  EXPECT_GE(count, 1) << "Processor count must be at least 1";
}

TEST(GetProcessorCountTest_156, DoesNotReturnZero_156) {
  int count = GetProcessorCount();
  EXPECT_NE(count, 0) << "Processor count should never be zero";
}

TEST(GetProcessorCountTest_156, DoesNotReturnNegative_156) {
  int count = GetProcessorCount();
  EXPECT_GE(count, 1) << "Processor count should not be negative";
}

TEST(GetProcessorCountTest_156, StabilityUnderRepeatedCalls_156) {
  // Call multiple times to ensure no instability or resource leaks
  for (int i = 0; i < 100; ++i) {
    int count = GetProcessorCount();
    EXPECT_GT(count, 0);
  }
}
