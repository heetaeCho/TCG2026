#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>

// Include necessary headers
#include "poppler-page.h"
#include "poppler-private.h"
#include "poppler.h"
#include "PDFRectangle.h"
#include "TextOutputDev.h"

// We need to mock TextPage::getSelectionRegion since it's a dependency.
// However, since we're treating the function as a black box and we need
// to set up real PopplerPage objects, we'll use integration-style tests
// with actual poppler document loading where possible.

// For testing purposes, we create a helper to load a simple PDF page.
// If direct document creation isn't feasible, we mock the necessary components.

#include <poppler-document.h>
#include <cstring>
#include <cmath>

class PopplerPageGetSelectedRegionTest_2442 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Try to create a minimal PDF document in memory
        // We'll use a simple PDF content
        const char *pdf_content =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
            "/Contents 4 0 R/Resources<</Font<</F1 5 0 R>>>>>>endobj\n"
            "4 0 obj<</Length 44>>\nstream\n"
            "BT /F1 12 Tf 100 700 Td (Hello World) Tj ET\n"
            "endstream\nendobj\n"
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

        gsize len = strlen(pdf_content);
        GError *error = nullptr;

        // Create a GBytes from the PDF content
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

        if (doc == nullptr && error != nullptr) {
            g_error_free(error);
            error = nullptr;
            // Fallback: try from data
            doc = poppler_document_new_from_data((char*)pdf_content, (int)len, nullptr, &error);
            if (error) {
                g_error_free(error);
            }
        }

        g_object_unref(stream);
        g_bytes_unref(bytes);

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
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

// Test that selecting an empty region returns a valid (possibly empty) cairo region
TEST_F(PopplerPageGetSelectedRegionTest_2442, EmptySelectionReturnsValidRegion_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 0.0;
    selection.y2 = 0.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    // An empty selection should result in an empty region
    EXPECT_TRUE(cairo_region_is_empty(region));

    cairo_region_destroy(region);
}

// Test with scale factor 1.0 and glyph selection style
TEST_F(PopplerPageGetSelectedRegionTest_2442, GlyphSelectionWithScale1_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    // The region should be valid (not in error state)
    EXPECT_NE(cairo_region_status(region), CAIRO_STATUS_NO_MEMORY);

    cairo_region_destroy(region);
}

// Test with scale factor 2.0
TEST_F(PopplerPageGetSelectedRegionTest_2442, ScaleFactor2_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region1 = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);
    cairo_region_t *region2 = poppler_page_get_selected_region(
        page, 2.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region1, nullptr);
    ASSERT_NE(region2, nullptr);

    // If there are selected rectangles, the scaled version should have larger extents
    if (!cairo_region_is_empty(region1) && !cairo_region_is_empty(region2)) {
        cairo_rectangle_int_t extents1, extents2;
        cairo_region_get_extents(region1, &extents1);
        cairo_region_get_extents(region2, &extents2);

        // With scale 2.0, coordinates should be approximately double
        EXPECT_NEAR(extents2.x, extents1.x * 2, 2);
        EXPECT_NEAR(extents2.y, extents1.y * 2, 2);
        EXPECT_NEAR(extents2.width, extents1.width * 2, 2);
        EXPECT_NEAR(extents2.height, extents1.height * 2, 2);
    }

    cairo_region_destroy(region1);
    cairo_region_destroy(region2);
}

// Test word selection style
TEST_F(PopplerPageGetSelectedRegionTest_2442, WordSelectionStyle_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_WORD, &selection);

    ASSERT_NE(region, nullptr);
    EXPECT_NE(cairo_region_status(region), CAIRO_STATUS_NO_MEMORY);

    cairo_region_destroy(region);
}

// Test line selection style
TEST_F(PopplerPageGetSelectedRegionTest_2442, LineSelectionStyle_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_LINE, &selection);

    ASSERT_NE(region, nullptr);
    EXPECT_NE(cairo_region_status(region), CAIRO_STATUS_NO_MEMORY);

    cairo_region_destroy(region);
}

// Test with a very small scale factor
TEST_F(PopplerPageGetSelectedRegionTest_2442, VerySmallScaleFactor_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 0.01, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    cairo_region_destroy(region);
}

