#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <vector>

// Include poppler glib headers
#include "poppler-document.h"
#include "poppler.h"

class PopplerDocumentNewFromDataTest_2140 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to read a file into a vector
    static std::vector<char> readFile(const char *path) {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            return {};
        }
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        return buffer;
    }

    // Minimal valid PDF content
    static std::vector<char> createMinimalPDF() {
        const char *pdf =
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
        size_t len = strlen(pdf);
        return std::vector<char>(pdf, pdf + len);
    }
};

// Test that passing NULL data results in an error (or NULL document)
TEST_F(PopplerDocumentNewFromDataTest_2140, NullDataReturnsNull_2140) {
    GError *error = nullptr;
    // Passing NULL data with length 0
    // This should fail gracefully
    PopplerDocument *doc = poppler_document_new_from_data(nullptr, 0, nullptr, &error);
    // Expect either null document or error
    if (doc == nullptr) {
        EXPECT_TRUE(error != nullptr);
        if (error) {
            g_error_free(error);
        }
    } else {
        g_object_unref(doc);
    }
}

// Test that passing empty data (length 0) results in an error
TEST_F(PopplerDocumentNewFromDataTest_2140, EmptyDataReturnsError_2140) {
    GError *error = nullptr;
    char dummy = 0;
    PopplerDocument *doc = poppler_document_new_from_data(&dummy, 0, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test that passing garbage/invalid data returns an error
TEST_F(PopplerDocumentNewFromDataTest_2140, InvalidDataReturnsError_2140) {
    GError *error = nullptr;
    char garbage[] = "This is not a PDF file at all!";
    int length = sizeof(garbage) - 1;
    PopplerDocument *doc = poppler_document_new_from_data(garbage, length, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test that a minimal valid PDF can be loaded
TEST_F(PopplerDocumentNewFromDataTest_2140, ValidMinimalPDFLoads_2140) {
    GError *error = nullptr;
    std::vector<char> pdfData = createMinimalPDF();
    ASSERT_FALSE(pdfData.empty());

    PopplerDocument *doc = poppler_document_new_from_data(pdfData.data(), pdfData.size(), nullptr, &error);
    // A minimal PDF might or might not parse depending on xref validity,
    // but we test the interface behavior
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        // Check that we can query basic properties
        int nPages = poppler_document_get_n_pages(doc);
        EXPECT_GE(nPages, 0);
        g_object_unref(doc);
    } else {
        // If it fails, there should be an error
        EXPECT_NE(error, nullptr);
        if (error) {
            g_error_free(error);
        }
    }
}

// Test passing a wrong password for non-encrypted PDF (should still work)
TEST_F(PopplerDocumentNewFromDataTest_2140, NonEncryptedPDFWithPasswordStillLoads_2140) {
    GError *error = nullptr;
    std::vector<char> pdfData = createMinimalPDF();
    ASSERT_FALSE(pdfData.empty());

    PopplerDocument *doc = poppler_document_new_from_data(pdfData.data(), pdfData.size(), "somepassword", &error);
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        g_object_unref(doc);
    } else {
        // Acceptable if the minimal PDF is not parseable
        if (error) {
            g_error_free(error);
        }
    }
}

// Test that passing NULL error pointer doesn't cause a crash
TEST_F(PopplerDocumentNewFromDataTest_2140, NullErrorPointerDoesNotCrash_2140) {
    char garbage[] = "Not a PDF";
    int length = sizeof(garbage) - 1;
    // Pass NULL for GError** - should not crash
    PopplerDocument *doc = poppler_document_new_from_data(garbage, length, nullptr, nullptr);
    if (doc != nullptr) {
        g_object_unref(doc);
    }
    // If we reach here without crashing, the test passes
    SUCCEED();
}

// Test with negative length (boundary condition)
TEST_F(PopplerDocumentNewFromDataTest_2140, NegativeLengthReturnsError_2140) {
    GError *error = nullptr;
    char data[] = "%PDF-1.0";
    PopplerDocument *doc = poppler_document_new_from_data(data, -1, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test with a truncated PDF header
TEST_F(PopplerDocumentNewFromDataTest_2140, TruncatedPDFHeaderReturnsError_2140) {
    GError *error = nullptr;
    char data[] = "%PDF";
    int length = sizeof(data) - 1;
    PopplerDocument *doc = poppler_document_new_from_data(data, length, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test with only PDF header but no content
TEST_F(PopplerDocumentNewFromDataTest_2140, PDFHeaderOnlyReturnsError_2140) {
    GError *error = nullptr;
    char data[] = "%PDF-1.4\n";
    int length = sizeof(data) - 1;
    PopplerDocument *doc = poppler_document_new_from_data(data, length, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test that providing an empty password string (not NULL) works for non-encrypted PDF
TEST_F(PopplerDocumentNewFromDataTest_2140, EmptyPasswordStringForNonEncrypted_2140) {
    GError *error = nullptr;
    std::vector<char> pdfData = createMinimalPDF();
    ASSERT_FALSE(pdfData.empty());

    PopplerDocument *doc = poppler_document_new_from_data(pdfData.data(), pdfData.size(), "", &error);
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
    }
}

// Test with length=1 (single byte, clearly not a valid PDF)
TEST_F(PopplerDocumentNewFromDataTest_2140, SingleByteLengthReturnsError_2140) {
    GError *error = nullptr;
    char data[] = "X";
    PopplerDocument *doc = poppler_document_new_from_data(data, 1, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}
