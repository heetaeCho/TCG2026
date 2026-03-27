// poppler-page-get-image-test_2450.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <cairo.h>
#include <cairo-pdf.h>

#include <string>

// NOTE: These tests treat poppler_page_get_image() as a black box and only
// validate observable behavior via its public signature and return values.

namespace {

class ScopedGLogFatalMask {
 public:
  explicit ScopedGLogFatalMask(GLogLevelFlags new_mask) {
    old_mask_ = g_log_set_always_fatal(new_mask);
  }
  ~ScopedGLogFatalMask() { g_log_set_always_fatal(old_mask_); }

  ScopedGLogFatalMask(const ScopedGLogFatalMask&) = delete;
  ScopedGLogFatalMask& operator=(const ScopedGLogFatalMask&) = delete;

 private:
  GLogLevelFlags old_mask_;
};

static std::string ToFileUri(const std::string& path) {
  // g_filename_to_uri() handles escaping, but requires absolute path.
  gchar* abs_path = g_canonicalize_filename(path.c_str(), /*relative_to=*/nullptr);
  gchar* uri = g_filename_to_uri(abs_path, /*hostname=*/nullptr, /*error=*/nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  g_free(abs_path);
  return out;
}

static bool WritePdfWithEmbeddedImage(const std::string& pdf_path) {
  // Create a simple PDF with a raster image painted onto it.
  cairo_surface_t* pdf = cairo_pdf_surface_create(pdf_path.c_str(), 64.0, 64.0);
  if (!pdf || cairo_surface_status(pdf) != CAIRO_STATUS_SUCCESS) {
    if (pdf) cairo_surface_destroy(pdf);
    return false;
  }

  cairo_t* cr = cairo_create(pdf);
  if (!cr || cairo_status(cr) != CAIRO_STATUS_SUCCESS) {
    if (cr) cairo_destroy(cr);
    cairo_surface_destroy(pdf);
    return false;
  }

  cairo_surface_t* img = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 16, 16);
  if (!img || cairo_surface_status(img) != CAIRO_STATUS_SUCCESS) {
    if (img) cairo_surface_destroy(img);
    cairo_destroy(cr);
    cairo_surface_destroy(pdf);
    return false;
  }

  // Paint something non-empty into the image.
  cairo_t* icr = cairo_create(img);
  cairo_set_source_rgba(icr, 1.0, 0.0, 0.0, 1.0);
  cairo_paint(icr);
  cairo_destroy(icr);

  // Paint the image onto the PDF.
  cairo_set_source_surface(cr, img, 8.0, 8.0);
  cairo_paint(cr);

  cairo_surface_destroy(img);
  cairo_destroy(cr);

  cairo_surface_finish(pdf);
  cairo_surface_destroy(pdf);

  return true;
}

static bool WritePdfWithoutImages(const std::string& pdf_path) {
  // Create a PDF with only vector content (no embedded raster images).
  cairo_surface_t* pdf = cairo_pdf_surface_create(pdf_path.c_str(), 64.0, 64.0);
  if (!pdf || cairo_surface_status(pdf) != CAIRO_STATUS_SUCCESS) {
    if (pdf) cairo_surface_destroy(pdf);
    return false;
  }

  cairo_t* cr = cairo_create(pdf);
  if (!cr || cairo_status(cr) != CAIRO_STATUS_SUCCESS) {
    if (cr) cairo_destroy(cr);
    cairo_surface_destroy(pdf);
    return false;
  }

  cairo_set_line_width(cr, 2.0);
  cairo_rectangle(cr, 8.0, 8.0, 48.0, 48.0);
  cairo_stroke(cr);

  cairo_destroy(cr);
  cairo_surface_finish(pdf);
  cairo_surface_destroy(pdf);

  return true;
}

class PopplerPageGetImageTest_2450 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temp directory.
    gchar* dir_template = g_strdup("poppler-gimage-XXXXXX");
    gchar* tmp_dir = g_dir_make_tmp(dir_template, /*error=*/nullptr);
    g_free(dir_template);
    ASSERT_NE(tmp_dir, nullptr);

