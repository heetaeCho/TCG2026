#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"

#include <string>



using namespace Catch;



TEST(StringRefTest_5, DefaultConstructorCreatesEmptyStringRef_5) {

    StringRef strRef;

    EXPECT_TRUE(strRef.empty());

    EXPECT_EQ(strRef.size(), 0);

}



TEST(StringRefTest_5, ConstructorWithCStringSetsCorrectValues_5) {

    const char* testString = "Hello";

    StringRef strRef(testString);

    EXPECT_FALSE(strRef.empty());

    EXPECT_EQ(strRef.size(), std::strlen(testString));

    EXPECT_STREQ(strRef.data(), testString);

}



TEST(StringRefTest_5, ConstructorWithCStringAndSizeSetsCorrectValues_5) {

    const char* testString = "Hello";

    size_t size = 3;

    StringRef strRef(testString, size);

    EXPECT_FALSE(strRef.empty());

    EXPECT_EQ(strRef.size(), size);

    EXPECT_STREQ(strRef.data(), "Hel");

}



TEST(StringRefTest_5, ConstructorWithStdStringSetsCorrectValues_5) {

    std::string testString = "World";

    StringRef strRef(testString);

    EXPECT_FALSE(strRef.empty());

    EXPECT_EQ(strRef.size(), testString.size());

    EXPECT_STREQ(strRef.data(), testString.c_str());

}



TEST(StringRefTest_5, SubstrReturnsCorrectStringRef_5) {

    const char* testString = "HelloWorld";

    StringRef strRef(testString);

    StringRef subStr = strRef.substr(5, 5);

    EXPECT_FALSE(subStr.empty());

    EXPECT_EQ(subStr.size(), 5);

    EXPECT_STREQ(subStr.data(), "World");

}



TEST(StringRefTest_5, SubstrWithInvalidSizeReturnsEmptyStringRef_5) {

    const char* testString = "Hello";

    StringRef strRef(testString);

    StringRef subStr = strRef.substr(0, 10); // Requesting more characters than available

    EXPECT_TRUE(subStr.empty());

    EXPECT_EQ(subStr.size(), 0);

}



TEST(StringRefTest_5, CompareOperatorReturnsZeroForEqualStrings_5) {

    const char* testString1 = "Hello";

    const char* testString2 = "Hello";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_EQ(strRef1.compare(strRef2), 0);

}



TEST(StringRefTest_5, CompareOperatorReturnsNegativeForLesserString_5) {

    const char* testString1 = "Apple";

    const char* testString2 = "Banana";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_LT(strRef1.compare(strRef2), 0);

}



TEST(StringRefTest_5, CompareOperatorReturnsPositiveForGreaterString_5) {

    const char* testString1 = "Banana";

    const char* testString2 = "Apple";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_GT(strRef1.compare(strRef2), 0);

}



TEST(StringRefTest_5, EqualityOperatorReturnsTrueForEqualStrings_5) {

    const char* testString1 = "Hello";

    const char* testString2 = "Hello";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_TRUE(strRef1 == strRef2);

}



TEST(StringRefTest_5, EqualityOperatorReturnsFalseForDifferentStrings_5) {

    const char* testString1 = "Hello";

    const char* testString2 = "World";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_FALSE(strRef1 == strRef2);

}



TEST(StringRefTest_5, InequalityOperatorReturnsTrueForDifferentStrings_5) {

    const char* testString1 = "Hello";

    const char* testString2 = "World";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_TRUE(strRef1 != strRef2);

}



TEST(StringRefTest_5, InequalityOperatorReturnsFalseForEqualStrings_5) {

    const char* testString1 = "Hello";

    const char* testString2 = "Hello";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_FALSE(strRef1 != strRef2);

}



TEST(StringRefTest_5, LessThanOperatorReturnsTrueForLesserString_5) {

    const char* testString1 = "Apple";

    const char* testString2 = "Banana";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_TRUE(strRef1 < strRef2);

}



TEST(StringRefTest_5, LessThanOperatorReturnsFalseForGreaterString_5) {

    const char* testString1 = "Banana";

    const char* testString2 = "Apple";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    EXPECT_FALSE(strRef1 < strRef2);

}



TEST(StringRefTest_5, OperatorPlusConcatenatesStrings_5) {

    const char* testString1 = "Hello";

    const char* testString2 = "World";

    StringRef strRef1(testString1);

    StringRef strRef2(testString2);

    std::string result = strRef1 + strRef2;

    EXPECT_EQ(result, "HelloWorld");

}



TEST(StringRefTest_5, OperatorPlusEqualsAppendsStrings_5) {

    const char* testString1 = "Hello";

    const char* testString2 = "World";

    StringRef strRef2(testString2);

    std::string result(testString1);

    result += strRef2;

    EXPECT_EQ(result, "HelloWorld");

}



TEST(StringRefTest_5, OperatorStreamInsertionOutputsStringRefContent_5) {

    const char* testString = "Hello";

    StringRef strRef(testString);

    std::ostringstream oss;

    oss << strRef;

    EXPECT_EQ(oss.str(), "Hello");

}
