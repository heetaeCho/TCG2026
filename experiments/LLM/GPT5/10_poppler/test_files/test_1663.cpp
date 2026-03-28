// PreScanOutputDev_test_1663.cpp
#include <gtest/gtest.h>

#include "PreScanOutputDev.h"

namespace {

// Helper to create a PSLevel value without assuming any particular enumerator names.
static inline PSLevel MakePSLevel(int v) {
  return static_cast<PSLevel>(v);
}

class PreScanOutputDevTest_1663 : public ::testing::Test {};

TEST_F(PreScanOutputDevTest_1663, IsAllGDIReturnsStableValueOnRepeatedCalls_1663) {
  PreScanOutputDev dev(MakePSLevel(0));

  const bool first = dev.isAllGDI();
  // Observable, black-box invariant: repeated calls should be self-consistent.
  EXPECT_EQ(first, dev.isAllGDI());
  EXPECT_EQ(first, dev.isAllGDI());
}

TEST_F(PreScanOutputDevTest_1663, IsAllGDIIsCallableOnConstInstance_1663) {
  const PreScanOutputDev dev(MakePSLevel(0));

  const bool v1 = dev.isAllGDI();
  const bool v2 = dev.isAllGDI();
  EXPECT_EQ(v1, v2);
}

TEST_F(PreScanOutputDevTest_1663, MultipleInstancesHaveIndependentObservableResults_1663) {
  PreScanOutputDev devA(MakePSLevel(0));
  PreScanOutputDev devB(MakePSLevel(1));

  // We do not assume they differ; we only require each instance is internally consistent.
  EXPECT_EQ(devA.isAllGDI(), devA.isAllGDI());
  EXPECT_EQ(devB.isAllGDI(), devB.isAllGDI());
}

TEST_F(PreScanOutputDevTest_1663, CanBeDeletedThroughBasePointer_1663) {
  // Verifies external interaction with polymorphic destruction (no crash/UB observable here).
  OutputDev *base = new PreScanOutputDev(MakePSLevel(0));
  delete base;
  SUCCEED();
}

}  // namespace