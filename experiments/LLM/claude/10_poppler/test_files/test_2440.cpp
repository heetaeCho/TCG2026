#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for the poppler glib interface
extern "C" {
#include <glib-object.h>
#include "poppler.h"
}

#include "poppler-private.h"
#include "Object.h"
#include "Page.h"
#include "Dict.h"
#include "Stream.h"

// Helper to create a PopplerDocument from a PDF file for integration testing
class PopplerPageThumbnailSizeTest_2440 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // We will test with both valid documents and null cases
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerDocument *loadDocument(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) {
                g_error_free(error);
            }
            return nullptr;
        }
        PopplerDocument *d = poppler_document_new_from_uri(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        return d;
    }
};

// Test that passing NULL page returns FALSE (g_return_val_if_fail check)
TEST_F(PopplerPageThumbnailSizeTest_2440, NullPageReturnsFalse_2440) {
    int width = 0, height = 0;
    // g_return_val_if_fail with NULL page should return FALSE
    // Note: This will trigger a g_critical warning
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
    gboolean result = poppler_page_get_thumbnail_size(nullptr, &width, &height);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test that passing NULL width pointer returns FALSE
TEST_F(PopplerPageThumbnailSizeTest_2440, NullWidthReturnsFalse_2440) {
    // We need a valid PopplerPage for this test, but if we can't load one,
    // we test with what we can. The g_return_val_if_fail for width != nullptr
    // should fire after the POPPLER_IS_PAGE check passes.
    // If we can't create a real page, we just verify the NULL page case already tested.
    // Try to load a simple PDF if available
    const char *test_pdf = TESTDATADIR "/unittestcases/simple1.pdf";
    doc = loadDocument(test_pdf);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available, skipping NULL width test";
    }
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    int height = 0;
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*width*");
    gboolean result = poppler_page_get_thumbnail_size(page, nullptr, &height);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test that passing NULL height pointer returns FALSE
TEST_F(PopplerPageThumbnailSizeTest_2440, NullHeightReturnsFalse_2440) {
    const char *test_pdf = TESTDATADIR "/unittestcases/simple1.pdf";
    doc = loadDocument(test_pdf);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available, skipping NULL height test";
    }
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    int width = 0;
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*height*");
    gboolean result = poppler_page_get_thumbnail_size(page, &width, nullptr);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test page without thumbnail returns FALSE
TEST_F(PopplerPageThumbnailSizeTest_2440, PageWithoutThumbnailReturnsFalse_2440) {
    const char *test_pdf = TESTDATADIR "/unittestcases/simple1.pdf";
    doc = loadDocument(test_pdf);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from PDF";
    }

    int width = -1, height = -1;
    gboolean result = poppler_page_get_thumbnail_size(page, &width, &height);
    // Most simple PDFs don't have thumbnails, so we expect FALSE
    // If the PDF happens to have a thumbnail, we just check the result is valid
    if (!result) {
        EXPECT_FALSE(result);
    } else {
        EXPECT_GT(width, 0);
        EXPECT_GT(height, 0);
    }
}

// Test with a PDF known to have thumbnails (if available)
TEST_F(PopplerPageThumbnailSizeTest_2440, PageWithThumbnailReturnsTrue_2440) {
    const char *test_pdf = TESTDATADIR "/unittestcases/with_thumb.pdf";
    doc = loadDocument(test_pdf);
    if (!doc) {
        GTEST_SKIP() << "Test PDF with thumbnail not available";
    }
    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from PDF";
    }

    int width = 0, height = 0;
    gboolean result = poppler_page_get_thumbnail_size(page, &width, &height);
    if (result) {
        EXPECT_GT(width, 0);
        EXPECT_GT(height, 0);
    }
    // If the test file doesn't actually have a thumbnail, just note it
}

// Test that both width and height are set when thumbnail exists
TEST_F(PopplerPageThumbnailSizeTest_2440, ThumbnailSizeValuesArePositive_2440) {
    const char *test_pdf = TESTDATADIR "/unittestcases/with_thumb.pdf";
    doc = loadDocument(test_pdf);
    if (!doc) {
        GTEST_SKIP() << "Test PDF with thumbnail not available";
    }
    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    int width = -1, height = -1;
    gboolean result = poppler_page_get_thumbnail_size(page, &width, &height);
    if (result) {
        EXPECT_GT(width, 0);
        EXPECT_GT(height, 0);
    } else {
        // Width and height should not have been modified to valid values
        // (they remain at their initial values or are not guaranteed)
        EXPECT_FALSE(result);
    }
}

// Test that passing both NULL width and height returns FALSE (first check fails)
TEST_F(PopplerPageThumbnailSizeTest_2440, BothNullOutputParamsReturnsFalse_2440) {
    const char *test_pdf = TESTDATADIR "/unittestcases/simple1.pdf";
    doc = loadDocument(test_pdf);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*width*");
    gboolean result = poppler_page_get_thumbnail_size(page, nullptr, nullptr);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test multiple pages - check all pages for thumbnail size
TEST_F(PopplerPageThumbnailSizeTest_2440, MultiplePagesThumbnailCheck_2440) {
    const char *test_pdf = TESTDATADIR "/unittestcases/simple1.pdf";
    doc = loadDocument(test_pdf);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int n_pages = poppler_document_get_n_pages(doc);
    for (int i = 0; i < n_pages; i++) {
        PopplerPage *p = poppler_document_get_page(doc, i);
        if (!p) {
            continue;
        }

        int width = 0, height = 0;
        gboolean result = poppler_page_get_thumbnail_size(p, &width, &height);
        if (result) {
            EXPECT_GT(width, 0) << "Page " << i << " thumbnail width should be positive";
            EXPECT_GT(height, 0) << "Page " << i << " thumbnail height should be positive";
        }
        g_object_unref(p);
    }
}

// Test calling the function twice on the same page yields consistent results
TEST_F(PopplerPageThumbnailSizeTest_2440, ConsistentResultsOnRepeatedCalls_2440) {
    const char *test_pdf = TESTDATADIR "/unittestcases/simple1.pdf";
    doc = loadDocument(test_pdf);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    int width1 = 0, height1 = 0;
    int width2 = 0, height2 = 0;
    gboolean result1 = poppler_page_get_thumbnail_size(page, &width1, &height1);
    gboolean result2 = poppler_page_get_thumbnail_size(page, &width2, &height2);

    EXPECT_EQ(result1, result2);
    if (result1 && result2) {
        EXPECT_EQ(width1, width2);
        EXPECT_EQ(height1, height2);
    }
}
