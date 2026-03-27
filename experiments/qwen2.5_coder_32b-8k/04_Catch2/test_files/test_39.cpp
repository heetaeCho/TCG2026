#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest_39 : public ::testing::Test {

protected:

    std::string testString = "Sample text for testing";

    Column column; // Assuming Column is properly defined elsewhere

    AnsiSkippingString::const_iterator it;

    AnsiSkippingString::const_iterator endIt;



    void SetUp() override {

        it = AnsiSkippingString::const_iterator(testString);

        endIt = AnsiSkippingString::const_iterator(testString, AnsiSkippingString::const_iterator::EndTag());

    }

};



TEST_F(AnsiSkippingStringTest_39, ConstructorInitialization_39) {

    EXPECT_NE(it.m_string, nullptr);

    EXPECT_EQ(*it.m_string, testString);

    EXPECT_EQ(it.m_it, testString.begin());



    EXPECT_NE(endIt.m_string, nullptr);

    EXPECT_EQ(*endIt.m_string, testString);

    EXPECT_EQ(endIt.m_it, testString.end());

}



TEST_F(AnsiSkippingStringTest_39, PreIncrementOperator_39) {

    auto originalPosition = it.m_it;

    ++it;

    EXPECT_NE(it.m_it, originalPosition);

}



TEST_F(AnsiSkippingStringTest_39, PostIncrementOperator_39) {

    auto originalPosition = it.m_it;

    auto tempIt = it++;

    EXPECT_EQ(tempIt.m_it, originalPosition);

    EXPECT_NE(it.m_it, originalPosition);

}



TEST_F(AnsiSkippingStringTest_39, PreDecrementOperator_39) {

    ++it; // Move to next position

    auto originalPosition = it.m_it;

    --it;

    EXPECT_EQ(it.m_it, testString.begin());

    EXPECT_NE(it.m_it, originalPosition);

}



TEST_F(AnsiSkippingStringTest_39, PostDecrementOperator_39) {

    ++it; // Move to next position

    auto originalPosition = it.m_it;

    auto tempIt = it--;

    EXPECT_EQ(tempIt.m_it, originalPosition);

    EXPECT_NE(it.m_it, originalPosition);

}



TEST_F(AnsiSkippingStringTest_39, DereferenceOperator_String_39) {

    std::string expectedSubstring = "Sample";

    it.m_it = testString.begin();

    EXPECT_EQ((*it).substr(0, 6), expectedSubstring);

}



TEST_F(AnsiSkippingStringTest_39, EqualityOperator_39) {

    EXPECT_TRUE(it == it);

    EXPECT_FALSE(it == endIt);

}



TEST_F(AnsiSkippingStringTest_39, InequalityOperator_39) {

    EXPECT_TRUE(it != endIt);

    EXPECT_FALSE(it != it);

}



TEST_F(AnsiSkippingStringTest_39, LessThanOrEqualToOperator_39) {

    EXPECT_TRUE(it <= it);

    EXPECT_TRUE(it <= endIt);

    EXPECT_FALSE(endIt <= it);

}



TEST_F(AnsiSkippingStringTest_39, OneBeforeMethod_39) {

    ++it;

    auto oneBeforeIt = it.oneBefore();

    EXPECT_EQ(oneBeforeIt.m_it, testString.begin());

}
