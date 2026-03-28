#include "gtest/gtest.h"
#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"
#include <string>
#include <type_traits>

namespace {

// Use a reasonable max_depth for testing
using TestDepthGuard = YAML::DepthGuard<2048>;

class DepthGuardTest_92 : public ::testing::Test {
protected:
    int depth = 0;
    YAML::Mark mark;
    std::string msg = "test message";
};

// Test that constructing a DepthGuard increments the depth
TEST_F(DepthGuardTest_92, ConstructionIncrementsDepth_92) {
    EXPECT_EQ(depth, 0);
    {
        TestDepthGuard guard(depth, mark, msg);
        EXPECT_EQ(depth, 1);
    }
}

// Test that destroying a DepthGuard decrements the depth
TEST_F(DepthGuardTest_92, DestructionDecrementsDepth_92) {
    EXPECT_EQ(depth, 0);
    {
        TestDepthGuard guard(depth, mark, msg);
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
}

// Test that current_depth returns the current depth value
TEST_F(DepthGuardTest_92, CurrentDepthReturnsCorrectValue_92) {
    TestDepthGuard guard(depth, mark, msg);
    EXPECT_EQ(guard.current_depth(), 1);
}

// Test nested DepthGuards increment and decrement correctly
TEST_F(DepthGuardTest_92, NestedGuardsTrackDepthCorrectly_92) {
    EXPECT_EQ(depth, 0);
    {
        TestDepthGuard guard1(depth, mark, msg);
        EXPECT_EQ(depth, 1);
        EXPECT_EQ(guard1.current_depth(), 1);
        {
            TestDepthGuard guard2(depth, mark, msg);
            EXPECT_EQ(depth, 2);
            EXPECT_EQ(guard2.current_depth(), 2);
        }
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
}

// Test that exceeding max_depth throws an exception
TEST_F(DepthGuardTest_92, ExceedingMaxDepthThrows_92) {
    // Use a small max_depth to test the boundary
    using SmallDepthGuard = YAML::DepthGuard<2>;
    
    int smallDepth = 0;
    
    SmallDepthGuard guard1(smallDepth, mark, msg);
    EXPECT_EQ(smallDepth, 1);
    
    SmallDepthGuard guard2(smallDepth, mark, msg);
    EXPECT_EQ(smallDepth, 2);
    
    // The third guard should exceed max_depth of 2
    EXPECT_THROW(SmallDepthGuard guard3(smallDepth, mark, msg), YAML::DeepRecursion);
}

// Test that DepthGuard is not copyable
TEST_F(DepthGuardTest_92, NotCopyConstructible_92) {
    EXPECT_FALSE(std::is_copy_constructible<TestDepthGuard>::value);
}

// Test that DepthGuard is not movable
TEST_F(DepthGuardTest_92, NotMoveConstructible_92) {
    EXPECT_FALSE(std::is_move_constructible<TestDepthGuard>::value);
}

// Test that DepthGuard is not copy assignable
TEST_F(DepthGuardTest_92, NotCopyAssignable_92) {
    EXPECT_FALSE(std::is_copy_assignable<TestDepthGuard>::value);
}

// Test that DepthGuard is not move assignable
TEST_F(DepthGuardTest_92, NotMoveAssignable_92) {
    EXPECT_FALSE(std::is_move_assignable<TestDepthGuard>::value);
}

// Test boundary: exactly at max_depth should succeed
TEST_F(DepthGuardTest_92, ExactlyAtMaxDepthSucceeds_92) {
    using SmallDepthGuard = YAML::DepthGuard<3>;
    
    int smallDepth = 0;
    
    SmallDepthGuard guard1(smallDepth, mark, msg);
    SmallDepthGuard guard2(smallDepth, mark, msg);
    SmallDepthGuard guard3(smallDepth, mark, msg);
    
    EXPECT_EQ(smallDepth, 3);
    EXPECT_EQ(guard3.current_depth(), 3);
}

// Test that after exception from exceeding depth, depth is still incremented
// but can be managed properly
TEST_F(DepthGuardTest_92, DepthRestoredAfterExceedingMaxDepth_92) {
    using SmallDepthGuard = YAML::DepthGuard<1>;
    
    int smallDepth = 0;
    
    {
        SmallDepthGuard guard1(smallDepth, mark, msg);
        EXPECT_EQ(smallDepth, 1);
        
        EXPECT_THROW(SmallDepthGuard guard2(smallDepth, mark, msg), YAML::DeepRecursion);
    }
    // After guard1 is destroyed, depth should be back to 0
    EXPECT_EQ(smallDepth, 0);
}

// Test multiple sequential (non-nested) guards
TEST_F(DepthGuardTest_92, SequentialGuardsWorkCorrectly_92) {
    {
        TestDepthGuard guard1(depth, mark, msg);
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
    
    {
        TestDepthGuard guard2(depth, mark, msg);
        EXPECT_EQ(depth, 1);
    }
    EXPECT_EQ(depth, 0);
}

// Test with a custom message string
TEST_F(DepthGuardTest_92, CustomMessageDoesNotAffectBehavior_92) {
    TestDepthGuard guard(depth, mark, "custom error message");
    EXPECT_EQ(depth, 1);
    EXPECT_EQ(guard.current_depth(), 1);
}

}  // namespace
