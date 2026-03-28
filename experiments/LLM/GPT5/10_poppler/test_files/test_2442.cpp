// poppler-page-get-selected-region-test_2442.cc
#include <gtest/gtest.h>

#include <poppler.h>          // poppler-glib
#include <glib.h>
#include <cairo.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

namespace {

static std::string MakeFileUri(const char *path) {
  // poppler_document_new_from_file expects a URI (e.g., file:///tmp/x.pdf).
  gchar *uri = g_filename_to_uri(path, /*hostname=*/nullptr, /*error=*/nullptr);
  std::string out = uri ? uri : "";
  if (uri)
    g_free(uri);
  return out;
}

static bool WriteMinimalPdfToPath(const char *path) {
  // A tiny, valid PDF with one page and the word "Hello" drawn.
  //
  // Coordinates:
  //   MediaBox: 0..200 x 0..200
  //   Text: "Hello" at (50, 100), font size 24, Helvetica.
  //
  // NOTE: Keep syntax simple and compute a correct xref table.
  const char *header = "%PDF-1.4\n";

  const std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
  const std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
  const std::string obj3 =
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << /Font << /F1 5 0 R >> >>\n"
      ">>\n"
      "endobj\n";

  const std::string stream_payload =
      "BT\n"
      "/F1 24 Tf\n"
      "50 100 Td\n"
      "(Hello) Tj\n"
      "ET\n";

  char obj4_prefix[256];
  std::snprintf(obj4_prefix, sizeof(obj4_prefix),
                "4 0 obj\n<< /Length %zu >>\nstream\n", stream_payload.size());
  const std::string obj4 = std::string(obj4_prefix) + stream_payload + "endstream\nendobj\n";

  const std::string obj5 =
      "5 0 obj\n"
      "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
      "endobj\n";

  // We'll assemble, tracking byte offsets for xref (objects 0..5).
  std::string pdf;
  pdf.reserve(4096);
  pdf += header;

  std::vector<long> offsets(6, 0);  // offsets[obj_num]
  auto append_obj = [&](int obj_num, const std::string &obj) {
    offsets[obj_num] = static_cast<long>(pdf.size());
    pdf += obj;
  };

  append_obj(1, obj1);
  append_obj(2, obj2);
  append_obj(3, obj3);
  append_obj(4, obj4);
  append_obj(5, obj5);

  const long xref_offset = static_cast<long>(pdf.size());

  // xref table for 0..5
  pdf += "xref\n";
  pdf += "0 6\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    char line[32];
    std::snprintf(line, sizeof(line), "%010ld 00000 n \n", offsets[i]);
    pdf += line;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  {
    char line[64];
    std::snprintf(line, sizeof(line), "%ld\n", xref_offset);
    pdf += line;
  }
  pdf += "%%EOF\n";

  FILE *fp = std::fopen(path, "wb");
  if (!fp)
    return false;
  const size_t written = std::fwrite(pdf.data(), 1, pdf.size(), fp);
  std::fclose(fp);
  return written == pdf.size();
}

static std::string MakeTempPdfPath() {
  // Use glib's mkstemp for a unique filename.
  gchar *tmpl = g_strdup("poppler_selected_region_XXXXXX.pdf");
  // g_mkstemp modifies in-place and returns an fd.
  int fd = g_mkstemp(tmpl);
  if (fd >= 0)
    close(fd);
  std::string path = tmpl ? tmpl : "";
  if (tmpl)
    g_free(tmpl);
  return path;
}

class PopplerPageGetSelectedRegionTest_2442 : public ::testing::Test {
public:
  void SetUp() override {
    pdf_path_ = MakeTempPdfPath();
    ASSERT_FALSE(pdf_path_.empty());
    ASSERT_TRUE(WriteMinimalPdfToPath(pdf_path_.c_str()));

    const std::string uri = MakeFileUri(pdf_path_.c_str());
    ASSERT_FALSE(uri.empty());

    GError *error = nullptr;
    doc_ = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
    if (!doc_) {
      std::string msg = error ? error->message : "unknown error";
      if (error)
        g_error_free(error);
      FAIL() << "Failed to open test PDF: " << msg;
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
    if (!pdf_path_.empty()) {
      std::remove(pdf_path_.c_str());
    }
  }

protected:
  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
  std::string pdf_path_;
};

static PopplerRectangle MakeSelectionWholePage() {
  PopplerRectangle sel;
  // Use a very large selection that surely covers the text, regardless of
  // coordinate origin conventions.
  sel.x1 = -1000.0;
  sel.y1 = -1000.0;
  sel.x2 =  2000.0;
  sel.y2 =  2000.0;
  return sel;
}

}  // namespace

TEST_F(PopplerPageGetSelectedRegionTest_2442, ReturnsNonNullRegionForGlyphStyle_2442) {
  PopplerRectangle sel = MakeSelectionWholePage();
  cairo_region_t *region =
      poppler_page_get_selected_region(page_, /*scale=*/1.0, POPPLER_SELECTION_GLYPH, &sel);
  ASSERT_NE(region, nullptr);

  // Should select something (the "Hello" text).
  EXPECT_FALSE(cairo_region_is_empty(region));

  cairo_region_destroy(region);
}

TEST_F(PopplerPageGetSelectedRegionTest_2442, ReturnsNonNullRegionForWordAndLineStyles_2442) {
  PopplerRectangle sel = MakeSelectionWholePage();

  cairo_region_t *region_word =
      poppler_page_get_selected_region(page_, 1.0, POPPLER_SELECTION_WORD, &sel);
  ASSERT_NE(region_word, nullptr);
  EXPECT_FALSE(cairo_region_is_empty(region_word));
  cairo_region_destroy(region_word);

  cairo_region_t *region_line =
      poppler_page_get_selected_region(page_, 1.0, POPPLER_SELECTION_LINE, &sel);
  ASSERT_NE(region_line, nullptr);
  EXPECT_FALSE(cairo_region_is_empty(region_line));
  cairo_region_destroy(region_line);
}

TEST_F(PopplerPageGetSelectedRegionTest_2442, ScaleAffectsRegionExtents_2442) {
  PopplerRectangle sel = MakeSelectionWholePage();

  cairo_region_t *r1 =
      poppler_page_get_selected_region(page_, /*scale=*/1.0, POPPLER_SELECTION_GLYPH, &sel);
  ASSERT_NE(r1, nullptr);
  ASSERT_FALSE(cairo_region_is_empty(r1));

  cairo_region_t *r2 =
      poppler_page_get_selected_region(page_, /*scale=*/2.0, POPPLER_SELECTION_GLYPH, &sel);
  ASSERT_NE(r2, nullptr);
  ASSERT_FALSE(cairo_region_is_empty(r2));

  cairo_rectangle_int_t e1;
  cairo_rectangle_int_t e2;
  cairo_region_get_extents(r1, &e1);
  cairo_region_get_extents(r2, &e2);

  // Extents should grow roughly proportional to scale (allowing rounding).
  EXPECT_GE(e2.width,  (e1.width  * 2) - 2);
  EXPECT_GE(e2.height, (e1.height * 2) - 2);

  cairo_region_destroy(r2);
  cairo_region_destroy(r1);
}

TEST_F(PopplerPageGetSelectedRegionTest_2442, ZeroScaleProducesEmptyOrDegenerateRegion_2442) {
  PopplerRectangle sel = MakeSelectionWholePage();

  cairo_region_t *region =
      poppler_page_get_selected_region(page_, /*scale=*/0.0, POPPLER_SELECTION_GLYPH, &sel);
  ASSERT_NE(region, nullptr);

  // With scale=0, all rectangles unioned should have 0 width/height after rounding,
  // so region is expected to be empty (or at least have zero extents).
  if (!cairo_region_is_empty(region)) {
    cairo_rectangle_int_t e;
    cairo_region_get_extents(region, &e);
    EXPECT_EQ(e.width, 0);
    EXPECT_EQ(e.height, 0);
  }

  cairo_region_destroy(region);
}

TEST_F(PopplerPageGetSelectedRegionTest_2442, EmptySelectionLikelyProducesEmptyRegion_2442) {
  PopplerRectangle sel;
  sel.x1 = 10.0;
  sel.y1 = 10.0;
  sel.x2 = 10.0;  // zero-area selection
  sel.y2 = 10.0;

  cairo_region_t *region =
      poppler_page_get_selected_region(page_, /*scale=*/1.0, POPPLER_SELECTION_GLYPH, &sel);
  ASSERT_NE(region, nullptr);

  // Observable behavior: should not crash; for a zero-area selection,
  // the region is expected to be empty.
  EXPECT_TRUE(cairo_region_is_empty(region));

  cairo_region_destroy(region);
}

TEST_F(PopplerPageGetSelectedRegionTest_2442, VeryLargeScaleStillReturnsValidRegion_2442) {
  PopplerRectangle sel = MakeSelectionWholePage();

  cairo_region_t *region =
      poppler_page_get_selected_region(page_, /*scale=*/100.0, POPPLER_SELECTION_WORD, &sel);
  ASSERT_NE(region, nullptr);

  // Should still be non-empty for our test PDF (text exists).
  EXPECT_FALSE(cairo_region_is_empty(region));

  cairo_rectangle_int_t e;
  cairo_region_get_extents(region, &e);

  // With a very large scale, extents should be noticeably large.
  EXPECT_GT(e.width,  10);
  EXPECT_GT(e.height, 10);

  cairo_region_destroy(region);
}