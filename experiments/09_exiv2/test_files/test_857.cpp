#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Eq;



class LangAltValueTest_857 : public ::testing::Test {

protected:

    LangAltValue value_;

};



TEST_F(LangAltValueTest_857, ToStringWithExistingQualifier_ReturnsCorrectString_857) {

    value_.read(R"({"en":"Hello", "fr":"Bonjour"})");

    EXPECT_EQ(value_.toString("en"), "Hello");

}



TEST_F(LangAltValueTest_857, ToStringWithNonExistingQualifier_ReturnsEmptyString_857) {

    value_.read(R"({"en":"Hello", "fr":"Bonjour"})");

    EXPECT_EQ(value_.toString("de"), "");

}



TEST_F(LangAltValueTest_857, ToStringBoundaryCondition_EmptyJsonString_ReturnsEmptyString_857) {

    value_.read("");

    EXPECT_EQ(value_.toString("en"), "");

}



TEST_F(LangAltValueTest_857, ToStringBoundaryCondition_InvalidJsonString_ReturnsEmptyString_857) {

    value_.read("{invalid json}");

    EXPECT_EQ(value_.toString("en"), "");

}



TEST_F(LangAltValueTest_857, ReadValidJsonString_CountReturnsCorrectNumber_857) {

    value_.read(R"({"en":"Hello", "fr":"Bonjour"})");

    EXPECT_EQ(value_.count(), 2);

}



TEST_F(LangAltValueTest_857, ReadEmptyJsonString_CountReturnsZero_857) {

    value_.read("");

    EXPECT_EQ(value_.count(), 0);

}



TEST_F(LangAltValueTest_857, ReadInvalidJsonString_CountReturnsZero_857) {

    value_.read("{invalid json}");

    EXPECT_EQ(value_.count(), 0);

}
