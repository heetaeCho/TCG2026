// File: ./TestProjects/poppler/glib/poppler-font-description-new-test_2124.cc
//
// Unit tests for:
//   PopplerFontDescription *poppler_font_description_new(const char *font_name)
//
// Constraints:
// - Treat implementation as a black box (test observable behavior only).
// - No private/internal state access.
// - Include normal, boundary, and observable error cases.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Forward declarations (match production headers)
typedef struct _PopplerFontDescription PopplerFontDescription;

typedef enum {
  POPPLER_STRETCH_ULTRA_CONDENSED = 0,
  POPPLER_STRETCH_EXTRA_CONDENSED = 1,
  POPPLER_STRETCH_CONDENSED = 2,
  POPPLER_STRETCH_SEMI_CONDENSED = 3,
  POPPLER_STRETCH_NORMAL = 4,
  POPPLER_STRETCH_SEMI_EXPANDED = 5,
  POPPLER_STRETCH_EXPANDED = 6,
  POPPLER_STRETCH_EXTRA_EXPANDED = 7,
  POPPLER_STRETCH_ULTRA_EXPANDED = 8
} PopplerStretch;

typedef enum {
  POPPLER_STYLE_NORMAL = 0,
  POPPLER_STYLE_OBLIQUE = 1,
  POPPLER_STYLE_ITALIC = 2
} PopplerStyle;

typedef enum {
  POPPLER_WEIGHT_THIN = 100,
  POPPLER_WEIGHT_ULTRALIGHT = 200,
  POPPLER_WEIGHT_LIGHT = 300,
  POPPLER_WEIGHT_NORMAL = 400,
  POPPLER_WEIGHT_MEDIUM = 500,
  POPPLER_WEIGHT_SEMIBOLD = 600,
  POPPLER_WEIGHT_BOLD = 700,
  POPPLER_WEIGHT_ULTRABOLD = 800,
  POPPLER_WEIGHT_HEAVY = 900
} PopplerWeight;

// The function under test (from poppler-annot.cc)
PopplerFontDescription *poppler_font_description_new(const char *font_name);

}  // extern "C"

// We rely on the public struct layout from the public header.
extern "C" {
struct _PopplerFontDescription {
  char *font_name;
  double size_pt;
  PopplerStretch stretch;
  PopplerStyle style;
  PopplerWeight weight;
};
}  // extern "C"

namespace {

class PopplerFontDescriptionNewTest_2124 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Nothing: each test frees its own allocations.
  }

  static void FreeFontDesc(PopplerFontDescription *desc) {
    if (!desc) return;
    // This matches GLib ownership expectations for g_strdup/g_new0 allocations.
    g_free(desc->font_name);
    g_free(desc);
  }
};

TEST_F(PopplerFontDescriptionNewTest_2124, ReturnsNonNullForTypicalName_2124) {
  PopplerFontDescription *desc = poppler_font_description_new("Helvetica");
  ASSERT_NE(desc, nullptr);

  // Basic sanity: duplicated string should be non-null and equal.
  ASSERT_NE(desc->font_name, nullptr);
  EXPECT_STREQ(desc->font_name, "Helvetica");

  FreeFontDesc(desc);
}

TEST_F(PopplerFontDescriptionNewTest_2124, InitializesDefaultFieldsToExpectedDefaults_2124) {
  PopplerFontDescription *desc = poppler_font_description_new("Times-Roman");
  ASSERT_NE(desc, nullptr);

  // Observable defaults from the interface/struct fields.
  EXPECT_DOUBLE_EQ(desc->size_pt, 11.0);
  EXPECT_EQ(desc->stretch, POPPLER_STRETCH_NORMAL);
  EXPECT_EQ(desc->style, POPPLER_STYLE_NORMAL);
  EXPECT_EQ(desc->weight, POPPLER_WEIGHT_NORMAL);

  FreeFontDesc(desc);
}

TEST_F(PopplerFontDescriptionNewTest_2124, DuplicatesInputStringNotAliasingCallerBuffer_2124) {
  char buf[64];
  g_strlcpy(buf, "Courier", sizeof(buf));

  PopplerFontDescription *desc = poppler_font_description_new(buf);
  ASSERT_NE(desc, nullptr);
  ASSERT_NE(desc->font_name, nullptr);

  // Should not alias caller buffer: pointer differs.
  EXPECT_NE(desc->font_name, buf);
  EXPECT_STREQ(desc->font_name, "Courier");

  // Mutate caller buffer; created description should remain unchanged if duplicated.
  g_strlcpy(buf, "Changed", sizeof(buf));
  EXPECT_STREQ(desc->font_name, "Courier");

  FreeFontDesc(desc);
}

TEST_F(PopplerFontDescriptionNewTest_2124, AcceptsEmptyStringName_2124) {
  PopplerFontDescription *desc = poppler_font_description_new("");
  ASSERT_NE(desc, nullptr);

  ASSERT_NE(desc->font_name, nullptr);
  EXPECT_STREQ(desc->font_name, "");

  // Defaults still apply.
  EXPECT_DOUBLE_EQ(desc->size_pt, 11.0);
  EXPECT_EQ(desc->stretch, POPPLER_STRETCH_NORMAL);
  EXPECT_EQ(desc->style, POPPLER_STYLE_NORMAL);
  EXPECT_EQ(desc->weight, POPPLER_WEIGHT_NORMAL);

  FreeFontDesc(desc);
}

// Error/exceptional case (observable behavior):
// Passing nullptr to a C API may be invalid; many GLib string functions tolerate
// nullptr by returning nullptr, but behavior may vary. We only assert that the
// call does not crash, and if a struct is returned, its invariants are sane.
TEST_F(PopplerFontDescriptionNewTest_2124, NullNameDoesNotCrashAndReturnsConsistentObject_2124) {
  PopplerFontDescription *desc = poppler_font_description_new(nullptr);

  // If implementation chooses to return nullptr, that's acceptable as an
  // observable error behavior; if non-null, validate fields are consistent.
  if (desc == nullptr) {
    SUCCEED();
    return;
  }

  // If non-null, font_name may be nullptr; other defaults should still be set.
  EXPECT_DOUBLE_EQ(desc->size_pt, 11.0);
  EXPECT_EQ(desc->stretch, POPPLER_STRETCH_NORMAL);
  EXPECT_EQ(desc->style, POPPLER_STYLE_NORMAL);
  EXPECT_EQ(desc->weight, POPPLER_WEIGHT_NORMAL);

  // Free safely.
  FreeFontDesc(desc);
}

}  // namespace