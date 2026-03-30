#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest_611 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(AnsiSkippingStringTest_611, ConstructorFromStringLiteral_611) {

    AnsiSkippingString str("Hello, World!");

    EXPECT_EQ(str.size(), 13);

}



TEST_F(AnsiSkippingStringTest_611, ConstructorFromRValueString_611) {

    std::string text = "Hello, World!";

    AnsiSkippingString str(std::move(text));

    EXPECT_EQ(str.size(), 13);

}



TEST_F(AnsiSkippingStringTest_611, EmptyStringConstructor_611) {

    AnsiSkippingString str("");

    EXPECT_EQ(str.size(), 0);

}



TEST_F(AnsiSkippingStringTest_611, BeginAndEndIterators_611) {

    AnsiSkippingString str("Hello");

    auto begin = str.begin();

    auto end = str.end();

    EXPECT_NE(begin, end);



    size_t count = 0;

    for (auto it = begin; it != end; ++it) {

        ++count;

    }

    EXPECT_EQ(count, 5);

}



TEST_F(AnsiSkippingStringTest_611, SubstringFromIterators_611) {

    AnsiSkippingString str("Hello, World!");

    auto begin = str.begin();

    std::advance(begin, 7); // Move to 'W'

    auto end = str.end();

    std::advance(end, -6); // Move to '!'

    

    EXPECT_EQ(str.substring(begin, end), "World");

}



TEST_F(AnsiSkippingStringTest_611, SubstringFullString_611) {

    AnsiSkippingString str("Hello, World!");

    auto begin = str.begin();

    auto end = str.end();

    EXPECT_EQ(str.substring(begin, end), "Hello, World!");

}



TEST_F(AnsiSkippingStringTest_611, SubstringBoundaryConditions_611) {

    AnsiSkippingString str("Hello");

    auto begin = str.begin();

    auto end = str.begin(); // Empty substring

    EXPECT_EQ(str.substring(begin, end), "");



    std::advance(end, 5); // Full string

    EXPECT_EQ(str.substring(begin, end), "Hello");



    std::advance(begin, 1);

    std::advance(end, 1); // Out of bounds end, should still work

    EXPECT_EQ(str.substring(begin, end), "");

}
