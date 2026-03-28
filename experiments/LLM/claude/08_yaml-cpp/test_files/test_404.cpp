#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

// Since the partial code shows a simplified version of impl with min(),
// we test the publicly accessible static constexpr functions.

namespace {

// We need to figure out how to instantiate impl. Based on the partial code,
// it seems like impl is a struct with static methods. The simplified version
// doesn't require template parameters, so we test directly.

using namespace YAML::jkj::dragonbox::detail;

// Test fixture
class ImplTest_404 : public ::testing::Test {
protected:
    // Nothing to set up
};

// ==================== min() tests ====================

TEST_F(ImplTest_404, MinReturnsSmaller_WhenFirstIsSmaller_404) {
    EXPECT_EQ(impl::min(1, 2), 1);
}

TEST_F(ImplTest_404, MinReturnsSmaller_WhenSecondIsSmaller_404) {
    EXPECT_EQ(impl::min(5, 3), 3);
}

TEST_F(ImplTest_404, MinReturnsSameValue_WhenBothEqual_404) {
    EXPECT_EQ(impl::min(7, 7), 7);
}

TEST_F(ImplTest_404, MinHandlesZeros_404) {
    EXPECT_EQ(impl::min(0, 0), 0);
}

TEST_F(ImplTest_404, MinHandlesNegativeValues_404) {
    EXPECT_EQ(impl::min(-3, -1), -3);
}

TEST_F(ImplTest_404, MinHandlesMixedSignValues_404) {
    EXPECT_EQ(impl::min(-5, 5), -5);
}

TEST_F(ImplTest_404, MinHandlesNegativeAndZero_404) {
    EXPECT_EQ(impl::min(-1, 0), -1);
}

TEST_F(ImplTest_404, MinHandlesZeroAndPositive_404) {
    EXPECT_EQ(impl::min(0, 10), 0);
}

TEST_F(ImplTest_404, MinHandlesIntMinBoundary_404) {
    constexpr int int_min = std::numeric_limits<int>::min();
    EXPECT_EQ(impl::min(int_min, 0), int_min);
}

TEST_F(ImplTest_404, MinHandlesIntMaxBoundary_404) {
    constexpr int int_max = std::numeric_limits<int>::max();
    EXPECT_EQ(impl::min(int_max, 0), 0);
}

TEST_F(ImplTest_404, MinHandlesBothIntMinAndIntMax_404) {
    constexpr int int_min = std::numeric_limits<int>::min();
    constexpr int int_max = std::numeric_limits<int>::max();
    EXPECT_EQ(impl::min(int_min, int_max), int_min);
}

TEST_F(ImplTest_404, MinHandlesBothIntMax_404) {
    constexpr int int_max = std::numeric_limits<int>::max();
    EXPECT_EQ(impl::min(int_max, int_max), int_max);
}

TEST_F(ImplTest_404, MinHandlesBothIntMin_404) {
    constexpr int int_min = std::numeric_limits<int>::min();
    EXPECT_EQ(impl::min(int_min, int_min), int_min);
}

TEST_F(ImplTest_404, MinIsConstexpr_404) {
    constexpr int result = impl::min(10, 20);
    EXPECT_EQ(result, 10);
}

TEST_F(ImplTest_404, MinIsNoexcept_404) {
    EXPECT_TRUE(noexcept(impl::min(1, 2)));
}

TEST_F(ImplTest_404, MinHandlesLargeNegativeValues_404) {
    EXPECT_EQ(impl::min(-1000000, -999999), -1000000);
}

TEST_F(ImplTest_404, MinHandlesConsecutiveValues_404) {
    EXPECT_EQ(impl::min(41, 42), 41);
    EXPECT_EQ(impl::min(42, 41), 41);
}

TEST_F(ImplTest_404, MinHandlesOneAndNegativeOne_404) {
    EXPECT_EQ(impl::min(1, -1), -1);
    EXPECT_EQ(impl::min(-1, 1), -1);
}

} // namespace
