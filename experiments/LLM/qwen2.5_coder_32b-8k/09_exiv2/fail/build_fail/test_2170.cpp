#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <string>



namespace {



using namespace Exiv2;



TEST_F(LangAltValueTest_2170, ConstructorWithEmptyString_2170) {

    LangAltValue value("");

    EXPECT_EQ(value.count(), 0U);

}



TEST_F(LangAltValueTest_2170, ReadValidString_2170) {

    std::string validBuf = "lang=EN,Hello";

    LangAltValue value(validBuf);

    EXPECT_EQ(value.count(), 1U);

}



TEST_F(LangAltValueTest_2170, ReadInvalidString_2170) {

    std::string invalidBuf = "invalid_format";

    LangAltValue value(invalidBuf);

    EXPECT_EQ(value.count(), 0U);

}



TEST_F(LangAltValueTest_2170, ToStringWithQualifier_2170) {

    std::string validBuf = "lang=EN,Hello";

    LangAltValue value(validBuf);

    EXPECT_EQ(value.toString("lang=EN"), "Hello");

}



TEST_F(LangAltValueTest_2170, ToStringWithoutQualifier_2170) {

    std::string validBuf = "lang=EN,Hello";

    LangAltValue value(validBuf);

    EXPECT_EQ(value.toString(0), "Hello");

}



TEST_F(LangAltValueTest_2170, ToInt64BoundaryCondition_2170) {

    std::string bufWithNumber = "lang=EN,12345";

    LangAltValue value(bufWithNumber);

    EXPECT_EQ(value.toInt64(0), 12345LL);

}



TEST_F(LangAltValueTest_2170, ToUint32BoundaryCondition_2170) {

    std::string bufWithNumber = "lang=EN,12345";

    LangAltValue value(bufWithNumber);

    EXPECT_EQ(value.toUint32(0), 12345U);

}



TEST_F(LangAltValueTest_2170, ToFloatBoundaryCondition_2170) {

    std::string bufWithNumber = "lang=EN,123.45";

    LangAltValue value(bufWithNumber);

    EXPECT_FLOAT_EQ(value.toFloat(0), 123.45f);

}



TEST_F(LangAltValueTest_2170, ToRationalBoundaryCondition_2170) {

    std::string bufWithNumber = "lang=EN,1/2";

    LangAltValue value(bufWithNumber);

    Rational expected(1, 2);

    EXPECT_EQ(value.toRational(0), expected);

}



TEST_F(LangAltValueTest_2170, CloneFunctionality_2170) {

    std::string validBuf = "lang=EN,Hello";

    LangAltValue value(validBuf);

    auto clone = value.clone();

    EXPECT_EQ(clone->toString("lang=EN"), "Hello");

}



TEST_F(LangAltValueTest_2170, CountFunctionalityAfterRead_2170) {

    std::string validBuf = "lang=EN,Hello;lang=FR,Bonjour";

    LangAltValue value(validBuf);

    EXPECT_EQ(value.count(), 2U);

}



TEST_F(LangAltValueTest_2170, SizeFunctionality_2170) {

    std::string validBuf = "lang=EN,Hello";

    LangAltValue value(validBuf);

    EXPECT_GT(value.size(), 0U); // Assuming size() returns the number of bytes used

}



} // namespace
