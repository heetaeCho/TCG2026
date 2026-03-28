// TEST_ID: 303
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::wuint::uint128;

class Uint128HighTest_303 : public ::testing::Test {};

TEST_F(Uint128HighTest_303, HighReturnsValueFromCtor_303) {
  const uint128 v{stdr::uint_least64_t{0x1122334455667788ULL},
                  stdr::uint_least64_t{0x99AABBCCDDEEFF00ULL}};
  EXPECT_EQ(v.high(), stdr::uint_least64_t{0x1122334455667788ULL});
}

TEST_F(Uint128HighTest_303, HighReflectsDirectlyAssignedPublicField_303) {
  uint128 v{};
  v.high_ = stdr::uint_least64_t{42};
  EXPECT_EQ(v.high(), stdr::uint_least64_t{42});

  v.high_ = stdr::uint_least64_t{0};
  EXPECT_EQ(v.high(), stdr::uint_least64_t{0});
}

TEST_F(Uint128HighTest_303, HighHandlesBoundaryValues_303) {
  const uint128 zero{stdr::uint_least64_t{0}, stdr::uint_least64_t{123}};
  EXPECT_EQ(zero.high(), stdr::uint_least64_t{0});

  const auto maxv = (std::numeric_limits<stdr::uint_least64_t>::max)();
  const uint128 vmax{maxv, stdr::uint_least64_t{0}};
  EXPECT_EQ(vmax.high(), maxv);
}

TEST_F(Uint128HighTest_303, HighIsNoexceptAndConstCallable_303) {
  const uint128 v{stdr::uint_least64_t{7}, stdr::uint_least64_t{9}};
  EXPECT_TRUE(noexcept(v.high()));

  // Also verify it can be called on a const reference.
  const uint128& cv = v;
  EXPECT_EQ(cv.high(), stdr::uint_least64_t{7});
}

TEST_F(Uint128HighTest_303, HighIsUsableInConstantEvaluation_303) {
  constexpr uint128 v{stdr::uint_least64_t{5}, stdr::uint_least64_t{6}};
  static_assert(v.high() == stdr::uint_least64_t{5}, "uint128::high() must be constexpr-usable");
  EXPECT_EQ(v.high(), stdr::uint_least64_t{5});
}

}  // namespace