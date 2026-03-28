#include "gtest/gtest.h"
#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"
#include <string>
#include <type_traits>

namespace {

// Use a reasonable max_depth for testing
constexpr int kTestMaxDepth = 2048;

using TestDepthGuard = YAML::DepthGuard<kTestMaxDepth>;

// Test that constructing a DepthGuard increments depth and destructor decrements it
TEST(DepthGuardTest_546, ConstructorIncrementsDepthAndDestructorDecrements_546) {
    int depth = 0;
    YAML::Mark mark;
    {
        TestDepthGuard guard(depth, mark, "test");
        EXPECT_EQ(depth, 1);
        EXPECT_EQ(guard.current_depth(), 1);
    }
    EXPECT_EQ(depth, 0);
}

// Test multiple nested DepthGuards incrementing depth correctly
TEST(DepthGuardTest_546, MultipleNestedGuardsIncrementDepth_546) {
    int depth = 0;
    YAML::Mark mark;
    {
        TestDepthGuard guard1(depth, mark, "test1");
        EXPECT_EQ(depth, 1);
        EXPECT_EQ(guard1.current_depth(), 1);
        {
            TestDepthGuard guard2(depth, mark, "test2");
            EXPECT_EQ(depth, 2);
            EXPECT_EQ(guard2.current_depth(), 2);
            {
                TestDepthGuard guard3(depth, mark, "test3");
                EXPECT_EQ(depth, 3);
                EXPECT_EQ(guard3.current_depth(), 3);
            }
            EXPECT_EQ(depth, 2);
        }
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
}

// Test that exceeding max_depth throws an exception
TEST(DepthGuardTest_546, ExceedingMaxDepthThrows_546) {
    constexpr int kSmallMax = 2;
    using SmallDepthGuard = YAML::DepthGuard<kSmallMax>;
    
    int depth = 0;
    YAML::Mark mark;
    
    SmallDepthGuard guard1(depth, mark, "level1");
    EXPECT_EQ(depth, 1);
    
    SmallDepthGuard guard2(depth, mark, "level2");
    EXPECT_EQ(depth, 2);
    
    // The third guard should exceed max_depth of 2 and throw
    EXPECT_THROW(
        SmallDepthGuard guard3(depth, mark, "level3"),
        YAML::DeepRecursion
    );
}

// Test that current_depth returns the correct value
TEST(DepthGuardTest_546, CurrentDepthReturnsCorrectValue_546) {
    int depth = 5;
    YAML::Mark mark;
    
    TestDepthGuard guard(depth, mark, "test");
    EXPECT_EQ(guard.current_depth(), 6);
}

// Test that depth is decremented even when starting from non-zero
TEST(DepthGuardTest_546, DepthDecrementedFromNonZeroStart_546) {
    int depth = 10;
    YAML::Mark mark;
    {
        TestDepthGuard guard(depth, mark, "test");
        EXPECT_EQ(depth, 11);
    }
    EXPECT_EQ(depth, 10);
}

// Test that DepthGuard is not copyable
TEST(DepthGuardTest_546, IsNotCopyConstructible_546) {
    EXPECT_FALSE(std::is_copy_constructible<TestDepthGuard>::value);
}

// Test that DepthGuard is not copy assignable
TEST(DepthGuardTest_546, IsNotCopyAssignable_546) {
    EXPECT_FALSE(std::is_copy_assignable<TestDepthGuard>::value);
}

// Test that DepthGuard is not move constructible
TEST(DepthGuardTest_546, IsNotMoveConstructible_546) {
    EXPECT_FALSE(std::is_move_constructible<TestDepthGuard>::value);
}

// Test that DepthGuard is not move assignable
TEST(DepthGuardTest_546, IsNotMoveAssignable_546) {
    EXPECT_FALSE(std::is_move_assignable<TestDepthGuard>::value);
}

// Test boundary: exactly at max_depth should still succeed, max_depth+1 should throw
TEST(DepthGuardTest_546, BoundaryAtExactMaxDepth_546) {
    constexpr int kMax = 3;
    using BoundaryGuard = YAML::DepthGuard<kMax>;
    
    int depth = 0;
    YAML::Mark mark;
    
    {
        BoundaryGuard guard1(depth, mark, "1");
        EXPECT_EQ(depth, 1);
        {
            BoundaryGuard guard2(depth, mark, "2");
            EXPECT_EQ(depth, 2);
            {
                BoundaryGuard guard3(depth, mark, "3");
                EXPECT_EQ(depth, 3);
                // This should now throw since depth would become 4 > 3
                EXPECT_THROW(
                    BoundaryGuard guard4(depth, mark, "4"),
                    YAML::DeepRecursion
                );
            }
            EXPECT_EQ(depth, 2);
        }
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
}

// Test that the message is accessible through the thrown exception
TEST(DepthGuardTest_546, ExceptionContainsMessage_546) {
    constexpr int kSmallMax = 1;
    using SmallGuard = YAML::DepthGuard<kSmallMax>;
    
    int depth = 0;
    YAML::Mark mark;
    
    SmallGuard guard1(depth, mark, "first");
    
    try {
        SmallGuard guard2(depth, mark, "overflow message");
        FAIL() << "Expected DeepRecursion exception";
    } catch (const YAML::DeepRecursion& e) {
        // Exception was thrown as expected
        std::string what_str(e.what());
        EXPECT_FALSE(what_str.empty());
    }
}

// Test sequential (non-nested) usage - depth returns to original between guards
TEST(DepthGuardTest_546, SequentialUsageResetsDepth_546) {
    int depth = 0;
    YAML::Mark mark;
    
    {
        TestDepthGuard guard1(depth, mark, "first");
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
    
    {
        TestDepthGuard guard2(depth, mark, "second");
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
}

}  // namespace
