// SPDX-License-Identifier: GPL-2.0-or-later
//
// TEST_ID: 1073
//
// Unit tests for: Exiv2::Image::clearExifData()
// File under test: ./TestProjects/exiv2/src/image.cpp

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>

namespace {

class ImageClearExifDataTest_1073 : public ::testing::Test {
protected:
  static std::unique_ptr<Exiv2::Image> makeImage() {
    // Treat Image as a black box; we only need a constructible instance.
    // Use a minimal ImageType / supportedMetadata; exact values are not part of this test.
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::Image>(static_cast<Exiv2::ImageType>(0), /*supportedMetadata*/ 0, std::move(io));
  }
};

TEST_F(ImageClearExifDataTest_1073, ClearExifDataOnEmptyKeepsEmpty_1073) {
  auto image = makeImage();

  EXPECT_TRUE(image->exifData().empty());
  EXPECT_EQ(image->exifData().count(), 0u);

  EXPECT_NO_THROW(image->clearExifData());

  EXPECT_TRUE(image->exifData().empty());
  EXPECT_EQ(image->exifData().count(), 0u);
}

TEST_F(ImageClearExifDataTest_1073, ClearExifDataRemovesPreviouslyAddedEntries_1073) {
  auto image = makeImage();

  // Use only the public interface: operator[] is declared on ExifData and is observable via count/empty.
  image->exifData()["Exif.Image.Make"];
  ASSERT_FALSE(image->exifData().empty());
  ASSERT_GE(image->exifData().count(), 1u);

  image->clearExifData();

  EXPECT_TRUE(image->exifData().empty());
  EXPECT_EQ(image->exifData().count(), 0u);
}

TEST_F(ImageClearExifDataTest_1073, ClearExifDataIsIdempotent_1073) {
  auto image = makeImage();

  image->exifData()["Exif.Image.Model"];
  ASSERT_GE(image->exifData().count(), 1u);

  EXPECT_NO_THROW(image->clearExifData());
  EXPECT_TRUE(image->exifData().empty());
  EXPECT_EQ(image->exifData().count(), 0u);

  // Call again (boundary / idempotency).
  EXPECT_NO_THROW(image->clearExifData());
  EXPECT_TRUE(image->exifData().empty());
  EXPECT_EQ(image->exifData().count(), 0u);
}

TEST_F(ImageClearExifDataTest_1073, ClearExifDataDoesNotPreventAddingNewEntriesAfterwards_1073) {
  auto image = makeImage();

  image->exifData()["Exif.Image.Artist"];
  ASSERT_GE(image->exifData().count(), 1u);

  image->clearExifData();
  ASSERT_TRUE(image->exifData().empty());

  // After clearing, adding again via public API should be observable.
  image->exifData()["Exif.Image.Copyright"];
  EXPECT_FALSE(image->exifData().empty());
  EXPECT_GE(image->exifData().count(), 1u);
}

}  // namespace