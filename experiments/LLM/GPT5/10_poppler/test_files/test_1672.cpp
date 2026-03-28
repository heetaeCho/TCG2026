// CairoFontEngine_isSubstitute_test_1672.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Poppler headers
#include "CairoFontEngine.h"
#include "Object.h" // for Ref (Poppler)

namespace {

static Ref MakeRef_1672(int num, int gen) {
  Ref r;
  r.num = num;
  r.gen = gen;
  return r;
}

} // namespace

class CairoFontTest_1672 : public ::testing::Test {};

TEST_F(CairoFontTest_1672, IsSubstituteReturnsTrueWhenConstructedAsSubstitute_1672) {
  Ref ref = MakeRef_1672(1, 0);

  // The header shows cairo_font_face as an int* in this test project.
  // Use nullptr to avoid ownership assumptions in the destructor.
  int *fontFace = nullptr;

  int codeToGID = 0;
  CairoFont font(ref, fontFace, std::move(codeToGID), /*substituteA=*/true, /*printingA=*/false);

  EXPECT_TRUE(font.isSubstitute());
}

TEST_F(CairoFontTest_1672, IsSubstituteReturnsFalseWhenConstructedNotSubstitute_1672) {
  Ref ref = MakeRef_1672(2, 0);
  int *fontFace = nullptr;

  int codeToGID = 0;
  CairoFont font(ref, fontFace, std::move(codeToGID), /*substituteA=*/false, /*printingA=*/false);

  EXPECT_FALSE(font.isSubstitute());
}

TEST_F(CairoFontTest_1672, IsSubstituteIsConstAndStableAcrossMultipleCalls_1672) {
  Ref ref = MakeRef_1672(3, 0);
  int *fontFace = nullptr;

  int codeToGID = 0;
  CairoFont font(ref, fontFace, std::move(codeToGID), /*substituteA=*/true, /*printingA=*/true);

  const CairoFont &cfont = font; // exercise const-call surface
  EXPECT_TRUE(cfont.isSubstitute());
  EXPECT_TRUE(cfont.isSubstitute());
  EXPECT_TRUE(cfont.isSubstitute());
}

TEST_F(CairoFontTest_1672, CopyOperationsAreDisabledByInterface_1672) {
  // Observable via type traits (no internal logic assumptions).
  EXPECT_FALSE((std::is_copy_constructible_v<CairoFont>));
  EXPECT_FALSE((std::is_copy_assignable_v<CairoFont>));
}