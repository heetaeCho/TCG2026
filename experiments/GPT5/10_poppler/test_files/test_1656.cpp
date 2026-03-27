// PreScanOutputDev_useDrawChar_test_1656.cpp

#include <gtest/gtest.h>

#include "PreScanOutputDev.h"

// NOTE: We treat PreScanOutputDev as a black box. These tests only verify
// observable behavior through the public interface.

class PreScanOutputDevTest_1656 : public ::testing::Test {
protected:
  // Construct using a value-converted PSLevel to avoid assuming specific enumerators.
  // This relies only on the constructor signature taking PSLevel by value.
  PreScanOutputDev MakeDev() { return PreScanOutputDev(static_cast<PSLevel>(0)); }
};

TEST_F(PreScanOutputDevTest_1656, UseDrawCharReturnsTrue_1656) {
  auto dev = MakeDev();
  EXPECT_TRUE(dev.useDrawChar());
}

TEST_F(PreScanOutputDevTest_1656, UseDrawCharIsStableAcrossMultipleCalls_1656) {
  auto dev = MakeDev();

  const bool first = dev.useDrawChar();
  const bool second = dev.useDrawChar();
  const bool third = dev.useDrawChar();

  EXPECT_TRUE(first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(PreScanOutputDevTest_1656, UseDrawCharViaBasePointerReturnsTrue_1656) {
  auto dev = MakeDev();

  OutputDev* base = &dev;
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useDrawChar());
}