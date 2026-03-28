// =================================================================================================
// TestProjects/exiv2/tests/test_psdimage_mimetype_1185.cpp
//
// Unit tests for Exiv2::PsdImage::mimeType()
// TEST_ID: 1185
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/psdimage.hpp>

namespace {

class PsdImageTest_1185 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr makeIo() {
    // Use an in-memory IO object; no PSD bytes are required for mimeType().
    return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo());
  }
};

}  // namespace

TEST_F(PsdImageTest_1185, MimeTypeReturnsPhotoshopMime_1185) {
  Exiv2::PsdImage image(makeIo());
  EXPECT_EQ(image.mimeType(), std::string("image/x-photoshop"));
}

TEST_F(PsdImageTest_1185, MimeTypeIsStableAcrossMultipleCalls_1185) {
  Exiv2::PsdImage image(makeIo());

  const std::string first = image.mimeType();
  const std::string second = image.mimeType();
  const std::string third = image.mimeType();

  EXPECT_EQ(first, "image/x-photoshop");
  EXPECT_EQ(second, "image/x-photoshop");
  EXPECT_EQ(third, "image/x-photoshop");
}

TEST_F(PsdImageTest_1185, MimeTypeCallableOnConstObject_1185) {
  const Exiv2::PsdImage image(makeIo());
  EXPECT_EQ(image.mimeType(), std::string("image/x-photoshop"));
}

TEST_F(PsdImageTest_1185, MimeTypeIsNonEmpty_1185) {
  Exiv2::PsdImage image(makeIo());
  EXPECT_FALSE(image.mimeType().empty());
}