// poppler_text_span_get_text_test_2548.cc
#include <gtest/gtest.h>

#include <glib.h>

// Include the public header if available in your build; otherwise the forward
// declarations below can be used (and the struct definition must match the
// library's ABI).
//
// If your project already provides PopplerTextSpan in a header, prefer that.
extern "C" {

// Forward declarations (match Poppler GLib style)
typedef struct _PopplerTextSpan PopplerTextSpan;

// Function under test
const gchar *poppler_text_span_get_text(PopplerTextSpan *poppler_text_span);

} // extern "C"

// Minimal struct definition to construct test instances.
// NOTE: This must match the actual definition used by the compiled library.
// If your build already provides a definition via a header, remove this block.
struct _PopplerTextSpan {
  gchar *text;
};

class PopplerTextSpanGetTextTest_2548 : public ::testing::Test {};

TEST_F(PopplerTextSpanGetTextTest_2548, NullSpanReturnsNullAndLogsCritical_2548) {
  // g_return_val_if_fail() emits a critical log message on failure.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*assertion*poppler_text_span*failed*");

  const gchar *result = poppler_text_span_get_text(nullptr);
  EXPECT_EQ(result, nullptr);

  g_test_assert_expected_messages();
}

TEST_F(PopplerTextSpanGetTextTest_2548, NonNullSpanWithNullTextReturnsNull_2548) {
  PopplerTextSpan span{};
  span.text = nullptr;

  const gchar *result = poppler_text_span_get_text(&span);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerTextSpanGetTextTest_2548, ReturnsSamePointerForValidText_2548) {
  PopplerTextSpan span{};
  gchar buf[] = "Hello Poppler";
  span.text = buf;

  const gchar *result = poppler_text_span_get_text(&span);

  // Observable behavior: returns the stored pointer; and it should read as the same string.
  EXPECT_EQ(result, static_cast<const gchar *>(buf));
  EXPECT_STREQ(result, "Hello Poppler");
}

TEST_F(PopplerTextSpanGetTextTest_2548, ReturnsPointerEvenForEmptyString_2548) {
  PopplerTextSpan span{};
  gchar buf[] = "";
  span.text = buf;

  const gchar *result = poppler_text_span_get_text(&span);
  EXPECT_EQ(result, static_cast<const gchar *>(buf));
  EXPECT_STREQ(result, "");
}