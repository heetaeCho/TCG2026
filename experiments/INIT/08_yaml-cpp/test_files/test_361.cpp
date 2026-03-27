#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

// These tests treat the implementation as a black box and only verify observable behavior:
// - delegate forwards a tag object of type nearest_toward_plus_infinity_t as the first argument
// - delegate forwards remaining arguments in order
// - return value is exactly whatever the provided callable returns
// - callable is invoked exactly once
// - works with a "Func f" parameter that may be unused (as in the implementation)

namespace {

using YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_plus_infinity_t;

// A callable that records how it was called.
struct RecorderFunc_361 {
  // state that is observable by the test through this object (external interaction)
  static inline int calls = 0;
  static inline int last_a = 0;
  static inline long long last_b = 0;

  int operator()(nearest_toward_plus_infinity_t, int a, long long b) const noexcept {
    ++calls;
    last_a = a;
    last_b = b;
    return a + static_cast<int>(b);
  }

  static void Reset() {
    calls = 0;
    last_a = 0;
    last_b = 0;
  }
};

// A callable returning a non-trivial type to ensure decltype propagation works.
struct ReturnType_361 {
  int v;
  bool operator==(const ReturnType_361& other) const { return v == other.v; }
};

struct ReturnObjectFunc_361 {
  ReturnType_361 operator()(nearest_toward_plus_infinity_t, int x) const noexcept {
    return ReturnType_361{x * 2};
  }
};

// A callable that can accept a const ref argument to verify argument passing.
struct ConstRefArgFunc_361 {
  static inline int calls = 0;
  static inline int seen = 0;

  int operator()(nearest_toward_plus_infinity_t, const int& x) const noexcept {
    ++calls;
    seen = x;
    return x;
  }

  static void Reset() {
    calls = 0;
    seen = 0;
  }
};

}  // namespace

class NearestTowardPlusInfinityPolicyTest_361 : public ::testing::Test {
 protected:
  void SetUp() override {
    RecorderFunc_361::Reset();
    ConstRefArgFunc_361::Reset();
  }
};

TEST_F(NearestTowardPlusInfinityPolicyTest_361, DelegateInvokesCallableOnceAndReturnsValue_361) {
  // Arrange
  using Policy = nearest_toward_plus_infinity_t;
  RecorderFunc_361 func{};

  // Act
  // The first parameter (SignedSignificandBits) is unused by the implementation but required by signature.
  // The second parameter (Func f) is also unused by the implementation; we pass a default-constructible placeholder.
  struct UnusedF_361 {};
  const int result = Policy::delegate(0, UnusedF_361{}, 7, 5LL);

  // Assert
  EXPECT_EQ(RecorderFunc_361::calls, 1);
  EXPECT_EQ(RecorderFunc_361::last_a, 7);
  EXPECT_EQ(RecorderFunc_361::last_b, 5LL);
  EXPECT_EQ(result, 12);
}

TEST_F(NearestTowardPlusInfinityPolicyTest_361, DelegateForwardsArgumentsInOrder_361) {
  using Policy = nearest_toward_plus_infinity_t;

  // Use different values to ensure ordering is correct.
  RecorderFunc_361 func{};
  struct UnusedF_361 {};

  const int result = Policy::delegate(123, UnusedF_361{}, 42, 100LL);

  EXPECT_EQ(RecorderFunc_361::calls, 1);
  EXPECT_EQ(RecorderFunc_361::last_a, 42);
  EXPECT_EQ(RecorderFunc_361::last_b, 100LL);
  EXPECT_EQ(result, 142);
}

TEST_F(NearestTowardPlusInfinityPolicyTest_361, DelegatePropagatesNonTrivialReturnType_361) {
  using Policy = nearest_toward_plus_infinity_t;
  struct UnusedF_361 {};

  // This ensures the return type matches exactly what the callable returns.
  const ReturnType_361 out = Policy::delegate(0, UnusedF_361{}, 9);

  EXPECT_EQ(out, (ReturnType_361{18}));
}

TEST_F(NearestTowardPlusInfinityPolicyTest_361, DelegateAllowsConstRefArguments_361) {
  using Policy = nearest_toward_plus_infinity_t;
  struct UnusedF_361 {};

  int x = 33;
  const int result = Policy::delegate(0, UnusedF_361{}, x);

  EXPECT_EQ(ConstRefArgFunc_361::calls, 1);
  EXPECT_EQ(ConstRefArgFunc_361::seen, 33);
  EXPECT_EQ(result, 33);
}

TEST_F(NearestTowardPlusInfinityPolicyTest_361, DelegateCompilesAndIsNoexceptWhenCallableIsNoexcept_361) {
  using Policy = nearest_toward_plus_infinity_t;
  struct UnusedF_361 {};

  // If delegate is declared noexcept, this should be true regardless, but we keep it interface-driven.
  static_assert(noexcept(Policy::delegate(0, UnusedF_361{}, 1, 2LL)),
                "delegate should be noexcept per its signature");
}

TEST_F(NearestTowardPlusInfinityPolicyTest_361, DelegateWorksWithBoundaryIntegerValues_361) {
  using Policy = nearest_toward_plus_infinity_t;
  struct UnusedF_361 {};

  const int a = std::numeric_limits<int>::max();
  const long long b = 0;

  const int result = Policy::delegate(0, UnusedF_361{}, a, b);

  EXPECT_EQ(RecorderFunc_361::calls, 1);
  EXPECT_EQ(RecorderFunc_361::last_a, a);
  EXPECT_EQ(RecorderFunc_361::last_b, b);
  EXPECT_EQ(result, a);
}

// "Exceptional or error cases (if observable)":
// delegate is noexcept and takes no runtime error reporting; the only observable "error" case
// would be compilation failure or termination, neither of which is representable as a gtest runtime
// assertion without violating black-box constraints. The tests above cover observable interactions.