// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_bmffimage_pixelHeight_1195.cpp

#include <gtest/gtest.h>

#include "exiv2/bmffimage.hpp"
#include "exiv2/memio.hpp"
#include "exiv2/exif.hpp"

namespace {

class BmffImageTest_1195 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::BmffImage> makeImage(size_t max_box_depth = 10) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::BmffImage>(std::move(io), /*create=*/false, max_box_depth);
  }
};

TEST_F(BmffImageTest_1195, PixelHeight_UsesExifPixelYDimensionWhenPresent_1195) {
  auto img = makeImage();

  img->exifData()["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(123);

  EXPECT_EQ(img->pixelHeight(), 123u);
}

TEST_F(BmffImageTest_1195, PixelHeight_ReflectsUpdatedExifValue_1195) {
  auto img = makeImage();

  img->exifData()["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(10);
  EXPECT_EQ(img->pixelHeight(), 10u);

  img->exifData()["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(999);
  EXPECT_EQ(img->pixelHeight(), 999u);
}

TEST_F(BmffImageTest_1195, PixelHeight_BoundaryValuesFromExifAreReturned_1195) {
  auto img = makeImage();

  img->exifData()["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(0);
  EXPECT_EQ(img->pixelHeight(), 0u);

  img->exifData()["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(0xFFFFFFFFu);
  EXPECT_EQ(img->pixelHeight(), 0xFFFFFFFFu);
}

TEST_F(BmffImageTest_1195, PixelHeight_FallsBackWhenExifKeyAbsent_1195) {
  auto img = makeImage();

  const uint32_t baseline = img->pixelHeight();

  img->exifData()["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(321);
  EXPECT_EQ(img->pixelHeight(), 321u);

  // Remove the key and verify it falls back to the original baseline.
  auto& exif = img->exifData();
  Exiv2::ExifKey key("Exif.Photo.PixelYDimension");
  auto it = exif.findKey(key);
  ASSERT_NE(it, exif.end());
  exif.erase(it);

  EXPECT_EQ(img->pixelHeight(), baseline);
}

TEST_F(BmffImageTest_1195, PixelHeight_NotAffectedByUnrelatedExifKeys_1195) {
  auto img = makeImage();

  const uint32_t baseline = img->pixelHeight();

  img->exifData()["Exif.Photo.PixelXDimension"] = static_cast<uint32_t>(777);  // unrelated
  EXPECT_EQ(img->pixelHeight(), baseline);

  img->exifData()["Exif.Photo.PixelYDimension"] = static_cast<uint32_t>(888);
  EXPECT_EQ(img->pixelHeight(), 888u);
}

}  // namespace