#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Define a mock struct for FormatTraits if needed, but in this case, it's not necessary as we treat the implementation as a black box.



struct TestFormatTraits {

    using exponent_int = int;

    using carrier_uint = unsigned int;

};



typedef float_bits<TestFormatTraits> TestFloatBits;



class DragonboxTest_291 : public ::testing::Test {

protected:

    TestFloatBits test_float_bits;

};



TEST_F(DragonboxTest_291, BinaryExponent_ReturnsCorrectValue_291) {

    // Assuming some known values for testing

    TestFormatTraits::exponent_int exponent_bits = 0x7F800000; // Example bits representing the exponent

    TestFormatTraits::exponent_int expected_exponent = 127;     // Expected result based on IEEE 754 single-precision format



    EXPECT_EQ(TestFloatBits::binary_exponent(exponent_bits), expected_exponent);

}



TEST_F(DragonboxTest_291, BinaryExponent_BoundaryCondition_Zero_291) {

    TestFormatTraits::exponent_int exponent_bits = 0; // Zero bits

    TestFormatTraits::exponent_int expected_exponent = -126; // Expected result based on IEEE 754 single-precision format



    EXPECT_EQ(TestFloatBits::binary_exponent(exponent_bits), expected_exponent);

}



TEST_F(DragonboxTest_291, BinaryExponent_BoundaryCondition_Max_291) {

    TestFormatTraits::exponent_int exponent_bits = 0xFF800000; // Max bits

    TestFormatTraits::exponent_int expected_exponent = 127;     // Expected result based on IEEE 754 single-precision format



    EXPECT_EQ(TestFloatBits::binary_exponent(exponent_bits), expected_exponent);

}



TEST_F(DragonboxTest_291, BinaryExponent_ExceptionalCase_Denormalized_291) {

    TestFormatTraits::exponent_int exponent_bits = 0; // Denormalized number

    EXPECT_EQ(test_float_bits.is_finite(exponent_bits), true); // Denormalized numbers are finite

}



TEST_F(DragonboxTest_291, IsFinite_ReturnsTrueForNormalNumber_291) {

    TestFormatTraits::carrier_uint bit_pattern = 0x40490fdb; // Example bits representing a normal number (3.14f)

    test_float_bits = TestFloatBits(bit_pattern);



    EXPECT_TRUE(test_float_bits.is_finite());

}



TEST_F(DragonboxTest_291, IsFinite_ReturnsFalseForInfinity_291) {

    TestFormatTraits::carrier_uint bit_pattern = 0x7F800000; // Example bits representing positive infinity

    test_float_bits = TestFloatBits(bit_pattern);



    EXPECT_FALSE(test_float_bits.is_finite());

}



TEST_F(DragonboxTest_291, IsFinite_ReturnsFalseForNegativeInfinity_291) {

    TestFormatTraits::carrier_uint bit_pattern = 0xFF800000; // Example bits representing negative infinity

    test_float_bits = TestFloatBits(bit_pattern);



    EXPECT_FALSE(test_float_bits.is_finite());

}



TEST_F(DragonboxTest_291, IsFinite_ReturnsTrueForDenormalizedNumber_291) {

    TestFormatTraits::carrier_uint bit_pattern = 0x00400000; // Example bits representing a denormalized number

    test_float_bits = TestFloatBits(bit_pattern);



    EXPECT_TRUE(test_float_bits.is_finite());

}
