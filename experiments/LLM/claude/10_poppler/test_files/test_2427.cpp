#include <glib-object.h>
#include <glib.h>
#include "poppler.h"
#include "poppler-private.h"
#include <gtest/gtest.h>

class PopplerPageGetIndexTest_2427 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    
    void SetUp() override {
        // We need a valid PDF document to get pages from.
        // Create a minimal PDF in memory or load from a test file.
        // Using a simple approach: create a minimal PDF in a temp file.
        const char *minimal_pdf = 
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R 4 0 R]/Count 2>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "4 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000184 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n"
            "253\n"
            "%%EOF\n";
        
        gchar *tmp_path = nullptr;
        GError *error = nullptr;
        gint fd = g_file_open_tmp("test_poppler_XXXXXX.pdf", &tmp_path, &error);
        if (fd != -1 && tmp_path) {
            gssize len = strlen(minimal_pdf);
            write(fd, minimal_pdf, len);
            close(fd);
            
            gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
            if (uri) {
                document = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            g_unlink(tmp_path);
            g_free(tmp_path);
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
};

TEST_F(PopplerPageGetIndexTest_2427, FirstPageReturnsIndexZero_2427) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    int index = poppler_page_get_index(page);
    EXPECT_EQ(index, 0);
    
    g_object_unref(page);
}

TEST_F(PopplerPageGetIndexTest_2427, SecondPageReturnsIndexOne_2427) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    if (n_pages < 2) {
        GTEST_SKIP() << "Document has fewer than 2 pages";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 1);
    ASSERT_NE(page, nullptr);
    
    int index = poppler_page_get_index(page);
    EXPECT_EQ(index, 1);
    
    g_object_unref(page);
}

TEST_F(PopplerPageGetIndexTest_2427, NullPageReturnsZero_2427) {
    // According to g_return_val_if_fail, passing NULL should return 0
    // This may produce a g_critical warning, but should not crash.
    // We suppress the expected warning for a cleaner test output.
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
    
    int index = poppler_page_get_index(nullptr);
    EXPECT_EQ(index, 0);
    
    g_test_assert_expected_messages();
}

TEST_F(PopplerPageGetIndexTest_2427, PageIndexMatchesRequestedPage_2427) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    
    for (int i = 0; i < n_pages; i++) {
        PopplerPage *page = poppler_document_get_page(document, i);
        ASSERT_NE(page, nullptr) << "Failed to get page " << i;
        
        int index = poppler_page_get_index(page);
        EXPECT_EQ(index, i) << "Page index mismatch for page " << i;
        
        g_object_unref(page);
    }
}

TEST_F(PopplerPageGetIndexTest_2427, CalledMultipleTimesReturnsSameValue_2427) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    int index1 = poppler_page_get_index(page);
    int index2 = poppler_page_get_index(page);
    int index3 = poppler_page_get_index(page);
    
    EXPECT_EQ(index1, index2);
    EXPECT_EQ(index2, index3);
    EXPECT_EQ(index1, 0);
    
    g_object_unref(page);
}
