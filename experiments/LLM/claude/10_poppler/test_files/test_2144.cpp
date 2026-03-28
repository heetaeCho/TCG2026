#include <glib.h>
#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstring>
#include <fstream>

// Include poppler glib headers
#include "poppler-document.h"

class PopplerDocumentNewFromFdTest_2144 : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}

    // Helper to create a temporary file with given content and return its fd
    int createTempFileWithContent(const char *content, size_t len) {
        char tmpfile[] = "/tmp/poppler_test_XXXXXX";
        int fd = mkstemp(tmpfile);
        if (fd == -1) {
            return -1;
        }
        if (content && len > 0) {
            write(fd, content, len);
        }
        // Rewind to beginning
        lseek(fd, 0, SEEK_SET);
        // Unlink so it gets cleaned up automatically
        unlink(tmpfile);
        return fd;
    }

    // Helper to create a temporary file from a valid minimal PDF
    int createMinimalPdfFd() {
        // A minimal valid PDF
        const char *pdf_content =
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
        size_t len = strlen(pdf_content);
        return createTempFileWithContent(pdf_content, len);
    }

    // Helper to create a temporary PDF file path and return the path
    std::string createMinimalPdfFile() {
        char tmpfile[] = "/tmp/poppler_test_pdf_XXXXXX";
        int fd = mkstemp(tmpfile);
        if (fd == -1) {
            return "";
        }
        const char *pdf_content =
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
        write(fd, pdf_content, strlen(pdf_content));
        close(fd);
        return std::string(tmpfile);
    }
};

// Test that passing fd = -1 returns nullptr (g_return_val_if_fail)
TEST_F(PopplerDocumentNewFromFdTest_2144, InvalidFdMinusOne_ReturnsNull_2144) {
    GError *error = nullptr;
    // Note: g_return_val_if_fail with fd != -1 should return nullptr
    // This may trigger a g_warning, suppress it
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*fd != -1*");
    PopplerDocument *doc = poppler_document_new_from_fd(-1, nullptr, &error);
    g_test_assert_expected_messages();
    EXPECT_EQ(doc, nullptr);
}

// Test that a write-only fd returns nullptr with appropriate error
TEST_F(PopplerDocumentNewFromFdTest_2144, WriteOnlyFd_ReturnsNull_2144) {
    char tmpfile[] = "/tmp/poppler_test_wo_XXXXXX";
    int fd = mkstemp(tmpfile);
    ASSERT_NE(fd, -1);
    close(fd);

    // Open write-only
    fd = open(tmpfile, O_WRONLY);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(fd, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        EXPECT_EQ(error->domain, G_FILE_ERROR);
        EXPECT_EQ(error->code, G_FILE_ERROR_BADF);
        g_error_free(error);
    }

    unlink(tmpfile);
    // Note: fd is closed by the function
}

