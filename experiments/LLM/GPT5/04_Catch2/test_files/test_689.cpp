// File: tests/string_to_colour_mode_689_tests.cpp

#include <gtest/gtest.h>

// Public interfaces only (treat implementation as a black box)
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// Optional is part of Catch's public interface in Detail namespace.
// We include Catch's optional header to avoid relying on assumptions.
#include "catch2/internal/catch_optional.hpp"

// The function under test is implemented in a .cpp, so we forward-declare
// its signature here to call it without including the .cpp itself.
namespace Catch {
namespace Detail {
    Optional<ColourMode> stringToColourMode( StringRef colourMode );
} // namespace Detail
} // namespace Catch

using Catch::StringRef;
using Catch::ColourMode;

class StringToColourModeTest_689 : public ::testing::Test {};

// ----- Normal operation: exact matches -----

TEST_F(StringToColourModeTest_689, ParsesDefault_689) {
    auto result = Catch::Detail::stringToColourMode(StringRef("default"));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::PlatformDefault);
}

TEST_F(StringToColourModeTest_689, ParsesAnsi_689) {
    auto result = Catch::Detail::stringToColourMode(StringRef("ansi"));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::ANSI);
}

TEST_F(StringToColourModeTest_689, ParsesWin32_689) {
    auto result = Catch::Detail::stringToColourMode(StringRef("win32"));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::Win32);
}

TEST_F(StringToColourModeTest_689, ParsesNone_689) {
    auto result = Catch::Detail::stringToColourMode(StringRef("none"));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, ColourMode::None);
}

// ----- Boundary/exceptional inputs: case-sensitivity, whitespace, empty, unknown -----

TEST_F(StringToColourModeTest_689, RejectsDifferentCase_689) {
    // Case-sensitive: upper/lower/mixed variants should not be accepted.
    for (const char* s : {"DEFAULT", "Ansi", "WIN32", "None"}) {
        auto result = Catch::Detail::stringToColourMode(StringRef(s));
        EXPECT_FALSE(result.has_value()) << "Unexpectedly accepted: " << s;
    }
}

TEST_F(StringToColourModeTest_689, RejectsWithLeadingOrTrailingSpaces_689) {
    for (const char* s : {" default", "default ", " ansi", "ansi ", " win32", "win32 ", " none", "none "}) {
        auto result = Catch::Detail::stringToColourMode(StringRef(s));
        EXPECT_FALSE(result.has_value()) << "Unexpectedly accepted: '" << s << "'";
    }
}

TEST_F(StringToColourModeTest_689, RejectsEmptyString_689) {
    auto result = Catch::Detail::stringToColourMode(StringRef(""));
    EXPECT_FALSE(result.has_value());
}

TEST_F(StringToColourModeTest_689, RejectsUnknownTokens_689) {
    for (const char* s : {"purple", "defaultt", "ansii", "win320", "nope"}) {
        auto result = Catch::Detail::stringToColourMode(StringRef(s));
        EXPECT_FALSE(result.has_value()) << "Unexpectedly accepted: " << s;
    }
}
