// PreScanOutputDev_1662_test.cc
#include <gtest/gtest.h>

#include "PreScanOutputDev.h"

namespace {

class PreScanOutputDevTest_1662 : public ::testing::Test {};

TEST_F(PreScanOutputDevTest_1662, UsesTransparency_ReturnsBoolAndIsCallableOnConst_1662) {
  const PreScanOutputDev dev;
  // Observable behavior: method is callable, returns a bool.
  const bool v = dev.usesTransparency();
  (void)v;
  SUCCEED();
}

TEST_F(PreScanOutputDevTest_1662, UsesTransparency_IsStableAcrossRepeatedCalls_1662) {
  const PreScanOutputDev dev;

  const bool first = dev.usesTransparency();
  const bool second = dev.usesTransparency();
  const bool third = dev.usesTransparency();

  // With no mutating API exposed in the provided interface, repeated calls should
  // observe the same value for the same object.
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(PreScanOutputDevTest_1662, UsesTransparency_CopyConstructionPreservesObservedValue_1662) {
  const PreScanOutputDev original;
  const bool before = original.usesTransparency();

  const PreScanOutputDev copy(original);
  const bool after = copy.usesTransparency();

  EXPECT_EQ(before, after);
}

TEST_F(PreScanOutputDevTest_1662, UsesTransparency_CopyAssignmentPreservesObservedValue_1662) {
  const PreScanOutputDev original;
  const bool before = original.usesTransparency();

  PreScanOutputDev assigned;
  assigned = original;

  const bool after = assigned.usesTransparency();
  EXPECT_EQ(before, after);
}

TEST_F(PreScanOutputDevTest_1662, UsesTransparency_MoveConstructionPreservesObservedValue_1662) {
  PreScanOutputDev original;
  const bool before = original.usesTransparency();

  PreScanOutputDev moved(std::move(original));
  const bool after = moved.usesTransparency();

  // We only assert on the moved-to object vs the value observed pre-move.
  EXPECT_EQ(before, after);
}

TEST_F(PreScanOutputDevTest_1662, UsesTransparency_MoveAssignmentPreservesObservedValue_1662) {
  PreScanOutputDev original;
  const bool before = original.usesTransparency();

  PreScanOutputDev target;
  target = std::move(original);

  const bool after = target.usesTransparency();
  EXPECT_EQ(before, after);
}

TEST_F(PreScanOutputDevTest_1662, UsesTransparency_DoesNotThrow_1662) {
  const PreScanOutputDev dev;
  EXPECT_NO_THROW((void)dev.usesTransparency());
}

}  // namespace