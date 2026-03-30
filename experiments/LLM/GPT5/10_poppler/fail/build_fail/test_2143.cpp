// File: poppler-document-new-from-gfile-test-2143.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <gio/gio.h>

#include <poppler.h>

namespace {

class PopplerDocumentNewFromGFileTest_2143 : public ::testing::Test {
protected:
    void SetUp() override { temp_paths_ = g_ptr_array_new_with_free_func(g_free); }

    void TearDown() override {
        // Best-effort cleanup of temp files.
        for (guint i = 0; i < temp_paths_->len; ++i) {
            const char *path = static_cast<const char *>(g_ptr_array_index(temp_paths_, i));
            if (path) {
                g_remove(path);
            }
        }
        g_ptr_array_free(temp_paths_, TRUE);
    }

    // Creates a temp file with the provided bytes and returns a GFile* for the path.
    // Caller owns returned GFile*.
    GFile *CreateTempFileWithBytes(const guint8 *data, gsize len) {
        gchar *path = nullptr;
        gint fd = g_file_open_tmp("poppler_gfile_XXXXXX", &path, nullptr);
        EXPECT_GE(fd, 0);
        EXPECT_NE(path, nullptr);

        // Track for deletion at teardown.
        g_ptr_array_add(temp_paths_, g_strdup(path));

        // Write content.
        GError *write_error = nullptr;
        gboolean ok = g_file_set_contents(path, reinterpret_cast<const gchar *>(data), static_cast<gssize>(len), &write_error);
        if (!ok) {
            if (write_error) {
                ADD_FAILURE() << "g_file_set_contents failed: " << write_error->message;
                g_error_free(write_error);
            } else {
                ADD_FAILURE() << "g_file_set_contents failed with unknown error";
            }
        }

        close(fd);
        GFile *file = g_file_new_for_path(path);
        g_free(path);
        return file;
    }

private:
    GPtrArray *temp_paths_{nullptr};
};

// A tiny, valid one-page PDF (generated with correct xref offsets).
static const guint8 kMinimalValidPdf_2143[] =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 44 >>\n"
    "stream\n"
    "BT\n"
    "/F1 24 Tf\n"
    "72 120 Td\n"
    "(Hello) Tj\n"
    "ET\n"
    "endstream\n"
    "endobj\n"
    "5 0 obj\n"
    "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
    "endobj\n"
    "xref\n"
    "0 6\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "0000000241 00000 n \n"
    "0000000327 00000 n \n"
    "trailer\n"
    "<< /Size 6 /Root 1 0 R >>\n"
    "startxref\n"
    "397\n"
    "%%EOF\n";

TEST_F(PopplerDocumentNewFromGFileTest_2143, NullFile_ReturnsNullAndLogsCritical_2143) {
    // g_return_val_if_fail() should emit a critical and return NULL.
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*g_return_val_if_fail*");
    PopplerDocument *doc = poppler_document_new_from_gfile(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(doc, nullptr);
    g_test_assert_expected_messages();
}

TEST_F(PopplerDocumentNewFromGFileTest_2143, NonGFileObject_ReturnsNullAndLogsCritical_2143) {
    // Pass something that's not a GFile*; should trip G_IS_FILE(file) guard.
    GObject *not_a_file = g_object_new(G_TYPE_OBJECT, nullptr);

    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*g_return_val_if_fail*");
    PopplerDocument *doc =
        poppler_document_new_from_gfile(reinterpret_cast<GFile *>(not_a_file), nullptr, nullptr, nullptr);
    EXPECT_EQ(doc, nullptr);
    g_test_assert_expected_messages();

    g_object_unref(not_a_file);
}

TEST_F(PopplerDocumentNewFromGFileTest_2143, NativeFile_InvalidPdf_ReturnsNullAndSetsError_2143) {
    static const guint8 kNotPdf[] = "this is not a pdf\n";
    GFile *file = CreateTempFileWithBytes(kNotPdf, sizeof(kNotPdf) - 1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_gfile(file, /*password=*/nullptr, /*cancellable=*/nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        EXPECT_NE(error->message, nullptr);
        EXPECT_NE(g_strcmp0(error->message, ""), 0);
        g_error_free(error);
    }

    g_object_unref(file);
}

TEST_F(PopplerDocumentNewFromGFileTest_2143, NativeFile_ValidPdf_ReturnsDocument_2143) {
    GFile *file = CreateTempFileWithBytes(kMinimalValidPdf_2143, sizeof(kMinimalValidPdf_2143) - 1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_gfile(file, /*password=*/nullptr, /*cancellable=*/nullptr, &error);

    EXPECT_NE(doc, nullptr);
    EXPECT_EQ(error, nullptr);

    if (doc) {
        // Basic observable behavior via public API: should have at least 1 page.
        int n_pages = poppler_document_get_n_pages(doc);
        EXPECT_GE(n_pages, 1);
        g_object_unref(doc);
    }
    if (error) {
        g_error_free(error);
    }

    g_object_unref(file);
}

TEST_F(PopplerDocumentNewFromGFileTest_2143, NonNativeUnreadableUri_ReturnsNullAndSetsError_2143) {
    // Use a non-native URI scheme that should fail quickly to read.
    // Whether the implementation takes the "native" or "non-native" branch is not asserted;
    // only the observable outcome is tested.
    GFile *file = g_file_new_for_uri("resource:///this-file-should-not-exist-2143.pdf");

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_gfile(file, /*password=*/nullptr, /*cancellable=*/nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        EXPECT_NE(error->message, nullptr);
        EXPECT_NE(g_strcmp0(error->message, ""), 0);
        g_error_free(error);
    }

    g_object_unref(file);
}

} // namespace