// File: poppler-annot-free-text-get-font-desc-test_2101.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

// The public headers typically forward-declare PopplerAnnotFreeText as an
// incomplete struct type. For unit testing this single function (which only
// reads `font_desc`), we complete the type with the fields provided in the prompt.
struct _PopplerAnnotFreeText {
  PopplerFontDescription* font_desc;
  PopplerColor font_color;
};

class PopplerAnnotFreeTextGetFontDescTest_2101 : public ::testing::Test {
 protected:
  static PopplerAnnotFreeText* MakeAnnotWithFontDesc(PopplerFontDescription* desc) {
    auto* annot = static_cast<PopplerAnnotFreeText*>(g_malloc0(sizeof(_PopplerAnnotFreeText)));
    annot->font_desc = desc;
    return annot;
  }

  static void FreeAnnotOnly(PopplerAnnotFreeText* annot) {
    g_free(annot);
  }
};

TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, ReturnsNullWhenFontDescIsNull_2101) {
  PopplerAnnotFreeText* annot = MakeAnnotWithFontDesc(nullptr);

  PopplerFontDescription* out = poppler_annot_free_text_get_font_desc(annot);
  EXPECT_EQ(out, nullptr);

  FreeAnnotOnly(annot);
}

TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, ReturnsNonNullCopyWhenFontDescIsSet_2101) {
  PopplerFontDescription* original = poppler_font_description_new("Sans");
  ASSERT_NE(original, nullptr);

  PopplerAnnotFreeText* annot = MakeAnnotWithFontDesc(original);

  PopplerFontDescription* out = poppler_annot_free_text_get_font_desc(annot);
  ASSERT_NE(out, nullptr);

  // Observable behavior: the function returns a newly allocated copy (not the same pointer).
  EXPECT_NE(out, original);

  poppler_font_description_free(out);
  poppler_font_description_free(original);
  FreeAnnotOnly(annot);
}

TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, MultipleCallsReturnDistinctCopies_2101) {
  PopplerFontDescription* original = poppler_font_description_new("Serif");
  ASSERT_NE(original, nullptr);

  PopplerAnnotFreeText* annot = MakeAnnotWithFontDesc(original);

  PopplerFontDescription* out1 = poppler_annot_free_text_get_font_desc(annot);
  PopplerFontDescription* out2 = poppler_annot_free_text_get_font_desc(annot);

  ASSERT_NE(out1, nullptr);
  ASSERT_NE(out2, nullptr);

  // Each call should return a newly allocated copy.
  EXPECT_NE(out1, original);
  EXPECT_NE(out2, original);
  EXPECT_NE(out1, out2);

  poppler_font_description_free(out2);
  poppler_font_description_free(out1);
  poppler_font_description_free(original);
  FreeAnnotOnly(annot);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, DeathOnNullAnnotPointer_2101) {
  // The implementation dereferences poppler_annot; passing nullptr is an error case.
  // Death test makes the behavior observable without relying on internal state.
  EXPECT_DEATH(
      {
        (void)poppler_annot_free_text_get_font_desc(nullptr);
      },
      ".*");
}
#endif