// File: tests/isColourImplAvailable_tests.cpp
#include <gtest/gtest.h>

// Provided dependency: ColourMode enum
#include "catch2/interfaces/catch_interfaces_config.hpp"

// The function under test is defined in a .cpp without a public header,
// so we declare it here to call it (not re-implementing it).
namespace Catch {
    bool isColourImplAvailable( ColourMode colourSelection );
}

// Test suite
class ConsoleColourImplTest_634 : public ::testing::Test {};

// --- Normal operation cases ---

TEST_F(ConsoleColourImplTest_634, ReturnsTrueForANSI_634) {
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::ANSI));
}

TEST_F(ConsoleColourImplTest_634, ReturnsTrueForNone_634) {
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::None));
}

TEST_F(ConsoleColourImplTest_634, ReturnsTrueForPlatformDefault_634) {
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::PlatformDefault));
}

// --- Platform-dependent case (Win32) ---

TEST_F(ConsoleColourImplTest_634, HandlesWin32AccordingToConfigMacro_634) {
#if defined(CATCH_CONFIG_COLOUR_WIN32)
    // When the Win32 colour support is compiled in, it should be reported as available.
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::Win32));
#else
    // When not compiled in, Win32 should not be reported as available.
    EXPECT_FALSE(Catch::isColourImplAvailable(Catch::ColourMode::Win32));
#endif
}

// --- Boundary / exceptional observable behavior ---

TEST_F(ConsoleColourImplTest_634, ReturnsFalseForUnknownEnumValue_634) {
    // Cast an out-of-range value to ColourMode; observable behavior should be "not available".
    auto invalid = static_cast<Catch::ColourMode>(999);
    EXPECT_FALSE(Catch::isColourImplAvailable(invalid));
}
