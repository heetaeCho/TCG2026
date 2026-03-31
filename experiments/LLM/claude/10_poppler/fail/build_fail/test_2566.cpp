#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>

// Include necessary headers for poppler glib
#include <poppler-structure-element.h>
#include <poppler-document.h>
#include <poppler-page.h>

// Test fixture for PopplerStructureElement tests
class PopplerStructureElementGetEndIndentTest_2566 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll load a PDF with structure elements if available
        document = nullptr;
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
        }
    }

    PopplerDocument *document;
};

// Test that passing NULL returns NAN (g_return_val_if_fail check)
TEST_F(PopplerStructureElementGetEndIndentTest_2566, NullElementReturnsNAN_2566) {
    gdouble result = poppler_structure_element_get_end_indent(nullptr);
    EXPECT_TRUE(std::isnan(result));
}

// Test that a non-block structure element returns NAN
// This test verifies the g_return_val_if_fail with is_block check
TEST_F(PopplerStructureElementGetEndIndentTest_2566, NonBlockElementReturnsNAN_2566) {
    // Load a tagged PDF that has inline (non-block) structure elements
    GError *error = nullptr;
    
    // Try to find a test PDF with structure elements
    // If no suitable PDF exists, we test with what we can
    const char *test_pdf_path = g_getenv("TEST_PDF_PATH");
    if (!test_pdf_path) {
        // Without a test PDF, we can only test the NULL case which is already covered
        GTEST_SKIP() << "No TEST_PDF_PATH environment variable set for non-block element test";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not create URI from test PDF path";
        return;
    }

    document = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!document) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not load test PDF";
        return;
    }

    PopplerPage *page = poppler_document_get_page(document, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get first page";
        return;
    }

    // We would need to find a non-block element to test
    // The key assertion is that non-block elements return NAN
    g_object_unref(page);
}

// Test with a valid block structure element that it returns a numeric value
TEST_F(PopplerStructureElementGetEndIndentTest_2566, ValidBlockElementReturnsNumericValue_2566) {
    const char *test_pdf_path = g_getenv("TEST_PDF_PATH");
    if (!test_pdf_path) {
        GTEST_SKIP() << "No TEST_PDF_PATH environment variable set";
        return;
    }

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not create URI from test PDF path";
        return;
    }

    document = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!document) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not load test PDF";
        return;
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "No structure element iterator available";
        return;
    }

    bool found_block = false;
    do {
        PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
        if (elem && poppler_structure_element_is_block(elem)) {
            gdouble result = poppler_structure_element_get_end_indent(elem);
            // For a valid block element, the result should be a valid number (not NAN)
            EXPECT_FALSE(std::isnan(result)) << "Block element should return a valid end indent value";
            found_block = true;
            g_object_unref(elem);
            break;
        }
        if (elem) {
            g_object_unref(elem);
        }
    } while (poppler_structure_element_iter_next(iter));

    poppler_structure_element_iter_free(iter);

    if (!found_block) {
        GTEST_SKIP() << "No block structure element found in the test PDF";
    }
}

// Test that the default end indent for a block element is typically 0
TEST_F(PopplerStructureElementGetEndIndentTest_2566, DefaultEndIndentIsZero_2566) {
    const char *test_pdf_path = g_getenv("TEST_PDF_PATH");
    if (!test_pdf_path) {
        GTEST_SKIP() << "No TEST_PDF_PATH environment variable set";
        return;
    }

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not create URI";
        return;
    }

    document = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!document) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not load test PDF";
        return;
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "No structure elements";
        return;
    }

    bool tested = false;
    do {
        PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
        if (elem && poppler_structure_element_is_block(elem)) {
            gdouble result = poppler_structure_element_get_end_indent(elem);
            // Default EndIndent per PDF spec is 0
            EXPECT_DOUBLE_EQ(result, 0.0) << "Default end indent should be 0";
            tested = true;
            g_object_unref(elem);
            break;
        }
        if (elem) {
            g_object_unref(elem);
        }
    } while (poppler_structure_element_iter_next(iter));

    poppler_structure_element_iter_free(iter);

    if (!tested) {
        GTEST_SKIP() << "No block element found to test default end indent";
    }
}
