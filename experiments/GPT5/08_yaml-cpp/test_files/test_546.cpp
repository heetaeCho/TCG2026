// test_depthguard_546.cpp
#include <gtest/gtest.h>

#include <limits>
#include <string>
#include <type_traits>

#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"

namespace {

using YAML::DepthGuard;
using YAML::Mark;

class DepthGuardTest_546 : public ::testing::Test {};

TEST_F(DepthGuardTest_546, CurrentDepthMatchesReferencedDepth_546) {
  int depth = 3;
  DepthGuard<10> guard(depth, Mark(), std::string("msg"));

  // Observable behavior: current_depth() should reflect the same depth variable
  // used to construct the guard.
  EXPECT_EQ(guard.current_depth(), depth);
}

TEST_F(DepthGuardTest_546, DestructorDecrementsDepthByOneOnScopeExit_546) {
  int depth = 7;

  int depth_during_lifetime = 0;
  {
    DepthGuard<10> guard(depth, Mark(), std::string("msg"));
    depth_during_lifetime = depth;  // capture value while guard is alive
    EXPECT_EQ(guard.current_depth(), depth);
  }

  // Based on the provided destructor: ~DepthGuard() { --m_depth; }
  EXPECT_EQ(depth, depth_during_lifetime - 1);
}

TEST_F(DepthGuardTest_546, NestedGuardsEachDecrementDepthOnTheirOwnScopeExit_546) {
  int depth = 0;

  int depth_after_outer_construct = 0;
  int depth_after_inner_construct = 0;

  {
    DepthGuard<10> outer(depth, Mark(), std::string("outer"));
    depth_after_outer_construct = depth;

    {
      DepthGuard<10> inner(depth, Mark(), std::string("inner"));
      depth_after_inner_construct = depth;
      EXPECT_EQ(inner.current_depth(), depth);
    }

    // After inner guard destruction, depth should be decremented by 1
    // relative to what it was while inner guard was alive.
    EXPECT_EQ(depth, depth_after_inner_construct - 1);
    EXPECT_EQ(outer.current_depth(), depth);
  }

  // After outer guard destruction, depth should be decremented by 1
  // relative to what it was while outer guard was alive.
  EXPECT_EQ(depth, depth_after_outer_construct - 1);
}

TEST_F(DepthGuardTest_546, DestructorDecrementsFromZeroToNegative_546) {
  int depth = 0;

  int depth_during_lifetime = 0;
  {
    DepthGuard<10> guard(depth, Mark(), std::string("msg"));
    depth_during_lifetime = depth;
  }

  // If depth was 0 (or any value) during lifetime, destructor decrements by 1.
  EXPECT_EQ(depth, depth_during_lifetime - 1);
}

TEST_F(DepthGuardTest_546, CopyAndMoveOperationsAreNotAllowed_546) {
  using DG = DepthGuard<10>;

  // The interface declares copy/move ctor and assignment deleted.
  EXPECT_FALSE(std::is_copy_constructible<DG>::value);
  EXPECT_FALSE(std::is_move_constructible<DG>::value);
  EXPECT_FALSE(std::is_copy_assignable<DG>::value);
  EXPECT_FALSE(std::is_move_assignable<DG>::value);
}

}  // namespace