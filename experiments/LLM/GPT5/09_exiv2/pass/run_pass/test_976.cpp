// =================================================================================================
// TEST_ID: 976
// Unit tests for: Exiv2::newPngInstance(BasicIo::UniquePtr io, bool create)
// File under test: ./TestProjects/exiv2/src/pngimage.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/pngimage.hpp>

#include <cstdint>
#include <memory>
#include <vector>

namespace {

class PngImageFactoryTest_976 : public ::testing::Test {
 protected:
  // A tiny, valid 1x1 PNG (commonly used minimal PNG).
  static std::vector<uint8_t> MinimalValidPngBytes() {
    return {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,  // PNG signature
        0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,  // IHDR chunk
        0x00, 0x00, 0x00, 0x01,                          // width  = 1
        0x00, 0x00, 0x00, 0x01,                          // height = 1
        0x08,                                            // bit depth
        0x06,                                            // color type (RGBA)
        0x00,                                            // compression
        0x00,                                            // filter
        0x00,                                            // interlace
        0x1F, 0x15, 0xC4, 0x89,                          // CRC
        0x00, 0x00, 0x00, 0x0A, 0x49, 0x44, 0x41, 0x54,  // IDAT chunk
        0x78, 0x9C, 0x63, 0x00, 0x01, 0x00, 0x00, 0x05, 0x00, 0x01,
        0x0D, 0x0A, 0x2D, 0xB4,  // CRC
        0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44,  // IEND chunk
        0xAE, 0x42, 0x60, 0x82                                   // CRC
    };
  }

  static Exiv2::BasicIo::UniquePtr MakeMemIo(const std::vector<uint8_t>& bytes) {
    // MemIo provides an in-memory BasicIo implementation.
    return std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size());
  }
};

TEST_F(PngImageFactoryTest_976, ValidPngBytesCreateFalseReturnsNonNull_976) {
  auto bytes = MinimalValidPngBytes();
  auto io = MakeMemIo(bytes);

  Exiv2::Image::UniquePtr image = Exiv2::newPngInstance(std::move(io), /*create=*/false);

  ASSERT_NE(image, nullptr);
  EXPECT_TRUE(image->good());
}

TEST_F(PngImageFactoryTest_976, ValidPngBytesCreateTrueReturnsNonNull_976) {
  auto bytes = MinimalValidPngBytes();
  auto io = MakeMemIo(bytes);

  Exiv2::Image::UniquePtr image = Exiv2::newPngInstance(std::move(io), /*create=*/true);

  ASSERT_NE(image, nullptr);
  EXPECT_TRUE(image->good());
}

TEST_F(PngImageFactoryTest_976, ReturnedInstanceReportsPngMimeTypeWhenAvailable_976) {
  auto bytes = MinimalValidPngBytes();
  auto io = MakeMemIo(bytes);

  Exiv2::Image::UniquePtr image = Exiv2::newPngInstance(std::move(io), /*create=*/false);

  ASSERT_NE(image, nullptr);
  // Observable behavior via public interface (virtual call through Image).
  // We avoid asserting exact string casing/format beyond PNG identification.
  const std::string mime = image->mimeType();
  EXPECT_FALSE(mime.empty());
  EXPECT_NE(mime.find("png"), std::string::npos);
}

TEST_F(PngImageFactoryTest_976, EmptyInputReturnsNull_976) {
  std::vector<uint8_t> empty;
  auto io = MakeMemIo(empty);

  Exiv2::Image::UniquePtr image = Exiv2::newPngInstance(std::move(io), /*create=*/false);

  EXPECT_EQ(image, nullptr);
}

TEST_F(PngImageFactoryTest_976, WrongSignatureReturnsNull_976) {
  // Not a PNG: simple junk bytes.
  std::vector<uint8_t> junk = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
  auto io = MakeMemIo(junk);

  Exiv2::Image::UniquePtr image = Exiv2::newPngInstance(std::move(io), /*create=*/false);

  EXPECT_EQ(image, nullptr);
}

TEST_F(PngImageFactoryTest_976, TruncatedPngSignatureReturnsNull_976) {
  // Only part of the PNG signature (less than 8 bytes).
  std::vector<uint8_t> truncated = {0x89, 0x50, 0x4E, 0x47};
  auto io = MakeMemIo(truncated);

  Exiv2::Image::UniquePtr image = Exiv2::newPngInstance(std::move(io), /*create=*/false);

  EXPECT_EQ(image, nullptr);
}

TEST_F(PngImageFactoryTest_976, MovesUniquePtrIntoFactory_976) {
  auto bytes = MinimalValidPngBytes();
  auto io = MakeMemIo(bytes);

  Exiv2::BasicIo* raw_before_move = io.get();
  ASSERT_NE(raw_before_move, nullptr);

  Exiv2::Image::UniquePtr image = Exiv2::newPngInstance(std::move(io), /*create=*/false);

  // After move, caller's unique_ptr must be empty (observable C++ move behavior).
  EXPECT_EQ(io, nullptr);

  // Result either null (if implementation deems it not good) or valid; for valid PNG we expect non-null.
  ASSERT_NE(image, nullptr);
  EXPECT_TRUE(image->good());
}

}  // namespace