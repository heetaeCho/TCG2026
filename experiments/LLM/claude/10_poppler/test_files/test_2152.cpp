#include <gtest/gtest.h>
#include <glib-object.h>

// Include poppler glib headers
extern "C" {
#include "poppler-document.h"
#include "poppler-page.h"
}

class PopplerDocumentGetPageTest_2152 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Load a known PDF test file
        GError *error = nullptr;
        // Try to create a document from a simple PDF file
        gchar *uri = g_filename_to_uri("../test/unittestcases/simple1.pdf", nullptr, &error);
        if (uri) {
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
        // If the above path doesn't work, try alternative paths
        if (!document) {
            uri = g_filename_to_uri("test/unittestcases/simple1.pdf", nullptr, &error);
            if (uri) {
                document = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

// Test that getting the first page (index 0) returns a valid page
TEST_F(PopplerDocumentGetPageTest_2152, GetFirstPageReturnsValidPage_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int n_pages = poppler_document_get_n_pages(document);
    ASSERT_GT(n_pages, 0);

    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    g_object_unref(page);
}

// Test that getting the last page returns a valid page
TEST_F(PopplerDocumentGetPageTest_2152, GetLastPageReturnsValidPage_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int n_pages = poppler_document_get_n_pages(document);
    ASSERT_GT(n_pages, 0);

    PopplerPage *page = poppler_document_get_page(document, n_pages - 1);
    ASSERT_NE(page, nullptr);
    g_object_unref(page);
}

// Test that a negative index returns NULL
TEST_F(PopplerDocumentGetPageTest_2152, NegativeIndexReturnsNull_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerPage *page = poppler_document_get_page(document, -1);
    EXPECT_EQ(page, nullptr);
}

// Test that an index equal to n_pages returns NULL (out of bounds)
TEST_F(PopplerDocumentGetPageTest_2152, IndexEqualToNPagesReturnsNull_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int n_pages = poppler_document_get_n_pages(document);

    PopplerPage *page = poppler_document_get_page(document, n_pages);
    EXPECT_EQ(page, nullptr);
}

// Test that an index beyond n_pages returns NULL
TEST_F(PopplerDocumentGetPageTest_2152, IndexBeyondNPagesReturnsNull_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int n_pages = poppler_document_get_n_pages(document);

    PopplerPage *page = poppler_document_get_page(document, n_pages + 100);
    EXPECT_EQ(page, nullptr);
}

// Test that the returned page has the correct index
TEST_F(PopplerDocumentGetPageTest_2152, ReturnedPageHasCorrectIndex_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int n_pages = poppler_document_get_n_pages(document);
    ASSERT_GT(n_pages, 0);

    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);

    int page_index = poppler_page_get_index(page);
    EXPECT_EQ(page_index, 0);

    g_object_unref(page);
}

// Test that getting all pages sequentially works
TEST_F(PopplerDocumentGetPageTest_2152, GetAllPagesSequentially_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int n_pages = poppler_document_get_n_pages(document);
    ASSERT_GT(n_pages, 0);

    for (int i = 0; i < n_pages; i++) {
        PopplerPage *page = poppler_document_get_page(document, i);
        ASSERT_NE(page, nullptr) << "Page at index " << i << " should not be null";
        EXPECT_EQ(poppler_page_get_index(page), i);
        g_object_unref(page);
    }
}

// Test getting the same page twice returns valid pages
TEST_F(PopplerDocumentGetPageTest_2152, GetSamePageTwice_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int n_pages = poppler_document_get_n_pages(document);
    ASSERT_GT(n_pages, 0);

    PopplerPage *page1 = poppler_document_get_page(document, 0);
    PopplerPage *page2 = poppler_document_get_page(document, 0);

    ASSERT_NE(page1, nullptr);
    ASSERT_NE(page2, nullptr);

    EXPECT_EQ(poppler_page_get_index(page1), 0);
    EXPECT_EQ(poppler_page_get_index(page2), 0);

    g_object_unref(page1);
    g_object_unref(page2);
}

// Test with a very large negative index
TEST_F(PopplerDocumentGetPageTest_2152, VeryLargeNegativeIndexReturnsNull_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerPage *page = poppler_document_get_page(document, -999999);
    EXPECT_EQ(page, nullptr);
}

// Test with a very large positive index
TEST_F(PopplerDocumentGetPageTest_2152, VeryLargePositiveIndexReturnsNull_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerPage *page = poppler_document_get_page(document, 999999);
    EXPECT_EQ(page, nullptr);
}

// Test that the returned page is a valid GObject
TEST_F(PopplerDocumentGetPageTest_2152, ReturnedPageIsValidGObject_2152) {
    if (!document) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int n_pages = poppler_document_get_n_pages(document);
    ASSERT_GT(n_pages, 0);

    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(POPPLER_IS_PAGE(page));

    g_object_unref(page);
}
