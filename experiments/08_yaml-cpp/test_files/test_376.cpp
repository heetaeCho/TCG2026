#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary includes and setup for the class under test



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding { namespace detail {



class NearestOpenTest : public ::testing::Test {

protected:

    using SignedSignificandBits = int; // Example type, can be any signed integral type

};



TEST_F(NearestOpenTest_376, ShorterInterval_ReturnsEmptyInterval_376) {

    auto result = nearest_open_t::shorter_interval(SignedSignificandBits{0});

    EXPECT_TRUE(result.empty());

}



// Boundary condition test with a positive value

TEST_F(NearestOpenTest_376, ShorterInterval_PositiveValue_ReturnsEmptyInterval_376) {

    auto result = nearest_open_t::shorter_interval(SignedSignificandBits{123});

    EXPECT_TRUE(result.empty());

}



// Boundary condition test with a negative value

TEST_F(NearestOpenTest_376, ShorterInterval_NegativeValue_ReturnsEmptyInterval_376) {

    auto result = nearest_open_t::shorter_interval(SignedSignificandBits{-123});

    EXPECT_TRUE(result.empty());

}



// Test for zero as a boundary condition

TEST_F(NearestOpenTest_376, ShorterInterval_ZeroValue_ReturnsEmptyInterval_376) {

    auto result = nearest_open_t::shorter_interval(SignedSignificandBits{0});

    EXPECT_TRUE(result.empty());

}



} // namespace detail

} // namespace decimal_to_binary_rounding

} // namespace policy

} // namespace dragonbox

} // namespace jkj

} // namespace YAML
