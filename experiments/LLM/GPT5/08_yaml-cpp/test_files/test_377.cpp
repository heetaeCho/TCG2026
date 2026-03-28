// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_to_even_static_boundary_test_377.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_static_boundary_t;

// A controllable "SignedSignificandBits" stand-in.
// We only rely on the public surface that delegate uses: has_even_significand_bits().
struct FakeSignedSignificandBits_377 {
  bool even = false;
  constexpr bool has_even_significand_bits() const noexcept { return even; }
};

// A callable that can detect which tag type was passed and record received argument(s).
struct RecordingFunc_377 {
  enum class Which { kNone, kClosed, kOpen };

  Which which = Which::kNone;
  int received = 0;

  int operator()(YAML::jkj::dragonbox::detail::nearest_always_closed_t, int x) noexcept {
    which = Which::kClosed;
    received = x;
    return 111;
  }

  int operator()(YAML::jkj::dragonbox::detail::nearest_always_open_t, int x) noexcept {
    which = Which::kOpen;
    received = x;
    return 222;
  }
};

}  // namespace

class NearestToEvenStaticBoundaryTest_377 : public ::testing::Test {};

TEST_F(NearestToEvenStaticBoundaryTest_377, EvenSignificandBitsCallsNearestAlwaysClosed_377) {
  FakeSignedSignificandBits_377 bits{true};
  RecordingFunc_377 f;

  const int result = Policy::delegate(bits, f, 42);

  EXPECT_EQ(result, 111);
  EXPECT_EQ(f.which, RecordingFunc_377::Which::kClosed);
  EXPECT_EQ(f.received, 42);
}

TEST_F(NearestToEvenStaticBoundaryTest_377, OddSignificandBitsCallsNearestAlwaysOpen_377) {
  FakeSignedSignificandBits_377 bits{false};
  RecordingFunc_377 f;

  const int result = Policy::delegate(bits, f, -7);

  EXPECT_EQ(result, 222);
  EXPECT_EQ(f.which, RecordingFunc_377::Which::kOpen);
  EXPECT_EQ(f.received, -7);
}

TEST_F(NearestToEvenStaticBoundaryTest_377, DelegateIsNoexcept_377) {
  FakeSignedSignificandBits_377 bits{true};
  RecordingFunc_377 f;

  EXPECT_TRUE(noexcept(Policy::delegate(bits, f, 1)));
}

TEST_F(NearestToEvenStaticBoundaryTest_377, DelegateWorksInConstantEvaluation_377) {
  // Compile-time callable that returns different values by tag.
  struct ConstexprFunc_377 {
    constexpr int operator()(YAML::jkj::dragonbox::detail::nearest_always_closed_t, int x) const {
      return x + 1;
    }
    constexpr int operator()(YAML::jkj::dragonbox::detail::nearest_always_open_t, int x) const {
      return x + 2;
    }
  };

  {
    constexpr FakeSignedSignificandBits_377 bits{true};
    constexpr int out = Policy::delegate(bits, ConstexprFunc_377{}, 10);
    static_assert(out == 11, "Expected closed path for even significand bits");
    EXPECT_EQ(out, 11);
  }
  {
    constexpr FakeSignedSignificandBits_377 bits{false};
    constexpr int out = Policy::delegate(bits, ConstexprFunc_377{}, 10);
    static_assert(out == 12, "Expected open path for odd significand bits");
    EXPECT_EQ(out, 12);
  }
}

TEST_F(NearestToEvenStaticBoundaryTest_377, ReturnTypeMatchesCallableReturnType_377) {
  struct ReturnsLong_377 {
    long operator()(YAML::jkj::dragonbox::detail::nearest_always_closed_t, int) noexcept { return 5L; }
    long operator()(YAML::jkj::dragonbox::detail::nearest_always_open_t, int) noexcept { return 6L; }
  };

  FakeSignedSignificandBits_377 bits{true};
  ReturnsLong_377 f;

  using Ret = decltype(Policy::delegate(bits, f, 0));
  static_assert(std::is_same_v<Ret, long>, "delegate should return the callable's return type");

  EXPECT_EQ(Policy::delegate(bits, f, 0), 5L);
  bits.even = false;
  EXPECT_EQ(Policy::delegate(bits, f, 0), 6L);
}