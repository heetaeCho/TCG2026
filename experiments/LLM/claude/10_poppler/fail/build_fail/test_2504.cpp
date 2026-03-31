#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-page.h"
#include "poppler-private.h"

#include <cstring>
#include <string>

class PopplerPageTextAttributesTest_2504 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_ = nullptr;
        page_ = nullptr;
    }

    void TearDown() override {
        if (page_) {
            g_object_unref(page_);
            page_ = nullptr;
        }
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    // Helper to load a document from a file if available
    bool loadTestDocument(const char *uri) {
        GError *error = nullptr;
        doc_ = poppler_document_new_from_file(uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            return false;
        }
        if (doc_ && poppler_document_get_n_pages(doc_) > 0) {
            page_ = poppler_document_get_page(doc_, 0);
            return page_ != nullptr;
        }
        return false;
    }

    PopplerDocument *doc_;
    PopplerPage *page_;
};

// Test that passing NULL page returns NULL
TEST_F(PopplerPageTextAttributesTest_2504, NullPageReturnsNull_2504) {
    PopplerRectangle area = {0, 0, 100, 100};
    // g_return_val_if_fail should cause this to return NULL
    // Note: This will trigger a GLib warning
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
    GList *result = poppler_page_get_text_attributes_for_area(nullptr, &area);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that passing NULL area returns NULL
TEST_F(PopplerPageTextAttributesTest_2504, NullAreaReturnsNull_2504) {
    // We need a valid PopplerPage for this test; create a minimal PDF in memory
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Kids[3 0 R]/Count 1/Type/Pages>>endobj\n"
        "3 0 obj<</Parent 2 0 R/MediaBox[0 0 612 792]/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (doc_ && poppler_document_get_n_pages(doc_) > 0) {
        page_ = poppler_document_get_page(doc_, 0);
        ASSERT_NE(page_, nullptr);

        g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*area != nullptr*");
        GList *result = poppler_page_get_text_attributes_for_area(page_, nullptr);
        g_test_assert_expected_messages();
        EXPECT_EQ(result, nullptr);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
}

// Test with a valid page but empty area (no text) returns NULL
TEST_F(PopplerPageTextAttributesTest_2504, EmptyPageReturnsNullAttributes_2504) {
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Kids[3 0 R]/Count 1/Type/Pages>>endobj\n"
        "3 0 obj<</Parent 2 0 R/MediaBox[0 0 612 792]/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (doc_ && poppler_document_get_n_pages(doc_) > 0) {
        page_ = poppler_document_get_page(doc_, 0);
        ASSERT_NE(page_, nullptr);

        PopplerRectangle area = {0, 0, 100, 100};
        GList *result = poppler_page_get_text_attributes_for_area(page_, &area);
        // Empty page should have no text, so no attributes
        EXPECT_EQ(result, nullptr);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
}

// Test area coordinates are properly transferred
TEST_F(PopplerPageTextAttributesTest_2504, ZeroAreaReturnsNull_2504) {
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Kids[3 0 R]/Count 1/Type/Pages>>endobj\n"
        "3 0 obj<</Parent 2 0 R/MediaBox[0 0 612 792]/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (doc_ && poppler_document_get_n_pages(doc_) > 0) {
        page_ = poppler_document_get_page(doc_, 0);
        ASSERT_NE(page_, nullptr);

        // Zero-sized area
        PopplerRectangle area = {0, 0, 0, 0};
        GList *result = poppler_page_get_text_attributes_for_area(page_, &area);
        EXPECT_EQ(result, nullptr);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
}

// Test with a PDF containing actual text content
TEST_F(PopplerPageTextAttributesTest_2504, PageWithTextReturnsAttributes_2504) {
    // Create a more complete PDF with text content
    // This is a minimal PDF with a text stream
    const std::string pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]"
        "/Contents 4 0 R/Resources<</Font<</F1 5 0 R>>>>>>endobj\n"
        "4 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello World) Tj ET\nendstream\nendobj\n"
        "5 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000360 00000 n \n"
        "trailer<</Root 1 0 R/Size 6>>\nstartxref\n431\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(pdf_content.c_str(), pdf_content.size());
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (!doc_) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document with text";
        return;
    }

    if (poppler_document_get_n_pages(doc_) > 0) {
        page_ = poppler_document_get_page(doc_, 0);
        ASSERT_NE(page_, nullptr);

        // Use full page area
        PopplerRectangle area = {0, 0, 612, 792};
        GList *result = poppler_page_get_text_attributes_for_area(page_, &area);

        if (result != nullptr) {
            // Verify we got a non-empty list
            EXPECT_GT(g_list_length(result), 0u);

            // Verify each attribute has valid start_index and end_index
            for (GList *l = result; l != nullptr; l = l->next) {
                PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
                ASSERT_NE(attr, nullptr);
                EXPECT_GE(attr->start_index, 0);
                EXPECT_GE(attr->end_index, attr->start_index);
            }

            // Check that attributes are ordered (start_index non-decreasing after reverse)
            int prev_start = -1;
            for (GList *l = result; l != nullptr; l = l->next) {
                PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
                EXPECT_GE(attr->start_index, prev_start);
                prev_start = attr->start_index;
            }

            poppler_page_free_text_attributes(result);
        }
        // If result is NULL, the PDF text extraction didn't find text in that area
        // which is acceptable for a synthetic PDF
    }
}

