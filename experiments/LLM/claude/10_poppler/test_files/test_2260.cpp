#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler glib headers
#include "poppler-document.h"

class PopplerPSFileFreeTest_2260 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing nullptr does not crash (g_return_if_fail should handle it)
TEST_F(PopplerPSFileFreeTest_2260, NullPointerDoesNotCrash_2260)
{
    // g_return_if_fail should silently return when ps_file is nullptr
    poppler_ps_file_free(nullptr);
    // If we reach here without crashing, the test passes
    SUCCEED();
}

// Test that a valid PopplerPSFile can be created and freed without issues
TEST_F(PopplerPSFileFreeTest_2260, ValidPSFileCanBeFreed_2260)
{
    // We need a valid PopplerDocument to create a PopplerPSFile
    // Create a minimal PDF in memory for testing
    const char *pdf_content = "%PDF-1.0\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                               "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                               "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                               "xref\n0 4\n0000000000 65535 f \n"
                               "0000000009 00000 n \n0000000058 00000 n \n"
                               "0000000115 00000 n \n"
                               "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Write to a temp file
    gchar *tmp_filename = nullptr;
    GError *error = nullptr;
    gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmp_filename, &error);
    if (fd == -1 || error != nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create temporary file";
        return;
    }

    FILE *fp = fdopen(fd, "wb");
    if (!fp) {
        close(fd);
        g_free(tmp_filename);
        GTEST_SKIP() << "Could not open temporary file for writing";
        return;
    }
    fwrite(pdf_content, 1, strlen(pdf_content), fp);
    fclose(fp);

    // Build a URI from the filename
    gchar *uri = g_filename_to_uri(tmp_filename, nullptr, &error);
    if (!uri) {
        if (error) {
            g_error_free(error);
        }
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP() << "Could not create URI from filename";
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!doc) {
        if (error) {
            g_error_free(error);
        }
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP() << "Could not create PopplerDocument from test PDF";
        return;
    }

    // Create a temporary output PS filename
    gchar *ps_filename = nullptr;
    gint ps_fd = g_file_open_tmp("poppler_test_XXXXXX.ps", &ps_filename, &error);
    if (ps_fd == -1) {
        if (error) {
            g_error_free(error);
        }
        g_object_unref(doc);
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP() << "Could not create temporary PS file";
        return;
    }
    close(ps_fd);

    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GE(n_pages, 1);

    PopplerPSFile *ps_file = poppler_ps_file_new(doc, ps_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);

    // Free the PS file - this is the main function under test
    poppler_ps_file_free(ps_file);
    // ps_file is now invalid, we should not use it

    // Cleanup
    g_object_unref(doc);
    g_unlink(ps_filename);
    g_free(ps_filename);
    g_unlink(tmp_filename);
    g_free(tmp_filename);

    SUCCEED();
}

// Test that poppler_ps_file_set_paper_size works before freeing
TEST_F(PopplerPSFileFreeTest_2260, SetPaperSizeThenFree_2260)
{
    const char *pdf_content = "%PDF-1.0\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                               "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                               "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                               "xref\n0 4\n0000000000 65535 f \n"
                               "0000000009 00000 n \n0000000058 00000 n \n"
                               "0000000115 00000 n \n"
                               "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    gchar *tmp_filename = nullptr;
    GError *error = nullptr;
    gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmp_filename, &error);
    if (fd == -1) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create temporary file";
        return;
    }

    FILE *fp = fdopen(fd, "wb");
    if (!fp) {
        close(fd);
        g_free(tmp_filename);
        GTEST_SKIP();
        return;
    }
    fwrite(pdf_content, 1, strlen(pdf_content), fp);
    fclose(fp);

    gchar *uri = g_filename_to_uri(tmp_filename, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP();
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!doc) {
        if (error) g_error_free(error);
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP();
        return;
    }

    gchar *ps_filename = nullptr;
    gint ps_fd = g_file_open_tmp("poppler_test_XXXXXX.ps", &ps_filename, &error);
    if (ps_fd == -1) {
        if (error) g_error_free(error);
        g_object_unref(doc);
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP();
        return;
    }
    close(ps_fd);

    int n_pages = poppler_document_get_n_pages(doc);
    PopplerPSFile *ps_file = poppler_ps_file_new(doc, ps_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);

    // Set paper size before freeing
    poppler_ps_file_set_paper_size(ps_file, 595.0, 842.0); // A4 size

    // Set duplex
    poppler_ps_file_set_duplex(ps_file, TRUE);

    // Free should work fine after setting properties
    poppler_ps_file_free(ps_file);

    g_object_unref(doc);
    g_unlink(ps_filename);
    g_free(ps_filename);
    g_unlink(tmp_filename);
    g_free(tmp_filename);

    SUCCEED();
}
