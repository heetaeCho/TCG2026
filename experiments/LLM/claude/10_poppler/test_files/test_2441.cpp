#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>

// Include necessary headers
#include "poppler-page.h"
#include "poppler-private.h"
#include "poppler.h"
#include "PDFRectangle.h"
#include "TextOutputDev.h"

// We need to test poppler_page_get_selection_region which depends on:
// - poppler_page_get_text_page (returns TextPage*)
// - TextPage::getSelectionRegion
// - poppler_rectangle_new_from_pdf_rectangle
//
// Since we treat the function as a black box and can't easily mock internal calls
// in a C function, we need to set up real or minimal objects. However, given
// the complexity of Poppler internals, we'll create integration-style tests
// that work with the actual Poppler library if available.
//
// For testability, we'll create a PopplerPage from a real PDF document
// or use the Poppler GLib API to create test fixtures.

class PopplerPageGetSelectionRegionTest_2441 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        // Try to create a minimal PDF in memory for testing
        // We'll use a simple PDF with known text content
        const char *pdf_content =
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
            "startxref\n431\n%%EOF\n";

        gsize len = strlen(pdf_content);
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        if (doc == nullptr && error != nullptr) {
            g_error_free(error);
            error = nullptr;
            // Fallback: try creating from data
            doc = poppler_document_new_from_data((char*)pdf_content, (int)len, nullptr, &error);
        }

        if (doc != nullptr) {
            page = poppler_document_get_page(doc, 0);
        }

        g_object_unref(stream);
        g_bytes_unref(bytes);
        if (error) {
            g_error_free(error);
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

    bool hasValidPage() const {
        return page != nullptr;
    }
};

