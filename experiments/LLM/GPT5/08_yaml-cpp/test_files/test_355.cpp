#include <type_traits>
#include <utility>

#include <gtest/gtest.h>

#include "yaml-cpp/src/contrib/dragonbox.h"

namespace {

// The class under test lives in:
// YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_t
using NearestToEven =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_t;

// Helper functors to observe delegate() behavior without relying on internals.

struct ReturnSentinelFunctor_355 {
  // Accept the policy tag as first argument and forward remaining args.
  template <class Tag, class... Args>
  constexpr int operator()(Tag, Args&&...) const noexcept {
    return 12345;
  }
};

struct ForwardOneArgFunctor_355 {
  template <class Tag, class T>
  constexpr int operator()(Tag, T v) const noexcept {
    return static_cast<int>(v);
  }
};

struct ForwardTwoArgsFunctor_355 {
  template <class Tag, class A, class B>
  constexpr long long operator()(Tag, A a, B b) const noexcept {
    return static_cast<long long>(a) + static_cast<long long>(b);
  }
};

struct CaptureTagTypeFunctor_355 {
  template <class Tag>
  constexpr bool operator()(Tag) const noexcept {
    // Ensure the tag is the expected type.
    return std::is_same_v<std::decay_t<Tag>, NearestToEven>;
  }
};

struct NoexceptProbeFunctor_355 {
  template <class Tag>
  constexpr int operator()(Tag) const noexcept {
    return 7;
  }
};

struct DeletedDefaultCtorFunctor_355 {
  DeletedDefaultCtorFunctor_355() = delete;
  explicit DeletedDefaultCtorFunctor_355(int) {}
  template <class Tag>
  int operator()(Tag) const noexcept {
    return 1;
  }
};

}  // namespace

// TEST_ID = 355

TEST(NearestToEvenDelegateTest_355, ReturnsFunctorResult_NoArgs_355) {
  // SignedSignificandBits is not used for observable behavior; just provide an instance.
  constexpr int dummy_bits = 0;

  const int result = NearestToEven::delegate(dummy_bits, ReturnSentinelFunctor_355{});
  EXPECT_EQ(result, 12345);
}

TEST(NearestToEvenDelegateTest_355, ForwardsSingleArgument_355) {
  constexpr int dummy_bits = 1;

  const int result = NearestToEven::delegate(dummy_bits, ForwardOneArgFunctor_355{}, 42);
  EXPECT_EQ(result, 42);
}

TEST(NearestToEvenDelegateTest_355, ForwardsMultipleArguments_355) {
  constexpr int dummy_bits = 2;

  const long long result =
      NearestToEven::delegate(dummy_bits, ForwardTwoArgsFunctor_355{}, 10, 20);
  EXPECT_EQ(result, 30);
}

TEST(NearestToEvenDelegateTest_355, PassesNearestToEvenTagAsFirstParameter_355) {
  constexpr int dummy_bits = 3;

  const bool ok = NearestToEven::delegate(dummy_bits, CaptureTagTypeFunctor_355{});
  EXPECT_TRUE(ok);
}

TEST(NearestToEvenDelegateTest_355, CanBeUsedInConstantExpression_355) {
  constexpr int dummy_bits = 4;

  constexpr int value = NearestToEven::delegate(dummy_bits, ReturnSentinelFunctor_355{});
  static_assert(value == 12345, "delegate() should be usable in constexpr context");
  EXPECT_EQ(value, 12345);
}

TEST(NearestToEvenDelegateTest_355, DelegateIsNoexceptWhenFunctorCallIsNoexcept_355) {
  constexpr int dummy_bits = 5;

  // If the underlying invocation is noexcept, delegate should be noexcept as declared.
  static_assert(noexcept(NearestToEven::delegate(dummy_bits, NoexceptProbeFunctor_355{})),
                "delegate() should be noexcept for noexcept functors");
  EXPECT_EQ(NearestToEven::delegate(dummy_bits, NoexceptProbeFunctor_355{}), 7);
}

TEST(NearestToEvenDelegateTest_355, WorksWithNonDefaultConstructibleFunctorViaPassedInstance_355) {
  constexpr int dummy_bits = 6;

  // Even though delegate's return type uses Func{} in decltype, the call should use the passed f.
  // This test ensures we can pass an instance that is not default-constructible.
  DeletedDefaultCtorFunctor_355 f(1);
  const int result = NearestToEven::delegate(dummy_bits, f);
  EXPECT_EQ(result, 1);
}