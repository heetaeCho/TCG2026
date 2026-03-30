// MarkedContentOutputDev_test_1677.cpp
#include <gtest/gtest.h>

#include "MarkedContentOutputDev.h"

namespace {

class MarkedContentOutputDevTest_1677 : public ::testing::Test {};

TEST_F(MarkedContentOutputDevTest_1677, InterpretType3CharsReturnsFalse_1677) {
  MarkedContentOutputDev dev;
  EXPECT_FALSE(dev.interpretType3Chars());
}

TEST_F(MarkedContentOutputDevTest_1677, InterpretType3CharsIsStableAcrossMultipleCalls_1677) {
  MarkedContentOutputDev dev;

  EXPECT_FALSE(dev.interpretType3Chars());
  EXPECT_FALSE(dev.interpretType3Chars());
  EXPECT_FALSE(dev.interpretType3Chars());
}

TEST_F(MarkedContentOutputDevTest_1677, InterpretType3CharsIndependentBetweenInstances_1677) {
  MarkedContentOutputDev dev1;
  MarkedContentOutputDev dev2;

  EXPECT_FALSE(dev1.interpretType3Chars());
  EXPECT_FALSE(dev2.interpretType3Chars());
}

}  // namespace