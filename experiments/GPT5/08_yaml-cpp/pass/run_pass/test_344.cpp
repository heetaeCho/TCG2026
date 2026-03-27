// File: ./TestProjects/yaml-cpp/test/dragonbox_symmetric_boundary_test_344.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::symmetric_boundary;

TEST(SymmetricBoundaryTest_344, IncludeRightEndpointReflectsIsClosedFalse_344) {
  symmetric_boundary sb{};
  sb.is_closed = false;

  EXPECT_FALSE(sb.include_right_endpoint());
}

TEST(SymmetricBoundaryTest_344, IncludeRightEndpointReflectsIsClosedTrue_344) {
  symmetric_boundary sb{};
  sb.is_closed = true;

  EXPECT_TRUE(sb.include_right_endpoint());
}

TEST(SymmetricBoundaryTest_344, IncludeRightEndpointTracksMutationOfIsClosed_344) {
  symmetric_boundary sb{};
  sb.is_closed = false;
  EXPECT_FALSE(sb.include_right_endpoint());

  sb.is_closed = true;
  EXPECT_TRUE(sb.include_right_endpoint());

  sb.is_closed = false;
  EXPECT_FALSE(sb.include_right_endpoint());
}

TEST(SymmetricBoundaryTest_344, IncludeRightEndpointIsCallableOnConstObject_344) {
  symmetric_boundary sb{};
  sb.is_closed = true;

  const symmetric_boundary& csb = sb;
  EXPECT_TRUE(csb.include_right_endpoint());
}

// Verify constexpr usability (observable at compile time).
static_assert([] {
  constexpr symmetric_boundary sb_true{true};
  return sb_true.include_right_endpoint() == true;
}());

static_assert([] {
  constexpr symmetric_boundary sb_false{false};
  return sb_false.include_right_endpoint() == false;
}());

}  // namespace