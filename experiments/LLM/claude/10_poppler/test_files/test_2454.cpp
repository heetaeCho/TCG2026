#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>

class PopplerPageFormFieldMappingTest_2454 : public ::testing::Test {
protected:
    PopplerDocument *doc_with_forms = nullptr;
    PopplerDocument *doc_without_forms = nullptr;
    
    void SetUp() override {
        // Try to create a simple PDF without forms for testing
        // We'll attempt to load test PDFs if available
    }
    
    void TearDown() override {
        if (doc_with_forms) {
            g_object_unref(doc_with_forms);
        }
        if (doc_without_forms) {
            g_object_unref(doc_without_forms);
        }
    }
    
    PopplerDocument* createSimplePdfDocument() {
        // Create a minimal PDF in memory
        const char *pdf_content = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
        
        gsize len = strlen(pdf_content);
        GError *error = nullptr;
        
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        PopplerDocument *doc = poppler_document_new_from_stream(
            stream, len, nullptr, nullptr, &error);
        
        g_object_unref(stream);
        g_bytes_unref(bytes);
        
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

// Test that passing NULL returns NULL (g_return_val_if_fail check)
TEST_F(PopplerPageFormFieldMappingTest_2454, NullPageReturnsNull_2454) {
    GList *result = poppler_page_get_form_field_mapping(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that a page without form fields returns NULL or empty list
TEST_F(PopplerPageFormFieldMappingTest_2454, PageWithoutFormsReturnsNullOrEmpty_2454) {
    PopplerDocument *doc = createSimplePdfDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *result = poppler_page_get_form_field_mapping(page);
    // A page without forms should return NULL (no form widgets)
    EXPECT_EQ(result, nullptr);
    
    if (result) {
        poppler_page_free_form_field_mapping(result);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
}

// Test that the free function handles NULL gracefully
TEST_F(PopplerPageFormFieldMappingTest_2454, FreeMappingHandlesNull_2454) {
    // Should not crash
    poppler_page_free_form_field_mapping(nullptr);
}

// Test with a PDF containing form fields (if available)
TEST_F(PopplerPageFormFieldMappingTest_2454, FormFieldMappingHasValidArea_2454) {
    // Try to find a test PDF with forms
    const char *test_paths[] = {
        "test-form.pdf",
        "../test-form.pdf",
        "tests/test-form.pdf",
        nullptr
    };
    
    PopplerDocument *doc = nullptr;
    GError *error = nullptr;
    
    for (int i = 0; test_paths[i] != nullptr; i++) {
        gchar *uri = g_filename_to_uri(test_paths[i], nullptr, nullptr);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
            if (doc) break;
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }
    
    if (!doc) {
        GTEST_SKIP() << "No test PDF with form fields available";
    }
    
    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GT(n_pages, 0);
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *mappings = poppler_page_get_form_field_mapping(page);
    
    if (mappings) {
        // Verify each mapping has valid data
        for (GList *l = mappings; l != nullptr; l = l->next) {
            PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping *)l->data;
            ASSERT_NE(mapping, nullptr);
            EXPECT_NE(mapping->field, nullptr);
            // Area coordinates should be reasonable (not NaN or infinity)
            EXPECT_FALSE(std::isnan(mapping->area.x1));
            EXPECT_FALSE(std::isnan(mapping->area.y1));
            EXPECT_FALSE(std::isnan(mapping->area.x2));
            EXPECT_FALSE(std::isnan(mapping->area.y2));
        }
        
        poppler_page_free_form_field_mapping(mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
}

// Test that the returned list length matches expected count
TEST_F(PopplerPageFormFieldMappingTest_2454, MappingListLengthConsistency_2454) {
    PopplerDocument *doc = createSimplePdfDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    // Call twice to verify consistency
    GList *result1 = poppler_page_get_form_field_mapping(page);
    GList *result2 = poppler_page_get_form_field_mapping(page);
    
    guint len1 = result1 ? g_list_length(result1) : 0;
    guint len2 = result2 ? g_list_length(result2) : 0;
    
    EXPECT_EQ(len1, len2);
    
    if (result1) poppler_page_free_form_field_mapping(result1);
    if (result2) poppler_page_free_form_field_mapping(result2);
    
    g_object_unref(page);
    g_object_unref(doc);
}

// Test poppler_form_field_mapping_new and copy
TEST_F(PopplerPageFormFieldMappingTest_2454, FormFieldMappingNewReturnsValid_2454) {
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    
    // New mapping should have zeroed area
    EXPECT_DOUBLE_EQ(mapping->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 0.0);
    EXPECT_EQ(mapping->field, nullptr);
    
    poppler_form_field_mapping_free(mapping);
}

// Test that poppler_form_field_mapping_copy works
TEST_F(PopplerPageFormFieldMappingTest_2454, FormFieldMappingCopy_2454) {
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    
    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    
    EXPECT_DOUBLE_EQ(copy->area.x1, mapping->area.x1);
    EXPECT_DOUBLE_EQ(copy->area.y1, mapping->area.y1);
    EXPECT_DOUBLE_EQ(copy->area.x2, mapping->area.x2);
    EXPECT_DOUBLE_EQ(copy->area.y2, mapping->area.y2);
    
    poppler_form_field_mapping_free(mapping);
    poppler_form_field_mapping_free(copy);
}

// Test that poppler_form_field_mapping_free handles NULL
TEST_F(PopplerPageFormFieldMappingTest_2454, FormFieldMappingFreeHandlesNull_2454) {
    // Should not crash
    poppler_form_field_mapping_free(nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
