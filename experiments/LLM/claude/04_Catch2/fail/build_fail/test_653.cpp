#include <gtest/gtest.h>
#include <string>

// Include the necessary headers
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// Test: convertInto with a normal string copies source to target
TEST(ConvertIntoTest_653, NormalStringCopiedToTarget_653) {
    std::string source = "hello world";
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_EQ(target, "hello world");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultBase::Ok);
}

// Test: convertInto returns Matched parse result type
TEST(ConvertIntoTest_653, ReturnsMatchedResult_653) {
    std::string source = "test";
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto with empty string
TEST(ConvertIntoTest_653, EmptyStringCopiedToTarget_653) {
    std::string source = "";
    std::string target = "previous value";
    auto result = convertInto(source, target);
    EXPECT_EQ(target, "");
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto with string containing spaces
TEST(ConvertIntoTest_653, StringWithSpaces_653) {
    std::string source = "  spaces everywhere  ";
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_EQ(target, "  spaces everywhere  ");
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto with string containing special characters
TEST(ConvertIntoTest_653, StringWithSpecialCharacters_653) {
    std::string source = "!@#$%^&*()_+-=[]{}|;':\",./<>?";
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_EQ(target, source);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto with string containing newlines and tabs
TEST(ConvertIntoTest_653, StringWithWhitespaceCharacters_653) {
    std::string source = "line1\nline2\ttab";
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_EQ(target, source);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto overwrites existing target value
TEST(ConvertIntoTest_653, OverwritesExistingTargetValue_653) {
    std::string source = "new value";
    std::string target = "old value";
    auto result = convertInto(source, target);
    EXPECT_EQ(target, "new value");
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto with a very long string
TEST(ConvertIntoTest_653, VeryLongString_653) {
    std::string source(10000, 'a');
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_EQ(target, source);
    EXPECT_EQ(target.size(), 10000u);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto with string containing null characters embedded
TEST(ConvertIntoTest_653, StringWithEmbeddedNullCharacters_653) {
    std::string source("hello\0world", 11);
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_EQ(target, source);
    EXPECT_EQ(target.size(), 11u);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto with single character string
TEST(ConvertIntoTest_653, SingleCharacterString_653) {
    std::string source = "x";
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_EQ(target, "x");
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: convertInto result has no error message (since it's ok)
TEST(ConvertIntoTest_653, ResultHasNoErrorMessage_653) {
    std::string source = "test";
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test: ParseResultType enum values
TEST(ParseResultTypeTest_653, EnumValues_653) {
    EXPECT_EQ(static_cast<int>(ParseResultType::Matched), 0);
    EXPECT_EQ(static_cast<int>(ParseResultType::NoMatch), 1);
    EXPECT_EQ(static_cast<int>(ParseResultType::ShortCircuitAll), 2);
    EXPECT_EQ(static_cast<int>(ParseResultType::ShortCircuitSame), 3);
}

// Test: convertInto with Unicode characters in UTF-8
TEST(ConvertIntoTest_653, UnicodeString_653) {
    std::string source = u8"こんにちは世界";
    std::string target;
    auto result = convertInto(source, target);
    EXPECT_EQ(target, source);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: Multiple consecutive calls to convertInto
TEST(ConvertIntoTest_653, MultipleConsecutiveCalls_653) {
    std::string target;
    
    auto result1 = convertInto(std::string("first"), target);
    EXPECT_EQ(target, "first");
    EXPECT_TRUE(static_cast<bool>(result1));
    
    auto result2 = convertInto(std::string("second"), target);
    EXPECT_EQ(target, "second");
    EXPECT_TRUE(static_cast<bool>(result2));
    
    auto result3 = convertInto(std::string(""), target);
    EXPECT_EQ(target, "");
    EXPECT_TRUE(static_cast<bool>(result3));
}
