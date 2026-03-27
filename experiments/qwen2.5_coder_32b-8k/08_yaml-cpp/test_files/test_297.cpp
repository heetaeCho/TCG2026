#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Fixture for float_bits tests

class FloatBitsTest_297 : public ::testing::Test {

protected:

    using FormatTraits = /* appropriate format traits type */;

    using BitsType = float_bits<FormatTraits>;

    

    BitsType positive_bits;

    BitsType negative_bits;

    BitsType zero_bits;



    void SetUp() override {

        // Initialize with appropriate bit patterns for positive, negative, and zero

        positive_bits = BitsType(/* bit pattern for a positive number */);

        negative_bits = BitsType(/* bit pattern for a negative number */);

        zero_bits = BitsType(/* bit pattern for zero */);

    }

};



// Test if is_negative returns true for negative numbers

TEST_F(FloatBitsTest_297, IsNegative_ReturnsTrueForNegativeNumbers_297) {

    EXPECT_TRUE(negative_bits.is_negative());

}



// Test if is_negative returns false for positive numbers

TEST_F(FloatBitsTest_297, IsNegative_ReturnsFalseForPositiveNumbers_297) {

    EXPECT_FALSE(positive_bits.is_negative());

}



// Test if is_negative returns false for zero

TEST_F(FloatBitsTest_297, IsNegative_ReturnsFalseForZero_297) {

    EXPECT_FALSE(zero_bits.is_negative());

}

```


