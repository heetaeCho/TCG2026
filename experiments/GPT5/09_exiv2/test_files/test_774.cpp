// =================================================================================================
// Exiv2 unit tests for Exiv2::ExifThumb::erase()
// File: test_exifthumb_erase_774.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

class ExifThumbTest_774 : public ::testing::Test {
 protected:
  Exiv2::ExifData exif_;
};

// Helper: check presence of a key in ExifData using only public API.
static bool HasKey(const Exiv2::ExifData& exif, const char* key) {
  Exiv2::ExifKey k(key);
  return exif.findKey(k) != exif.end();
}

}  // namespace

TEST_F(ExifThumbTest_774, EraseOnEmptyExifDataDoesNotThrow_774) {
  Exiv2::ExifThumb thumb(exif_);
  EXPECT_NO_THROW(thumb.erase());
  EXPECT_TRUE(exif_.empty());
}

TEST_F(ExifThumbTest_774, EraseRemovesIfd1ThumbnailTagsButKeepsOtherTags_774) {
  // Non-thumbnail tag (commonly stored in IFD0 / Exif IFD depending on tag).
  exif_["Exif.Image.Make"] = "UnitTestCam";

  // Thumbnail-related tags (commonly associated with IFD1 thumbnail).
  exif_["Exif.Thumbnail.Compression"] = uint16_t(6);  // JPEG
  exif_["Exif.Thumbnail.JPEGInterchangeFormat"] = uint32_t(1234);
  exif_["Exif.Thumbnail.JPEGInterchangeFormatLength"] = uint32_t(5678);

  ASSERT_TRUE(HasKey(exif_, "Exif.Image.Make"));
  ASSERT_TRUE(HasKey(exif_, "Exif.Thumbnail.Compression"));
  ASSERT_TRUE(HasKey(exif_, "Exif.Thumbnail.JPEGInterchangeFormat"));
  ASSERT_TRUE(HasKey(exif_, "Exif.Thumbnail.JPEGInterchangeFormatLength"));

  Exiv2::ExifThumb thumb(exif_);
  thumb.erase();

  // Observable behavior: thumbnail keys removed, other keys remain.
  EXPECT_TRUE(HasKey(exif_, "Exif.Image.Make"));
  EXPECT_FALSE(HasKey(exif_, "Exif.Thumbnail.Compression"));
  EXPECT_FALSE(HasKey(exif_, "Exif.Thumbnail.JPEGInterchangeFormat"));
  EXPECT_FALSE(HasKey(exif_, "Exif.Thumbnail.JPEGInterchangeFormatLength"));
}

TEST_F(ExifThumbTest_774, EraseIsIdempotentWhenCalledMultipleTimes_774) {
  exif_["Exif.Image.Model"] = "UnitTestModel";
  exif_["Exif.Thumbnail.Compression"] = uint16_t(6);
  exif_["Exif.Thumbnail.JPEGInterchangeFormat"] = uint32_t(42);

  Exiv2::ExifThumb thumb(exif_);

  ASSERT_TRUE(HasKey(exif_, "Exif.Image.Model"));
  ASSERT_TRUE(HasKey(exif_, "Exif.Thumbnail.Compression"));
  ASSERT_TRUE(HasKey(exif_, "Exif.Thumbnail.JPEGInterchangeFormat"));

  EXPECT_NO_THROW(thumb.erase());
  EXPECT_TRUE(HasKey(exif_, "Exif.Image.Model"));
  EXPECT_FALSE(HasKey(exif_, "Exif.Thumbnail.Compression"));
  EXPECT_FALSE(HasKey(exif_, "Exif.Thumbnail.JPEGInterchangeFormat"));

  // Second call should be safe and keep state stable.
  EXPECT_NO_THROW(thumb.erase());
  EXPECT_TRUE(HasKey(exif_, "Exif.Image.Model"));
  EXPECT_FALSE(HasKey(exif_, "Exif.Thumbnail.Compression"));
  EXPECT_FALSE(HasKey(exif_, "Exif.Thumbnail.JPEGInterchangeFormat"));
}

TEST_F(ExifThumbTest_774, EraseDoesNotRemoveNonIfd1ExifTags_774) {
  // Populate a variety of non-thumbnail tags.
  exif_["Exif.Image.Make"] = "MakeA";
  exif_["Exif.Image.Software"] = "SoftB";
  exif_["Exif.Photo.DateTimeOriginal"] = "2026:02:05 21:00:00";

  // Also add a thumbnail key to ensure erase actually does something.
  exif_["Exif.Thumbnail.Compression"] = uint16_t(6);

  ASSERT_TRUE(HasKey(exif_, "Exif.Image.Make"));
  ASSERT_TRUE(HasKey(exif_, "Exif.Image.Software"));
  ASSERT_TRUE(HasKey(exif_, "Exif.Photo.DateTimeOriginal"));
  ASSERT_TRUE(HasKey(exif_, "Exif.Thumbnail.Compression"));

  Exiv2::ExifThumb thumb(exif_);
  thumb.erase();

  // Non-thumbnail keys should remain observable after erase.
  EXPECT_TRUE(HasKey(exif_, "Exif.Image.Make"));
  EXPECT_TRUE(HasKey(exif_, "Exif.Image.Software"));
  EXPECT_TRUE(HasKey(exif_, "Exif.Photo.DateTimeOriginal"));

  // Thumbnail key removed.
  EXPECT_FALSE(HasKey(exif_, "Exif.Thumbnail.Compression"));
}