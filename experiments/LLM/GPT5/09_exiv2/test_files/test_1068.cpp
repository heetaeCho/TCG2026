// TEST_ID 1068
// File: test_image_exifdata_1068.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

namespace {

class ImageExifDataTest_1068 : public ::testing::Test {
protected:
  static Exiv2::Image makeImage() {
    Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
    // Avoid assuming specific enum values; use a safe cast.
    return Exiv2::Image(static_cast<Exiv2::ImageType>(0), static_cast<uint16_t>(0), std::move(io));
  }
};

TEST_F(ImageExifDataTest_1068, InitiallyEmpty_1068) {
  auto image = makeImage();
  EXPECT_TRUE(image.exifData().empty());
  EXPECT_EQ(0u, image.exifData().size());
}

TEST_F(ImageExifDataTest_1068, ReturnsSameReferenceEachCall_1068) {
  auto image = makeImage();

  Exiv2::ExifData* first = &image.exifData();
  Exiv2::ExifData* second = &image.exifData();

  EXPECT_EQ(first, second);
}

TEST_F(ImageExifDataTest_1068, AllowsMutationThroughReturnedReference_1068) {
  auto image = makeImage();

  Exiv2::ExifData& exifRef = image.exifData();
  exifRef["Exif.Image.Make"] = "UnitTestMake";

  // Verify observable behavior via the public API: the value is accessible on subsequent calls.
  ASSERT_FALSE(image.exifData().empty());
  EXPECT_EQ("UnitTestMake", image.exifData()["Exif.Image.Make"].toString());
}

TEST_F(ImageExifDataTest_1068, ClearThroughReturnedReferenceIsObservable_1068) {
  auto image = makeImage();

  image.exifData()["Exif.Image.Model"] = "UnitTestModel";
  ASSERT_FALSE(image.exifData().empty());

  Exiv2::ExifData& exifRef = image.exifData();
  exifRef.clear();

  EXPECT_TRUE(image.exifData().empty());
  EXPECT_EQ(0u, image.exifData().size());
}

}  // namespace