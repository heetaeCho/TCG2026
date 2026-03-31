#include <gtest/gtest.h>

// Include the necessary headers
namespace Catch {
    enum class ColourMode : unsigned int {
        PlatformDefault = 0,
        ANSI = 1,
        Win32 = 2,
        None = 3
    };

    bool isColourImplAvailable(ColourMode colourSelection);
}

class IsColourImplAvailableTest_634 : public ::testing::Test {
protected:
};

TEST_F(IsColourImplAvailableTest_634, ANSIModeIsAvailable_634) {
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::ANSI));
}

TEST_F(IsColourImplAvailableTest_634, NoneModeIsAvailable_634) {
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::None));
}

TEST_F(IsColourImplAvailableTest_634, PlatformDefaultModeIsAvailable_634) {
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::PlatformDefault));
}

TEST_F(IsColourImplAvailableTest_634, Win32ModeAvailability_634) {
    // Win32 is available only if CATCH_CONFIG_COLOUR_WIN32 is defined
#if defined(CATCH_CONFIG_COLOUR_WIN32)
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::Win32));
#else
    EXPECT_FALSE(Catch::isColourImplAvailable(Catch::ColourMode::Win32));
#endif
}

TEST_F(IsColourImplAvailableTest_634, InvalidEnumValueReturnsFalse_634) {
    // Using a value beyond the known enum range
    auto invalidMode = static_cast<Catch::ColourMode>(99);
    EXPECT_FALSE(Catch::isColourImplAvailable(invalidMode));
}

TEST_F(IsColourImplAvailableTest_634, EnumValueFourReturnsFalse_634) {
    // Value just beyond the defined enum values
    auto unknownMode = static_cast<Catch::ColourMode>(4);
    EXPECT_FALSE(Catch::isColourImplAvailable(unknownMode));
}

TEST_F(IsColourImplAvailableTest_634, EnumValueFiveReturnsFalse_634) {
    auto unknownMode = static_cast<Catch::ColourMode>(5);
    EXPECT_FALSE(Catch::isColourImplAvailable(unknownMode));
}

TEST_F(IsColourImplAvailableTest_634, LargeEnumValueReturnsFalse_634) {
    auto unknownMode = static_cast<Catch::ColourMode>(1000);
    EXPECT_FALSE(Catch::isColourImplAvailable(unknownMode));
}

TEST_F(IsColourImplAvailableTest_634, AllDefinedModesChecked_634) {
    // Verify all defined enum values produce expected results
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::PlatformDefault));
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::ANSI));
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::None));
    
    // Win32 conditional
#if defined(CATCH_CONFIG_COLOUR_WIN32)
    EXPECT_TRUE(Catch::isColourImplAvailable(Catch::ColourMode::Win32));
#else
    EXPECT_FALSE(Catch::isColourImplAvailable(Catch::ColourMode::Win32));
#endif
}
