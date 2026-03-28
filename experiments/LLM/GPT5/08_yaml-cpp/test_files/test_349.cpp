// TEST_ID: 349
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using OpenInterval =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::open;

TEST(DragonboxIntervalOpenTest_349, IncludeLeftEndpointIsFalse_349) {
  // Observable behavior provided by the partial implementation.
  EXPECT_FALSE(OpenInterval::include_left_endpoint());

  // Also verify it's stable across calls (no inference about internals).
  EXPECT_EQ(OpenInterval::include_left_endpoint(),
            OpenInterval::include_left_endpoint());
}

TEST(DragonboxIntervalOpenTest_349, IncludeRightEndpointIsConstexprAndNoexcept_349) {
  // Verify the function is usable in constant-evaluation context.
  // (This asserts "constexpr-compatibility" without assuming any specific value.)
  constexpr bool right = OpenInterval::include_right_endpoint();
  (void)right;

  // Verify it is declared/implemented as noexcept (observable via type system).
  static_assert(noexcept(OpenInterval::include_right_endpoint()),
                "include_right_endpoint() must be noexcept");

  // Runtime: verify it's callable and returns a bool consistently.
  const bool r1 = OpenInterval::include_right_endpoint();
  const bool r2 = OpenInterval::include_right_endpoint();
  EXPECT_EQ(r1, r2);
}

TEST(DragonboxIntervalOpenTest_349, IncludeLeftEndpointIsConstexprAndNoexcept_349) {
  // Even though we also check runtime behavior, ensure constexpr/noexcept as well.
  constexpr bool left = OpenInterval::include_left_endpoint();
  static_assert(left == false, "include_left_endpoint() must be false");
  static_assert(noexcept(OpenInterval::include_left_endpoint()),
                "include_left_endpoint() must be noexcept");
}

}  // namespace