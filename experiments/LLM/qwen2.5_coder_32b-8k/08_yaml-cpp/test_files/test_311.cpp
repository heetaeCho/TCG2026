#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail::wuint;



// Fixture for uint128 tests

class Uint128Test_311 : public ::testing::Test {

protected:

    uint128 y;

    std::uint_least64_t x;



    void SetUp() override {

        x = 0x123456789ABCDEF0ULL; // Example value for x

        y = uint128(0xFEDCBA9876543210ULL, 0x0123456789ABCDEFULL); // Example value for y

    }

};



// Test normal operation of umul192_lower128

TEST_F(Uint128Test_311, NormalOperation_311) {

    auto result = detail::wuint::umul192_lower128(x, y);

    EXPECT_EQ(result.high(), (x * y.high() + umul128(x, y.low()).high()) & UINT64_C(0xffffffffffffffff));

    EXPECT_EQ(result.low(), umul128(x, y.low()).low());

}



// Test boundary conditions: x = 0

TEST_F(Uint128Test_311, BoundaryXZero_311) {

    x = 0;

    auto result = detail::wuint::umul192_lower128(x, y);

    EXPECT_EQ(result.high(), 0ULL);

    EXPECT_EQ(result.low(), 0ULL);

}



// Test boundary conditions: y.high() = 0

TEST_F(Uint128Test_311, BoundaryYHighZero_311) {

    y = uint128(0, y.low());

    auto result = detail::wuint::umul192_lower128(x, y);

    EXPECT_EQ(result.high(), 0ULL);

    EXPECT_EQ(result.low(), umul128(x, y.low()).low());

}



// Test boundary conditions: y.low() = 0

TEST_F(Uint128Test_311, BoundaryYLowZero_311) {

    y = uint128(y.high(), 0);

    auto result = detail::wuint::umul192_lower128(x, y);

    EXPECT_EQ(result.high(), (x * y.high()) & UINT64_C(0xffffffffffffffff));

    EXPECT_EQ(result.low(), 0ULL);

}



// Test boundary conditions: x and y are maximum values

TEST_F(Uint128Test_311, BoundaryMaxValues_311) {

    x = UINT64_MAX;

    y = uint128(UINT64_MAX, UINT64_MAX);

    auto result = detail::wuint::umul192_lower128(x, y);

    EXPECT_EQ(result.high(), (x * y.high() + umul128(x, y.low()).high()) & UINT64_C(0xffffffffffffffff));

    EXPECT_EQ(result.low(), umul128(x, y.low()).low());

}
