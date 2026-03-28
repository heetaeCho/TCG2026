// poppler-annot-free-text-set-font-color-test_2102.cc
#include <gtest/gtest.h>

#include <climits>

// Minimal type definitions based strictly on the provided snippets.
// (No internal logic is re-implemented.)

extern "C" {

typedef struct _PopplerFontDescription PopplerFontDescription;

typedef struct _PopplerColor {
  int red;
  int green;
  int blue;
} PopplerColor;

typedef struct _PopplerAnnotFreeText {
  PopplerFontDescription* font_desc;
  PopplerColor font_color;
} PopplerAnnotFreeText;

// Function under test (implemented in the real codebase).
void poppler_annot_free_text_set_font_color(PopplerAnnotFreeText* poppler_annot,
                                           PopplerColor* color);
}  // extern "C"

class PopplerAnnotFreeTextSetFontColorTest_2102 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Make death tests more robust across platforms.
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  }
};

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, CopiesFontColorValues_2102) {
  PopplerAnnotFreeText annot{};
  annot.font_desc = nullptr;
  annot.font_color = PopplerColor{1, 2, 3};

  PopplerColor new_color{10, 20, 30};
  poppler_annot_free_text_set_font_color(&annot, &new_color);

  EXPECT_EQ(annot.font_color.red, 10);
  EXPECT_EQ(annot.font_color.green, 20);
  EXPECT_EQ(annot.font_color.blue, 30);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, OverwritesPreviousColor_2102) {
  PopplerAnnotFreeText annot{};
  annot.font_desc = nullptr;
  annot.font_color = PopplerColor{111, 222, 333};

  PopplerColor new_color{0, 0, 0};
  poppler_annot_free_text_set_font_color(&annot, &new_color);

  EXPECT_EQ(annot.font_color.red, 0);
  EXPECT_EQ(annot.font_color.green, 0);
  EXPECT_EQ(annot.font_color.blue, 0);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, BoundaryValuesAreCopied_2102) {
  PopplerAnnotFreeText annot{};
  annot.font_desc = nullptr;
  annot.font_color = PopplerColor{7, 8, 9};

  PopplerColor boundary_color{INT_MIN, 0, INT_MAX};
  poppler_annot_free_text_set_font_color(&annot, &boundary_color);

  EXPECT_EQ(annot.font_color.red, INT_MIN);
  EXPECT_EQ(annot.font_color.green, 0);
  EXPECT_EQ(annot.font_color.blue, INT_MAX);
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, DeathOnNullAnnot_2102) {
  PopplerColor color{1, 2, 3};
  ASSERT_DEATH(
      {
        poppler_annot_free_text_set_font_color(nullptr, &color);
      },
      "");
}

TEST_F(PopplerAnnotFreeTextSetFontColorTest_2102, DeathOnNullColor_2102) {
  PopplerAnnotFreeText annot{};
  annot.font_desc = nullptr;
  annot.font_color = PopplerColor{1, 2, 3};

  ASSERT_DEATH(
      {
        poppler_annot_free_text_set_font_color(&annot, nullptr);
      },
      "");
}