// File: CairoFontEngine_init_type3_glyph_test_1752.cc
#include <gtest/gtest.h>

#include <cairo.h>

#include <array>
#include <cmath>
#include <memory>
#include <type_traits>

// Expose the TU-local static function for testing by including the .cc.
// This does not re-implement any logic; it compiles the production code into this test TU.
#define static /* expose internal linkage for tests */
#include "./TestProjects/poppler/poppler/CairoFontEngine.cc"
#undef static

namespace {

struct CairoObjs {
  cairo_font_face_t *face = nullptr;
  cairo_scaled_font_t *scaled = nullptr;
  cairo_font_options_t *opts = nullptr;

  ~CairoObjs() {
    if (scaled) {
      cairo_scaled_font_destroy(scaled);
    }
    if (face) {
      cairo_font_face_destroy(face);
    }
    if (opts) {
      cairo_font_options_destroy(opts);
    }
  }
};

inline bool NearlyEqual(double a, double b, double eps = 1e-9) {
  return std::fabs(a - b) <= eps;
}

// Creates a cairo_scaled_font_t whose font-face has type3_font_info_t attached as user-data.
// Returns nullptr scaled font on failure (caller can ASSERT/skip accordingly).
template <typename FontT>
CairoObjs MakeScaledFontWithType3Info(FontT *font_obj, type3_font_info_t **out_info) {
  CairoObjs o;

  o.face = cairo_toy_font_face_create("Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  if (!o.face || cairo_font_face_status(o.face) != CAIRO_STATUS_SUCCESS) {
    return o;
  }

  // Allocate the info object that _init_type3_glyph expects to find via user-data.
  auto *info = new type3_font_info_t();
  // The field name/type is taken from the compiled production code.
  info->font = font_obj;

  // Attach to font face; on failure, clean up.
  cairo_status_t st = cairo_font_face_set_user_data(o.face, &type3_font_key, info,
                                                   [](void *p) { delete static_cast<type3_font_info_t *>(p); });
  if (st != CAIRO_STATUS_SUCCESS) {
    delete info;
    return o;
  }

  cairo_matrix_t font_matrix;
  cairo_matrix_t ctm;
  cairo_matrix_init_identity(&font_matrix);
  cairo_matrix_init_identity(&ctm);

  o.opts = cairo_font_options_create();
  if (!o.opts || cairo_font_options_status(o.opts) != CAIRO_STATUS_SUCCESS) {
    return o;
  }

  o.scaled = cairo_scaled_font_create(o.face, &font_matrix, &ctm, o.opts);
  if (!o.scaled || cairo_scaled_font_status(o.scaled) != CAIRO_STATUS_SUCCESS) {
    return o;
  }

  if (out_info) {
    *out_info = info;
  }
  return o;
}

} // namespace

// ------------------------------
// Tests (TEST_ID = 1752)
// ------------------------------

TEST(CairoFontEngineInitType3GlyphTest_1752, ComputesExtentsFromFontBBox_Normal_1752) {
  using InfoT = type3_font_info_t;
  using FontPtrT = decltype(std::declval<InfoT>().font);
  using FontT = std::remove_pointer_t<FontPtrT>;

  // This test requires that the font object can be constructed from a bbox.
  // If the concrete type does not support such construction, we skip (rather than guessing internals).
  const std::array<double, 4> bbox{1.0, 2.0, 10.0, 20.0}; // [?, x1, x2, y2] per usage in code
  if constexpr (std::is_constructible_v<FontT, std::array<double, 4>>) {
    auto font = std::make_unique<FontT>(bbox);

    type3_font_info_t *info = nullptr;
    CairoObjs o = MakeScaledFontWithType3Info<FontT>(font.get(), &info);
    ASSERT_NE(o.scaled, nullptr);

    cairo_font_extents_t extents{};
    cairo_status_t st = _init_type3_glyph(o.scaled, nullptr, &extents);
    EXPECT_EQ(st, CAIRO_STATUS_SUCCESS);

    // Observable relationships defined by the function:
    // ascent = mat[3], descent = -mat[3], height = ascent + descent, max_x_advance = mat[2] - mat[1], max_y_advance = 0
    EXPECT_TRUE(NearlyEqual(extents.ascent, bbox[3]));
    EXPECT_TRUE(NearlyEqual(extents.descent, -bbox[3]));
    EXPECT_TRUE(NearlyEqual(extents.height, extents.ascent + extents.descent));
    EXPECT_TRUE(NearlyEqual(extents.max_x_advance, bbox[2] - bbox[1]));
    EXPECT_TRUE(NearlyEqual(extents.max_y_advance, 0.0));
  } else if constexpr (std::is_constructible_v<FontT, const std::array<double, 4> &>) {
    auto font = std::make_unique<FontT>(bbox);

    type3_font_info_t *info = nullptr;
    CairoObjs o = MakeScaledFontWithType3Info<FontT>(font.get(), &info);
    ASSERT_NE(o.scaled, nullptr);

    cairo_font_extents_t extents{};
    cairo_status_t st = _init_type3_glyph(o.scaled, nullptr, &extents);
    EXPECT_EQ(st, CAIRO_STATUS_SUCCESS);

    EXPECT_TRUE(NearlyEqual(extents.ascent, bbox[3]));
    EXPECT_TRUE(NearlyEqual(extents.descent, -bbox[3]));
    EXPECT_TRUE(NearlyEqual(extents.height, extents.ascent + extents.descent));
    EXPECT_TRUE(NearlyEqual(extents.max_x_advance, bbox[2] - bbox[1]));
    EXPECT_TRUE(NearlyEqual(extents.max_y_advance, 0.0));
  } else {
    GTEST_SKIP() << "Font type used by type3_font_info_t is not constructible from a bbox in this build.";
  }
}

