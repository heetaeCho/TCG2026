// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifthumb_setjpegthumbnail_771.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/exif.hpp"

namespace {

class ExifThumbTest_771 : public ::testing::Test {
 protected:
  Exiv2::ExifData exifData_;
  Exiv2::ExifThumb thumb_{exifData_};

  static std::vector<Exiv2::byte> MakeDummyJpegBytes() {
    // Minimal-ish JPEG header bytes (SOI + APP0 marker start). Content isn't validated here.
    return {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00};
  }

  static Exiv2::ExifData::iterator Find(Exiv2::ExifData& data, const std::string& keyStr) {
    Exiv2::ExifKey key(keyStr);
    return data.findKey(key);
  }

  static std::string ToStringOf(Exiv2::ExifData& data, const std::string& keyStr) {
    auto it = Find(data, keyStr);
    EXPECT_NE(it, data.end()) << "Expected key to exist: " << keyStr;
    if (it == data.end()) return {};
    return it->toString();
  }

  static int64_t ToInt64Of(Exiv2::ExifData& data, const std::string& keyStr, size_t n = 0) {
    auto it = Find(data, keyStr);
    EXPECT_NE(it, data.end()) << "Expected key to exist: " << keyStr;
    if (it == data.end()) return 0;
    return it->toInt64(n);
  }
};

TEST_F(ExifThumbTest_771, SetsResolutionTags_771) {
  const auto jpeg = MakeDummyJpegBytes();

  const Exiv2::URational xres(72, 1);
  const Exiv2::URational yres(300, 1);
  const uint16_t unit = 2;  // Commonly "inches" in EXIF, but we only treat it as an observable value.

  thumb_.setJpegThumbnail(jpeg.data(), jpeg.size(), xres, yres, unit);

  EXPECT_NE(Find(exifData_, "Exif.Thumbnail.XResolution"), exifData_.end());
  EXPECT_NE(Find(exifData_, "Exif.Thumbnail.YResolution"), exifData_.end());
  EXPECT_NE(Find(exifData_, "Exif.Thumbnail.ResolutionUnit"), exifData_.end());

  // Use toString() for rationals to avoid assumptions about Rational/URational internal representation.
  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.XResolution"), "72/1");
  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.YResolution"), "300/1");
  EXPECT_EQ(ToInt64Of(exifData_, "Exif.Thumbnail.ResolutionUnit"), static_cast<int64_t>(unit));
}

TEST_F(ExifThumbTest_771, OverwritesExistingResolutionTags_771) {
  const auto jpeg = MakeDummyJpegBytes();

  thumb_.setJpegThumbnail(jpeg.data(), jpeg.size(), Exiv2::URational(72, 1), Exiv2::URational(72, 1), 1);

  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.XResolution"), "72/1");
  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.YResolution"), "72/1");
  EXPECT_EQ(ToInt64Of(exifData_, "Exif.Thumbnail.ResolutionUnit"), 1);

  // Call again with different values; observable behavior should reflect the latest call.
  thumb_.setJpegThumbnail(jpeg.data(), jpeg.size(), Exiv2::URational(600, 1), Exiv2::URational(1200, 1), 2);

  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.XResolution"), "600/1");
  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.YResolution"), "1200/1");
  EXPECT_EQ(ToInt64Of(exifData_, "Exif.Thumbnail.ResolutionUnit"), 2);
}

TEST_F(ExifThumbTest_771, AcceptsZeroSizedBufferAndStillSetsResolutionTags_771) {
  // Boundary condition: size == 0. We avoid assuming thumbnail-writing behavior; we only
  // check the observable tag updates performed by this overload.
  const Exiv2::byte* buf = nullptr;
  const size_t size = 0;

  const Exiv2::URational xres(1, 1);
  const Exiv2::URational yres(1, 2);
  const uint16_t unit = 0;

  // If the implementation throws on (nullptr,0), this test will fail; however, from the
  // provided snippet this overload always assigns the tags after calling setJpegThumbnail(buf,size).
  // Treating it as black-box: we assert it does not throw and tags are set.
  EXPECT_NO_THROW(thumb_.setJpegThumbnail(buf, size, xres, yres, unit));

  EXPECT_NE(Find(exifData_, "Exif.Thumbnail.XResolution"), exifData_.end());
  EXPECT_NE(Find(exifData_, "Exif.Thumbnail.YResolution"), exifData_.end());
  EXPECT_NE(Find(exifData_, "Exif.Thumbnail.ResolutionUnit"), exifData_.end());

  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.XResolution"), "1/1");
  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.YResolution"), "1/2");
  EXPECT_EQ(ToInt64Of(exifData_, "Exif.Thumbnail.ResolutionUnit"), 0);
}

TEST_F(ExifThumbTest_771, SupportsMaxResolutionUnitValue_771) {
  const auto jpeg = MakeDummyJpegBytes();

  const Exiv2::URational xres(65535, 1);
  const Exiv2::URational yres(65535, 2);
  const uint16_t unit = std::numeric_limits<uint16_t>::max();

  thumb_.setJpegThumbnail(jpeg.data(), jpeg.size(), xres, yres, unit);

  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.XResolution"), "65535/1");
  EXPECT_EQ(ToStringOf(exifData_, "Exif.Thumbnail.YResolution"), "65535/2");
  EXPECT_EQ(ToInt64Of(exifData_, "Exif.Thumbnail.ResolutionUnit"), static_cast<int64_t>(unit));
}

}  // namespace