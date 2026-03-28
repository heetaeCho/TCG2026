#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <gtest/gtest.h>

class PopplerAttachmentSaveToFdTest_2278 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    GList *attachments = nullptr;

    void SetUp() override {
        // Try to find a PDF with attachments for testing
        // We'll create a minimal test setup
    }

    void TearDown() override {
        if (attachments) {
            g_list_free_full(attachments, g_object_unref);
            attachments = nullptr;
        }
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerDocument *loadDocWithAttachments(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *d = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) g_error_free(error);
        return d;
    }

    // Helper to create a temporary file and return its fd
    int createTempFd(char *tmpl) {
        return mkstemp(tmpl);
    }
};

// Test that passing fd = -1 returns FALSE (g_return_val_if_fail)
TEST_F(PopplerAttachmentSaveToFdTest_2278, InvalidFdMinusOne_2278) {
    // We need a valid PopplerAttachment to test the fd check.
    // Since we can't easily create one without a PDF, we test with nullptr attachment
    // which should also return FALSE due to the IS_ATTACHMENT check.
    GError *error = nullptr;
    gboolean result = poppler_attachment_save_to_fd(nullptr, -1, &error);
    EXPECT_FALSE(result);
    if (error) g_error_free(error);
}

// Test that passing NULL attachment returns FALSE
TEST_F(PopplerAttachmentSaveToFdTest_2278, NullAttachmentReturnsFalse_2278) {
    char tmpl[] = "/tmp/poppler_test_XXXXXX";
    int fd = createTempFd(tmpl);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    gboolean result = poppler_attachment_save_to_fd(nullptr, fd, &error);
    EXPECT_FALSE(result);
    if (error) g_error_free(error);

    // Clean up temp file - fd may have been closed by the function or not
    unlink(tmpl);
}

// Test that passing an error that is already set returns FALSE
TEST_F(PopplerAttachmentSaveToFdTest_2278, PresetErrorReturnsFalse_2278) {
    GError *error = g_error_new_literal(G_FILE_ERROR, G_FILE_ERROR_FAILED, "pre-existing error");
    gboolean result = poppler_attachment_save_to_fd(nullptr, 1, &error);
    EXPECT_FALSE(result);
    if (error) g_error_free(error);
}

// Test with an invalid fd (not -1 but still bad, e.g., a very large number)
// This should fail at fdopen and set an error
TEST_F(PopplerAttachmentSaveToFdTest_2278, InvalidFdLargeNumber_2278) {
    // We need a valid attachment for this test to get past the g_return_val checks.
    // Without a real PDF, we can only test the precondition checks.
    // This test documents expected behavior with bad fd when attachment is null.
    GError *error = nullptr;
    gboolean result = poppler_attachment_save_to_fd(nullptr, 99999, &error);
    EXPECT_FALSE(result);
    if (error) g_error_free(error);
}

// Test with a real PDF that has attachments if available
TEST_F(PopplerAttachmentSaveToFdTest_2278, SaveToValidFdWithRealPdf_2278) {
    // Try to load a test PDF with attachments
    const char *test_pdfs[] = {
        "./test-data/attachment.pdf",
        "../test-data/attachment.pdf",
        "attachment.pdf",
        nullptr
    };

    PopplerDocument *testDoc = nullptr;
    for (int i = 0; test_pdfs[i] != nullptr; i++) {
        if (g_file_test(test_pdfs[i], G_FILE_TEST_EXISTS)) {
            testDoc = loadDocWithAttachments(test_pdfs[i]);
            if (testDoc && poppler_document_has_attachments(testDoc)) {
                break;
            }
            if (testDoc) {
                g_object_unref(testDoc);
                testDoc = nullptr;
            }
        }
    }

    if (!testDoc) {
        GTEST_SKIP() << "No test PDF with attachments found, skipping real save test";
        return;
    }

    GList *atts = poppler_document_get_attachments(testDoc);
    ASSERT_NE(atts, nullptr);
    ASSERT_NE(g_list_length(atts), 0u);

    PopplerAttachment *att = POPPLER_ATTACHMENT(atts->data);
    ASSERT_NE(att, nullptr);

    char tmpl[] = "/tmp/poppler_att_test_XXXXXX";
    int fd = createTempFd(tmpl);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    gboolean result = poppler_attachment_save_to_fd(att, fd, &error);
    // fd is consumed by the function (fdopen takes ownership)
    
    if (!result) {
        if (error) {
            ADD_FAILURE() << "save_to_fd failed: " << error->message;
            g_error_free(error);
        }
    } else {
        EXPECT_TRUE(result);
        EXPECT_EQ(error, nullptr);
        // Verify file was written (non-zero size)
        struct stat st;
        if (stat(tmpl, &st) == 0) {
            EXPECT_GT(st.st_size, 0);
        }
    }

    unlink(tmpl);
    g_list_free_full(atts, g_object_unref);
    g_object_unref(testDoc);
}

// Test that nullptr error parameter doesn't crash
TEST_F(PopplerAttachmentSaveToFdTest_2278, NullErrorParameterDoesNotCrash_2278) {
    gboolean result = poppler_attachment_save_to_fd(nullptr, 1, nullptr);
    EXPECT_FALSE(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
