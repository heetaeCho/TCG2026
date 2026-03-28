// File: test_exifthumb_setjpegthumbnail_773.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <vector>

#include "exiv2/exif.hpp"

namespace {

// Helper to compare Exifdatum data area with expected bytes.
static void ExpectDataAreaEquals(const Exiv2::Exifdatum& d, const std::vector<Exiv2::byte>& expected) {
  const auto sz = d.sizeDataArea();
  EXPECT_EQ(sz, expected.size());

  const Exiv2::DataBuf buf = d.dataArea();
  // DataBuf is expected to describe the data area contents.
  ASSERT_EQ(buf.size_, expected.size());

  if (!expected.empty()) {
    ASSERT_NE(buf.pData_, nullptr);
    EXPECT_EQ(0, std::memcmp(buf.pData_, expected.data(), expected.size()));
  }
}

class ExifThumbTest_773 : public ::testing::Test {
 protected:
  Exiv2::ExifData exifData_;
  Exiv2::ExifThumb thumb_{exifData_};
};

}  // namespace

TEST_F(ExifThumbTest_773, SetJpegThumbnailSetsRequiredExifKeysAndDataArea_773) {
  ASSERT_TRUE(exifData_.empty());
  ASSERT_EQ(exifData_.count(), 0u);

  const std::vector<Exiv2::byte> jpegBytes = {
      static_cast<Exiv2::byte>(0xFF), static_cast<Exiv2::byte>(0xD8),  // SOI
      static_cast<Exiv2::byte>(0xFF), static_cast<Exiv2::byte>(0xD9)   // EOI
  };

  thumb_.setJpegThumbnail(jpegBytes.data(), jpegBytes.size());

  // Compression should be present and set (observable via value conversion).
  Exiv2::Exifdatum& compression = exifData_["Exif.Thumbnail.Compression"];
  EXPECT_EQ(compression.toInt64(0), 6);

  // Interchange format should be set to 0 (as an observable numeric value).
  Exiv2::Exifdatum& fmt = exifData_["Exif.Thumbnail.JPEGInterchangeFormat"];
  EXPECT_EQ(fmt.toInt64(0), 0);

  // Length should match the provided size.
  Exiv2::Exifdatum& len = exifData_["Exif.Thumbnail.JPEGInterchangeFormatLength"];
  EXPECT_EQ(len.toInt64(0), static_cast<int64_t>(jpegBytes.size()));

  // Data area should match the provided bytes.
  ExpectDataAreaEquals(fmt, jpegBytes);
}

TEST_F(ExifThumbTest_773, SetJpegThumbnailOverwritesPreviousThumbnailData_773) {
  const std::vector<Exiv2::byte> first = {static_cast<Exiv2::byte>(0x01),
                                         static_cast<Exiv2::byte>(0x02),
                                         static_cast<Exiv2::byte>(0x03)};
  const std::vector<Exiv2::byte> second = {static_cast<Exiv2::byte>(0xAA),
                                          static_cast<Exiv2::byte>(0xBB)};

  thumb_.setJpegThumbnail(first.data(), first.size());

  {
    Exiv2::Exifdatum& compression = exifData_["Exif.Thumbnail.Compression"];
    EXPECT_EQ(compression.toInt64(0), 6);

    Exiv2::Exifdatum& fmt = exifData_["Exif.Thumbnail.JPEGInterchangeFormat"];
    ExpectDataAreaEquals(fmt, first);

    Exiv2::Exifdatum& len = exifData_["Exif.Thumbnail.JPEGInterchangeFormatLength"];
    EXPECT_EQ(len.toInt64(0), static_cast<int64_t>(first.size()));
  }

  // Second call should update observable values.
  thumb_.setJpegThumbnail(second.data(), second.size());

  Exiv2::Exifdatum& compression = exifData_["Exif.Thumbnail.Compression"];
  EXPECT_EQ(compression.toInt64(0), 6);

  Exiv2::Exifdatum& fmt = exifData_["Exif.Thumbnail.JPEGInterchangeFormat"];
  ExpectDataAreaEquals(fmt, second);

  Exiv2::Exifdatum& len = exifData_["Exif.Thumbnail.JPEGInterchangeFormatLength"];
  EXPECT_EQ(len.toInt64(0), static_cast<int64_t>(second.size()));
}

TEST_F(ExifThumbTest_773, SetJpegThumbnailWithZeroSizeCreatesKeysAndZeroLength_773) {
  const std::vector<Exiv2::byte> bytes = {
      static_cast<Exiv2::byte>(0xFF), static_cast<Exiv2::byte>(0xD8)};

  // Boundary: size == 0 (buffer pointer is non-null).
  thumb_.setJpegThumbnail(bytes.data(), 0u);

  Exiv2::Exifdatum& compression = exifData_["Exif.Thumbnail.Compression"];
  EXPECT_EQ(compression.toInt64(0), 6);

  Exiv2::Exifdatum& fmt = exifData_["Exif.Thumbnail.JPEGInterchangeFormat"];
  EXPECT_EQ(fmt.toInt64(0), 0);

  Exiv2::Exifdatum& len = exifData_["Exif.Thumbnail.JPEGInterchangeFormatLength"];
  EXPECT_EQ(len.toInt64(0), 0);

  const auto sz = fmt.sizeDataArea();
  EXPECT_EQ(sz, 0u);

  const Exiv2::DataBuf buf = fmt.dataArea();
  EXPECT_EQ(buf.size_, 0u);
}

TEST_F(ExifThumbTest_773, SetJpegThumbnailDoesNotDependOnCallerBufferAfterCall_773) {
  std::vector<Exiv2::byte> bytes = {
      static_cast<Exiv2::byte>(0x10), static_cast<Exiv2::byte>(0x20), static_cast<Exiv2::byte>(0x30)};

  thumb_.setJpegThumbnail(bytes.data(), bytes.size());

  // Mutate caller-owned buffer after the call.
  bytes[0] = static_cast<Exiv2::byte>(0x99);
  bytes[1] = static_cast<Exiv2::byte>(0x88);
  bytes[2] = static_cast<Exiv2::byte>(0x77);

  // Observable behavior: the stored data area should remain equal to the original bytes passed at call time.
  // (This test verifies the public-facing result; it does not assume any specific internal mechanism.)
  const std::vector<Exiv2::byte> expectedOriginal = {
      static_cast<Exiv2::byte>(0x10), static_cast<Exiv2::byte>(0x20), static_cast<Exiv2::byte>(0x30)};

  Exiv2::Exifdatum& fmt = exifData_["Exif.Thumbnail.JPEGInterchangeFormat"];
  ExpectDataAreaEquals(fmt, expectedOriginal);

  Exiv2::Exifdatum& len = exifData_["Exif.Thumbnail.JPEGInterchangeFormatLength"];
  EXPECT_EQ(len.toInt64(0), static_cast<int64_t>(expectedOriginal.size()));
}