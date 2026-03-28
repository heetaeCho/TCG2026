// TEST_ID: 351
#include <gtest/gtest.h>

#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Interval =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::left_closed_right_open;

TEST(LeftClosedRightOpenTest_351, IncludeLeftEndpointIsTrue_351) {
    // Compile-time verification (the provided interface shows this returns true).
    static_assert(Interval::include_left_endpoint() == true,
                  "left_closed_right_open must include the left endpoint");

    // Runtime verification (observable behavior through the public interface).
    EXPECT_TRUE(Interval::include_left_endpoint());
}

TEST(LeftClosedRightOpenTest_351, IncludeLeftEndpointIsNoexceptAndBool_351) {
    static_assert(noexcept(Interval::include_left_endpoint()),
                  "include_left_endpoint() should be noexcept");
    static_assert(std::is_same_v<decltype(Interval::include_left_endpoint()), bool>,
                  "include_left_endpoint() should return bool");

    (void)Interval::include_left_endpoint();  // Ensures the call is well-formed.
}

TEST(LeftClosedRightOpenTest_351, IncludeRightEndpointIsCallableNoexceptAndBool_351) {
    // Only verify properties that are observable from the interface:
    // - callable
    // - noexcept
    // - returns bool
    static_assert(noexcept(Interval::include_right_endpoint()),
                  "include_right_endpoint() should be noexcept");
    static_assert(std::is_same_v<decltype(Interval::include_right_endpoint()), bool>,
                  "include_right_endpoint() should return bool");

    const bool v = Interval::include_right_endpoint();
    (void)v;  // No assumption about the returned value.
}

}  // namespace