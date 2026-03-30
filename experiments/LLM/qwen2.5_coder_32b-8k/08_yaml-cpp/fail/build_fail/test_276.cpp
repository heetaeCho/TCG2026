#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Mocking a simple format for testing

struct TestFormat {

    static constexpr int significand_bits = 52;

    static constexpr int exponent_bits = 11;

};



typedef uint64_t carrier_uint;

typedef int32_t exponent_int;



typedef ieee754_binary_traits<TestFormat, carrier_uint, exponent_int> TestTraits;



TEST_F(DragonboxTest_276, IsPositive_Zero_ReturnsFalse_276) {

    EXPECT_FALSE(TestTraits::is_positive(0));

}



TEST_F(DragonboxTest_276, IsPositive_PositiveValue_ReturnsTrue_276) {

    EXPECT_TRUE(TestTraits::is_positive(1));

}



TEST_F(DragonboxTest_276, IsPositive_NegativeValue_ReturnsFalse_276) {

    carrier_uint negative_value = (carrier_uint(1) << (TestFormat::significand_bits + TestFormat::exponent_bits)) | 1;

    EXPECT_FALSE(TestTraits::is_positive(negative_value));

}



TEST_F(DragonboxTest_276, IsPositive_BoundaryValue_ReturnsFalse_276) {

    carrier_uint boundary_value = (carrier_uint(1) << (TestFormat::significand_bits + TestFormat::exponent_bits));

    EXPECT_FALSE(TestTraits::is_positive(boundary_value));

}



TEST_F(DragonboxTest_276, IsPositive_MaxValue_ReturnsTrue_276) {

    carrier_uint max_value = ~(carrier_uint(1) << (TestFormat::significand_bits + TestFormat::exponent_bits));

    EXPECT_TRUE(TestTraits::is_positive(max_value));

}
