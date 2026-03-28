#include <gtest/gtest.h>
#include <cairo.h>

extern "C" {
#include "poppler.h"
#include "poppler-page.h"
#include "poppler-document.h"
}

class PopplerPageRenderTest_2434 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    cairo_surface_t *surface = nullptr;
    cairo_t *cr = nullptr;

    void SetUp() override {
        // Try to load a simple PDF for testing
        // We use a minimal approach: create a document from a file if available
        GError *error = nullptr;
        
        // Attempt to create a minimal PDF in memory
        // First try loading from a common test file path
        const char *test_pdf_path = nullptr;
        
        // Try to find a test PDF - we'll generate one using cairo
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 200, 200);
        cr = cairo_create(surface);
    }

    void TearDown() override {
        if (cr) {
            cairo_destroy(cr);
            cr = nullptr;
        }
        if (surface) {
            cairo_surface_destroy(surface);
            surface = nullptr;
        }
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    bool LoadTestDocument(const char *uri) {
        GError *error = nullptr;
        doc = poppler_document_new_from_file(uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            return false;
        }
        if (doc && poppler_document_get_n_pages(doc) > 0) {
            page = poppler_document_get_page(doc, 0);
            return page != nullptr;
        }
        return false;
    }

    // Helper to create a minimal PDF in a temp file and load it
    bool CreateAndLoadMinimalPDF() {
        const char *tmp_path = "/tmp/test_poppler_2434.pdf";
        
        // Create a minimal PDF using cairo
        cairo_surface_t *pdf_surface = cairo_pdf_surface_create(tmp_path, 200, 200);
        cairo_t *pdf_cr = cairo_create(pdf_surface);
        cairo_set_source_rgb(pdf_cr, 1.0, 0.0, 0.0);
        cairo_rectangle(pdf_cr, 10, 10, 100, 100);
        cairo_fill(pdf_cr);
        cairo_show_page(pdf_cr);
        cairo_destroy(pdf_cr);
        cairo_surface_destroy(pdf_surface);
        
        gchar *uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
        if (!uri) return false;
        
        bool result = LoadTestDocument(uri);
        g_free(uri);
        return result;
    }
};

// Test that poppler_page_render does not crash with a valid page and valid cairo context
TEST_F(PopplerPageRenderTest_2434, RenderValidPageDoesNotCrash_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ASSERT_NE(page, nullptr);
    ASSERT_NE(cr, nullptr);
    
    // Should not crash or throw
    poppler_page_render(page, cr);
    
    // Verify cairo is still in a good state
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test rendering to a surface and verify something was drawn
TEST_F(PopplerPageRenderTest_2434, RenderProducesOutput_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    // Clear surface to white first
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);
    
    // Get pixel data before render
    cairo_surface_flush(surface);
    unsigned char *data_before = cairo_image_surface_get_data(surface);
    int stride = cairo_image_surface_get_stride(surface);
    int height = cairo_image_surface_get_height(surface);
    
    // Copy the data before rendering
    std::vector<unsigned char> before(data_before, data_before + stride * height);
    
    poppler_page_render(page, cr);
    
    cairo_surface_flush(surface);
    unsigned char *data_after = cairo_image_surface_get_data(surface);
    
    // Check if any pixels changed (the test PDF has a red rectangle)
    bool pixels_changed = false;
    for (int i = 0; i < stride * height; ++i) {
        if (before[i] != data_after[i]) {
            pixels_changed = true;
            break;
        }
    }
    
    EXPECT_TRUE(pixels_changed) << "Rendering should modify at least some pixels";
}

// Test rendering with different cairo surface sizes
TEST_F(PopplerPageRenderTest_2434, RenderToSmallSurface_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    // Create a very small surface
    cairo_surface_t *small_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    cairo_t *small_cr = cairo_create(small_surface);
    
    // Should not crash even on a tiny surface
    poppler_page_render(page, small_cr);
    
    EXPECT_EQ(cairo_status(small_cr), CAIRO_STATUS_SUCCESS);
    
    cairo_destroy(small_cr);
    cairo_surface_destroy(small_surface);
}

