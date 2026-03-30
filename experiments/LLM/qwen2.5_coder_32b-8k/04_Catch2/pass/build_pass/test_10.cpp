#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;



TEST(StringRefTest_10, DefaultConstructorCreatesEmptyString_10) {

    StringRef str;

    EXPECT_TRUE(str.empty());

    EXPECT_EQ(str.size(), 0);

}



TEST(StringRefTest_10, CharArrayConstructorCreatesValidStringRef_10) {

    const char* rawChars = "Hello";

    StringRef str(rawChars);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), strlen(rawChars));

    EXPECT_STREQ(str.data(), rawChars);

}



TEST(StringRefTest_10, CharArrayAndSizeConstructorCreatesValidStringRef_10) {

    const char* rawChars = "Hello";

    size_t size = 3;

    StringRef str(rawChars, size);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), size);

    EXPECT_STREQ(str.data(), "Hel");

}



TEST(StringRefTest_10, StdStringConstructorCreatesValidStringRef_10) {

    std::string stdStr = "World";

    StringRef str(stdStr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), stdStr.size());

    EXPECT_STREQ(str.data(), stdStr.c_str());

}



TEST(StringRefTest_10, OperatorEqualReturnsTrueForSameContent_10) {

    const char* rawChars = "Hello";

    StringRef str1(rawChars);

    StringRef str2(rawChars);

    EXPECT_TRUE(str1 == str2);

}



TEST(StringRefTest_10, OperatorNotEqualReturnsFalseForSameContent_10) {

    const char* rawChars = "Hello";

    StringRef str1(rawChars);

    StringRef str2(rawChars);

    EXPECT_FALSE(str1 != str2);

}



TEST(StringRefTest_10, OperatorEqualReturnsFalseForDifferentContent_10) {

    StringRef str1("Hello");

    StringRef str2("World");

    EXPECT_FALSE(str1 == str2);

}



TEST(StringRefTest_10, OperatorNotEqualReturnsTrueForDifferentContent_10) {

    StringRef str1("Hello");

    StringRef str2("World");

    EXPECT_TRUE(str1 != str2);

}



TEST(StringRefTest_10, OperatorLessThanWorksCorrectly_10) {

    StringRef str1("Apple");

    StringRef str2("Banana");

    EXPECT_TRUE(str1 < str2);

    EXPECT_FALSE(str2 < str1);

}



TEST(StringRefTest_10, CompareMethodReturnsNegativeForFirstStringSmaller_10) {

    StringRef str1("Apple");

    StringRef str2("Banana");

    EXPECT_LT(str1.compare(str2), 0);

}



TEST(StringRefTest_10, CompareMethodReturnsPositiveForFirstStringLarger_10) {

    StringRef str1("Zebra");

    StringRef str2("Banana");

    EXPECT_GT(str1.compare(str2), 0);

}



TEST(StringRefTest_10, CompareMethodReturnsZeroForEqualStrings_10) {

    StringRef str1("Hello");

    StringRef str2("Hello");

    EXPECT_EQ(str1.compare(str2), 0);

}



TEST(StringRefTest_10, SubstrMethodCreatesValidStringRef_10) {

    StringRef str("HelloWorld");

    StringRef substr = str.substr(5, 5);

    EXPECT_FALSE(substr.empty());

    EXPECT_EQ(substr.size(), 5);

    EXPECT_STREQ(substr.data(), "World");

}



TEST(StringRefTest_10, SubstrMethodHandlesBoundaryConditions_10) {

    StringRef str("Hello");

    StringRef substrStart = str.substr(0, 2);

    EXPECT_FALSE(substrStart.empty());

    EXPECT_EQ(substrStart.size(), 2);

    EXPECT_STREQ(substrStart.data(), "He");



    StringRef substrEnd = str.substr(3, 10); // Length exceeds original size

    EXPECT_FALSE(substrEnd.empty());

    EXPECT_EQ(substrEnd.size(), 2);

    EXPECT_STREQ(substrEnd.data(), "lo");

}



TEST(StringRefTest_10, OperatorIndexAccessReturnsCorrectCharacter_10) {

    StringRef str("Hello");

    EXPECT_EQ(str[0], 'H');

    EXPECT_EQ(str[4], 'o');

}



TEST(StringRefTest_10, EmptyMethodReturnsTrueForEmptyString_10) {

    StringRef str;

    EXPECT_TRUE(str.empty());

}



TEST(StringRefTest_10, EmptyMethodReturnsFalseForNonEmptyString_10) {

    StringRef str("Hello");

    EXPECT_FALSE(str.empty());

}



TEST(StringRefTest_10, SizeMethodReturnsCorrectSize_10) {

    const char* rawChars = "Hello";

    StringRef str(rawChars);

    EXPECT_EQ(str.size(), strlen(rawChars));

}



TEST(StringRefTest_10, DataMethodReturnsPointerToData_10) {

    const char* rawChars = "Hello";

    StringRef str(rawChars);

    EXPECT_STREQ(str.data(), rawChars);

}



TEST(StringRefTest_10, OperatorPlusCreatesNewString_10) {

    StringRef str1("Hello");

    StringRef str2("World");

    std::string result = str1 + str2;

    EXPECT_EQ(result, "HelloWorld");

}



TEST(StringRefTest_10, OperatorPlusEqualsAppendsToString_10) {

    std::string str = "Hello";

    StringRef str2("World");

    str += str2;

    EXPECT_EQ(str, "HelloWorld");

}



TEST(StringRefTest_10, OstreamOperatorOutputsCorrectString_10) {

    StringRef str("Hello");

    testing::internal::CaptureStdout();

    std::cout << str;

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Hello");

}



TEST(StringRefTest_10, ConversionOperatorCreatesStdString_10) {

    StringRef str("Hello");

    std::string result = static_cast<std::string>(str);

    EXPECT_EQ(result, "Hello");

}
