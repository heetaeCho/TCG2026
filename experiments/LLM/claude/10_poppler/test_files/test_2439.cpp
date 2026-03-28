#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>

// We need to include the relevant headers for the types used
// Since render_selection is a static function in poppler-page.cc, we cannot directly
// test it from outside the translation unit. However, we can test the public API
// functions that use it, such as poppler_page_render_selection.

// For this test, we'll focus on testing what we can observe through the public
// poppler glib API.

extern "C" {
#include <poppler.h>
}

#include <cstring>
#include <string>
#include <memory>

// Helper to create a test PDF document in memory
static PopplerDocument *create_test_document_with_text() {
    // Create a minimal PDF with some text content for selection testing
    // We'll try to load from a simple PDF string
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
        "   /Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 44 >>\n"
        "stream\n"
        "BT /F1 12 Tf 100 700 Td (Hello World) Tj ET\n"
        "endstream\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000360 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "441\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GBytes *bytes = g_bytes_new(pdf_content, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    g_bytes_unref(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
    g_object_unref(stream);

    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

class PopplerPageRenderSelectionTest_2439 : public ::testing::Test {
protected:
    void SetUp() override {
        document = create_test_document_with_text();
        if (document) {
            page = poppler_document_get_page(document, 0);
        } else {
            page = nullptr;
        }
        // Create a cairo surface and context for rendering
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 612, 792);
        cr = cairo_create(surface);
    }

    void TearDown() override {
        if (cr) {
            cairo_destroy(cr);
        }
        if (surface) {
            cairo_surface_destroy(surface);
        }
        if (page) {
            g_object_unref(page);
        }
        if (document) {
            g_object_unref(document);
        }
    }

    PopplerDocument *document = nullptr;
    PopplerPage *page = nullptr;
    cairo_surface_t *surface = nullptr;
    cairo_t *cr = nullptr;
};

// Test that render_selection with GLYPH style does not crash
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionGlyphStyle_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 0.0, 0.0, 612.0, 792.0 };
    PopplerColor glyph_color = { 65535, 65535, 65535 };
    PopplerColor background_color = { 0, 0, 65535 };

    // This should not crash
    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test that render_selection with WORD style does not crash
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionWordStyle_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 0.0, 0.0, 612.0, 792.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 0, 0, 65535 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_WORD,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test that render_selection with LINE style does not crash
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionLineStyle_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 0.0, 0.0, 612.0, 792.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 65535, 0, 0 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_LINE,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test with a small selection rectangle (boundary condition)
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionSmallRect_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 100.0, 700.0, 101.0, 701.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 65535, 65535, 0 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test with zero-area selection rectangle (boundary)
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionZeroAreaRect_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 100.0, 700.0, 100.0, 700.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 65535, 65535, 0 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test with different color values (boundary: all zeros)
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionBlackColors_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 0.0, 0.0, 612.0, 792.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 0, 0, 0 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test with maximum color values
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionMaxColors_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 0.0, 0.0, 612.0, 792.0 };
    PopplerColor glyph_color = { 65535, 65535, 65535 };
    PopplerColor background_color = { 65535, 65535, 65535 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test rendering selection to a 1x1 pixel surface (boundary)
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionTinyCanvas_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    cairo_surface_t *tiny_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    cairo_t *tiny_cr = cairo_create(tiny_surface);

    PopplerRectangle selection = { 0.0, 0.0, 612.0, 792.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 65535, 0, 0 };

    poppler_page_render_selection(page, tiny_cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(tiny_cr), CAIRO_STATUS_SUCCESS);

    cairo_destroy(tiny_cr);
    cairo_surface_destroy(tiny_surface);
}

// Test that calling render_selection multiple times does not cause issues
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionMultipleCalls_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 0.0, 0.0, 612.0, 792.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 65535, 0, 0 };

    for (int i = 0; i < 5; i++) {
        poppler_page_render_selection(page, cr, &selection, nullptr,
                                      POPPLER_SELECTION_GLYPH,
                                      &glyph_color, &background_color);
    }

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test with selection rectangle outside page bounds
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionOutOfBounds_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { -100.0, -100.0, -50.0, -50.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 65535, 0, 0 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test with very large selection rectangle
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionLargeRect_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { -10000.0, -10000.0, 10000.0, 10000.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 65535, 0, 0 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test with different selection styles sequentially
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionAllStylesSequential_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 0.0, 0.0, 612.0, 792.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 0, 0, 65535 };

    PopplerSelectionStyle styles[] = {
        POPPLER_SELECTION_GLYPH,
        POPPLER_SELECTION_WORD,
        POPPLER_SELECTION_LINE
    };

    for (auto style : styles) {
        poppler_page_render_selection(page, cr, &selection, nullptr,
                                      style,
                                      &glyph_color, &background_color);
        EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
    }
}

// Test with inverted selection rectangle (x1 > x2, y1 > y2)
TEST_F(PopplerPageRenderSelectionTest_2439, RenderSelectionInvertedRect_2439) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection = { 612.0, 792.0, 0.0, 0.0 };
    PopplerColor glyph_color = { 0, 0, 0 };
    PopplerColor background_color = { 0, 65535, 0 };

    poppler_page_render_selection(page, cr, &selection, nullptr,
                                  POPPLER_SELECTION_GLYPH,
                                  &glyph_color, &background_color);

    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}
