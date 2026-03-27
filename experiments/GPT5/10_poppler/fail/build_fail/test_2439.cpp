// render_selection_test_2439.cc
#include <gtest/gtest.h>

#include <cairo.h>
#include <glib.h>

#include "poppler.h"

// We need access to PopplerPage/PopplerDocument internals as used by render_selection().
#include "poppler-private.h"
#include "poppler-page.h"

// Include the implementation TU so the `static` helper is visible to this test.
// (These unit tests treat the implementation as a black box and only validate
// observable effects through cairo output.)
#include "./TestProjects/poppler/glib/poppler-page.cc"

namespace {

class RenderSelectionTest_2439 : public ::testing::Test {
 protected:
  static std::string BuildSimplePdf_2439() {
    // Build a minimal, valid 1-page PDF containing the text "Hello".
    // We compute xref offsets programmatically to avoid hardcoding them.
    struct Obj {
      int num;
      std::string body;  // includes "obj ... endobj\n"
      size_t offset = 0;
    };

    std::vector<Obj> objs;
    objs.push_back({1,
                    "1 0 obj\n"
                    "<< /Type /Catalog /Pages 2 0 R >>\n"
                    "endobj\n"});
    objs.push_back({2,
                    "2 0 obj\n"
                    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                    "endobj\n"});
    objs.push_back({3,
                    "3 0 obj\n"
                    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                    "   /Resources << /Font << /F1 5 0 R >> >>\n"
                    "   /Contents 4 0 R >>\n"
                    "endobj\n"});

    // Content stream: place "Hello" roughly centered-ish.
    const std::string stream =
        "BT\n"
        "/F1 24 Tf\n"
        "50 100 Td\n"
        "(Hello) Tj\n"
        "ET\n";
    objs.push_back({4,
                    "4 0 obj\n"
                    "<< /Length " +
                        std::to_string(stream.size()) +
                        " >>\n"
                        "stream\n" +
                        stream +
                        "endstream\n"
                        "endobj\n"});
    objs.push_back({5,
                    "5 0 obj\n"
                    "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
                    "endobj\n"});

    std::string pdf;
    pdf.reserve(2048);
    pdf += "%PDF-1.4\n";
    pdf += "%\xE2\xE3\xCF\xD3\n";  // binary comment

    // Record object offsets.
    for (auto &o : objs) {
      o.offset = pdf.size();
      pdf += o.body;
    }

    const size_t xref_offset = pdf.size();
    pdf += "xref\n";
    pdf += "0 6\n";
    pdf += "0000000000 65535 f \n";

    auto fmt_off = [](size_t off) {
      char buf[32];
      // 10-digit, zero-padded byte offset.
      g_snprintf(buf, sizeof(buf), "%010zu 00000 n \n", off);
      return std::string(buf);
    };

    // Objects 1..5
    for (const auto &o : objs) {
      pdf += fmt_off(o.offset);
    }

    pdf += "trailer\n";
    pdf += "<< /Size 6 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_offset);
    pdf += "\n%%EOF\n";

    return pdf;
  }

  static PopplerDocument *LoadDoc_2439(GError **error) {
    const std::string pdf = BuildSimplePdf_2439();
    return poppler_document_new_from_data(pdf.data(),
                                          static_cast<int>(pdf.size()),
                                          /*password=*/nullptr, error);
  }

  static cairo_surface_t *MakeSurface_2439(int w, int h) {
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
    cairo_t *cr = cairo_create(surface);

    // Paint white background.
    cairo_set_source_rgba(cr, 1, 1, 1, 1);
    cairo_paint(cr);

    cairo_destroy(cr);
    return surface;
  }

  static uint64_t HashSurface_2439(cairo_surface_t *surface) {
    cairo_surface_flush(surface);
    const unsigned char *data = cairo_image_surface_get_data(surface);
    const int stride = cairo_image_surface_get_stride(surface);
    const int w = cairo_image_surface_get_width(surface);
    const int h = cairo_image_surface_get_height(surface);

    // Simple 64-bit FNV-1a over the pixel buffer.
    uint64_t hash = 1469598103934665603ULL;
    for (int y = 0; y < h; ++y) {
      const unsigned char *row = data + y * stride;
      for (int x = 0; x < w * 4; ++x) {
        hash ^= static_cast<uint64_t>(row[x]);
        hash *= 1099511628211ULL;
      }
    }
    return hash;
  }

