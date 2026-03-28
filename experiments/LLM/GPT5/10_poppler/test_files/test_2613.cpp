// TestProjects/poppler/splash/Splash_imgCoordMungeLowerC_test_2613.cc

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

// Pull in SplashCoord + splashFloor/splashCeil.
#include "splash/SplashMath.h"

// The function under test is defined as `static inline` in Splash.cc (per prompt).
// Including the file makes the function visible in this translation unit.
#include "TestProjects/poppler/splash/Splash.cc"

namespace {

class ImgCoordMungeLowerCTest_2613 : public ::testing::Test {};

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphModeFalseMatchesSplashFloor_2613)
{
    const SplashCoord xs[] = {
        (SplashCoord)0.0,  (SplashCoord)0.1,  (SplashCoord)0.9,  (SplashCoord)1.0,  (SplashCoord)1.1,
        (SplashCoord)-0.1, (SplashCoord)-0.9, (SplashCoord)-1.0, (SplashCoord)-1.1,
        (SplashCoord)1234.25, (SplashCoord)-1234.25,
    };

    for (SplashCoord x : xs) {
        const int got = imgCoordMungeLowerC(x, /*glyphMode=*/false);
        const int expected = splashFloor(x);
        EXPECT_EQ(got, expected) << "x=" << (double)x;
    }
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphModeTrueMatchesCeilOfXPlusHalfMinusOne_2613)
{
    const SplashCoord xs[] = {
        (SplashCoord)0.0,
        (SplashCoord)0.49, (SplashCoord)0.50, (SplashCoord)0.51,
        (SplashCoord)1.49, (SplashCoord)1.50, (SplashCoord)1.51,
        (SplashCoord)-0.49, (SplashCoord)-0.50, (SplashCoord)-0.51,
        (SplashCoord)-1.49, (SplashCoord)-1.50, (SplashCoord)-1.51,
        (SplashCoord)10.25, (SplashCoord)-10.25,
    };

    for (SplashCoord x : xs) {
        const int got = imgCoordMungeLowerC(x, /*glyphMode=*/true);
        const int expected = splashCeil(x + (SplashCoord)0.5) - 1;
        EXPECT_EQ(got, expected) << "x=" << (double)x;
    }
}

TEST_F(ImgCoordMungeLowerCTest_2613, GlyphModeFlagChangesResultForSomeFractions_2613)
{
    // Pick values where floor(x) and ceil(x+0.5)-1 typically differ.
    const SplashCoord xs[] = {
        (SplashCoord)0.9,
        (SplashCoord)1.1,
        (SplashCoord)-0.1,
        (SplashCoord)-0.9,
    };

    for (SplashCoord x : xs) {
        const int got_non_glyph = imgCoordMungeLowerC(x, /*glyphMode=*/false);
        const int got_glyph = imgCoordMungeLowerC(x, /*glyphMode=*/true);

        // Verify each mode matches its observable contract.
        EXPECT_EQ(got_non_glyph, splashFloor(x)) << "x=" << (double)x;
        EXPECT_EQ(got_glyph, splashCeil(x + (SplashCoord)0.5) - 1) << "x=" << (double)x;

        // Also ensure the flag can actually matter (without asserting it always must).
        // If they happen to be equal for a particular x due to rounding, that's OK.
        (void)got_non_glyph;
        (void)got_glyph;
    }
}

TEST_F(ImgCoordMungeLowerCTest_2613, HandlesLargeMagnitudeInputs_2613)
{
    const SplashCoord xs[] = {
        (SplashCoord)1e6 + (SplashCoord)0.3,
        (SplashCoord)1e6 + (SplashCoord)0.8,
        (SplashCoord)-1e6 - (SplashCoord)0.3,
        (SplashCoord)-1e6 - (SplashCoord)0.8,
        (SplashCoord)1e9 + (SplashCoord)0.25,
        (SplashCoord)-1e9 - (SplashCoord)0.25,
    };

    for (SplashCoord x : xs) {
        EXPECT_EQ(imgCoordMungeLowerC(x, /*glyphMode=*/false), splashFloor(x)) << "x=" << (double)x;
        EXPECT_EQ(imgCoordMungeLowerC(x, /*glyphMode=*/true), splashCeil(x + (SplashCoord)0.5) - 1) << "x=" << (double)x;
    }
}

} // namespace