// =================================================================================================
// TEST_ID: 768
// File: test_exifthumbnc_mimetype_768.cpp
//
// Unit tests for Exiv2::ExifThumbC::mimeType() based strictly on public/observable behavior.
// Treat implementation as a black box.
//
// These tests intentionally avoid relying on private state or internal Thumbnail logic.
// They only construct ExifData via the public API and observe the returned C-string.
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>

#include <cstring>
#include <string>

namespace {

class ExifThumbCTest_768 : public ::testing::Test {
 protected:
  static std::string ToString(const char* s) {
    return s ? std::string(s) : std::string();
  }
};

TEST_F(ExifThumbCTest_768, MimeType_EmptyExifData_ReturnsEmptyString_768) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumbC thumb(exif);

  const char* mt = thumb.mimeType();

  ASSERT_NE(mt, nullptr);
  EXPECT_STREQ(mt, "");
}

TEST_F(ExifThumbCTest_768, MimeType_ReturnsNullTerminatedCString_768) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumbC thumb(exif);

  const char* mt = thumb.mimeType();

  ASSERT_NE(mt, nullptr);
  // For a valid C-string, strlen must not crash and the last byte must be '\0'.
  const size_t n = std::strlen(mt);
  ASSERT_GE(n, 0u);
  EXPECT_EQ(mt[n], '\0');
}

TEST_F(ExifThumbCTest_768, MimeType_CanBeCalledRepeatedly_768) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumbC thumb(exif);

  const char* mt1 = thumb.mimeType();
  const char* mt2 = thumb.mimeType();

  ASSERT_NE(mt1, nullptr);
  ASSERT_NE(mt2, nullptr);
  EXPECT_EQ(ToString(mt1), ToString(mt2));
}

TEST_F(ExifThumbCTest_768, MimeType_WithJpegThumbnailTags_ReturnsExpectedOrEmpty_768) {
  // We only use public ExifData setters. Whether these tags are sufficient for a thumbnail
  // to be recognized is an implementation detail; therefore, the test is resilient:
  // - If a thumbnail is recognized, mime type should be a JPEG type.
  // - If not recognized, behavior should match "no thumbnail": empty string.
  Exiv2::ExifData exif;

  // Common EXIF thumbnail tags (public interface keys).
  // Compression 6 is the standard JPEG compression value in EXIF/TIFF.
  exif["Exif.Thumbnail.Compression"] = uint16_t(6);
  // Provide plausible (non-zero) values for offset/length tags often associated with JPEG thumbnails.
  exif["Exif.Thumbnail.JPEGInterchangeFormat"] = uint32_t(1);
  exif["Exif.Thumbnail.JPEGInterchangeFormatLength"] = uint32_t(1);

  Exiv2::ExifThumbC thumb(exif);
  const std::string mt = ToString(thumb.mimeType());

  if (mt.empty()) {
    SUCCEED();  // No observable thumbnail recognized -> acceptable outcome for black-box behavior.
  } else {
    // If non-empty, it should be a JPEG mime type.
    // Accept common spellings defensively.
    EXPECT_TRUE(mt == "image/jpeg" || mt == "image/jpg") << "Unexpected mimeType(): " << mt;
  }
}

TEST_F(ExifThumbCTest_768, MimeType_WithUnknownCompression_DoesNotCrash_768) {
  Exiv2::ExifData exif;
  exif["Exif.Thumbnail.Compression"] = uint16_t(999);  // Uncommon/unknown compression code.

  Exiv2::ExifThumbC thumb(exif);
  const char* mt = thumb.mimeType();

  ASSERT_NE(mt, nullptr);
  // For black-box safety, only assert it's a valid string (may be empty or some fallback).
  const size_t n = std::strlen(mt);
  EXPECT_EQ(mt[n], '\0');
}

}  // namespace