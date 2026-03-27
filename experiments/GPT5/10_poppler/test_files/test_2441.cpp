// poppler-page-get-selection-region-test.cc
//
// Unit tests for poppler_page_get_selection_region()
// TEST_ID: 2441
//
// These tests treat Poppler as a black box and validate only observable behavior
// through the public API and return values.

#include <gtest/gtest.h>

#include <glib.h>
#include <cairo.h>
#include <cairo-pdf.h>

#include "poppler.h"
#include "poppler-page.h"

namespace {

class PopplerPageGetSelectionRegionTest_2441 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a temporary PDF via Cairo (avoids hand-crafting PDF syntax).
    gchar *tmp_name = nullptr;
    GError *error = nullptr;

    // Make a unique temp filename.
    int fd = g_file_open_tmp("poppler_selection_region_XXXXXX.pdf", &tmp_name, &error);
    ASSERT_NE(fd, -1) << "g_file_open_tmp failed: " << (error ? error->message : "unknown");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }
    // We will write using Cairo; close the fd from g_file_open_tmp.
    close(fd);

    pdf_path_ = tmp_name;
    g_free(tmp_name);

    // Create a simple one-page PDF with a line of text.
    constexpr double kWidth = 612.0;   // 8.5in * 72
    constexpr double kHeight = 792.0;  // 11in * 72
    cairo_surface_t *surface = cairo_pdf_surface_create(pdf_path_, kWidth, kHeight);
    ASSERT_NE(surface, nullptr);

    cairo_t *cr = cairo_create(surface);
    ASSERT_NE(cr, nullptr);

    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 24.0);
    cairo_move_to(cr, 72.0, 200.0);
    cairo_show_text(cr, "Hello Poppler");
    cairo_show_page(cr);

    cairo_destroy(cr);
    cairo_surface_finish(surface);
    cairo_surface_destroy(surface);

    // Load the PDF with Poppler.
    gchar *uri = g_filename_to_uri(pdf_path_, /*hostname=*/nullptr, &error);
    ASSERT_NE(uri, nullptr) << "g_filename_to_uri failed: " << (error ? error->message : "unknown");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    doc_ = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    ASSERT_NE(doc_, nullptr) << "poppler_document_new_from_file failed: "
                             << (error ? error->message : "unknown");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
  }

  void TearDown() override {
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (pdf_path_) {
      g_remove(pdf_path_);
      g_free(pdf_path_);
      pdf_path_ = nullptr;
    }
  }

  static void FreeRegionList(GList *region) {
    for (GList *l = region; l != nullptr; l = l->next) {
      // poppler_rectangle_new_from_pdf_rectangle() allocates a PopplerRectangle*.
      // Free it as a plain allocation (Poppler GLib uses g_new/g_malloc patterns here).
      g_free(l->data);
    }
    g_list_free(region);
  }

  // Returns a selection rectangle that covers the entire page.
  PopplerRectangle WholePageSelection() const {
    PopplerRectangle sel{};
    gdouble width = 0.0, height = 0.0;
    poppler_page_get_size(page_, &width, &height);

    // PopplerRectangle uses doubles in the public API.
    sel.x1 = 0.0;
    sel.y1 = 0.0;
    sel.x2 = width;
    sel.y2 = height;
    return sel;
  }

  // Returns an "empty" selection rectangle (zero area).
  static PopplerRectangle EmptySelectionAtOrigin() {
    PopplerRectangle sel{};
    sel.x1 = 0.0;
    sel.y1 = 0.0;
    sel.x2 = 0.0;
    sel.y2 = 0.0;
    return sel;
  }

  // Compares two returned regions in a minimal, observable way:
  // same length and same rectangle coordinates in the same order.
  static void ExpectSameRegion(GList *a, GList *b) {
    ASSERT_EQ(g_list_length(a), g_list_length(b));
    for (GList *la = a, *lb = b; la && lb; la = la->next, lb = lb->next) {
      const auto *ra = static_cast<const PopplerRectangle *>(la->data);
      const auto *rb = static_cast<const PopplerRectangle *>(lb->data);
      ASSERT_NE(ra, nullptr);
      ASSERT_NE(rb, nullptr);
      EXPECT_DOUBLE_EQ(ra->x1, rb->x1);
      EXPECT_DOUBLE_EQ(ra->y1, rb->y1);
      EXPECT_DOUBLE_EQ(ra->x2, rb->x2);
      EXPECT_DOUBLE_EQ(ra->y2, rb->y2);
    }
  }

  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
  gchar *pdf_path_ = nullptr;
};

