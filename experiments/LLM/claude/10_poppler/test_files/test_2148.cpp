#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

class PopplerDocumentSaveToFdTest_2148 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    gchar *tmp_pdf_path = nullptr;
    gchar *tmp_output_path = nullptr;
    int output_fd = -1;

    void SetUp() override {
        // Create a minimal PDF in a temp file to load as a PopplerDocument
        GError *error = nullptr;

        tmp_pdf_path = g_strdup("/tmp/poppler_test_input_2148.pdf");
        tmp_output_path = g_strdup("/tmp/poppler_test_output_2148.pdf");

        // Create a minimal valid PDF
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

        FILE *f = fopen(tmp_pdf_path, "wb");
        if (f) {
            fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
            fclose(f);
        }

        gchar *uri = g_filename_to_uri(tmp_pdf_path, nullptr, &error);
        if (uri) {
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
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
        if (output_fd != -1) {
            close(output_fd);
            output_fd = -1;
        }
        if (tmp_pdf_path) {
            unlink(tmp_pdf_path);
            g_free(tmp_pdf_path);
        }
        if (tmp_output_path) {
            unlink(tmp_output_path);
            g_free(tmp_output_path);
        }
    }

    int createOutputFd() {
        output_fd = open(tmp_output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        return output_fd;
    }
};

// Test normal save with include_changes = TRUE
TEST_F(PopplerDocumentSaveToFdTest_2148, SaveToFdWithChanges_2148) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    int fd = createOutputFd();
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    gboolean result = poppler_document_save_to_fd(document, fd, TRUE, &error);
    output_fd = -1; // fd is consumed by fdopen inside the function

    // The result depends on the actual implementation; we check no crash
    if (!result && error) {
        g_error_free(error);
    }
    // At minimum, function should not crash
    SUCCEED();
}

// Test normal save with include_changes = FALSE
TEST_F(PopplerDocumentSaveToFdTest_2148, SaveToFdWithoutChanges_2148) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    int fd = createOutputFd();
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    gboolean result = poppler_document_save_to_fd(document, fd, FALSE, &error);
    output_fd = -1; // fd is consumed by fdopen

    if (!result && error) {
        g_error_free(error);
    }
    SUCCEED();
}

// Test that passing fd = -1 returns FALSE (g_return_val_if_fail)
TEST_F(PopplerDocumentSaveToFdTest_2148, InvalidFdMinusOne_2148) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GError *error = nullptr;
    gboolean result = poppler_document_save_to_fd(document, -1, FALSE, &error);
    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test that passing NULL document returns FALSE (g_return_val_if_fail)
TEST_F(PopplerDocumentSaveToFdTest_2148, NullDocument_2148) {
    int fd = createOutputFd();
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    gboolean result = poppler_document_save_to_fd(nullptr, fd, FALSE, &error);
    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test with an invalid fd (not -1, but not a valid open fd)
// fdopen should fail, and we should get an error
TEST_F(PopplerDocumentSaveToFdTest_2148, InvalidFdNotOpen_2148) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Use a very high fd number that is almost certainly not open
    int bad_fd = 9999;

    GError *error = nullptr;
    gboolean result = poppler_document_save_to_fd(document, bad_fd, FALSE, &error);
    EXPECT_FALSE(result);
    EXPECT_NE(error, nullptr);
    if (error) {
        // Verify the error message mentions the FD
        EXPECT_TRUE(g_str_has_prefix(error->message, "Failed to open FD") ||
                    strstr(error->message, "9999") != nullptr);
        EXPECT_EQ(error->domain, G_FILE_ERROR);
        g_error_free(error);
    }
}

// Test saving to fd with NULL error pointer (should not crash)
TEST_F(PopplerDocumentSaveToFdTest_2148, NullErrorPointer_2148) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    int fd = createOutputFd();
    ASSERT_NE(fd, -1);

    // Pass NULL for error - should not crash
    gboolean result = poppler_document_save_to_fd(document, fd, TRUE, nullptr);
    output_fd = -1; // fd consumed by fdopen
    // Just ensure no crash
    (void)result;
    SUCCEED();
}

// Test that the output file actually has content after save
TEST_F(PopplerDocumentSaveToFdTest_2148, OutputFileHasContent_2148) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    int fd = createOutputFd();
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    gboolean result = poppler_document_save_to_fd(document, fd, FALSE, &error);
    output_fd = -1; // fd consumed by fdopen

    if (result) {
        struct stat st;
        int stat_result = stat(tmp_output_path, &st);
        ASSERT_EQ(stat_result, 0);
        EXPECT_GT(st.st_size, 0);
    } else {
        if (error) {
            g_error_free(error);
        }
    }
}

// Test with a read-only fd (should fail on fdopen with "wb")
TEST_F(PopplerDocumentSaveToFdTest_2148, ReadOnlyFd_2148) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Create a file first, then open read-only
    FILE *f = fopen(tmp_output_path, "w");
    if (f) {
        fclose(f);
    }

    int fd = open(tmp_output_path, O_RDONLY);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    gboolean result = poppler_document_save_to_fd(document, fd, FALSE, &error);

    // fdopen with "wb" on a read-only fd should fail
    if (!result) {
        EXPECT_NE(error, nullptr);
        if (error) {
            EXPECT_EQ(error->domain, G_FILE_ERROR);
            g_error_free(error);
        }
    } else {
        // Some systems might allow this; just ensure no crash
        if (error) {
            g_error_free(error);
        }
    }
}

// Test saving with include_changes TRUE and FALSE produce valid output
TEST_F(PopplerDocumentSaveToFdTest_2148, SaveBothModesProduceOutput_2148) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Save with changes
    {
        gchar *path1 = g_strdup("/tmp/poppler_test_out1_2148.pdf");
        int fd1 = open(path1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        ASSERT_NE(fd1, -1);

        GError *error = nullptr;
        gboolean result = poppler_document_save_to_fd(document, fd1, TRUE, &error);
        if (error) g_error_free(error);

        if (result) {
            struct stat st;
            ASSERT_EQ(stat(path1, &st), 0);
            EXPECT_GT(st.st_size, 0);
        }
        unlink(path1);
        g_free(path1);
    }

    // Save without changes
    {
        gchar *path2 = g_strdup("/tmp/poppler_test_out2_2148.pdf");
        int fd2 = open(path2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        ASSERT_NE(fd2, -1);

        GError *error = nullptr;
        gboolean result = poppler_document_save_to_fd(document, fd2, FALSE, &error);
        if (error) g_error_free(error);

        if (result) {
            struct stat st;
            ASSERT_EQ(stat(path2, &st), 0);
            EXPECT_GT(st.st_size, 0);
        }
        unlink(path2);
        g_free(path2);
    }
}
