#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Test fixture for ValueType<Rational>

class ValueTypeRationalTest_162 : public ::testing::Test {

protected:

    Rational rationalValue;

    ValueType<Rational> valueRational;



    void SetUp() override {

        rationalValue = Rational(1, 2);

        valueRational = ValueType<Rational>(rationalValue, TypeId::rational);

    }

};



// Test normal operation of toUint32

TEST_F(ValueTypeRationalTest_162, ToUint32_NormalOperation_162) {

    uint32_t result = valueRational.toUint32(0);

    EXPECT_EQ(result, 500000); // Assuming LARGE_INT is 1000000

}



// Test boundary condition of toUint32 with zero numerator

TEST_F(ValueTypeRationalTest_162, ToUint32_ZeroNumerator_162) {

    ValueType<Rational> valueZero(Rational(0, 1), TypeId::rational);

    uint32_t result = valueZero.toUint32(0);

    EXPECT_EQ(result, 0);

}



// Test boundary condition of toUint32 with zero denominator (should not occur in normal usage)

TEST_F(ValueTypeRationalTest_162, ToUint32_ZeroDenominator_162) {

    // This test assumes that the implementation handles zero denominator gracefully

    ValueType<Rational> valueZero(Rational(1, 0), TypeId::rational);

    EXPECT_THROW(valueZero.toUint32(0), std::overflow_error); // Assuming exception is thrown

}



// Test exceptional case of toUint32 with out-of-bounds index

TEST_F(ValueTypeRationalTest_162, ToUint32_OutOfBoundsIndex_162) {

    EXPECT_THROW(valueRational.toUint32(1), std::out_of_range); // Assuming exception is thrown for invalid index

}
