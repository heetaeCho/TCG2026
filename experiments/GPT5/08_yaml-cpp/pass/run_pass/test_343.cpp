// File: ./TestProjects/yaml-cpp/test/dragonbox_symmetric_boundary_test_343.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::symmetric_boundary;

TEST(SymmetricBoundaryTest_343, ValueInitializationSetsIsClosedFalse_343) {
  symmetric_boundary b{};  // value-initialized => zero-initialized members
  EXPECT_FALSE(b.is_closed);
  EXPECT_FALSE(b.include_left_endpoint());
}

TEST(SymmetricBoundaryTest_343, IncludeLeftEndpointReflectsIsClosedTrue_343) {
  symmetric_boundary b{};
  b.is_closed = true;

  EXPECT_TRUE(b.include_left_endpoint());
}

TEST(SymmetricBoundaryTest_343, IncludeLeftEndpointReflectsIsClosedFalse_343) {
  symmetric_boundary b{};
  b.is_closed = false;

  EXPECT_FALSE(b.include_left_endpoint());
}

TEST(SymmetricBoundaryTest_343, IncludeRightEndpointIsCallableAndNoexcept_343) {
  symmetric_boundary b{};
  b.is_closed = false;

  // Observable through the interface: the function can be called and is noexcept.
  static_assert(noexcept(std::declval<const symmetric_boundary&>().include_right_endpoint()),
                "include_right_endpoint() must be noexcept");
  static_assert(std::is_same_v<decltype(std::declval<const symmetric_boundary&>().include_right_endpoint()), bool>,
                "include_right_endpoint() must return bool");

  // Runtime smoke call (no behavioral assumption about returned value).
  (void)b.include_right_endpoint();
  SUCCEED();
}

TEST(SymmetricBoundaryTest_343, IncludeRightEndpointIsConstCallable_343) {
  const symmetric_boundary b{true};

  // Verify it is callable on const objects (observable through compilation and callability).
  (void)b.include_right_endpoint();
  SUCCEED();
}

TEST(SymmetricBoundaryTest_343, IncludeLeftEndpointIsNoexceptAndReturnsBool_343) {
  static_assert(noexcept(std::declval<const symmetric_boundary&>().include_left_endpoint()),
                "include_left_endpoint() must be noexcept");
  static_assert(std::is_same_v<decltype(std::declval<const symmetric_boundary&>().include_left_endpoint()), bool>,
                "include_left_endpoint() must return bool");
  SUCCEED();
}

}  // namespace