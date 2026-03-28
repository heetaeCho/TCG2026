#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Since the provided code shows a static function symbol() in the Catch namespace
// that returns 'm', we test that behavior.

namespace {

// Test that symbol() returns the expected character 'm'
TEST(CatchSymbolTest_99, ReturnsCorrectSymbol_99) {
    char result = Catch::symbol();
    EXPECT_EQ(result, 'm');
}

// Test that the return type is char (implicitly tested by assignment)
TEST(CatchSymbolTest_99, ReturnTypeIsChar_99) {
    auto result = Catch::symbol();
    static_assert(std::is_same<decltype(result), char>::value, 
                  "symbol() should return char");
    EXPECT_EQ(result, 'm');
}

// Test that calling symbol() multiple times returns the same value (consistency)
TEST(CatchSymbolTest_99, ConsistentReturnValue_99) {
    char first = Catch::symbol();
    char second = Catch::symbol();
    char third = Catch::symbol();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// Test that the returned value is not null character
TEST(CatchSymbolTest_99, ReturnValueIsNotNull_99) {
    char result = Catch::symbol();
    EXPECT_NE(result, '\0');
}

// Test that the returned value is a lowercase letter
TEST(CatchSymbolTest_99, ReturnValueIsLowercaseLetter_99) {
    char result = Catch::symbol();
    EXPECT_GE(result, 'a');
    EXPECT_LE(result, 'z');
}

// Test that the returned character is printable
TEST(CatchSymbolTest_99, ReturnValueIsPrintable_99) {
    char result = Catch::symbol();
    EXPECT_TRUE(std::isprint(static_cast<unsigned char>(result)));
}

// Test the specific expected value boundary
TEST(CatchSymbolTest_99, ExactValueCheck_99) {
    char result = Catch::symbol();
    EXPECT_EQ(static_cast<int>(result), static_cast<int>('m'));
}

}  // namespace
