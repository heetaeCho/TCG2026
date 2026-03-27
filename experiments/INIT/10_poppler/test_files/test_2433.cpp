// File: poppler-page-render-full-test_2433.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cairo.h>
#include <cairo-pdf.h>

#include <cstdio>
#include <string>

// Function under test (implemented in poppler-page.cc)
extern "C" void poppler_page_render_full(PopplerPage *page,
                                        cairo_t *cairo,
                                        gboolean printing,
                                        PopplerRenderAnnotsFlags flags);

namespace {

class PopplerPageRenderFullTest_2433 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Create a small PDF file via cairo so Poppler can reliably load it.
    tmp_pdf_path_ = MakeTempPdfPath_2433();
    ASSERT_FALSE(tmp_pdf_path_.empty());

    {
      cairo_surface_t *pdf_surface =
          cairo_pdf_surface_create(tmp_pdf_path_.c_str(), 200.0, 200.0);
      ASSERT_NE(pdf_surface, nullptr);

      cairo_t *cr = cairo_create(pdf_surface);
      ASSERT_NE(cr, nullptr);

      // Draw something simple.
      cairo_move_to(cr, 10, 10);
      cairo_line_to(cr, 190, 190);
      cairo_stroke(cr);

      cairo_destroy(cr);
      cairo_surface_finish(pdf_surface);
      cairo_surface_destroy(pdf_surface);
    }

    // Convert filename to file:// URI for poppler_document_new_from_file.
    GError *error = nullptr;
    char *uri = g_filename_to_uri(tmp_pdf_path_.c_str(), /*hostname=*/nullptr, &error);
    ASSERT_EQ(error, nullptr);
    ASSERT_NE(uri, nullptr);
    tmp_pdf_uri_ = uri;
    g_free(uri);

    doc_ = poppler_document_new_from_file(tmp_pdf_uri_.c_str(), /*password=*/nullptr, &error);
    ASSERT_EQ(error, nullptr);
    ASSERT_NE(doc_, nullptr);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    // Create an image surface and cairo context for rendering.
    image_surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 64, 64);
    ASSERT_NE(image_surface_, nullptr);
    cr_ = cairo_create(image_surface_);
    ASSERT_NE(cr_, nullptr);
  }

  void TearDown() override
  {
    if (cr_) {
      cairo_destroy(cr_);
      cr_ = nullptr;
    }
    if (image_surface_) {
      cairo_surface_destroy(image_surface_);
      image_surface_ = nullptr;
    }
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (!tmp_pdf_path_.empty()) {
      std::remove(tmp_pdf_path_.c_str());
    }
  }

  static std::string MakeTempPdfPath_2433()
  {
    // g_file_open_tmp creates a file in a safe temp location.
    GError *error = nullptr;
    gchar *filename = nullptr;
    int fd = g_file_open_tmp("poppler_page_render_full_2433_XXXXXX.pdf", &filename, &error);
    if (fd >= 0) {
      close(fd);
    }
    if (error != nullptr || filename == nullptr) {
      if (error) {
        g_error_free(error);
      }
      if (filename) {
        g_free(filename);
      }
      return {};
    }
    std::string path(filename);
    g_free(filename);
    return path;
  }

  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;

  cairo_surface_t *image_surface_ = nullptr;
  cairo_t *cr_ = nullptr;

  std::string tmp_pdf_path_;
  std::string tmp_pdf_uri_;
};

static void GetCairoMatrix_2433(cairo_t *cr, cairo_matrix_t *out)
{
  ASSERT_NE(cr, nullptr);
  ASSERT_NE(out, nullptr);
  cairo_get_matrix(cr, out);
}

static void ExpectCairoMatrixEq_2433(const cairo_matrix_t &a, const cairo_matrix_t &b)
{
  // Exact compare is OK here because we set integers / exact transforms.
  EXPECT_DOUBLE_EQ(a.xx, b.xx);
  EXPECT_DOUBLE_EQ(a.yx, b.yx);
  EXPECT_DOUBLE_EQ(a.xy, b.xy);
  EXPECT_DOUBLE_EQ(a.yy, b.yy);
  EXPECT_DOUBLE_EQ(a.x0, b.x0);
  EXPECT_DOUBLE_EQ(a.y0, b.y0);
}

} // namespace

