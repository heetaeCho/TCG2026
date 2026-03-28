#include <gtest/gtest.h>

#include <Exiv2/exiv2.hpp>



namespace {



using namespace Exiv2;



class FloatToRationalCastTest_1161 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(FloatToRationalCastTest_1161, PositiveSmallValue_1161) {

    float f = 0.000001f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, 1000000);

}



TEST_F(FloatToRationalCastTest_1161, PositiveMediumValue_1161) {

    float f = 0.001f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, 1000);

}



TEST_F(FloatToRationalCastTest_1161, PositiveLargeValue_1161) {

    float f = 1.5f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, 3);

    EXPECT_EQ(result.second, 2);

}



TEST_F(FloatToRationalCastTest_1161, NegativeSmallValue_1161) {

    float f = -0.000001f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, -1);

    EXPECT_EQ(result.second, 1000000);

}



TEST_F(FloatToRationalCastTest_1161, NegativeMediumValue_1161) {

    float f = -0.001f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, -1);

    EXPECT_EQ(result.second, 1000);

}



TEST_F(FloatToRationalCastTest_1161, NegativeLargeValue_1161) {

    float f = -1.5f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, -3);

    EXPECT_EQ(result.second, 2);

}



TEST_F(FloatToRationalCastTest_1161, ZeroValue_1161) {

    float f = 0.0f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 1);

}



TEST_F(FloatToRationalCastTest_1161, MaxPositiveValue_1161) {

    float f = static_cast<float>(std::numeric_limits<int32_t>::max());

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, std::numeric_limits<int32_t>::max());

    EXPECT_EQ(result.second, 1);

}



TEST_F(FloatToRationalCastTest_1161, MaxNegativeValue_1161) {

    float f = static_cast<float>(std::numeric_limits<int32_t>::min());

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, std::numeric_limits<int32_t>::min());

    EXPECT_EQ(result.second, 1);

}



TEST_F(FloatToRationalCastTest_1161, TooLargePositiveValue_1161) {

    float f = static_cast<float>(std::numeric_limits<int32_t>::max()) * 2.0f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, 0);

}



TEST_F(FloatToRationalCastTest_1161, TooLargeNegativeValue_1161) {

    float f = static_cast<float>(std::numeric_limits<int32_t>::min()) * 2.0f;

    Rational result = floatToRationalCast(f);

    EXPECT_EQ(result.first, -1);

    EXPECT_EQ(result.second, 0);

}



} // namespace