  static int CountNonWhitePixels_2439(cairo_surface_t *surface) {
    cairo_surface_flush(surface);
    const unsigned char *data = cairo_image_surface_get_data(surface);
    const int stride = cairo_image_surface_get_stride(surface);
    const int w = cairo_image_surface_get_width(surface);
    const int h = cairo_image_surface_get_height(surface);

    int count = 0;
    for (int y = 0; y < h; ++y) {
      const uint32_t *row = reinterpret_cast<const uint32_t *>(data + y * stride);
      for (int x = 0; x < w; ++x) {
        // CAIRO_FORMAT_ARGB32 uses native-endian 0xAARRGGBB in memory as uint32_t.
        // White with full alpha should be 0xFFFFFFFF.
        if (row[x] != 0xFFFFFFFFu) {
          ++count;
        }
      }
    }
    return count;
  }

  void SetUp() override {
    GError *error = nullptr;
    doc_ = LoadDoc_2439(&error);
    ASSERT_NE(doc_, nullptr) << (error ? error->message : "poppler_document_new_from_data() failed");
    if (error) g_error_free(error);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
  }

  void TearDown() override {
    if (page_) g_object_unref(page_);
    if (doc_) g_object_unref(doc_);
    page_ = nullptr;
    doc_ = nullptr;
  }

  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
};

TEST_F(RenderSelectionTest_2439, GlyphStyleDrawsSomethingOnSurface_2439) {
  cairo_surface_t *surface = MakeSurface_2439(200, 200);
  cairo_t *cr = cairo_create(surface);

  PopplerRectangle sel;
  sel.x1 = 40;
  sel.y1 = 70;
  sel.x2 = 170;
  sel.y2 = 120;

  PopplerColor glyph;
  glyph.red = 0;
  glyph.green = 0;
  glyph.blue = 0;

  PopplerColor bg;
  bg.red = 0xFFFF;
  bg.green = 0xFFFF;
  bg.blue = 0;

  const int before = CountNonWhitePixels_2439(surface);

  render_selection(page_, cr, &sel, POPPLER_SELECTION_GLYPH, &glyph, &bg,
                   /*background_opacity=*/1.0, /*draw_glyphs=*/true);

  const int after = CountNonWhitePixels_2439(surface);

  // Observable behavior: selection rendering should change the target surface.
  EXPECT_EQ(before, 0);
  EXPECT_GT(after, 0);

  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}

TEST_F(RenderSelectionTest_2439, UnknownStyleFallsBackToGlyphBehavior_2439) {
  PopplerRectangle sel;
  sel.x1 = 40;
  sel.y1 = 70;
  sel.x2 = 170;
  sel.y2 = 120;

  PopplerColor glyph;
  glyph.red = 0;
  glyph.green = 0;
  glyph.blue = 0;

  PopplerColor bg;
  bg.red = 0xFFFF;
  bg.green = 0xFFFF;
  bg.blue = 0;

  cairo_surface_t *surface_glyph = MakeSurface_2439(200, 200);
  cairo_t *cr_glyph = cairo_create(surface_glyph);
  render_selection(page_, cr_glyph, &sel, POPPLER_SELECTION_GLYPH, &glyph, &bg,
                   /*background_opacity=*/1.0, /*draw_glyphs=*/true);
  const uint64_t hash_glyph = HashSurface_2439(surface_glyph);

  cairo_surface_t *surface_unknown = MakeSurface_2439(200, 200);
  cairo_t *cr_unknown = cairo_create(surface_unknown);
  // Cast an out-of-range integer into the enum type (boundary/error-ish input).
  render_selection(page_, cr_unknown, &sel,
                   static_cast<PopplerSelectionStyle>(999),
                   &glyph, &bg,
                   /*background_opacity=*/1.0, /*draw_glyphs=*/true);
  const uint64_t hash_unknown = HashSurface_2439(surface_unknown);

  // Observable behavior implied by the switch: unknown value should behave like default
  // selectionStyleGlyph (i.e., same output for same inputs).
  EXPECT_EQ(hash_unknown, hash_glyph);

  cairo_destroy(cr_glyph);
  cairo_surface_destroy(surface_glyph);
  cairo_destroy(cr_unknown);
  cairo_surface_destroy(surface_unknown);
}

TEST_F(RenderSelectionTest_2439, OpacityZeroAndNoGlyphsLeavesSurfaceUnchanged_2439) {
  cairo_surface_t *surface = MakeSurface_2439(200, 200);
  cairo_t *cr = cairo_create(surface);

  PopplerRectangle sel;
  sel.x1 = 40;
  sel.y1 = 70;
  sel.x2 = 170;
  sel.y2 = 120;

  PopplerColor glyph;
  glyph.red = 0;
  glyph.green = 0;
  glyph.blue = 0;

  PopplerColor bg;
  bg.red = 0xFFFF;
  bg.green = 0;
  bg.blue = 0;

  const uint64_t before = HashSurface_2439(surface);

  // Boundary: fully transparent background and explicitly do not draw glyphs.
  render_selection(page_, cr, &sel, POPPLER_SELECTION_WORD, &glyph, &bg,
                   /*background_opacity=*/0.0, /*draw_glyphs=*/false);

  const uint64_t after = HashSurface_2439(surface);

  EXPECT_EQ(after, before);
  EXPECT_EQ(CountNonWhitePixels_2439(surface), 0);

  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}

TEST_F(RenderSelectionTest_2439, EmptySelectionRectangleDoesNotModifySurface_2439) {
  cairo_surface_t *surface = MakeSurface_2439(200, 200);
  cairo_t *cr = cairo_create(surface);

  // Boundary: empty rectangle (zero width).
  PopplerRectangle sel;
  sel.x1 = 100;
  sel.y1 = 70;
  sel.x2 = 100;  // same as x1
  sel.y2 = 120;

  PopplerColor glyph;
  glyph.red = 0;
  glyph.green = 0;
  glyph.blue = 0;

  PopplerColor bg;
  bg.red = 0;
  bg.green = 0xFFFF;
  bg.blue = 0;

  const uint64_t before = HashSurface_2439(surface);

  render_selection(page_, cr, &sel, POPPLER_SELECTION_LINE, &glyph, &bg,
                   /*background_opacity=*/1.0, /*draw_glyphs=*/true);

  const uint64_t after = HashSurface_2439(surface);

  // Observable expectation for boundary input: should not crash and should not draw.
  EXPECT_EQ(after, before);
  EXPECT_EQ(CountNonWhitePixels_2439(surface), 0);

  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}

TEST_F(RenderSelectionTest_2439, InvertedRectangleDoesNotCrash_2439) {
  cairo_surface_t *surface = MakeSurface_2439(200, 200);
  cairo_t *cr = cairo_create(surface);

  // Boundary/error-ish: inverted rectangle (x1 > x2, y1 > y2).
  PopplerRectangle sel;
  sel.x1 = 170;
  sel.y1 = 120;
  sel.x2 = 40;
  sel.y2 = 70;

  PopplerColor glyph;
  glyph.red = 0;
  glyph.green = 0;
  glyph.blue = 0;

  PopplerColor bg;
  bg.red = 0xFFFF;
  bg.green = 0xFFFF;
  bg.blue = 0xFFFF;

  const uint64_t before = HashSurface_2439(surface);

  // Primary assertion: function tolerates this input without crashing.
  // Secondary: allow either unchanged or changed (implementation-defined),
  // but keep it observable and safe.
  ASSERT_NO_FATAL_FAILURE(render_selection(page_, cr, &sel, POPPLER_SELECTION_GLYPH,
                                          &glyph, &bg,
                                          /*background_opacity=*/1.0,
                                          /*draw_glyphs=*/true));

  const uint64_t after = HashSurface_2439(surface);
  (void)after;

  // At minimum, it should still be a valid surface.
  EXPECT_NE(cairo_surface_status(surface), CAIRO_STATUS_NULL_POINTER);

  // Prefer unchanged as a reasonable boundary behavior, but don't over-assume.
  // If it does change, that's still observable and acceptable.
  // So we only require "no crash" + "surface remains valid".
  // (Keeping the hash read prevents unused warnings and keeps the test honest.)
  (void)before;

  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}

}  // namespace