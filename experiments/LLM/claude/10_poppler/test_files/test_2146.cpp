#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>

// Include poppler glib headers
#include "poppler-document.h"

class PopplerDocumentSaveTest_2146 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    std::string test_pdf_path;
    std::string test_pdf_uri;

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        test_pdf_path = "/tmp/test_poppler_save_2146.pdf";
        
        // Minimal valid PDF content
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

        std::ofstream ofs(test_pdf_path, std::ios::binary);
        ofs.write(minimal_pdf, strlen(minimal_pdf));
        ofs.close();

        // Convert path to URI
        gchar *uri = g_filename_to_uri(test_pdf_path.c_str(), nullptr, nullptr);
        if (uri) {
            test_pdf_uri = uri;
            g_free(uri);
        }

        // Load the document
        GError *error = nullptr;
        document = poppler_document_new_from_file(test_pdf_uri.c_str(), nullptr, &error);
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
        // Clean up test files
        std::remove(test_pdf_path.c_str());
        std::remove("/tmp/test_poppler_save_output_2146.pdf");
    }
};

// Test saving document to a valid file URI
TEST_F(PopplerDocumentSaveTest_2146, SaveToValidUri_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    std::string output_path = "/tmp/test_poppler_save_output_2146.pdf";
    gchar *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    gboolean result = poppler_document_save(document, output_uri, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    // Verify the file was actually created
    std::ifstream check(output_path);
    EXPECT_TRUE(check.good());
    check.close();

    g_free(output_uri);
}

// Test saving with an invalid URI (not a file:// URI)
TEST_F(PopplerDocumentSaveTest_2146, SaveToInvalidUri_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    gboolean result = poppler_document_save(document, "not_a_valid_uri", &error);

    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test saving with an empty URI string
TEST_F(PopplerDocumentSaveTest_2146, SaveToEmptyUri_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    gboolean result = poppler_document_save(document, "", &error);

    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test saving with a URI pointing to a non-writable location
TEST_F(PopplerDocumentSaveTest_2146, SaveToNonWritableLocation_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    // Try to save to a directory that shouldn't be writable
    gchar *output_uri = g_filename_to_uri("/proc/test_output_2146.pdf", nullptr, nullptr);
    if (!output_uri) {
        GTEST_SKIP() << "Could not create URI for non-writable path";
    }

    gboolean result = poppler_document_save(document, output_uri, &error);

    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
    g_free(output_uri);
}

// Test saving with NULL error parameter (should not crash)
TEST_F(PopplerDocumentSaveTest_2146, SaveWithNullErrorParam_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    std::string output_path = "/tmp/test_poppler_save_output_2146.pdf";
    gchar *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    gboolean result = poppler_document_save(document, output_uri, nullptr);

    EXPECT_TRUE(result);

    g_free(output_uri);
    std::remove(output_path.c_str());
}

// Test saving to the same file that was opened
TEST_F(PopplerDocumentSaveTest_2146, SaveToSameFile_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    gboolean result = poppler_document_save(document, test_pdf_uri.c_str(), &error);

    // The result depends on the implementation - it may succeed or fail
    // but it should not crash
    if (error) {
        g_error_free(error);
    }
    // Just verify we didn't crash
    SUCCEED();
}

// Test that saving with an HTTP URI fails (not a file URI)
TEST_F(PopplerDocumentSaveTest_2146, SaveToHttpUri_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    gboolean result = poppler_document_save(document, "http://example.com/output.pdf", &error);

    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test saving with NULL document (should return FALSE due to g_return_val_if_fail)
TEST_F(PopplerDocumentSaveTest_2146, SaveWithNullDocument_2146) {
    std::string output_path = "/tmp/test_poppler_save_output_2146.pdf";
    gchar *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    // This should trigger the g_return_val_if_fail and return FALSE
    gboolean result = poppler_document_save(nullptr, output_uri, &error);

    EXPECT_FALSE(result);

    g_free(output_uri);
}

// Test saving document and then loading the saved file
TEST_F(PopplerDocumentSaveTest_2146, SaveAndReload_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    std::string output_path = "/tmp/test_poppler_save_output_2146.pdf";
    gchar *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    gboolean result = poppler_document_save(document, output_uri, &error);
    ASSERT_TRUE(result);
    ASSERT_EQ(error, nullptr);

    // Try to load the saved file
    PopplerDocument *reloaded = poppler_document_new_from_file(output_uri, nullptr, &error);
    EXPECT_NE(reloaded, nullptr);
    EXPECT_EQ(error, nullptr);

    if (reloaded) {
        // Verify the reloaded document has the same number of pages
        int original_pages = poppler_document_get_n_pages(document);
        int reloaded_pages = poppler_document_get_n_pages(reloaded);
        EXPECT_EQ(original_pages, reloaded_pages);

        g_object_unref(reloaded);
    }

    if (error) {
        g_error_free(error);
    }
    g_free(output_uri);
}

// Test saving with a URI that has special characters in path
TEST_F(PopplerDocumentSaveTest_2146, SaveToPathWithSpaces_2146) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    std::string output_path = "/tmp/test poppler save 2146.pdf";
    gchar *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    gboolean result = poppler_document_save(document, output_uri, &error);

    EXPECT_TRUE(result);
    if (error) {
        g_error_free(error);
    }

    g_free(output_uri);
    std::remove(output_path.c_str());
}
