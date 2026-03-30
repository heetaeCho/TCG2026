#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



class LangAltValueTest_853 : public Test {

protected:

    LangAltValue langAltValue_;

};



TEST_F(LangAltValueTest_853, CloneReturnsNonNullPointer_853) {

    auto cloned = langAltValue_.clone();

    EXPECT_NE(cloned.get(), nullptr);

}



TEST_F(LangAltValueTest_853, CountIsZeroInitially_853) {

    EXPECT_EQ(langAltValue_.count(), 0u);

}



TEST_F(LangAltValueTest_853, ToStringReturnsEmptyStringWithoutQualifier_853) {

    EXPECT_EQ(langAltValue_.toString(""), "");

}



TEST_F(LangAltValueTest_853, ToStringWithIndexReturnsEmptyStringInitially_853) {

    EXPECT_EQ(langAltValue_.toString(0), "");

}



TEST_F(LangAltValueTest_853, ToInt64ReturnsZeroInitially_853) {

    EXPECT_EQ(langAltValue_.toInt64(0), 0);

}



TEST_F(LangAltValueTest_853, ToUint32ReturnsZeroInitially_853) {

    EXPECT_EQ(langAltValue_.toUint32(0), 0u);

}



TEST_F(LangAltValueTest_853, ToFloatReturnsZeroInitially_853) {

    EXPECT_FLOAT_EQ(langAltValue_.toFloat(0), 0.0f);

}



TEST_F(LangAltValueTest_853, ToRationalReturnsZeroInitially_853) {

    EXPECT_EQ(langAltValue_.toRational(0), Rational(0, 1));

}



// Assuming read() modifies the internal state and count() reflects it

TEST_F(LangAltValueTest_853, ReadUpdatesCount_853) {

    std::string buf = "some_data";

    langAltValue_.read(buf);

    EXPECT_GT(langAltValue_.count(), 0u);

}



// Assuming read() modifies the internal state and toString() reflects it

TEST_F(LangAltValueTest_853, ReadUpdatesToStringOutput_853) {

    std::string buf = "some_data";

    langAltValue_.read(buf);

    EXPECT_FALSE(langAltValue_.toString(0).empty());

}



// Assuming read() modifies the internal state and toString() with qualifier reflects it

TEST_F(LangAltValueTest_853, ReadUpdatesToStringWithQualifierOutput_853) {

    std::string buf = "some_data";

    langAltValue_.read(buf);

    EXPECT_FALSE(langAltValue_.toString("x-default").empty());

}
