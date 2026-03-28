// PreScanOutputDev_usesPatternImageMask_test_1664.cpp

#include <gtest/gtest.h>

#include "PreScanOutputDev.h"

namespace {

class PreScanOutputDevTest_1664 : public ::testing::Test {
 protected:
  static PreScanOutputDev MakeDev() {
    // Avoid depending on specific PSLevel enumerator names.
    return PreScanOutputDev(static_cast<PSLevel>(0));
  }
};

TEST_F(PreScanOutputDevTest_1664, UsesPatternImageMask_IsCallableAfterConstruction_1664) {
  PreScanOutputDev dev = MakeDev();
  const bool v = dev.usesPatternImageMask();
  (void)v;  // observable: call succeeds and returns a bool
}

TEST_F(PreScanOutputDevTest_1664, UsesPatternImageMask_IsStableAcrossRepeatedCalls_1664) {
  PreScanOutputDev dev = MakeDev();

  const bool v1 = dev.usesPatternImageMask();
  const bool v2 = dev.usesPatternImageMask();
  const bool v3 = dev.usesPatternImageMask();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(PreScanOutputDevTest_1664, UsesPatternImageMask_WorksThroughConstReference_1664) {
  PreScanOutputDev dev = MakeDev();
  const PreScanOutputDev& cdev = dev;

  const bool v1 = cdev.usesPatternImageMask();
  const bool v2 = cdev.usesPatternImageMask();

  EXPECT_EQ(v1, v2);
}

TEST_F(PreScanOutputDevTest_1664, UsesPatternImageMask_CallableAfterClearStats_1664) {
  PreScanOutputDev dev = MakeDev();

  const bool before = dev.usesPatternImageMask();

  dev.clearStats();

  const bool after1 = dev.usesPatternImageMask();
  const bool after2 = dev.usesPatternImageMask();

  // Black-box: we don't assume whether clearStats changes the value.
  // We only verify it's callable and stable across repeated calls post-clearStats.
  EXPECT_EQ(after1, after2);

  (void)before;
}

}  // namespace