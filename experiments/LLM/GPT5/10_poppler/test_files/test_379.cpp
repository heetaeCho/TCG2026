// File: StitchingFunction_getBounds_379_test.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the real header from the codebase.
#include "poppler/Function.h"

namespace {

// TEST_ID = 379
class StitchingFunctionTest_379 : public ::testing::Test {};

template <typename T>
using getBounds_expr_t = decltype(std::declval<const T&>().getBounds());

}  // namespace

// Verifies the exact member function pointer type for getBounds().
TEST_F(StitchingFunctionTest_379, GetBounds_HasExpectedMemberFunctionType_379) {
  using Expected = const double* (StitchingFunction::*)() const;
  static_assert(std::is_same_v<decltype(&StitchingFunction::getBounds), Expected>,
                "StitchingFunction::getBounds must be 'const double* () const'");
  SUCCEED();
}

// Verifies getBounds() is callable on a const StitchingFunction reference.
TEST_F(StitchingFunctionTest_379, GetBounds_IsCallableOnConstObject_379) {
  static_assert(std::is_same_v<getBounds_expr_t<StitchingFunction>, const double*>,
                "Calling getBounds() on const object must yield const double*");
  SUCCEED();
}

// Boundary/robustness at the type level: return is a pointer type and points-to const double.
TEST_F(StitchingFunctionTest_379, GetBounds_ReturnsPointerToConstDouble_379) {
  using R = getBounds_expr_t<StitchingFunction>;
  static_assert(std::is_pointer_v<R>, "getBounds() must return a pointer type");
  static_assert(std::is_same_v<std::remove_pointer_t<R>, const double>,
                "getBounds() must return pointer-to-const-double");
  SUCCEED();
}