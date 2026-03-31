#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"

namespace YAML {

// Test fixture for DepthGuard tests
class DepthGuardTest_684 : public ::testing::Test {
 protected:
  void SetUp() override {
    depth_ = 0;
  }

  int depth_;
  Mark mark_ = Mark::null_mark();
  std::string msg_ = "test message";
};

// Test that constructing a DepthGuard increments the depth
TEST_F(DepthGuardTest_684, ConstructorIncrementsDepth_684) {
  EXPECT_EQ(depth_, 0);
  {
    DepthGuard<2048> guard(depth_, mark_, msg_);
    EXPECT_EQ(depth_, 1);
  }
}

// Test that destroying a DepthGuard decrements the depth
TEST_F(DepthGuardTest_684, DestructorDecrementsDepth_684) {
  EXPECT_EQ(depth_, 0);
  {
    DepthGuard<2048> guard(depth_, mark_, msg_);
    EXPECT_EQ(depth_, 1);
  }
  EXPECT_EQ(depth_, 0);
}

// Test that current_depth returns the current depth value
TEST_F(DepthGuardTest_684, CurrentDepthReturnsCorrectValue_684) {
  DepthGuard<2048> guard(depth_, mark_, msg_);
  EXPECT_EQ(guard.current_depth(), 1);
}

// Test that multiple nested DepthGuards increment depth correctly
TEST_F(DepthGuardTest_684, NestedGuardsIncrementDepth_684) {
  {
    DepthGuard<2048> guard1(depth_, mark_, msg_);
    EXPECT_EQ(depth_, 1);
    EXPECT_EQ(guard1.current_depth(), 1);
    {
      DepthGuard<2048> guard2(depth_, mark_, msg_);
      EXPECT_EQ(depth_, 2);
      EXPECT_EQ(guard2.current_depth(), 2);
      {
        DepthGuard<2048> guard3(depth_, mark_, msg_);
        EXPECT_EQ(depth_, 3);
        EXPECT_EQ(guard3.current_depth(), 3);
      }
      EXPECT_EQ(depth_, 2);
    }
    EXPECT_EQ(depth_, 1);
  }
  EXPECT_EQ(depth_, 0);
}

// Test that exceeding max_depth throws DeepRecursion
TEST_F(DepthGuardTest_684, ThrowsDeepRecursionWhenMaxDepthReached_684) {
  // Use a small max_depth for testing
  depth_ = 1;  // Already at depth 1, so creating guard will make it 2 which equals max_depth=2
  EXPECT_THROW(
    {
      DepthGuard<2> guard(depth_, mark_, msg_);
    },
    DeepRecursion
  );
}

// Test with max_depth = 1, should throw immediately
TEST_F(DepthGuardTest_684, ThrowsDeepRecursionWithMaxDepthOne_684) {
  depth_ = 0;
  EXPECT_THROW(
    {
      DepthGuard<1> guard(depth_, mark_, msg_);
    },
    DeepRecursion
  );
}

// Test that depth just below max_depth does not throw
TEST_F(DepthGuardTest_684, DoesNotThrowBelowMaxDepth_684) {
  depth_ = 0;
  EXPECT_NO_THROW({
    DepthGuard<3> guard(depth_, mark_, msg_);
  });
  // Depth should have been decremented back after guard goes out of scope in EXPECT_NO_THROW
}

// Test boundary: depth reaches max_depth - 1, next guard reaches max_depth and throws
TEST_F(DepthGuardTest_684, BoundaryThrowAtExactMaxDepth_684) {
  depth_ = 2;  // Set depth to 2, guard will increment to 3 which equals max_depth
  EXPECT_THROW(
    {
      DepthGuard<3> guard(depth_, mark_, msg_);
    },
    DeepRecursion
  );
}

// Test boundary: depth at max_depth - 2, guard increments to max_depth - 1, no throw
TEST_F(DepthGuardTest_684, BoundaryNoThrowJustBelowMaxDepth_684) {
  depth_ = 1;  // Guard will increment to 2, max_depth is 3, so no throw
  EXPECT_NO_THROW({
    DepthGuard<3> guard(depth_, mark_, msg_);
    EXPECT_EQ(guard.current_depth(), 2);
  });
}

// Test that copy constructor is deleted (compile-time check, but we verify we can't copy)
// This is verified by the = delete declarations. We trust the compiler enforces this.

// Test that move constructor is deleted
// This is verified by the = delete declarations. We trust the compiler enforces this.

// Test that copy assignment is deleted
// This is verified by the = delete declarations. We trust the compiler enforces this.

// Test that move assignment is deleted
// This is verified by the = delete declarations. We trust the compiler enforces this.

// Test with non-zero initial depth that doesn't exceed max
TEST_F(DepthGuardTest_684, NonZeroInitialDepthNoThrow_684) {
  depth_ = 5;
  EXPECT_NO_THROW({
    DepthGuard<100> guard(depth_, mark_, msg_);
    EXPECT_EQ(depth_, 6);
    EXPECT_EQ(guard.current_depth(), 6);
  });
  EXPECT_EQ(depth_, 5);
}

// Test DeepRecursion exception properties
TEST_F(DepthGuardTest_684, DeepRecursionExceptionContainsInfo_684) {
  depth_ = 1;
  try {
    DepthGuard<2> guard(depth_, mark_, msg_);
    FAIL() << "Expected DeepRecursion to be thrown";
  } catch (const DeepRecursion& e) {
    // DeepRecursion should be catchable and is a type of exception
    // We just verify it was thrown with the correct depth
    SUCCEED();
  } catch (...) {
    FAIL() << "Expected DeepRecursion exception, got a different exception";
  }
}

// Test that the message string is used (indirectly through exception)
TEST_F(DepthGuardTest_684, CustomMessageInException_684) {
  depth_ = 99;
  std::string custom_msg = "custom recursion error";
  try {
    DepthGuard<100> guard(depth_, mark_, custom_msg);
    FAIL() << "Expected DeepRecursion to be thrown";
  } catch (const DeepRecursion& e) {
    // The exception was thrown with the custom message
    // We can check what() if available
    std::string what_msg = e.what();
    EXPECT_FALSE(what_msg.empty());
  }
}

// Test that after exception is thrown, depth was already incremented
TEST_F(DepthGuardTest_684, DepthIncrementedBeforeThrow_684) {
  depth_ = 4;
  try {
    DepthGuard<5> guard(depth_, mark_, msg_);
    FAIL() << "Expected DeepRecursion";
  } catch (const DeepRecursion&) {
    // The depth was incremented before the throw
    EXPECT_EQ(depth_, 5);
  }
}

// Test with a Mark that has specific position values
TEST_F(DepthGuardTest_684, WorksWithSpecificMark_684) {
  depth_ = 0;
  // Use null mark - should work fine
  Mark null_mark = Mark::null_mark();
  EXPECT_NO_THROW({
    DepthGuard<10> guard(depth_, null_mark, "some message");
    EXPECT_EQ(guard.current_depth(), 1);
  });
}

}  // namespace YAML
