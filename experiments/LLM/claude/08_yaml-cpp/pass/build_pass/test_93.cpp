#include "gtest/gtest.h"
#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/mark.h"
#include <string>
#include <type_traits>

namespace {

// Use a reasonable max_depth for testing
constexpr int kTestMaxDepth = 2048;

class DepthGuardTest_93 : public ::testing::Test {
protected:
    int depth_ = 0;
    YAML::Mark mark_;
    std::string msg_ = "test message";
};

// Test that constructing a DepthGuard increments the depth
TEST_F(DepthGuardTest_93, ConstructionIncrementsDepth_93) {
    EXPECT_EQ(depth_, 0);
    {
        YAML::DepthGuard<kTestMaxDepth> guard(depth_, mark_, msg_);
        EXPECT_EQ(guard.current_depth(), 1);
        EXPECT_EQ(depth_, 1);
    }
    // After destruction, depth should be decremented back
    EXPECT_EQ(depth_, 0);
}

// Test that nested DepthGuards increment depth correctly
TEST_F(DepthGuardTest_93, NestedGuardsIncrementDepth_93) {
    {
        YAML::DepthGuard<kTestMaxDepth> guard1(depth_, mark_, msg_);
        EXPECT_EQ(guard1.current_depth(), 1);
        {
            YAML::DepthGuard<kTestMaxDepth> guard2(depth_, mark_, msg_);
            EXPECT_EQ(guard2.current_depth(), 2);
            {
                YAML::DepthGuard<kTestMaxDepth> guard3(depth_, mark_, msg_);
                EXPECT_EQ(guard3.current_depth(), 3);
            }
            EXPECT_EQ(depth_, 2);
        }
        EXPECT_EQ(depth_, 1);
    }
    EXPECT_EQ(depth_, 0);
}

// Test that destruction decrements the depth
TEST_F(DepthGuardTest_93, DestructionDecrementsDepth_93) {
    {
        YAML::DepthGuard<kTestMaxDepth> guard(depth_, mark_, msg_);
        EXPECT_EQ(depth_, 1);
    }
    EXPECT_EQ(depth_, 0);
}

// Test that current_depth returns the current depth value
TEST_F(DepthGuardTest_93, CurrentDepthReturnsCorrectValue_93) {
    YAML::DepthGuard<kTestMaxDepth> guard(depth_, mark_, msg_);
    EXPECT_EQ(guard.current_depth(), 1);
}

// Test that exceeding max_depth throws an exception
TEST_F(DepthGuardTest_93, ExceedingMaxDepthThrows_93) {
    constexpr int smallMax = 2;
    {
        YAML::DepthGuard<smallMax> guard1(depth_, mark_, msg_);
        EXPECT_EQ(guard1.current_depth(), 1);
        {
            YAML::DepthGuard<smallMax> guard2(depth_, mark_, msg_);
            EXPECT_EQ(guard2.current_depth(), 2);
            // Third guard should exceed the max depth of 2
            EXPECT_THROW(
                {
                    YAML::DepthGuard<smallMax> guard3(depth_, mark_, msg_);
                },
                YAML::DeepRecursion
            );
        }
    }
}

// Test boundary: depth exactly at max should still be allowed (or throw - depends on implementation)
TEST_F(DepthGuardTest_93, DepthAtMaxBoundary_93) {
    constexpr int maxD = 3;
    {
        YAML::DepthGuard<maxD> guard1(depth_, mark_, msg_);
        {
            YAML::DepthGuard<maxD> guard2(depth_, mark_, msg_);
            {
                YAML::DepthGuard<maxD> guard3(depth_, mark_, msg_);
                EXPECT_EQ(guard3.current_depth(), 3);
                // Next one should throw
                EXPECT_THROW(
                    {
                        YAML::DepthGuard<maxD> guard4(depth_, mark_, msg_);
                    },
                    YAML::DeepRecursion
                );
            }
        }
    }
    EXPECT_EQ(depth_, 0);
}

// Test that DepthGuard is not copy-constructible
TEST_F(DepthGuardTest_93, NotCopyConstructible_93) {
    EXPECT_FALSE((std::is_copy_constructible<YAML::DepthGuard<kTestMaxDepth>>::value));
}

// Test that DepthGuard is not move-constructible
TEST_F(DepthGuardTest_93, NotMoveConstructible_93) {
    EXPECT_FALSE((std::is_move_constructible<YAML::DepthGuard<kTestMaxDepth>>::value));
}

// Test that DepthGuard is not copy-assignable
TEST_F(DepthGuardTest_93, NotCopyAssignable_93) {
    EXPECT_FALSE((std::is_copy_assignable<YAML::DepthGuard<kTestMaxDepth>>::value));
}

// Test that DepthGuard is not move-assignable
TEST_F(DepthGuardTest_93, NotMoveAssignable_93) {
    EXPECT_FALSE((std::is_move_assignable<YAML::DepthGuard<kTestMaxDepth>>::value));
}

// Test with initial non-zero depth
TEST_F(DepthGuardTest_93, InitialNonZeroDepth_93) {
    depth_ = 5;
    {
        YAML::DepthGuard<kTestMaxDepth> guard(depth_, mark_, msg_);
        EXPECT_EQ(guard.current_depth(), 6);
    }
    EXPECT_EQ(depth_, 5);
}

// Test that exception safety: depth is properly managed even when exception is thrown
TEST_F(DepthGuardTest_93, DepthRestoredAfterException_93) {
    constexpr int smallMax = 1;
    {
        YAML::DepthGuard<smallMax> guard1(depth_, mark_, msg_);
        EXPECT_EQ(depth_, 1);
        try {
            YAML::DepthGuard<smallMax> guard2(depth_, mark_, msg_);
        } catch (const YAML::DeepRecursion&) {
            // depth should have been decremented back if the constructor threw after incrementing
        }
        // After the failed guard, we should still be at depth 1 (from guard1)
        EXPECT_GE(depth_, 1);
    }
    EXPECT_EQ(depth_, 0);
}

// Test with max_depth of 1
TEST_F(DepthGuardTest_93, MaxDepthOne_93) {
    constexpr int maxD = 1;
    {
        YAML::DepthGuard<maxD> guard1(depth_, mark_, msg_);
        EXPECT_EQ(guard1.current_depth(), 1);
        EXPECT_THROW(
            {
                YAML::DepthGuard<maxD> guard2(depth_, mark_, msg_);
            },
            YAML::DeepRecursion
        );
    }
    EXPECT_EQ(depth_, 0);
}

}  // namespace
