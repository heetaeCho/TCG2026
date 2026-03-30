// Copyright (C) 2026
// Unit tests for GfxTilingPattern::getYStep
//
// TEST_ID: 496
//
// Constraints note:
// - GfxTilingPattern has no accessible public constructor (private ctor; typically created via parse()).
// - To avoid inferring internal behavior or touching private state, these tests validate observable
//   interface properties (signature/const-correctness) using type traits and declval.

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/GfxState.h"

namespace {

TEST(GfxTilingPatternTest_496, GetYStep_ReturnTypeIsDouble_496) {
  // Verify the public interface returns a double.
  using RetT = decltype(std::declval<const GfxTilingPattern&>().getYStep());
  EXPECT_TRUE((std::is_same_v<RetT, double>));
}

TEST(GfxTilingPatternTest_496, GetYStep_IsConstMemberFunction_496) {
  // Verify we can form a pointer to a const-qualified member function with the expected signature.
  double (GfxTilingPattern::*pmf)() const = &GfxTilingPattern::getYStep;
  (void)pmf;
  SUCCEED();
}

TEST(GfxTilingPatternTest_496, GetYStep_CallableOnConstReference_496) {
  // This is an interface-level check: expression must be well-formed on const objects.
  // (We do not attempt to instantiate GfxTilingPattern because construction is not public.)
  constexpr bool kWellFormed =
      std::is_invocable_r_v<double, decltype(&GfxTilingPattern::getYStep), const GfxTilingPattern*>;
  EXPECT_TRUE(kWellFormed);
}

TEST(GfxTilingPatternTest_496, GetYStep_CallableOnConstPointer_496) {
  // Similar interface check for pointer usage.
  constexpr bool kWellFormed =
      std::is_invocable_r_v<double, decltype(&GfxTilingPattern::getYStep), const GfxTilingPattern&>;
  EXPECT_TRUE(kWellFormed);
}

}  // namespace