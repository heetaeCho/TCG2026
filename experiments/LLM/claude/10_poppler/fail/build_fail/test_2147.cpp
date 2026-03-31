#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>

class PopplerDocumentSaveACopyTest_2147 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    std::string test_pdf_path;
    std::string test_pdf_uri;

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        test_pdf_path = std::string(g_get_tmp_dir()) + "/test_poppler_2147.pdf";
        
        // Minimal valid PDF content
        const char *minimal_pdf = 
            "%PDF-1.0\n"
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

        std::ofstream ofs(test_pdf_path, std::ios::binary);
        ofs.write(minimal_pdf, strlen(minimal_pdf));
        ofs.close();

        char *uri = g_filename_to_uri(test_pdf_path.c_str(), nullptr, nullptr);
        if (uri) {
            test_pdf_uri = uri;
            g_free(uri);
        }

        GError *error = nullptr;
        document = poppler_document_new_from_file(test_pdf_uri.c_str(), nullptr, &error);
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
        // Clean up test files
        g_unlink(test_pdf_path.c_str());
    }
};

// Test: Save a copy with a valid URI to a new file
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyValidUri_2147) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    std::string output_path = std::string(g_get_tmp_dir()) + "/test_poppler_save_copy_2147.pdf";
    char *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    gboolean result = poppler_document_save_a_copy(document, output_uri, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    // Verify file was created
    EXPECT_TRUE(g_file_test(output_path.c_str(), G_FILE_TEST_EXISTS));

    g_free(output_uri);
    g_unlink(output_path.c_str());
}

// Test: Save a copy with an invalid URI should fail
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyInvalidUri_2147) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    // Not a valid URI - no scheme
    gboolean result = poppler_document_save_a_copy(document, "not_a_valid_uri", &error);

    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test: Save a copy with NULL document should return FALSE (g_return_val_if_fail)
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyNullDocument_2147) {
    std::string output_path = std::string(g_get_tmp_dir()) + "/test_poppler_null_doc_2147.pdf";
    char *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    // Passing NULL document should trigger g_return_val_if_fail and return FALSE
    gboolean result = poppler_document_save_a_copy(nullptr, output_uri, &error);

    EXPECT_FALSE(result);

    g_free(output_uri);
    g_unlink(output_path.c_str());
}

// Test: Save a copy with an empty string URI
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyEmptyUri_2147) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    gboolean result = poppler_document_save_a_copy(document, "", &error);

    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test: Save a copy to a path that doesn't exist (invalid directory)
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyInvalidPath_2147) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Valid URI but to a non-existent directory
    std::string invalid_path = "/nonexistent_dir_2147/subdir/output.pdf";
    char *output_uri = g_filename_to_uri(invalid_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    gboolean result = poppler_document_save_a_copy(document, output_uri, &error);

    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }

    g_free(output_uri);
}

// Test: Save a copy with a valid file:// URI scheme
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyFileSchemeUri_2147) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    std::string output_path = std::string(g_get_tmp_dir()) + "/test_poppler_file_scheme_2147.pdf";
    char *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    gboolean result = poppler_document_save_a_copy(document, output_uri, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    // Verify saved file can be opened as a valid PDF
    if (result) {
        GError *open_error = nullptr;
        char *saved_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
        PopplerDocument *saved_doc = poppler_document_new_from_file(saved_uri, nullptr, &open_error);
        if (saved_doc) {
            EXPECT_EQ(poppler_document_get_n_pages(saved_doc), poppler_document_get_n_pages(document));
            g_object_unref(saved_doc);
        }
        if (open_error) {
            g_error_free(open_error);
        }
        g_free(saved_uri);
    }

    g_free(output_uri);
    g_unlink(output_path.c_str());
}

// Test: Save a copy with NULL error parameter (should still work)
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyNullError_2147) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    std::string output_path = std::string(g_get_tmp_dir()) + "/test_poppler_null_error_2147.pdf";
    char *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    gboolean result = poppler_document_save_a_copy(document, output_uri, nullptr);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_file_test(output_path.c_str(), G_FILE_TEST_EXISTS));

    g_free(output_uri);
    g_unlink(output_path.c_str());
}

// Test: Save a copy overwriting an existing file
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyOverwriteExistingFile_2147) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    std::string output_path = std::string(g_get_tmp_dir()) + "/test_poppler_overwrite_2147.pdf";

    // Create a file first
    {
        std::ofstream ofs(output_path);
        ofs << "dummy content";
        ofs.close();
    }
    ASSERT_TRUE(g_file_test(output_path.c_str(), G_FILE_TEST_EXISTS));

    char *output_uri = g_filename_to_uri(output_path.c_str(), nullptr, nullptr);
    ASSERT_NE(output_uri, nullptr);

    GError *error = nullptr;
    gboolean result = poppler_document_save_a_copy(document, output_uri, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    g_free(output_uri);
    g_unlink(output_path.c_str());
}

// Test: Save a copy with non-file URI scheme (e.g., http://) should fail
TEST_F(PopplerDocumentSaveACopyTest_2147, SaveACopyNonFileUri_2147) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    gboolean result = poppler_document_save_a_copy(document, "http://example.com/test.pdf", &error);

    // g_filename_from_uri should fail for non-file URIs
    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}
