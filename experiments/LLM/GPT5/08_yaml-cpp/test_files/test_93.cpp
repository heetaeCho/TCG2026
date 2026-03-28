// File: test/depthguard_test.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"

namespace {

TEST(DepthGuardTest_93, TypeTraits_NonCopyableNonMovable_93) {
  using Guard = YAML::DepthGuard<10>;

  static_assert(!std::is_copy_constructible_v<Guard>,
                "DepthGuard must not be copy constructible");
  static_assert(!std::is_move_constructible_v<Guard>,
                "DepthGuard must not be move constructible");
  static_assert(!std::is_copy_assignable_v<Guard>,
                "DepthGuard must not be copy assignable");
  static_assert(!std::is_move_assignable_v<Guard>,
                "DepthGuard must not be move assignable");

  static_assert(std::is_same_v<decltype(std::declval<const Guard&>().current_depth()), int>,
                "current_depth() must return int");
}

TEST(DepthGuardTest_93, CurrentDepthTracksExternalDepthChanges_93) {
  int depth = 3;
  const YAML::Mark mark;  // default-constructible in yaml-cpp
  YAML::DepthGuard<10> guard(depth, mark, "depth message");

  const int baseline = guard.current_depth();
  depth += 7;

  EXPECT_EQ(guard.current_depth(), baseline + 7);
}

TEST(DepthGuardTest_93, CurrentDepthTracksNegativeDepthChanges_93) {
  int depth = -1;
  const YAML::Mark mark;
  YAML::DepthGuard<10> guard(depth, mark, "neg depth");

  const int baseline = guard.current_depth();
  depth -= 4;

  EXPECT_EQ(guard.current_depth(), baseline - 4);
}

TEST(DepthGuardTest_93, MultipleGuardsObserveSameDepthReference_93) {
  int depth = 0;
  const YAML::Mark mark;

  YAML::DepthGuard<10> guard1(depth, mark, "g1");
  YAML::DepthGuard<10> guard2(depth, mark, "g2");

  const int b1 = guard1.current_depth();
  const int b2 = guard2.current_depth();

  depth += 2;

  EXPECT_EQ(guard1.current_depth(), b1 + 2);
  EXPECT_EQ(guard2.current_depth(), b2 + 2);
}

}  // namespace
