#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class XmpArrayValueTest_843 : public ::testing::Test {

protected:

    XmpArrayValue xmpArrayValue{TypeId::xmpText};

};



TEST_F(XmpArrayValueTest_843, ReadNonEmptyBuffer_843) {

    int result = xmpArrayValue.read("test");

    EXPECT_EQ(result, 0);

}



TEST_F(XmpArrayValueTest_843, ReadEmptyBuffer_843) {

    int result = xmpArrayValue.read("");

    EXPECT_EQ(result, 0);

}



TEST_F(XmpArrayValueTest_843, CountAfterRead_843) {

    xmpArrayValue.read("test");

    EXPECT_EQ(xmpArrayValue.count(), 1);

}



TEST_F(XmpArrayValueTest_843, CountInitiallyZero_843) {

    EXPECT_EQ(xmpArrayValue.count(), 0);

}



// Assuming that toInt64, toUint32, toFloat, and toRational throw exceptions or return default values for non-numeric data.

TEST_F(XmpArrayValueTest_843, ToInt64NonNumeric_843) {

    xmpArrayValue.read("test");

    EXPECT_THROW(xmpArrayValue.toInt64(0), std::exception);

}



TEST_F(XmpArrayValueTest_843, ToUint32NonNumeric_843) {

    xmpArrayValue.read("test");

    EXPECT_THROW(xmpArrayValue.toUint32(0), std::exception);

}



TEST_F(XmpArrayValueTest_843, ToFloatNonNumeric_843) {

    xmpArrayValue.read("test");

    EXPECT_THROW(xmpArrayValue.toFloat(0), std::exception);

}



TEST_F(XmpArrayValueTest_843, ToRationalNonNumeric_843) {

    xmpArrayValue.read("test");

    EXPECT_THROW(xmpArrayValue.toRational(0), std::exception);

}



TEST_F(XmpArrayValueTest_843, ToStringReturnsContent_843) {

    xmpArrayValue.read("test");

    EXPECT_EQ(xmpArrayValue.toString(0), "test");

}



TEST_F(XmpArrayValueTest_843, WriteNonEmpty_843) {

    xmpArrayValue.read("test");

    std::ostringstream oss;

    xmpArrayValue.write(oss);

    EXPECT_EQ(oss.str(), "test");

}



TEST_F(XmpArrayValueTest_843, WriteEmpty_843) {

    std::ostringstream oss;

    xmpArrayValue.write(oss);

    EXPECT_EQ(oss.str(), "");

}
