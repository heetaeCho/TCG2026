// poppler_text_span_copy_test_2542.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string>

extern "C" {

// Prefer real project headers when available.
#if defined(__has_include)
#  if __has_include("poppler-structure-element.h")
#    include "poppler-structure-element.h"
#  endif
#  if __has_include(<poppler.h>)
#    include <poppler.h>
#  endif
#endif

// Fallback (only if the type isn't provided by headers in this build).
#ifndef POPPLER_TYPE_TEXT_SPAN
// If PopplerTextSpan isn't declared by included headers, declare the minimal
// shape required by the public function signature used in this test.
// This mirrors the observable fields used by the copy function.
typedef struct _PopplerTextSpan {
  gchar *text;
  gchar *font_name;
} PopplerTextSpan;
#endif

PopplerTextSpan *poppler_text_span_copy(PopplerTextSpan *poppler_text_span);

} // extern "C"

namespace {

class PopplerTextSpanCopyTest_2542 : public ::testing::Test {
protected:
  static PopplerTextSpan *MakeSpan(const char *text, const char *font_name) {
    PopplerTextSpan *span = g_slice_new0(PopplerTextSpan);
    span->text = text ? g_strdup(text) : nullptr;
    span->font_name = font_name ? g_strdup(font_name) : nullptr;
    return span;
  }

  static void FreeSpan(PopplerTextSpan *span) {
    if (!span)
      return;
    g_free(span->text);
    g_free(span->font_name);
    g_slice_free(PopplerTextSpan, span);
  }
};

TEST_F(PopplerTextSpanCopyTest_2542, NullInputReturnsNull_2542) {
  EXPECT_EQ(poppler_text_span_copy(nullptr), nullptr);
}

TEST_F(PopplerTextSpanCopyTest_2542, CopiesTextAndFontNameDeeply_2542) {
  PopplerTextSpan *orig = MakeSpan("Hello", "SomeFont");
  ASSERT_NE(orig, nullptr);

  PopplerTextSpan *copy = poppler_text_span_copy(orig);
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, orig);

  ASSERT_NE(copy->text, nullptr);
  ASSERT_NE(orig->text, nullptr);
  EXPECT_STREQ(copy->text, orig->text);
  EXPECT_NE(copy->text, orig->text); // deep copy

  ASSERT_NE(copy->font_name, nullptr);
  ASSERT_NE(orig->font_name, nullptr);
  EXPECT_STREQ(copy->font_name, orig->font_name);
  EXPECT_NE(copy->font_name, orig->font_name); // deep copy

  FreeSpan(copy);
  FreeSpan(orig);
}

TEST_F(PopplerTextSpanCopyTest_2542, CopiesWhenFontNameIsNull_2542) {
  PopplerTextSpan *orig = MakeSpan("Hello", nullptr);
  ASSERT_NE(orig, nullptr);

  PopplerTextSpan *copy = poppler_text_span_copy(orig);
  ASSERT_NE(copy, nullptr);

  ASSERT_NE(copy->text, nullptr);
  ASSERT_NE(orig->text, nullptr);
  EXPECT_STREQ(copy->text, orig->text);
  EXPECT_NE(copy->text, orig->text);

  EXPECT_EQ(copy->font_name, nullptr);

  FreeSpan(copy);
  FreeSpan(orig);
}

TEST_F(PopplerTextSpanCopyTest_2542, HandlesNullTextPointer_2542) {
  PopplerTextSpan *orig = MakeSpan(nullptr, "FontX");
  ASSERT_NE(orig, nullptr);

  PopplerTextSpan *copy = poppler_text_span_copy(orig);
  ASSERT_NE(copy, nullptr);

  EXPECT_EQ(copy->text, nullptr);

  ASSERT_NE(copy->font_name, nullptr);
  ASSERT_NE(orig->font_name, nullptr);
  EXPECT_STREQ(copy->font_name, orig->font_name);
  EXPECT_NE(copy->font_name, orig->font_name);

  FreeSpan(copy);
  FreeSpan(orig);
}

TEST_F(PopplerTextSpanCopyTest_2542, CopiesEmptyStrings_2542) {
  PopplerTextSpan *orig = MakeSpan("", "");
  ASSERT_NE(orig, nullptr);

  PopplerTextSpan *copy = poppler_text_span_copy(orig);
  ASSERT_NE(copy, nullptr);

  ASSERT_NE(copy->text, nullptr);
  ASSERT_NE(copy->font_name, nullptr);
  EXPECT_STREQ(copy->text, "");
  EXPECT_STREQ(copy->font_name, "");
  EXPECT_NE(copy->text, orig->text);
  EXPECT_NE(copy->font_name, orig->font_name);

  FreeSpan(copy);
  FreeSpan(orig);
}

TEST_F(PopplerTextSpanCopyTest_2542, OriginalMutationDoesNotAffectCopy_2542) {
  PopplerTextSpan *orig = MakeSpan("ABCDE", "FontY");
  ASSERT_NE(orig, nullptr);

  PopplerTextSpan *copy = poppler_text_span_copy(orig);
  ASSERT_NE(copy, nullptr);

  // Mutate original buffers (they are owned by this test).
  ASSERT_NE(orig->text, nullptr);
  ASSERT_NE(orig->font_name, nullptr);
  orig->text[0] = 'Z';
  orig->font_name[0] = 'Q';

  // Copy should remain unchanged if deep-copied.
  ASSERT_NE(copy->text, nullptr);
  ASSERT_NE(copy->font_name, nullptr);
  EXPECT_STREQ(copy->text, "ABCDE");
  EXPECT_STREQ(copy->font_name, "FontY");

  FreeSpan(copy);
  FreeSpan(orig);
}

} // namespace