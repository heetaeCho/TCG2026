// =================================================================================================
// Copyright ...
//
// Unit tests for Exiv2::Rw2Image::pixelHeight()
// File: ./TestProjects/exiv2/src/rw2image.cpp (partial)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>
#include <string>

#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/rw2image.hpp>
#include <exiv2/value.hpp>

namespace {

class Rw2ImagePixelHeightTest_1577 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Rw2Image> MakeImage() {
    // Use an in-memory IO so construction does not depend on filesystem.
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::Rw2Image>(std::move(io));
  }

  static constexpr const char* kSensorHeightKey = "Exif.PanasonicRaw.SensorHeight";
};

TEST_F(Rw2ImagePixelHeightTest_1577, ReturnsZeroWhenKeyMissing_1577) {
  auto img = MakeImage();

  // No Exif data set for the key.
  EXPECT_EQ(0u, img->pixelHeight());
}

TEST_F(Rw2ImagePixelHeightTest_1577, ReturnsValueWhenKeyPresentWithUint32_1577) {
  auto img = MakeImage();

  img->exifData()[kSensorHeightKey] = static_cast<uint32_t>(123u);

  EXPECT_EQ(123u, img->pixelHeight());
}

TEST_F(Rw2ImagePixelHeightTest_1577, ReturnsZeroWhenKeyPresentButCountIsZero_1577) {
  auto img = MakeImage();

  // Create a Value with no elements (count==0) and add it under the expected key.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(nullptr, v.get());
  ASSERT_EQ(0u, v->count());

  img->exifData().add(Exiv2::ExifKey(kSensorHeightKey), v.get());

  EXPECT_EQ(0u, img->pixelHeight());
}

TEST_F(Rw2ImagePixelHeightTest_1577, ReturnsZeroWhenKeyPresentWithValueZero_1577) {
  auto img = MakeImage();

  img->exifData()[kSensorHeightKey] = static_cast<uint32_t>(0u);

  EXPECT_EQ(0u, img->pixelHeight());
}

TEST_F(Rw2ImagePixelHeightTest_1577, ReturnsMaxUint32WhenKeyPresentWithMaxValue_1577) {
  auto img = MakeImage();

  const uint32_t maxv = std::numeric_limits<uint32_t>::max();
  img->exifData()[kSensorHeightKey] = maxv;

  EXPECT_EQ(maxv, img->pixelHeight());
}

TEST_F(Rw2ImagePixelHeightTest_1577, ReflectsUpdatesWhenExifValueChanges_1577) {
  auto img = MakeImage();

  img->exifData()[kSensorHeightKey] = static_cast<uint32_t>(10u);
  EXPECT_EQ(10u, img->pixelHeight());

  img->exifData()[kSensorHeightKey] = static_cast<uint32_t>(999u);
  EXPECT_EQ(999u, img->pixelHeight());
}

}  // namespace