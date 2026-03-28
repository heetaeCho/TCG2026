#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest : public ::testing::Test {

protected:

    std::string sampleText = "Hello World!";

    AnsiSkippingString ansiStr;

    

    void SetUp() override {

        ansiStr = AnsiSkippingString(sampleText);

    }

};



TEST_F(AnsiSkippingStringTest_613, ConstructorWithLValueReference_613) {

    EXPECT_EQ(ansiStr.substring(ansiStr.begin(), ansiStr.end()), sampleText);

}



TEST_F(AnsiSkippingStringTest_613, ConstructorWithRValueReference_613) {

    AnsiSkippingString movedStr(std::move(sampleText));

    EXPECT_EQ(movedStr.substring(movedStr.begin(), movedStr.end()), "Hello World!");

}



TEST_F(AnsiSkippingStringTest_613, BeginEndIteratorsEquality_613) {

    EXPECT_TRUE(ansiStr.begin() != ansiStr.end());

}



TEST_F(AnsiSkippingStringTest_613, SubstringFullText_613) {

    EXPECT_EQ(ansiStr.substring(ansiStr.begin(), ansiStr.end()), sampleText);

}



TEST_F(AnsiSkippingStringTest_613, IteratorIncrementOperator_613) {

    auto it = ansiStr.begin();

    ++it;

    EXPECT_NE(it, ansiStr.begin());

}



TEST_F(AnsiSkippingStringTest_613, IteratorDecrementOperator_613) {

    auto it = ansiStr.end();

    --it;

    EXPECT_NE(it, ansiStr.end());

}



TEST_F(AnsiSkippingStringTest_613, IteratorDereferenceOperator_613) {

    auto it = ansiStr.begin();

    EXPECT_EQ(*it, 'H');

}



TEST_F(AnsiSkippingStringTest_613, SubstringPartialText_613) {

    auto startIt = ansiStr.begin();

    ++startIt;

    auto endIt = ansiStr.end();

    --endIt;

    EXPECT_EQ(ansiStr.substring(startIt, endIt), "ello World");

}



TEST_F(AnsiSkippingStringTest_613, SizeFunction_613) {

    EXPECT_EQ(ansiStr.size(), sampleText.size());

}
