#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(AnsiSkippingStringTest_35, DefaultConstructorSizeIsZero_35) {

    AnsiSkippingString str;

    EXPECT_EQ(str.size(), 0);

}



TEST_F(AnsiSkippingStringTest_35, ConstructorWithStringLiteral_35) {

    const std::string testString = "Hello, World!";

    AnsiSkippingString str(testString);

    EXPECT_EQ(str.size(), testString.size());

}



TEST_F(AnsiSkippingStringTest_35, ConstructorWithRValueReference_35) {

    std::string testString = "Hello, World!";

    AnsiSkippingString str(std::move(testString));

    EXPECT_EQ(str.size(), 13); // Size after moving should still be correct

}



TEST_F(AnsiSkippingStringTest_35, EmptyStringSizeIsZero_35) {

    const std::string emptyString = "";

    AnsiSkippingString str(emptyString);

    EXPECT_EQ(str.size(), 0);

}



// Assuming preprocessString does not alter the size of the string in a way that is observable

TEST_F(AnsiSkippingStringTest_35, SizeDoesNotChangeAfterBeginAndEnd_35) {

    const std::string testString = "Hello";

    AnsiSkippingString str(testString);

    auto beginIt = str.begin();

    auto endIt = str.end();

    EXPECT_EQ(str.size(), testString.size());

}



TEST_F(AnsiSkippingStringTest_35, SubstringReturnsCorrectLength_35) {

    const std::string testString = "Hello, World!";

    AnsiSkippingString str(testString);

    auto beginIt = str.begin();

    auto endIt = str.end();

    std::string substringResult = str.substring(beginIt, endIt);

    EXPECT_EQ(substringResult.size(), testString.size());

}



TEST_F(AnsiSkippingStringTest_35, SubstringWithIterators_35) {

    const std::string testString = "Hello, World!";

    AnsiSkippingString str(testString);

    auto beginIt = str.begin();

    std::advance(beginIt, 7); // Move iterator to 'W'

    auto endIt = beginIt;

    std::advance(endIt, 5); // Move iterator to the end of "World"

    std::string substringResult = str.substring(beginIt, endIt);

    EXPECT_EQ(substringResult, "World");

}



TEST_F(AnsiSkippingStringTest_35, SubstringWithSameIterator_35) {

    const std::string testString = "Hello";

    AnsiSkippingString str(testString);

    auto it = str.begin();

    std::string substringResult = str.substring(it, it);

    EXPECT_EQ(substringResult, "");

}



TEST_F(AnsiSkippingStringTest_35, SubstringWithInvalidIteratorRange_35) {

    const std::string testString = "Hello";

    AnsiSkippingString str(testString);

    auto beginIt = str.begin();

    auto endIt = str.end();

    std::advance(beginIt, 3); // Move iterator to 'l'

    std::advance(endIt, -1);   // Move iterator to 'o'

    std::string substringResult = str.substring(beginIt, endIt);

    EXPECT_EQ(substringResult, "ll");

}
