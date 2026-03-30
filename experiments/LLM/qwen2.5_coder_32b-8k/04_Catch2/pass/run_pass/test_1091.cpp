#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest_1091 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(AnsiSkippingStringTest_1091, ConstructorWithConstStringRef_1091) {

    std::string text = "Sample text";

    AnsiSkippingString ansistr(text);

    EXPECT_EQ(ansistr.size(), text.length());

}



TEST_F(AnsiSkippingStringTest_1091, ConstructorWithRValueRef_1091) {

    std::string text = "Sample text";

    AnsiSkippingString ansistr(std::move(text));

    EXPECT_EQ(ansistr.size(), 11); // Length of "Sample text"

}



TEST_F(AnsiSkippingStringTest_1091, SizeReturnsCorrectLength_1091) {

    std::string text = "Another example";

    AnsiSkippingString ansistr(text);

    EXPECT_EQ(ansistr.size(), text.length());

}



TEST_F(AnsiSkippingStringTest_1091, EmptyStringSizeIsZero_1091) {

    std::string text = "";

    AnsiSkippingString ansistr(text);

    EXPECT_EQ(ansistr.size(), 0);

}



TEST_F(AnsiSkippingStringTest_1091, BeginAndEndIteratorsAreConsistent_1091) {

    std::string text = "Test string";

    AnsiSkippingString ansistr(text);

    auto beginIt = ansistr.begin();

    auto endIt = ansistr.end();

    EXPECT_EQ(std::distance(beginIt, endIt), static_cast<int>(text.length()));

}



TEST_F(AnsiSkippingStringTest_1091, SubstringReturnsCorrectPart_1091) {

    std::string text = "Hello, world!";

    AnsiSkippingString ansistr(text);

    auto beginIt = ansistr.begin();

    std::advance(beginIt, 7); // Move to 'w'

    auto endIt = ansistr.end();

    std::advance(endIt, -1); // Move to 'd'

    EXPECT_EQ(ansistr.substring(beginIt, endIt), "world");

}



TEST_F(AnsiSkippingStringTest_1091, SubstringHandlesEmptyRange_1091) {

    std::string text = "Hello";

    AnsiSkippingString ansistr(text);

    auto beginIt = ansistr.begin();

    auto endIt = ansistr.begin(); // Same as begin

    EXPECT_EQ(ansistr.substring(beginIt, endIt), "");

}
