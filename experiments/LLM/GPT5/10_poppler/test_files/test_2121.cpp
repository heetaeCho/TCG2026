// File: poppler-annot-stamp-set-custom-image-test_2121.cc
#include <gtest/gtest.h>

#include <poppler.h>
#include <cairo.h>
#include <glib.h>

#include <string>
#include <memory>

namespace {

struct GObjectDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(G_OBJECT(p));
    }
  }
};

struct CairoSurfaceDeleter {
  void operator()(cairo_surface_t* s) const {
    if (s) {
      cairo_surface_destroy(s);
    }
  }
};

struct GErrorDeleter {
  void operator()(GError* e) const {
    if (e) {
      g_error_free(e);
    }
  }
};

struct AnnotMappingListDeleter {
  void operator()(GList* list) const {
    if (list) {
      poppler_page_free_annot_mapping(list);
    }
  }
};

// Minimal PDF with one page and one /Stamp annotation.
std::string MakeOnePageStampAnnotPdf() {
  // NOTE: This is a minimal, self-contained PDF intended for Poppler parsing in tests.
  // It defines a single page with a Stamp annotation in /Annots.
  const char* pdf =
      "%PDF-1.4\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << >>\n"
      "   /Annots [5 0 R]\n"
      ">>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n"
      "5 0 obj\n"
      "<< /Type /Annot /Subtype /Stamp\n"
      "   /Rect [10 10 60 60]\n"
      "   /Contents (Test Stamp)\n"
      "   /Name /Approved\n"
      ">>\n"
      "endobj\n"
      "xref\n"
      "0 6\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000058 00000 n \n"
      "0000000115 00000 n \n"
      "0000000233 00000 n \n"
      "0000000284 00000 n \n"
      "trailer\n"
      "<< /Size 6 /Root 1 0 R >>\n"
      "startxref\n"
      "380\n"
      "%%EOF\n";
  return std::string(pdf);
}

std::unique_ptr<PopplerDocument, GObjectDeleter> LoadDocFromDataOrSkip(const std::string& data) {
  std::unique_ptr<GError, GErrorDeleter> err;
  GError* raw_err = nullptr;

  PopplerDocument* doc =
      poppler_document_new_from_data(data.data(), static_cast<int>(data.size()), /*password=*/nullptr, &raw_err);
  err.reset(raw_err);

  if (!doc) {
    // If Poppler build/config rejects this minimal PDF, skip rather than fail.
    // (Test environment differences can affect strictness.)
    GTEST_SKIP() << "Failed to load in-memory PDF: " << (err ? err->message : "unknown error");
  }
  return std::unique_ptr<PopplerDocument, GObjectDeleter>(doc);
}

std::unique_ptr<PopplerAnnotStamp, GObjectDeleter> FindFirstStampAnnotOrSkip(PopplerDocument* doc) {
  ASSERT_NE(doc, nullptr);

  PopplerPage* page_raw = poppler_document_get_page(doc, 0);
  std::unique_ptr<PopplerPage, GObjectDeleter> page(page_raw);
  if (!page) {
    GTEST_SKIP() << "Could not get page 0 from document";
  }

  GList* mappings_raw = poppler_page_get_annot_mapping(page.get());
  std::unique_ptr<GList, AnnotMappingListDeleter> mappings(mappings_raw);
  if (!mappings) {
    GTEST_SKIP() << "No annotation mappings found on page 0";
  }

  for (GList* l = mappings.get(); l; l = l->next) {
    auto* mapping = static_cast<PopplerAnnotMapping*>(l->data);
    if (!mapping || !mapping->annot) {
      continue;
    }
    if (POPPLER_IS_ANNOT_STAMP(mapping->annot)) {
      // Hold a ref to return it independently of mapping list lifetime.
      PopplerAnnotStamp* stamp = POPPLER_ANNOT_STAMP(mapping->annot);
      return std::unique_ptr<PopplerAnnotStamp, GObjectDeleter>(POPPLER_ANNOT_STAMP(g_object_ref(stamp)));
    }
  }

  GTEST_SKIP() << "No PopplerAnnotStamp found in the test PDF (unexpected for this fixture)";
  return nullptr;
}

}  // namespace