TEST_F(PopplerPageRenderFullTest_2433, RendersWithoutPrinting_DoesNotCorruptCairoState_2433)
{
  // Arrange: establish a known cairo state (matrix + clip).
  cairo_translate(cr_, 5.0, 7.0);
  cairo_rectangle(cr_, 1.0, 2.0, 30.0, 40.0);
  cairo_clip(cr_);

  cairo_matrix_t before_matrix;
  GetCairoMatrix_2433(cr_, &before_matrix);

  double before_x1 = 0, before_y1 = 0, before_x2 = 0, before_y2 = 0;
  cairo_clip_extents(cr_, &before_x1, &before_y1, &before_x2, &before_y2);

  // Act
  poppler_page_render_full(page_, cr_, FALSE, POPPLER_RENDER_ANNOTS_NONE);

  // Assert: save/restore should keep cairo state stable for callers.
  cairo_matrix_t after_matrix;
  GetCairoMatrix_2433(cr_, &after_matrix);
  ExpectCairoMatrixEq_2433(before_matrix, after_matrix);

  double after_x1 = 0, after_y1 = 0, after_x2 = 0, after_y2 = 0;
  cairo_clip_extents(cr_, &after_x1, &after_y1, &after_x2, &after_y2);

  EXPECT_DOUBLE_EQ(before_x1, after_x1);
  EXPECT_DOUBLE_EQ(before_y1, after_y1);
  EXPECT_DOUBLE_EQ(before_x2, after_x2);
  EXPECT_DOUBLE_EQ(before_y2, after_y2);
}

TEST_F(PopplerPageRenderFullTest_2433, RendersWithPrinting_DoesNotCorruptCairoState_2433)
{
  // Arrange
  cairo_scale(cr_, 2.0, 3.0);
  cairo_rectangle(cr_, 0.0, 0.0, 10.0, 10.0);
  cairo_clip(cr_);

  cairo_matrix_t before_matrix;
  GetCairoMatrix_2433(cr_, &before_matrix);

  // Act
  poppler_page_render_full(page_, cr_, TRUE, POPPLER_RENDER_ANNOTS_NONE);

  // Assert
  cairo_matrix_t after_matrix;
  GetCairoMatrix_2433(cr_, &after_matrix);
  ExpectCairoMatrixEq_2433(before_matrix, after_matrix);
}

TEST_F(PopplerPageRenderFullTest_2433, Boundary_TinySurface_DoesNotCrash_2433)
{
  // Create a 1x1 surface/context as a boundary condition.
  cairo_surface_t *tiny = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
  ASSERT_NE(tiny, nullptr);
  cairo_t *tiny_cr = cairo_create(tiny);
  ASSERT_NE(tiny_cr, nullptr);

  // Act / Assert (no crash)
  poppler_page_render_full(page_, tiny_cr, FALSE, POPPLER_RENDER_ANNOTS_NONE);

  cairo_destroy(tiny_cr);
  cairo_surface_destroy(tiny);
}

TEST_F(PopplerPageRenderFullTest_2433, Boundary_MultipleCalls_SameInputs_DoesNotCrash_2433)
{
  // Act / Assert: calling multiple times should be safe from the public interface POV.
  poppler_page_render_full(page_, cr_, FALSE, POPPLER_RENDER_ANNOTS_NONE);
  poppler_page_render_full(page_, cr_, FALSE, POPPLER_RENDER_ANNOTS_NONE);
  poppler_page_render_full(page_, cr_, TRUE, POPPLER_RENDER_ANNOTS_NONE);
}

TEST_F(PopplerPageRenderFullTest_2433, Error_NullCairo_TriggersCritical_2433)
{
  // g_return_if_fail(cairo != nullptr) should raise a critical.
  // Make criticals fatal *in the death-test subprocess* so the failure is observable.
  EXPECT_DEATH(
      {
        g_log_set_always_fatal(static_cast<GLogLevelFlags>(G_LOG_FATAL_MASK | G_LOG_LEVEL_CRITICAL));
        poppler_page_render_full(page_, nullptr, FALSE, POPPLER_RENDER_ANNOTS_NONE);
      },
      ".*");
}

TEST_F(PopplerPageRenderFullTest_2433, Error_NullPage_TriggersCritical_2433)
{
  // g_return_if_fail(POPPLER_IS_PAGE(page)) should raise a critical.
  EXPECT_DEATH(
      {
        g_log_set_always_fatal(static_cast<GLogLevelFlags>(G_LOG_FATAL_MASK | G_LOG_LEVEL_CRITICAL));
        poppler_page_render_full(nullptr, cr_, FALSE, POPPLER_RENDER_ANNOTS_NONE);
      },
      ".*");
}

TEST_F(PopplerPageRenderFullTest_2433, Flags_AcceptsNonZeroFlagsValue_2433)
{
  // Boundary-ish: pass a non-zero flags value without assuming exact semantics.
  // (If POPPLER_RENDER_ANNOTS_ALL exists, prefer it; otherwise use a generic non-zero cast.)
  PopplerRenderAnnotsFlags flags = POPPLER_RENDER_ANNOTS_NONE;
#ifdef POPPLER_RENDER_ANNOTS_ALL
  flags = POPPLER_RENDER_ANNOTS_ALL;
#else
  flags = static_cast<PopplerRenderAnnotsFlags>(1);
#endif

  // Act / Assert: should not crash.
  poppler_page_render_full(page_, cr_, FALSE, flags);
}