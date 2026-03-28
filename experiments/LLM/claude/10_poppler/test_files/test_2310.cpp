#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler glib headers
extern "C" {
#include "poppler-form-field.h"
#include "poppler-private.h"
#include "poppler-document.h"
}

class PopplerFormFieldGetFontSizeTest_2310 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns 0 (the g_return_val_if_fail guard)
TEST_F(PopplerFormFieldGetFontSizeTest_2310, NullFieldReturnsZero_2310)
{
    gdouble result = poppler_form_field_get_font_size(nullptr);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test that passing an invalid (non-PopplerFormField) GObject returns 0
TEST_F(PopplerFormFieldGetFontSizeTest_2310, InvalidObjectTypeReturnsZero_2310)
{
    // Create a plain GObject which is not a PopplerFormField
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    ASSERT_NE(obj, nullptr);

    gdouble result = poppler_form_field_get_font_size((PopplerFormField *)obj);
    EXPECT_DOUBLE_EQ(result, 0.0);

    g_object_unref(obj);
}

// Test that the function currently returns 0 for any valid PopplerFormField
// Note: Based on the provided implementation, it always returns 0.
// We need a valid PopplerFormField to test this. Since constructing one
// requires internal poppler structures, we test the observable behavior
// through the NULL/invalid paths which are the accessible boundary conditions.

// Test calling the function multiple times with NULL is consistent
TEST_F(PopplerFormFieldGetFontSizeTest_2310, RepeatedCallsWithNullReturnZero_2310)
{
    for (int i = 0; i < 10; ++i) {
        gdouble result = poppler_form_field_get_font_size(nullptr);
        EXPECT_DOUBLE_EQ(result, 0.0);
    }
}
