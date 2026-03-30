// SPDX-License-Identifier: GPL-2.0-or-later
// File: stitchingfunction_getscale_test_381.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Function.h"

namespace {

class StitchingFunctionTest_381 : public ::testing::Test {};

// Normal operation (observable via interface): method exists and returns expected type.
TEST_F(StitchingFunctionTest_381, GetScaleReturnTypeIsConstDoublePtr_381) {
  using Ret = decltype(std::declval<const StitchingFunction&>().getScale());
  EXPECT_TRUE((std::is_same_v<Ret, const double*>));
}

// Boundary/const-correctness: callable on const object (i.e., method is const-qualified in interface).
TEST_F(StitchingFunctionTest_381, GetScaleCallableOnConstObject_381) {
  // If getScale were not const-qualified, this decltype would fail to compile.
  using Ret = decltype(std::declval<const StitchingFunction&>().getScale());
  (void)static_cast<Ret>(nullptr);  // quiet unused warnings and confirm the type is a pointer type
  SUCCEED();
}

// Boundary condition: returned pointer is a raw pointer; it is valid to compare/copy as a value.
TEST_F(StitchingFunctionTest_381, GetScalePointerIsCopyableAndComparable_381) {
  using Ptr = decltype(std::declval<const StitchingFunction&>().getScale());
  EXPECT_TRUE((std::is_copy_constructible_v<Ptr>));
  EXPECT_TRUE((std::is_copy_assignable_v<Ptr>));
  EXPECT_TRUE((std::is_trivially_copyable_v<Ptr>));
}

// Exceptional/error-case (observable via interface only): callers must be able to handle nullptr.
TEST_F(StitchingFunctionTest_381, GetScaleReturnTypeSupportsNullptr_381) {
  using Ptr = decltype(std::declval<const StitchingFunction&>().getScale());
  Ptr p = nullptr;
  EXPECT_EQ(p, nullptr);
}

}  // namespace