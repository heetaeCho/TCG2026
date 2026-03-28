#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib-object.h>
}

#include "poppler-form-field.h"
#include "poppler-private.h"
#include "Form.h"

// We need to mock FormWidget since it's an external dependency
class MockFormWidget : public FormWidget {
public:
    // We can't easily construct FormWidget, so we use a mock approach
    MOCK_CONST_METHOD0(isReadOnly, bool());
    MOCK_METHOD1(setReadOnly, void(bool));
};

// Since we can't easily instantiate PopplerFormField through GObject system
// without the full poppler glib infrastructure, we'll create a test fixture
// that sets up the necessary structures.

// Forward declarations for GObject type system
extern "C" {
    GType poppler_form_field_get_type(void);
    gboolean poppler_form_field_is_read_only(PopplerFormField *field);
}

class PopplerFormFieldIsReadOnlyTest_2311 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns FALSE (g_return_val_if_fail guard)
TEST_F(PopplerFormFieldIsReadOnlyTest_2311, NullFieldReturnsFalse_2311) {
    // g_return_val_if_fail should return FALSE for NULL input
    // This also tests the POPPLER_IS_FORM_FIELD check
    gboolean result = poppler_form_field_is_read_only(NULL);
    EXPECT_EQ(result, FALSE);
}

// Test that an invalid GObject (not a PopplerFormField) returns FALSE
TEST_F(PopplerFormFieldIsReadOnlyTest_2311, InvalidObjectReturnsFalse_2311) {
    // Create a plain GObject which is not a PopplerFormField
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    gboolean result = poppler_form_field_is_read_only((PopplerFormField *)obj);
    EXPECT_EQ(result, FALSE);
    g_object_unref(obj);
}

// Integration-style test: if we can create a real PopplerFormField with a widget
// that reports isReadOnly() as true, we expect TRUE.
// Since creating a full PopplerFormField requires PDFDoc and other infrastructure,
// we test what we can through the public C API.

// Test with a properly constructed PopplerFormField where widget->isReadOnly() returns true
// This requires being able to construct a PopplerFormField, which needs poppler infrastructure.
// We'll test boundary: the g_return_val_if_fail check with various invalid inputs.

TEST_F(PopplerFormFieldIsReadOnlyTest_2311, InvalidCastReturnsFalse_2311) {
    // Passing a random pointer that's not a valid GObject should trigger the guard
    // Note: This might cause warnings but should return FALSE safely
    // We skip this test if it would cause undefined behavior
    // Instead, test with NULL which is guaranteed safe
    gboolean result = poppler_form_field_is_read_only(nullptr);
    EXPECT_FALSE(result);
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
#include "poppler-form-field.h"
}

#include "poppler-private.h"
#include "Form.h"

class PopplerFormFieldReadOnlyTest_2311 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Passing NULL to poppler_form_field_is_read_only should return FALSE
// due to g_return_val_if_fail guard
TEST_F(PopplerFormFieldReadOnlyTest_2311, NullFieldReturnsFalse_2311) {
    gboolean result = poppler_form_field_is_read_only(NULL);
    EXPECT_EQ(result, FALSE);
}

// Test: Passing nullptr should also return FALSE
TEST_F(PopplerFormFieldReadOnlyTest_2311, NullptrFieldReturnsFalse_2311) {
    gboolean result = poppler_form_field_is_read_only(nullptr);
    EXPECT_FALSE(result);
}

// Test: Passing an object that is not a PopplerFormField should return FALSE
TEST_F(PopplerFormFieldReadOnlyTest_2311, NonFormFieldObjectReturnsFalse_2311) {
    GObject *plain_obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    ASSERT_NE(plain_obj, nullptr);
    
    gboolean result = poppler_form_field_is_read_only(reinterpret_cast<PopplerFormField *>(plain_obj));
    EXPECT_EQ(result, FALSE);
    
    g_object_unref(plain_obj);
}