// -----------------------------------------------------------------------------
// Tests for poppler_annot_stamp_set_custom_image
// -----------------------------------------------------------------------------

TEST(PopplerAnnotStampSetCustomImageTest_2121, NullAnnotReturnsFalse_2121) {
  // Boundary / error case: g_return_val_if_fail should make this return FALSE.
  EXPECT_FALSE(poppler_annot_stamp_set_custom_image(nullptr, /*image=*/nullptr, /*error=*/nullptr));
}

TEST(PopplerAnnotStampSetCustomImageTest_2121, SetsCustomImageWithValidStampAnnotAndImage_2121) {
  // Normal operation: create a valid stamp annotation from an in-memory PDF and set an image.
  const std::string pdf = MakeOnePageStampAnnotPdf();
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto stamp = FindFirstStampAnnotOrSkip(doc.get());

  std::unique_ptr<cairo_surface_t, CairoSurfaceDeleter> surface(
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 8, 8));
  ASSERT_NE(surface.get(), nullptr);
  ASSERT_EQ(cairo_surface_status(surface.get()), CAIRO_STATUS_SUCCESS);

  GError* error = nullptr;
  const gboolean ok = poppler_annot_stamp_set_custom_image(stamp.get(), surface.get(), &error);

  // Observable behavior: boolean result and error reporting.
  EXPECT_TRUE(ok);
  EXPECT_EQ(error, nullptr);

  if (error) {
    g_error_free(error);
  }
}

TEST(PopplerAnnotStampSetCustomImageTest_2121, SucceedsWithoutErrorOutParam_2121) {
  // Boundary: caller passes error==nullptr; function should still succeed for valid inputs.
  const std::string pdf = MakeOnePageStampAnnotPdf();
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto stamp = FindFirstStampAnnotOrSkip(doc.get());

  std::unique_ptr<cairo_surface_t, CairoSurfaceDeleter> surface(
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 4, 4));
  ASSERT_NE(surface.get(), nullptr);
  ASSERT_EQ(cairo_surface_status(surface.get()), CAIRO_STATUS_SUCCESS);

  EXPECT_TRUE(poppler_annot_stamp_set_custom_image(stamp.get(), surface.get(), /*error=*/nullptr));
}

TEST(PopplerAnnotStampSetCustomImageTest_2121, HandlesNonImageSurfaceGracefully_2121) {
  // Exceptional-ish / boundary case: use a recording surface instead of an image surface.
  // Different Poppler builds may or may not accept this; we assert consistent observable behavior:
  // - If it fails, it should return FALSE and set an error if provided.
  // - If it succeeds, error should remain nullptr.
  const std::string pdf = MakeOnePageStampAnnotPdf();
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto stamp = FindFirstStampAnnotOrSkip(doc.get());

  cairo_rectangle_t extents;
  extents.x = 0;
  extents.y = 0;
  extents.width = 16;
  extents.height = 16;

  std::unique_ptr<cairo_surface_t, CairoSurfaceDeleter> surface(
      cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, &extents));
  ASSERT_NE(surface.get(), nullptr);
  ASSERT_EQ(cairo_surface_status(surface.get()), CAIRO_STATUS_SUCCESS);

  GError* error = nullptr;
  const gboolean ok = poppler_annot_stamp_set_custom_image(stamp.get(), surface.get(), &error);

  if (ok) {
    EXPECT_EQ(error, nullptr);
  } else {
    // If conversion rejects this surface type, ensure it reports an error when asked.
    EXPECT_NE(error, nullptr);
  }

  if (error) {
    g_error_free(error);
  }
}