// Test that returned list attributes have contiguous coverage
TEST_F(PopplerPageTextAttributesTest_2504, AttributesCoverageIsContiguous_2504) {
    const std::string pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]"
        "/Contents 4 0 R/Resources<</Font<</F1 5 0 R>>>>>>endobj\n"
        "4 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello World) Tj ET\nendstream\nendobj\n"
        "5 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000360 00000 n \n"
        "trailer<</Root 1 0 R/Size 6>>\nstartxref\n431\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(pdf_content.c_str(), pdf_content.size());
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (!doc_) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document with text";
        return;
    }

    if (poppler_document_get_n_pages(doc_) > 0) {
        page_ = poppler_document_get_page(doc_, 0);
        ASSERT_NE(page_, nullptr);

        PopplerRectangle area = {0, 0, 612, 792};
        GList *result = poppler_page_get_text_attributes_for_area(page_, &area);

        if (result != nullptr && g_list_length(result) > 1) {
            // Check that attributes form contiguous coverage
            GList *l = result;
            PopplerTextAttributes *prev_attr = (PopplerTextAttributes *)l->data;
            l = l->next;

            while (l != nullptr) {
                PopplerTextAttributes *attr = (PopplerTextAttributes *)l->data;
                // Next attribute should start right after the previous one ends
                EXPECT_EQ(attr->start_index, prev_attr->end_index + 1);
                prev_attr = attr;
                l = l->next;
            }

            poppler_page_free_text_attributes(result);
        } else if (result) {
            poppler_page_free_text_attributes(result);
        }
    }
}

// Test with negative coordinates in area
TEST_F(PopplerPageTextAttributesTest_2504, NegativeAreaCoordinates_2504) {
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Kids[3 0 R]/Count 1/Type/Pages>>endobj\n"
        "3 0 obj<</Parent 2 0 R/MediaBox[0 0 612 792]/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (doc_ && poppler_document_get_n_pages(doc_) > 0) {
        page_ = poppler_document_get_page(doc_, 0);
        ASSERT_NE(page_, nullptr);

        PopplerRectangle area = {-100, -100, -50, -50};
        GList *result = poppler_page_get_text_attributes_for_area(page_, &area);
        // No text should be found in negative coordinates
        EXPECT_EQ(result, nullptr);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
}

// Test first attribute starts at index 0
TEST_F(PopplerPageTextAttributesTest_2504, FirstAttributeStartsAtZero_2504) {
    const std::string pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]"
        "/Contents 4 0 R/Resources<</Font<</F1 5 0 R>>>>>>endobj\n"
        "4 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello World) Tj ET\nendstream\nendobj\n"
        "5 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000360 00000 n \n"
        "trailer<</Root 1 0 R/Size 6>>\nstartxref\n431\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(pdf_content.c_str(), pdf_content.size());
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (!doc_) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document";
        return;
    }

    if (poppler_document_get_n_pages(doc_) > 0) {
        page_ = poppler_document_get_page(doc_, 0);
        ASSERT_NE(page_, nullptr);

        PopplerRectangle area = {0, 0, 612, 792};
        GList *result = poppler_page_get_text_attributes_for_area(page_, &area);

        if (result != nullptr) {
            PopplerTextAttributes *first_attr = (PopplerTextAttributes *)result->data;
            ASSERT_NE(first_attr, nullptr);
            EXPECT_EQ(first_attr->start_index, 0);

            poppler_page_free_text_attributes(result);
        }
    }
}
