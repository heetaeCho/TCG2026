#include "gtest/gtest.h"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

using namespace Catch;
using namespace Catch::Detail;

// Test normal operation: "default" maps to PlatformDefault
TEST(StringToColourModeTest_689, DefaultReturnsPlatformDefault_689) {
    auto result = stringToColourMode("default");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::PlatformDefault);
}

// Test normal operation: "ansi" maps to ANSI
TEST(StringToColourModeTest_689, AnsiReturnsANSI_689) {
    auto result = stringToColourMode("ansi");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::ANSI);
}

// Test normal operation: "win32" maps to Win32
TEST(StringToColourModeTest_689, Win32ReturnsWin32_689) {
    auto result = stringToColourMode("win32");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::Win32);
}

// Test normal operation: "none" maps to None
TEST(StringToColourModeTest_689, NoneReturnsNone_689) {
    auto result = stringToColourMode("none");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::None);
}

// Test error case: unrecognized string returns empty optional
TEST(StringToColourModeTest_689, UnrecognizedStringReturnsEmpty_689) {
    auto result = stringToColourMode("unknown");
    EXPECT_FALSE(result.has_value());
}

// Test error case: empty string returns empty optional
TEST(StringToColourModeTest_689, EmptyStringReturnsEmpty_689) {
    auto result = stringToColourMode("");
    EXPECT_FALSE(result.has_value());
}

// Test boundary: case sensitivity - "Default" should not match
TEST(StringToColourModeTest_689, CaseSensitiveDefault_689) {
    auto result = stringToColourMode("Default");
    EXPECT_FALSE(result.has_value());
}

// Test boundary: case sensitivity - "ANSI" (uppercase) should not match
TEST(StringToColourModeTest_689, CaseSensitiveANSI_689) {
    auto result = stringToColourMode("ANSI");
    EXPECT_FALSE(result.has_value());
}

// Test boundary: case sensitivity - "Win32" should not match
TEST(StringToColourModeTest_689, CaseSensitiveWin32_689) {
    auto result = stringToColourMode("Win32");
    EXPECT_FALSE(result.has_value());
}

// Test boundary: case sensitivity - "None" should not match
TEST(StringToColourModeTest_689, CaseSensitiveNone_689) {
    auto result = stringToColourMode("None");
    EXPECT_FALSE(result.has_value());
}

// Test boundary: string with leading whitespace
TEST(StringToColourModeTest_689, LeadingWhitespaceReturnsEmpty_689) {
    auto result = stringToColourMode(" default");
    EXPECT_FALSE(result.has_value());
}

// Test boundary: string with trailing whitespace
TEST(StringToColourModeTest_689, TrailingWhitespaceReturnsEmpty_689) {
    auto result = stringToColourMode("default ");
    EXPECT_FALSE(result.has_value());
}

// Test boundary: partial match
TEST(StringToColourModeTest_689, PartialMatchReturnsEmpty_689) {
    auto result = stringToColourMode("def");
    EXPECT_FALSE(result.has_value());
}

// Test boundary: string with extra characters
TEST(StringToColourModeTest_689, ExtraCharactersReturnsEmpty_689) {
    auto result = stringToColourMode("defaults");
    EXPECT_FALSE(result.has_value());
}

// Test with std::string input (StringRef can be constructed from std::string)
TEST(StringToColourModeTest_689, StdStringInputDefault_689) {
    std::string input = "default";
    auto result = stringToColourMode(StringRef(input));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::PlatformDefault);
}

// Test with std::string input for ansi
TEST(StringToColourModeTest_689, StdStringInputAnsi_689) {
    std::string input = "ansi";
    auto result = stringToColourMode(StringRef(input));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::ANSI);
}

// Test random garbage string
TEST(StringToColourModeTest_689, GarbageStringReturnsEmpty_689) {
    auto result = stringToColourMode("xyzzy123!@#");
    EXPECT_FALSE(result.has_value());
}

// Test that the enum values are correct
TEST(StringToColourModeTest_689, EnumValuesAreCorrect_689) {
    EXPECT_EQ(static_cast<int>(*stringToColourMode("default")), 0);
    EXPECT_EQ(static_cast<int>(*stringToColourMode("ansi")), 1);
    EXPECT_EQ(static_cast<int>(*stringToColourMode("win32")), 2);
    EXPECT_EQ(static_cast<int>(*stringToColourMode("none")), 3);
}