TEST_F(PopplerPageGetSelectionRegionTest_2441, ReturnsNonEmptyRegionForWholePageSelection_2441) {
  PopplerRectangle selection = WholePageSelection();

  GList *region =
      poppler_page_get_selection_region(page_, /*scale=*/1.0, POPPLER_SELECTION_GLYPH, &selection);

  // Observable behavior: should return a list (possibly empty if something went wrong),
  // but for a page containing text and a whole-page selection we expect at least one rect.
  ASSERT_NE(region, nullptr);
  EXPECT_GT(g_list_length(region), 0u);

  // Rectangles should be well-formed (x1<=x2, y1<=y2).
  for (GList *l = region; l != nullptr; l = l->next) {
    const auto *r = static_cast<const PopplerRectangle *>(l->data);
    ASSERT_NE(r, nullptr);
    EXPECT_LE(r->x1, r->x2);
    EXPECT_LE(r->y1, r->y2);
  }

  FreeRegionList(region);
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, DifferentSelectionStylesReturnLists_2441) {
  PopplerRectangle selection = WholePageSelection();

  GList *glyph =
      poppler_page_get_selection_region(page_, /*scale=*/1.0, POPPLER_SELECTION_GLYPH, &selection);
  GList *word =
      poppler_page_get_selection_region(page_, /*scale=*/1.0, POPPLER_SELECTION_WORD, &selection);
  GList *line =
      poppler_page_get_selection_region(page_, /*scale=*/1.0, POPPLER_SELECTION_LINE, &selection);

  ASSERT_NE(glyph, nullptr);
  ASSERT_NE(word, nullptr);
  ASSERT_NE(line, nullptr);

  // Do not assume internal segmentation rules; only require "it returns something" for this PDF.
  EXPECT_GT(g_list_length(glyph), 0u);
  EXPECT_GT(g_list_length(word), 0u);
  EXPECT_GT(g_list_length(line), 0u);

  FreeRegionList(glyph);
  FreeRegionList(word);
  FreeRegionList(line);
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, EmptySelectionYieldsEmptyOrNullRegion_2441) {
  PopplerRectangle selection = EmptySelectionAtOrigin();

  GList *region =
      poppler_page_get_selection_region(page_, /*scale=*/1.0, POPPLER_SELECTION_GLYPH, &selection);

  // Accept either nullptr or an empty list (both are observable and reasonable for an empty selection).
  if (region) {
    EXPECT_EQ(g_list_length(region), 0u);
    FreeRegionList(region);
  } else {
    SUCCEED();
  }
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, InvalidStyleBehavesLikeDefaultGlyph_2441) {
  PopplerRectangle selection = WholePageSelection();

  GList *glyph =
      poppler_page_get_selection_region(page_, /*scale=*/1.0, POPPLER_SELECTION_GLYPH, &selection);

  // Pass an out-of-range enum value (observable "error-ish" input).
  const auto invalid_style = static_cast<PopplerSelectionStyle>(999);
  GList *invalid =
      poppler_page_get_selection_region(page_, /*scale=*/1.0, invalid_style, &selection);

  ASSERT_NE(glyph, nullptr);
  ASSERT_NE(invalid, nullptr);

  // The implementation has no default case; it initializes to glyph.
  // Observable expectation: invalid style should match glyph behavior.
  ExpectSameRegion(glyph, invalid);

  FreeRegionList(glyph);
  FreeRegionList(invalid);
}

TEST_F(PopplerPageGetSelectionRegionTest_2441, ScaleBoundaryValuesDoNotCrash_2441) {
  PopplerRectangle selection = WholePageSelection();

  // scale = 0.0 (boundary)
  GList *zero =
      poppler_page_get_selection_region(page_, /*scale=*/0.0, POPPLER_SELECTION_GLYPH, &selection);
  // scale negative (error-ish boundary)
  GList *neg =
      poppler_page_get_selection_region(page_, /*scale=*/-1.0, POPPLER_SELECTION_GLYPH, &selection);
  // large scale
  GList *large =
      poppler_page_get_selection_region(page_, /*scale=*/1000.0, POPPLER_SELECTION_GLYPH, &selection);

  // We only assert "call succeeds" (no crash) and returned list is well-formed if present.
  auto check_list = [](GList *region) {
    if (!region) {
      return;
    }
    for (GList *l = region; l != nullptr; l = l->next) {
      const auto *r = static_cast<const PopplerRectangle *>(l->data);
      ASSERT_NE(r, nullptr);
      EXPECT_LE(r->x1, r->x2);
      EXPECT_LE(r->y1, r->y2);
    }
  };

  check_list(zero);
  check_list(neg);
  check_list(large);

  if (zero) FreeRegionList(zero);
  if (neg) FreeRegionList(neg);
  if (large) FreeRegionList(large);
}

}  // namespace