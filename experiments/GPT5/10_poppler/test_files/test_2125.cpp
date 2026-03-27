// File: poppler_font_description_free_test_2125.cc
#include <gtest/gtest.h>

#include <glib.h>

// Include the public header that declares PopplerFontDescription.
// Adjust include path if your build uses a different layout.
#include "poppler-annot.h"

extern "C" {
void poppler_font_description_free(PopplerFontDescription *font_desc);
}

class PopplerFontDescriptionFreeTest_2125 : public ::testing::Test {
protected:
  static PopplerFontDescription* NewDescWithName(const char* name) {
    // Allocate with GLib so poppler_font_description_free (which uses g_free)
    // is paired with compatible allocation.
    PopplerFontDescription* desc = g_new0(PopplerFontDescription, 1);
    desc->font_name = name ? g_strdup(name) : nullptr;
    return desc;
  }
};

TEST_F(PopplerFontDescriptionFreeTest_2125, FreesValidDescription_2125) {
  PopplerFontDescription* desc = NewDescWithName("DejaVu Sans");
  ASSERT_NE(desc, nullptr);
  ASSERT_NE(desc->font_name, nullptr);

  // Observable behavior: should not crash on valid input.
  EXPECT_NO_THROW(poppler_font_description_free(desc));
}

TEST_F(PopplerFontDescriptionFreeTest_2125, FreesWhenFontNameIsNull_2125) {
  PopplerFontDescription* desc = NewDescWithName(nullptr);
  ASSERT_NE(desc, nullptr);
  ASSERT_EQ(desc->font_name, nullptr);

  // Boundary: font_name == NULL should be safely handled (g_free(NULL) is OK).
  EXPECT_NO_THROW(poppler_font_description_free(desc));
}

TEST_F(PopplerFontDescriptionFreeTest_2125, FreesWhenFontNameIsEmptyString_2125) {
  PopplerFontDescription* desc = NewDescWithName("");
  ASSERT_NE(desc, nullptr);
  ASSERT_NE(desc->font_name, nullptr);
  ASSERT_STREQ(desc->font_name, "");

  // Boundary: empty string still a valid allocation to free.
  EXPECT_NO_THROW(poppler_font_description_free(desc));
}

TEST_F(PopplerFontDescriptionFreeTest_2125, DeathOnNullDescriptionPointer_2125) {
  // Error case: passing NULL for font_desc is invalid for this API (dereference).
  // Use a death test to capture the observable failure mode.
  EXPECT_DEATH({ poppler_font_description_free(nullptr); }, ".*");
}