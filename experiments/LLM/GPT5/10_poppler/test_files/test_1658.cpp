// PreScanOutputDev_tests_1658.cpp
#include <gtest/gtest.h>

#include "PreScanOutputDev.h"

namespace {

class PreScanOutputDevTest_1658 : public ::testing::Test {
protected:
  PreScanOutputDev dev_;
};

TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForZeroType_1658) {
  EXPECT_TRUE(dev_.useShadedFills(0));
}

TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForPositiveType_1658) {
  EXPECT_TRUE(dev_.useShadedFills(1));
  EXPECT_TRUE(dev_.useShadedFills(42));
}

TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForNegativeType_1658) {
  EXPECT_TRUE(dev_.useShadedFills(-1));
  EXPECT_TRUE(dev_.useShadedFills(-42));
}

TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForIntMinAndMax_1658) {
  EXPECT_TRUE(dev_.useShadedFills(std::numeric_limits<int>::min()));
  EXPECT_TRUE(dev_.useShadedFills(std::numeric_limits<int>::max()));
}

TEST_F(PreScanOutputDevTest_1658, UseShadedFillsIsDeterministicAcrossCalls_1658) {
  const int types[] = {0, 1, -1, 123, -999};
  for (int t : types) {
    EXPECT_TRUE(dev_.useShadedFills(t));
    EXPECT_TRUE(dev_.useShadedFills(t));
  }
}

}  // namespace