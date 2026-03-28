#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Define a test fixture for the ieee754_binary_traits class

template <typename Format, typename CarrierUInt, typename ExponentInt>

class Ieee754BinaryTraitsTest : public ::testing::Test {

protected:

    using Traits = ieee754_binary_traits<Format, CarrierUInt, ExponentInt>;

};



// Specialize the test fixture for a specific format

using TestTypes = ::testing::Types<

    ieee754_binary_traits<ieee754::binary32, std::uint32_t, std::int32_t>,

    ieee754_binary_traits<ieee754::binary64, std::uint64_t, std::int32_t>

>;



TYPED_TEST_SUITE(Ieee754BinaryTraitsTest, TestTypes);



// Test the binary_significand function with normal operation

TYPED_TEST(Ieee754BinaryTraitsTest, BinarySignificand_NormalOperation_274) {

    using Traits = typename TestFixture::Traits;

    auto significand_bits = 0b1010;

    auto exponent_bits = 5;



    auto result = Traits::binary_significand(significand_bits, exponent_bits);



    EXPECT_EQ(result, 0b101010000); // Expected result considering the template parameters

}



// Test the binary_significand function with boundary conditions (exponent_bits == 0)

TYPED_TEST(Ieee754BinaryTraitsTest, BinarySignificand_ExponentZero_274) {

    using Traits = typename TestFixture::Traits;

    auto significand_bits = 0b1010;

    auto exponent_bits = 0;



    auto result = Traits::binary_significand(significand_bits, exponent_bits);



    EXPECT_EQ(result, 0b1010); // Expected result when exponent_bits is zero

}



// Test the binary_significand function with boundary conditions (significand_bits == 0)

TYPED_TEST(Ieee754BinaryTraitsTest, BinarySignificand_SignificandZero_274) {

    using Traits = typename TestFixture::Traits;

    auto significand_bits = 0;

    auto exponent_bits = 5;



    auto result = Traits::binary_significand(significand_bits, exponent_bits);



    EXPECT_EQ(result, 0b100000); // Expected result when significand_bits is zero

}



// Test the binary_significand function with boundary conditions (both bits are zero)

TYPED_TEST(Ieee754BinaryTraitsTest, BinarySignificand_BothZero_274) {

    using Traits = typename TestFixture::Traits;

    auto significand_bits = 0;

    auto exponent_bits = 0;



    auto result = Traits::binary_significand(significand_bits, exponent_bits);



    EXPECT_EQ(result, 0); // Expected result when both bits are zero

}



// Test the binary_significand function with large values (normal operation)

TYPED_TEST(Ieee754BinaryTraitsTest, BinarySignificand_LargeValues_274) {

    using Traits = typename TestFixture::Traits;
