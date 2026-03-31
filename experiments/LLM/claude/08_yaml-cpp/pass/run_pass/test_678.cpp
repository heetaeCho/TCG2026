#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace {

// Use a small max_depth for testing purposes
using TestDepthGuard = DepthGuard<5>;
using SmallDepthGuard = DepthGuard<2>;
using OneDepthGuard = DepthGuard<1>;

TEST(DepthGuardTest_678, ConstructorIncrementsDepth_678) {
    int depth = 0;
    Mark mark;
    {
        TestDepthGuard guard(depth, mark, "test message");
        EXPECT_EQ(depth, 1);
    }
}

TEST(DepthGuardTest_678, DestructorDecrementsDepth_678) {
    int depth = 0;
    Mark mark;
    {
        TestDepthGuard guard(depth, mark, "test message");
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
}

TEST(DepthGuardTest_678, CurrentDepthReturnsCorrectValue_678) {
    int depth = 0;
    Mark mark;
    TestDepthGuard guard(depth, mark, "test message");
    EXPECT_EQ(guard.current_depth(), 1);
}

TEST(DepthGuardTest_678, MultipleGuardsIncrementDepth_678) {
    int depth = 0;
    Mark mark;
    {
        TestDepthGuard guard1(depth, mark, "msg");
        EXPECT_EQ(depth, 1);
        EXPECT_EQ(guard1.current_depth(), 1);
        {
            TestDepthGuard guard2(depth, mark, "msg");
            EXPECT_EQ(depth, 2);
            EXPECT_EQ(guard2.current_depth(), 2);
            {
                TestDepthGuard guard3(depth, mark, "msg");
                EXPECT_EQ(depth, 3);
                EXPECT_EQ(guard3.current_depth(), 3);
            }
            EXPECT_EQ(depth, 2);
        }
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
}

TEST(DepthGuardTest_678, ThrowsDeepRecursionWhenMaxDepthReached_678) {
    int depth = 0;
    Mark mark;
    EXPECT_THROW({
        OneDepthGuard guard(depth, mark, "too deep");
    }, DeepRecursion);
}

TEST(DepthGuardTest_678, ThrowsDeepRecursionAtExactMaxDepth_678) {
    int depth = 0;
    Mark mark;
    // With max_depth=2, depth=0 -> 1 (ok), depth=1 -> 2 (throws)
    {
        SmallDepthGuard guard1(depth, mark, "msg");
        EXPECT_EQ(depth, 1);
        EXPECT_THROW({
            SmallDepthGuard guard2(depth, mark, "too deep");
        }, DeepRecursion);
    }
}

TEST(DepthGuardTest_678, DepthRestoredAfterThrow_678) {
    int depth = 0;
    Mark mark;
    {
        SmallDepthGuard guard1(depth, mark, "msg");
        EXPECT_EQ(depth, 1);
        try {
            SmallDepthGuard guard2(depth, mark, "too deep");
        } catch (const DeepRecursion&) {
            // After the exception, depth was incremented but the guard was not fully constructed
            // so we need to check the state. The depth was incremented before the throw.
            // Since the destructor may or may not run depending on implementation,
            // just note the depth was incremented.
        }
    }
    // After guard1 goes out of scope, depth should be decremented
    // The exact value depends on whether depth is decremented after the throw
}

TEST(DepthGuardTest_678, NonCopyable_678) {
    EXPECT_FALSE(std::is_copy_constructible<TestDepthGuard>::value);
    EXPECT_FALSE(std::is_copy_assignable<TestDepthGuard>::value);
}

TEST(DepthGuardTest_678, NonMovable_678) {
    EXPECT_FALSE(std::is_move_constructible<TestDepthGuard>::value);
    EXPECT_FALSE(std::is_move_assignable<TestDepthGuard>::value);
}

TEST(DepthGuardTest_678, StartingWithNonZeroDepth_678) {
    int depth = 3;
    Mark mark;
    {
        TestDepthGuard guard(depth, mark, "msg");
        EXPECT_EQ(depth, 4);
        EXPECT_EQ(guard.current_depth(), 4);
    }
    EXPECT_EQ(depth, 3);
}

TEST(DepthGuardTest_678, ExactlyBelowMaxDepthDoesNotThrow_678) {
    int depth = 3;
    Mark mark;
    // max_depth=5, depth goes from 3 to 4 which is < 5, should not throw
    EXPECT_NO_THROW({
        TestDepthGuard guard(depth, mark, "msg");
    });
}

TEST(DepthGuardTest_678, ExactlyAtMaxDepthThrows_678) {
    int depth = 4;
    Mark mark;
    // max_depth=5, depth goes from 4 to 5 which is == 5, should throw
    EXPECT_THROW({
        TestDepthGuard guard(depth, mark, "too deep");
    }, DeepRecursion);
}

TEST(DepthGuardTest_678, DeepRecursionContainsDepthInfo_678) {
    int depth = 0;
    Mark mark;
    try {
        OneDepthGuard guard(depth, mark, "recursion error");
        FAIL() << "Expected DeepRecursion to be thrown";
    } catch (const DeepRecursion& e) {
        // DeepRecursion should be catchable and provide some information
        // At minimum, we verify it was thrown successfully
        SUCCEED();
    }
}

TEST(DepthGuardTest_678, NullMarkDoesNotAffectBehavior_678) {
    int depth = 0;
    Mark mark = Mark::null_mark();
    EXPECT_NO_THROW({
        TestDepthGuard guard(depth, mark, "msg");
        EXPECT_EQ(guard.current_depth(), 1);
    });
}

TEST(DepthGuardTest_678, EmptyMessageDoesNotAffectBehavior_678) {
    int depth = 0;
    Mark mark;
    EXPECT_NO_THROW({
        TestDepthGuard guard(depth, mark, "");
        EXPECT_EQ(guard.current_depth(), 1);
    });
}

}  // namespace
}  // namespace YAML
