#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_string_manip.cpp"



using namespace Catch;



// Test Fixture for toLower function

class ToLowerTest_590 : public ::testing::Test {

protected:

    // No additional setup needed for this test fixture

};



// Test normal operation with a mixed case string

TEST_F(ToLowerTest_590, ConvertsMixedCaseStringToLowerCase_590) {

    std::string input = "HelloWorld";

    std::string expectedOutput = "helloworld";

    EXPECT_EQ(toLower(input), expectedOutput);

}



// Test normal operation with an already lower case string

TEST_F(ToLowerTest_590, LeavesLowerCaseStringUnchanged_590) {

    std::string input = "helloworld";

    std::string expectedOutput = "helloworld";

    EXPECT_EQ(toLower(input), expectedOutput);

}



// Test normal operation with an upper case string

TEST_F(ToLowerTest_590, ConvertsUpperCaseStringToLowerCase_590) {

    std::string input = "HELLOWORLD";

    std::string expectedOutput = "helloworld";

    EXPECT_EQ(toLower(input), expectedOutput);

}



// Test boundary condition with an empty string

TEST_F(ToLowerTest_590, HandlesEmptyStringCorrectly_590) {

    std::string input = "";

    std::string expectedOutput = "";

    EXPECT_EQ(toLower(input), expectedOutput);

}



// Test boundary condition with a single character (lower case)

TEST_F(ToLowerTest_590, ConvertsSingleLowerCaseCharacterToLowerCase_590) {

    std::string input = "a";

    std::string expectedOutput = "a";

    EXPECT_EQ(toLower(input), expectedOutput);

}



// Test boundary condition with a single character (upper case)

TEST_F(ToLowerTest_590, ConvertsSingleUpperCaseCharacterToLowerCase_590) {

    std::string input = "A";

    std::string expectedOutput = "a";

    EXPECT_EQ(toLower(input), expectedOutput);

}



// Test exceptional or error cases with non-alphabetic characters

TEST_F(ToLowerTest_590, LeavesNonAlphabeticCharactersUnchanged_590) {

    std::string input = "1234!@#$%^&*()";

    std::string expectedOutput = "1234!@#$%^&*()";

    EXPECT_EQ(toLower(input), expectedOutput);

}



// Test exceptional or error cases with spaces

TEST_F(ToLowerTest_590, LeavesSpacesUnchanged_590) {

    std::string input = "Hello World";

    std::string expectedOutput = "hello world";

    EXPECT_EQ(toLower(input), expectedOutput);

}