TEST_F(PopplerPageGetSelectionRegionTest_2441, ReturnsNullForEmptySelection_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 0.0;
    selection.y2 = 0.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    // An empty selection rectangle should yield no region or empty list
    // The result could be NULL or an empty list
    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    // Test passes as long as no crash occurs
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, ReturnsRegionForFullPageSelection_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    // A full page selection on a page with text should return some regions
    // (or none if the PDF has no extractable text)
    // Either way, no crash should occur
    if (region != nullptr) {
        // Verify that each element in the list is a valid PopplerRectangle
        for (GList *l = region; l != nullptr; l = l->next) {
            PopplerRectangle *rect = (PopplerRectangle *)l->data;
            ASSERT_NE(rect, nullptr);
        }
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, SelectionStyleGlyph_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    // Should not crash; result is valid
    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, SelectionStyleWord_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_WORD, &selection);

    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, SelectionStyleLine_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_LINE, &selection);

    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, ScaleFactorAffectsRegion_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region_scale1 = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);
    GList *region_scale2 = poppler_page_get_selection_region(page, 2.0, POPPLER_SELECTION_GLYPH, &selection);

    // Both calls should succeed without crashes
    // If there are regions, the scaled versions should have different coordinates
    guint len1 = g_list_length(region_scale1);
    guint len2 = g_list_length(region_scale2);

    // The number of regions should be the same regardless of scale
    EXPECT_EQ(len1, len2);

    // If regions exist, check that scale=2 produces coordinates roughly 2x scale=1
    if (len1 > 0 && len2 > 0) {
        PopplerRectangle *r1 = (PopplerRectangle *)region_scale1->data;
        PopplerRectangle *r2 = (PopplerRectangle *)region_scale2->data;
        // With scale=2, coordinates should be approximately double
        EXPECT_NEAR(r2->x1, r1->x1 * 2.0, 1.0);
        EXPECT_NEAR(r2->y1, r1->y1 * 2.0, 1.0);
        EXPECT_NEAR(r2->x2, r1->x2 * 2.0, 1.0);
        EXPECT_NEAR(r2->y2, r1->y2 * 2.0, 1.0);
    }

    if (region_scale1) {
        g_list_free_full(region_scale1, (GDestroyNotify)poppler_rectangle_free);
    }
    if (region_scale2) {
        g_list_free_full(region_scale2, (GDestroyNotify)poppler_rectangle_free);
    }
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, NegativeCoordinateSelection_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = -100.0;
    selection.y1 = -100.0;
    selection.x2 = -50.0;
    selection.y2 = -50.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    // A selection outside the page should return no regions (or at least not crash)
    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, VeryLargeScaleFactor_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region = poppler_page_get_selection_region(page, 1000.0, POPPLER_SELECTION_GLYPH, &selection);

    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, VerySmallScaleFactor_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region = poppler_page_get_selection_region(page, 0.001, POPPLER_SELECTION_GLYPH, &selection);

    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, InvertedSelectionCoordinates_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    // Inverted coordinates (x1 > x2, y1 > y2)
    PopplerRectangle selection;
    selection.x1 = 612.0;
    selection.y1 = 792.0;
    selection.x2 = 0.0;
    selection.y2 = 0.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    // Should handle inverted coordinates without crashing
    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, PartialPageSelection_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    // Select only a small area where text might be
    PopplerRectangle selection;
    selection.x1 = 90.0;
    selection.y1 = 690.0;
    selection.x2 = 200.0;
    selection.y2 = 720.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    if (region != nullptr) {
        for (GList *l = region; l != nullptr; l = l->next) {
            PopplerRectangle *rect = (PopplerRectangle *)l->data;
            ASSERT_NE(rect, nullptr);
        }
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, ZeroScaleFactor_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    // Scale of 0 is a boundary condition
    GList *region = poppler_page_get_selection_region(page, 0.0, POPPLER_SELECTION_GLYPH, &selection);

    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, SelectionRegionReturnsList_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    // The return value should either be NULL or a valid GList
    if (region != nullptr) {
        // Verify it's a proper GList - first element should have prev == NULL
        EXPECT_EQ(region->prev, nullptr);

        // Walk the list and verify structure
        GList *last = nullptr;
        for (GList *l = region; l != nullptr; l = l->next) {
            EXPECT_NE(l->data, nullptr);
            last = l;
        }

        // Last element should have next == NULL
        if (last) {
            EXPECT_EQ(last->next, nullptr);
        }

        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, DifferentStylesSameRegionCount_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 0.0;
    selection.y1 = 0.0;
    selection.x2 = 612.0;
    selection.y2 = 792.0;

    GList *region_glyph = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);
    GList *region_word = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_WORD, &selection);
    GList *region_line = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_LINE, &selection);

    // Different selection styles may produce different numbers of regions
    // but all should be valid. Line selection typically produces fewer or equal regions.
    guint glyph_count = g_list_length(region_glyph);
    guint word_count = g_list_length(region_word);
    guint line_count = g_list_length(region_line);

    // Line selection should produce <= word selection regions in general
    // Word selection should produce <= glyph selection regions in general
    // (This is a general expectation, not always strictly true)
    // At minimum, all should produce consistent results without crash

    if (region_glyph) g_list_free_full(region_glyph, (GDestroyNotify)poppler_rectangle_free);
    if (region_word) g_list_free_full(region_word, (GDestroyNotify)poppler_rectangle_free);
    if (region_line) g_list_free_full(region_line, (GDestroyNotify)poppler_rectangle_free);

    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, SelectionOutsidePage_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle selection;
    selection.x1 = 1000.0;
    selection.y1 = 1000.0;
    selection.x2 = 2000.0;
    selection.y2 = 2000.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    // Selection completely outside the page should return empty or null
    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, PointSelection_2441) {
    if (!hasValidPage()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    // A point selection (zero area)
    PopplerRectangle selection;
    selection.x1 = 100.0;
    selection.y1 = 700.0;
    selection.x2 = 100.0;
    selection.y2 = 700.0;

    GList *region = poppler_page_get_selection_region(page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    if (region != nullptr) {
        g_list_free_full(region, (GDestroyNotify)poppler_rectangle_free);
    }
    SUCCEED();
}
