#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"

#include "catch2/catch_case_sensitive.hpp"



using namespace Catch::Matchers;

using ::testing::Eq;



class CasedStringTest_216 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }

};



TEST_F(CasedStringTest_216, AdjustString_CaseSensitive_216) {

    CasedString casedStr("HelloWorld", CaseSensitive::Yes);

    EXPECT_EQ(casedStr.adjustString("HelloWorld"), "HelloWorld");

}



TEST_F(CasedStringTest_216, AdjustString_NotCaseSensitive_216) {

    CasedString casedStr("HelloWorld", CaseSensitive::No);

    EXPECT_EQ(casedStr.adjustString("HelloWorld"), "helloworld");

}



TEST_F(CasedStringTest_216, AdjustString_EmptyString_216) {

    CasedString casedStr("", CaseSensitive::Yes);

    EXPECT_EQ(casedStr.adjustString(""), "");

}



TEST_F(CasedStringTest_216, AdjustString_AllUpperCase_216) {

    CasedString casedStr("HELLOWORLD", CaseSensitive::No);

    EXPECT_EQ(casedStr.adjustString("HELLOWORLD"), "helloworld");

}



TEST_F(CasedStringTest_216, AdjustString_MixedCase_216) {

    CasedString casedStr("HeLlOwOrLd", CaseSensitive::No);

    EXPECT_EQ(casedStr.adjustString("HeLlOwOrLd"), "helloworld");

}



TEST_F(CasedStringTest_216, CaseSensitivitySuffix_CaseSensitive_216) {

    CasedString casedStr("HelloWorld", CaseSensitive::Yes);

    EXPECT_EQ(casedStr.caseSensitivitySuffix(), "");

}



TEST_F(CasedStringTest_216, CaseSensitivitySuffix_NotCaseSensitive_216) {

    CasedString casedStr("HelloWorld", CaseSensitive::No);

    EXPECT_EQ(casedStr.caseSensitivitySuffix(), "(case-insensitive)");

}
