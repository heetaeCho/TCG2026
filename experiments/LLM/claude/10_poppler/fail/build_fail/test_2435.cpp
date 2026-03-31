#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>

// Include the necessary poppler headers
#include "poppler.h"
#include "poppler-page.h"
#include "poppler-private.h"

// We need to intercept calls to poppler_page_render_full to verify the flags
// Since we can't mock static/free functions directly, we'll use a global tracking mechanism

static bool g_render_full_called = false;
static bool g_render_full_printing = false;
static int g_render_full_flags = 0;
static PopplerPage *g_render_full_page = nullptr;
static cairo_t *g_render_full_cairo = nullptr;

// Mock/stub for poppler_page_render_full
extern "C" {
void poppler_page_render_full(PopplerPage *page, cairo_t *cairo, gboolean printing, PopplerRenderAnnotsFlags flags)
{
    g_render_full_called = true;
    g_render_full_page = page;
    g_render_full_cairo = cairo;
    g_render_full_printing = printing;
    g_render_full_flags = (int)flags;
}
}

class PopplerPageRenderForPrintingTest_2435 : public ::testing::Test {
protected:
    void SetUp() override
    {
        g_render_full_called = false;
        g_render_full_printing = false;
        g_render_full_flags = 0;
        g_render_full_page = nullptr;
        g_render_full_cairo = nullptr;

        // Create a cairo surface and context for testing
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
        cr = cairo_create(surface);
    }

    void TearDown() override
    {
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }

    cairo_surface_t *surface;
    cairo_t *cr;
};

