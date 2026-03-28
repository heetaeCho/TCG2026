#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>
#include <poppler.h>

// Helper to create a test PDF document in memory
static PopplerDocument *create_test_document()
{
    // Create a minimal PDF in memory
    const char *pdf_content =
        "%PDF-1.4\n"
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

    gsize len = strlen(pdf_content);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data((char *)pdf_content, (int)len, nullptr, &error);
    
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    
    return doc;
}

// Alternative: create document from a GBytes object
static PopplerDocument *create_test_document_from_bytes()
{
    const char *pdf_content =
        "%PDF-1.4\n"
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

    gsize len = strlen(pdf_content);
    GError *error = nullptr;
    
    // Try using poppler_document_new_from_bytes if available, otherwise fallback
    GBytes *bytes = g_bytes_new(pdf_content, len);
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (error) {
        g_error_free(error);
        return nullptr;
    }
    
    return doc;
}

class PopplerPageRenderForPrintingTest_2436 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    cairo_surface_t *surface = nullptr;
    cairo_t *cr = nullptr;

    void SetUp() override
    {
        doc = create_test_document_from_bytes();
        if (!doc) {
            doc = create_test_document();
        }
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
        // Create an image surface for rendering
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 612, 792);
        cr = cairo_create(surface);
    }

    void TearDown() override
    {
        if (cr) {
            cairo_destroy(cr);
        }
        if (surface) {
            cairo_surface_destroy(surface);
        }
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that poppler_page_render_for_printing does not crash with valid inputs
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingValidInputs_2436)
{
    if (!page || !cr) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    // Should not crash or throw
    poppler_page_render_for_printing(page, cr);
    
    cairo_status_t status = cairo_status(cr);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
}

// Test that cairo context remains valid after rendering for printing
TEST_F(PopplerPageRenderForPrintingTest_2436, CairoContextValidAfterRender_2436)
{
    if (!page || !cr) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    poppler_page_render_for_printing(page, cr);
    
    // Cairo context should still be usable
    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, 100, 100);
    cairo_status_t status = cairo_status(cr);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
}

// Test rendering for printing on a small surface
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingSmallSurface_2436)
{
    if (!page) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    // Create a very small surface
    cairo_surface_t *small_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    cairo_t *small_cr = cairo_create(small_surface);
    
    // Should not crash even with a tiny surface
    poppler_page_render_for_printing(page, small_cr);
    
    cairo_status_t status = cairo_status(small_cr);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
    
    cairo_destroy(small_cr);
    cairo_surface_destroy(small_surface);
}

// Test that POPPLER_RENDER_ANNOTS_PRINT_ALL flag value is correct
TEST_F(PopplerPageRenderForPrintingTest_2436, PrintAllFlagValue_2436)
{
    // POPPLER_RENDER_ANNOTS_PRINT_ALL should match the expected combined value
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_PRINT_ALL, -32800771);
}

// Test rendering for printing with a scaled cairo context
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingWithScaling_2436)
{
    if (!page || !cr) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    // Apply scaling to simulate different DPI
    cairo_scale(cr, 2.0, 2.0);
    
    poppler_page_render_for_printing(page, cr);
    
    cairo_status_t status = cairo_status(cr);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
}

// Test rendering for printing with a translated cairo context
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingWithTranslation_2436)
{
    if (!page || !cr) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    cairo_translate(cr, 100.0, 100.0);
    
    poppler_page_render_for_printing(page, cr);
    
    cairo_status_t status = cairo_status(cr);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
}

// Test rendering for printing with a rotated cairo context
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingWithRotation_2436)
{
    if (!page || !cr) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    cairo_rotate(cr, G_PI / 4.0);
    
    poppler_page_render_for_printing(page, cr);
    
    cairo_status_t status = cairo_status(cr);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
}

// Test rendering for printing on a PDF surface (actual printing scenario)
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingToPDFSurface_2436)
{
    if (!page) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    // Create a PDF surface (simulates printing to PDF)
    cairo_surface_t *pdf_surface = cairo_pdf_surface_create("/dev/null", 612, 792);
    cairo_t *pdf_cr = cairo_create(pdf_surface);
    
    if (cairo_status(pdf_cr) == CAIRO_STATUS_SUCCESS) {
        poppler_page_render_for_printing(page, pdf_cr);
        
        cairo_status_t status = cairo_status(pdf_cr);
        EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
    }
    
    cairo_destroy(pdf_cr);
    cairo_surface_destroy(pdf_surface);
}

// Test that rendering for printing can be called multiple times on same page
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingMultipleTimes_2436)
{
    if (!page || !cr) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    poppler_page_render_for_printing(page, cr);
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
    
    poppler_page_render_for_printing(page, cr);
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
    
    poppler_page_render_for_printing(page, cr);
    EXPECT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);
}

// Test the enum flag relationships
TEST_F(PopplerPageRenderForPrintingTest_2436, AnnotsFlagRelationships_2436)
{
    // PRINT_ALL and PRINT_MARKUP should be equal based on the enum definition
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_PRINT_ALL, POPPLER_RENDER_ANNOTS_PRINT_MARKUP);
    
    // PRINT_DOCUMENT should be equal to WIDGET
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT, POPPLER_RENDER_ANNOTS_WIDGET);
    
    // ALL should encompass all individual flags
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_ALL, 67108863);
    
    // NONE should be zero
    EXPECT_EQ(POPPLER_RENDER_ANNOTS_NONE, 0);
}

// Test rendering for printing preserves cairo save/restore state
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingPreservesCairoState_2436)
{
    if (!page || !cr) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    cairo_save(cr);
    cairo_scale(cr, 0.5, 0.5);
    
    poppler_page_render_for_printing(page, cr);
    
    cairo_restore(cr);
    
    cairo_status_t status = cairo_status(cr);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
}

// Test rendering for printing on a recording surface
TEST_F(PopplerPageRenderForPrintingTest_2436, RenderForPrintingToRecordingSurface_2436)
{
    if (!page) {
        GTEST_SKIP() << "Could not create test document/page";
    }
    
    cairo_surface_t *rec_surface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, nullptr);
    cairo_t *rec_cr = cairo_create(rec_surface);
    
    poppler_page_render_for_printing(page, rec_cr);
    
    cairo_status_t status = cairo_status(rec_cr);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
    
    cairo_destroy(rec_cr);
    cairo_surface_destroy(rec_surface);
}
