#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail::wuint;



// Test Fixture for umul128 tests

class Umul128Test_307 : public ::testing::Test {

protected:

    // You can set up any common state here if needed

};



// Normal operation test

TEST_F(Umul128Test_307, NormalOperation_307) {

    uint128 result = umul128(123456789, 987654321);

    EXPECT_EQ(result.high_, 0);

    EXPECT_EQ(result.low_, 121932631112635269ULL);

}



// Boundary conditions test with zero

TEST_F(Umul128Test_307, ZeroMultiplication_307) {

    uint128 result = umul128(0, 987654321);

    EXPECT_EQ(result.high_, 0);

    EXPECT_EQ(result.low_, 0);



    result = umul128(123456789, 0);

    EXPECT_EQ(result.high_, 0);

    EXPECT_EQ(result.low_, 0);

}



// Boundary conditions test with maximum uint64_t value

TEST_F(Umul128Test_307, MaxUint64Multiplication_307) {

    std::uint_least64_t max_value = UINT64_MAX;

    uint128 result = umul128(max_value, 1);

    EXPECT_EQ(result.high_, 0);

    EXPECT_EQ(result.low_, max_value);



    result = umul128(1, max_value);

    EXPECT_EQ(result.high_, 0);

    EXPECT_EQ(result.low_, max_value);

}



// Boundary conditions test with maximum uint64_t values

TEST_F(Umul128Test_307, MaxUint64MultiplicationWithMax_307) {

    std::uint_least64_t max_value = UINT64_MAX;

    uint128 result = umul128(max_value, max_value);

    EXPECT_EQ(result.high_, 18446744073709551614ULL);

    EXPECT_EQ(result.low_, 1ULL);

}
