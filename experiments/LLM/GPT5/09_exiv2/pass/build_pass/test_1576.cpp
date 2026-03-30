// File: test_rw2image_pixelwidth_1576.cpp
// TEST_ID: 1576

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>

#include "exiv2/rw2image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/exif.hpp"

namespace {

class Rw2ImagePixelWidthTest_1576 : public ::testing::Test {
 protected:
  // Use an in-memory IO backend (common in Exiv2). The tests do not rely on its internal behavior.
  std::unique_ptr<Exiv2::Rw2Image> makeImage() {
    return std::make_unique<Exiv2::Rw2Image>(std::make_unique<Exiv2::MemIo>());
  }
};

TEST_F(Rw2ImagePixelWidthTest_1576, ReturnsZeroWhenExifTagMissing_1576) {
  auto img = makeImage();

  // No Exif.PanasonicRaw.SensorWidth entry present.
  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(Rw2ImagePixelWidthTest_1576, ReturnsStoredValueWhenExifTagPresent_1576) {
  auto img = makeImage();

  // Set the tag via the public ExifData interface.
  img->exifData()["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint32_t>(4032);

  EXPECT_EQ(img->pixelWidth(), 4032u);
}

TEST_F(Rw2ImagePixelWidthTest_1576, ReturnsZeroWhenStoredValueIsZero_1576) {
  auto img = makeImage();

  img->exifData()["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint32_t>(0);

  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(Rw2ImagePixelWidthTest_1576, HandlesMaxUint32Value_1576) {
  auto img = makeImage();

  const uint32_t kMax = std::numeric_limits<uint32_t>::max();
  img->exifData()["Exif.PanasonicRaw.SensorWidth"] = kMax;

  EXPECT_EQ(img->pixelWidth(), kMax);
}

TEST_F(Rw2ImagePixelWidthTest_1576, IgnoresOtherTagsAndStillReturnsZeroIfTargetMissing_1576) {
  auto img = makeImage();

  img->exifData()["Exif.Image.ImageWidth"] = static_cast<uint32_t>(9999);
  img->exifData()["Exif.Photo.PixelXDimension"] = static_cast<uint32_t>(8888);

  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(Rw2ImagePixelWidthTest_1576, UpdatingTagUpdatesReturnedValue_1576) {
  auto img = makeImage();

  img->exifData()["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint32_t>(100);
  EXPECT_EQ(img->pixelWidth(), 100u);

  img->exifData()["Exif.PanasonicRaw.SensorWidth"] = static_cast<uint32_t>(200);
  EXPECT_EQ(img->pixelWidth(), 200u);
}

}  // namespace