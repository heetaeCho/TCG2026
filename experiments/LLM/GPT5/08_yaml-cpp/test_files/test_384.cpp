// File: dragonbox_384_test.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

// Handy aliases to keep tests readable.
using Policy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::away_from_zero_t;
using Tag = YAML::jkj::dragonbox::detail::right_closed_directed_t;

// A functor that records what it was called with.
struct RecordingFunctor {
  int call_count = 0;
  int last_a = 0;
  long long last_b = 0;

  constexpr int operator()(Tag, int a, long long b) noexcept {
    ++call_count;
    last_a = a;
    last_b = b;
    return a + static_cast<int>(b);
  }
};

// Two-overload functor used to verify the *tag* drives overload resolution.
struct OverloadByTagFunctor {
  constexpr int operator()(Tag, int v) const noexcept { return v + 1; }

  struct OtherTag {};
  constexpr int operator()(OtherTag, int v) const noexcept { return v + 999; }
};

// No-arg functor to verify empty parameter pack forwarding.
struct NoArgFunctor {
  constexpr int operator()(Tag) const noexcept { return 1234; }
};

}  // namespace

TEST(AwayFromZeroTTest_384, DelegateReturnsFunctorResult_384) {
  RecordingFunctor f{};
  const int signed_bits_dummy = 42;

  const int out = Policy::delegate(signed_bits_dummy, f, 7, 11LL);

  EXPECT_EQ(out, 18);
  EXPECT_EQ(f.call_count, 1);
}

TEST(AwayFromZeroTTest_384, DelegateForwardsArgsUnmodified_384) {
  RecordingFunctor f{};
  const unsigned signed_bits_dummy = 0;

  (void)Policy::delegate(signed_bits_dummy, f, -3, 100LL);

  EXPECT_EQ(f.call_count, 1);
  EXPECT_EQ(f.last_a, -3);
  EXPECT_EQ(f.last_b, 100LL);
}

TEST(AwayFromZeroTTest_384, DelegateUsesRightClosedDirectedTag_384) {
  OverloadByTagFunctor f{};
  const int signed_bits_dummy = 1;

  // If delegate uses Tag, this picks the Tag overload (v + 1), not v + 999.
  const int out = Policy::delegate(signed_bits_dummy, f, 10);

  EXPECT_EQ(out, 11);
}

TEST(AwayFromZeroTTest_384, DelegateWorksWithEmptyArgsPack_384) {
  NoArgFunctor f{};
  const int signed_bits_dummy = 0;

  const int out = Policy::delegate(signed_bits_dummy, f);

  EXPECT_EQ(out, 1234);
}

TEST(AwayFromZeroTTest_384, DelegateIsNoexceptWhenFunctorIsNoexcept_384) {
  NoArgFunctor f{};
  const int signed_bits_dummy = 0;

  static_assert(noexcept(Policy::delegate(signed_bits_dummy, f)),
                "delegate should be noexcept for noexcept functors");
}

TEST(AwayFromZeroTTest_384, DelegateUsableInConstantExpression_384) {
  constexpr NoArgFunctor f{};
  constexpr int signed_bits_dummy = 0;

  constexpr int out = Policy::delegate(signed_bits_dummy, f);
  static_assert(out == 1234, "delegate should be constexpr-evaluable");
  EXPECT_EQ(out, 1234);
}