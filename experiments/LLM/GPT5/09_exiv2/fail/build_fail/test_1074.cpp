// SPDX-License-Identifier: MIT
// File: test_image_setexifdata_1074.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

// Helper: add an ASCII Exif tag/value using only public Exiv2 APIs.
static void addAsciiTag(Exiv2::ExifData& exif, const std::string& key, const std::string& value) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(v.get() != nullptr);
  v->read(value);
  exif.add(Exiv2::ExifKey(key), v.get());
}

// Helper: create an Image instance with a BasicIo implementation.
static std::unique_ptr<Exiv2::Image> makeImage() {
  auto io = std::make_unique<Exiv2::MemIo>();
  // Avoid relying on specific enum values/names: treat ImageType as an opaque enum.
  return std::make_unique<Exiv2::Image>(static_cast<Exiv2::ImageType>(0), /*supportedMetadata=*/0,
                                        std::move(io));
}

class ImageSetExifDataTest_1074 : public ::testing::Test {
 protected:
  std::unique_ptr<Exiv2::Image> image_{makeImage()};
};

}  // namespace

// The TEST_ID is 1074
TEST_F(ImageSetExifDataTest_1074, SetExifDataCopiesAllTags_1074) {
  Exiv2::ExifData src;
  addAsciiTag(src, "Exif.Image.Make", "Canon");
  addAsciiTag(src, "Exif.Image.Model", "EOS");

  ASSERT_TRUE(image_->exifData().empty());  // precondition visible via public API

  image_->setExifData(src);

  EXPECT_EQ(image_->exifData().count(), src.count());
  EXPECT_FALSE(image_->exifData().empty());

  const auto makeIt = image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(makeIt, image_->exifData().end());

  const auto modelIt = image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Model"));
  ASSERT_NE(modelIt, image_->exifData().end());
}

// The TEST_ID is 1074
TEST_F(ImageSetExifDataTest_1074, SetExifDataOverwritesPreviousExifData_1074) {
  Exiv2::ExifData first;
  addAsciiTag(first, "Exif.Image.Make", "Nikon");
  image_->setExifData(first);

  ASSERT_EQ(image_->exifData().count(), first.count());
  ASSERT_NE(image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Make")), image_->exifData().end());

  Exiv2::ExifData second;
  addAsciiTag(second, "Exif.Image.Model", "D850");
  image_->setExifData(second);

  // Observable behavior: exifData() reflects the newly set ExifData.
  EXPECT_EQ(image_->exifData().count(), second.count());
  EXPECT_EQ(image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Make")), image_->exifData().end());
  EXPECT_NE(image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Model")), image_->exifData().end());
}

// The TEST_ID is 1074
TEST_F(ImageSetExifDataTest_1074, SetExifDataWithEmptyClearsExifData_1074) {
  Exiv2::ExifData nonEmpty;
  addAsciiTag(nonEmpty, "Exif.Image.Make", "Sony");
  image_->setExifData(nonEmpty);
  ASSERT_FALSE(image_->exifData().empty());

  Exiv2::ExifData empty;
  ASSERT_TRUE(empty.empty());

  image_->setExifData(empty);

  EXPECT_TRUE(image_->exifData().empty());
  EXPECT_EQ(image_->exifData().count(), 0u);
}

// The TEST_ID is 1074
TEST_F(ImageSetExifDataTest_1074, SetExifDataIsDeepCopyAgainstSourceMutation_1074) {
  Exiv2::ExifData src;
  addAsciiTag(src, "Exif.Image.Make", "Fujifilm");
  image_->setExifData(src);

  ASSERT_NE(image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Make")), image_->exifData().end());
  ASSERT_EQ(image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Model")), image_->exifData().end());

  // Mutate the source after setting.
  addAsciiTag(src, "Exif.Image.Model", "X-T5");

  // Observable requirement for a setter taking const&: image's stored ExifData should not
  // change when the caller mutates their original ExifData afterwards.
  EXPECT_EQ(image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Model")), image_->exifData().end());
}