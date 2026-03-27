#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/value.hpp>

#include <string>

#include <sstream>



using namespace Exiv2;

using testing::_;

using testing::Return;



class XmpTextValueTest_837 : public ::testing::Test {

protected:

    XmpTextValue xmpTextValue;

};



TEST_F(XmpTextValueTest_837, DefaultConstructorInitializesCountToZero_837) {

    EXPECT_EQ(xmpTextValue.count(), 0);

}



TEST_F(XmpTextValueTest_837, ConstructorWithEmptyStringInitializesCountToZero_837) {

    XmpTextValue value("");

    EXPECT_EQ(value.count(), 0);

}



TEST_F(XmpTextValueTest_837, ReadWithNonEmptyStringSetsCountCorrectly_837) {

    xmpTextValue.read("test");

    EXPECT_EQ(xmpTextValue.count(), 1); // Assuming read with non-empty string sets count to 1

}



TEST_F(XmpTextValueTest_837, CloneCreatesObjectWithSameCount_837) {

    xmpTextValue.read("test");

    XmpTextValue::UniquePtr clonedValue = xmpTextValue.clone();

    EXPECT_EQ(clonedValue->count(), xmpTextValue.count());

}



TEST_F(XmpTextValueTest_837, ToInt64ReturnsZeroForEmptyString_837) {

    int64_t result = xmpTextValue.toInt64(0);

    EXPECT_EQ(result, 0);

}



TEST_F(XmpTextValueTest_837, ToUint32ReturnsZeroForEmptyString_837) {

    uint32_t result = xmpTextValue.toUint32(0);

    EXPECT_EQ(result, 0);

}



TEST_F(XmpTextValueTest_837, ToFloatReturnsZeroForEmptyString_837) {

    float result = xmpTextValue.toFloat(0);

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST_F(XmpTextValueTest_837, ToRationalReturnsZeroForEmptyString_837) {

    Rational result = xmpTextValue.toRational(0);

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 1); // Default denominator is typically 1

}



TEST_F(XmpTextValueTest_837, WriteToStreamDoesNotThrowForEmptyString_837) {

    std::ostringstream oss;

    EXPECT_NO_THROW(xmpTextValue.write(oss));

}



TEST_F(XmpTextValueTest_837, ReadWithLargeStringDoesNotThrow_837) {

    std::string largeString(1000000, 'a'); // Assuming LARGE_INT is 1000000

    EXPECT_NO_THROW(xmpTextValue.read(largeString));

}
