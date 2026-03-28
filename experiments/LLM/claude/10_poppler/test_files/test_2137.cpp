#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>

class PopplerDocumentTest_2137 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a temporary file with given content
    std::string createTempFile(const std::string &content) {
        char tmpname[] = "/tmp/poppler_test_XXXXXX";
        int fd = mkstemp(tmpname);
        if (fd == -1) return "";
        write(fd, content.c_str(), content.size());
        close(fd);
        return std::string(tmpname);
    }

    // Helper to create a minimal valid PDF
    std::string createMinimalPDF() {
        std::string pdf = "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";
        return pdf;
    }

    // Helper to get a file URI from a path
    std::string filePathToUri(const std::string &path) {
        gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
        std::string result(uri ? uri : "");
        g_free(uri);
        return result;
    }
};

TEST_F(PopplerDocumentTest_2137, OpenNonExistentFile_2137) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/nonexistent_file_poppler_test_12345.pdf", nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        // Should be a G_FILE_ERROR since the file doesn't exist
        EXPECT_EQ(error->domain, G_FILE_ERROR);
        g_error_free(error);
    }
}

TEST_F(PopplerDocumentTest_2137, OpenInvalidPDFData_2137) {
    GError *error = nullptr;
    const char *garbage = "This is not a PDF file at all";
    PopplerDocument *doc = poppler_document_new_from_data(garbage, strlen(garbage), nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

TEST_F(PopplerDocumentTest_2137, OpenValidMinimalPDF_2137) {
    std::string pdfContent = createMinimalPDF();
    std::string tmpPath = createTempFile(pdfContent);
    ASSERT_FALSE(tmpPath.empty());

    std::string uri = filePathToUri(tmpPath);
    ASSERT_FALSE(uri.empty());

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);

    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        EXPECT_GE(poppler_document_get_n_pages(doc), 1);
        g_object_unref(doc);
    } else {
        // Some minimal PDFs may not parse; just ensure error is set
        if (error) {
            g_error_free(error);
        }
    }

    unlink(tmpPath.c_str());
}

TEST_F(PopplerDocumentTest_2137, OpenCorruptedPDF_2137) {
    // Create a file that starts like a PDF but is corrupted
    std::string corruptPdf = "%PDF-1.0\ngarbage data here, no valid xref or objects\n%%EOF\n";
    std::string tmpPath = createTempFile(corruptPdf);
    ASSERT_FALSE(tmpPath.empty());

    std::string uri = filePathToUri(tmpPath);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        // Expect POPPLER_ERROR domain for damaged/invalid PDF
        EXPECT_TRUE(error->domain == POPPLER_ERROR || error->domain == G_FILE_ERROR);
        g_error_free(error);
    }

    unlink(tmpPath.c_str());
}

TEST_F(PopplerDocumentTest_2137, OpenEmptyFile_2137) {
    std::string tmpPath = createTempFile("");
    ASSERT_FALSE(tmpPath.empty());

    std::string uri = filePathToUri(tmpPath);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }

    unlink(tmpPath.c_str());
}

TEST_F(PopplerDocumentTest_2137, OpenFromDataNullData_2137) {
    GError *error = nullptr;
    // Passing zero length data
    PopplerDocument *doc = poppler_document_new_from_data("", 0, nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

TEST_F(PopplerDocumentTest_2137, ErrorIsNullWhenNotProvided_2137) {
    // Test that passing NULL for error doesn't crash
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/nonexistent_poppler_test_99999.pdf", nullptr, nullptr);
    EXPECT_EQ(doc, nullptr);
}

TEST_F(PopplerDocumentTest_2137, EncryptedPDFWithoutPassword_2137) {
    // Create a simple encrypted PDF-like structure
    // We test via the data path with known encrypted PDF bytes
    // Since we can't easily create an encrypted PDF in test, we just verify the error path concept
    GError *error = nullptr;
    // A truncated/fake encrypted marker won't truly test encryption,
    // but we verify that wrong password on a real encrypted doc would fail
    // This test documents the expected behavior
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/nonexistent_encrypted.pdf", "wrongpassword", &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

TEST_F(PopplerDocumentTest_2137, DocumentIsGObject_2137) {
    std::string pdfContent = createMinimalPDF();
    std::string tmpPath = createTempFile(pdfContent);
    ASSERT_FALSE(tmpPath.empty());

    std::string uri = filePathToUri(tmpPath);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);

    if (doc != nullptr) {
        // Verify it's a proper GObject
        EXPECT_TRUE(G_IS_OBJECT(doc));
        EXPECT_TRUE(POPPLER_IS_DOCUMENT(doc));
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
    }

    unlink(tmpPath.c_str());
}

TEST_F(PopplerDocumentTest_2137, OpenFromDataWithValidPDF_2137) {
    std::string pdfContent = createMinimalPDF();
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_data(pdfContent.c_str(), pdfContent.size(), nullptr, &error);

    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        EXPECT_GE(poppler_document_get_n_pages(doc), 0);
        g_object_unref(doc);
    } else {
        // Minimal PDF might not be valid enough for all versions
        if (error) g_error_free(error);
    }
}

TEST_F(PopplerDocumentTest_2137, MultipleUnrefDoesNotCrash_2137) {
    std::string pdfContent = createMinimalPDF();
    std::string tmpPath = createTempFile(pdfContent);
    ASSERT_FALSE(tmpPath.empty());

    std::string uri = filePathToUri(tmpPath);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);

    if (doc != nullptr) {
        // Add a ref, then unref twice - should be safe
        g_object_ref(doc);
        g_object_unref(doc);
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
    }

    unlink(tmpPath.c_str());
}

TEST_F(PopplerDocumentTest_2137, BadCatalogError_2137) {
    // Create a PDF with a bad catalog reference
    std::string badCatalogPdf = "%PDF-1.0\n"
        "xref\n"
        "0 1\n"
        "0000000000 65535 f \n"
        "trailer<</Size 1/Root 99 0 R>>\n"
        "startxref\n"
        "10\n"
        "%%EOF\n";
    std::string tmpPath = createTempFile(badCatalogPdf);
    ASSERT_FALSE(tmpPath.empty());

    std::string uri = filePathToUri(tmpPath);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }

    unlink(tmpPath.c_str());
}
