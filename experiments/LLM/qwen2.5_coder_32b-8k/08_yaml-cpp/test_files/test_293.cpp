#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Assuming some reasonable types for carrier_uint and exponent_int based on common usage in such contexts.

using carrier_uint = uint64_t;

using exponent_int = int32_t;



class DragonboxFloatBitsTest : public ::testing::Test {

protected:

    float_bits<typename float_bits<>::format_traits> fb;

};



TEST_F(DragonboxFloatBitsTest_293, DefaultConstructorInitializesCorrectly_293) {

    // Assuming default constructor initializes to a valid state (e.g., zero or some known value).

    EXPECT_TRUE(fb.is_finite());

}



TEST_F(DragonboxFloatBitsTest_293, ExtractExponentBitsReturnsExpectedValue_293) {

    // Assuming a specific bit pattern for testing.

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_EQ(fb.extract_exponent_bits(), 127); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, ExtractSignificandBitsReturnsExpectedValue_293) {

    // Assuming a specific bit pattern for testing.

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_EQ(fb.extract_significand_bits(), 1558175); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, BinaryExponentStaticMethodReturnsExpectedValue_293) {

    exponent_int exp_bits = 127;

    EXPECT_EQ(float_bits<typename float_bits<>::format_traits>::binary_exponent(exp_bits), 0); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, BinaryExponentMethodReturnsExpectedValue_293) {

    // Assuming a specific bit pattern for testing.

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_EQ(fb.binary_exponent(), 0); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, BinarySignificandStaticMethodReturnsExpectedValue_293) {

    carrier_uint sig_bits = 1558175;

    exponent_int exp_bits = 0;

    EXPECT_EQ(float_bits<typename float_bits<>::format_traits>::binary_significand(sig_bits, exp_bits), 4660046); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, BinarySignificandMethodReturnsExpectedValue_293) {

    // Assuming a specific bit pattern for testing.

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_EQ(fb.binary_significand(), 4660046); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, IsNonzeroReturnsTrueForNonzeroValue_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_TRUE(fb.is_nonzero());

}



TEST_F(DragonboxFloatBitsTest_293, IsPositiveReturnsTrueForPositiveValue_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_TRUE(fb.is_positive());

}



TEST_F(DragonboxFloatBitsTest_293, IsNegativeReturnsFalseForPositiveValue_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_FALSE(fb.is_negative());

}



TEST_F(DragonboxFloatBitsTest_293, IsFiniteReturnsTrueForNormalNumber_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_TRUE(fb.is_finite());

}



TEST_F(DragonboxFloatBitsTest_293, HasEvenSignificandBitsReturnsExpectedValue_293) {

    // Assuming a specific bit pattern for testing.

    float_bits<typename float_bits<>::format_traits> fb(0x40490fdb);

    EXPECT_FALSE(fb.has_even_significand_bits()); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, BoundaryConditionsWithZeroExponent_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x3f800000);

    EXPECT_EQ(fb.extract_exponent_bits(), 127); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, BoundaryConditionsWithMaxExponent_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x7f800000);

    EXPECT_EQ(fb.extract_exponent_bits(), 255); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, BoundaryConditionsWithMinNormalExponent_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x01800000);

    EXPECT_EQ(fb.extract_exponent_bits(), -126); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, BoundaryConditionsWithMaxSignificand_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x7f800001);

    EXPECT_EQ(fb.extract_significand_bits(), 1); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, ErrorCaseWithNaN_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x7fc00000);

    EXPECT_FALSE(fb.is_finite()); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, ErrorCaseWithInfinity_293) {

    float_bits<typename float_bits<>::format_traits> fb(0x7f800000);

    EXPECT_FALSE(fb.is_finite()); // Example value based on IEEE 754 single precision.

}



TEST_F(DragonboxFloatBitsTest_293, ErrorCaseWithNegativeInfinity_293) {

    float_bits<typename float_bits<>::format_traits> fb(0xff800000);

    EXPECT_FALSE(fb.is_finite()); // Example value based on IEEE 754 single precision.

}