// Test rendering with a scaled cairo context
TEST_F(PopplerPageRenderTest_2434, RenderWithScaledContext_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_scale(cr, 2.0, 2.0);
    
    // Should not crash with a scaled context
    poppler_page_render(page, cr);
    
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test rendering with a translated cairo context
TEST_F(PopplerPageRenderTest_2434, RenderWithTranslatedContext_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_translate(cr, 50.0, 50.0);
    
    poppler_page_render(page, cr);
    
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test rendering with a rotated cairo context
TEST_F(PopplerPageRenderTest_2434, RenderWithRotatedContext_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_rotate(cr, 0.5);
    
    poppler_page_render(page, cr);
    
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test rendering the same page twice
TEST_F(PopplerPageRenderTest_2434, RenderSamePageTwice_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    poppler_page_render(page, cr);
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
    
    // Render again - should not crash
    poppler_page_render(page, cr);
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test rendering to an RGBA surface (with alpha)
TEST_F(PopplerPageRenderTest_2434, RenderToRGBASurface_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_surface_t *rgba_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 300, 300);
    cairo_t *rgba_cr = cairo_create(rgba_surface);
    
    poppler_page_render(page, rgba_cr);
    
    EXPECT_EQ(cairo_status(rgba_cr), CAIRO_STATUS_SUCCESS);
    
    cairo_destroy(rgba_cr);
    cairo_surface_destroy(rgba_surface);
}

// Test rendering to an RGB24 surface (no alpha)
TEST_F(PopplerPageRenderTest_2434, RenderToRGB24Surface_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_surface_t *rgb_surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 300, 300);
    cairo_t *rgb_cr = cairo_create(rgb_surface);
    
    poppler_page_render(page, rgb_cr);
    
    EXPECT_EQ(cairo_status(rgb_cr), CAIRO_STATUS_SUCCESS);
    
    cairo_destroy(rgb_cr);
    cairo_surface_destroy(rgb_surface);
}

// Test that rendering with a clipped region works
TEST_F(PopplerPageRenderTest_2434, RenderWithClipping_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_rectangle(cr, 10, 10, 50, 50);
    cairo_clip(cr);
    
    poppler_page_render(page, cr);
    
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test rendering with identity matrix
TEST_F(PopplerPageRenderTest_2434, RenderWithIdentityMatrix_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_matrix_t identity;
    cairo_matrix_init_identity(&identity);
    cairo_set_matrix(cr, &identity);
    
    poppler_page_render(page, cr);
    
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test that PopplerRenderAnnotsFlags enum values are correct
TEST_F(PopplerPageRenderTest_2434, AnnotsFlagsValues_2434) {
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_NONE, 0);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_TEXT, 1);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_LINK, 2);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_FREETEXT, 4);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_LINE, 8);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_SQUARE, 16);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_CIRCLE, 32);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_POLYGON, 64);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_POLYLINE, 128);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_HIGHLIGHT, 256);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_UNDERLINE, 512);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_SQUIGGLY, 1024);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_STRIKEOUT, 2048);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_STAMP, 4096);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_CARET, 8192);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_INK, 16384);
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_ALL, 67108863);
}

// Test rendering to a zero-scaled context (degenerate transform)
TEST_F(PopplerPageRenderTest_2434, RenderWithZeroScale_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_scale(cr, 0.0, 0.0);
    
    // This may set cairo to an error state but should not crash
    poppler_page_render(page, cr);
    
    // We just verify it didn't crash; cairo status may or may not be success
}

// Test rendering preserves cairo save/restore state
TEST_F(PopplerPageRenderTest_2434, RenderPreservesCairoState_2434) {
    if (!CreateAndLoadMinimalPDF()) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    
    poppler_page_render(page, cr);
    
    // We should be able to restore without issues
    cairo_restore(cr);
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}
