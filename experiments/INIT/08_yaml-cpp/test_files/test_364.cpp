// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_toward_minus_infinity_test_364.cpp

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using RoundingPolicy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_minus_infinity_t;

using Tag = RoundingPolicy;

class NearestTowardMinusInfinityRoundingTest_364 : public ::testing::Test {};

struct CaptureArgsFunctor {
  bool* called = nullptr;
  int* got_i = nullptr;
  std::string* got_s = nullptr;

  // Accept Tag first (as specified by delegate), then forwarded args.
  int operator()(Tag, int i, std::string s) const {
    if (called) *called = true;
    if (got_i) *got_i = i;
    if (got_s) *got_s = std::move(s);
    return 12345;
  }
};

struct ReturnTypeFunctor {
  long operator()(Tag, int x) const { return static_cast<long>(x) * 10L; }
};

struct MoveOnlyFunctor {
  int operator()(Tag, std::unique_ptr<int> p) const { return p ? *p : -1; }
};

struct ConstexprFunctor {
  // Must be usable in a constant-evaluated context.
  constexpr int operator()(Tag, int x, int y) const { return x + y; }
};

struct NoexceptFunctor {
  int operator()(Tag, int x) const noexcept { return x + 1; }
};

struct ThrowingFunctor {
  int operator()(Tag, int) const { throw std::runtime_error("boom"); }
};

TEST_F(NearestTowardMinusInfinityRoundingTest_364, DelegateInvokesFunctorAndPassesArgs_364) {
  bool called = false;
  int got_i = 0;
  std::string got_s;

  CaptureArgsFunctor f;
  f.called = &called;
  f.got_i = &got_i;
  f.got_s = &got_s;

  // SignedSignificandBits parameter exists but is not part of the callable signature.
  const int signed_bits = 7;

  int ret = RoundingPolicy::delegate(signed_bits, f, 42, std::string("hello"));

  EXPECT_TRUE(called);
  EXPECT_EQ(got_i, 42);
  EXPECT_EQ(got_s, "hello");
  EXPECT_EQ(ret, 12345);
}

TEST_F(NearestTowardMinusInfinityRoundingTest_364, DelegatePropagatesReturnValueAndType_364) {
  // Return type should be whatever the functor returns.
  static_assert(std::is_same_v<decltype(RoundingPolicy::delegate(0, ReturnTypeFunctor{}, 3)), long>);

  long ret = RoundingPolicy::delegate(0, ReturnTypeFunctor{}, 3);
  EXPECT_EQ(ret, 30L);
}

TEST_F(NearestTowardMinusInfinityRoundingTest_364, DelegateWorksWithMoveOnlyArguments_364) {
  auto p = std::make_unique<int>(99);
  int ret = RoundingPolicy::delegate(0, MoveOnlyFunctor{}, std::move(p));
  EXPECT_EQ(ret, 99);
}

TEST_F(NearestTowardMinusInfinityRoundingTest_364, DelegateIsUsableInConstexprContext_364) {
  // If delegate is truly constexpr-capable for this call, this should compile and pass.
  constexpr int v = RoundingPolicy::delegate(0, ConstexprFunctor{}, 2, 5);
  static_assert(v == 7);
  EXPECT_EQ(v, 7);
}

TEST_F(NearestTowardMinusInfinityRoundingTest_364, DelegateIsNoexcept_364) {
  // The delegate function is declared noexcept, so the call expression should be noexcept.
  static_assert(noexcept(RoundingPolicy::delegate(0, NoexceptFunctor{}, 1)));
  EXPECT_EQ(RoundingPolicy::delegate(0, NoexceptFunctor{}, 10), 11);
}

TEST_F(NearestTowardMinusInfinityRoundingTest_364, SignedSignificandBitsDoesNotAffectArgumentPassing_364) {
  bool called1 = false, called2 = false;
  int got_i1 = 0, got_i2 = 0;
  std::string got_s1, got_s2;

  CaptureArgsFunctor f1;
  f1.called = &called1;
  f1.got_i = &got_i1;
  f1.got_s = &got_s1;

  CaptureArgsFunctor f2;
  f2.called = &called2;
  f2.got_i = &got_i2;
  f2.got_s = &got_s2;

  (void)RoundingPolicy::delegate(0, f1, 7, std::string("x"));
  (void)RoundingPolicy::delegate(999999, f2, 7, std::string("x"));

  EXPECT_TRUE(called1);
  EXPECT_TRUE(called2);
  EXPECT_EQ(got_i1, got_i2);
  EXPECT_EQ(got_s1, got_s2);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(NearestTowardMinusInfinityRoundingTest_364, DelegateTerminatesIfFunctorThrows_364) {
  // delegate is noexcept; a throw escaping should terminate.
  EXPECT_DEATH(
      {
        // Use a volatile to discourage over-optimization in some build modes.
        volatile int sink = RoundingPolicy::delegate(0, ThrowingFunctor{}, 1);
        (void)sink;
      },
      "");
}
#endif

}  // namespace