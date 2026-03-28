// SplashBitmapCMYKEncoder_getKind_242_test.cc
#include <gtest/gtest.h>

#include "Stream.h"

#include <type_traits>
#include <memory>

#if __has_include("splash/SplashBitmap.h")
#  include "splash/SplashBitmap.h"
#  define HAVE_SPLASH_BITMAP_H 1
#else
#  define HAVE_SPLASH_BITMAP_H 0
#endif

#if __has_include("splash/SplashTypes.h")
#  include "splash/SplashTypes.h"
#endif

namespace {

#if HAVE_SPLASH_BITMAP_H

// Try to construct a SplashBitmap using a few common Poppler constructor signatures.
// If none match, return nullptr and tests will be skipped.
std::unique_ptr<SplashBitmap> MakeSplashBitmapOrNull()
{
  // We try to avoid assuming one exact Poppler version by probing constructibility.
  // NOTE: We don't infer internal logic; this is only to create a valid collaborator object.
  constexpr int kW = 1;
  constexpr int kH = 1;
  constexpr int kRowPad = 1;

  // Try to pick a CMYK-ish mode if it exists; otherwise fall back to whatever compiles.
  // Many Poppler versions have SplashColorMode and values like splashModeCMYK8.
  // If those names don't exist, these blocks simply won't compile in that configuration,
  // so we keep the "mode" selection inside the same requires/constructible checks.

#if defined(SplashColorMode)
  // no-op: SplashColorMode is a type, but the macro check isn't reliable across versions
#endif

  // Helper lambdas to keep each attempt self-contained.
  auto try5 = []() -> std::unique_ptr<SplashBitmap> {
#if defined(splashModeCMYK8)
    using ModeT = decltype(splashModeCMYK8);
    if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, ModeT, bool>) {
      return std::make_unique<SplashBitmap>(kW, kH, kRowPad, splashModeCMYK8, false);
    }
    if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, ModeT, bool, bool>) {
      return std::make_unique<SplashBitmap>(kW, kH, kRowPad, splashModeCMYK8, false, true);
    }
#endif
    return nullptr;
  };

  auto tryRGB = []() -> std::unique_ptr<SplashBitmap> {
#if defined(splashModeRGB8)
    using ModeT = decltype(splashModeRGB8);
    if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, ModeT, bool>) {
      return std::make_unique<SplashBitmap>(kW, kH, kRowPad, splashModeRGB8, false);
    }
    if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, ModeT, bool, bool>) {
      return std::make_unique<SplashBitmap>(kW, kH, kRowPad, splashModeRGB8, false, true);
    }
#endif
    return nullptr;
  };

  auto bmp = try5();
  if (bmp) {
    return bmp;
  }
  bmp = tryRGB();
  if (bmp) {
    return bmp;
  }

  // Final attempt: try a very generic signature with an int "mode" if such ctor exists.
  if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, int, bool>) {
    return std::make_unique<SplashBitmap>(kW, kH, kRowPad, /*mode*/ 0, /*alpha*/ false);
  }
  if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, int, bool, bool>) {
    return std::make_unique<SplashBitmap>(kW, kH, kRowPad, /*mode*/ 0, /*alpha*/ false, /*topDown*/ true);
  }

  return nullptr;
}

#endif  // HAVE_SPLASH_BITMAP_H

class SplashBitmapCMYKEncoderTest_242 : public ::testing::Test {
protected:
  void SetUp() override
  {
#if HAVE_SPLASH_BITMAP_H
    bmp_ = MakeSplashBitmapOrNull();
    if (bmp_) {
      enc_ = std::make_unique<SplashBitmapCMYKEncoder>(bmp_.get());
    }
#endif
  }

#if HAVE_SPLASH_BITMAP_H
  std::unique_ptr<SplashBitmap> bmp_;
  std::unique_ptr<SplashBitmapCMYKEncoder> enc_;
#endif
};

}  // namespace

TEST_F(SplashBitmapCMYKEncoderTest_242, GetKindReturnsStrWeird_242)
{
#if !HAVE_SPLASH_BITMAP_H
  GTEST_SKIP() << "SplashBitmap.h not available in this build configuration.";
#else
  if (!enc_) {
    GTEST_SKIP() << "Could not construct SplashBitmap with available signatures; skipping.";
  }
  EXPECT_EQ(enc_->getKind(), strWeird);
#endif
}

TEST_F(SplashBitmapCMYKEncoderTest_242, GetKindWorksViaBasePointer_242)
{
#if !HAVE_SPLASH_BITMAP_H
  GTEST_SKIP() << "SplashBitmap.h not available in this build configuration.";
#else
  if (!enc_) {
    GTEST_SKIP() << "Could not construct SplashBitmap with available signatures; skipping.";
  }
  Stream *base = enc_.get();
  ASSERT_NE(base, nullptr);
  EXPECT_EQ(base->getKind(), strWeird);
#endif
}

TEST_F(SplashBitmapCMYKEncoderTest_242, GetKindIsCallableOnConstObject_242)
{
#if !HAVE_SPLASH_BITMAP_H
  GTEST_SKIP() << "SplashBitmap.h not available in this build configuration.";
#else
  if (!enc_) {
    GTEST_SKIP() << "Could not construct SplashBitmap with available signatures; skipping.";
  }
  const SplashBitmapCMYKEncoder &cenc = *enc_;
  EXPECT_EQ(cenc.getKind(), strWeird);
#endif
}