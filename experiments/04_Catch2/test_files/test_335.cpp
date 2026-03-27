#include <gtest/gtest.h>

#include "catch2/internal/catch_random_integer_helpers.hpp"

#include <limits>



class TransposeToNaturalOrderTest_335 : public ::testing::Test {

protected:

    using OriginalType = int;

    using UnsignedType = unsigned int;



    static constexpr auto highest_bit = UnsignedType(1) << (sizeof(UnsignedType) * CHAR_BIT - 1);



    void checkTranspose(int originalValue, unsigned int expectedUnsignedValue) {

        EXPECT_EQ(Catch::Detail::transposeToNaturalOrder<OriginalType, UnsignedType>(expectedUnsignedValue), expectedUnsignedValue);

    }

};



TEST_F(TransposeToNaturalOrderTest_335, ZeroInput_335) {

    // Test zero input

    checkTranspose(0, highest_bit);

}



TEST_F(TransposeToNaturalOrderTest_335, MaxPositiveInt_335) {

    // Test max positive int

    unsigned int expected = std::numeric_limits<int>::max() ^ highest_bit;

    checkTranspose(std::numeric_limits<int>::max(), expected);

}



TEST_F(TransposeToNaturalOrderTest_335, MinNegativeInt_335) {

    // Test min negative int

    unsigned int expected = std::numeric_limits<int>::min() ^ highest_bit;

    checkTranspose(std::numeric_limits<int>::min(), expected);

}



TEST_F(TransposeToNaturalOrderTest_335, RandomPositiveValue_335) {

    // Test a random positive value

    int originalValue = 42;

    unsigned int expected = originalValue ^ highest_bit;

    checkTranspose(originalValue, expected);

}



TEST_F(TransposeToNaturalOrderTest_335, RandomNegativeValue_335) {

    // Test a random negative value

    int originalValue = -42;

    unsigned int expected = static_cast<unsigned int>(originalValue) ^ highest_bit;

    checkTranspose(originalValue, expected);

}
