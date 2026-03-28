#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

// We need to create a minimal FormatTraits to instantiate impl.
// However, based on the partial code provided, the `max` function is
// a static constexpr method that simply compares two ints.
// We'll test it through the namespace path given.

namespace {

using namespace YAML::jkj::dragonbox::detail;

// Since the partial code shows impl as a struct with a public static max,
// and the known dependencies show it's templated on FormatTraits,
// we test max (and min if accessible) as black-box functions.

// The partial code provided shows a non-templated struct impl with max.
// We'll test based on that interface.

class ImplMaxTest_405 : public ::testing::Test {
protected:
    // Helper to call max
    static constexpr int callMax(int x, int y) noexcept {
        return impl::max(x, y);
    }
};

// Normal operation tests

TEST_F(ImplMaxTest_405, MaxReturnsLargerWhenFirstIsGreater_405) {
    EXPECT_EQ(impl::max(10, 5), 10);
}

TEST_F(ImplMaxTest_405, MaxReturnsLargerWhenSecondIsGreater_405) {
    EXPECT_EQ(impl::max(3, 7), 7);
}

TEST_F(ImplMaxTest_405, MaxReturnsValueWhenBothAreEqual_405) {
    EXPECT_EQ(impl::max(4, 4), 4);
}

TEST_F(ImplMaxTest_405, MaxWithPositiveAndNegative_405) {
    EXPECT_EQ(impl::max(-3, 5), 5);
}

TEST_F(ImplMaxTest_405, MaxWithNegativeAndPositive_405) {
    EXPECT_EQ(impl::max(5, -3), 5);
}

TEST_F(ImplMaxTest_405, MaxWithBothNegative_405) {
    EXPECT_EQ(impl::max(-10, -3), -3);
}

TEST_F(ImplMaxTest_405, MaxWithBothNegativeReversed_405) {
    EXPECT_EQ(impl::max(-3, -10), -3);
}

TEST_F(ImplMaxTest_405, MaxWithBothNegativeEqual_405) {
    EXPECT_EQ(impl::max(-7, -7), -7);
}

// Boundary condition tests

TEST_F(ImplMaxTest_405, MaxWithZeroAndPositive_405) {
    EXPECT_EQ(impl::max(0, 1), 1);
}

TEST_F(ImplMaxTest_405, MaxWithPositiveAndZero_405) {
    EXPECT_EQ(impl::max(1, 0), 1);
}

TEST_F(ImplMaxTest_405, MaxWithZeroAndNegative_405) {
    EXPECT_EQ(impl::max(0, -1), 0);
}

TEST_F(ImplMaxTest_405, MaxWithNegativeAndZero_405) {
    EXPECT_EQ(impl::max(-1, 0), 0);
}

TEST_F(ImplMaxTest_405, MaxWithBothZero_405) {
    EXPECT_EQ(impl::max(0, 0), 0);
}

TEST_F(ImplMaxTest_405, MaxWithIntMax_405) {
    constexpr int int_max = std::numeric_limits<int>::max();
    EXPECT_EQ(impl::max(int_max, 0), int_max);
}

TEST_F(ImplMaxTest_405, MaxWithIntMin_405) {
    constexpr int int_min = std::numeric_limits<int>::min();
    EXPECT_EQ(impl::max(int_min, 0), 0);
}

TEST_F(ImplMaxTest_405, MaxWithIntMaxAndIntMin_405) {
    constexpr int int_max = std::numeric_limits<int>::max();
    constexpr int int_min = std::numeric_limits<int>::min();
    EXPECT_EQ(impl::max(int_max, int_min), int_max);
}

TEST_F(ImplMaxTest_405, MaxWithIntMinAndIntMax_405) {
    constexpr int int_max = std::numeric_limits<int>::max();
    constexpr int int_min = std::numeric_limits<int>::min();
    EXPECT_EQ(impl::max(int_min, int_max), int_max);
}

TEST_F(ImplMaxTest_405, MaxWithIntMaxBoth_405) {
    constexpr int int_max = std::numeric_limits<int>::max();
    EXPECT_EQ(impl::max(int_max, int_max), int_max);
}

TEST_F(ImplMaxTest_405, MaxWithIntMinBoth_405) {
    constexpr int int_min = std::numeric_limits<int>::min();
    EXPECT_EQ(impl::max(int_min, int_min), int_min);
}

// Constexpr verification
TEST_F(ImplMaxTest_405, MaxIsConstexpr_405) {
    constexpr int result = impl::max(3, 5);
    EXPECT_EQ(result, 5);
    static_assert(impl::max(3, 5) == 5, "max should be constexpr");
    static_assert(impl::max(10, 2) == 10, "max should be constexpr");
    static_assert(impl::max(4, 4) == 4, "max should be constexpr");
}

TEST_F(ImplMaxTest_405, MaxWithOneAndMinusOne_405) {
    EXPECT_EQ(impl::max(1, -1), 1);
    EXPECT_EQ(impl::max(-1, 1), 1);
}

TEST_F(ImplMaxTest_405, MaxWithLargePositiveValues_405) {
    EXPECT_EQ(impl::max(1000000, 999999), 1000000);
}

TEST_F(ImplMaxTest_405, MaxWithLargeNegativeValues_405) {
    EXPECT_EQ(impl::max(-1000000, -999999), -999999);
}

TEST_F(ImplMaxTest_405, MaxWithConsecutiveValues_405) {
    EXPECT_EQ(impl::max(42, 43), 43);
    EXPECT_EQ(impl::max(43, 42), 43);
}

} // namespace
