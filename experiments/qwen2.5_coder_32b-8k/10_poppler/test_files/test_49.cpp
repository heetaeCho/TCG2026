#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "FoFiType1.cc"



class FoFiType1TokenizerTest : public ::testing::Test {

protected:

    void SetUp() override {

        tokenizer = std::make_unique<FoFiType1Tokenizer>("Hello World! This is a test.");

    }



    std::unique_ptr<FoFiType1Tokenizer> tokenizer;

};



TEST_F(FoFiType1TokenizerTest_49, GetToken_ReturnsFirstWord_49) {

    auto token = tokenizer->getToken();

    ASSERT_TRUE(token.has_value());

    EXPECT_EQ(*token, "Hello");

}



TEST_F(FoFiType1TokenizerTest_49, GetToken_SecondCall_ReturnsSecondWord_49) {

    tokenizer->getToken(); // First call to skip "Hello"

    auto token = tokenizer->getToken();

    ASSERT_TRUE(token.has_value());

    EXPECT_EQ(*token, "World!");

}



TEST_F(FoFiType1TokenizerTest_49, GetToken_EndOfInput_ReturnsEmpty_49) {

    tokenizer->getToken(); // Skip "Hello"

    tokenizer->getToken(); // Skip "World!"

    tokenizer->getToken(); // Skip "This"

    tokenizer->getToken(); // Skip "is"

    tokenizer->getToken(); // Skip "a"

    tokenizer->getToken(); // Skip "test."

    auto token = tokenizer->getToken();

    EXPECT_FALSE(token.has_value());

}



TEST_F(FoFiType1TokenizerTest_49, GetToken_MultipleSpaces_SkipsThem_49) {

    tokenizer.reset(new FoFiType1Tokenizer("Hello   World!"));

    tokenizer->getToken(); // Skip "Hello"

    auto token = tokenizer->getToken();

    ASSERT_TRUE(token.has_value());

    EXPECT_EQ(*token, "World!");

}



TEST_F(FoFiType1TokenizerTest_49, GetToken_StartWithSpaces_IgnoresThem_49) {

    tokenizer.reset(new FoFiType1Tokenizer("   Hello World!"));

    auto token = tokenizer->getToken();

    ASSERT_TRUE(token.has_value());

    EXPECT_EQ(*token, "Hello");

}



TEST_F(FoFiType1TokenizerTest_49, GetToken_EndsWithSpaces_ReturnsWord_49) {

    tokenizer.reset(new FoFiType1Tokenizer("Hello World!   "));

    tokenizer->getToken(); // Skip "Hello"

    auto token = tokenizer->getToken();

    ASSERT_TRUE(token.has_value());

    EXPECT_EQ(*token, "World!");

}



TEST_F(FoFiType1TokenizerTest_49, GetToken_EmptyString_ReturnsEmpty_49) {

    tokenizer.reset(new FoFiType1Tokenizer(""));

    auto token = tokenizer->getToken();

    EXPECT_FALSE(token.has_value());

}



TEST_F(FoFiType1TokenizerTest_49, GetToken_StringWithOnlySeparators_ReturnsEmpty_49) {

    tokenizer.reset(new FoFiType1Tokenizer(" \t\n\r"));

    auto token = tokenizer->getToken();

    EXPECT_FALSE(token.has_value());

}
