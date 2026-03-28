// depthguard_test_92.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <string>

#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"

namespace {

using DepthGuard92 = YAML::DepthGuard<10>;

TEST(DepthGuardTest_92, DestructorDecrementsDepthByOneRelativeToDepthDuringLifetime_92) {
  int depth = 0;
  const YAML::Mark mark;
  const std::string msg = "depth guard";

  int depth_during_lifetime = 0;
  {
    DepthGuard92 guard(depth, mark, msg);
    depth_during_lifetime = depth;

    // If current_depth() is exposed, it should reflect the observable depth while alive.
    EXPECT_EQ(guard.current_depth(), depth);
  }

  // Only rely on the observable destructor effect relative to the value during lifetime.
  EXPECT_EQ(depth, depth_during_lifetime - 1);
}

TEST(DepthGuardTest_92, CurrentDepthTracksReferencedDepthWhenDepthChangesExternally_92) {
  int depth = 7;
  const YAML::Mark mark;
  const std::string msg = "depth guard";

  DepthGuard92 guard(depth, mark, msg);

  EXPECT_EQ(guard.current_depth(), depth);

  // Change the referenced depth through the external reference and observe via the public API.
  ++depth;
  EXPECT_EQ(guard.current_depth(), depth);

  depth += 10;
  EXPECT_EQ(guard.current_depth(), depth);
}

TEST(DepthGuardTest_92, NestedGuardsEachDecrementOnceOnScopeExit_92) {
  int depth = 0;
  const YAML::Mark mark;
  const std::string msg = "depth guard";

  int depth_after_inner_destruct = 0;

  {
    DepthGuard92 outer(depth, mark, msg);
    EXPECT_EQ(outer.current_depth(), depth);

    int depth_during_inner = 0;
    {
      DepthGuard92 inner(depth, mark, msg);
      EXPECT_EQ(inner.current_depth(), depth);
      depth_during_inner = depth;
    }

    // Inner guard destroyed: depth should decrease by 1 relative to the value observed during inner lifetime.
    EXPECT_EQ(depth, depth_during_inner - 1);

    // Record depth while outer is still alive; then ensure outer destruction decrements once more.
    depth_after_inner_destruct = depth;
    EXPECT_EQ(outer.current_depth(), depth);
  }

  // Outer guard destroyed: depth should decrease by 1 relative to the value after inner destruction.
  EXPECT_EQ(depth, depth_after_inner_destruct - 1);
}

TEST(DepthGuardTest_92, TypeIsNotCopyableOrMovable_92) {
  static_assert(!std::is_copy_constructible_v<DepthGuard92>, "DepthGuard should not be copy-constructible");
  static_assert(!std::is_copy_assignable_v<DepthGuard92>, "DepthGuard should not be copy-assignable");
  static_assert(!std::is_move_constructible_v<DepthGuard92>, "DepthGuard should not be move-constructible");
  static_assert(!std::is_move_assignable_v<DepthGuard92>, "DepthGuard should not be move-assignable");

  SUCCEED();
}

}  // namespace
