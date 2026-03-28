// File: poppler-text-attributes-copy-test_2478.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-page.h"  // PopplerTextAttributes, PopplerColor
// poppler_text_attributes_copy is implemented in poppler-page.cc

namespace {

class PopplerTextAttributesCopyTest_2478 : public ::testing::Test {
 protected:
  static void FreeAttrs(PopplerTextAttributes* attrs) {
    if (!attrs) return;
    // The copy implementation uses g_strdup() for font_name, so g_free is correct here.
    // In Poppler, PopplerTextAttributes is typically slice-allocated, so g_slice_free matches g_slice_dup.
    g_free(reinterpret_cast<gpointer>(attrs->font_name));
    g_slice_free(PopplerTextAttributes, attrs);
  }

  static PopplerTextAttributes* NewAttrsWithFontName(const char* font_name_utf8) {
    PopplerTextAttributes* attrs = g_slice_new0(PopplerTextAttributes);
    attrs->font_name = reinterpret_cast<decltype(attrs->font_name)>(g_strdup(font_name_utf8));
    return attrs;
  }

  static PopplerTextAttributes* NewAttrsWithNullFontName() {
    PopplerTextAttributes* attrs = g_slice_new0(PopplerTextAttributes);
    attrs->font_name = nullptr;
    return attrs;
  }
};

TEST_F(PopplerTextAttributesCopyTest_2478, CopyCopiesScalarFields_2478) {
  PopplerTextAttributes* src = NewAttrsWithFontName("DejaVu Sans");

  src->font_size = 12;
  src->is_underlined = 1;
  src->start_index = 3;
  src->end_index = 9;

  // PopplerColor is defined by the real header; set to a deterministic value.
  // (Most Poppler GLib builds define PopplerColor with red/green/blue as guint16.)
  src->color.red = 0x1111;
  src->color.green = 0x2222;
  src->color.blue = 0x3333;

  PopplerTextAttributes* dst = poppler_text_attributes_copy(src);
  ASSERT_NE(dst, nullptr);
  EXPECT_NE(dst, src);

  EXPECT_EQ(dst->font_size, src->font_size);
  EXPECT_EQ(dst->is_underlined, src->is_underlined);
  EXPECT_EQ(dst->start_index, src->start_index);
  EXPECT_EQ(dst->end_index, src->end_index);

  EXPECT_EQ(dst->color.red, src->color.red);
  EXPECT_EQ(dst->color.green, src->color.green);
  EXPECT_EQ(dst->color.blue, src->color.blue);

  FreeAttrs(dst);
  FreeAttrs(src);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyDeepCopiesFontName_2478) {
  PopplerTextAttributes* src = NewAttrsWithFontName("Times New Roman");
  ASSERT_NE(src->font_name, nullptr);

  PopplerTextAttributes* dst = poppler_text_attributes_copy(src);
  ASSERT_NE(dst, nullptr);

  ASSERT_NE(dst->font_name, nullptr);
  // Must be a deep copy: different pointers but same string content.
  EXPECT_NE(dst->font_name, src->font_name);
  EXPECT_STREQ(reinterpret_cast<const char*>(dst->font_name),
               reinterpret_cast<const char*>(src->font_name));

  FreeAttrs(dst);
  FreeAttrs(src);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyAllowsNullFontName_2478) {
  PopplerTextAttributes* src = NewAttrsWithNullFontName();
  ASSERT_EQ(src->font_name, nullptr);

  PopplerTextAttributes* dst = poppler_text_attributes_copy(src);
  ASSERT_NE(dst, nullptr);

  EXPECT_EQ(dst->font_name, nullptr);

  // Other fields should still be duplicated as part of the struct copy.
  EXPECT_EQ(dst->font_size, src->font_size);
  EXPECT_EQ(dst->is_underlined, src->is_underlined);
  EXPECT_EQ(dst->start_index, src->start_index);
  EXPECT_EQ(dst->end_index, src->end_index);

  FreeAttrs(dst);
  FreeAttrs(src);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyDoesNotAliasFontNameBuffer_2478) {
  PopplerTextAttributes* src = NewAttrsWithFontName("ABCDEF");
  ASSERT_NE(src->font_name, nullptr);

  PopplerTextAttributes* dst = poppler_text_attributes_copy(src);
  ASSERT_NE(dst, nullptr);
  ASSERT_NE(dst->font_name, nullptr);

  const char* dst_before = reinterpret_cast<const char*>(dst->font_name);
  EXPECT_STREQ(dst_before, "ABCDEF");

  // Mutate source string buffer (g_strdup returns writable memory).
  char* src_buf = reinterpret_cast<char*>(src->font_name);
  src_buf[0] = 'Z';

  // Copy must remain unchanged if it deep-copied the font_name.
  EXPECT_STREQ(reinterpret_cast<const char*>(dst->font_name), "ABCDEF");
  EXPECT_STREQ(reinterpret_cast<const char*>(src->font_name), "ZBCDEF");

  FreeAttrs(dst);
  FreeAttrs(src);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerTextAttributesCopyTest_2478, NullInputDies_2478) {
  // The provided implementation dereferences text_attrs unconditionally,
  // so passing nullptr is an observable error case (process death).
  EXPECT_DEATH({ (void)poppler_text_attributes_copy(nullptr); }, "");
}
#endif

}  // namespace