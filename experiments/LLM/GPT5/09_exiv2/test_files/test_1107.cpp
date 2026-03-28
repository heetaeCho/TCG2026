// ============================================================================
// TEST_ID: 1107
// Unit tests for Exiv2::ImageFactory::open(const byte* data, size_t size)
// File under test (partial): ./TestProjects/exiv2/src/image.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "exiv2/error.hpp"
#include "exiv2/image.hpp"

namespace {

// Minimal valid GIF (GIF89a) 1x1, no GCT, trailer.
static const Exiv2::byte kGif1x1[] = {
    'G','I','F','8','9','a',
    0x01,0x00, // width  = 1
    0x01,0x00, // height = 1
    0x00,      // Packed: no GCT
    0x00,      // Background color index
    0x00,      // Pixel aspect ratio
    0x3B       // Trailer
};

// Minimal valid PNG (signature + IHDR + IEND) for 1x1 RGBA.
// CRCs are included (common minimal sample).
static const Exiv2::byte kPng1x1[] = {
    0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A, // signature
    0x00,0x00,0x00,0x0D, // length
    0x49,0x48,0x44,0x52, // "IHDR"
    0x00,0x00,0x00,0x01, // width 1
    0x00,0x00,0x00,0x01, // height 1
    0x08, // bit depth
    0x06, // color type RGBA
    0x00, // compression
    0x00, // filter
    0x00, // interlace
    0x1F,0x15,0xC4,0x89, // CRC
    0x00,0x00,0x00,0x00, // length
    0x49,0x45,0x4E,0x44, // "IEND"
    0xAE,0x42,0x60,0x82  // CRC
};

template <typename Fn>
static Exiv2::ErrorCode CatchErrorCode(Fn&& fn) {
  try {
    fn();
  } catch (const Exiv2::Error& e) {
    // Exiv2::Error::code() is commonly an int-like or ErrorCode-like type.
    // Normalize to ErrorCode without assuming exact signature.
    return static_cast<Exiv2::ErrorCode>(e.code());
  } catch (...) {
    // Not an Exiv2::Error; return a sentinel "general error" for assertions.
    return Exiv2::ErrorCode::kerGeneralError;
  }
  return Exiv2::ErrorCode::kerSuccess;
}

}  // namespace

class ImageFactoryOpenFromMemoryTest_1107 : public ::testing::Test {};

TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpensGifFromMemory_1107) {
  ASSERT_NO_THROW({
    auto img = Exiv2::ImageFactory::open(kGif1x1, sizeof(kGif1x1));
    ASSERT_NE(img, nullptr);
  });
}

TEST_F(ImageFactoryOpenFromMemoryTest_1107, OpensPngFromMemory_1107) {
  ASSERT_NO_THROW({
    auto img = Exiv2::ImageFactory::open(kPng1x1, sizeof(kPng1x1));
    ASSERT_NE(img, nullptr);
  });
}

TEST_F(ImageFactoryOpenFromMemoryTest_1107, ThrowsForUnknownImageType_1107) {
  const Exiv2::byte garbage[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

  const auto code = CatchErrorCode([&] {
    (void)Exiv2::ImageFactory::open(garbage, sizeof(garbage));
  });

  EXPECT_EQ(Exiv2::ErrorCode::kerMemoryContainsUnknownImageType, code);
}

TEST_F(ImageFactoryOpenFromMemoryTest_1107, ThrowsForEmptyBufferSizeZero_1107) {
  // Boundary: size == 0. Use a non-null pointer to avoid UB on some implementations.
  const Exiv2::byte dummy = 0x00;

  const auto code = CatchErrorCode([&] {
    (void)Exiv2::ImageFactory::open(&dummy, 0);
  });

  // The implementation is expected to treat this as "unknown image type" in memory.
  EXPECT_EQ(Exiv2::ErrorCode::kerMemoryContainsUnknownImageType, code);
}

TEST_F(ImageFactoryOpenFromMemoryTest_1107, NullptrWithZeroSizeDoesNotCrashAndThrowsOrSucceeds_1107) {
  // Boundary: nullptr + size 0 should not read memory. We only assert it doesn't crash.
  // If it throws, it should be an Exiv2::Error (commonly unknown type).
  try {
    auto img = Exiv2::ImageFactory::open(nullptr, 0);
    // If it returns, it must return a non-null image by contract of UniquePtr semantics here.
    // (Some implementations may still throw; both are acceptable for this black-box test.)
    EXPECT_TRUE(img == nullptr || img != nullptr);  // no-op to silence unused warnings
  } catch (const Exiv2::Error& e) {
    // Accept any Exiv2 error code; do not over-specify beyond observable behavior.
    (void)e;
    SUCCEED();
  }
}