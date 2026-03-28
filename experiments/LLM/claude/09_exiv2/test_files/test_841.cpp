#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cmath>
#include <limits>

class XmpTextValueTest_841 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(XmpTextValueTest_841, ToFloatWithIntegerValue_841) {
    Exiv2::XmpTextValue value;
    value.read("42");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 42.0f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithDecimalValue_841) {
    Exiv2::XmpTextValue value;
    value.read("3.14");
    float result = value.toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithNegativeValue_841) {
    Exiv2::XmpTextValue value;
    value.read("-7.5");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, -7.5f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithZero_841) {
    Exiv2::XmpTextValue value;
    value.read("0");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithFractionString_841) {
    Exiv2::XmpTextValue value;
    value.read("1/2");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.5f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithFractionNegativeNumerator_841) {
    Exiv2::XmpTextValue value;
    value.read("-3/4");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, -0.75f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithLargeValue_841) {
    Exiv2::XmpTextValue value;
    value.read("1000000.5");
    float result = value.toFloat(0);
    EXPECT_NEAR(result, 1000000.5f, 1.0f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithVerySmallValue_841) {
    Exiv2::XmpTextValue value;
    value.read("0.0001");
    float result = value.toFloat(0);
    EXPECT_NEAR(result, 0.0001f, 0.00001f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithNParameterIgnored_841) {
    Exiv2::XmpTextValue value;
    value.read("5.5");
    float result0 = value.toFloat(0);
    float result1 = value.toFloat(1);
    float result99 = value.toFloat(99);
    EXPECT_FLOAT_EQ(result0, result1);
    EXPECT_FLOAT_EQ(result0, result99);
}

TEST_F(XmpTextValueTest_841, ToFloatWithPositiveSign_841) {
    Exiv2::XmpTextValue value;
    value.read("+2.5");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 2.5f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithWholeNumberFraction_841) {
    Exiv2::XmpTextValue value;
    value.read("10/5");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 2.0f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithNegativeDecimal_841) {
    Exiv2::XmpTextValue value;
    value.read("-0.001");
    float result = value.toFloat(0);
    EXPECT_NEAR(result, -0.001f, 0.0001f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithFractionOneDenominator_841) {
    Exiv2::XmpTextValue value;
    value.read("7/1");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 7.0f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithEmptyString_841) {
    Exiv2::XmpTextValue value;
    value.read("");
    // Just ensure it doesn't crash; the result may be 0 or undefined
    float result = value.toFloat(0);
    EXPECT_FALSE(std::isnan(result) && std::isinf(result) && result != 0.0f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithLeadingZeros_841) {
    Exiv2::XmpTextValue value;
    value.read("007.5");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 7.5f);
}

TEST_F(XmpTextValueTest_841, ToFloatWithIntegerFraction_841) {
    Exiv2::XmpTextValue value;
    value.read("100/10");
    float result = value.toFloat(0);
    EXPECT_FLOAT_EQ(result, 10.0f);
}
