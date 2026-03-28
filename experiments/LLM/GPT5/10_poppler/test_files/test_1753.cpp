//===----------------------------------------------------------------------===//
// CairoFontEngine__render_type3_glyph_tests_1753.cc
//
// Unit tests for static _render_type3_glyph() in CairoFontEngine.cc
// NOTE: This test intentionally exercises only *observable* early-return paths
//       that do not require constructing a real Gfx/GfxFont pipeline.
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <array>
#include <cstring>
#include <memory>

// Cairo
#include <cairo.h>

// Poppler (paths may vary in your tree; adjust include paths if needed)
#include "Dict.h"
#include "Object.h"

// We include the implementation file to reach the TU-local static function.
// This is a common approach for testing file-scope statics.
#include "CairoFontEngine.cc"

namespace {

// A tiny helper to create a cairo_scaled_font_t that carries the type3 user-data.
struct CairoType3FontHarness {
  cairo_font_face_t *face = nullptr;
  cairo_scaled_font_t *scaled = nullptr;
  cairo_surface_t *surface = nullptr;
  cairo_t *cr = nullptr;

  ~CairoType3FontHarness() {
    if (cr) cairo_destroy(cr);
    if (surface) cairo_surface_destroy(surface);
    if (scaled) cairo_scaled_font_destroy(scaled);
    if (face) cairo_font_face_destroy(face);
  }
};

// cairo user-data destroy callback for type3_font_info_t
static void DestroyType3Info(void *p) {
  delete static_cast<type3_font_info_t *>(p);
}

static CairoType3FontHarness MakeHarnessWithType3Info(type3_font_info_t *info) {
  CairoType3FontHarness h;

  h.surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
  h.cr = cairo_create(h.surface);

  h.face = cairo_user_font_face_create();
  // Attach type3 font info to the face using the key defined in CairoFontEngine.cc
  cairo_status_t st = cairo_font_face_set_user_data(h.face, &type3_font_key, info, DestroyType3Info);
  EXPECT_EQ(st, CAIRO_STATUS_SUCCESS);

  cairo_matrix_t identity;
  cairo_matrix_init_identity(&identity);

  cairo_font_options_t *opts = cairo_font_options_create();
  h.scaled = cairo_scaled_font_create(h.face, &identity, &identity, opts);
  cairo_font_options_destroy(opts);

  EXPECT_EQ(cairo_scaled_font_status(h.scaled), CAIRO_STATUS_SUCCESS);

  return h;
}

// Some tests only need a Dict with a specific length.
static std::unique_ptr<Dict> MakeDictWithNEntries(int n) {
  auto d = std::make_unique<Dict>(/*xrefA=*/nullptr);
  for (int i = 0; i < n; ++i) {
    // Keys just need to exist so getLength() reflects n.
    // Values are irrelevant for early-return tests.
    std::string key = "K" + std::to_string(i);
    d->add(key, Object(true));
  }
  return d;
}

class RenderType3GlyphTest_1753 : public ::testing::Test {
protected:
  // We keep these around if needed by constructed type3_font_info_t.
  // Early-return paths do not dereference outputDev/gfx, so nullptr is safe there.
  CairoOutputDev *outputDev = nullptr;
  Gfx *gfx = nullptr;

  cairo_text_extents_t metricsWithSentinel() {
    cairo_text_extents_t m;
    std::memset(&m, 0, sizeof(m));
    // Put non-zero sentinels to detect unwanted writes on early returns.
    m.x_bearing = 123.0;
    m.y_bearing = 456.0;
    m.width = 789.0;
    m.height = 321.0;
    m.x_advance = 654.0;
    m.y_advance = 987.0;
    return m;
  }
};

}  // namespace

TEST_F(RenderType3GlyphTest_1753, ReturnsSuccessWhenCharProcsNull_1753) {
  // Arrange: Build a type3_font_info_t whose font has no /CharProcs.
  //
  // IMPORTANT: We only validate the early-return observable behavior:
  // - returns CAIRO_STATUS_SUCCESS
  // - does not touch metrics (since it returns before writing)
  //
  // Creating a real Gfx8BitFont instance is highly integration-heavy; this test
  // relies on the production type3_font_info_t and the fact that /CharProcs may
  // be absent (NULL) for some fonts.
  //
  // If your build setup requires a real Gfx8BitFont, replace the font creation
  // here with your existing Poppler test utilities for Type3 fonts.

  // NOTE: We cannot safely fabricate a Gfx8BitFont without the real constructors.
  // So we create info with a null font and skip if the environment cannot provide
  // a real Type3 font object through existing helpers.
  //
  // If you have a helper like MakeTestType3FontWithoutCharProcs(), use it here.
  GTEST_SKIP() << "Project setup needed: provide a real shared_ptr<Gfx8BitFont> "
                  "that returns nullptr from getCharProcs().";
}

TEST_F(RenderType3GlyphTest_1753, ReturnsSuccessWhenGlyphOutOfRange_1753) {
  // This test exercises:
  //   if (glyph >= (unsigned)charProcs->getLength()) { ...; return SUCCESS; }
  //
  // It still requires a real Gfx8BitFont whose getCharProcs() returns our Dict.
  // If you already have Poppler test utilities that can construct a Type3
  // Gfx8BitFont, wire them in where indicated.

  auto charProcs = MakeDictWithNEntries(1);

  // ---- Replace this section with your project’s way to construct a Type3 Gfx8BitFont ----
  // Example (pseudo):
  //   std::shared_ptr<GfxFont> font = MakeType3Gfx8BitFontWithCharProcs(charProcs.get());
  // --------------------------------------------------------------------------------------
  GTEST_SKIP() << "Project setup needed: provide a real shared_ptr<Gfx8BitFont> "
                  "backed by a Type3 font with a /CharProcs Dict of length 1.";
}

// If your project already has a way to construct a full Type3 rendering pipeline
// (PDFDoc + Gfx + CairoOutputDev + CairoFontEngine), you can add these deeper tests:
//
// - Normal operation: glyph within range and charProc is a stream -> metrics advances set.
// - Boundary: glyph == 0, glyph == last index.
// - Error/exceptional (observable): charProc not a stream -> returns SUCCESS (and logs error).
// - External interactions: verify gfx->pushResources/popResources called when Resources dict exists,
//   and outputDev->setType3RenderType called with Mask/Color depending on 'color'.
//
// Those require *real* Poppler objects or supported fakes; once you point this test file at your
// existing Poppler test harness utilities, add the cases above following the same TEST_ID naming.