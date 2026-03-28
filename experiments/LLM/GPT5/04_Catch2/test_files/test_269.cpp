// File: tests/StringMakerIntConvertTest_269.cpp

#include <gtest/gtest.h>
#include <string>
#include <limits>
#include <cctype>

// Use the header path provided in the prompt.
#include "Catch2/src/catch2/catch_tostring.hpp"

namespace {

bool IsDecimalString(const std::string& s) {
    if (s.empty()) return false;
    size_t i = 0;
    if (s[0] == '-') {
        if (s.size() == 1) return false; // must have digits after '-'
        i = 1;
    }
    for (; i < s.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    return true;
}

} // namespace

// Normal operation: positive integer
TEST(StringMakerIntTest_269, ConvertsPositiveInteger_269) {
    int v = 12345;
    std::string s = Catch::StringMaker<int>::convert(v);
    EXPECT_EQ(s, std::to_string(v));
    EXPECT_FALSE(s.empty());
}

// Normal operation: zero
TEST(StringMakerIntTest_269, ConvertsZero_269) {
    int v = 0;
    std::string s = Catch::StringMaker<int>::convert(v);
    EXPECT_EQ(s, "0");
    EXPECT_TRUE(IsDecimalString(s));
}

// Normal operation: negative integer
TEST(StringMakerIntTest_269, ConvertsNegativeInteger_269) {
    int v = -4567;
    std::string s = Catch::StringMaker<int>::convert(v);
    EXPECT_EQ(s, std::to_string(v));
    EXPECT_TRUE(IsDecimalString(s));
}

// Boundary: INT_MAX
TEST(StringMakerIntTest_269, ConvertsIntMax_269) {
    int v = std::numeric_limits<int>::max();
    std::string s = Catch::StringMaker<int>::convert(v);
    EXPECT_EQ(s, std::to_string(v));
    EXPECT_TRUE(IsDecimalString(s));
}

// Boundary: INT_MIN
TEST(StringMakerIntTest_269, ConvertsIntMin_269) {
    int v = std::numeric_limits<int>::min();
    std::string s = Catch::StringMaker<int>::convert(v);
    EXPECT_EQ(s, std::to_string(v));
    EXPECT_TRUE(IsDecimalString(s));
}

// Property: no leading or trailing whitespace
TEST(StringMakerIntTest_269, NoLeadingOrTrailingWhitespace_269) {
    int values[] = {0, 1, -1, 1024, -2048};
    for (int v : values) {
        std::string s = Catch::StringMaker<int>::convert(v);
        ASSERT_FALSE(s.empty());
        // Check first and last characters are not whitespace
        EXPECT_FALSE(std::isspace(static_cast<unsigned char>(s.front())));
        EXPECT_FALSE(std::isspace(static_cast<unsigned char>(s.back())));
    }
}

// Robustness: multiple consecutive calls should be independent/stateless
TEST(StringMakerIntTest_269, ConsecutiveCallsAreIndependent_269) {
    const int values[] = {0, 42, -42, 123456789, -987654321};
    for (int v : values) {
        std::string s = Catch::StringMaker<int>::convert(v);
        EXPECT_EQ(s, std::to_string(v));
        EXPECT_TRUE(IsDecimalString(s));
    }
}
