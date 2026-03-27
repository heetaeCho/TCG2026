// poppler-text-attributes-free-test.cpp
//
// Unit tests for poppler_text_attributes_free()
// TEST_ID: 2479

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-page.h"

// Function under test (implemented in poppler-page.cc and linked from the library/object files)
void poppler_text_attributes_free(PopplerTextAttributes *text_attrs);
}

namespace {

class PopplerTextAttributesFreeTest_2479 : public ::testing::Test {
protected:
  static PopplerTextAttributes *NewAttrsWithFontNameBytes(gsize bytes) {
    // Allocate the struct using the same allocator family as production code expects to free.
    auto *attrs = g_slice_new0(PopplerTextAttributes);

    // font_name is declared as int* in the provided header snippet; the implementation uses g_free().
    // Allocate raw bytes so g_free() is valid regardless of the declared pointer type.
    if (bytes > 0) {
      attrs->font_name = static_cast<int *>(g_malloc0(bytes));
    } else {
      attrs->font_name = nullptr;
    }

    // Fill remaining fields with some boundary-ish values (should not affect freeing behavior).
    attrs->font_size = G_MAXINT;
    attrs->is_underlined = 1;
    attrs->start_index = 0;
    attrs->end_index = G_MAXINT;

    return attrs;
  }
};

TEST_F(PopplerTextAttributesFreeTest_2479, FreesValidObjectWithNonNullFontName_2479) {
  PopplerTextAttributes *attrs = NewAttrsWithFontNameBytes(/*bytes=*/64);
  ASSERT_NE(attrs, nullptr);
  ASSERT_NE(attrs->font_name, nullptr);

  // Observable behavior: should not crash for a valid object.
  EXPECT_NO_THROW(poppler_text_attributes_free(attrs));
}

TEST_F(PopplerTextAttributesFreeTest_2479, FreesValidObjectWithNullFontName_2479) {
  PopplerTextAttributes *attrs = NewAttrsWithFontNameBytes(/*bytes=*/0);
  ASSERT_NE(attrs, nullptr);
  ASSERT_EQ(attrs->font_name, nullptr);

  // g_free(NULL) is permitted; observable behavior should be no crash.
  EXPECT_NO_THROW(poppler_text_attributes_free(attrs));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerTextAttributesFreeTest_2479, NullPointerIsInvalidAndDies_2479) {
  // The interface does not specify null-safety; dereferencing a null pointer is observable as a crash.
  // Use a death test to document this boundary/error case if it occurs in the implementation.
  EXPECT_DEATH(
      {
        poppler_text_attributes_free(nullptr);
      },
      "");
}
#endif

}  // namespace