// Test: No options set - should only have POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT flag
TEST_F(PopplerPageRenderForPrintingTest_2435, NoOptions_OnlyDocumentFlag_2435)
{
    PopplerPage *page = nullptr; // We'll pass nullptr since render_full is stubbed

    PopplerPrintFlags options = (PopplerPrintFlags)0;
    poppler_page_render_for_printing_with_options(page, cr, options);

    EXPECT_TRUE(g_render_full_called);
    EXPECT_TRUE(g_render_full_printing);
    EXPECT_EQ(g_render_full_flags, (int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT);
    EXPECT_EQ(g_render_full_page, page);
    EXPECT_EQ(g_render_full_cairo, cr);
}

// Test: POPPLER_PRINT_STAMP_ANNOTS_ONLY option adds PRINT_STAMP flag
TEST_F(PopplerPageRenderForPrintingTest_2435, StampAnnotsOnly_AddsStampFlag_2435)
{
    PopplerPage *page = nullptr;

    PopplerPrintFlags options = POPPLER_PRINT_STAMP_ANNOTS_ONLY;
    poppler_page_render_for_printing_with_options(page, cr, options);

    EXPECT_TRUE(g_render_full_called);
    EXPECT_TRUE(g_render_full_printing);

    int expected_flags = (int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT | (int)POPPLER_RENDER_ANNOTS_PRINT_STAMP;
    EXPECT_EQ(g_render_full_flags, expected_flags);
}

// Test: POPPLER_PRINT_MARKUP_ANNOTS option adds PRINT_MARKUP flag
TEST_F(PopplerPageRenderForPrintingTest_2435, MarkupAnnots_AddsMarkupFlag_2435)
{
    PopplerPage *page = nullptr;

    PopplerPrintFlags options = POPPLER_PRINT_MARKUP_ANNOTS;
    poppler_page_render_for_printing_with_options(page, cr, options);

    EXPECT_TRUE(g_render_full_called);
    EXPECT_TRUE(g_render_full_printing);

    int expected_flags = (int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT | (int)POPPLER_RENDER_ANNOTS_PRINT_MARKUP;
    EXPECT_EQ(g_render_full_flags, expected_flags);
}

// Test: Both STAMP and MARKUP options set
TEST_F(PopplerPageRenderForPrintingTest_2435, StampAndMarkupAnnots_AddsBothFlags_2435)
{
    PopplerPage *page = nullptr;

    PopplerPrintFlags options = (PopplerPrintFlags)(POPPLER_PRINT_STAMP_ANNOTS_ONLY | POPPLER_PRINT_MARKUP_ANNOTS);
    poppler_page_render_for_printing_with_options(page, cr, options);

    EXPECT_TRUE(g_render_full_called);
    EXPECT_TRUE(g_render_full_printing);

    int expected_flags = (int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT | (int)POPPLER_RENDER_ANNOTS_PRINT_STAMP | (int)POPPLER_RENDER_ANNOTS_PRINT_MARKUP;
    EXPECT_EQ(g_render_full_flags, expected_flags);
}

// Test: Verify that printing parameter is always true
TEST_F(PopplerPageRenderForPrintingTest_2435, PrintingParameterAlwaysTrue_2435)
{
    PopplerPage *page = nullptr;

    poppler_page_render_for_printing_with_options(page, cr, (PopplerPrintFlags)0);

    EXPECT_TRUE(g_render_full_printing);
}

// Test: Verify page and cairo are passed through correctly
TEST_F(PopplerPageRenderForPrintingTest_2435, PageAndCairoPassedThrough_2435)
{
    // Use a non-null fake page pointer (cast from an arbitrary address)
    PopplerPage *fake_page = reinterpret_cast<PopplerPage *>(0xDEADBEEF);

    poppler_page_render_for_printing_with_options(fake_page, cr, (PopplerPrintFlags)0);

    EXPECT_EQ(g_render_full_page, fake_page);
    EXPECT_EQ(g_render_full_cairo, cr);
}

// Test: POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT is always present in base flags
TEST_F(PopplerPageRenderForPrintingTest_2435, DocumentFlagAlwaysPresent_2435)
{
    PopplerPage *page = nullptr;

    // Test with no options
    poppler_page_render_for_printing_with_options(page, cr, (PopplerPrintFlags)0);
    EXPECT_NE(g_render_full_flags & (int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT, 0);

    // Test with stamp option
    g_render_full_flags = 0;
    poppler_page_render_for_printing_with_options(page, cr, POPPLER_PRINT_STAMP_ANNOTS_ONLY);
    EXPECT_NE(g_render_full_flags & (int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT, 0);

    // Test with markup option
    g_render_full_flags = 0;
    poppler_page_render_for_printing_with_options(page, cr, POPPLER_PRINT_MARKUP_ANNOTS);
    EXPECT_NE(g_render_full_flags & (int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT, 0);
}

// Test: Without STAMP option, PRINT_STAMP flag should not be set
TEST_F(PopplerPageRenderForPrintingTest_2435, NoStampOptionMeansNoStampFlag_2435)
{
    PopplerPage *page = nullptr;

    poppler_page_render_for_printing_with_options(page, cr, (PopplerPrintFlags)0);

    // Check that PRINT_STAMP bits beyond PRINT_DOCUMENT are not set
    // POPPLER_RENDER_ANNOTS_PRINT_STAMP = 528384
    // POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT = 524288
    // The additional bits from STAMP that are not in DOCUMENT
    int stamp_only_bits = (int)POPPLER_RENDER_ANNOTS_PRINT_STAMP & ~(int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT;
    EXPECT_EQ(g_render_full_flags & stamp_only_bits, 0);
}

// Test: Without MARKUP option, PRINT_MARKUP flag should not be set
TEST_F(PopplerPageRenderForPrintingTest_2435, NoMarkupOptionMeansNoMarkupFlag_2435)
{
    PopplerPage *page = nullptr;

    poppler_page_render_for_printing_with_options(page, cr, (PopplerPrintFlags)0);

    int markup_only_bits = (int)POPPLER_RENDER_ANNOTS_PRINT_MARKUP & ~(int)POPPLER_RENDER_ANNOTS_PRINT_DOCUMENT;
    EXPECT_EQ(g_render_full_flags & markup_only_bits, 0);
}
