#include <glib-object.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

class PopplerPSFileNewFdTest_2257 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    
    void SetUp() override {
        // Create a minimal valid PDF in memory to get a PopplerDocument
        GError *error = nullptr;
        
        // Create a minimal PDF file for testing
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
        
        // Write to a temp file
        char tmpname[] = "/tmp/poppler_test_XXXXXX";
        int tmpfd = mkstemp(tmpname);
        if (tmpfd >= 0) {
            write(tmpfd, minimal_pdf, strlen(minimal_pdf));
            close(tmpfd);
            
            gchar *uri = g_filename_to_uri(tmpname, nullptr, nullptr);
            if (uri) {
                document = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            unlink(tmpname);
        }
        
        if (error) {
            g_error_free(error);
        }
    }
    
    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
    
    int createTempFd() {
        char tmpname[] = "/tmp/poppler_ps_test_XXXXXX";
        int fd = mkstemp(tmpname);
        if (fd >= 0) {
            unlink(tmpname); // unlink immediately, fd still valid
        }
        return fd;
    }
};

TEST_F(PopplerPSFileNewFdTest_2257, ValidParameters_ReturnsNonNull_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 1);
    EXPECT_NE(ps_file, nullptr);
    
    if (ps_file) {
        g_object_unref(ps_file);
    }
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, NullDocument_ReturnsNull_2257) {
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    // Passing NULL document should return nullptr
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(nullptr, fd, 0, 1);
    EXPECT_EQ(ps_file, nullptr);
    
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, InvalidFdMinusOne_ReturnsNull_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, -1, 0, 1);
    EXPECT_EQ(ps_file, nullptr);
}

TEST_F(PopplerPSFileNewFdTest_2257, ZeroNPages_ReturnsNull_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 0);
    EXPECT_EQ(ps_file, nullptr);
    
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, NegativeNPages_ReturnsNull_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, -1);
    EXPECT_EQ(ps_file, nullptr);
    
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, FirstPageZero_SinglePage_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 1);
    EXPECT_NE(ps_file, nullptr);
    
    if (ps_file) {
        g_object_unref(ps_file);
    }
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, FirstPageNonZero_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 5, 3);
    EXPECT_NE(ps_file, nullptr);
    
    if (ps_file) {
        g_object_unref(ps_file);
    }
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, MultiplePages_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 100);
    EXPECT_NE(ps_file, nullptr);
    
    if (ps_file) {
        g_object_unref(ps_file);
    }
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, LargeFirstPage_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 999, 1);
    EXPECT_NE(ps_file, nullptr);
    
    if (ps_file) {
        g_object_unref(ps_file);
    }
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, ReturnedObjectIsValidGObject_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Verify it's a valid GObject by checking type
    EXPECT_TRUE(POPPLER_IS_PS_FILE(ps_file));
    
    g_object_unref(ps_file);
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, ValidFdNonStandard_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    ASSERT_GT(fd, 2); // Should be greater than stderr
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 1);
    EXPECT_NE(ps_file, nullptr);
    
    if (ps_file) {
        g_object_unref(ps_file);
    }
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, NPages_ExactlyOne_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    // Boundary: n_pages = 1 (minimum valid value)
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 1);
    EXPECT_NE(ps_file, nullptr);
    
    if (ps_file) {
        g_object_unref(ps_file);
    }
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, AllInvalidParams_ReturnsNull_2257) {
    // All parameters invalid
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(nullptr, -1, 0, 0);
    EXPECT_EQ(ps_file, nullptr);
}

TEST_F(PopplerPSFileNewFdTest_2257, SetPaperSizeAfterCreation_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Test that we can call poppler_ps_file_set_paper_size without crashing
    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);
    
    g_object_unref(ps_file);
    close(fd);
}

TEST_F(PopplerPSFileNewFdTest_2257, SetDuplexAfterCreation_2257) {
    if (!document) GTEST_SKIP() << "Could not create test document";
    
    int fd = createTempFd();
    ASSERT_NE(fd, -1);
    
    PopplerPSFile *ps_file = poppler_ps_file_new_fd(document, fd, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Test that we can call poppler_ps_file_set_duplex without crashing
    poppler_ps_file_set_duplex(ps_file, TRUE);
    
    g_object_unref(ps_file);
    close(fd);
}
