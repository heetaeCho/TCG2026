#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace testing;



class StringRefTest_3 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed.

    }



    void TearDown() override {

        // Teardown code, if needed.

    }

};



TEST_F(StringRefTest_3, DefaultConstructorCreatesEmptyString_3) {

    StringRef str;

    EXPECT_TRUE(str.empty());

    EXPECT_EQ(str.size(), 0u);

}



TEST_F(StringRefTest_3, ConstructorFromCStringCreatesValidStringRef_3) {

    const char* testStr = "Hello";

    StringRef str(testStr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), strlen(testStr));

    EXPECT_EQ(std::string(str), testStr);

}



TEST_F(StringRefTest_3, ConstructorFromStdStringCreatesValidStringRef_3) {

    std::string testStr = "World";

    StringRef str(testStr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), testStr.size());

    EXPECT_EQ(std::string(str), testStr);

}



TEST_F(StringRefTest_3, EmptyStringReturnsTrueForEmptyCheck_3) {

    StringRef emptyStr;

    EXPECT_TRUE(emptyStr.empty());

}



TEST_F(StringRefTest_3, NonEmptyStringReturnsFalseForEmptyCheck_3) {

    const char* testStr = "Hello";

    StringRef str(testStr);

    EXPECT_FALSE(str.empty());

}



TEST_F(StringRefTest_3, SizeReturnsCorrectLength_3) {

    const char* testStr = "SampleText";

    StringRef str(testStr);

    EXPECT_EQ(str.size(), strlen(testStr));

}



TEST_F(StringRefTest_3, SubstrCreatesValidStringRef_3) {

    const char* testStr = "HelloWorld";

    StringRef str(testStr);

    StringRef subStr = str.substr(5, 5);

    EXPECT_EQ(std::string(subStr), "World");

}



TEST_F(StringRefTest_3, DataReturnsPointerToStartOfData_3) {

    const char* testStr = "SampleText";

    StringRef str(testStr);

    EXPECT_EQ(str.data(), testStr);

}



TEST_F(StringRefTest_3, BeginAndEndReturnValidIterators_3) {

    const char* testStr = "TestString";

    StringRef str(testStr);

    std::string constructedStr(str.begin(), str.end());

    EXPECT_EQ(constructedStr, testStr);

}



TEST_F(StringRefTest_3, OperatorLessThanComparesLexicographically_3) {

    StringRef str1("abc");

    StringRef str2("def");

    EXPECT_TRUE(str1 < str2);

    EXPECT_FALSE(str2 < str1);

}



TEST_F(StringRefTest_3, CompareFunctionReturnsNegativeForLesserString_3) {

    StringRef str1("abc");

    StringRef str2("def");

    EXPECT_LT(str1.compare(str2), 0);

}



TEST_F(StringRefTest_3, CompareFunctionReturnsPositiveForGreaterString_3) {

    StringRef str1("xyz");

    StringRef str2("uvw");

    EXPECT_GT(str1.compare(str2), 0);

}



TEST_F(StringRefTest_3, CompareFunctionReturnsZeroForEqualStrings_3) {

    StringRef str1("same");

    StringRef str2("same");

    EXPECT_EQ(str1.compare(str2), 0);

}



TEST_F(StringRefTest_3, OperatorPlusConcatenatesStringRefs_3) {

    StringRef str1("Hello");

    StringRef str2("World");

    std::string concatenated = str1 + str2;

    EXPECT_EQ(concatenated, "HelloWorld");

}



TEST_F(StringRefTest_3, OperatorEqualsComparesStringsForEquality_3) {

    StringRef str1("equal");

    StringRef str2("equal");

    StringRef str3("different");

    EXPECT_TRUE(str1 == str2);

    EXPECT_FALSE(str1 == str3);

}



TEST_F(StringRefTest_3, OperatorNotEqualsComparesStringsForInequality_3) {

    StringRef str1("notEqual");

    StringRef str2("equal");

    EXPECT_TRUE(str1 != str2);

    EXPECT_FALSE(str1 != str1);

}



TEST_F(StringRefTest_3, OperatorBracketAccessesCorrectCharacter_3) {

    StringRef str("Indexing");

    EXPECT_EQ(str[0], 'I');

    EXPECT_EQ(str[7], 'g');

}
