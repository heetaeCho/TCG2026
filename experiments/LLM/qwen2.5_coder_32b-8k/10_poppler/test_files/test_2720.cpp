#include <gtest/gtest.h>

#include "./TestProjects/poppler/utils/pdftotext.cc"



// Test fixture for myStringReplace function

class MyStringReplaceTest_2720 : public ::testing::Test {

protected:

    // No additional setup needed for this simple function

};



// Test case to verify normal operation with a single replacement

TEST_F(MyStringReplaceTest_2720, SingleReplacement_2720) {

    std::string result = myStringReplace("hello world", "world", "universe");

    EXPECT_EQ(result, "hello universe");

}



// Test case to verify multiple replacements in the same string

TEST_F(MyStringReplaceTest_2720, MultipleReplacements_2720) {

    std::string result = myStringReplace("banana", "a", "o");

    EXPECT_EQ(result, "bonono");

}



// Test case to verify no replacement when oldToken is not found

TEST_F(MyStringReplaceTest_2720, NoReplacement_2720) {

    std::string result = myStringReplace("apple", "b", "c");

    EXPECT_EQ(result, "apple");

}



// Test case to verify replacement of empty oldToken (should have no effect)

TEST_F(MyStringReplaceTest_2720, EmptyOldToken_2720) {

    std::string result = myStringReplace("apple", "", "b");

    EXPECT_EQ(result, "apple");

}



// Test case to verify replacement with empty newToken (removal of oldToken)

TEST_F(MyStringReplaceTest_2720, EmptyNewToken_2720) {

    std::string result = myStringReplace("banana", "a", "");

    EXPECT_EQ(result, "bnn");

}



// Test case to verify boundary condition with very large string

TEST_F(MyStringReplaceTest_2720, LargeString_2720) {

    std::string largeString(10000, 'a');

    std::string result = myStringReplace(largeString, "aaa", "b");

    EXPECT_EQ(result.size(), 6668); // Expected size after replacements

}



// Test case to verify boundary condition with empty input string

TEST_F(MyStringReplaceTest_2720, EmptyInputString_2720) {

    std::string result = myStringReplace("", "a", "b");

    EXPECT_EQ(result, "");

}
