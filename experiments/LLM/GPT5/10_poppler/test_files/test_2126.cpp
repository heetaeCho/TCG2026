// File: poppler-font-description-copy-test-2126.cc

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-annot.h"

// Function under test (C++ linkage in this codebase).
PopplerFontDescription *poppler_font_description_copy(PopplerFontDescription *font_desc);

namespace {

class PopplerFontDescriptionCopyTest_2126 : public ::testing::Test {
protected:
  static PopplerFontDescription *MakeDesc(const char *name,
                                         double size_pt,
                                         PopplerStretch stretch,
                                         PopplerWeight weight,
                                         PopplerStyle style) {
    auto *d = g_new(PopplerFontDescription, 1);
    d->font_name = name ? g_strdup(name) : nullptr;
    d->size_pt = size_pt;
    d->stretch = stretch;
    d->weight = weight;
    d->style = style;
    return d;
  }

  static void FreeDesc(PopplerFontDescription *d) {
    if (!d)
      return;
    g_free(d->font_name);
    g_free(d);
  }
};

TEST_F(PopplerFontDescriptionCopyTest_2126, CopiesAllFieldsAndDuplicatesFontName_2126) {
  PopplerStretch stretch = static_cast<PopplerStretch>(1);
  PopplerWeight weight = static_cast<PopplerWeight>(2);
  PopplerStyle style = static_cast<PopplerStyle>(3);

  PopplerFontDescription *src = MakeDesc("DejaVu Sans", 12.5, stretch, weight, style);
  ASSERT_NE(src, nullptr);
  ASSERT_NE(src->font_name, nullptr);

  PopplerFontDescription *copy = poppler_font_description_copy(src);
  ASSERT_NE(copy, nullptr);

  // Different object pointer.
  EXPECT_NE(copy, src);

  // Scalar fields copied.
  EXPECT_DOUBLE_EQ(copy->size_pt, src->size_pt);
  EXPECT_EQ(copy->stretch, src->stretch);
  EXPECT_EQ(copy->weight, src->weight);
  EXPECT_EQ(copy->style, src->style);

  // String duplicated (same contents, different pointer).
  ASSERT_NE(copy->font_name, nullptr);
  EXPECT_STREQ(copy->font_name, src->font_name);
  EXPECT_NE(copy->font_name, src->font_name);

  FreeDesc(copy);
  FreeDesc(src);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopiesEmptyFontNameString_2126) {
  PopplerStretch stretch = static_cast<PopplerStretch>(0);
  PopplerWeight weight = static_cast<PopplerWeight>(0);
  PopplerStyle style = static_cast<PopplerStyle>(0);

  PopplerFontDescription *src = MakeDesc("", 0.0, stretch, weight, style);
  ASSERT_NE(src, nullptr);
  ASSERT_NE(src->font_name, nullptr);
  EXPECT_STREQ(src->font_name, "");

  PopplerFontDescription *copy = poppler_font_description_copy(src);
  ASSERT_NE(copy, nullptr);

  ASSERT_NE(copy->font_name, nullptr);
  EXPECT_STREQ(copy->font_name, "");
  EXPECT_NE(copy->font_name, src->font_name);

  EXPECT_DOUBLE_EQ(copy->size_pt, 0.0);

  FreeDesc(copy);
  FreeDesc(src);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, HandlesNullFontName_2126) {
  PopplerStretch stretch = static_cast<PopplerStretch>(7);
  PopplerWeight weight = static_cast<PopplerWeight>(8);
  PopplerStyle style = static_cast<PopplerStyle>(9);

  PopplerFontDescription *src = MakeDesc(nullptr, 9.75, stretch, weight, style);
  ASSERT_NE(src, nullptr);
  EXPECT_EQ(src->font_name, nullptr);

  PopplerFontDescription *copy = poppler_font_description_copy(src);
  ASSERT_NE(copy, nullptr);

  // If the source name is null, the copy should observe a null name too.
  EXPECT_EQ(copy->font_name, nullptr);

  // Other fields copied.
  EXPECT_DOUBLE_EQ(copy->size_pt, src->size_pt);
  EXPECT_EQ(copy->stretch, src->stretch);
  EXPECT_EQ(copy->weight, src->weight);
  EXPECT_EQ(copy->style, src->style);

  FreeDesc(copy);
  FreeDesc(src);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyIsIndependentFromSourceFontNameLifetime_2126) {
  PopplerStretch stretch = static_cast<PopplerStretch>(4);
  PopplerWeight weight = static_cast<PopplerWeight>(5);
  PopplerStyle style = static_cast<PopplerStyle>(6);

  PopplerFontDescription *src = MakeDesc("OriginalName", 11.0, stretch, weight, style);
  ASSERT_NE(src, nullptr);
  ASSERT_NE(src->font_name, nullptr);

  PopplerFontDescription *copy = poppler_font_description_copy(src);
  ASSERT_NE(copy, nullptr);
  ASSERT_NE(copy->font_name, nullptr);
  EXPECT_STREQ(copy->font_name, "OriginalName");

  // Replace source font_name with a different allocation/value.
  g_free(src->font_name);
  src->font_name = g_strdup("MutatedName");
  ASSERT_NE(src->font_name, nullptr);
  EXPECT_STREQ(src->font_name, "MutatedName");

  // Copy should remain unchanged if it truly duplicated the string.
  ASSERT_NE(copy->font_name, nullptr);
  EXPECT_STREQ(copy->font_name, "OriginalName");

  FreeDesc(copy);
  FreeDesc(src);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopiesVeryLongFontName_2126) {
  const int kLen = 8192;
  GString *gs = g_string_sized_new(kLen);
  for (int i = 0; i < kLen; ++i)
    g_string_append_c(gs, static_cast<gchar>('A' + (i % 26)));

  PopplerFontDescription *src =
      MakeDesc(gs->str, 123.0, static_cast<PopplerStretch>(10), static_cast<PopplerWeight>(11),
               static_cast<PopplerStyle>(12));
  ASSERT_NE(src, nullptr);
  ASSERT_NE(src->font_name, nullptr);

  PopplerFontDescription *copy = poppler_font_description_copy(src);
  ASSERT_NE(copy, nullptr);
  ASSERT_NE(copy->font_name, nullptr);

  EXPECT_EQ(strlen(copy->font_name), strlen(src->font_name));
  EXPECT_STREQ(copy->font_name, src->font_name);
  EXPECT_NE(copy->font_name, src->font_name);

  g_string_free(gs, TRUE);
  FreeDesc(copy);
  FreeDesc(src);
}

}  // namespace