TEST(CairoFontEngineInitType3GlyphTest_1752, Boundary_ZeroBBoxProducesZeroExtents_1752) {
  using InfoT = type3_font_info_t;
  using FontPtrT = decltype(std::declval<InfoT>().font);
  using FontT = std::remove_pointer_t<FontPtrT>;

  const std::array<double, 4> bbox{0.0, 0.0, 0.0, 0.0};
  if constexpr (std::is_constructible_v<FontT, std::array<double, 4>> ||
                std::is_constructible_v<FontT, const std::array<double, 4> &>) {
    std::unique_ptr<FontT> font =
        (std::is_constructible_v<FontT, std::array<double, 4>>)
            ? std::make_unique<FontT>(bbox)
            : std::make_unique<FontT>(bbox);

    type3_font_info_t *info = nullptr;
    CairoObjs o = MakeScaledFontWithType3Info<FontT>(font.get(), &info);
    ASSERT_NE(o.scaled, nullptr);

    cairo_font_extents_t extents{};
    cairo_status_t st = _init_type3_glyph(o.scaled, nullptr, &extents);
    EXPECT_EQ(st, CAIRO_STATUS_SUCCESS);

    EXPECT_TRUE(NearlyEqual(extents.ascent, 0.0));
    EXPECT_TRUE(NearlyEqual(extents.descent, -0.0));
    EXPECT_TRUE(NearlyEqual(extents.height, 0.0));
    EXPECT_TRUE(NearlyEqual(extents.max_x_advance, 0.0));
    EXPECT_TRUE(NearlyEqual(extents.max_y_advance, 0.0));
  } else {
    GTEST_SKIP() << "Font type used by type3_font_info_t is not constructible from a bbox in this build.";
  }
}

TEST(CairoFontEngineInitType3GlyphTest_1752, Boundary_NegativeY2HandledAsSpecified_1752) {
  using InfoT = type3_font_info_t;
  using FontPtrT = decltype(std::declval<InfoT>().font);
  using FontT = std::remove_pointer_t<FontPtrT>;

  // y2 negative => ascent negative, descent positive, height still ascent+descent (may become 0 if exact negation).
  const std::array<double, 4> bbox{0.0, 1.0, 5.0, -7.0};
  if constexpr (std::is_constructible_v<FontT, std::array<double, 4>> ||
                std::is_constructible_v<FontT, const std::array<double, 4> &>) {
    std::unique_ptr<FontT> font =
        (std::is_constructible_v<FontT, std::array<double, 4>>)
            ? std::make_unique<FontT>(bbox)
            : std::make_unique<FontT>(bbox);

    type3_font_info_t *info = nullptr;
    CairoObjs o = MakeScaledFontWithType3Info<FontT>(font.get(), &info);
    ASSERT_NE(o.scaled, nullptr);

    cairo_font_extents_t extents{};
    cairo_status_t st = _init_type3_glyph(o.scaled, nullptr, &extents);
    EXPECT_EQ(st, CAIRO_STATUS_SUCCESS);

    EXPECT_TRUE(NearlyEqual(extents.ascent, bbox[3]));     // -7
    EXPECT_TRUE(NearlyEqual(extents.descent, -bbox[3]));   // +7
    EXPECT_TRUE(NearlyEqual(extents.height, extents.ascent + extents.descent));
    EXPECT_TRUE(NearlyEqual(extents.max_x_advance, bbox[2] - bbox[1])); // 4
    EXPECT_TRUE(NearlyEqual(extents.max_y_advance, 0.0));
  } else {
    GTEST_SKIP() << "Font type used by type3_font_info_t is not constructible from a bbox in this build.";
  }
}

TEST(CairoFontEngineInitType3GlyphTest_1752, ErrorCase_NullExtentsPointerDeath_1752) {
  // Observable exceptional behavior: passing nullptr extents will dereference it in the function.
  // Use a death test to verify it fails fast rather than silently succeeding.
  // (Only run when death tests are supported.)
#if GTEST_HAS_DEATH_TEST
  using InfoT = type3_font_info_t;
  using FontPtrT = decltype(std::declval<InfoT>().font);
  using FontT = std::remove_pointer_t<FontPtrT>;

  const std::array<double, 4> bbox{0.0, 0.0, 1.0, 1.0};
  if constexpr (std::is_constructible_v<FontT, std::array<double, 4>> ||
                std::is_constructible_v<FontT, const std::array<double, 4> &>) {
    std::unique_ptr<FontT> font =
        (std::is_constructible_v<FontT, std::array<double, 4>>)
            ? std::make_unique<FontT>(bbox)
            : std::make_unique<FontT>(bbox);

    type3_font_info_t *info = nullptr;
    CairoObjs o = MakeScaledFontWithType3Info<FontT>(font.get(), &info);
    ASSERT_NE(o.scaled, nullptr);

    EXPECT_DEATH(
        {
          // NOLINTNEXTLINE: intentionally passing nullptr to validate crash behavior.
          (void)_init_type3_glyph(o.scaled, nullptr, nullptr);
        },
        "");
  } else {
    GTEST_SKIP() << "Font type used by type3_font_info_t is not constructible from a bbox in this build.";
  }
#else
  GTEST_SKIP() << "Death tests are not supported in this configuration.";
#endif
}