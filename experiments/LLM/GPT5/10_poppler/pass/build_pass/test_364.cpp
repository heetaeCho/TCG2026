// TEST_ID: 364
// File: sampled_function_get_decode_min_test_364.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Poppler header under test
#include "Function.h"

namespace {

// Helper type-traits for member function detection without constructing objects.
template <typename T>
using getDecodeMin_expr_t =
    decltype(std::declval<const T&>().getDecodeMin(std::declval<int>()));

}  // namespace

// NOTE:
// The provided interface snippet exposes only:
//   double SampledFunction::getDecodeMin(int i) const
//
// In many Poppler builds, constructing a valid SampledFunction requires
// PDF Object/Dict/Stream setup. Since that construction API is not part of the
// provided interface snippet here, these tests focus on *observable interface
// guarantees* that can be verified without relying on internal state or
// re-implementing any logic.

TEST(SampledFunctionTest_364, GetDecodeMin_IsCallableOnConst_364) {
  // Verifies getDecodeMin can be invoked on a const instance (const-correctness).
  static_assert(std::is_same_v<getDecodeMin_expr_t<SampledFunction>, double>,
                "SampledFunction::getDecodeMin(int) must return double and be callable on const objects.");
  SUCCEED();
}

TEST(SampledFunctionTest_364, GetDecodeMin_MemberFunctionPointerType_364) {
  // Verifies the exact member function pointer type matches: double (SampledFunction::*)(int) const
  using Expected = double (SampledFunction::*)(int) const;
  Expected ptr = &SampledFunction::getDecodeMin;

  // If it compiles, the signature matches; additionally ensure the pointer is non-null.
  EXPECT_NE(ptr, nullptr);
}

TEST(SampledFunctionTest_364, GetDecodeMin_AcceptsIntParameterType_364) {
  // Boundary-ish compile-time check: the parameter is exactly int (not size_t, etc.).
  // Taking the address with an explicit type enforces the signature.
  double (SampledFunction::*ptr)(int) const = &SampledFunction::getDecodeMin;
  EXPECT_NE(ptr, nullptr);
}

TEST(SampledFunctionTest_364, GetDecodeMin_IsNotStatic_364) {
  // If it were static, &SampledFunction::getDecodeMin would be a plain function pointer.
  // Here we assert it's a member function pointer.
  EXPECT_TRUE((std::is_member_function_pointer_v<decltype(&SampledFunction::getDecodeMin)>));
}