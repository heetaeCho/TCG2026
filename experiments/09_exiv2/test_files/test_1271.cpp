#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/utils.cpp"



using namespace Exiv2::Internal;



// Test suite for upper function

class UpperFunctionTest_1271 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



TEST_F(UpperFunctionTest_1271, NormalOperation_1271) {

    std::string input = "hello";

    std::string expected_output = "HELLO";

    EXPECT_EQ(upper(input), expected_output);

}



TEST_F(UpperFunctionTest_1271, EmptyString_1271) {

    std::string input = "";

    std::string expected_output = "";

    EXPECT_EQ(upper(input), expected_output);

}



TEST_F(UpperFunctionTest_1271, AlreadyUpperCase_1271) {

    std::string input = "HELLO";

    std::string expected_output = "HELLO";

    EXPECT_EQ(upper(input), expected_output);

}



TEST_F(UpperFunctionTest_1271, MixedCase_1271) {

    std::string input = "HeLlO";

    std::string expected_output = "HELLO";

    EXPECT_EQ(upper(input), expected_output);

}



TEST_F(UpperFunctionTest_1271, NonAlphabetCharacters_1271) {

    std::string input = "123!@#helloWORLD$%^";

    std::string expected_output = "123!@#HELLOWORLD$%^";

    EXPECT_EQ(upper(input), expected_output);

}



TEST_F(UpperFunctionTest_1271, SingleCharacterLower_1271) {

    std::string input = "a";

    std::string expected_output = "A";

    EXPECT_EQ(upper(input), expected_output);

}



TEST_F(UpperFunctionTest_1271, SingleCharacterUpper_1271) {

    std::string input = "A";

    std::string expected_output = "A";

    EXPECT_EQ(upper(input), expected_output);

}