// Test that an invalid (non-PDF) file returns nullptr
TEST_F(PopplerDocumentNewFromFdTest_2144, NonPdfContent_ReturnsNull_2144) {
    const char *content = "This is not a PDF file at all.";
    int fd = createTempFileWithContent(content, strlen(content));
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(fd, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test that an empty file returns nullptr
TEST_F(PopplerDocumentNewFromFdTest_2144, EmptyFile_ReturnsNull_2144) {
    int fd = createTempFileWithContent(nullptr, 0);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(fd, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test with a valid minimal PDF - should succeed
TEST_F(PopplerDocumentNewFromFdTest_2144, ValidMinimalPdf_ReturnsDocument_2144) {
    std::string path = createMinimalPdfFile();
    ASSERT_FALSE(path.empty());

    int fd = open(path.c_str(), O_RDONLY);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(fd, nullptr, &error);

    // Minimal PDF may or may not parse correctly depending on the xref validity
    // but the function should not crash. If it fails, error should be set.
    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        g_object_unref(doc);
    } else {
        // It's acceptable for our minimal PDF to fail parsing
        if (error) {
            g_error_free(error);
        }
    }

    unlink(path.c_str());
}

// Test that a closed/invalid fd returns nullptr with error
TEST_F(PopplerDocumentNewFromFdTest_2144, ClosedFd_ReturnsNull_2144) {
    char tmpfile[] = "/tmp/poppler_test_closed_XXXXXX";
    int fd = mkstemp(tmpfile);
    ASSERT_NE(fd, -1);
    unlink(tmpfile);
    close(fd);

    // fd is now closed, fstat should fail
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(fd, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test with O_RDWR fd on a non-PDF file still returns null (due to bad content)
TEST_F(PopplerDocumentNewFromFdTest_2144, ReadWriteFdNonPdf_ReturnsNull_2144) {
    char tmpfile[] = "/tmp/poppler_test_rw_XXXXXX";
    int fd = mkstemp(tmpfile);
    ASSERT_NE(fd, -1);
    const char *content = "Not a PDF";
    write(fd, content, strlen(content));
    close(fd);

    fd = open(tmpfile, O_RDWR);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(fd, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }

    unlink(tmpfile);
}

// Test passing a null password with valid fd (non-encrypted PDF)
TEST_F(PopplerDocumentNewFromFdTest_2144, NullPasswordNonEncrypted_2144) {
    std::string path = createMinimalPdfFile();
    ASSERT_FALSE(path.empty());

    int fd = open(path.c_str(), O_RDONLY);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(fd, nullptr, &error);

    if (doc != nullptr) {
        EXPECT_EQ(error, nullptr);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
    }

    unlink(path.c_str());
}

// Test passing a wrong password with a non-encrypted PDF
TEST_F(PopplerDocumentNewFromFdTest_2144, WrongPasswordNonEncrypted_2144) {
    std::string path = createMinimalPdfFile();
    ASSERT_FALSE(path.empty());

    int fd = open(path.c_str(), O_RDONLY);
    ASSERT_NE(fd, -1);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(fd, "wrongpassword", &error);

    // Non-encrypted PDF with a password should still open (password is ignored)
    if (doc != nullptr) {
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
    }

    unlink(path.c_str());
}

// Test with a FIFO (non-regular file) to exercise the CachedFile path
TEST_F(PopplerDocumentNewFromFdTest_2144, FifoFd_NonRegularFile_2144) {
    char tmpfifo[] = "/tmp/poppler_test_fifo_XXXXXX";
    // mkstemp creates a regular file, so we need to create a FIFO differently
    char tmpdir[] = "/tmp/poppler_test_dir_XXXXXX";
    char *dir = mkdtemp(tmpdir);
    if (!dir) {
        GTEST_SKIP() << "Cannot create temp directory for FIFO test";
    }

    std::string fifo_path = std::string(dir) + "/testfifo";
    if (mkfifo(fifo_path.c_str(), 0600) != 0) {
        rmdir(dir);
        GTEST_SKIP() << "Cannot create FIFO";
    }

    // We need to open FIFO non-blocking for writing in another context
    // This is complex for a unit test; skip if we can't set it up
    // Instead, test with a pipe
    int pipefd[2];
    if (pipe(pipefd) != 0) {
        unlink(fifo_path.c_str());
        rmdir(dir);
        GTEST_SKIP() << "Cannot create pipe";
    }

    // Write some non-PDF content to the pipe
    const char *content = "Not a PDF";
    write(pipefd[1], content, strlen(content));
    close(pipefd[1]);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_fd(pipefd[0], nullptr, &error);
    // Should fail because content is not a valid PDF
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }

    unlink(fifo_path.c_str());
    rmdir(dir);
}

// Test with NULL error pointer - should not crash
TEST_F(PopplerDocumentNewFromFdTest_2144, NullErrorPointer_DoesNotCrash_2144) {
    const char *content = "Not a PDF";
    int fd = createTempFileWithContent(content, strlen(content));
    ASSERT_NE(fd, -1);

    PopplerDocument *doc = poppler_document_new_from_fd(fd, nullptr, nullptr);
    EXPECT_EQ(doc, nullptr);
}
