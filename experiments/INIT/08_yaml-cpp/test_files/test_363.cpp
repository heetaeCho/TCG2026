// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_toward_plus_infinity_shorter_interval_test.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// A small helper type to serve as SignedSignificandBits for the templated API.
// It provides is_negative() and also lets us observe how many times it is called.
// NOTE: shorter_interval takes its argument by value, so the call counter must be
// shared across copies (we use an int*).
struct SignedBitsProbe {
  bool negative{};
  int* calls{nullptr};

  constexpr bool is_negative() const noexcept {
    if (calls) {
      ++(*calls);
    }
    return negative;
  }
};

}  // namespace

// Bring the type under test into a shorter alias.
using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::
    nearest_toward_plus_infinity_t;

TEST(NearestTowardPlusInfinityShorterIntervalTest_363,
     PositiveSignedBitsYieldsExpectedBoundary_363) {
  SignedBitsProbe s{false, nullptr};

  const auto result = Policy::shorter_interval(s);

  // Observable behavior: the implementation constructs asymmetric_boundary from
  // a boolean expression; we validate by comparing to the same construction.
  const auto expected =
      decltype(result){true};  // !false == true
  EXPECT_EQ(result, expected);
}

TEST(NearestTowardPlusInfinityShorterIntervalTest_363,
     NegativeSignedBitsYieldsExpectedBoundary_363) {
  SignedBitsProbe s{true, nullptr};

  const auto result = Policy::shorter_interval(s);

  const auto expected =
      decltype(result){false};  // !true == false
  EXPECT_EQ(result, expected);
}

TEST(NearestTowardPlusInfinityShorterIntervalTest_363,
     CallsIsNegativeExactlyOnce_363) {
  int calls = 0;
  SignedBitsProbe s{true, &calls};

  (void)Policy::shorter_interval(s);

  EXPECT_EQ(calls, 1);
}

TEST(NearestTowardPlusInfinityShorterIntervalTest_363,
     IsNoexceptAndDoesNotThrow_363) {
  SignedBitsProbe s{false, nullptr};

  EXPECT_TRUE(noexcept(Policy::shorter_interval(s)));
  EXPECT_NO_THROW((void)Policy::shorter_interval(s));
}

TEST(NearestTowardPlusInfinityShorterIntervalTest_363,
     UsableInConstexprContext_363) {
  // This test primarily ensures the API can be used in a constexpr context.
  // We avoid asserting on fields that may not be publicly exposed.
  constexpr SignedBitsProbe s{false, nullptr};
  constexpr auto r = Policy::shorter_interval(s);
  (void)r;

  SUCCEED();
}
``