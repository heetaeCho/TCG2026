// TEST_ID: 362
#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using RoundingPolicy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_plus_infinity_t;
using Boundary = YAML::jkj::dragonbox::interval_type::asymmetric_boundary;

// A minimal SignedSignificandBits model for exercising the templated interface.
// This is an external collaborator (template argument) and does not rely on any internal state.
struct FakeSignedSignificandBits_362 {
  bool neg{};
  constexpr bool is_negative() const noexcept { return neg; }
};

TEST(NearestTowardPlusInfinityRoundingTest_362, NormalInterval_PositiveSign_ReturnsExpectedBoundary_362) {
  constexpr FakeSignedSignificandBits_362 s{false};

  const auto boundary = RoundingPolicy::normal_interval(s);

  // Expected observable behavior: returns an asymmetric_boundary that can be constructed from a bool.
  EXPECT_EQ(boundary, Boundary{true});
}

TEST(NearestTowardPlusInfinityRoundingTest_362, NormalInterval_NegativeSign_ReturnsExpectedBoundary_362) {
  constexpr FakeSignedSignificandBits_362 s{true};

  const auto boundary = RoundingPolicy::normal_interval(s);

  EXPECT_EQ(boundary, Boundary{false});
}

TEST(NearestTowardPlusInfinityRoundingTest_362, NormalInterval_DifferentSigns_ProduceDifferentBoundaries_362) {
  constexpr FakeSignedSignificandBits_362 pos{false};
  constexpr FakeSignedSignificandBits_362 neg{true};

  const auto b_pos = RoundingPolicy::normal_interval(pos);
  const auto b_neg = RoundingPolicy::normal_interval(neg);

  EXPECT_NE(b_pos, b_neg);
}

TEST(NearestTowardPlusInfinityRoundingTest_362, NormalInterval_IsConstexprAndNoexcept_362) {
  static_assert(noexcept(RoundingPolicy::normal_interval(FakeSignedSignificandBits_362{false})),
                "normal_interval should be noexcept");

  // If normal_interval and the boundary type support constexpr evaluation, this should compile.
  constexpr auto b1 = RoundingPolicy::normal_interval(FakeSignedSignificandBits_362{false});
  constexpr auto b2 = RoundingPolicy::normal_interval(FakeSignedSignificandBits_362{true});

  static_assert(b1 == Boundary{true}, "Positive sign should yield Boundary{true} in constexpr context");
  static_assert(b2 == Boundary{false}, "Negative sign should yield Boundary{false} in constexpr context");
}

}  // namespace