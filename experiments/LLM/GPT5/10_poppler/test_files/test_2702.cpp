// File: html_string_getfont_test_2702.cc
#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

// Poppler headers (expected to exist in the codebase build environment)
#include "HtmlOutputDev.h"
#include "HtmlFonts.h"

// GfxState is part of poppler core; include path may vary by build.
// Most poppler trees provide "GfxState.h".
#include "GfxState.h"

namespace {

// Compile-time helper: try to create a GfxState using whichever constructor exists
// in the target Poppler version, without assuming internal behavior.
template <typename... Args>
static constexpr bool kGfxStateConstructible =
    std::is_constructible<GfxState, Args...>::value;

static std::unique_ptr<GfxState> MakeAnyGfxState_2702() {
  // Try a few common constructor shapes seen across Poppler/Xpdf derivatives.

  // (x1, y1, x2, y2, rotate, upsideDown)
  if constexpr (kGfxStateConstructible<double, double, double, double, int, bool>) {
    return std::make_unique<GfxState>(0.0, 0.0, 612.0, 792.0, 0, false);
  }

  // (x1, y1, x2, y2, rotate, upsideDown, /*something*/)
  if constexpr (kGfxStateConstructible<double, double, double, double, int, bool, bool>) {
    return std::make_unique<GfxState>(0.0, 0.0, 612.0, 792.0, 0, false, false);
  }

  // (hDPI, vDPI, x1, y1, x2, y2, rotate, upsideDown)
  if constexpr (kGfxStateConstructible<double, double, double, double, double, double, int, bool>) {
    return std::make_unique<GfxState>(72.0, 72.0, 0.0, 0.0, 612.0, 792.0, 0, false);
  }

  // If none match, return null and tests will skip.
  return nullptr;
}

class HtmlStringGetFontTest_2702 : public ::testing::Test {
 protected:
  std::unique_ptr<GfxState> state_;

  void SetUp() override { state_ = MakeAnyGfxState_2702(); }
};

}  // namespace

TEST_F(HtmlStringGetFontTest_2702, ConstructorMayRegisterFontAndGetFontReturnsMemberOfAccumulator_2702) {
  if (!state_) {
    GTEST_SKIP() << "No compatible GfxState constructor detected in this Poppler version.";
  }

  HtmlFontAccu fonts;
  HtmlString s(state_.get(), /*fontSize=*/12.0, &fonts);

  // getFont() should return a reference to some font stored in the accumulator.
  // We do not assume which index it is (black-box), only that it corresponds
  // to an element returned by HtmlFontAccu::Get for some valid i.
  const HtmlFont& f = s.getFont();

  ASSERT_GE(fonts.size(), 1) << "Expected at least one font registered after construction.";

  bool matched = false;
  for (int i = 0; i < fonts.size(); ++i) {
    const HtmlFont* pi = fonts.Get(i);
    if (pi && (&f == pi)) {
      matched = true;
      break;
    }
  }
  EXPECT_TRUE(matched) << "getFont() did not match any HtmlFontAccu::Get(i) pointer.";
}

TEST_F(HtmlStringGetFontTest_2702, GetFontStaysWithinAccumulatorAfterAddCharEndString_2702) {
  if (!state_) {
    GTEST_SKIP() << "No compatible GfxState constructor detected in this Poppler version.";
  }

  HtmlFontAccu fonts;
  HtmlString s(state_.get(), /*fontSize=*/10.0, &fonts);

  // Exercise public mutators (black-box). We don't assume how they affect fontpos.
  s.addChar(state_.get(), /*x=*/0.0, /*y=*/0.0, /*dx=*/1.0, /*dy=*/0.0, /*u=*/static_cast<Unicode>('A'));
  s.endString();

  const HtmlFont& f = s.getFont();

  ASSERT_GE(fonts.size(), 1);

  bool matched = false;
  for (int i = 0; i < fonts.size(); ++i) {
    const HtmlFont* pi = fonts.Get(i);
    if (pi && (&f == pi)) {
      matched = true;
      break;
    }
  }
  EXPECT_TRUE(matched);
}

TEST_F(HtmlStringGetFontTest_2702, GetFontWithNullFontsPointerDies_2702) {
  if (!state_) {
    GTEST_SKIP() << "No compatible GfxState constructor detected in this Poppler version.";
  }

  // Depending on implementation, the constructor may dereference fonts immediately
  // (e.g., to add/register a font), or getFont() may be the first dereference.
  // Accept either as a valid observable "error case" via a death test.

  EXPECT_DEATH(
      {
        HtmlString s(state_.get(), /*fontSize=*/12.0, /*fonts=*/nullptr);
        (void)s.getFont();
      },
      "");
}

TEST_F(HtmlStringGetFontTest_2702, GetFontWithEmptyAccumulatorDiesOrAsserts_2702) {
  if (!state_) {
    GTEST_SKIP() << "No compatible GfxState constructor detected in this Poppler version.";
  }

  // Boundary/error case: provide an accumulator that (by black-box behavior) might
  // not contain an entry for fontpos; dereference of fonts->Get(fontpos) could fail.
  // We cannot force internal fontpos, but we can at least exercise a scenario where
  // accumulator is not pre-populated by tests themselves.
  HtmlFontAccu fonts;

  // If constructor ensures a font is always added, this won't be a death case.
  // In that situation, we still have coverage via the normal tests.
  // So: only assert death if size remains 0 after construction.
  HtmlString s(state_.get(), /*fontSize=*/12.0, &fonts);

  if (fonts.size() == 0) {
    EXPECT_DEATH({ (void)s.getFont(); }, "");
  } else {
    // Otherwise, just ensure it returns a valid member (no assumptions about which one).
    const HtmlFont& f = s.getFont();
    bool matched = false;
    for (int i = 0; i < fonts.size(); ++i) {
      const HtmlFont* pi = fonts.Get(i);
      if (pi && (&f == pi)) {
        matched = true;
        break;
      }
    }
    EXPECT_TRUE(matched);
  }
}