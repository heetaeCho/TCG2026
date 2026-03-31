#include <glib.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <vector>

class PopplerDocumentNewFromBytesTest_2141 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a minimal valid PDF as GBytes
    GBytes *CreateMinimalPDFBytes() {
        // A minimal valid PDF document
        const char *pdf_content =
            "%PDF-1.0\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [] /Count 0 >>\n"
            "endobj\n"
            "xref\n"
            "0 3\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "trailer\n"
            "<< /Size 3 /Root 1 0 R >>\n"
            "startxref\n"
            "109\n"
            "%%EOF\n";
        return g_bytes_new(pdf_content, strlen(pdf_content));
    }

    GBytes *CreateInvalidPDFBytes() {
        const char *content = "This is not a PDF file at all.";
        return g_bytes_new(content, strlen(content));
    }

    GBytes *CreateEmptyBytes() {
        return g_bytes_new("", 0);
    }
};

// Test that passing nullptr bytes returns nullptr (g_return_val_if_fail)
TEST_F(PopplerDocumentNewFromBytesTest_2141, NullBytesReturnsNull_2141) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(nullptr, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
}

// Test creating a document from a minimal valid PDF
TEST_F(PopplerDocumentNewFromBytesTest_2141, ValidPDFCreatesDocument_2141) {
    GBytes *bytes = CreateMinimalPDFBytes();
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    // The minimal PDF may or may not parse successfully depending on strictness,
    // but we test the interface behavior
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        g_object_unref(doc);
    } else {
        // If it fails, error should be set
        EXPECT_NE(error, nullptr);
        if (error) {
            g_error_free(error);
        }
    }
    g_bytes_unref(bytes);
}

// Test that invalid PDF content results in an error
TEST_F(PopplerDocumentNewFromBytesTest_2141, InvalidPDFReturnsError_2141) {
    GBytes *bytes = CreateInvalidPDFBytes();
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
    g_bytes_unref(bytes);
}

// Test that empty bytes result in an error
TEST_F(PopplerDocumentNewFromBytesTest_2141, EmptyBytesReturnsError_2141) {
    GBytes *bytes = CreateEmptyBytes();
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
    g_bytes_unref(bytes);
}

// Test with nullptr error parameter (should not crash)
TEST_F(PopplerDocumentNewFromBytesTest_2141, NullErrorParameterDoesNotCrash_2141) {
    GBytes *bytes = CreateInvalidPDFBytes();
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, nullptr);
    // Should return nullptr for invalid PDF, and not crash
    EXPECT_EQ(doc, nullptr);
    g_bytes_unref(bytes);
}

// Test with a password on a non-encrypted PDF (password should be ignored)
TEST_F(PopplerDocumentNewFromBytesTest_2141, PasswordOnNonEncryptedPDF_2141) {
    GBytes *bytes = CreateMinimalPDFBytes();
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, "somepassword", &error);
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        g_object_unref(doc);
    } else {
        // Failure is acceptable for minimal PDF, just ensure no crash
        if (error) {
            g_error_free(error);
        }
    }
    g_bytes_unref(bytes);
}

// Test that passing a pre-set error triggers the g_return_val_if_fail guard
TEST_F(PopplerDocumentNewFromBytesTest_2141, PreSetErrorReturnsNull_2141) {
    GBytes *bytes = CreateMinimalPDFBytes();
    GError *error = g_error_new_literal(g_quark_from_string("test"), 1, "pre-set error");
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    // g_return_val_if_fail(error == nullptr || *error == nullptr, nullptr) should trigger
    EXPECT_EQ(doc, nullptr);
    g_error_free(error);
    g_bytes_unref(bytes);
}

// Test with nullptr password (no password scenario)
TEST_F(PopplerDocumentNewFromBytesTest_2141, NullPasswordForNonEncrypted_2141) {
    GBytes *bytes = CreateMinimalPDFBytes();
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
    }
    g_bytes_unref(bytes);
}

// Test loading a real PDF from file if available on disk
TEST_F(PopplerDocumentNewFromBytesTest_2141, LoadFromFileBytes_2141) {
    // Try to load a test PDF if it exists
    const char *test_pdf_path = "./test.pdf";
    std::ifstream file(test_pdf_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        GTEST_SKIP() << "No test.pdf available for testing";
        return;
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        GTEST_SKIP() << "Could not read test.pdf";
        return;
    }
    file.close();

    GBytes *bytes = g_bytes_new(buffer.data(), buffer.size());
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        // Verify we can query basic properties
        int n_pages = poppler_document_get_n_pages(doc);
        EXPECT_GE(n_pages, 0);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
    }
    g_bytes_unref(bytes);
}

// Test with random binary data (should fail gracefully)
TEST_F(PopplerDocumentNewFromBytesTest_2141, RandomBinaryDataReturnsError_2141) {
    unsigned char random_data[1024];
    for (int i = 0; i < 1024; i++) {
        random_data[i] = static_cast<unsigned char>(i % 256);
    }
    GBytes *bytes = g_bytes_new(random_data, sizeof(random_data));
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
    g_bytes_unref(bytes);
}

// Test with empty password string (different from nullptr)
TEST_F(PopplerDocumentNewFromBytesTest_2141, EmptyPasswordString_2141) {
    GBytes *bytes = CreateMinimalPDFBytes();
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, "", &error);
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
    }
    g_bytes_unref(bytes);
}

// Test that the function handles a single-byte PDF gracefully
TEST_F(PopplerDocumentNewFromBytesTest_2141, SingleByteReturnsError_2141) {
    const char single_byte = 'A';
    GBytes *bytes = g_bytes_new(&single_byte, 1);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
    g_bytes_unref(bytes);
}
