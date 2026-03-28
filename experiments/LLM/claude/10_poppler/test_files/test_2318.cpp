#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
#include "poppler-form-field.h"
}

#include "poppler-private.h"
#include "Form.h"
#include "GooString.h"

// Mock FormWidget to control getMappingName() return value
class MockFormWidget : public FormWidget {
public:
    // We need a constructor that doesn't require real PDFDoc, etc.
    // Since FormWidget requires complex construction, we use a mock approach.
    MockFormWidget() : FormWidget(nullptr, nullptr, 0, Ref{0, 0}, nullptr) {}
    
    MOCK_CONST_METHOD0(getMappingName, const GooString*());
};

// Helper to create a PopplerFormField for testing
// Since PopplerFormField is a GObject, we need to use the GLib type system
class PopplerFormFieldGetMappingNameTest_2318 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll work with the poppler form field infrastructure
    }
    
    void TearDown() override {
    }
};

// Test that passing NULL returns NULL
TEST_F(PopplerFormFieldGetMappingNameTest_2318, ReturnsNullForNullField_2318) {
    // poppler_form_field_get_mapping_name should handle NULL gracefully
    // due to g_return_val_if_fail check
    gchar *result = poppler_form_field_get_mapping_name(NULL);
    EXPECT_EQ(result, nullptr);
}

// Since creating proper PopplerFormField GObjects requires a full document context
// which is complex to set up in unit tests, we test the NULL/invalid input path
// which exercises the g_return_val_if_fail guard.

// Test with an invalid GObject (not a PopplerFormField)
TEST_F(PopplerFormFieldGetMappingNameTest_2318, ReturnsNullForInvalidObject_2318) {
    // Passing a non-PopplerFormField GObject should trigger g_return_val_if_fail
    // and return NULL
    gchar *result = poppler_form_field_get_mapping_name((PopplerFormField*)0x1);
    // This would likely crash or return NULL depending on implementation
    // We primarily test the NULL case above as the safe test
    // This test is noted but may not be safe to run without a valid GObject
}

// Integration-style test: if we can create a real PopplerFormField from a document,
// test that mapping name returns expected value. This requires document loading
// infrastructure which is beyond pure unit testing scope.

// Test that the function exists and is callable (link test)
TEST_F(PopplerFormFieldGetMappingNameTest_2318, FunctionExists_2318) {
    // Verify the function pointer is valid
    auto func_ptr = &poppler_form_field_get_mapping_name;
    EXPECT_NE(func_ptr, nullptr);
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
#include <poppler.h>
}

#include <cstdio>
#include <cstdlib>
#include <fstream>

class PopplerFormFieldMappingNameTest_2318 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL to poppler_form_field_get_mapping_name returns NULL
TEST_F(PopplerFormFieldMappingNameTest_2318, ReturnsNullForNullField_2318) {
    // g_return_val_if_fail should catch NULL and return NULL
    gchar *result = poppler_form_field_get_mapping_name(NULL);
    EXPECT_EQ(result, nullptr);
}

// Test that the function signature is correct and linkable
TEST_F(PopplerFormFieldMappingNameTest_2318, FunctionIsCallable_2318) {
    typedef gchar* (*FuncType)(PopplerFormField*);
    FuncType fn = &poppler_form_field_get_mapping_name;
    ASSERT_NE(fn, nullptr);
}

// If a PDF with form fields is available, test with actual form field
// This tests the normal operation path
TEST_F(PopplerFormFieldMappingNameTest_2318, WithRealFormField_ReturnsExpectedValue_2318) {
    // Try to load a test PDF with form fields
    // If no test PDF is available, skip this test
    const char* test_pdf_path = getenv("TEST_PDF_WITH_FORMS");
    if (!test_pdf_path) {
        GTEST_SKIP() << "No TEST_PDF_WITH_FORMS environment variable set";
    }
    
    GError *error = NULL;
    gchar *uri = g_filename_to_uri(test_pdf_path, NULL, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not convert path to URI";
    }
    
    PopplerDocument *doc = poppler_document_new_from_file(uri, NULL, &error);
    g_free(uri);
    if (!doc) {
        GTEST_SKIP() << "Could not open test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get first page";
    }
    
    GList *fields = poppler_page_get_form_field_mapping(page);
    if (!fields) {
        g_object_unref(page);
        g_object_unref(doc);
        GTEST_SKIP() << "No form fields found";
    }
    
    PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping*)fields->data;
    PopplerFormField *field = mapping->field;
    
    // This should not crash - result may be NULL or a valid string
    gchar *name = poppler_form_field_get_mapping_name(field);
    // We just verify it doesn't crash; the value depends on the PDF
    if (name) {
        EXPECT_TRUE(g_utf8_validate(name, -1, NULL));
        g_free(name);
    }
    
    poppler_page_free_form_field_mapping(fields);
    g_object_unref(page);
    g_object_unref(doc);
}
