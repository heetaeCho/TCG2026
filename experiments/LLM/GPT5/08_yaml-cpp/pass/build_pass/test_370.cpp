#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

#include <string>
#include <type_traits>

namespace {

using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_away_from_zero_t;

// Verifies the policy tag type and returns a computed value.
struct TagAndArgsFunc {
  int* call_count = nullptr;

  constexpr TagAndArgsFunc() = default;
  explicit constexpr TagAndArgsFunc(int* c) : call_count(c) {}

  constexpr int operator()(Policy /*tag*/, int a, int b) const {
    if (call_count) {
      ++(*call_count);
    }
    return a * 100 + b;
  }
};

// Supports zero additional args: only receives the policy tag.
struct NoExtraArgsFunc {
  int* call_count = nullptr;

  constexpr NoExtraArgsFunc() = default;
  explicit constexpr NoExtraArgsFunc(int* c) : call_count(c) {}

  constexpr int operator()(Policy /*tag*/) const {
    if (call_count) {
      ++(*call_count);
    }
    return 42;
  }
};

// Returns a reference to validate return type propagation.
struct RefReturnFunc {
  static std::string& Storage() {
    static std::string s = "ref-storage";
    return s;
  }

  constexpr RefReturnFunc() = default;

  const std::string& operator()(Policy /*tag*/) const { return Storage(); }
};

// A constexpr-friendly functor for compile-time checks.
struct ConstexprSumFunc {
  constexpr ConstexprSumFunc() = default;

  constexpr int operator()(Policy /*tag*/, int x, int y) const { return x + y; }
};

}  // namespace

TEST(NearestAwayFromZeroDelegateTest_370, CallsFunctorWithPolicyTagAndArgs_370) {
  int calls = 0;
  TagAndArgsFunc f(&calls);

  // SignedSignificandBits is a separate parameter; use a representative value.
  const int result = Policy::delegate(123, f, 7, 9);

  EXPECT_EQ(calls, 1);
  EXPECT_EQ(result, 709);  // a*100 + b
}

TEST(NearestAwayFromZeroDelegateTest_370, WorksWithNoExtraArgs_370) {
  int calls = 0;
  NoExtraArgsFunc f(&calls);

  const int result = Policy::delegate(0, f);

  EXPECT_EQ(calls, 1);
  EXPECT_EQ(result, 42);
}

TEST(NearestAwayFromZeroDelegateTest_370, PropagatesReferenceReturnType_370) {
  RefReturnFunc f;

  const std::string& ref = Policy::delegate(0, f);

  EXPECT_EQ(&ref, &RefReturnFunc::Storage());
  EXPECT_EQ(ref, "ref-storage");
}

TEST(NearestAwayFromZeroDelegateTest_370, IsNoexcept_370) {
  TagAndArgsFunc f;
  static_assert(noexcept(Policy::delegate(0, f, 1, 2)),
                "delegate should be noexcept as declared");
  EXPECT_TRUE((noexcept(Policy::delegate(0, f, 1, 2))));
}

TEST(NearestAwayFromZeroDelegateTest_370, IsUsableInConstantExpressions_370) {
  constexpr ConstexprSumFunc f{};
  constexpr int v = Policy::delegate(0, f, 10, 20);
  static_assert(v == 30, "constexpr delegate call should work");

  EXPECT_EQ(v, 30);
}

TEST(NearestAwayFromZeroDelegateTest_370, AcceptsDifferentSignedSignificandBitsTypes_370) {
  TagAndArgsFunc f;

  // Just verify it compiles and behaves the same regardless of this parameter type.
  const int r1 = Policy::delegate(1, f, 3, 4);
  const int r2 = Policy::delegate(std::integral_constant<int, 7>{}, f, 3, 4);

  EXPECT_EQ(r1, 304);
  EXPECT_EQ(r2, 304);
}