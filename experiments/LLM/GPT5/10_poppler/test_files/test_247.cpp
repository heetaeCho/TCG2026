// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_splashbitmap_cmyk_encoder_247.cpp
//
// Unit tests for SplashBitmapCMYKEncoder::unfilteredRewind()
// Constraints respected:
// - Treat implementation as a black box
// - Only test observable behavior via public/virtual interface
// - Use gMock only to verify external interaction (virtual call forwarding)

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <type_traits>

#include "poppler/Stream.h"

// Splash headers are part of Poppler; we try to include them if present.
#if __has_include("splash/SplashBitmap.h")
#include "splash/SplashBitmap.h"
#endif
#if __has_include("splash/SplashTypes.h")
#include "splash/SplashTypes.h"
#endif

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Helper that tries to construct a minimal SplashBitmap with common Poppler signatures.
// If construction isn't possible in this build configuration, returns nullptr and tests will skip.
static std::unique_ptr<SplashBitmap> MakeSmallBitmapOrNull() {
#if __has_include("splash/SplashBitmap.h")
  // Many Poppler versions expose SplashColorMode in SplashTypes.h; if not present,
  // we still try constructors without the mode parameter.
#if __has_include("splash/SplashTypes.h")
  // Prefer CMYK if available.
  // (If your Poppler uses a different enumerator name, compilation will fail;
  // in that case, update this constant accordingly.)
  constexpr SplashColorMode kMode = splashModeCMYK;

  if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, SplashColorMode, bool, bool>) {
    return std::make_unique<SplashBitmap>(1, 1, 4, kMode, /*alphaA=*/false, /*topDownA=*/true);
  } else if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, SplashColorMode, bool>) {
    return std::make_unique<SplashBitmap>(1, 1, 4, kMode, /*alphaA=*/false);
  } else if constexpr (std::is_constructible_v<SplashBitmap, int, int, SplashColorMode, bool>) {
    return std::make_unique<SplashBitmap>(1, 1, kMode, /*alphaA=*/false);
  } else if constexpr (std::is_constructible_v<SplashBitmap, int, int, SplashColorMode>) {
    return std::make_unique<SplashBitmap>(1, 1, kMode);
  }
#endif  // splash/SplashTypes.h

  // Fallback attempts without a color-mode parameter (some builds may have these).
  if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, bool, bool>) {
    return std::make_unique<SplashBitmap>(1, 1, 4, /*alphaA=*/false, /*topDownA=*/true);
  } else if constexpr (std::is_constructible_v<SplashBitmap, int, int, int, bool>) {
    return std::make_unique<SplashBitmap>(1, 1, 4, /*alphaA=*/false);
  } else if constexpr (std::is_constructible_v<SplashBitmap, int, int>) {
    return std::make_unique<SplashBitmap>(1, 1);
  }

  return nullptr;
#else
  return nullptr;
#endif
}

// We verify that unfilteredRewind() forwards to the virtual rewind() on the dynamic type.
// This is an observable external interaction through the public virtual interface.
class MockSplashBitmapCMYKEncoder : public SplashBitmapCMYKEncoder {
 public:
  explicit MockSplashBitmapCMYKEncoder(SplashBitmap* bmp) : SplashBitmapCMYKEncoder(bmp) {}

  MOCK_METHOD(bool, rewind, (), (override));
};

class SplashBitmapCMYKEncoderTest_247 : public ::testing::Test {
 protected:
  void SetUp() override { bmp_ = MakeSmallBitmapOrNull(); }

  std::unique_ptr<SplashBitmap> bmp_;
};

}  // namespace

TEST_F(SplashBitmapCMYKEncoderTest_247, UnfilteredRewind_ForwardsToRewindAndPropagatesTrue_247) {
  if (!bmp_) {
    GTEST_SKIP() << "SplashBitmap could not be constructed in this build configuration.";
  }

  StrictMock<MockSplashBitmapCMYKEncoder> enc(bmp_.get());

  EXPECT_CALL(enc, rewind()).Times(1).WillOnce(Return(true));

  EXPECT_TRUE(enc.unfilteredRewind());
}

TEST_F(SplashBitmapCMYKEncoderTest_247, UnfilteredRewind_ForwardsToRewindAndPropagatesFalse_247) {
  if (!bmp_) {
    GTEST_SKIP() << "SplashBitmap could not be constructed in this build configuration.";
  }

  StrictMock<MockSplashBitmapCMYKEncoder> enc(bmp_.get());

  EXPECT_CALL(enc, rewind()).Times(1).WillOnce(Return(false));

  EXPECT_FALSE(enc.unfilteredRewind());
}

TEST_F(SplashBitmapCMYKEncoderTest_247, UnfilteredRewind_CanBeCalledMultipleTimes_247) {
  if (!bmp_) {
    GTEST_SKIP() << "SplashBitmap could not be constructed in this build configuration.";
  }

  StrictMock<MockSplashBitmapCMYKEncoder> enc(bmp_.get());

  EXPECT_CALL(enc, rewind())
      .Times(3)
      .WillOnce(Return(true))
      .WillOnce(Return(true))
      .WillOnce(Return(false));

  EXPECT_TRUE(enc.unfilteredRewind());
  EXPECT_TRUE(enc.unfilteredRewind());
  EXPECT_FALSE(enc.unfilteredRewind());
}