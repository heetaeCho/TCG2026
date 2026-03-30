// File: poppler-annot-free-text-get-font-color-test_2103.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <poppler.h>

// The production code lives in ./TestProjects/poppler/glib/poppler-annot.cc.
// We only rely on the provided interface and the known dependency layout.
//
// Forward declarations (public headers typically forward-declare these types).
extern "C" PopplerColor *poppler_annot_free_text_get_font_color(PopplerAnnotFreeText *poppler_annot);

// Known dependency (provided in prompt).
// Public headers usually do NOT expose the struct fields, so we define it here for test setup.
struct _PopplerAnnotFreeText {
  PopplerFontDescription *font_desc;
  PopplerColor font_color;
};

static void ExpectPopplerColorEq(const PopplerColor &a, const PopplerColor &b) {
  EXPECT_EQ(a.red, b.red);
  EXPECT_EQ(a.green, b.green);
  EXPECT_EQ(a.blue, b.blue);
}

TEST(PopplerAnnotFreeTextGetFontColorTest_2103, ReturnsNonNullCopyAndMatchesValue_2103) {
  _PopplerAnnotFreeText annot{};
  annot.font_desc = nullptr;
  annot.font_color.red = 0x1234;
  annot.font_color.green = 0xABCD;
  annot.font_color.blue = 0x0001;

  PopplerColor *out = poppler_annot_free_text_get_font_color(
      reinterpret_cast<PopplerAnnotFreeText *>(&annot));

  ASSERT_NE(out, nullptr);
  // Must be a newly allocated object (not an alias to the struct field).
  EXPECT_NE(out, &annot.font_color);

  ExpectPopplerColorEq(*out, annot.font_color);

  g_free(out);
}

TEST(PopplerAnnotFreeTextGetFontColorTest_2103, ReturnedColorIsIndependentCopy_2103) {
  _PopplerAnnotFreeText annot{};
  annot.font_desc = nullptr;
  annot.font_color.red = 0x0102;
  annot.font_color.green = 0x0304;
  annot.font_color.blue = 0x0506;

  PopplerColor *out = poppler_annot_free_text_get_font_color(
      reinterpret_cast<PopplerAnnotFreeText *>(&annot));
  ASSERT_NE(out, nullptr);

  // Mutate returned color; original must not change (copy semantics observable via API result).
  out->red = 0xFFFF;
  out->green = 0x0000;
  out->blue = 0x1111;

  EXPECT_EQ(annot.font_color.red, 0x0102);
  EXPECT_EQ(annot.font_color.green, 0x0304);
  EXPECT_EQ(annot.font_color.blue, 0x0506);

  g_free(out);
}

TEST(PopplerAnnotFreeTextGetFontColorTest_2103, BoundaryAllZeros_2103) {
  _PopplerAnnotFreeText annot{};
  annot.font_desc = nullptr;
  annot.font_color.red = 0x0000;
  annot.font_color.green = 0x0000;
  annot.font_color.blue = 0x0000;

  PopplerColor *out = poppler_annot_free_text_get_font_color(
      reinterpret_cast<PopplerAnnotFreeText *>(&annot));

  ASSERT_NE(out, nullptr);
  ExpectPopplerColorEq(*out, annot.font_color);

  g_free(out);
}

TEST(PopplerAnnotFreeTextGetFontColorTest_2103, BoundaryAllMax_2103) {
  _PopplerAnnotFreeText annot{};
  annot.font_desc = nullptr;
  annot.font_color.red = 0xFFFF;
  annot.font_color.green = 0xFFFF;
  annot.font_color.blue = 0xFFFF;

  PopplerColor *out = poppler_annot_free_text_get_font_color(
      reinterpret_cast<PopplerAnnotFreeText *>(&annot));

  ASSERT_NE(out, nullptr);
  ExpectPopplerColorEq(*out, annot.font_color);

  g_free(out);
}

TEST(PopplerAnnotFreeTextGetFontColorTest_2103, DeathOnNullAnnot_2103) {
  // The provided implementation dereferences poppler_annot unconditionally.
  // If the project later changes behavior (e.g., returns NULL on invalid input),
  // this test can be adjusted accordingly.
  ASSERT_DEATH(
      {
        (void)poppler_annot_free_text_get_font_color(nullptr);
      },
      "");
}