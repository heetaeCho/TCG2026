// poppler-form-field-get-font-size-test.cc
//
// Unit tests for:
//   gdouble poppler_form_field_get_font_size(PopplerFormField *field)
//
// Constraints respected:
// - Treat implementation as black box
// - Only verify observable behavior via public API (return value / g_return checks)
// - No access to private/internal state
//
// TEST_ID: 2310

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

// Helpers to capture GLib critical warnings triggered by g_return_* macros.
class PopplerFormFieldGetFontSizeTest_2310 : public ::testing::Test {
protected:
  void SetUp() override {
    // Make sure GLib doesn't abort the process on criticals for these tests.
    // We'll assert them via EXPECT_*_MESSAGE instead.
    g_log_set_always_fatal(static_cast<GLogLevelFlags>(G_LOG_FATAL_MASK & ~G_LOG_LEVEL_CRITICAL));
  }

  void TearDown() override {
    // Restore default fatal mask (best effort).
    g_log_set_always_fatal(G_LOG_FATAL_MASK);
  }
};

TEST_F(PopplerFormFieldGetFontSizeTest_2310, NullFieldReturnsZeroAndEmitsCritical_2310) {
  // g_return_val_if_fail(POPPLER_IS_FORM_FIELD(field), 0)
  // Observable behavior: returns 0 and emits a critical assertion.
  EXPECT_GLIB_CRITICAL_MESSAGE("poppler_form_field_get_font_size", "*POPPLER_IS_FORM_FIELD*");
  const gdouble size = poppler_form_field_get_font_size(nullptr);
  EXPECT_DOUBLE_EQ(size, 0.0);
}

TEST_F(PopplerFormFieldGetFontSizeTest_2310, InvalidPointerReturnsZeroAndEmitsCritical_2310) {
  // Boundary/error case: non-null pointer that is not a PopplerFormField instance.
  // We pass a valid GObject of a different type (PopplerDocument) to avoid UB from
  // passing random pointers while still failing POPPLER_IS_FORM_FIELD.
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file("file:///nonexistent.pdf", nullptr, &error);
  // doc may be null (likely), but that's fine: if null, we'd be duplicating the null test.
  // Ensure we have a real object of another type; use a generic GObject if PopplerDocument failed.
  if (!doc) {
    if (error) g_error_free(error);
    GObject* obj = g_object_new(G_TYPE_OBJECT, nullptr);

    EXPECT_GLIB_CRITICAL_MESSAGE("poppler_form_field_get_font_size", "*POPPLER_IS_FORM_FIELD*");
    const gdouble size = poppler_form_field_get_font_size(reinterpret_cast<PopplerFormField*>(obj));
    EXPECT_DOUBLE_EQ(size, 0.0);

    g_object_unref(obj);
    return;
  }

  EXPECT_GLIB_CRITICAL_MESSAGE("poppler_form_field_get_font_size", "*POPPLER_IS_FORM_FIELD*");
  const gdouble size = poppler_form_field_get_font_size(reinterpret_cast<PopplerFormField*>(doc));
  EXPECT_DOUBLE_EQ(size, 0.0);

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetFontSizeTest_2310, ValidFormFieldObjectReturnsZero_2310) {
  // Normal operation (as observable from the provided implementation):
  // When given a valid PopplerFormField instance, function returns 0.
  //
  // We create a minimal valid instance by allocating a GObject of the PopplerFormField type.
  // This does not rely on internal fields; it only ensures POPPLER_IS_FORM_FIELD(field) passes.
  PopplerFormField* field = POPPLER_FORM_FIELD(g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
  ASSERT_NE(field, nullptr);

  // No critical expected for valid instance.
  const gdouble size = poppler_form_field_get_font_size(field);
  EXPECT_DOUBLE_EQ(size, 0.0);

  g_object_unref(field);
}

TEST_F(PopplerFormFieldGetFontSizeTest_2310, RepeatedCallsAreStableForValidField_2310) {
  // Boundary-ish: repeated invocations should consistently return the same observable result.
  PopplerFormField* field = POPPLER_FORM_FIELD(g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
  ASSERT_NE(field, nullptr);

  const gdouble s1 = poppler_form_field_get_font_size(field);
  const gdouble s2 = poppler_form_field_get_font_size(field);
  const gdouble s3 = poppler_form_field_get_font_size(field);

  EXPECT_DOUBLE_EQ(s1, 0.0);
  EXPECT_DOUBLE_EQ(s2, 0.0);
  EXPECT_DOUBLE_EQ(s3, 0.0);

  g_object_unref(field);
}