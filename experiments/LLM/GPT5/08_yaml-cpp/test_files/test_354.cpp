// TEST_ID: 354
#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {
namespace interval_type =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

using RightClosedLeftOpen_354 = interval_type::right_closed_left_open;

template <typename T, typename = void>
struct HasIncludeLeftEndpoint_354 : std::false_type {};
template <typename T>
struct HasIncludeLeftEndpoint_354<T, std::void_t<decltype(T::include_left_endpoint())>>
    : std::true_type {};
}  // namespace

// Compile-time checks (no assumptions about internal logic beyond the interface).
static_assert(noexcept(RightClosedLeftOpen_354::include_right_endpoint()),
              "include_right_endpoint() must be noexcept");
static_assert(RightClosedLeftOpen_354::include_right_endpoint(),
              "right_closed_left_open must include the right endpoint");

TEST(DragonboxIntervalTypeTest_354, IncludeRightEndpointReturnsTrue_354) {
  EXPECT_TRUE(RightClosedLeftOpen_354::include_right_endpoint());
}

TEST(DragonboxIntervalTypeTest_354, IncludeRightEndpointIsStableAcrossCalls_354) {
  const bool first = RightClosedLeftOpen_354::include_right_endpoint();
  const bool second = RightClosedLeftOpen_354::include_right_endpoint();
  EXPECT_EQ(first, second);
  EXPECT_TRUE(first);
}

TEST(DragonboxIntervalTypeTest_354, IncludeRightEndpointUsableInConstexprContext_354) {
  constexpr bool v = RightClosedLeftOpen_354::include_right_endpoint();
  EXPECT_TRUE(v);
}

TEST(DragonboxIntervalTypeTest_354, IncludeLeftEndpointIfPresentIsCallableAndNoexcept_354) {
  if constexpr (HasIncludeLeftEndpoint_354<RightClosedLeftOpen_354>::value) {
    static_assert(noexcept(RightClosedLeftOpen_354::include_left_endpoint()),
                  "include_left_endpoint() must be noexcept if present");
    constexpr bool v = RightClosedLeftOpen_354::include_left_endpoint();
    (void)v;  // We don't assert the value (not provided by the interface snippet).
    SUCCEED();
  } else {
    SUCCEED();
  }
}