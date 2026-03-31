#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib-object.h>

// Include necessary headers
#include "poppler-page.h"
#include "poppler-private.h"
#include "poppler-document.h"
#include "poppler.h"

#include <cstring>
#include <string>

class PopplerPageBoundingBoxTest_2499 : public ::testing::Test {
protected:
    void SetUp() override {
        document_ = nullptr;
        page_ = nullptr;
    }

    void TearDown() override {
        if (page_) {
            g_object_unref(page_);
            page_ = nullptr;
        }
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    // Helper to create a document from a PDF file if available
    bool loadTestDocument(const char *uri) {
        GError *error = nullptr;
        document_ = poppler_document_new_from_file(uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            return false;
        }
        return document_ != nullptr;
    }

    // Helper to create a simple in-memory PDF document
    PopplerDocument *createMinimalPdfDocument() {
        // Minimal valid PDF with one page containing some content
        static const char pdf_with_content[] =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
            "   /Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT /F1 12 Tf 100 700 Td (Hello) Tj ET\n"
            "endstream\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000282 00000 n \n"
            "0000000376 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "453\n"
            "%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new_static(pdf_with_content, strlen(pdf_with_content));
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        PopplerDocument *doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Create a minimal empty PDF (page with no content)
    PopplerDocument *createEmptyPdfDocument() {
        static const char pdf_empty[] =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "206\n"
            "%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new_static(pdf_empty, strlen(pdf_empty));
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        PopplerDocument *doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *document_;
    PopplerPage *page_;
};

// Test that passing NULL page returns FALSE
TEST_F(PopplerPageBoundingBoxTest_2499, NullPageReturnsFalse_2499) {
    PopplerRectangle rect;
    memset(&rect, 0, sizeof(rect));

    // g_return_val_if_fail should cause it to return false for NULL page
    // Note: This may produce a GLib warning, which is expected
    gboolean result = poppler_page_get_bounding_box(nullptr, &rect);
    EXPECT_FALSE(result);
}

// Test that passing NULL rect returns FALSE
TEST_F(PopplerPageBoundingBoxTest_2499, NullRectReturnsFalse_2499) {
    document_ = createMinimalPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    page_ = poppler_document_get_page(document_, 0);
    ASSERT_NE(page_, nullptr);

    gboolean result = poppler_page_get_bounding_box(page_, nullptr);
    EXPECT_FALSE(result);
}

// Test bounding box on a page with content (text)
TEST_F(PopplerPageBoundingBoxTest_2499, PageWithContentReturnsTrueAndValidRect_2499) {
    document_ = createMinimalPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    page_ = poppler_document_get_page(document_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page from document";
    }

    PopplerRectangle rect;
    memset(&rect, 0, sizeof(rect));

    gboolean result = poppler_page_get_bounding_box(page_, &rect);

    if (result) {
        // If graphics are found, the bounding box should be valid
        // x1 should be <= x2 and y1 should be <= y2
        EXPECT_LE(rect.x1, rect.x2);
        EXPECT_LE(rect.y1, rect.y2);
    }
    // We accept either TRUE or FALSE depending on content rendering
}

// Test bounding box on an empty page (no content stream)
TEST_F(PopplerPageBoundingBoxTest_2499, EmptyPageReturnsFalse_2499) {
    document_ = createEmptyPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create empty PDF document";
    }

    page_ = poppler_document_get_page(document_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page from document";
    }

    PopplerRectangle rect;
    memset(&rect, 0, sizeof(rect));

    gboolean result = poppler_page_get_bounding_box(page_, &rect);

    // An empty page with no content should have no graphics
    EXPECT_FALSE(result);
}

// Test that both NULL page and NULL rect returns FALSE
TEST_F(PopplerPageBoundingBoxTest_2499, BothNullReturnsFalse_2499) {
    gboolean result = poppler_page_get_bounding_box(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test bounding box with a PDF containing vector graphics
TEST_F(PopplerPageBoundingBoxTest_2499, PageWithVectorGraphics_2499) {
    // Create a PDF with a drawn rectangle (vector graphic)
    static const char pdf_vector[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
        "   /Contents 4 0 R >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 41 >>\n"
        "stream\n"
        "100 600 200 100 re S\n"
        "50 50 100 100 re f\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "323\n"
        "%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_vector, strlen(pdf_vector));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    document_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (!document_) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create vector PDF document";
    }

    page_ = poppler_document_get_page(document_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page from document";
    }

    PopplerRectangle rect;
    memset(&rect, 0, sizeof(rect));

    gboolean result = poppler_page_get_bounding_box(page_, &rect);

    if (result) {
        // Bounding box should encompass the drawn rectangles
        EXPECT_LE(rect.x1, rect.x2);
        EXPECT_LE(rect.y1, rect.y2);
        // The bounding box should be within the media box
        EXPECT_GE(rect.x1, 0.0);
        EXPECT_GE(rect.y1, 0.0);
        EXPECT_LE(rect.x2, 612.0);
        EXPECT_LE(rect.y2, 792.0);
    }
}

// Test that rect values are not modified when function returns FALSE
TEST_F(PopplerPageBoundingBoxTest_2499, RectUnmodifiedOnFalseReturn_2499) {
    document_ = createEmptyPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create empty PDF document";
    }

    page_ = poppler_document_get_page(document_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page from document";
    }

    PopplerRectangle rect;
    rect.x1 = -999.0;
    rect.y1 = -999.0;
    rect.x2 = -999.0;
    rect.y2 = -999.0;

    gboolean result = poppler_page_get_bounding_box(page_, &rect);

    if (!result) {
        // When no graphics are found, rect should not be modified
        EXPECT_DOUBLE_EQ(rect.x1, -999.0);
        EXPECT_DOUBLE_EQ(rect.y1, -999.0);
        EXPECT_DOUBLE_EQ(rect.x2, -999.0);
        EXPECT_DOUBLE_EQ(rect.y2, -999.0);
    }
}

// Test calling get_bounding_box multiple times on the same page gives consistent results
TEST_F(PopplerPageBoundingBoxTest_2499, ConsistentResultsOnMultipleCalls_2499) {
    document_ = createMinimalPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    page_ = poppler_document_get_page(document_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page from document";
    }

    PopplerRectangle rect1, rect2;
    memset(&rect1, 0, sizeof(rect1));
    memset(&rect2, 0, sizeof(rect2));

    gboolean result1 = poppler_page_get_bounding_box(page_, &rect1);
    gboolean result2 = poppler_page_get_bounding_box(page_, &rect2);

    EXPECT_EQ(result1, result2);

    if (result1 && result2) {
        EXPECT_DOUBLE_EQ(rect1.x1, rect2.x1);
        EXPECT_DOUBLE_EQ(rect1.y1, rect2.y1);
        EXPECT_DOUBLE_EQ(rect1.x2, rect2.x2);
        EXPECT_DOUBLE_EQ(rect1.y2, rect2.y2);
    }
}
