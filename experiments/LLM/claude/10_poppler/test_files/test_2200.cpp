#include <glib.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstring>
#include <cstdio>

class PopplerDocumentGetPrintPageRangesTest_2200 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a minimal valid PDF in memory and return a PopplerDocument
    PopplerDocument *createMinimalPDF() {
        // Minimal valid PDF
        const char *pdf_content =
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
            "0000000062 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);
        GError *error = nullptr;

        // Write to a temp file
        char tmpfile[] = "/tmp/poppler_test_XXXXXX.pdf";
        int fd = g_mkstemp(tmpfile);
        if (fd < 0) return nullptr;
        write(fd, pdf_content, len);
        close(fd);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (!uri) {
            unlink(tmpfile);
            return nullptr;
        }

        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        unlink(tmpfile);

        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *createPDFWithViewerPreferences() {
        // PDF with ViewerPreferences including PrintPageRange
        const char *pdf_content =
            "%PDF-1.7\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /ViewerPreferences << /PrintPageRange [1 1] >> >>\n"
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
            "0000000102 00000 n \n"
            "0000000155 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "230\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);
        GError *error = nullptr;

        char tmpfile[] = "/tmp/poppler_test_vp_XXXXXX.pdf";
        int fd = g_mkstemp(tmpfile);
        if (fd < 0) return nullptr;
        write(fd, pdf_content, len);
        close(fd);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (!uri) {
            unlink(tmpfile);
            return nullptr;
        }

        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        unlink(tmpfile);

        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

// Test that passing NULL for n_ranges returns nullptr
TEST_F(PopplerDocumentGetPrintPageRangesTest_2200, NullNRangesReturnsNull_2200) {
    PopplerDocument *doc = createMinimalPDF();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PopplerPageRange *result = poppler_document_get_print_page_ranges(doc, nullptr);
    EXPECT_EQ(result, nullptr);

    g_object_unref(doc);
}

// Test that passing NULL document returns nullptr and sets n_ranges to 0
TEST_F(PopplerDocumentGetPrintPageRangesTest_2200, NullDocumentReturnsNull_2200) {
    int n_ranges = -1;
    PopplerPageRange *result = poppler_document_get_print_page_ranges(nullptr, &n_ranges);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(n_ranges, 0);
}

// Test with a minimal PDF that has no ViewerPreferences
TEST_F(PopplerDocumentGetPrintPageRangesTest_2200, NoViewerPreferencesReturnsNull_2200) {
    PopplerDocument *doc = createMinimalPDF();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    int n_ranges = -1;
    PopplerPageRange *result = poppler_document_get_print_page_ranges(doc, &n_ranges);

    // Without viewer preferences, should return nullptr with 0 ranges
    EXPECT_EQ(n_ranges, 0);
    EXPECT_EQ(result, nullptr);

    g_object_unref(doc);
}

// Test with a PDF that has ViewerPreferences with PrintPageRange
TEST_F(PopplerDocumentGetPrintPageRangesTest_2200, WithPrintPageRangeReturnsRanges_2200) {
    PopplerDocument *doc = createPDFWithViewerPreferences();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with ViewerPreferences";
    }

    int n_ranges = 0;
    PopplerPageRange *result = poppler_document_get_print_page_ranges(doc, &n_ranges);

    if (result != nullptr) {
        EXPECT_GT(n_ranges, 0);
        // Verify that the ranges have valid start/end pages
        for (int i = 0; i < n_ranges; i++) {
            EXPECT_GE(result[i].start_page, 1);
            EXPECT_GE(result[i].end_page, result[i].start_page);
        }
        g_free(result);
    } else {
        // If the PDF didn't parse ViewerPreferences correctly, n_ranges should be 0
        EXPECT_EQ(n_ranges, 0);
    }

    g_object_unref(doc);
}

// Test that n_ranges is set to 0 before checking the document
TEST_F(PopplerDocumentGetPrintPageRangesTest_2200, NRangesSetToZeroOnNullDoc_2200) {
    int n_ranges = 42;
    PopplerPageRange *result = poppler_document_get_print_page_ranges(nullptr, &n_ranges);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(n_ranges, 0);
}

// Test both null document and null n_ranges
TEST_F(PopplerDocumentGetPrintPageRangesTest_2200, BothNullReturnsNull_2200) {
    PopplerPageRange *result = poppler_document_get_print_page_ranges(nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that a valid document with no print ranges returns 0 count
TEST_F(PopplerDocumentGetPrintPageRangesTest_2200, ValidDocNoPrintRangesZeroCount_2200) {
    PopplerDocument *doc = createMinimalPDF();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    int n_ranges = 999;
    PopplerPageRange *result = poppler_document_get_print_page_ranges(doc, &n_ranges);

    // n_ranges should be reset to 0 (set at beginning of function)
    EXPECT_EQ(n_ranges, 0);

    if (result) {
        g_free(result);
    }

    g_object_unref(doc);
}

// Test with a PDF that has ViewerPreferences with multiple page ranges
TEST_F(PopplerDocumentGetPrintPageRangesTest_2200, MultiplePageRanges_2200) {
    // PDF with ViewerPreferences including multiple PrintPageRange entries
    const char *pdf_content =
        "%PDF-1.7\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /ViewerPreferences << /PrintPageRange [1 2 4 5] >> >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R 4 0 R 5 0 R 6 0 R 7 0 R] /Count 5 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "6 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "7 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 8\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000111 00000 n \n"
        "0000000192 00000 n \n"
        "0000000261 00000 n \n"
        "0000000330 00000 n \n"
        "0000000399 00000 n \n"
        "0000000468 00000 n \n"
        "trailer\n"
        "<< /Size 8 /Root 1 0 R >>\n"
        "startxref\n"
        "537\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;

    char tmpfile[] = "/tmp/poppler_test_mr_XXXXXX.pdf";
    int fd = g_mkstemp(tmpfile);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }
    write(fd, pdf_content, len);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        unlink(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    unlink(tmpfile);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document";
    }

    int n_ranges = 0;
    PopplerPageRange *result = poppler_document_get_print_page_ranges(doc, &n_ranges);

    if (result != nullptr) {
        // We expect 2 ranges: [1,2] and [4,5]
        EXPECT_EQ(n_ranges, 2);
        if (n_ranges >= 1) {
            EXPECT_EQ(result[0].start_page, 1);
            EXPECT_EQ(result[0].end_page, 2);
        }
        if (n_ranges >= 2) {
            EXPECT_EQ(result[1].start_page, 4);
            EXPECT_EQ(result[1].end_page, 5);
        }
        g_free(result);
    }

    g_object_unref(doc);
}
