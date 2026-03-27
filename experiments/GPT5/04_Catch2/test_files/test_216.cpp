// File: cased_string_tests_216.cpp

#include <gtest/gtest.h>

// Include the provided interfaces (paths as given in the prompt)
#include "Catch2/src/catch2/catch_case_sensitive.hpp"
#include "Catch2/src/catch2/matchers/catch_matchers_string.hpp"

using Catch::CaseSensitive;
using Catch::Matchers::CasedString;

//
// We only test behavior observable via the public interface:
//  - adjustString(const std::string&)
//  - construction effect on public member m_str
// No assumptions are made about any private state.
//

// Normal operation: Case-insensitive -> lowercases input
TEST(CasedStringTest_216, AdjustString_LowersWhenCaseInsensitive_216) {
    CasedString ci("ignored", CaseSensitive::No);
    EXPECT_EQ(ci.adjustString("AbCDeF"), std::string("abcdef"));
}

// Normal operation: Case-sensitive -> preserves input
TEST(CasedStringTest_216, AdjustString_PreservesWhenCaseSensitive_216) {
    CasedString cs("ignored", CaseSensitive::Yes);
    const std::string input = "AbCDeF";
    EXPECT_EQ(cs.adjustString(input), input);
}

// Boundary: empty string
TEST(CasedStringTest_216, AdjustString_EmptyString_216) {
    CasedString ci("ignored", CaseSensitive::No);
    EXPECT_EQ(ci.adjustString(""), std::string(""));
}

// Boundary/neutral: non-alphabetic characters (should be unchanged even when insensitive)
TEST(CasedStringTest_216, AdjustString_NonAlphabeticUnchanged_216) {
    CasedString ci("ignored", CaseSensitive::No);
    const std::string symbols = "12345 !@#$_-+=[](){}.,;:/?";
    EXPECT_EQ(ci.adjustString(symbols), symbols);
}

// Constructor effect: stored string is adjusted when case-insensitive
TEST(CasedStringTest_216, Ctor_StoresAdjustedString_WhenCaseInsensitive_216) {
    CasedString ci("HeLLo", CaseSensitive::No);
    EXPECT_EQ(ci.m_str, std::string("hello"));
}

// Constructor effect: stored string is preserved when case-sensitive
TEST(CasedStringTest_216, Ctor_StoresOriginalString_WhenCaseSensitive_216) {
    const std::string original = "HeLLo";
    CasedString cs(original, CaseSensitive::Yes);
    EXPECT_EQ(cs.m_str, original);
}
