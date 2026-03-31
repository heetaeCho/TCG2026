#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstdio>
#include <cstdlib>
#include <string>

class PopplerDocumentGetPdfSubtypeTest_2203 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a minimal valid PDF file and return a PopplerDocument
    PopplerDocument *createDocumentFromMinimalPDF() {
        // Create a minimal PDF in a temporary file
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
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        char tmpfile[] = "/tmp/poppler_test_XXXXXX.pdf";
        int fd = mkstemps(tmpfile, 4);
        if (fd == -1) {
            return nullptr;
        }
        write(fd, pdf_content, strlen(pdf_content));
        close(fd);

        tmp_filename_ = tmpfile;

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
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

    void cleanupTempFile() {
        if (!tmp_filename_.empty()) {
            unlink(tmp_filename_.c_str());
            tmp_filename_.clear();
        }
    }

    std::string tmp_filename_;
};

// Test that calling poppler_document_get_pdf_subtype with NULL returns POPPLER_PDF_SUBTYPE_NONE
TEST_F(PopplerDocumentGetPdfSubtypeTest_2203, NullDocumentReturnsNone_2203) {
    // g_return_val_if_fail should catch NULL and return POPPLER_PDF_SUBTYPE_NONE
    // We need to suppress GLib critical warnings for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    PopplerPDFSubtype result = poppler_document_get_pdf_subtype(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, POPPLER_PDF_SUBTYPE_NONE);
}

// Test that a standard PDF (not a subtype) returns a valid enum value
TEST_F(PopplerDocumentGetPdfSubtypeTest_2203, StandardPdfReturnsValidSubtype_2203) {
    PopplerDocument *doc = createDocumentFromMinimalPDF();
    ASSERT_NE(doc, nullptr) << "Failed to create test document";

    PopplerPDFSubtype subtype = poppler_document_get_pdf_subtype(doc);

    // A minimal standard PDF should return either UNSET or NONE
    EXPECT_TRUE(subtype == POPPLER_PDF_SUBTYPE_UNSET ||
                subtype == POPPLER_PDF_SUBTYPE_NONE ||
                subtype == POPPLER_PDF_SUBTYPE_PDF_A ||
                subtype == POPPLER_PDF_SUBTYPE_PDF_E ||
                subtype == POPPLER_PDF_SUBTYPE_PDF_UA ||
                subtype == POPPLER_PDF_SUBTYPE_PDF_VT ||
                subtype == POPPLER_PDF_SUBTYPE_PDF_X)
        << "Returned subtype value: " << subtype;

    g_object_unref(doc);
    cleanupTempFile();
}

// Test that the return value is within the valid enum range
TEST_F(PopplerDocumentGetPdfSubtypeTest_2203, ReturnValueInValidEnumRange_2203) {
    PopplerDocument *doc = createDocumentFromMinimalPDF();
    ASSERT_NE(doc, nullptr) << "Failed to create test document";

    PopplerPDFSubtype subtype = poppler_document_get_pdf_subtype(doc);
    EXPECT_GE(static_cast<int>(subtype), static_cast<int>(POPPLER_PDF_SUBTYPE_UNSET));
    EXPECT_LE(static_cast<int>(subtype), static_cast<int>(POPPLER_PDF_SUBTYPE_NONE));

    g_object_unref(doc);
    cleanupTempFile();
}

// Test that calling the function multiple times on the same document returns consistent results
TEST_F(PopplerDocumentGetPdfSubtypeTest_2203, ConsistentResultOnMultipleCalls_2203) {
    PopplerDocument *doc = createDocumentFromMinimalPDF();
    ASSERT_NE(doc, nullptr) << "Failed to create test document";

    PopplerPDFSubtype subtype1 = poppler_document_get_pdf_subtype(doc);
    PopplerPDFSubtype subtype2 = poppler_document_get_pdf_subtype(doc);
    PopplerPDFSubtype subtype3 = poppler_document_get_pdf_subtype(doc);

    EXPECT_EQ(subtype1, subtype2);
    EXPECT_EQ(subtype2, subtype3);

    g_object_unref(doc);
    cleanupTempFile();
}

// Test with a minimal PDF that a plain PDF returns UNSET or NONE (no PDF/A, PDF/X, etc. metadata)
TEST_F(PopplerDocumentGetPdfSubtypeTest_2203, MinimalPdfNoSubtypeMetadata_2203) {
    PopplerDocument *doc = createDocumentFromMinimalPDF();
    ASSERT_NE(doc, nullptr) << "Failed to create test document";

    PopplerPDFSubtype subtype = poppler_document_get_pdf_subtype(doc);

    // A minimal PDF without any subtype conformance metadata should typically return UNSET or NONE
    EXPECT_TRUE(subtype == POPPLER_PDF_SUBTYPE_UNSET || subtype == POPPLER_PDF_SUBTYPE_NONE)
        << "Expected UNSET or NONE for a minimal PDF, got: " << subtype;

    g_object_unref(doc);
    cleanupTempFile();
}
