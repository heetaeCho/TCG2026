#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringIteratorTest : public ::testing::Test {

protected:

    const std::string testString = "Hello, World!";

    const Column column; // Assuming Column is default constructible for this test

    AnsiSkippingString::const_iterator it;

    

    void SetUp() override {

        it = AnsiSkippingString::const_iterator(testString);

    }

};



TEST_F(AnsiSkippingStringIteratorTest_41, InitialPositionAtStart_41) {

    EXPECT_EQ(*it, 'H');

}



TEST_F(AnsiSkippingStringIteratorTest_41, IncrementOperatorAdvances_41) {

    ++it;

    EXPECT_EQ(*it, 'e');

}



TEST_F(AnsiSkippingStringIteratorTest_41, PostIncrementOperatorAdvances_41) {

    auto oldIt = it++;

    EXPECT_EQ(*oldIt, 'H');

    EXPECT_EQ(*it, 'e');

}



TEST_F(AnsiSkippingStringIteratorTest_41, DecrementOperatorRetreats_41) {

    ++it;

    --it;

    EXPECT_EQ(*it, 'H');

}



TEST_F(AnsiSkippingStringIteratorTest_41, PostDecrementOperatorRetreats_41) {

    ++it;

    auto oldIt = it--;

    EXPECT_EQ(*oldIt, 'e');

    EXPECT_EQ(*it, 'H');

}



TEST_F(AnsiSkippingStringIteratorTest_41, EqualityOperatorWorks_41) {

    AnsiSkippingString::const_iterator it2(testString);

    EXPECT_TRUE(it == it2);

    ++it;

    EXPECT_FALSE(it == it2);

}



TEST_F(AnsiSkippingStringIteratorTest_41, InequalityOperatorWorks_41) {

    AnsiSkippingString::const_iterator it2(testString);

    EXPECT_FALSE(it != it2);

    ++it;

    EXPECT_TRUE(it != it2);

}



TEST_F(AnsiSkippingStringIteratorTest_41, LessThanOrEqualToOperatorWorks_41) {

    AnsiSkippingString::const_iterator it2(testString);

    EXPECT_TRUE(it <= it2);

    ++it2;

    EXPECT_TRUE(it <= it2);

    --it;

    EXPECT_FALSE(it <= it2);

}



TEST_F(AnsiSkippingStringIteratorTest_41, OneBeforeReturnsPreviousPosition_41) {

    ++it;

    auto oneBeforeIt = it.oneBefore();

    EXPECT_EQ(*oneBeforeIt, 'H');

}
