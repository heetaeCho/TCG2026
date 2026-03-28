#include <glib.h>
#include <poppler.h>
#include <glib/gstdio.h>
#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>

class PopplerDocumentGetAttachmentsTest_2156 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a minimal valid PDF in memory with no attachments
    PopplerDocument *createSimplePdfDocument() {
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n190\n%%EOF\n";

        GError *error = nullptr;
        gchar *tmp_path = nullptr;
        gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmp_path, &error);
        if (fd == -1) {
            g_free(tmp_path);
            return nullptr;
        }

        size_t len = strlen(pdf_content);
        write(fd, pdf_content, len);
        close(fd);

        gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);

        if (error) {
            g_error_free(error);
        }

        g_free(uri);
        // Store path for cleanup
        if (doc) {
            g_object_set_data_full(G_OBJECT(doc), "tmp-path", tmp_path, g_free);
        } else {
            g_unlink(tmp_path);
            g_free(tmp_path);
        }

        return doc;
    }

    void cleanupDocument(PopplerDocument *doc) {
        if (doc) {
            const gchar *path = (const gchar *)g_object_get_data(G_OBJECT(doc), "tmp-path");
            if (path) {
                g_unlink(path);
            }
            g_object_unref(doc);
        }
    }
};

// Test that passing NULL document returns NULL
TEST_F(PopplerDocumentGetAttachmentsTest_2156, NullDocumentReturnsNull_2156) {
    // g_return_val_if_fail should catch this and return NULL
    // Note: This will trigger a GLib critical warning
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    GList *result = poppler_document_get_attachments(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that a simple PDF with no attachments returns NULL (empty list)
TEST_F(PopplerDocumentGetAttachmentsTest_2156, NoAttachmentsReturnsNull_2156) {
    PopplerDocument *doc = createSimplePdfDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GList *result = poppler_document_get_attachments(doc);
    EXPECT_EQ(result, nullptr);

    cleanupDocument(doc);
}

// Test has_attachments is consistent with get_attachments for document without attachments
TEST_F(PopplerDocumentGetAttachmentsTest_2156, HasAttachmentsConsistentWithGetAttachments_2156) {
    PopplerDocument *doc = createSimplePdfDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    gboolean has = poppler_document_has_attachments(doc);
    GList *attachments = poppler_document_get_attachments(doc);

    if (has) {
        EXPECT_NE(attachments, nullptr);
    } else {
        EXPECT_EQ(attachments, nullptr);
    }

    if (attachments) {
        g_list_free_full(attachments, g_object_unref);
    }

    cleanupDocument(doc);
}

// Test that passing an invalid GObject (not a PopplerDocument) returns NULL
TEST_F(PopplerDocumentGetAttachmentsTest_2156, InvalidGObjectReturnsNull_2156) {
    // Create a random GObject that is not a PopplerDocument
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    GList *result = poppler_document_get_attachments((PopplerDocument *)obj);
    g_test_assert_expected_messages();

    EXPECT_EQ(result, nullptr);

    g_object_unref(obj);
}

// Test that returned list from a document with no embedded files has zero length
TEST_F(PopplerDocumentGetAttachmentsTest_2156, EmptyAttachmentListLength_2156) {
    PopplerDocument *doc = createSimplePdfDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GList *result = poppler_document_get_attachments(doc);
    guint length = g_list_length(result);
    EXPECT_EQ(length, 0u);

    if (result) {
        g_list_free_full(result, g_object_unref);
    }

    cleanupDocument(doc);
}

// Test calling get_attachments multiple times yields consistent results
TEST_F(PopplerDocumentGetAttachmentsTest_2156, MultipleCallsConsistent_2156) {
    PopplerDocument *doc = createSimplePdfDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GList *result1 = poppler_document_get_attachments(doc);
    GList *result2 = poppler_document_get_attachments(doc);

    guint len1 = g_list_length(result1);
    guint len2 = g_list_length(result2);
    EXPECT_EQ(len1, len2);

    if (result1) {
        g_list_free_full(result1, g_object_unref);
    }
    if (result2) {
        g_list_free_full(result2, g_object_unref);
    }

    cleanupDocument(doc);
}

// Test with a PDF loaded from data (in-memory) with no attachments
TEST_F(PopplerDocumentGetAttachmentsTest_2156, FromDataNoAttachments_2156) {
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        (const char *)pdf_content, strlen(pdf_content), nullptr, &error);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create document from data";
    }

    GList *result = poppler_document_get_attachments(doc);
    EXPECT_EQ(result, nullptr);

    if (result) {
        g_list_free_full(result, g_object_unref);
    }

    g_object_unref(doc);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