// Test with a large scale factor
TEST_F(PopplerPageGetSelectedRegionTest_2442, LargeScaleFactor_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 100.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    cairo_region_destroy(region);
}

// Test partial page selection
TEST_F(PopplerPageGetSelectedRegionTest_2442, PartialPageSelection_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 90.0;
    selection.y1 = 690.0;
    selection.x2 = 200.0;
    selection.y2 = 720.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    // The region extents should be within the selection bounds (approximately)
    if (!cairo_region_is_empty(region)) {
        cairo_rectangle_int_t extents;
        cairo_region_get_extents(region, &extents);

        EXPECT_GE(extents.x, (int)(selection.x1 - 1));
        EXPECT_GE(extents.y, (int)(selection.y1 - 1));
        EXPECT_LE(extents.x + extents.width, (int)(selection.x2 + 2));
        EXPECT_LE(extents.y + extents.height, (int)(selection.y2 + 2));
    }

    cairo_region_destroy(region);
}

// Test that different selection styles may produce different regions
TEST_F(PopplerPageGetSelectedRegionTest_2442, DifferentStylesMayDiffer_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region_glyph = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);
    cairo_region_t *region_word = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_WORD, &selection);
    cairo_region_t *region_line = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_LINE, &selection);

    ASSERT_NE(region_glyph, nullptr);
    ASSERT_NE(region_word, nullptr);
    ASSERT_NE(region_line, nullptr);

    // All should be valid regions
    EXPECT_EQ(cairo_region_status(region_glyph), CAIRO_STATUS_SUCCESS);
    EXPECT_EQ(cairo_region_status(region_word), CAIRO_STATUS_SUCCESS);
    EXPECT_EQ(cairo_region_status(region_line), CAIRO_STATUS_SUCCESS);

    cairo_region_destroy(region_glyph);
    cairo_region_destroy(region_word);
    cairo_region_destroy(region_line);
}

// Test selection outside page bounds returns empty region
TEST_F(PopplerPageGetSelectedRegionTest_2442, SelectionOutsidePageBounds_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 1000.0;
    selection.y1 = 1000.0;
    selection.x2 = 2000.0;
    selection.y2 = 2000.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    // Selection outside the page should yield an empty region (no text there)
    EXPECT_TRUE(cairo_region_is_empty(region));

    cairo_region_destroy(region);
}

// Test with zero scale factor
TEST_F(PopplerPageGetSelectedRegionTest_2442, ZeroScaleFactor_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 0.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    // With zero scale, all rectangles would collapse to zero-size
    cairo_region_destroy(region);
}

// Test with negative coordinates in selection rectangle
TEST_F(PopplerPageGetSelectedRegionTest_2442, NegativeSelectionCoordinates_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = -100.0;
    selection.y1 = -100.0;
    selection.x2 = 100.0;
    selection.y2 = 100.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    cairo_region_destroy(region);
}

// Test multiple calls return independent regions
TEST_F(PopplerPageGetSelectedRegionTest_2442, MultipleCallsReturnIndependentRegions_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region1 = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);
    cairo_region_t *region2 = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region1, nullptr);
    ASSERT_NE(region2, nullptr);
    // They should be different pointers (independent allocations)
    EXPECT_NE(region1, region2);

    // But they should have the same content
    EXPECT_TRUE(cairo_region_equal(region1, region2));

    cairo_region_destroy(region1);
    cairo_region_destroy(region2);
}

// Test with fractional scale
TEST_F(PopplerPageGetSelectedRegionTest_2442, FractionalScale_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.5, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    EXPECT_EQ(cairo_region_status(region), CAIRO_STATUS_SUCCESS);

    cairo_region_destroy(region);
}

// Test that returned region number of rectangles is non-negative
TEST_F(PopplerPageGetSelectedRegionTest_2442, RegionRectCountNonNegative_2442) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    cairo_region_t *region = poppler_page_get_selected_region(
        page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(region, nullptr);
    int num_rects = cairo_region_num_rectangles(region);
    EXPECT_GE(num_rects, 0);

    cairo_region_destroy(region);
}
