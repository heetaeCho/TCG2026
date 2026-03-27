// File: get_ft_load_flags_test_2606.cc
#include <gtest/gtest.h>

#include <ft2build.h>
#include FT_FREETYPE_H

// Include the implementation file to access the internal-linkage (static) function.
// This is a common unit-testing technique for file-local helpers.
#include "TestProjects/poppler/splash/SplashFTFont.cc"

namespace {

class GetFTLoadFlagsTest_2606 : public ::testing::Test {
protected:
  static void ExpectHasFlag(FT_Int32 flags, FT_Int32 mask) {
    EXPECT_NE(flags & mask, 0) << "Expected flag mask to be set: " << mask;
  }
  static void ExpectNoFlag(FT_Int32 flags, FT_Int32 mask) {
    EXPECT_EQ(flags & mask, 0) << "Expected flag mask to be NOT set: " << mask;
  }
};

TEST_F(GetFTLoadFlagsTest_2606, DefaultFlags_NoAA_HintingEnabled_NoSlight_NoFontType_2606) {
  const FT_Int32 flags =
      getFTLoadFlags(/*type1=*/false, /*trueType=*/false, /*aa=*/false,
                     /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  // Boundary/normal: with no conditions requesting extra bits, should stay default.
  EXPECT_EQ(flags, FT_LOAD_DEFAULT);
  ExpectNoFlag(flags, FT_LOAD_NO_BITMAP);
  ExpectNoFlag(flags, FT_LOAD_NO_HINTING);
  ExpectNoFlag(flags, FT_LOAD_TARGET_LIGHT);
  ExpectNoFlag(flags, FT_LOAD_NO_AUTOHINT);
}

TEST_F(GetFTLoadFlagsTest_2606, AntiAliasingAddsNoBitmap_2606) {
  const FT_Int32 flags =
      getFTLoadFlags(/*type1=*/false, /*trueType=*/false, /*aa=*/true,
                     /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  // Observable behavior: AA implies no embedded bitmaps.
  ExpectHasFlag(flags, FT_LOAD_NO_BITMAP);
  ExpectNoFlag(flags, FT_LOAD_NO_HINTING);
}

TEST_F(GetFTLoadFlagsTest_2606, HintingDisabledForcesNoHinting_2606) {
  const FT_Int32 flags =
      getFTLoadFlags(/*type1=*/true, /*trueType=*/true, /*aa=*/true,
                     /*enableFreeTypeHinting=*/false, /*enableSlightHinting=*/true);

  // Boundary: hinting disabled should force NO_HINTING regardless of other inputs.
  ExpectHasFlag(flags, FT_LOAD_NO_HINTING);
  // AA still should request no bitmap glyphs.
  ExpectHasFlag(flags, FT_LOAD_NO_BITMAP);

  // With hinting disabled, no hinting-target/autohint-related flags should be requested.
  ExpectNoFlag(flags, FT_LOAD_TARGET_LIGHT);
  ExpectNoFlag(flags, FT_LOAD_NO_AUTOHINT);
}

TEST_F(GetFTLoadFlagsTest_2606, SlightHintingRequestsTargetLight_2606) {
  const FT_Int32 flags =
      getFTLoadFlags(/*type1=*/false, /*trueType=*/true, /*aa=*/false,
                     /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/true);

  // Normal: slight hinting requests the light target.
  ExpectHasFlag(flags, FT_LOAD_TARGET_LIGHT);
  ExpectNoFlag(flags, FT_LOAD_NO_HINTING);
}

TEST_F(GetFTLoadFlagsTest_2606, TrueTypeWithAAAndHintingNoSlightRequestsNoAutoHint_2606) {
  const FT_Int32 flags =
      getFTLoadFlags(/*type1=*/false, /*trueType=*/true, /*aa=*/true,
                     /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  ExpectHasFlag(flags, FT_LOAD_NO_BITMAP);
  // Observable behavior specific to TrueType + AA + hinting enabled (no slight):
  ExpectHasFlag(flags, FT_LOAD_NO_AUTOHINT);

  ExpectNoFlag(flags, FT_LOAD_NO_HINTING);
  ExpectNoFlag(flags, FT_LOAD_TARGET_LIGHT);
}

TEST_F(GetFTLoadFlagsTest_2606, TrueTypeWithoutAAAndHintingNoSlightDoesNotRequestNoAutoHint_2606) {
  const FT_Int32 flags =
      getFTLoadFlags(/*type1=*/false, /*trueType=*/true, /*aa=*/false,
                     /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  ExpectNoFlag(flags, FT_LOAD_NO_BITMAP);
  ExpectNoFlag(flags, FT_LOAD_NO_AUTOHINT);
  ExpectNoFlag(flags, FT_LOAD_TARGET_LIGHT);
  ExpectNoFlag(flags, FT_LOAD_NO_HINTING);
}

TEST_F(GetFTLoadFlagsTest_2606, Type1WithHintingNoSlightRequestsTargetLight_2606) {
  const FT_Int32 flags_noaa =
      getFTLoadFlags(/*type1=*/true, /*trueType=*/false, /*aa=*/false,
                     /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  const FT_Int32 flags_aa =
      getFTLoadFlags(/*type1=*/true, /*trueType=*/false, /*aa=*/true,
                     /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  // Observable behavior: Type1 with hinting enabled (no slight) requests light target.
  ExpectHasFlag(flags_noaa, FT_LOAD_TARGET_LIGHT);
  ExpectNoFlag(flags_noaa, FT_LOAD_NO_BITMAP);

  ExpectHasFlag(flags_aa, FT_LOAD_TARGET_LIGHT);
  ExpectHasFlag(flags_aa, FT_LOAD_NO_BITMAP);

  // Should not force hinting off, and should not request no-autohint in the Type1 path.
  ExpectNoFlag(flags_noaa, FT_LOAD_NO_HINTING);
  ExpectNoFlag(flags_aa, FT_LOAD_NO_HINTING);
  ExpectNoFlag(flags_noaa, FT_LOAD_NO_AUTOHINT);
  ExpectNoFlag(flags_aa, FT_LOAD_NO_AUTOHINT);
}

TEST_F(GetFTLoadFlagsTest_2606, BothTrueTypeAndType1PrefersTrueTypeBranch_2606) {
  const FT_Int32 flags =
      getFTLoadFlags(/*type1=*/true, /*trueType=*/true, /*aa=*/false,
                     /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  // Boundary: if both are set, behavior should follow the TrueType path.
  // With aa=false, the TrueType path should not request NO_AUTOHINT,
  // and it should not request TARGET_LIGHT (that would be the Type1 path here).
  ExpectNoFlag(flags, FT_LOAD_NO_AUTOHINT);
  ExpectNoFlag(flags, FT_LOAD_TARGET_LIGHT);
  ExpectNoFlag(flags, FT_LOAD_NO_BITMAP);
  ExpectNoFlag(flags, FT_LOAD_NO_HINTING);
}

}  // namespace