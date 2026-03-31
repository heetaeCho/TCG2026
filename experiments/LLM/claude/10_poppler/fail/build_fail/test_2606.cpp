#include <gtest/gtest.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// Include the .cc file to access the static function
// We need to handle any dependencies
#include "splash/SplashFTFont.cc"

class GetFTLoadFlagsTest_2606 : public ::testing::Test {
protected:
};

// Test: No AA, no hinting => FT_LOAD_DEFAULT | FT_LOAD_NO_HINTING
TEST_F(GetFTLoadFlagsTest_2606, NoAANoHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(false, false, false, false, false);
    EXPECT_TRUE(flags & FT_LOAD_NO_HINTING);
    EXPECT_FALSE(flags & FT_LOAD_NO_BITMAP);
}

// Test: AA enabled, no hinting => FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING
TEST_F(GetFTLoadFlagsTest_2606, AAEnabledNoHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(false, false, true, false, false);
    EXPECT_TRUE(flags & FT_LOAD_NO_BITMAP);
    EXPECT_TRUE(flags & FT_LOAD_NO_HINTING);
}

// Test: Hinting enabled with slight hinting => FT_LOAD_TARGET_LIGHT
TEST_F(GetFTLoadFlagsTest_2606, HintingEnabledSlightHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(false, false, false, true, true);
    EXPECT_TRUE(flags & FT_LOAD_TARGET_LIGHT);
    EXPECT_FALSE(flags & FT_LOAD_NO_HINTING);
}

// Test: AA + Hinting + Slight hinting
TEST_F(GetFTLoadFlagsTest_2606, AAHintingSlightHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(false, false, true, true, true);
    EXPECT_TRUE(flags & FT_LOAD_NO_BITMAP);
    EXPECT_TRUE(flags & FT_LOAD_TARGET_LIGHT);
    EXPECT_FALSE(flags & FT_LOAD_NO_HINTING);
}

// Test: TrueType + AA + Hinting, no slight hinting => FT_LOAD_NO_AUTOHINT
TEST_F(GetFTLoadFlagsTest_2606, TrueTypeAAHintingNoSlightHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(false, true, true, true, false);
    EXPECT_TRUE(flags & FT_LOAD_NO_BITMAP);
    EXPECT_TRUE(flags & FT_LOAD_NO_AUTOHINT);
    EXPECT_FALSE(flags & FT_LOAD_NO_HINTING);
}

// Test: TrueType + no AA + Hinting, no slight hinting => just FT_LOAD_DEFAULT
TEST_F(GetFTLoadFlagsTest_2606, TrueTypeNoAAHintingNoSlightHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(false, true, false, true, false);
    // No NO_BITMAP (no AA), no NO_HINTING (hinting enabled), no TARGET_LIGHT (not slight), no NO_AUTOHINT (no AA for truetype)
    EXPECT_EQ(flags, FT_LOAD_DEFAULT);
}

// Test: Type1 + Hinting, no slight hinting => FT_LOAD_TARGET_LIGHT
TEST_F(GetFTLoadFlagsTest_2606, Type1HintingNoSlightHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(true, false, false, true, false);
    EXPECT_TRUE(flags & FT_LOAD_TARGET_LIGHT);
    EXPECT_FALSE(flags & FT_LOAD_NO_HINTING);
}

// Test: Type1 + AA + Hinting, no slight hinting => FT_LOAD_NO_BITMAP | FT_LOAD_TARGET_LIGHT
TEST_F(GetFTLoadFlagsTest_2606, Type1AAHintingNoSlightHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(true, false, true, true, false);
    EXPECT_TRUE(flags & FT_LOAD_NO_BITMAP);
    EXPECT_TRUE(flags & FT_LOAD_TARGET_LIGHT);
    EXPECT_FALSE(flags & FT_LOAD_NO_HINTING);
    EXPECT_FALSE(flags & FT_LOAD_NO_AUTOHINT);
}

// Test: Neither type1 nor truetype, hinting enabled, no slight hinting => just FT_LOAD_DEFAULT (no special flags)
TEST_F(GetFTLoadFlagsTest_2606, NeitherType1NorTrueTypeHintingNoSlightHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(false, false, false, true, false);
    EXPECT_EQ(flags, FT_LOAD_DEFAULT);
}

// Test: Both type1 and truetype set (edge case), AA + hinting, no slight => truetype branch takes precedence
TEST_F(GetFTLoadFlagsTest_2606, BothType1AndTrueTypeAAHinting_2606) {
    FT_Int32 flags = getFTLoadFlags(true, true, true, true, false);
    // truetype branch checked first: aa is true => NO_AUTOHINT
    EXPECT_TRUE(flags & FT_LOAD_NO_AUTOHINT);
    EXPECT_TRUE(flags & FT_LOAD_NO_BITMAP);
}

// Test: All false => FT_LOAD_DEFAULT | FT_LOAD_NO_HINTING
TEST_F(GetFTLoadFlagsTest_2606, AllFalse_2606) {
    FT_Int32 flags = getFTLoadFlags(false, false, false, false, false);
    EXPECT_EQ(flags, FT_LOAD_DEFAULT | FT_LOAD_NO_HINTING);
}

// Test: All true => AA + Hinting + Slight => FT_LOAD_NO_BITMAP | FT_LOAD_TARGET_LIGHT
TEST_F(GetFTLoadFlagsTest_2606, AllTrue_2606) {
    FT_Int32 flags = getFTLoadFlags(true, true, true, true, true);
    EXPECT_TRUE(flags & FT_LOAD_NO_BITMAP);
    EXPECT_TRUE(flags & FT_LOAD_TARGET_LIGHT);
    EXPECT_FALSE(flags & FT_LOAD_NO_HINTING);
}

// Test: Slight hinting without hinting enabled => NO_HINTING still set (slight hinting ignored)
TEST_F(GetFTLoadFlagsTest_2606, SlightHintingWithoutHintingEnabled_2606) {
    FT_Int32 flags = getFTLoadFlags(false, false, false, false, true);
    EXPECT_TRUE(flags & FT_LOAD_NO_HINTING);
}
