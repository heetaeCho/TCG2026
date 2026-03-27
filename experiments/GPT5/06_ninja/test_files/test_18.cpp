// File: optional_explanations_ptr_test_18.cc

#include "explanations.h"

#include <gtest/gtest.h>

// Test fixture (kept simple on purpose)
class OptionalExplanationsTest_18 : public ::testing::Test {};

// Normal operation: non-null pointer passed in should be returned by ptr().
TEST_F(OptionalExplanationsTest_18, PtrReturnsWrappedPointer_18) {
  Explanations explanations;
  OptionalExplanations optional(&explanations);

  // ptr() should give us back the same pointer we passed to the constructor.
  EXPECT_EQ(&explanations, optional.ptr());
}

// Boundary case: nullptr passed in should be returned by ptr().
TEST_F(OptionalExplanationsTest_18, PtrReturnsNullWhenConstructedWithNull_18) {
  OptionalExplanations optional(nullptr);

  // If constructed with nullptr, ptr() should return nullptr.
  EXPECT_EQ(nullptr, optional.ptr());
}
