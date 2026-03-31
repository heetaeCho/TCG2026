#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poppler GLib headers
#include "poppler.h"
#include "poppler-private.h"

// For FormWidget
#include "Form.h"

#include <glib-object.h>
#include <string>
#include <memory>

// Declaration of the function under test (it's internal/private API)
extern "C" {
PopplerFormField *_poppler_form_field_new(PopplerDocument *document, FormWidget *field);
}

class PopplerFormFieldNewTest_2307 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a PopplerDocument from a minimal PDF for testing
        // We need a valid PopplerDocument instance
        GError *error = nullptr;
        
        // Try to create a document from a minimal PDF in memory
        const char *minimal_pdf = 
            "%PDF-1.0\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n190\n%%EOF\n";

        gsize len = strlen(minimal_pdf);
        GBytes *bytes = g_bytes_new(minimal_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        document = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        
        if (document == nullptr && error != nullptr) {
            g_error_free(error);
            error = nullptr;
        }
        
        g_object_unref(stream);
        g_bytes_unref(bytes);
        
        // If stream approach didn't work, try from data
        if (document == nullptr) {
            document = poppler_document_new_from_data((char*)minimal_pdf, len, nullptr, &error);
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

// Test that passing NULL document returns NULL
TEST_F(PopplerFormFieldNewTest_2307, NullDocumentReturnsNull_2307) {
    // g_return_val_if_fail(POPPLER_IS_DOCUMENT(document), NULL) should trigger
    // We pass nullptr for document - this should return NULL
    // Note: This will produce a GLib warning, which is expected
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    PopplerFormField *result = _poppler_form_field_new(nullptr, (FormWidget*)0x1);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that passing NULL field returns NULL
TEST_F(PopplerFormFieldNewTest_2307, NullFieldReturnsNull_2307) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*field != nullptr*");
    PopplerFormField *result = _poppler_form_field_new(document, nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that passing both NULL returns NULL (document check first)
TEST_F(PopplerFormFieldNewTest_2307, BothNullReturnsNull_2307) {
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    PopplerFormField *result = _poppler_form_field_new(nullptr, nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that a non-PopplerDocument GObject is rejected
TEST_F(PopplerFormFieldNewTest_2307, InvalidDocumentTypeReturnsNull_2307) {
    // Create some other GObject that is NOT a PopplerDocument
    GObject *not_a_document = (GObject*)g_object_new(G_TYPE_OBJECT, nullptr);
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    PopplerFormField *result = _poppler_form_field_new((PopplerDocument*)not_a_document, (FormWidget*)0x1);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
    g_object_unref(not_a_document);
}

// Test successful creation with valid document and a form field from a real PDF
class PopplerFormFieldFromPDFTest_2307 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    
    void SetUp() override {
        // We need a PDF with actual form fields for full integration testing
        // For now we set up a basic document
    }
    
    void TearDown() override {
        if (document) {
            g_object_unref(document);
        }
    }
};

// Test that the result is a valid PopplerFormField GObject type
TEST_F(PopplerFormFieldNewTest_2307, ValidCreationReturnsNonNull_2307) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    // Get form fields from a page if available
    PopplerPage *page = poppler_document_get_page(document, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from document";
    }
    
    GList *fields = poppler_page_get_form_field_mapping(page);
    if (!fields) {
        g_object_unref(page);
        GTEST_SKIP() << "No form fields in test document";
    }
    
    // If we have form fields, verify they are valid PopplerFormField objects
    for (GList *l = fields; l != nullptr; l = l->next) {
        PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping *)l->data;
        ASSERT_NE(mapping->field, nullptr);
        EXPECT_TRUE(POPPLER_IS_FORM_FIELD(mapping->field));
    }
    
    poppler_page_free_form_field_mapping(fields);
    g_object_unref(page);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
