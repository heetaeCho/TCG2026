// TEST_ID 1549
// File: test_orfimage_pixelheight_1549.cpp

#include <gtest/gtest.h>

#include "exiv2/orfimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/exif.hpp"

namespace {

// Fixture focused on OrfImage::pixelHeight() observable behavior via public API.
class OrfImageTest_1549 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Use an in-memory IO so tests don't touch filesystem.
    // MemIo is a concrete BasicIo implementation provided by Exiv2.
    Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
    image_ = std::make_unique<Exiv2::OrfImage>(std::move(io), /*create=*/true);
  }

  std::unique_ptr<Exiv2::OrfImage> image_;
};

TEST_F(OrfImageTest_1549, ReturnsZeroWhenImageLengthKeyMissing_1549) {
  ASSERT_NE(image_, nullptr);

  // No "Exif.Image.ImageLength" present.
  EXPECT_NO_THROW({
    const uint32_t h = image_->pixelHeight();
    EXPECT_EQ(0u, h);
  });
}

TEST_F(OrfImageTest_1549, ReturnsStoredValueWhenImageLengthKeyPresent_1549) {
  ASSERT_NE(image_, nullptr);

  // Set via public ExifData API.
  image_->exifData()["Exif.Image.ImageLength"] = static_cast<uint32_t>(123u);

  EXPECT_NO_THROW({
    const uint32_t h = image_->pixelHeight();
    EXPECT_EQ(123u, h);
  });
}

TEST_F(OrfImageTest_1549, ReturnsZeroWhenImageLengthValueIsZero_1549) {
  ASSERT_NE(image_, nullptr);

  image_->exifData()["Exif.Image.ImageLength"] = static_cast<uint32_t>(0u);

  EXPECT_NO_THROW({
    const uint32_t h = image_->pixelHeight();
    EXPECT_EQ(0u, h);
  });
}

TEST_F(OrfImageTest_1549, ReturnsMaxUint32WhenImageLengthIsMax_1549) {
  ASSERT_NE(image_, nullptr);

  const uint32_t kMax = 0xFFFFFFFFu;
  image_->exifData()["Exif.Image.ImageLength"] = kMax;

  EXPECT_NO_THROW({
    const uint32_t h = image_->pixelHeight();
    EXPECT_EQ(kMax, h);
  });
}

}  // namespace