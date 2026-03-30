#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_stringref.hpp"

#include <string>



using namespace Catch;



TEST(StringRefTest_681, CompareEqualStrings_681) {

    StringRef str1("hello");

    StringRef str2("hello");

    EXPECT_EQ(str1.compare(str2), 0);

}



TEST(StringRefTest_681, CompareLessThanStrings_681) {

    StringRef str1("abc");

    StringRef str2("abcd");

    EXPECT_EQ(str1.compare(str2), -1);

}



TEST(StringRefTest_681, CompareGreaterThanStrings_681) {

    StringRef str1("abcd");

    StringRef str2("abc");

    EXPECT_EQ(str1.compare(str2), 1);

}



TEST(StringRefTest_681, OperatorLessThanTrue_681) {

    StringRef str1("abc");

    StringRef str2("abcd");

    EXPECT_TRUE(str1 < str2);

}



TEST(StringRefTest_681, OperatorLessThanFalse_681) {

    StringRef str1("abcd");

    StringRef str2("abc");

    EXPECT_FALSE(str1 < str2);

}



TEST(StringRefTest_681, OperatorEqualTrue_681) {

    StringRef str1("hello");

    StringRef str2("hello");

    EXPECT_TRUE(str1 == str2);

}



TEST(StringRefTest_681, OperatorNotEqualFalse_681) {

    StringRef str1("hello");

    StringRef str2("hello");

    EXPECT_FALSE(str1 != str2);

}



TEST(StringRefTest_681, OperatorEqualFalse_681) {

    StringRef str1("hello");

    StringRef str2("world");

    EXPECT_FALSE(str1 == str2);

}



TEST(StringRefTest_681, OperatorNotEqualTrue_681) {

    StringRef str1("hello");

    StringRef str2("world");

    EXPECT_TRUE(str1 != str2);

}



TEST(StringRefTest_681, SubstrBoundaryStart_681) {

    StringRef str("hello");

    StringRef substr = str.substr(0, 3);

    EXPECT_EQ(std::string(substr), "hel");

}



TEST(StringRefTest_681, SubstrBoundaryEnd_681) {

    StringRef str("hello");

    StringRef substr = str.substr(2, 3);

    EXPECT_EQ(std::string(substr), "llo");

}



TEST(StringRefTest_681, SubstrFullString_681) {

    StringRef str("hello");

    StringRef substr = str.substr(0, 5);

    EXPECT_EQ(std::string(substr), "hello");

}



TEST(StringRefTest_681, EmptyStringCheckTrue_681) {

    StringRef str;

    EXPECT_TRUE(str.empty());

}



TEST(StringRefTest_681, EmptyStringCheckFalse_681) {

    StringRef str("hello");

    EXPECT_FALSE(str.empty());

}



TEST(StringRefTest_681, SizeOfString_681) {

    StringRef str("hello");

    EXPECT_EQ(str.size(), 5);

}



TEST(StringRefTest_681, DataPointerCheck_681) {

    const char* rawChars = "hello";

    StringRef str(rawChars);

    EXPECT_EQ(str.data(), rawChars);

}



TEST(StringRefTest_681, ConstexprConstructorCheck_681) {

    constexpr StringRef str("hello", 5);

    static_assert(std::string_view(str.data(), str.size()) == "hello", "Constexpr constructor failed");

}



TEST(StringRefTest_681, StdStringConstructorCheck_681) {

    std::string stdStr = "hello";

    StringRef str(stdStr);

    EXPECT_EQ(std::string(str), stdStr);

}



TEST(StringRefTest_681, OperatorPlusConcatenateStrings_681) {

    StringRef str1("hello");

    StringRef str2("world");

    EXPECT_EQ(std::string(str1 + str2), "helloworld");

}



TEST(StringRefTest_681, OperatorPlusEmptyString_681) {

    StringRef str1("hello");

    StringRef str2("");

    EXPECT_EQ(std::string(str1 + str2), "hello");

}
