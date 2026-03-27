#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_stringref.hpp"

#include <string>



using namespace Catch;

using namespace std;



class StringRefTest_6 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    static constexpr const char* testString = "Hello, World!";

};



TEST_F(StringRefTest_6, DefaultConstructorCreatesEmptyStringRef_6) {

    StringRef str;

    EXPECT_TRUE(str.empty());

    EXPECT_EQ(str.size(), 0);

}



TEST_F(StringRefTest_6, CStyleStringConstructorSetsCorrectData_6) {

    StringRef str(testString);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), strlen(testString));

    EXPECT_STREQ(str.data(), testString);

}



TEST_F(StringRefTest_6, CStringAndSizeConstructorSetsCorrectData_6) {

    size_t len = 5;

    StringRef str(testString, len);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), len);

    EXPECT_EQ(memcmp(str.data(), testString, len), 0);

}



TEST_F(StringRefTest_6, StdStringConstructorSetsCorrectData_6) {

    std::string stdStr = "Hello";

    StringRef str(stdStr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), stdStr.size());

    EXPECT_STREQ(str.data(), stdStr.c_str());

}



TEST_F(StringRefTest_6, OperatorBracketReturnsCorrectCharacter_6) {

    StringRef str(testString);

    for (size_t i = 0; i < str.size(); ++i) {

        EXPECT_EQ(str[i], testString[i]);

    }

}



TEST_F(StringRefTest_6, OperatorBracketBoundsChecking_6) {

    StringRef str(testString);

    EXPECT_DEATH({char c = str[str.size()];}, "");

}



TEST_F(StringRefTest_6, EmptyReturnsTrueForEmptyStringRef_6) {

    StringRef str;

    EXPECT_TRUE(str.empty());

}



TEST_F(StringRefTest_6, SizeReturnsCorrectSize_6) {

    StringRef str(testString);

    EXPECT_EQ(str.size(), strlen(testString));

}



TEST_F(StringRefTest_6, SubstrReturnsCorrectSubstring_6) {

    size_t start = 7;

    size_t length = 5;

    StringRef str(testString);

    StringRef substr = str.substr(start, length);

    EXPECT_FALSE(substr.empty());

    EXPECT_EQ(substr.size(), length);

    EXPECT_STREQ(substr.data(), testString + start);

}



TEST_F(StringRefTest_6, SubstrBoundsChecking_6) {

    StringRef str(testString);

    EXPECT_DEATH({StringRef substr = str[str.size() + 1];}, "");

}



TEST_F(StringRefTest_6, CompareFunctionReturnsCorrectResult_6) {

    StringRef str1("abc");

    StringRef str2("def");



    EXPECT_LT(str1.compare(str2), 0);

    EXPECT_GT(str2.compare(str1), 0);

    EXPECT_EQ(str1.compare(str1), 0);

}



TEST_F(StringRefTest_6, LessThanOperatorReturnsCorrectResult_6) {

    StringRef str1("abc");

    StringRef str2("def");



    EXPECT_TRUE(str1 < str2);

    EXPECT_FALSE(str2 < str1);

    EXPECT_FALSE(str1 < str1);

}



TEST_F(StringRefTest_6, EqualityOperatorsReturnCorrectResult_6) {

    StringRef str1("test");

    StringRef str2("test");

    StringRef str3("another");



    EXPECT_TRUE(str1 == str2);

    EXPECT_FALSE(str1 != str2);

    EXPECT_FALSE(str1 == str3);

    EXPECT_TRUE(str1 != str3);

}



TEST_F(StringRefTest_6, OperatorPlusConcatenatesCorrectly_6) {

    StringRef str1("Hello");

    StringRef str2(", World!");

    std::string result = str1 + str2;

    EXPECT_EQ(result, "Hello, World!");

}



TEST_F(StringRefTest_6, OperatorPlusEqualsAppendsCorrectly_6) {

    std::string lhs = "Hello";

    StringRef rhs(", World!");

    lhs += rhs;

    EXPECT_EQ(lhs, "Hello, World!");

}
