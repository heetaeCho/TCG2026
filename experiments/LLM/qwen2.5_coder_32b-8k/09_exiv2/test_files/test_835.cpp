#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpTextValueTest_835 : public ::testing::Test {

protected:

    XmpTextValue xmpTextValue;

};



TEST_F(XmpTextValueTest_835, CloneReturnsNonNullPointer_835) {

    auto clonedValue = xmpTextValue.clone();

    EXPECT_NE(clonedValue.get(), nullptr);

}



TEST_F(XmpTextValueTest_835, SizeIsZeroForDefaultConstructor_835) {

    EXPECT_EQ(xmpTextValue.size(), 0U);

}



TEST_F(XmpTextValueTest_835, CountIsZeroForDefaultConstructor_835) {

    EXPECT_EQ(xmpTextValue.count(), 0U);

}



TEST_F(XmpTextValueTest_835, ReadReturnsZeroForEmptyString_835) {

    std::string emptyBuf = "";

    EXPECT_EQ(xmpTextValue.read(emptyBuf), 0);

}



TEST_F(XmpTextValueTest_835, ToInt64ThrowsForDefaultConstructor_835) {

    EXPECT_THROW(xmpTextValue.toInt64(0), Error);

}



TEST_F(XmpTextValueTest_835, ToUint32ThrowsForDefaultConstructor_835) {

    EXPECT_THROW(xmpTextValue.toUint32(0), Error);

}



TEST_F(XmpTextValueTest_835, ToFloatThrowsForDefaultConstructor_835) {

    EXPECT_THROW(xmpTextValue.toFloat(0), Error);

}



TEST_F(XmpTextValueTest_835, ToRationalThrowsForDefaultConstructor_835) {

    EXPECT_THROW(xmpTextValue.toRational(0), Error);

}



class XmpTextValueWithContentTest_835 : public ::testing::Test {

protected:

    XmpTextValue xmpTextValue;

    std::string testString = "test content";

};



TEST_F(XmpTextValueWithContentTest_835, ReadSetsCorrectSize_835) {

    xmpTextValue.read(testString);

    EXPECT_EQ(xmpTextValue.size(), testString.size());

}



TEST_F(XmpTextValueWithContentTest_835, ReadReturnsPositiveValueOnSuccess_835) {

    int result = xmpTextValue.read(testString);

    EXPECT_GT(result, 0);

}



TEST_F(XmpTextValueWithContentTest_835, ClonePreservesData_835) {

    xmpTextValue.read(testString);

    auto clonedValue = xmpTextValue.clone();

    std::ostringstream os1, os2;

    xmpTextValue.write(os1);

    clonedValue->write(os2);

    EXPECT_EQ(os1.str(), os2.str());

}



TEST_F(XmpTextValueWithContentTest_835, ToInt64ThrowsForNonNumericString_835) {

    xmpTextValue.read(testString);

    EXPECT_THROW(xmpTextValue.toInt64(0), Error);

}



TEST_F(XmpTextValueWithContentTest_835, ToUint32ThrowsForNonNumericString_835) {

    xmpTextValue.read(testString);

    EXPECT_THROW(xmpTextValue.toUint32(0), Error);

}



TEST_F(XmpTextValueWithContentTest_835, ToFloatThrowsForNonNumericString_835) {

    xmpTextValue.read(testString);

    EXPECT_THROW(xmpTextValue.toFloat(0), Error);

}



TEST_F(XmpTextValueWithContentTest_835, ToRationalThrowsForNonNumericString_835) {

    xmpTextValue.read(testString);

    EXPECT_THROW(xmpTextValue.toRational(0), Error);

}
