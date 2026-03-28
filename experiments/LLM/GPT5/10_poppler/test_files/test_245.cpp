// ============================================================================
// Unit tests for SplashBitmapCMYKEncoder (TEST_ID = 245)
// File: SplashBitmapCMYKEncoder_test_245.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

// Poppler headers (as referenced by the prompt)
#include "poppler/Stream.h"

// SplashBitmap lives in poppler's splash/ in typical layouts.
#if __has_include("splash/SplashBitmap.h")
#include "splash/SplashBitmap.h"
#elif __has_include(<splash/SplashBitmap.h>)
#include <splash/SplashBitmap.h>
#endif

namespace {

// ---- Compile-time helpers (no behavioral assumptions) -----------------------

template <typename T>
constexpr bool HasRewindV = requires(T t) {
  { t.rewind() } -> std::convertible_to<bool>;
};

template <typename T>
constexpr bool HasGetCharV = requires(T t) {
  { t.getChar() } -> std::convertible_to<int>;
};

template <typename T>
constexpr bool HasLookCharV = requires(T t) {
  { t.lookChar() } -> std::convertible_to<int>;
};

// ---- Test fixture -----------------------------------------------------------

class SplashBitmapCMYKEncoderTest_245 : public ::testing::Test {
protected:
  // Try to construct SplashBitmap with a few commonly-seen constructor signatures.
  // This is just to obtain a valid pointer for the encoder; tests do not assume
  // anything about bitmap internals.
  static std::unique_ptr<SplashBitmap> MakeBitmapOrNull(int w, int h) {
#if defined(SplashBitmap_h) || __has_include("splash/SplashBitmap.h") || __has_include(<splash/SplashBitmap.h>)
    // Many builds expose SplashColorMode in included headers; we avoid relying on
    // a specific CMYK enumerator name by using static_cast.
    using SCM = decltype(static_cast<SplashColorMode>(0));

    if constexpr (std::is_constructible_v<SplashBitmap, int, int, SCM, bool>) {
      return std::make_unique<SplashBitmap>(w, h, static_cast<SplashColorMode>(0), false);
    } else if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, SCM, bool>) {
      // Some variants take rowPad/rowAlign as an int.
      return std::make_unique<SplashBitmap>(w, h, 1, static_cast<SplashColorMode>(0), false);
    } else if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, SCM, bool, bool>) {
      // Some variants add a "topDown" / "separated" boolean; keep defaults simple.
      return std::make_unique<SplashBitmap>(w, h, 1, static_cast<SplashColorMode>(0), false, false);
    } else {
      // Unknown constructor signature in this build.
      return nullptr;
    }
#else
    (void)w;
    (void)h;
    return nullptr;
#endif
  }

  static bool CanMakeBitmap() {
    auto bmp = MakeBitmapOrNull(1, 1);
    return bmp != nullptr;
  }
};

} // namespace

// ----------------------------------------------------------------------------
// Tests (behavior is treated as a black box; only observable result asserted)
// ----------------------------------------------------------------------------

TEST_F(SplashBitmapCMYKEncoderTest_245, IsEncoderReturnsFalse_245) {
  if (!SplashBitmapCMYKEncoderTest_245::CanMakeBitmap()) {
    GTEST_SKIP() << "SplashBitmap constructor signature not available in this build.";
  }

  auto bmp = SplashBitmapCMYKEncoderTest_245::MakeBitmapOrNull(1, 1);
  ASSERT_NE(bmp, nullptr);

  SplashBitmapCMYKEncoder enc(bmp.get());
  EXPECT_FALSE(enc.isEncoder());
}

TEST_F(SplashBitmapCMYKEncoderTest_245, IsEncoderCallableOnConstObject_245) {
  if (!SplashBitmapCMYKEncoderTest_245::CanMakeBitmap()) {
    GTEST_SKIP() << "SplashBitmap constructor signature not available in this build.";
  }

  auto bmp = SplashBitmapCMYKEncoderTest_245::MakeBitmapOrNull(1, 1);
  ASSERT_NE(bmp, nullptr);

  const SplashBitmapCMYKEncoder enc(bmp.get());
  EXPECT_FALSE(enc.isEncoder());
}

TEST_F(SplashBitmapCMYKEncoderTest_245, IsEncoderRemainsFalseAfterOptionalOperations_245) {
  if (!SplashBitmapCMYKEncoderTest_245::CanMakeBitmap()) {
    GTEST_SKIP() << "SplashBitmap constructor signature not available in this build.";
  }

  auto bmp = SplashBitmapCMYKEncoderTest_245::MakeBitmapOrNull(1, 1);
  ASSERT_NE(bmp, nullptr);

  SplashBitmapCMYKEncoder enc(bmp.get());

  // These calls are guarded by compile-time detection to avoid assuming methods exist.
  if constexpr (HasRewindV<SplashBitmapCMYKEncoder>) {
    (void)enc.rewind();
  }
  if constexpr (HasLookCharV<SplashBitmapCMYKEncoder>) {
    (void)enc.lookChar();
  }
  if constexpr (HasGetCharV<SplashBitmapCMYKEncoder>) {
    (void)enc.getChar();
  }

  EXPECT_FALSE(enc.isEncoder());
}

TEST_F(SplashBitmapCMYKEncoderTest_245, IsEncoderFalseWithBoundarySizedBitmapIfConstructible_245) {
  if (!SplashBitmapCMYKEncoderTest_245::CanMakeBitmap()) {
    GTEST_SKIP() << "SplashBitmap constructor signature not available in this build.";
  }

  // Boundary condition: try zero-sized bitmap if the SplashBitmap constructor allows it.
  // We do not assume it must succeed; if construction fails/throws, we skip.
  std::unique_ptr<SplashBitmap> bmp;
  try {
    bmp = SplashBitmapCMYKEncoderTest_245::MakeBitmapOrNull(0, 0);
  } catch (...) {
    GTEST_SKIP() << "SplashBitmap(0,0,...) construction threw; boundary not supported in this build.";
  }

  if (!bmp) {
    GTEST_SKIP() << "SplashBitmap(0,0,...) not constructible in this build.";
  }

  SplashBitmapCMYKEncoder enc(bmp.get());
  EXPECT_FALSE(enc.isEncoder());
}