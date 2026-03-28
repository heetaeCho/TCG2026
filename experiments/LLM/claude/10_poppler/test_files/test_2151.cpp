#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <poppler-document.h>
#include <poppler.h>
}

#include <cstdlib>
#include <string>

class PopplerDocumentGetNPagesTest_2151 : public ::testing::Test {
protected:
    void SetUp() override {
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *document_;

    // Helper to find a test PDF file
    PopplerDocument *load_test_pdf(const char *filename) {
        GError *error = nullptr;
        gchar *uri = g_strdup_printf("file://%s", filename);
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *create_document_from_bytes(const unsigned char *data, gsize length) {
        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(data, length);
        PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
        g_bytes_unref(bytes);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

// Test that passing NULL returns 0 (g_return_val_if_fail check)
TEST_F(PopplerDocumentGetNPagesTest_2151, NullDocumentReturnsZero_2151) {
    // According to g_return_val_if_fail, passing NULL should return 0
    // This will emit a critical warning but should not crash
    int n_pages = poppler_document_get_n_pages(nullptr);
    EXPECT_EQ(n_pages, 0);
}

// Test that a valid single-page PDF returns the correct page count
TEST_F(PopplerDocumentGetNPagesTest_2151, ValidDocumentReturnsPositivePageCount_2151) {
    // Minimal valid PDF with 1 page
    // This is a minimal PDF 1.0 document
    const char *minimal_pdf =
        "%PDF-1.0\n"
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
        "190\n"
        "%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(minimal_pdf, strlen(minimal_pdf));
    document_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        int n_pages = poppler_document_get_n_pages(document_);
        EXPECT_EQ(n_pages, 1);
    } else {
        // If the minimal PDF doesn't parse, skip this test gracefully
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create a valid test PDF document";
    }
}

// Test with a multi-page PDF
TEST_F(PopplerDocumentGetNPagesTest_2151, MultiPageDocumentReturnsCorrectCount_2151) {
    // Minimal valid PDF with 2 pages
    const char *two_page_pdf =
        "%PDF-1.0\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R 4 0 R] /Count 2 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "271\n"
        "%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(two_page_pdf, strlen(two_page_pdf));
    document_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        int n_pages = poppler_document_get_n_pages(document_);
        EXPECT_EQ(n_pages, 2);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create a valid 2-page test PDF document";
    }
}

// Test that calling get_n_pages multiple times returns consistent results
TEST_F(PopplerDocumentGetNPagesTest_2151, ConsistentResultOnMultipleCalls_2151) {
    const char *minimal_pdf =
        "%PDF-1.0\n"
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
        "190\n"
        "%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(minimal_pdf, strlen(minimal_pdf));
    document_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        int n_pages_first = poppler_document_get_n_pages(document_);
        int n_pages_second = poppler_document_get_n_pages(document_);
        EXPECT_EQ(n_pages_first, n_pages_second);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create a valid test PDF document";
    }
}

// Test that the return value is non-negative for a valid document
TEST_F(PopplerDocumentGetNPagesTest_2151, ReturnValueIsNonNegative_2151) {
    const char *minimal_pdf =
        "%PDF-1.0\n"
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
        "190\n"
        "%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(minimal_pdf, strlen(minimal_pdf));
    document_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        int n_pages = poppler_document_get_n_pages(document_);
        EXPECT_GE(n_pages, 0);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create a valid test PDF document";
    }
}
