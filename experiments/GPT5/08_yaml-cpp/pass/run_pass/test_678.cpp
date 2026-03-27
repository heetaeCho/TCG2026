// TEST_ID: 678
#include <gtest/gtest.h>

#include <type_traits>
#include <string>

#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"

// DeepRecursion is thrown by DepthGuard when max depth is exceeded.
// In yaml-cpp it is typically declared in exceptions.h. If your build
// already brings it transitively via depthguard.h, this include is harmless;
// otherwise it is required for typed exception checks.
#include "yaml-cpp/exceptions.h"

namespace {

using YAML::Mark;

// Pick a small max depth to make boundary testing easy.
using Guard3 = YAML::DepthGuard<3>;

class DepthGuardTest_678 : public ::testing::Test {
protected:
  Mark mark_;
  std::string msg_{"depth message"};
};

TEST_F(DepthGuardTest_678, ConstructIncrementsDepthAndCurrentDepthMatches_678) {
  int depth = 0;
  {
    Guard3 g(depth, mark_, msg_);
    EXPECT_EQ(depth, 1);
    EXPECT_EQ(g.current_depth(), depth);
  }
}

TEST_F(DepthGuardTest_678, DestructorRestoresDepthOnScopeExit_678) {
  int depth = 0;
  {
    Guard3 g(depth, mark_, msg_);
    EXPECT_EQ(depth, 1);
  }
  // Observable RAII behavior: leaving scope should restore the original depth.
  EXPECT_EQ(depth, 0);
}

TEST_F(DepthGuardTest_678, NoThrowWhenBelowMaxDepthBoundary_678) {
  int depth = 1;  // For max_depth=3, ctor increments to 2, which should be allowed.
  EXPECT_NO_THROW({
    Guard3 g(depth, mark_, msg_);
    EXPECT_EQ(depth, 2);
    EXPECT_EQ(g.current_depth(), 2);
  });
  // After scope, depth should be restored.
  EXPECT_EQ(depth, 1);
}

TEST_F(DepthGuardTest_678, ThrowsDeepRecursionWhenReachingMaxDepth_678) {
  int depth = 2;  // For max_depth=3, ctor increments to 3 and should throw.
  try {
    Guard3 g(depth, mark_, msg_);
    FAIL() << "Expected YAML::DeepRecursion to be thrown";
  } catch (const YAML::DeepRecursion&) {
    // Constructor has observable side-effect through referenced depth.
    // If the ctor throws, the object is not constructed; no destructor runs.
    EXPECT_EQ(depth, 3);
  } catch (...) {
    FAIL() << "Expected YAML::DeepRecursion to be thrown";
  }
}

TEST_F(DepthGuardTest_678, CopyAndMoveAreDeleted_678) {
  static_assert(!std::is_copy_constructible_v<Guard3>, "DepthGuard should not be copy constructible");
  static_assert(!std::is_copy_assignable_v<Guard3>, "DepthGuard should not be copy assignable");
  static_assert(!std::is_move_constructible_v<Guard3>, "DepthGuard should not be move constructible");
  static_assert(!std::is_move_assignable_v<Guard3>, "DepthGuard should not be move assignable");

  SUCCEED();
}

}  // namespace