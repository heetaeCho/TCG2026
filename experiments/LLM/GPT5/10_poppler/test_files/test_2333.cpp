// poppler-form-field-text-get-text-test_2333.cc
//
// Unit tests for:
//   gchar *poppler_form_field_text_get_text(PopplerFormField *field)
//
// Constraints respected:
// - Treat implementation as black box (no internal logic reimplementation)
// - Use only observable behavior (returned value)
// - No private state access beyond what the provided interface/struct exposes
// - Boundary/error cases included when observable

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-private.h"   // struct _PopplerFormField { FormWidget *widget; ... }
#include "poppler/Form.h"      // FormWidgetText, GooString, FormFieldType, Ref

extern "C" {
gchar *poppler_form_field_text_get_text(PopplerFormField *field);
}

namespace {

class PopplerFormFieldTextGetTextTest_2333 : public ::testing::Test {
protected:
  PopplerFormFieldTextGetTextTest_2333() {
    // Zero-init to avoid garbage in unused action pointers.
    memset(&field_, 0, sizeof(field_));
    field_.widget = nullptr;
  }

  ~PopplerFormFieldTextGetTextTest_2333() override {
    // We only own widget_.
    field_.widget = nullptr;
  }

  // Helper: create a FormWidgetText with minimal inputs.
  // We intentionally do not assume anything about how these inputs are used;
  // tests will fail if the real implementation requires non-null values.
  void CreateTextWidget_2333() {
    // Many Poppler classes accept "null-ish" placeholders in tests; we do not
    // rely on any behavior besides not crashing during construction and calls
    // used by the public interface in this test.
    PDFDoc *doc = nullptr;
    Object *dictObj = nullptr;
    unsigned int num = 0;
    Ref ref;
    ref.num = 0;
    ref.gen = 0;
    FormField *parentField = nullptr;

    widget_ = std::make_unique<FormWidgetText>(doc, dictObj, num, ref, parentField);
    field_.widget = widget_.get();
  }

  // Helper: set widget content (if widget exists).
  void SetContentUtf8_2333(const char *s) {
    ASSERT_TRUE(widget_);
    widget_->setContent(std::make_unique<GooString>(s));
  }

  PopplerFormField field_;
  std::unique_ptr<FormWidgetText> widget_;
};

TEST_F(PopplerFormFieldTextGetTextTest_2333, ReturnsNullWhenContentIsNull_2333) {
  CreateTextWidget_2333();

  // Do not set content; observable expectation is that we get nullptr
  // if there's no content (tmp ? ... : nullptr).
  gchar *text = poppler_form_field_text_get_text(&field_);
  EXPECT_EQ(text, nullptr);

  // Nothing to free when nullptr.
}

TEST_F(PopplerFormFieldTextGetTextTest_2333, ReturnsUtf8StringWhenContentIsSet_2333) {
  CreateTextWidget_2333();
  SetContentUtf8_2333("Hello, Poppler!");

  gchar *text = poppler_form_field_text_get_text(&field_);
  ASSERT_NE(text, nullptr);
  EXPECT_STREQ(text, "Hello, Poppler!");

  g_free(text);
}

TEST_F(PopplerFormFieldTextGetTextTest_2333, HandlesEmptyStringContent_2333) {
  CreateTextWidget_2333();
  SetContentUtf8_2333("");

  gchar *text = poppler_form_field_text_get_text(&field_);
  ASSERT_NE(text, nullptr);
  EXPECT_STREQ(text, "");

  g_free(text);
}

TEST_F(PopplerFormFieldTextGetTextTest_2333, HandlesNonAsciiUtf8Content_2333) {
  CreateTextWidget_2333();

  // UTF-8 text; conversion helper should return a valid UTF-8 C string.
  // (We only assert round-trip string equality on the returned UTF-8.)
  SetContentUtf8_2333("Korean: 한글 ✓");

  gchar *text = poppler_form_field_text_get_text(&field_);
  ASSERT_NE(text, nullptr);
  EXPECT_STREQ(text, "Korean: 한글 ✓");

  g_free(text);
}

}  // namespace