#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
#include "poppler-form-field.h"
}

#include "poppler-private.h"
#include "Form.h"
#include "GooString.h"

// We need to mock FormWidget to control getFullyQualifiedName() behavior
class MockFormWidget : public FormWidget {
public:
    // We can't easily construct a real FormWidget, so we use a mock approach.
    // However, FormWidget requires complex dependencies. We'll use a different strategy.
    MOCK_METHOD(const GooString*, getFullyQualifiedName, (), ());
};

// Since we can't easily instantiate PopplerFormField through the GObject system
// without a real PDF document, we'll test through the public C API as much as possible.
// We need to create a minimal test fixture that sets up a PopplerFormField.

// Helper to create a PopplerFormField for testing
// Note: In practice, PopplerFormField is a GObject. We need to work with the
// actual GObject type system.

class PopplerFormFieldGetNameTest_2319 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL (g_return_val_if_fail check)
TEST_F(PopplerFormFieldGetNameTest_2319, ReturnsNullForNullField_2319)
{
    // g_return_val_if_fail(POPPLER_IS_FORM_FIELD(field), NULL) should trigger
    // and return NULL when field is NULL
    // We need to suppress GLib critical warnings for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_FORM_FIELD*");
    gchar *result = poppler_form_field_get_name(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that passing an invalid (non-PopplerFormField) GObject returns NULL
TEST_F(PopplerFormFieldGetNameTest_2319, ReturnsNullForInvalidObject_2319)
{
    // Create some other GObject that is not a PopplerFormField
    GObject *not_a_form_field = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_FORM_FIELD*");
    gchar *result = poppler_form_field_get_name((PopplerFormField *)not_a_form_field);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);

    g_object_unref(not_a_form_field);
}

// Integration-style test: We cannot easily create a real PopplerFormField without
// a real PopplerDocument/PopplerPage, so the most meaningful tests we can write
// at the unit level are the null/invalid input guards above.
// Below we document what would be tested with a real document.

// Test with a real PDF that has form fields would verify:
// 1. A field with a name returns a non-null UTF-8 string
// 2. The returned string matches the expected field name
// 3. A field whose getFullyQualifiedName() returns nullptr results in nullptr from get_name
// 4. The returned string must be freed with g_free

// Additional boundary test: cast a random pointer
TEST_F(PopplerFormFieldGetNameTest_2319, ReturnsNullForGarbagePointer_2319)
{
    // A non-GObject pointer should fail the POPPLER_IS_FORM_FIELD check
    int dummy = 42;
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_FORM_FIELD*");
    gchar *result = poppler_form_field_get_name((PopplerFormField *)(gpointer)&dummy);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
