#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include <string>



using namespace Exiv2;



// Mock class for ExifKey to satisfy constructor requirements

class MockExifKey : public ExifKey {

public:

    MockExifKey() : ExifKey("MockKey", ifdId::IFD0, 0x0000) {}

    std::string key() const override { return "MockKey"; }

};



// Fixture for Exifdatum tests

class ExifdatumTest_727 : public ::testing::Test {

protected:

    Exifdatum exifDatum;



    ExifdatumTest_727() : exifDatum(MockExifKey(), nullptr) {}

};



TEST_F(ExifdatumTest_727, SetValueStringNormalOperation_727) {

    std::string testValue = "test";

    setValue(exifDatum, testValue);

    EXPECT_EQ(exifDatum.toString(), testValue);

}



TEST_F(ExifdatumTest_727, SetValueIntNormalOperation_727) {

    int testValue = 42;

    setValue(exifDatum, testValue);

    EXPECT_EQ(exifDatum.toInt64(), static_cast<int64_t>(testValue));

}



TEST_F(ExifdatumTest_727, SetValueFloatNormalOperation_727) {

    float testValue = 3.14f;

    setValue(exifDatum, testValue);

    EXPECT_FLOAT_EQ(exifDatum.toFloat(), testValue);

}



TEST_F(ExifdatumTest_727, SetValueRationalNormalOperation_727) {

    Rational testValue(3, 2);

    setValue(exifDatum, testValue);

    EXPECT_EQ(exifDatum.toRational().first, testValue.first);

    EXPECT_EQ(exifDatum.toRational().second, testValue.second);

}



TEST_F(ExifdatumTest_727, SetValueStringBoundaryConditionEmptyString_727) {

    std::string emptyValue = "";

    setValue(exifDatum, emptyValue);

    EXPECT_EQ(exifDatum.toString(), emptyValue);

}



TEST_F(ExifdatumTest_727, SetValueIntBoundaryConditionZero_727) {

    int zeroValue = 0;

    setValue(exifDatum, zeroValue);

    EXPECT_EQ(exifDatum.toInt64(), static_cast<int64_t>(zeroValue));

}



TEST_F(ExifdatumTest_727, SetValueFloatBoundaryConditionZero_727) {

    float zeroValue = 0.0f;

    setValue(exifDatum, zeroValue);

    EXPECT_FLOAT_EQ(exifDatum.toFloat(), zeroValue);

}



TEST_F(ExifdatumTest_727, SetValueRationalBoundaryConditionZeroNumerator_727) {

    Rational zeroNumerator(0, 1);

    setValue(exifDatum, zeroNumerator);

    EXPECT_EQ(exifDatum.toRational().first, zeroNumerator.first);

    EXPECT_EQ(exifDatum.toRational().second, zeroNumerator.second);

}



TEST_F(ExifdatumTest_727, SetValueRationalBoundaryConditionZeroDenominator_727) {

    Rational zeroDenominator(1, 0); // This should be handled internally but test for robustness

    setValue(exifDatum, zeroDenominator);

    EXPECT_EQ(exifDatum.toRational().first, zeroDenominator.first);

    EXPECT_EQ(exifDatum.toRational().second, zeroDenominator.second);

}
