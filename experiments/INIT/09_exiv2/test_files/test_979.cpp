// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>

#include "exiv2/basicio.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/mrwimage.hpp"

namespace {

class MrwImageTest_979 : public ::testing::Test {
 protected:
  static Exiv2::MrwImage MakeImage() {
    Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo());
    return Exiv2::MrwImage(std::move(io), /*create=*/false);
  }
};

TEST_F(MrwImageTest_979, PixelWidth_NoExifKey_ReturnsZero_979) {
  auto img = MakeImage();

  EXPECT_EQ(0u, img.pixelWidth());
}

TEST_F(MrwImageTest_979, PixelWidth_UnrelatedExifKey_DoesNotAffectResult_979) {
  auto img = MakeImage();

  // Set some other key (not Exif.Image.ImageWidth)
  img.exifData()["Exif.Image.ImageLength"] = uint32_t{123};

  EXPECT_EQ(0u, img.pixelWidth());
}

TEST_F(MrwImageTest_979, PixelWidth_WithImageWidthKey_ReturnsStoredValue_979) {
  auto img = MakeImage();

  img.exifData()["Exif.Image.ImageWidth"] = uint32_t{640};

  EXPECT_EQ(640u, img.pixelWidth());
}

TEST_F(MrwImageTest_979, PixelWidth_BoundaryValues_ZeroAndMax_979) {
  auto img = MakeImage();

  img.exifData()["Exif.Image.ImageWidth"] = uint32_t{0};
  EXPECT_EQ(0u, img.pixelWidth());

  const uint32_t max_u32 = std::numeric_limits<uint32_t>::max();
  img.exifData()["Exif.Image.ImageWidth"] = max_u32;
  EXPECT_EQ(max_u32, img.pixelWidth());
}

TEST_F(MrwImageTest_979, PixelWidth_OverwritingValue_ReflectsLatestValue_979) {
  auto img = MakeImage();

  img.exifData()["Exif.Image.ImageWidth"] = uint32_t{1};
  EXPECT_EQ(1u, img.pixelWidth());

  img.exifData()["Exif.Image.ImageWidth"] = uint32_t{9999};
  EXPECT_EQ(9999u, img.pixelWidth());
}

}  // namespace