#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/utils/HtmlLinks.cc"

#include "./TestProjects/poppler/goo/GooString.h"



class EscapeSpecialCharsTest : public ::testing::Test {

protected:

    std::unique_ptr<GooString> testString;



    void SetUp() override {

        testString = std::make_unique<GooString>();

    }

};



TEST_F(EscapeSpecialCharsTest_2660, NormalOperation_NoSpecialChars_2660) {

    *testString = "HelloWorld";

    auto result = EscapeSpecialChars(testString.get());

    ASSERT_TRUE(result);

    EXPECT_EQ(result->toStr(), "HelloWorld");

}



TEST_F(EscapeSpecialCharsTest_2660, NormalOperation_AllSpecialChars_2660) {

    *testString = "\"&<>";

    auto result = EscapeSpecialChars(testString.get());

    ASSERT_TRUE(result);

    EXPECT_EQ(result->toStr(), "&quot;&amp;&lt;&gt;");

}



TEST_F(EscapeSpecialCharsTest_2660, BoundaryCondition_EmptyString_2660) {

    *testString = "";

    auto result = EscapeSpecialChars(testString.get());

    ASSERT_TRUE(result);

    EXPECT_EQ(result->toStr(), "");

}



TEST_F(EscapeSpecialCharsTest_2660, BoundaryCondition_SingleChar_NoSpecial_2660) {

    *testString = "H";

    auto result = EscapeSpecialChars(testString.get());

    ASSERT_FALSE(result); // No special characters to escape

}



TEST_F(EscapeSpecialCharsTest_2660, BoundaryCondition_SingleChar_Special_2660) {

    *testString = "\"";

    auto result = EscapeSpecialChars(testString.get());

    ASSERT_TRUE(result);

    EXPECT_EQ(result->toStr(), "&quot;");

}



TEST_F(EscapeSpecialCharsTest_2660, ExceptionalCase_NullInput_2660) {

    GooString* nullString = nullptr;

    auto result = EscapeSpecialChars(nullString);

    ASSERT_FALSE(result); // Null input should return null

}
