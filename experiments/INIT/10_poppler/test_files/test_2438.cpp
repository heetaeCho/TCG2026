// File: poppler-page-get-thumbnail-test.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <cairo.h>
#include <cairo-pdf.h>

#include <glib.h>

#include <string>

namespace {

class PopplerPageGetThumbnailTest_2438 : public ::testing::Test {
protected:
  void SetUp() override = default;
  void TearDown() override = default;

  static std::string CreateTempPdfPath() {
    // mkstemp needs a writable char buffer ending in "XXXXXX".
    std::string tmpl = std::string(g_get_tmp_dir()) + G_DIR_SEPARATOR_S + "poppler_thumb_2438_XXXXXX.pdf";
    std::string buf = tmpl;
    int fd = g_mkstemp_full(buf.data(), buf.size() + 1, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd >= 0) {
      close(fd);
    }
    // g_mkstemp_full mutates the template in-place.
    return buf;
  }

  static void WriteSimplePdf(const std::string &path) {
    cairo_surface_t *pdf = cairo_pdf_surface_create(path.c_str(), 300.0, 300.0);
    ASSERT_NE(pdf, nullptr);
    ASSERT_EQ(cairo_surface_status(pdf), CAIRO_STATUS_SUCCESS);

    cairo_t *cr = cairo_create(pdf);
    ASSERT_NE(cr, nullptr);
    ASSERT_EQ(cairo_status(cr), CAIRO_STATUS_SUCCESS);

    // Draw something minimal; this should not create a PDF thumbnail stream.
    cairo_move_to(cr, 20.0, 40.0);
    cairo_show_text(cr, "Poppler thumbnail test 2438");

    cairo_show_page(cr);

    cairo_destroy(cr);
    cairo_surface_destroy(pdf);
  }

  static PopplerDocument *OpenDocumentFromPath(const std::string &path) {
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
    EXPECT_EQ(error, nullptr);
    EXPECT_NE(uri, nullptr);
    if (!uri) {
      if (error) g_error_free(error);
      return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    EXPECT_EQ(error, nullptr);
    if (error) {
      g_error_free(error);
      return nullptr;
    }
    EXPECT_NE(doc, nullptr);
    return doc;
  }
};

TEST_F(PopplerPageGetThumbnailTest_2438, NullPageReturnsNull_2438) {
  // g_return_val_if_fail(POPPLER_IS_PAGE(page), NULL)
  cairo_surface_t *thumb = poppler_page_get_thumbnail(nullptr);
  EXPECT_EQ(thumb, nullptr);
}

TEST_F(PopplerPageGetThumbnailTest_2438, SimplePdfWithoutThumbnailReturnsNull_2438) {
  const std::string pdf_path = CreateTempPdfPath();
  WriteSimplePdf(pdf_path);

  PopplerDocument *doc = OpenDocumentFromPath(pdf_path);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  cairo_surface_t *thumb = poppler_page_get_thumbnail(page);

  // For a freshly generated simple PDF, there should be no embedded thumbnail stream,
  // so the observable result should be NULL.
  EXPECT_EQ(thumb, nullptr);

  if (thumb) {
    cairo_surface_destroy(thumb);
  }
  g_object_unref(page);
  g_object_unref(doc);

  // Best-effort cleanup.
  g_remove(pdf_path.c_str());
}

TEST_F(PopplerPageGetThumbnailTest_2438, MultipleCallsReturnConsistentNullForNoThumb_2438) {
  const std::string pdf_path = CreateTempPdfPath();
  WriteSimplePdf(pdf_path);

  PopplerDocument *doc = OpenDocumentFromPath(pdf_path);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  cairo_surface_t *thumb1 = poppler_page_get_thumbnail(page);
  cairo_surface_t *thumb2 = poppler_page_get_thumbnail(page);

  EXPECT_EQ(thumb1, nullptr);
  EXPECT_EQ(thumb2, nullptr);

  if (thumb1) cairo_surface_destroy(thumb1);
  if (thumb2) cairo_surface_destroy(thumb2);

  g_object_unref(page);
  g_object_unref(doc);

  g_remove(pdf_path.c_str());
}

TEST_F(PopplerPageGetThumbnailTest_2438, ReturnedSurfaceIfAnyIsUsable_2438) {
  // This test is defensive: if the environment/document unexpectedly provides a thumbnail,
  // we verify that the returned surface is a valid cairo surface we can query and destroy.
  const std::string pdf_path = CreateTempPdfPath();
  WriteSimplePdf(pdf_path);

  PopplerDocument *doc = OpenDocumentFromPath(pdf_path);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  cairo_surface_t *thumb = poppler_page_get_thumbnail(page);
  if (thumb) {
    EXPECT_EQ(cairo_surface_status(thumb), CAIRO_STATUS_SUCCESS);
    // Querying type is an observable property and should be safe for any surface.
    (void)cairo_surface_get_type(thumb);
    cairo_surface_destroy(thumb);
  } else {
    // For most simple PDFs, thumbnail is absent; NULL is acceptable/expected.
    SUCCEED();
  }

  g_object_unref(page);
  g_object_unref(doc);

  g_remove(pdf_path.c_str());
}

}  // namespace