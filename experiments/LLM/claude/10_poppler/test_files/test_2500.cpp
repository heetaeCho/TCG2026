#include <glib.h>
#include <glib-object.h>
#include "poppler.h"
#include "poppler-page.h"
#include "poppler-private.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class PopplerPageGetTextLayoutTest_2500 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Try to load a simple PDF for testing
        GError *error = nullptr;
        // Create a minimal PDF in memory or load from a test file
        // We'll attempt to create a document from a file URI
        gchar *uri = nullptr;
        gchar *cwd = g_get_current_dir();
        gchar *test_pdf_path = g_build_filename(cwd, "test_page_layout.pdf", NULL);
        
        // Check if test PDF exists, if not we'll create a minimal one
        if (!g_file_test(test_pdf_path, G_FILE_TEST_EXISTS)) {
            // Create a minimal valid PDF file
            const char *minimal_pdf =
                "%PDF-1.0\n"
                "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Contents 4 0 R/Resources<</Font<</F1 5 0 R>>>>>>endobj\n"
                "4 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello World) Tj ET\nendstream\nendobj\n"
                "5 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
                "xref\n0 6\n"
                "0000000000 65535 f \n"
                "0000000009 00000 n \n"
                "0000000058 00000 n \n"
                "0000000115 00000 n \n"
                "0000000266 00000 n \n"
                "0000000360 00000 n \n"
                "trailer<</Size 6/Root 1 0 R>>\n"
                "startxref\n430\n%%EOF\n";
            g_file_set_contents(test_pdf_path, minimal_pdf, -1, &error);
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }

        uri = g_filename_to_uri(test_pdf_path, NULL, &error);
        if (error) {
            g_error_free(error);
            error = nullptr;
        }

        if (uri) {
            document = poppler_document_new_from_file(uri, NULL, &error);
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            g_free(uri);
        }

        if (document) {
            page = poppler_document_get_page(document, 0);
        }

        g_free(test_pdf_path);
        g_free(cwd);
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

// Test that passing NULL page returns FALSE
TEST_F(PopplerPageGetTextLayoutTest_2500, NullPageReturnsFalse_2500) {
    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    // Passing NULL as page should return FALSE due to g_return_val_if_fail
    // Note: g_return_val_if_fail with POPPLER_IS_PAGE(NULL) should fail
    gboolean result = poppler_page_get_text_layout(nullptr, &rectangles, &n_rectangles);
    EXPECT_EQ(result, FALSE);
}

// Test normal operation with a valid page
TEST_F(PopplerPageGetTextLayoutTest_2500, ValidPageReturnsResult_2500) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout(page, &rectangles, &n_rectangles);

    // The function should succeed (return TRUE or FALSE depending on content)
    // Either way, the call should not crash
    if (result == TRUE) {
        // If there is text, we should have rectangles
        EXPECT_NE(rectangles, nullptr);
        EXPECT_GT(n_rectangles, 0u);
        g_free(rectangles);
    } else {
        // If no text layout found, n_rectangles should be 0
        EXPECT_EQ(n_rectangles, 0u);
    }
}

// Test that rectangles pointer is properly populated
TEST_F(PopplerPageGetTextLayoutTest_2500, RectanglesAreValid_2500) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout(page, &rectangles, &n_rectangles);

    if (result == TRUE && n_rectangles > 0) {
        // Check that rectangle coordinates are reasonable (within page bounds)
        double page_width, page_height;
        poppler_page_get_size(page, &page_width, &page_height);

        for (guint i = 0; i < n_rectangles; i++) {
            // Rectangles should have coordinates within or near the page dimensions
            EXPECT_GE(rectangles[i].x1, -1.0) << "Rectangle " << i << " x1 out of range";
            EXPECT_GE(rectangles[i].y1, -1.0) << "Rectangle " << i << " y1 out of range";
            EXPECT_LE(rectangles[i].x2, page_width + 1.0) << "Rectangle " << i << " x2 out of range";
            EXPECT_LE(rectangles[i].y2, page_height + 1.0) << "Rectangle " << i << " y2 out of range";
        }
        g_free(rectangles);
    }
}

// Test calling the function multiple times yields consistent results
TEST_F(PopplerPageGetTextLayoutTest_2500, ConsistentResultsOnMultipleCalls_2500) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle *rectangles1 = nullptr;
    guint n_rectangles1 = 0;
    gboolean result1 = poppler_page_get_text_layout(page, &rectangles1, &n_rectangles1);

    PopplerRectangle *rectangles2 = nullptr;
    guint n_rectangles2 = 0;
    gboolean result2 = poppler_page_get_text_layout(page, &rectangles2, &n_rectangles2);

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(n_rectangles1, n_rectangles2);

    if (result1 == TRUE && n_rectangles1 > 0) {
        for (guint i = 0; i < n_rectangles1; i++) {
            EXPECT_DOUBLE_EQ(rectangles1[i].x1, rectangles2[i].x1);
            EXPECT_DOUBLE_EQ(rectangles1[i].y1, rectangles2[i].y1);
            EXPECT_DOUBLE_EQ(rectangles1[i].x2, rectangles2[i].x2);
            EXPECT_DOUBLE_EQ(rectangles1[i].y2, rectangles2[i].y2);
        }
    }

    if (rectangles1) g_free(rectangles1);
    if (rectangles2) g_free(rectangles2);
}

// Test with a document loaded from data (empty page)
class PopplerPageGetTextLayoutEmptyTest_2500 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        // Create a minimal PDF with an empty page (no text content)
        const char *minimal_pdf =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n198\n%%EOF\n";

        gchar *cwd = g_get_current_dir();
        gchar *test_pdf_path = g_build_filename(cwd, "test_empty_page.pdf", NULL);
        g_file_set_contents(test_pdf_path, minimal_pdf, -1, &error);
        if (error) {
            g_error_free(error);
            error = nullptr;
        }

        gchar *uri = g_filename_to_uri(test_pdf_path, NULL, &error);
        if (error) {
            g_error_free(error);
            error = nullptr;
        }

        if (uri) {
            document = poppler_document_new_from_file(uri, NULL, &error);
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            g_free(uri);
        }

        if (document) {
            page = poppler_document_get_page(document, 0);
        }

        g_free(test_pdf_path);
        g_free(cwd);
    }

    void TearDown() override {
        if (page) g_object_unref(page);
        if (document) g_object_unref(document);
    }
};

// Test empty page returns no text layout
TEST_F(PopplerPageGetTextLayoutEmptyTest_2500, EmptyPageLayout_2500) {
    if (!page) {
        GTEST_SKIP() << "Could not load empty test PDF page";
    }

    PopplerRectangle *rectangles = nullptr;
    guint n_rectangles = 0;

    gboolean result = poppler_page_get_text_layout(page, &rectangles, &n_rectangles);

    // Empty page should have no text layout
    if (result == FALSE) {
        EXPECT_EQ(n_rectangles, 0u);
    }
    // Even if TRUE is returned, n_rectangles might be 0 for an empty page
    if (n_rectangles == 0) {
        EXPECT_EQ(rectangles, nullptr);
    } else {
        g_free(rectangles);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
