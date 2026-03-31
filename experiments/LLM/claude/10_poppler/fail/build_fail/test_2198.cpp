#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>

// Include poppler glib headers
#include "poppler-document.h"
#include "poppler.h"

class PopplerDocumentPrintDuplexTest_2198 : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}

    // Helper to create a minimal PDF in a temp file and return a PopplerDocument
    PopplerDocument *createPdfWithViewerPreferences(const std::string &duplexValue) {
        // Create a minimal PDF with ViewerPreferences containing the given Duplex value
        std::string pdf;
        pdf += "%PDF-1.7\n";

        // Object 1: Catalog
        std::string catalogObj;
        if (!duplexValue.empty()) {
            catalogObj = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R /ViewerPreferences << /Duplex /" + duplexValue + " >> >>\nendobj\n";
        } else {
            catalogObj = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        }

        // Object 2: Pages
        std::string pagesObj = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";

        // Object 3: Page
        std::string pageObj = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        size_t offset1 = pdf.size();
        pdf += catalogObj;
        size_t offset2 = pdf.size();
        pdf += pagesObj;
        size_t offset3 = pdf.size();
        pdf += pageObj;

        size_t xrefOffset = pdf.size();
        pdf += "xref\n";
        pdf += "0 4\n";
        pdf += "0000000000 65535 f \n";

        char buf[64];
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset1);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset2);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset3);
        pdf += buf;

        pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        pdf += "startxref\n";
        snprintf(buf, sizeof(buf), "%zu\n", xrefOffset);
        pdf += buf;
        pdf += "%%EOF\n";

        // Write to temp file
        char tmpName[] = "/tmp/poppler_test_XXXXXX.pdf";
        int fd = mkstemps(tmpName, 4);
        if (fd < 0) {
            return nullptr;
        }
        write(fd, pdf.c_str(), pdf.size());
        close(fd);

        tempFiles_.push_back(tmpName);

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpName, nullptr, &error);
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

    std::vector<std::string> tempFiles_;

    void cleanupTempFiles() {
        for (const auto &f : tempFiles_) {
            unlink(f.c_str());
        }
        tempFiles_.clear();
    }
};

// Test that a PDF with no ViewerPreferences returns POPPLER_PRINT_DUPLEX_NONE
TEST_F(PopplerDocumentPrintDuplexTest_2198, NoViewerPreferencesReturnsNone_2198) {
    PopplerDocument *doc = createPdfWithViewerPreferences("");
    if (doc) {
        PopplerPrintDuplex duplex = poppler_document_get_print_duplex(doc);
        EXPECT_EQ(duplex, POPPLER_PRINT_DUPLEX_NONE);
        g_object_unref(doc);
    }
    cleanupTempFiles();
}

// Test that a PDF with Duplex /None returns POPPLER_PRINT_DUPLEX_NONE
TEST_F(PopplerDocumentPrintDuplexTest_2198, DuplexNoneReturnsNone_2198) {
    PopplerDocument *doc = createPdfWithViewerPreferences("None");
    if (doc) {
        PopplerPrintDuplex duplex = poppler_document_get_print_duplex(doc);
        EXPECT_EQ(duplex, POPPLER_PRINT_DUPLEX_NONE);
        g_object_unref(doc);
    }
    cleanupTempFiles();
}

// Test that a PDF with Duplex /Simplex returns POPPLER_PRINT_DUPLEX_SIMPLEX
TEST_F(PopplerDocumentPrintDuplexTest_2198, DuplexSimplexReturnsSimplex_2198) {
    PopplerDocument *doc = createPdfWithViewerPreferences("Simplex");
    if (doc) {
        PopplerPrintDuplex duplex = poppler_document_get_print_duplex(doc);
        EXPECT_EQ(duplex, POPPLER_PRINT_DUPLEX_SIMPLEX);
        g_object_unref(doc);
    }
    cleanupTempFiles();
}

// Test that a PDF with Duplex /DuplexFlipShortEdge returns POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_SHORT_EDGE
TEST_F(PopplerDocumentPrintDuplexTest_2198, DuplexFlipShortEdgeReturnsFlipShortEdge_2198) {
    PopplerDocument *doc = createPdfWithViewerPreferences("DuplexFlipShortEdge");
    if (doc) {
        PopplerPrintDuplex duplex = poppler_document_get_print_duplex(doc);
        EXPECT_EQ(duplex, POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_SHORT_EDGE);
        g_object_unref(doc);
    }
    cleanupTempFiles();
}

// Test that a PDF with Duplex /DuplexFlipLongEdge returns POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_LONG_EDGE
TEST_F(PopplerDocumentPrintDuplexTest_2198, DuplexFlipLongEdgeReturnsFlipLongEdge_2198) {
    PopplerDocument *doc = createPdfWithViewerPreferences("DuplexFlipLongEdge");
    if (doc) {
        PopplerPrintDuplex duplex = poppler_document_get_print_duplex(doc);
        EXPECT_EQ(duplex, POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_LONG_EDGE);
        g_object_unref(doc);
    }
    cleanupTempFiles();
}

// Test that passing NULL document returns POPPLER_PRINT_DUPLEX_NONE (g_return_val_if_fail)
TEST_F(PopplerDocumentPrintDuplexTest_2198, NullDocumentReturnsNone_2198) {
    // g_return_val_if_fail with a non-POPPLER_IS_DOCUMENT should return the default
    // This tests the error/boundary case of a null pointer
    // Note: This may produce a g_critical warning, which is expected
    PopplerPrintDuplex duplex = poppler_document_get_print_duplex(nullptr);
    EXPECT_EQ(duplex, POPPLER_PRINT_DUPLEX_NONE);
}

// Test enum values are as expected
TEST_F(PopplerDocumentPrintDuplexTest_2198, EnumValuesCorrect_2198) {
    EXPECT_EQ(POPPLER_PRINT_DUPLEX_NONE, 0);
    EXPECT_EQ(POPPLER_PRINT_DUPLEX_SIMPLEX, 1);
    EXPECT_EQ(POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_SHORT_EDGE, 2);
    EXPECT_EQ(POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_LONG_EDGE, 3);
}

// Test that calling the function multiple times on the same document returns consistent results
TEST_F(PopplerDocumentPrintDuplexTest_2198, ConsistentResults_2198) {
    PopplerDocument *doc = createPdfWithViewerPreferences("Simplex");
    if (doc) {
        PopplerPrintDuplex duplex1 = poppler_document_get_print_duplex(doc);
        PopplerPrintDuplex duplex2 = poppler_document_get_print_duplex(doc);
        EXPECT_EQ(duplex1, duplex2);
        EXPECT_EQ(duplex1, POPPLER_PRINT_DUPLEX_SIMPLEX);
        g_object_unref(doc);
    }
    cleanupTempFiles();
}
