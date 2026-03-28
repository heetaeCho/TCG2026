#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;



TEST(StringRefTest_12, DefaultConstructorCreatesEmptyString_12) {

    StringRef str;

    EXPECT_TRUE(str.empty());

    EXPECT_EQ(str.size(), 0);

}



TEST(StringRefTest_12, CharArrayConstructorInitializesCorrectly_12) {

    const char* rawChars = "Hello";

    StringRef str(rawChars);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), 5);

    EXPECT_STREQ(str.data(), rawChars);

}



TEST(StringRefTest_12, CharArrayAndSizeConstructorInitializesCorrectly_12) {

    const char* rawChars = "Hello";

    size_t size = 3;

    StringRef str(rawChars, size);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), size);

    EXPECT_STREQ(std::string(str.data(), str.size()).c_str(), "Hel");

}



TEST(StringRefTest_12, StdStringConstructorInitializesCorrectly_12) {

    std::string stdStr = "World";

    StringRef str(stdStr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), 5);

    EXPECT_STREQ(str.data(), stdStr.c_str());

}



TEST(StringRefTest_12, OperatorEqualComparesIdenticalStrings_12) {

    StringRef str1("Hello");

    StringRef str2("Hello");

    EXPECT_TRUE(str1 == str2);

}



TEST(StringRefTest_12, OperatorNotEqualComparesDifferentStrings_12) {

    StringRef str1("Hello");

    StringRef str2("World");

    EXPECT_TRUE(str1 != str2);

}



TEST(StringRefTest_12, OperatorLessThanComparesLexicographically_12) {

    StringRef str1("Apple");

    StringRef str2("Banana");

    EXPECT_TRUE(str1 < str2);

}



TEST(StringRefTest_12, CompareFunctionReturnsZeroForEqualStrings_12) {

    StringRef str1("Hello");

    StringRef str2("Hello");

    EXPECT_EQ(str1.compare(str2), 0);

}



TEST(StringRefTest_12, CompareFunctionReturnsNegativeForSmallerString_12) {

    StringRef str1("Apple");

    StringRef str2("Banana");

    EXPECT_LT(str1.compare(str2), 0);

}



TEST(StringRefTest_12, CompareFunctionReturnsPositiveForLargerString_12) {

    StringRef str1("Cherry");

    StringRef str2("Banana");

    EXPECT_GT(str1.compare(str2), 0);

}



TEST(StringRefTest_12, SubstrCreatesCorrectSubstring_12) {

    StringRef str("HelloWorld");

    StringRef substr = str.substr(5, 5);

    EXPECT_EQ(substr.size(), 5);

    EXPECT_STREQ(substr.data(), "World");

}



TEST(StringRefTest_12, EmptyStringHasZeroSizeAndTrueEmpty_12) {

    StringRef str;

    EXPECT_TRUE(str.empty());

    EXPECT_EQ(str.size(), 0);

}



TEST(StringRefTest_12, NonEmptyStringHasNonZeroSizeAndFalseEmpty_12) {

    StringRef str("Test");

    EXPECT_FALSE(str.empty());

    EXPECT_NE(str.size(), 0);

}



TEST(StringRefTest_12, OperatorArrayAccessesCorrectCharacter_12) {

    StringRef str("Hello");

    EXPECT_EQ(str[0], 'H');

    EXPECT_EQ(str[4], 'o');

}



TEST(StringRefTest_12, BeginAndEndProvideValidIterators_12) {

    StringRef str("Test");

    auto it = str.begin();

    auto endIt = str.end();

    for (int i = 0; i < static_cast<int>(str.size()); ++i) {

        EXPECT_EQ(*it, str[i]);

        ++it;

    }

    EXPECT_EQ(it, endIt);

}
