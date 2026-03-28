#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler-document.h"
#include "poppler-private.h"

// We need to create a valid PopplerDocument for testing.
// Since we can't easily construct one without a real PDF, we'll use a minimal PDF in memory.

class PopplerPSFileTest_2256 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal valid PDF in a temporary file
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
        tmp_pdf_path = g_strdup("/tmp/test_poppler_psfile_2256.pdf");
        FILE *f = fopen(tmp_pdf_path, "wb");
        if (f) {
            fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmp_pdf_path, nullptr, &error);
        if (uri) {
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
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
        if (tmp_pdf_path) {
            g_remove(tmp_pdf_path);
            g_free(tmp_pdf_path);
            tmp_pdf_path = nullptr;
        }
    }

    gchar *tmp_pdf_path = nullptr;
};

// Test normal creation of a PopplerPSFile
TEST_F(PopplerPSFileTest_2256, NormalCreation_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const char *output_filename = "/tmp/test_output_2256.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);

    // Verify the fields are set correctly based on the implementation
    // first_page should be first_page + 1 = 0 + 1 = 1
    EXPECT_EQ(ps_file->first_page, 1);
    // last_page should be first_page + 1 + n_pages - 1 = 0 + 1 + 1 - 1 = 1
    EXPECT_EQ(ps_file->last_page, 1);
    // filename should be a copy
    EXPECT_STREQ(ps_file->filename, output_filename);
    // document should be set (and ref'd)
    EXPECT_NE(ps_file->document, nullptr);

    g_object_unref(ps_file);
}

// Test that first_page and last_page are computed correctly for non-zero first_page
TEST_F(PopplerPSFileTest_2256, FirstPageOffset_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const char *output_filename = "/tmp/test_output_offset_2256.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_filename, 2, 3);
    ASSERT_NE(ps_file, nullptr);

    // first_page = 2 + 1 = 3
    EXPECT_EQ(ps_file->first_page, 3);
    // last_page = 2 + 1 + 3 - 1 = 5
    EXPECT_EQ(ps_file->last_page, 5);

    g_object_unref(ps_file);
}

// Test with first_page = 0 and n_pages = 1
TEST_F(PopplerPSFileTest_2256, SinglePage_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const char *output_filename = "/tmp/test_single_page_2256.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);

    EXPECT_EQ(ps_file->first_page, 1);
    EXPECT_EQ(ps_file->last_page, 1);

    g_object_unref(ps_file);
}

// Test with multiple pages
TEST_F(PopplerPSFileTest_2256, MultiplePages_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const char *output_filename = "/tmp/test_multi_page_2256.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_filename, 0, 5);
    ASSERT_NE(ps_file, nullptr);

    EXPECT_EQ(ps_file->first_page, 1);
    // last_page = 0 + 1 + 5 - 1 = 5
    EXPECT_EQ(ps_file->last_page, 5);

    g_object_unref(ps_file);
}

// Test that NULL document returns NULL
TEST_F(PopplerPSFileTest_2256, NullDocumentReturnsNull_2256) {
    // Passing NULL document should trigger g_return_val_if_fail and return NULL
    // This may produce a g_warning, which is expected
    g_test_expect_message(nullptr, G_LOG_LEVEL_WARNING, "*");
    PopplerPSFile *ps_file = poppler_ps_file_new(nullptr, "/tmp/test_2256.ps", 0, 1);
    g_test_assert_expected_messages();
    EXPECT_EQ(ps_file, nullptr);
}

// Test that NULL filename returns NULL
TEST_F(PopplerPSFileTest_2256, NullFilenameReturnsNull_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    g_test_expect_message(nullptr, G_LOG_LEVEL_WARNING, "*");
    PopplerPSFile *ps_file = poppler_ps_file_new(document, nullptr, 0, 1);
    g_test_assert_expected_messages();
    EXPECT_EQ(ps_file, nullptr);
}

// Test that n_pages = 0 returns NULL (n_pages must be > 0)
TEST_F(PopplerPSFileTest_2256, ZeroNPagesReturnsNull_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    g_test_expect_message(nullptr, G_LOG_LEVEL_WARNING, "*");
    PopplerPSFile *ps_file = poppler_ps_file_new(document, "/tmp/test_2256.ps", 0, 0);
    g_test_assert_expected_messages();
    EXPECT_EQ(ps_file, nullptr);
}

// Test that negative n_pages returns NULL
TEST_F(PopplerPSFileTest_2256, NegativeNPagesReturnsNull_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    g_test_expect_message(nullptr, G_LOG_LEVEL_WARNING, "*");
    PopplerPSFile *ps_file = poppler_ps_file_new(document, "/tmp/test_2256.ps", 0, -1);
    g_test_assert_expected_messages();
    EXPECT_EQ(ps_file, nullptr);
}

// Test that the document reference count is increased
TEST_F(PopplerPSFileTest_2256, DocumentRefCountIncreased_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    guint ref_count_before = G_OBJECT(document)->ref_count;
    PopplerPSFile *ps_file = poppler_ps_file_new(document, "/tmp/test_ref_2256.ps", 0, 1);
    ASSERT_NE(ps_file, nullptr);

    guint ref_count_after = G_OBJECT(document)->ref_count;
    EXPECT_EQ(ref_count_after, ref_count_before + 1);

    g_object_unref(ps_file);
}

// Test that filename is a copy (not the same pointer)
TEST_F(PopplerPSFileTest_2256, FilenameIsCopied_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const char *output_filename = "/tmp/test_copy_2256.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);

    // The filename should be a different pointer but same content
    EXPECT_NE(ps_file->filename, output_filename);
    EXPECT_STREQ(ps_file->filename, output_filename);

    g_object_unref(ps_file);
}

// Test boundary: large first_page value
TEST_F(PopplerPSFileTest_2256, LargeFirstPage_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerPSFile *ps_file = poppler_ps_file_new(document, "/tmp/test_large_fp_2256.ps", 999, 1);
    ASSERT_NE(ps_file, nullptr);

    EXPECT_EQ(ps_file->first_page, 1000);
    EXPECT_EQ(ps_file->last_page, 1000);

    g_object_unref(ps_file);
}

// Test boundary: large n_pages value
TEST_F(PopplerPSFileTest_2256, LargeNPages_2256) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerPSFile *ps_file = poppler_ps_file_new(document, "/tmp/test_large_np_2256.ps", 0, 1000);
    ASSERT_NE(ps_file, nullptr);

    EXPECT_EQ(ps_file->first_page, 1);
    EXPECT_EQ(ps_file->last_page, 1000);

    g_object_unref(ps_file);
}
