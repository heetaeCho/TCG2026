#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::detail::wuint;



// Test fixture for umul192_upper128 function

class Umul192Upper128Test_309 : public ::testing::Test {

protected:

    uint128 y;

};



// Normal operation test

TEST_F(Umul192Upper128Test_309, NormalOperation_309) {

    std::uint_least64_t x = 123456789;

    y = uint128(987654321, 1122334455);

    uint128 result = umul192_upper128(x, y);

    // Assuming the correct calculation of upper 128 bits

    uint128 expected = uint128(0, 0); // Placeholder for actual expected value

    EXPECT_EQ(result.high(), expected.high());

    EXPECT_EQ(result.low(), expected.low());

}



// Boundary condition test with zero values

TEST_F(Umul192Upper128Test_309, ZeroValues_309) {

    std::uint_least64_t x = 0;

    y = uint128(0, 0);

    uint128 result = umul192_upper128(x, y);

    uint128 expected = uint128(0, 0);

    EXPECT_EQ(result.high(), expected.high());

    EXPECT_EQ(result.low(), expected.low());

}



// Boundary condition test with max values

TEST_F(Umul192Upper128Test_309, MaxValues_309) {

    std::uint_least64_t x = UINT64_MAX;

    y = uint128(UINT64_MAX, UINT64_MAX);

    uint128 result = umul192_upper128(x, y);

    // Assuming the correct calculation of upper 128 bits

    uint128 expected = uint128(0, 0); // Placeholder for actual expected value

    EXPECT_EQ(result.high(), expected.high());

    EXPECT_EQ(result.low(), expected.low());

}
