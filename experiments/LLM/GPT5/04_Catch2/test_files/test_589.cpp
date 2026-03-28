// tolowerinplace_tests_589.cpp
#include <gtest/gtest.h>
#include <string>

// Forward declaration from the provided interface
namespace Catch {
    void toLowerInPlace(std::string& s);
}

namespace {

// Verifies that basic uppercase ASCII letters are converted to lowercase.
TEST(ToLowerInPlaceTest_589, ConvertsUppercaseASCII_589) {
    std::string s = "ABCDEF";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "abcdef");
}

// Verifies mixed content: letters are lowercased, digits and punctuation unchanged.
TEST(ToLowerInPlaceTest_589, MixedCaseDigitsPunct_589) {
    std::string s = "AbC123!?-.";
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, "abc123!?-.");
}

// Verifies that an empty string remains unchanged (in-place no-op).
TEST(ToLowerInPlaceTest_589, EmptyStringNoChange_589) {
    std::string s;
    Catch::toLowerInPlace(s);
    EXPECT_TRUE(s.empty());
}

// Verifies that already-lowercase ASCII stays the same.
TEST(ToLowerInPlaceTest_589, AlreadyLowercaseUnaffected_589) {
    std::string s = "already lowercase";
    std::string original = s;
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, original);
}

// Verifies that non-ASCII UTF-8 bytes are not transformed (black-box expectation:
// function iterates over bytes and lowercases ASCII letters only).
TEST(ToLowerInPlaceTest_589, NonAsciiUtf8Preserved_589) {
    // "Ångström café" contains multi-byte UTF-8 characters.
    std::string s = u8"Ångström café";
    std::string original = s;
    Catch::toLowerInPlace(s);
    // Expect ASCII letters to be lowercased, non-ASCII bytes preserved.
    // Only 'N','G','S','T','R','M',' ' and 'C','A','F','E' might change if they are ASCII;
    // but the string already uses lowercase ASCII where present.
    EXPECT_EQ(s, original);
}

// Verifies idempotence: running twice yields same result after first application.
TEST(ToLowerInPlaceTest_589, IdempotentOnSecondCall_589) {
    std::string s = "HeLLo WoRLD!";
    Catch::toLowerInPlace(s);
    std::string once = s;
    Catch::toLowerInPlace(s);
    EXPECT_EQ(s, once);
}

} // namespace