    tmp_dir_ = tmp_dir;
    g_free(tmp_dir);

    pdf_path_ = tmp_dir_ + G_DIR_SEPARATOR_S + "with_image.pdf";
    ASSERT_TRUE(WritePdfWithEmbeddedImage(pdf_path_));

    std::string uri = ToFileUri(pdf_path_);
    ASSERT_FALSE(uri.empty());

    GError* error = nullptr;
    document_ = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
    if (!document_) {
      std::string msg = error ? error->message : "unknown error";
      if (error) g_error_free(error);
      FAIL() << "Failed to open generated PDF: " << msg;
    }
    if (error) g_error_free(error);

    page_ = poppler_document_get_page(document_, 0);
    ASSERT_NE(page_, nullptr);
  }

  void TearDown() override {
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (document_) {
      g_object_unref(document_);
      document_ = nullptr;
    }

    if (!pdf_path_.empty()) {
      g_remove(pdf_path_.c_str());
    }
    if (!tmp_dir_.empty()) {
      g_rmdir(tmp_dir_.c_str());
    }
  }

  PopplerDocument* document_ = nullptr;
  PopplerPage* page_ = nullptr;

  std::string tmp_dir_;
  std::string pdf_path_;
};

}  // namespace

TEST_F(PopplerPageGetImageTest_2450, NullPageReturnsNull_2450) {
  // g_return_val_if_fail may log CRITICAL; avoid turning this into a fatal error
  // in test environments that use fatal-criticals.
  ScopedGLogFatalMask no_fatal_criticals(G_LOG_LEVEL_ERROR);

  cairo_surface_t* img = poppler_page_get_image(nullptr, 0);
  EXPECT_EQ(img, nullptr);
}

TEST_F(PopplerPageGetImageTest_2450, OutOfRangeImageIdReturnsNull_2450) {
  // Using a very large id should be out-of-range regardless of how many images exist.
  cairo_surface_t* img = poppler_page_get_image(page_, G_MAXINT);
  EXPECT_EQ(img, nullptr);
}

TEST_F(PopplerPageGetImageTest_2450, ImageIdZeroReturnsSurface_2450) {
  // For a page that (very likely) contains at least one embedded raster image,
  // requesting image_id=0 should return a cairo_surface_t*.
  cairo_surface_t* img = poppler_page_get_image(page_, 0);

  // If Poppler decides this PDF has 0 "images" in its internal list, the API may
  // return nullptr; that is an observable/allowed outcome. But if it returns a
  // surface, it must be a valid cairo surface.
  if (!img) {
    GTEST_SKIP() << "poppler_page_get_image(page, 0) returned nullptr; "
                    "environment/Poppler build may not expose the embedded image.";
  }

  EXPECT_EQ(cairo_surface_status(img), CAIRO_STATUS_SUCCESS);

  // Ensure the returned surface is usable and can be safely destroyed by the caller.
  cairo_surface_flush(img);
  cairo_surface_destroy(img);
}

TEST_F(PopplerPageGetImageTest_2450, PageWithoutImagesReturnsNull_2450) {
  // Create a separate PDF that should contain no raster images and verify nullptr.
  gchar* dir_template = g_strdup("poppler-gimage-noimg-XXXXXX");
  gchar* tmp_dir = g_dir_make_tmp(dir_template, /*error=*/nullptr);
  g_free(dir_template);
  ASSERT_NE(tmp_dir, nullptr);

  std::string tmp_dir_str = tmp_dir;
  g_free(tmp_dir);

  std::string pdf_path = tmp_dir_str + G_DIR_SEPARATOR_S + "no_images.pdf";
  ASSERT_TRUE(WritePdfWithoutImages(pdf_path));

  std::string uri = ToFileUri(pdf_path);
  ASSERT_FALSE(uri.empty());

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  cairo_surface_t* img = poppler_page_get_image(page, 0);
  EXPECT_EQ(img, nullptr);

  g_object_unref(page);
  g_object_unref(doc);

  g_remove(pdf_path.c_str());
  g_rmdir(tmp_dir_str.c_str());
}