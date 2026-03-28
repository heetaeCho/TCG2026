#include <glib-object.h>
#include <gtest/gtest.h>
#include "poppler.h"
#include "poppler-page.h"
#include "poppler-private.h"
#include "poppler-document.h"

class PopplerPageGetTextForAreaTest_2445 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        // Try to load a test PDF. We'll use a minimal approach.
        // If no test PDF is available, we'll mark tests as skipped.
        gchar *uri = nullptr;
        gchar *cwd = g_get_current_dir();
        gchar *path = g_build_filename(cwd, "test.pdf", NULL);
        
        if (g_file_test(path, G_FILE_TEST_EXISTS)) {
            uri = g_filename_to_uri(path, NULL, NULL);
            doc = poppler_document_new_from_file(uri, NULL, &error);
            if (doc) {
                page = poppler_document_get_page(doc, 0);
            }
            g_free(uri);
        }
        g_free(path);
        g_free(cwd);
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that passing NULL page returns NULL
TEST_F(PopplerPageGetTextForAreaTest_2445, NullPageReturnsNull_2445) {
    PopplerRectangle area;
    area.x1 = 0;
    area.y1 = 0;
    area.x2 = 100;
    area.y2 = 100;
    
    // Expect g_return_val_if_fail to trigger and return NULL
    char *result = poppler_page_get_text_for_area(NULL, &area);
    EXPECT_EQ(result, nullptr);
}

// Test that passing NULL area returns NULL
TEST_F(PopplerPageGetTextForAreaTest_2445, NullAreaReturnsNull_2445) {
    if (!page) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    char *result = poppler_page_get_text_for_area(page, NULL);
    EXPECT_EQ(result, nullptr);
}

// Test that passing both NULL returns NULL
TEST_F(PopplerPageGetTextForAreaTest_2445, BothNullReturnsNull_2445) {
    char *result = poppler_page_get_text_for_area(NULL, NULL);
    EXPECT_EQ(result, nullptr);
}

// Test normal operation with a valid page and area
TEST_F(PopplerPageGetTextForAreaTest_2445, ValidPageAndAreaReturnsNonNull_2445) {
    if (!page) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerRectangle area;
    area.x1 = 0;
    area.y1 = 0;
    area.x2 = 500;
    area.y2 = 500;
    
    char *result = poppler_page_get_text_for_area(page, &area);
    // Result should be non-null (could be empty string if no text in area)
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test with zero-size area
TEST_F(PopplerPageGetTextForAreaTest_2445, ZeroSizeAreaReturnsEmptyOrNull_2445) {
    if (!page) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerRectangle area;
    area.x1 = 0;
    area.y1 = 0;
    area.x2 = 0;
    area.y2 = 0;
    
    char *result = poppler_page_get_text_for_area(page, &area);
    // With a zero-size area, we expect either NULL or an empty string
    if (result != nullptr) {
        EXPECT_STREQ(result, "");
        g_free(result);
    }
}

// Test with negative coordinates in area
TEST_F(PopplerPageGetTextForAreaTest_2445, NegativeCoordinatesArea_2445) {
    if (!page) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerRectangle area;
    area.x1 = -100;
    area.y1 = -100;
    area.x2 = -50;
    area.y2 = -50;
    
    char *result = poppler_page_get_text_for_area(page, &area);
    // Outside page bounds, expect empty string or non-null
    if (result != nullptr) {
        EXPECT_STREQ(result, "");
        g_free(result);
    }
}

// Test with very large area that covers entire page
TEST_F(PopplerPageGetTextForAreaTest_2445, LargeAreaCoversFullPage_2445) {
    if (!page) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerRectangle area;
    area.x1 = 0;
    area.y1 = 0;
    area.x2 = 10000;
    area.y2 = 10000;
    
    char *result = poppler_page_get_text_for_area(page, &area);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test that result is a valid UTF-8 string when text is returned
TEST_F(PopplerPageGetTextForAreaTest_2445, ReturnedTextIsValidUTF8_2445) {
    if (!page) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerRectangle area;
    area.x1 = 0;
    area.y1 = 0;
    area.x2 = 500;
    area.y2 = 500;
    
    char *result = poppler_page_get_text_for_area(page, &area);
    if (result != nullptr) {
        EXPECT_TRUE(g_utf8_validate(result, -1, NULL));
        g_free(result);
    }
}

// Test with inverted rectangle (x1 > x2, y1 > y2)
TEST_F(PopplerPageGetTextForAreaTest_2445, InvertedRectangle_2445) {
    if (!page) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerRectangle area;
    area.x1 = 500;
    area.y1 = 500;
    area.x2 = 0;
    area.y2 = 0;
    
    char *result = poppler_page_get_text_for_area(page, &area);
    // Should not crash; may return empty or valid text
    if (result != nullptr) {
        g_free(result);
    }
}
