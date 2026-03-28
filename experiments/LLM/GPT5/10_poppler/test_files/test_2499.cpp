// File: poppler-page-get-bounding-box-test_2499.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cairo.h>
#include <cairo-pdf.h>

#include <cmath>
#include <cstdio>
#include <string>

namespace {

struct TempDirDeleter {
  void operator()(gchar* p) const {
    if (p) {
      // Best-effort cleanup; tests delete files individually too.
      g_rmdir(p);
      g_free(p);
    }
  }
};

static std::string ToFileUri(const std::string& path) {
  // poppler_document_new_from_file expects a URI.
  gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, /*error=*/nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
}

static bool CreatePdfWithCairo(const std::string& path,
                               double width_pts,
                               double height_pts,
                               const std::function<void(cairo_t*)>& draw) {
  cairo_surface_t* surface = cairo_pdf_surface_create(path.c_str(), width_pts, height_pts);
  if (!surface) {
    return false;
  }
  cairo_status_t st = cairo_surface_status(surface);
  if (st != CAIRO_STATUS_SUCCESS) {
    cairo_surface_destroy(surface);
    return false;
  }

  cairo_t* cr = cairo_create(surface);
  if (!cr) {
    cairo_surface_destroy(surface);
    return false;
  }

  if (draw) {
    draw(cr);
  }

  cairo_show_page(cr);
  cairo_destroy(cr);

  cairo_surface_finish(surface);
  st = cairo_surface_status(surface);
  cairo_surface_destroy(surface);

  return st == CAIRO_STATUS_SUCCESS;
}

static PopplerDocument* LoadDocFromPath(const std::string& path) {
  GError* error = nullptr;
  const std::string uri = ToFileUri(path);
  if (uri.empty()) {
    return nullptr;
  }
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  if (error) {
    g_error_free(error);
  }
  return doc;
}

static PopplerPage* GetFirstPage(PopplerDocument* doc) {
  if (!doc) return nullptr;
  return poppler_document_get_page(doc, 0);
}

// Tries to initialize all 4 rectangle fields if they exist in the build.
// We avoid relying on private layout beyond the public header. If the header
// only contains x2/y2 in this project variant, these writes will fail to compile;
// in that environment, the production header should match the implementation
// (which clearly uses x1/y1/x2/y2). So we assume the real header has them.
static void InitRect(PopplerRectangle* r, double x1, double y1, double x2, double y2) {
  r->x1 = x1;
  r->y1 = y1;
  r->x2 = x2;
  r->y2 = y2;
}

static bool RectEquals(const PopplerRectangle& a,
                       double x1, double y1, double x2, double y2) {
  return a.x1 == x1 && a.y1 == y1 && a.x2 == x2 && a.y2 == y2;
}

}  // namespace

class PopplerPageGetBoundingBoxTest_2499 : public ::testing::Test {
 protected:
  void SetUp() override {
    gchar* tmp = g_dir_make_tmp("poppler-bbox-XXXXXX", /*error=*/nullptr);
    ASSERT_NE(tmp, nullptr);
    tmp_dir_.reset(tmp);

    blank_pdf_path_ = std::string(tmp_dir_.get()) + G_DIR_SEPARATOR_S + "blank.pdf";
    rect_pdf_path_  = std::string(tmp_dir_.get()) + G_DIR_SEPARATOR_S + "rect.pdf";

    // A blank page: no drawing operations.
    ASSERT_TRUE(CreatePdfWithCairo(blank_pdf_path_, 612.0, 792.0, [](cairo_t* /*cr*/) {
      // Intentionally empty.
    }));

    // A page with a stroked rectangle at known-ish coords.
    // Note: Bounding box may include stroke width; tests only assert it encloses our geometry.
    ASSERT_TRUE(CreatePdfWithCairo(rect_pdf_path_, 612.0, 792.0, [](cairo_t* cr) {
      cairo_set_line_width(cr, 2.0);
      cairo_rectangle(cr, 100.0, 150.0, 200.0, 120.0);  // x=[100..300], y=[150..270]
      cairo_stroke(cr);
    }));
  }

