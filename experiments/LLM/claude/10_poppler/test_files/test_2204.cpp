#include <glib-object.h>
#include <glib.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>

class PopplerDocumentGetPdfPartTest_2204 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a minimal valid PDF file and return a PopplerDocument
    PopplerDocument *createMinimalPdfDocument(const std::string &tmpPath) {
        // Create a minimal PDF 1.4 file
        std::ofstream ofs(tmpPath, std::ios::binary);
        ofs << "%PDF-1.4\n";
        ofs << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        ofs << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        ofs << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        ofs << "xref\n0 4\n";
        ofs << "0000000000 65535 f \n";
        ofs << "0000000009 00000 n \n";
        ofs << "0000000058 00000 n \n";
        ofs << "0000000115 00000 n \n";
        ofs << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        ofs << "startxref\n190\n%%EOF\n";
        ofs.close();

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpPath.c_str(), nullptr, &error);
        if (!uri) {
            if (error) {
                g_error_free(error);
            }
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        return doc;
    }
};

// Test that passing NULL returns POPPLER_PDF_SUBTYPE_PART_NONE
TEST_F(PopplerDocumentGetPdfPartTest_2204, NullDocumentReturnsNone_2204) {
    // Passing NULL should trigger g_return_val_if_fail and return POPPLER_PDF_SUBTYPE_PART_NONE
    PopplerPDFPart result = poppler_document_get_pdf_part(nullptr);
    EXPECT_EQ(result, POPPLER_PDF_SUBTYPE_PART_NONE);
}

// Test that a valid minimal PDF returns a valid PopplerPDFPart enum value
TEST_F(PopplerDocumentGetPdfPartTest_2204, ValidDocumentReturnsValidPart_2204) {
    std::string tmpPath = "/tmp/test_poppler_part_2204.pdf";
    PopplerDocument *doc = createMinimalPdfDocument(tmpPath);
    if (!doc) {
        // If we can't create the document, skip
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PopplerPDFPart result = poppler_document_get_pdf_part(doc);
    // The result should be a valid enum value
    EXPECT_GE(result, POPPLER_PDF_SUBTYPE_PART_UNSET);
    EXPECT_LE(result, POPPLER_PDF_SUBTYPE_PART_NONE);

    g_object_unref(doc);
    std::remove(tmpPath.c_str());
}

// Test that a regular PDF (not PDF/A, PDF/X etc.) returns UNSET or NONE for part
TEST_F(PopplerDocumentGetPdfPartTest_2204, RegularPdfReturnsUnsetOrNone_2204) {
    std::string tmpPath = "/tmp/test_poppler_regular_part_2204.pdf";
    PopplerDocument *doc = createMinimalPdfDocument(tmpPath);
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PopplerPDFPart result = poppler_document_get_pdf_part(doc);
    // A minimal PDF without subtype conformance should return UNSET or NONE
    EXPECT_TRUE(result == POPPLER_PDF_SUBTYPE_PART_UNSET || result == POPPLER_PDF_SUBTYPE_PART_NONE);

    g_object_unref(doc);
    std::remove(tmpPath.c_str());
}

// Test that the returned value is within the defined enum range
TEST_F(PopplerDocumentGetPdfPartTest_2204, ReturnValueWithinEnumRange_2204) {
    std::string tmpPath = "/tmp/test_poppler_range_part_2204.pdf";
    PopplerDocument *doc = createMinimalPdfDocument(tmpPath);
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PopplerPDFPart result = poppler_document_get_pdf_part(doc);
    int val = static_cast<int>(result);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 9);

    g_object_unref(doc);
    std::remove(tmpPath.c_str());
}

// Test calling the function multiple times on the same document returns consistent results
TEST_F(PopplerDocumentGetPdfPartTest_2204, ConsistentResultsOnMultipleCalls_2204) {
    std::string tmpPath = "/tmp/test_poppler_consistent_part_2204.pdf";
    PopplerDocument *doc = createMinimalPdfDocument(tmpPath);
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PopplerPDFPart result1 = poppler_document_get_pdf_part(doc);
    PopplerPDFPart result2 = poppler_document_get_pdf_part(doc);
    PopplerPDFPart result3 = poppler_document_get_pdf_part(doc);

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);

    g_object_unref(doc);
    std::remove(tmpPath.c_str());
}
