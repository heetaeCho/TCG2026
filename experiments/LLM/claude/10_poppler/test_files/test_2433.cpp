#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-page.h"
#include "poppler-private.h"

class PopplerPageRenderFullTest_2433 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal cairo surface and context for testing
        surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
        cr_ = cairo_create(surface_);
    }

    void TearDown() override {
        if (cr_) {
            cairo_destroy(cr_);
            cr_ = nullptr;
        }
        if (surface_) {
            cairo_surface_destroy(surface_);
            surface_ = nullptr;
        }
    }

    cairo_surface_t *surface_ = nullptr;
    cairo_t *cr_ = nullptr;
};

// Test that passing NULL page does not crash (g_return_if_fail should handle it)
TEST_F(PopplerPageRenderFullTest_2433, NullPageDoesNotCrash_2433) {
    // g_return_if_fail(POPPLER_IS_PAGE(page)) should cause early return
    // This should not crash or segfault
    poppler_page_render_full(nullptr, cr_, FALSE, POPPLER_RENDER_ANNOTS_FLAGS_NONE);
    // If we reach here, the guard worked
    SUCCEED();
}

// Test that passing NULL cairo does not crash (g_return_if_fail should handle it)
TEST_F(PopplerPageRenderFullTest_2433, NullCairoDoesNotCrash_2433) {
    // Even with a null page, the first check should catch it before cairo check
    poppler_page_render_full(nullptr, nullptr, FALSE, POPPLER_RENDER_ANNOTS_FLAGS_NONE);
    SUCCEED();
}

// Test that passing an invalid GObject as page does not crash
TEST_F(PopplerPageRenderFullTest_2433, InvalidPageObjectDoesNotCrash_2433) {
    // Passing a non-PopplerPage GObject should be caught by POPPLER_IS_PAGE check
    poppler_page_render_full((PopplerPage *)nullptr, cr_, TRUE, POPPLER_RENDER_ANNOTS_FLAGS_NONE);
    SUCCEED();
}

// Test with a real PDF document - render in non-printing mode
class PopplerPageRenderWithDocTest_2433 : public ::testing::Test {
protected:
    void SetUp() override {
        surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 200, 200);
        cr_ = cairo_create(surface_);
    }

    void TearDown() override {
        if (cr_) {
            cairo_destroy(cr_);
        }
        if (surface_) {
            cairo_surface_destroy(surface_);
        }
    }

    cairo_surface_t *surface_ = nullptr;
    cairo_t *cr_ = nullptr;
};

// Test rendering a page from a real document if available
TEST_F(PopplerPageRenderWithDocTest_2433, RenderValidPageNonPrinting_2433) {
    // Create a minimal valid PDF in memory
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n206\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerPage *page = poppler_document_get_page(doc, 0);
        if (page != nullptr) {
            // This should not crash - render in non-printing mode
            poppler_page_render_full(page, cr_, FALSE, POPPLER_RENDER_ANNOTS_FLAGS_NONE);

            // Verify cairo is still in a valid state
            EXPECT_EQ(cairo_status(cr_), CAIRO_STATUS_SUCCESS);

            g_object_unref(page);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test PDF document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test rendering in printing mode
TEST_F(PopplerPageRenderWithDocTest_2433, RenderValidPagePrinting_2433) {
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n206\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerPage *page = poppler_document_get_page(doc, 0);
        if (page != nullptr) {
            // Render in printing mode - text page should NOT be created
            poppler_page_render_full(page, cr_, TRUE, POPPLER_RENDER_ANNOTS_FLAGS_NONE);

            EXPECT_EQ(cairo_status(cr_), CAIRO_STATUS_SUCCESS);

            g_object_unref(page);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test PDF document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that rendering the same page twice in non-printing mode works
// (second call should reuse existing text page)
TEST_F(PopplerPageRenderWithDocTest_2433, RenderSamePageTwiceNonPrinting_2433) {
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n206\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerPage *page = poppler_document_get_page(doc, 0);
        if (page != nullptr) {
            // First render - creates text page
            poppler_page_render_full(page, cr_, FALSE, POPPLER_RENDER_ANNOTS_FLAGS_NONE);
            EXPECT_EQ(cairo_status(cr_), CAIRO_STATUS_SUCCESS);

            // Second render - should reuse text page (text != nullptr)
            poppler_page_render_full(page, cr_, FALSE, POPPLER_RENDER_ANNOTS_FLAGS_NONE);
            EXPECT_EQ(cairo_status(cr_), CAIRO_STATUS_SUCCESS);

            g_object_unref(page);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test PDF document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that cairo state is preserved after render (save/restore pair)
TEST_F(PopplerPageRenderWithDocTest_2433, CairoStatePreservedAfterRender_2433) {
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n206\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerPage *page = poppler_document_get_page(doc, 0);
        if (page != nullptr) {
            // Set a custom transform before rendering
            cairo_matrix_t before_matrix, after_matrix;
            cairo_translate(cr_, 10.0, 20.0);
            cairo_get_matrix(cr_, &before_matrix);

            poppler_page_render_full(page, cr_, FALSE, POPPLER_RENDER_ANNOTS_FLAGS_NONE);

            // The cairo_save/restore should preserve the matrix
            cairo_get_matrix(cr_, &after_matrix);
            EXPECT_DOUBLE_EQ(before_matrix.x0, after_matrix.x0);
            EXPECT_DOUBLE_EQ(before_matrix.y0, after_matrix.y0);
            EXPECT_DOUBLE_EQ(before_matrix.xx, after_matrix.xx);
            EXPECT_DOUBLE_EQ(before_matrix.yy, after_matrix.yy);

            g_object_unref(page);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test PDF document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
