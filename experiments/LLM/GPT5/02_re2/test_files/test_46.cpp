// File: lazyre2_operator_star_test.cc
#include <gtest/gtest.h>
#include <type_traits>

// The production header under test.
#include "re2/re2.h"

using re2::LazyRE2;
using re2::RE2;

// -------------------------
// Test fixture (empty; black-box testing)
class LazyRE2_OperatorStar_Test_46 : public ::testing::Test {};

// 1) Compile-time: operator* must return RE2& (type-level check)
TEST_F(LazyRE2_OperatorStar_Test_46, DerefReturnsRE2Ref_46) {
  LazyRE2 lazy;
  // Type check in unevaluated context; does not invoke get() at runtime.
  using DerefType = decltype(*lazy);
  static_assert(std::is_same<DerefType, RE2&>::value,
                "operator* must return RE2&");
  SUCCEED();  // Reaches here if the static assertion compiles.
}

// 2) Runtime: &(*obj) must equal obj.get() when non-null
TEST_F(LazyRE2_OperatorStar_Test_46, AddressEqualsGetWhenNonNull_46) {
  LazyRE2 lazy;

  RE2* p = lazy.get();
  if (p == nullptr) {
    GTEST_SKIP() << "LazyRE2::get() returned nullptr; skipping safe deref check.";
  }

  // Observable behavior: operator* forwards exactly to get().
  EXPECT_EQ(p, &(*lazy));
}

// 3) Runtime: Repeated calls are consistent (idempotent address through operator* and get())
TEST_F(LazyRE2_OperatorStar_Test_46, RepeatedCallsYieldSameAddress_46) {
  LazyRE2 lazy;

  RE2* p1 = lazy.get();
  if (p1 == nullptr) {
    GTEST_SKIP() << "LazyRE2::get() returned nullptr; skipping safe deref consistency check.";
  }

  // Check consistency between operator* and get() across multiple calls.
  EXPECT_EQ(p1, &(*lazy));

  RE2* p2 = lazy.get();
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, &(*lazy));
}

// 4) Const object: const-qualified operator* still yields the same address as get()
TEST_F(LazyRE2_OperatorStar_Test_46, ConstObjectAddressEqualsGet_46) {
  LazyRE2 lazy;
  const LazyRE2& clazy = lazy;

  RE2* p = clazy.get();
  if (p == nullptr) {
    GTEST_SKIP() << "LazyRE2::get() returned nullptr on const object; skipping safe deref check.";
  }

  // Even through a const reference, operator* must refer to the same RE2 instance.
  EXPECT_EQ(p, &(*clazy));
}
