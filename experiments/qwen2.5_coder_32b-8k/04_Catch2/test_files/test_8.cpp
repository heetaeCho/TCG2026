#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"

#include <string>



using namespace Catch;

using ::testing::Eq;



class StringRefTest_8 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(StringRefTest_8, DefaultConstructorCreatesEmptyString_8) {

    StringRef str;

    EXPECT_TRUE(str.empty());

    EXPECT_EQ(str.size(), 0);

}



TEST_F(StringRefTest_8, ConstructorWithCStringSetsCorrectSizeAndData_8) {

    const char* cstr = "hello";

    StringRef str(cstr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), strlen(cstr));

    EXPECT_STREQ(str.data(), cstr);

}



TEST_F(StringRefTest_8, ConstructorWithStringLiteralSetsCorrectSizeAndData_8) {

    StringRef str("world");

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), 5);

    EXPECT_STREQ(str.data(), "world");

}



TEST_F(StringRefTest_8, ConstructorWithStdStringSetsCorrectSizeAndData_8) {

    std::string stdstr = "example";

    StringRef str(stdstr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), stdstr.size());

    EXPECT_STREQ(str.data(), stdstr.c_str());

}



TEST_F(StringRefTest_8, SubstringFromStartCreatesCorrectStringRef_8) {

    StringRef str("substring");

    StringRef substr = str.substr(0, 5);

    EXPECT_FALSE(substr.empty());

    EXPECT_EQ(substr.size(), 5);

    EXPECT_STREQ(substr.data(), "subsr");

}



TEST_F(StringRefTest_8, SubstringFromMiddleCreatesCorrectStringRef_8) {

    StringRef str("substring");

    StringRef substr = str.substr(3, 4);

    EXPECT_FALSE(substr.empty());

    EXPECT_EQ(substr.size(), 4);

    EXPECT_STREQ(substr.data(), "strin");

}



TEST_F(StringRefTest_8, SubstringFromEndCreatesCorrectStringRef_8) {

    StringRef str("substring");

    StringRef substr = str.substr(5, 4);

    EXPECT_FALSE(substr.empty());

    EXPECT_EQ(substr.size(), 4);

    EXPECT_STREQ(substr.data(), "ring");

}



TEST_F(StringRefTest_8, SubstringWithLengthZeroCreatesEmptyStringRef_8) {

    StringRef str("substring");

    StringRef substr = str.substr(5, 0);

    EXPECT_TRUE(substr.empty());

    EXPECT_EQ(substr.size(), 0);

}



TEST_F(StringRefTest_8, EmptyStringComparisonReturnsTrue_8) {

    StringRef str1;

    StringRef str2;

    EXPECT_TRUE(str1 == str2);

}



TEST_F(StringRefTest_8, NonEmptyStringComparisonReturnsFalseForDifferentStrings_8) {

    StringRef str1("hello");

    StringRef str2("world");

    EXPECT_FALSE(str1 == str2);

}



TEST_F(StringRefTest_8, NonEmptyStringComparisonReturnsTrueForSameStrings_8) {

    StringRef str1("hello");

    StringRef str2("hello");

    EXPECT_TRUE(str1 == str2);

}



TEST_F(StringRefTest_8, LessThanOperatorWorksForDifferentStrings_8) {

    StringRef str1("abc");

    StringRef str2("def");

    EXPECT_TRUE(str1 < str2);

}



TEST_F(StringRefTest_8, LessThanOperatorReturnsFalseForSameStrings_8) {

    StringRef str1("abc");

    StringRef str2("abc");

    EXPECT_FALSE(str1 < str2);

}



TEST_F(StringRefTest_8, CompareMethodReturnsNegativeForLesserString_8) {

    StringRef str1("abc");

    StringRef str2("def");

    EXPECT_LT(str1.compare(str2), 0);

}



TEST_F(StringRefTest_8, CompareMethodReturnsPositiveForGreaterString_8) {

    StringRef str1("def");

    StringRef str2("abc");

    EXPECT_GT(str1.compare(str2), 0);

}



TEST_F(StringRefTest_8, CompareMethodReturnsZeroForSameStrings_8) {

    StringRef str1("abc");

    StringRef str2("abc");

    EXPECT_EQ(str1.compare(str2), 0);

}



TEST_F(StringRefTest_8, IndexOperatorAccessesCorrectCharacter_8) {

    StringRef str("example");

    EXPECT_EQ(str[0], 'e');

    EXPECT_EQ(str[3], 'a');

    EXPECT_EQ(str[6], 'e');

}



TEST_F(StringRefTest_8, EmptyStringRefIteratorComparison_8) {

    StringRef str;

    auto it = str.begin();

    EXPECT_TRUE(it == str.end());

}



TEST_F(StringRefTest_8, NonEmptyStringRefIteratorTraversal_8) {

    StringRef str("test");

    auto it = str.begin();

    EXPECT_EQ(*it++, 't');

    EXPECT_EQ(*it++, 'e');

    EXPECT_EQ(*it++, 's');

    EXPECT_EQ(*it++, 't');

    EXPECT_TRUE(it == str.end());

}
