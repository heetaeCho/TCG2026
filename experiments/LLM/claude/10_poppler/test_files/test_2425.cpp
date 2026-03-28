#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-private.h"

#include <string>
#include <cstdlib>

class PopplerPageTest_2425 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    
    void SetUp() override {
        // Create a minimal PDF in memory to get a valid document and page
        // We need a real PDF document to test page functionality
        GError *error = nullptr;
        
        // Try to create a document from a minimal PDF byte stream
        const char *minimal_pdf = 
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "206\n"
            "%%EOF\n";
        
        gsize len = strlen(minimal_pdf);
        document = poppler_document_new_from_data(minimal_pdf, (int)len, nullptr, &error);
        
        if (error) {
            g_error_free(error);
            document = nullptr;
        }
    }
    
    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

// Test that we can get a page from a document and it's valid
TEST_F(PopplerPageTest_2425, GetPageReturnsValidPage_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    g_object_unref(page);
}

// Test that getting an out-of-range page returns nullptr
TEST_F(PopplerPageTest_2425, GetPageOutOfRangeReturnsNull_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 100);
    EXPECT_EQ(page, nullptr);
}

// Test that getting a negative index page returns nullptr
TEST_F(PopplerPageTest_2425, GetPageNegativeIndexReturnsNull_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, -1);
    EXPECT_EQ(page, nullptr);
}

// Test page index
TEST_F(PopplerPageTest_2425, PageIndexIsCorrect_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    int index = poppler_page_get_index(page);
    EXPECT_EQ(index, 0);
    
    g_object_unref(page);
}

// Test page size retrieval
TEST_F(PopplerPageTest_2425, PageSizeIsPositive_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    
    EXPECT_GT(width, 0.0);
    EXPECT_GT(height, 0.0);
    
    g_object_unref(page);
}

// Test that page size matches expected values for our minimal PDF (612x792)
TEST_F(PopplerPageTest_2425, PageSizeMatchesMediaBox_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
    
    g_object_unref(page);
}

// Test getting text from an empty page returns empty or null
TEST_F(PopplerPageTest_2425, EmptyPageTextIsEmpty_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    char *text = poppler_page_get_text(page);
    if (text) {
        EXPECT_STREQ(text, "");
        g_free(text);
    }
    
    g_object_unref(page);
}

// Test that page finalize works properly (unreffing the page doesn't crash)
TEST_F(PopplerPageTest_2425, PageUnrefDoesNotCrash_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    // This triggers poppler_page_finalize internally
    EXPECT_NO_FATAL_FAILURE(g_object_unref(page));
}

// Test that the document reference count is managed properly
TEST_F(PopplerPageTest_2425, PageHoldsDocumentReference_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    guint ref_before = G_OBJECT(document)->ref_count;
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    guint ref_with_page = G_OBJECT(document)->ref_count;
    EXPECT_GT(ref_with_page, ref_before);
    
    g_object_unref(page);
    
    guint ref_after = G_OBJECT(document)->ref_count;
    EXPECT_EQ(ref_after, ref_before);
}

// Test multiple pages can be obtained and released without issues
TEST_F(PopplerPageTest_2425, MultiplePageGetAndRelease_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    // Get the same page multiple times
    PopplerPage *page1 = poppler_document_get_page(document, 0);
    PopplerPage *page2 = poppler_document_get_page(document, 0);
    
    ASSERT_NE(page1, nullptr);
    ASSERT_NE(page2, nullptr);
    
    g_object_unref(page1);
    g_object_unref(page2);
}

// Test poppler_page_get_label on first page
TEST_F(PopplerPageTest_2425, PageLabelIsNotNull_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    gchar *label = poppler_page_get_label(page);
    // Label should be non-null (at minimum "1" for first page)
    EXPECT_NE(label, nullptr);
    if (label) {
        g_free(label);
    }
    
    g_object_unref(page);
}

// Test getting page size with NULL pointers doesn't crash
TEST_F(PopplerPageTest_2425, PageSizeWithNullPtrDoesNotCrash_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    // Should not crash when passing NULL for width or height
    EXPECT_NO_FATAL_FAILURE(poppler_page_get_size(page, nullptr, nullptr));
    
    double width = 0;
    EXPECT_NO_FATAL_FAILURE(poppler_page_get_size(page, &width, nullptr));
    EXPECT_GT(width, 0.0);
    
    double height = 0;
    EXPECT_NO_FATAL_FAILURE(poppler_page_get_size(page, nullptr, &height));
    EXPECT_GT(height, 0.0);
    
    g_object_unref(page);
}

// Test that page is a GObject
TEST_F(PopplerPageTest_2425, PageIsGObject_2425) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(document, 0);
    ASSERT_NE(page, nullptr);
    
    EXPECT_TRUE(G_IS_OBJECT(page));
    EXPECT_TRUE(POPPLER_IS_PAGE(page));
    
    g_object_unref(page);
}
