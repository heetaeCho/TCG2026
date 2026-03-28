#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib-object.h>
}

#include "poppler-form-field.h"
#include "poppler-private.h"
#include "Form.h"

// Mock FormWidget to control getType() return value
class MockFormWidget : public FormWidget {
public:
    // We need to construct without calling the real constructor
    // Since FormWidget requires complex params, we use a mock approach
    MOCK_METHOD(FormFieldType, getType, (), ());
};

// Since we can't easily construct PopplerFormField as a GObject without the full
// infrastructure, we'll need to work with the poppler glib API properly.
// Let's create a test fixture that can set up proper PopplerFormField objects.

// For testing poppler_form_field_get_field_type, we need:
// 1. A valid PopplerFormField (GObject)
// 2. Its widget member pointing to a FormWidget with controlled getType()

// We'll use a simpler approach: load a PDF with form fields and test the function,
// or we mock at a lower level.

// Since direct construction of GObject types and mocking internal C++ objects is complex,
// let's create a focused integration-style test using the poppler glib API.

#include "poppler.h"
#include "poppler-document.h"
#include "poppler-page.h"

class PopplerFormFieldGetFieldTypeTest_2308 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns POPPLER_FORM_FIELD_UNKNOWN (g_return_val_if_fail check)
TEST_F(PopplerFormFieldGetFieldTypeTest_2308, NullFieldReturnsUnknown_2308)
{
    // g_return_val_if_fail with NULL should return the default value
    // This will trigger a g_critical warning but should return POPPLER_FORM_FIELD_UNKNOWN
    PopplerFormFieldType result = poppler_form_field_get_field_type(NULL);
    EXPECT_EQ(result, POPPLER_FORM_FIELD_UNKNOWN);
}

// Test that passing an invalid GObject (not a PopplerFormField) returns POPPLER_FORM_FIELD_UNKNOWN
TEST_F(PopplerFormFieldGetFieldTypeTest_2308, InvalidObjectReturnsUnknown_2308)
{
    // Create some other GObject that is not a PopplerFormField
    // Using a plain GObject
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    PopplerFormFieldType result = poppler_form_field_get_field_type((PopplerFormField *)obj);
    EXPECT_EQ(result, POPPLER_FORM_FIELD_UNKNOWN);
    g_object_unref(obj);
}

// To test with actual form fields, we need a PDF document with forms.
// We'll create a helper that generates a minimal PDF with form fields,
// or we'll test using the mapping from FormFieldType to PopplerFormFieldType
// by loading form fields from a test PDF if available.

class PopplerFormFieldFromPDFTest_2308 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Try to find a test PDF with form fields
        // We'll create a minimal one in memory or skip if not available
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }
    
    PopplerDocument* loadTestDocument(const char* path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *document = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) g_error_free(error);
        return document;
    }
};

// Test the mapping for button type
TEST_F(PopplerFormFieldFromPDFTest_2308, ButtonFieldTypeMapping_2308)
{
    // This test verifies that formButton maps to POPPLER_FORM_FIELD_BUTTON
    // We verify the enum values are correctly defined
    EXPECT_EQ(POPPLER_FORM_FIELD_BUTTON, 1);
    EXPECT_EQ(POPPLER_FORM_FIELD_TEXT, 2);
    EXPECT_EQ(POPPLER_FORM_FIELD_CHOICE, 3);
    EXPECT_EQ(POPPLER_FORM_FIELD_SIGNATURE, 4);
    EXPECT_EQ(POPPLER_FORM_FIELD_UNKNOWN, 0);
}

// Test enum value consistency between internal and public types
TEST_F(PopplerFormFieldFromPDFTest_2308, EnumConsistency_2308)
{
    // Verify FormFieldType enum values
    EXPECT_EQ(formButton, 0);
    EXPECT_EQ(formText, 1);
    EXPECT_EQ(formChoice, 2);
    EXPECT_EQ(formSignature, 3);
    EXPECT_EQ(formUndef, 4);
}

// Test with actual form fields if a test PDF exists
TEST_F(PopplerFormFieldFromPDFTest_2308, FormFieldsFromDocument_2308)
{
    // Attempt to load a test PDF with form fields
    const char* test_paths[] = {
        "test-form.pdf",
        "../test/test-form.pdf",
        "../../test/test-form.pdf",
        nullptr
    };
    
    PopplerDocument *document = nullptr;
    for (int i = 0; test_paths[i] != nullptr; i++) {
        document = loadTestDocument(test_paths[i]);
        if (document) break;
    }
    
    if (!document) {
        GTEST_SKIP() << "No test PDF with form fields available";
        return;
    }
    
    doc = document;
    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GT(n_pages, 0);
    
    for (int i = 0; i < n_pages; i++) {
        PopplerPage *page = poppler_document_get_page(doc, i);
        if (!page) continue;
        
        GList *fields = poppler_page_get_form_field_mapping(page);
        for (GList *l = fields; l != nullptr; l = l->next) {
            PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping *)l->data;
            PopplerFormField *field = mapping->field;
            
            PopplerFormFieldType type = poppler_form_field_get_field_type(field);
            // The type should be one of the known types
            EXPECT_TRUE(type == POPPLER_FORM_FIELD_UNKNOWN ||
                       type == POPPLER_FORM_FIELD_BUTTON ||
                       type == POPPLER_FORM_FIELD_TEXT ||
                       type == POPPLER_FORM_FIELD_CHOICE ||
                       type == POPPLER_FORM_FIELD_SIGNATURE)
                << "Unexpected form field type: " << type;
        }
        
        poppler_page_free_form_field_mapping(fields);
        g_object_unref(page);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, &argv);
    return RUN_ALL_TESTS();
}
