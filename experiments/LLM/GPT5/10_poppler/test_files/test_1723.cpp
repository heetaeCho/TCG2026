// File: CairoOutputDev_useDrawChar_test.cpp
// Target: ./TestProjects/poppler/poppler/CairoOutputDev.h

#include <gtest/gtest.h>

#include "poppler/CairoOutputDev.h"
#include "poppler/OutputDev.h"

namespace {

class CairoOutputDevTest_1723 : public ::testing::Test {
protected:
  CairoOutputDev dev_;
};

TEST_F(CairoOutputDevTest_1723, UseDrawCharReturnsTrue_1723) {
  EXPECT_TRUE(dev_.useDrawChar());
}

TEST_F(CairoOutputDevTest_1723, UseDrawCharIsStableAcrossMultipleCalls_1723) {
  EXPECT_TRUE(dev_.useDrawChar());
  EXPECT_TRUE(dev_.useDrawChar());
  EXPECT_TRUE(dev_.useDrawChar());
}

TEST_F(CairoOutputDevTest_1723, UseDrawCharViaBasePointerReturnsTrue_1723) {
  OutputDev *base = &dev_;
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useDrawChar());
}

TEST_F(CairoOutputDevTest_1723, UseDrawCharOnDifferentInstancesReturnsTrue_1723) {
  CairoOutputDev other;
  EXPECT_TRUE(dev_.useDrawChar());
  EXPECT_TRUE(other.useDrawChar());
}

} // namespace