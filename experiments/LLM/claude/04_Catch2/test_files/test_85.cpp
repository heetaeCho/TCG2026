#include <gtest/gtest.h>
#include <string>
#include <cstddef>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Test fixture for the Catch::convert function with nullptr_t
class CatchToStringTest_85 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that converting nullptr returns the string "nullptr"
TEST_F(CatchToStringTest_85, ConvertNullptrReturnsNullptrString_85) {
    std::string result = Catch::convert(nullptr);
    EXPECT_EQ(result, "nullptr");
}

// Test that the result is not empty
TEST_F(CatchToStringTest_85, ConvertNullptrReturnsNonEmptyString_85) {
    std::string result = Catch::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

// Test that the result has the expected length
TEST_F(CatchToStringTest_85, ConvertNullptrReturnsCorrectLength_85) {
    std::string result = Catch::convert(nullptr);
    EXPECT_EQ(result.length(), 7u); // "nullptr" has 7 characters
}

// Test that converting nullptr_t type explicitly works
TEST_F(CatchToStringTest_85, ConvertNullptrTExplicitType_85) {
    std::nullptr_t np = nullptr;
    std::string result = Catch::convert(np);
    EXPECT_EQ(result, "nullptr");
}

// Test consistency - calling multiple times yields the same result
TEST_F(CatchToStringTest_85, ConvertNullptrIsConsistent_85) {
    std::string result1 = Catch::convert(nullptr);
    std::string result2 = Catch::convert(nullptr);
    EXPECT_EQ(result1, result2);
}

// Test that the returned string is exactly "nullptr" with no extra whitespace or characters
TEST_F(CatchToStringTest_85, ConvertNullptrExactMatch_85) {
    std::string result = Catch::convert(nullptr);
    EXPECT_STREQ(result.c_str(), "nullptr");
}

// Test that the result does not contain unexpected substrings
TEST_F(CatchToStringTest_85, ConvertNullptrDoesNotContainNull_85) {
    std::string result = Catch::convert(nullptr);
    // It should be exactly "nullptr", not "null" or "NULL" or "0"
    EXPECT_NE(result, "null");
    EXPECT_NE(result, "NULL");
    EXPECT_NE(result, "0");
    EXPECT_NE(result, "NULLPTR");
}
