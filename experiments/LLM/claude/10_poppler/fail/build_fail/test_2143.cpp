#include <glib.h>
#include <gio/gio.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <cstdio>
#include <fstream>

class PopplerDocumentNewFromGFileTest_2143 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal valid PDF file for testing
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

        tmp_pdf_path_ = g_strdup("/tmp/test_poppler_gfile_2143.pdf");
        std::ofstream ofs(tmp_pdf_path_, std::ios::binary);
        ofs.write(minimal_pdf, strlen(minimal_pdf));
        ofs.close();

        tmp_invalid_path_ = g_strdup("/tmp/test_poppler_gfile_invalid_2143.txt");
        std::ofstream ofs2(tmp_invalid_path_, std::ios::binary);
        ofs2 << "This is not a PDF file at all.";
        ofs2.close();
    }

    void TearDown() override {
        if (tmp_pdf_path_) {
            g_remove(tmp_pdf_path_);
            g_free(tmp_pdf_path_);
        }
        if (tmp_invalid_path_) {
            g_remove(tmp_invalid_path_);
            g_free(tmp_invalid_path_);
        }
    }

    gchar *tmp_pdf_path_ = nullptr;
    gchar *tmp_invalid_path_ = nullptr;
};

// Test: Loading a valid native PDF file via GFile should succeed
TEST_F(PopplerDocumentNewFromGFileTest_2143, LoadValidNativePDF_2143) {
    GFile *file = g_file_new_for_path(tmp_pdf_path_);
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, &error);

    EXPECT_NE(doc, nullptr);
    EXPECT_EQ(error, nullptr);

    if (doc) {
        g_object_unref(doc);
    }
    g_object_unref(file);
}

// Test: Loading a non-existent file should return NULL and set error
TEST_F(PopplerDocumentNewFromGFileTest_2143, LoadNonExistentFile_2143) {
    GFile *file = g_file_new_for_path("/tmp/nonexistent_file_2143_poppler_test.pdf");
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);

    if (error) {
        g_error_free(error);
    }
    g_object_unref(file);
}

// Test: Loading an invalid (non-PDF) file should return NULL and set error
TEST_F(PopplerDocumentNewFromGFileTest_2143, LoadInvalidPDFFile_2143) {
    GFile *file = g_file_new_for_path(tmp_invalid_path_);
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);

    if (error) {
        g_error_free(error);
    }
    if (doc) {
        g_object_unref(doc);
    }
    g_object_unref(file);
}

// Test: Passing NULL password for an unencrypted PDF should work
TEST_F(PopplerDocumentNewFromGFileTest_2143, NullPasswordForUnencryptedPDF_2143) {
    GFile *file = g_file_new_for_path(tmp_pdf_path_);
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, &error);

    EXPECT_NE(doc, nullptr);
    EXPECT_EQ(error, nullptr);

    if (doc) {
        g_object_unref(doc);
    }
    g_object_unref(file);
}

// Test: Passing empty string password for an unencrypted PDF should work
TEST_F(PopplerDocumentNewFromGFileTest_2143, EmptyPasswordForUnencryptedPDF_2143) {
    GFile *file = g_file_new_for_path(tmp_pdf_path_);
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_gfile(file, "", nullptr, &error);

    EXPECT_NE(doc, nullptr);
    EXPECT_EQ(error, nullptr);

    if (doc) {
        g_object_unref(doc);
    }
    g_object_unref(file);
}

// Test: Valid PDF loaded via GFile should report correct page count
TEST_F(PopplerDocumentNewFromGFileTest_2143, ValidPDFHasOnePage_2143) {
    GFile *file = g_file_new_for_path(tmp_pdf_path_);
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, &error);

    ASSERT_NE(doc, nullptr);
    ASSERT_EQ(error, nullptr);

    int n_pages = poppler_document_get_n_pages(doc);
    EXPECT_EQ(n_pages, 1);

    g_object_unref(doc);
    g_object_unref(file);
}

// Test: Using a cancellable that is already cancelled should fail
TEST_F(PopplerDocumentNewFromGFileTest_2143, AlreadyCancelledCancellable_2143) {
    // For native files, cancellable isn't used in the native path (it goes through
    // poppler_document_new_from_file). This test uses a non-native path scenario
    // indirectly. We just test the native file path with a cancelled cancellable -
    // the native path doesn't use cancellable, so it should still succeed.
    GFile *file = g_file_new_for_path(tmp_pdf_path_);
    GCancellable *cancellable = g_cancellable_new();
    g_cancellable_cancel(cancellable);
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, cancellable, &error);

    // For native files, the cancellable is not checked, so doc should still be valid
    // This tests the behavior of the native file path
    EXPECT_NE(doc, nullptr);

    if (error) {
        g_error_free(error);
    }
    if (doc) {
        g_object_unref(doc);
    }
    g_object_unref(cancellable);
    g_object_unref(file);
}

// Test: Loading with NULL error parameter should not crash
TEST_F(PopplerDocumentNewFromGFileTest_2143, NullErrorParameter_2143) {
    GFile *file = g_file_new_for_path(tmp_pdf_path_);

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, nullptr);

    EXPECT_NE(doc, nullptr);

    if (doc) {
        g_object_unref(doc);
    }
    g_object_unref(file);
}

// Test: Loading non-existent file with NULL error parameter should return NULL without crash
TEST_F(PopplerDocumentNewFromGFileTest_2143, NonExistentFileNullError_2143) {
    GFile *file = g_file_new_for_path("/tmp/does_not_exist_2143.pdf");

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, nullptr);

    EXPECT_EQ(doc, nullptr);

    g_object_unref(file);
}

// Test: Loading via URI-based GFile for native file should work
TEST_F(PopplerDocumentNewFromGFileTest_2143, LoadViaFileURI_2143) {
    gchar *uri = g_filename_to_uri(tmp_pdf_path_, nullptr, nullptr);
    ASSERT_NE(uri, nullptr);

    GFile *file = g_file_new_for_uri(uri);
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_gfile(file, nullptr, nullptr, &error);

    EXPECT_NE(doc, nullptr);
    EXPECT_EQ(error, nullptr);

    if (doc) {
        g_object_unref(doc);
    }
    if (error) {
        g_error_free(error);
    }
    g_object_unref(file);
    g_free(uri);
}
