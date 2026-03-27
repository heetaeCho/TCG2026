// SPDX-License-Identifier: GPL-2.0-or-later
// File: bmffimage_test_1194.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>

#include "exiv2/basicio.hpp"
#include "exiv2/bmffimage.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace {

class BmffImageTest_1194 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::BmffImage> makeImage(size_t max_box_depth = 16) {
    // pixelWidth() in the provided snippet does not require IO access, but the class requires one.
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::BmffImage>(std::move(io), /*create=*/false, max_box_depth);
  }
};

TEST_F(BmffImageTest_1194, PixelWidth_NoExifKey_ReturnsFallbackDefault_1194) {
  auto img = makeImage();

  // With no Exif.Photo.PixelXDimension present, pixelWidth() should return the internal fallback.
  // The observable default fallback (from Image) is 0 unless set by other operations.
  EXPECT_EQ(0u, img->pixelWidth());
}

TEST_F(BmffImageTest_1194, PixelWidth_ExifKeySetViaOperatorBracket_ReturnsExifValue_1194) {
  auto img = makeImage();

  // Add the expected key/value through the public ExifData API.
  img->exifData()["Exif.Photo.PixelXDimension"] = static_cast<uint32_t>(123u);

  EXPECT_EQ(123u, img->pixelWidth());
}

TEST_F(BmffImageTest_1194, PixelWidth_ExifValueZero_ReturnsZero_1194) {
  auto img = makeImage();

  img->exifData()["Exif.Photo.PixelXDimension"] = static_cast<uint32_t>(0u);

  EXPECT_EQ(0u, img->pixelWidth());
}

TEST_F(BmffImageTest_1194, PixelWidth_ExifValueUint32Max_ReturnsUint32Max_1194) {
  auto img = makeImage();

  const uint32_t kMax = std::numeric_limits<uint32_t>::max();
  img->exifData()["Exif.Photo.PixelXDimension"] = kMax;

  EXPECT_EQ(kMax, img->pixelWidth());
}

TEST_F(BmffImageTest_1194, PixelWidth_ExifKeyPresentButEmptyCount_FallsBack_1194) {
  auto img = makeImage();

  // Create an Exifdatum with the right type but with no elements set -> count() is expected to be 0.
  // This uses only public Exiv2 interfaces.
  auto v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(nullptr, v.get());

  img->exifData().add(Exiv2::ExifKey("Exif.Photo.PixelXDimension"), v.get());

  // With count() == 0, pixelWidth() should use the fallback (observable default 0).
  EXPECT_EQ(0u, img->pixelWidth());
}

}  // namespace