  void TearDown() override {
    if (!blank_pdf_path_.empty()) {
      g_remove(blank_pdf_path_.c_str());
    }
    if (!rect_pdf_path_.empty()) {
      g_remove(rect_pdf_path_.c_str());
    }
    // tmp_dir_ removed by deleter best-effort.
  }

  std::unique_ptr<gchar, TempDirDeleter> tmp_dir_{nullptr};
  std::string blank_pdf_path_;
  std::string rect_pdf_path_;
};

TEST_F(PopplerPageGetBoundingBoxTest_2499, NullPageReturnsFalse_2499) {
  PopplerRectangle rect;
  InitRect(&rect, -1, -2, -3, -4);

  gboolean ok = poppler_page_get_bounding_box(nullptr, &rect);
  EXPECT_FALSE(ok);

  // Function should not scribble on rect when precondition fails.
  EXPECT_TRUE(RectEquals(rect, -1, -2, -3, -4));
}

TEST_F(PopplerPageGetBoundingBoxTest_2499, NullRectReturnsFalse_2499) {
  PopplerDocument* doc = LoadDocFromPath(rect_pdf_path_);
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  gboolean ok = poppler_page_get_bounding_box(page, nullptr);
  EXPECT_FALSE(ok);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetBoundingBoxTest_2499, BlankPageReturnsFalseAndDoesNotModifyRect_2499) {
  PopplerDocument* doc = LoadDocFromPath(blank_pdf_path_);
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  PopplerRectangle rect;
  InitRect(&rect, 111, 222, 333, 444);

  gboolean ok = poppler_page_get_bounding_box(page, &rect);
  EXPECT_FALSE(ok);

  // Contract in implementation: only writes rect when hasGraphics is true.
  EXPECT_TRUE(RectEquals(rect, 111, 222, 333, 444));

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetBoundingBoxTest_2499, PageWithVectorGraphicsReturnsTrueAndWritesRect_2499) {
  PopplerDocument* doc = LoadDocFromPath(rect_pdf_path_);
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  double page_w = 0.0, page_h = 0.0;
  poppler_page_get_size(page, &page_w, &page_h);
  ASSERT_GT(page_w, 0.0);
  ASSERT_GT(page_h, 0.0);

  PopplerRectangle rect;
  InitRect(&rect, -999, -999, -999, -999);

  gboolean ok = poppler_page_get_bounding_box(page, &rect);
  ASSERT_TRUE(ok);

  // Basic sanity: ordered coordinates.
  EXPECT_LE(rect.x1, rect.x2);
  EXPECT_LE(rect.y1, rect.y2);

  // Should be within (or extremely close to) the page bounds when using MediaBox.
  // We allow slight negatives / slight overshoot just in case of stroke inflation / float rounding.
  const double kTol = 5.0;
  EXPECT_GE(rect.x1, -kTol);
  EXPECT_GE(rect.y1, -kTol);
  EXPECT_LE(rect.x2, page_w + kTol);
  EXPECT_LE(rect.y2, page_h + kTol);

  // Should enclose the rectangle we drew: x=[100..300], y=[150..270]
  EXPECT_LE(rect.x1, 100.0);
  EXPECT_LE(rect.y1, 150.0);
  EXPECT_GE(rect.x2, 300.0);
  EXPECT_GE(rect.y2, 270.0);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetBoundingBoxTest_2499, RepeatedCallsAreConsistentForSamePage_2499) {
  PopplerDocument* doc = LoadDocFromPath(rect_pdf_path_);
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  PopplerRectangle r1, r2;
  InitRect(&r1, 0, 0, 0, 0);
  InitRect(&r2, 0, 0, 0, 0);

  gboolean ok1 = poppler_page_get_bounding_box(page, &r1);
  gboolean ok2 = poppler_page_get_bounding_box(page, &r2);

  ASSERT_TRUE(ok1);
  ASSERT_TRUE(ok2);

  // Black-box observable behavior: same input page => stable bounding box.
  EXPECT_DOUBLE_EQ(r1.x1, r2.x1);
  EXPECT_DOUBLE_EQ(r1.y1, r2.y1);
  EXPECT_DOUBLE_EQ(r1.x2, r2.x2);
  EXPECT_DOUBLE_EQ(r1.y2, r2.y2);

  g_object_unref(page);
  g_object_unref(doc);
}