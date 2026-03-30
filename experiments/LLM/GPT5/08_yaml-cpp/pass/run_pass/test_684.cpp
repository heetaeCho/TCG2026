// File: test/depthguard_test_684.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <string>

#include <yaml-cpp/depthguard.h>
#include <yaml-cpp/mark.h>

// DeepRecursion is referenced by DepthGuard's constructor in the provided code.
// In yaml-cpp it is typically declared in exceptions.h, so include it when available.
#include <yaml-cpp/exceptions.h>

namespace {

class DepthGuardTest_684 : public ::testing::Test {
 protected:
  YAML::Mark mark_{};
  std::string msg_{"depthguard test"};
};

TEST_F(DepthGuardTest_684, ConstructionIncrementsDepth_684) {
  int depth = 0;
  using Guard = YAML::DepthGuard<10>;

  Guard g(depth, mark_, msg_);
  EXPECT_EQ(depth, 1);
}

TEST_F(DepthGuardTest_684, DestructorRestoresDepthAfterScope_684) {
  int depth = 0;
  using Guard = YAML::DepthGuard<10>;

  {
    Guard g(depth, mark_, msg_);
    EXPECT_EQ(depth, 1);
  }

  // Observable RAII behavior: leaving scope should restore previous depth.
  EXPECT_EQ(depth, 0);
}

TEST_F(DepthGuardTest_684, NestedGuardsAccumulateAndThenRestore_684) {
  int depth = 0;
  using Guard = YAML::DepthGuard<10>;

  {
    Guard g1(depth, mark_, msg_);
    EXPECT_EQ(depth, 1);

    {
      Guard g2(depth, mark_, msg_);
      EXPECT_EQ(depth, 2);
    }
    EXPECT_EQ(depth, 1);
  }
  EXPECT_EQ(depth, 0);
}

TEST_F(DepthGuardTest_684, CurrentDepthMatchesExternalDepth_684) {
  int depth = 5;
  using Guard = YAML::DepthGuard<100>;

  Guard g(depth, mark_, msg_);
  // current_depth() is part of the public interface; validate it aligns with
  // observable external state.
  EXPECT_EQ(g.current_depth(), depth);
  EXPECT_EQ(depth, 6);
}

TEST_F(DepthGuardTest_684, DoesNotThrowBelowMaxDepthBoundary_684) {
  int depth = 1;
  using Guard = YAML::DepthGuard<3>;

  // Starting at 1: ctor increments to 2, which is still below max_depth (3),
  // so construction should succeed.
  EXPECT_NO_THROW({
    Guard g(depth, mark_, msg_);
    (void)g;
  });

  // RAII restoration should bring us back to the starting depth.
  EXPECT_EQ(depth, 1);
}

TEST_F(DepthGuardTest_684, ThrowsDeepRecursionAtMaxDepthBoundary_684) {
  int depth = 2;
  using Guard = YAML::DepthGuard<3>;

  // Starting at 2: ctor increments to 3, and since max_depth <= m_depth, it throws.
  EXPECT_THROW(
      {
        Guard g(depth, mark_, msg_);
        (void)g;
      },
      YAML::DeepRecursion);

  // Construction threw after incrementing depth; the object never finished constructing,
  // so no destructor runs. The observable external depth should remain incremented.
  EXPECT_EQ(depth, 3);
}

TEST_F(DepthGuardTest_684, MultipleThrowsContinueIncrementingWhenAlreadyAtOrAboveLimit_684) {
  int depth = 2;
  using Guard = YAML::DepthGuard<3>;

  EXPECT_THROW(
      {
        Guard g(depth, mark_, msg_);
        (void)g;
      },
      YAML::DeepRecursion);
  EXPECT_EQ(depth, 3);

  // Try again while already at 3: ctor increments to 4, should still throw.
  EXPECT_THROW(
      {
        Guard g(depth, mark_, msg_);
        (void)g;
      },
      YAML::DeepRecursion);
  EXPECT_EQ(depth, 4);
}

TEST_F(DepthGuardTest_684, CopyAndMoveOperationsAreDeleted_684) {
  using Guard = YAML::DepthGuard<10>;

  static_assert(!std::is_copy_constructible<Guard>::value,
                "DepthGuard copy construction should be deleted");
  static_assert(!std::is_move_constructible<Guard>::value,
                "DepthGuard move construction should be deleted");
  static_assert(!std::is_copy_assignable<Guard>::value,
                "DepthGuard copy assignment should be deleted");
  static_assert(!std::is_move_assignable<Guard>::value,
                "DepthGuard move assignment should be deleted");

  SUCCEED();
}

}  // namespace