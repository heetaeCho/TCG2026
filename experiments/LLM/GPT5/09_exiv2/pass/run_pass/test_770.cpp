// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 770
//
// Unit tests for Exiv2::ExifThumb::setJpegThumbnail(const std::string& path, URational xres, URational yres, uint16_t unit)
//
// Constraints respected:
// - Treat implementation as a black box
// - Only use public interfaces / observable behavior (return/throw + ExifData observable state)
// - No access to private/internal state
// - No mocking of internals

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <type_traits>
#include <vector>

namespace {

class ExifThumbSetJpegThumbnailPathTest_770 : public ::testing::Test {
 protected:
  static std::filesystem::path MakeUniquePath(const std::string& stem) {
    const auto base = std::filesystem::temp_directory_path();
    // Simple uniqueness: stem + pid-ish + counter-ish
    static std::uint64_t counter = 0;
    const auto name = stem + "_" + std::to_string(++counter) + ".bin";
    return base / name;
  }

  static void WriteFile(const std::filesystem::path& p, const std::vector<unsigned char>& bytes) {
    std::ofstream os(p, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(os.is_open()) << "Failed to open file for writing: " << p.string();
    if (!bytes.empty()) {
      os.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    }
    ASSERT_TRUE(os.good()) << "Failed while writing: " << p.string();
  }

  static bool IsReadableFile(const std::filesystem::path& p) {
    std::error_code ec;
    return std::filesystem::exists(p, ec) && std::filesystem::is_regular_file(p, ec);
  }

  static bool KeyExists(const Exiv2::ExifData& exif, const char* key) {
    Exiv2::ExifKey k(key);
    return exif.findKey(k) != exif.end();
  }

  template <typename T, typename = void>
  struct HasCopy : std::false_type {};
  template <typename T>
  struct HasCopy<T, std::void_t<decltype(std::declval<T&>().copy())>> : std::true_type {};

  template <typename T, typename = void>
  struct HasThumbnail : std::false_type {};
  template <typename T>
  struct HasThumbnail<T, std::void_t<decltype(std::declval<T&>().thumbnail())>> : std::true_type {};

  template <typename ThumbT>
  static Exiv2::DataBuf TryGetThumbData(ThumbT& thumb) {
    if constexpr (HasCopy<ThumbT>::value) {
      return thumb.copy();
    } else if constexpr (HasThumbnail<ThumbT>::value) {
      // Some Exiv2 versions expose thumbnail() returning DataBuf.
      return thumb.thumbnail();
    } else {
      return Exiv2::DataBuf();  // empty; caller should handle as "not available"
    }
  }
};

TEST_F(ExifThumbSetJpegThumbnailPathTest_770, ValidFileDoesNotThrowAndWritesResolutionTags_770) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumb thumb(exif);

  // Minimal JPEG-like bytes (SOI ... EOI). We don't assume validation details; we only assert no throw.
  const std::vector<unsigned char> jpegBytes = {0xFF, 0xD8, 0xFF, 0xD9};

  const auto p = MakeUniquePath("exiv2_exifthumb_770_valid");
  WriteFile(p, jpegBytes);
  ASSERT_TRUE(IsReadableFile(p));

  const Exiv2::URational xres{72, 1};
  const Exiv2::URational yres{300, 1};
  const std::uint16_t unit = 2;  // common EXIF: inches

  ASSERT_NO_THROW(thumb.setJpegThumbnail(p.string(), xres, yres, unit));

  // Observable behavior through public ExifData: resolution tags should exist and match inputs.
  // (We only assert keys that are part of the public ExifData view; no private state.)
  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.XResolution"));
  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.YResolution"));
  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.ResolutionUnit"));

  EXPECT_EQ(exif["Exif.Thumbnail.XResolution"].toRational().first, xres.first);
  EXPECT_EQ(exif["Exif.Thumbnail.XResolution"].toRational().second, xres.second);

  EXPECT_EQ(exif["Exif.Thumbnail.YResolution"].toRational().first, yres.first);
  EXPECT_EQ(exif["Exif.Thumbnail.YResolution"].toRational().second, yres.second);

  EXPECT_EQ(static_cast<std::uint32_t>(exif["Exif.Thumbnail.ResolutionUnit"].toUint32()),
            static_cast<std::uint32_t>(unit));

  // If the build exposes a public accessor for the thumbnail bytes, verify we can retrieve something non-empty.
  // (This is an optional observable check; it compiles away if not supported by the installed Exiv2 API.)
  const Exiv2::DataBuf got = TryGetThumbData(thumb);
  if (!got.empty()) {
    EXPECT_GE(got.size(), jpegBytes.size());
  }

  std::error_code ec;
  std::filesystem::remove(p, ec);
}

TEST_F(ExifThumbSetJpegThumbnailPathTest_770, NonExistentPathThrows_770) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumb thumb(exif);

  const auto missing = MakeUniquePath("exiv2_exifthumb_770_missing");
  std::error_code ec;
  std::filesystem::remove(missing, ec);  // ensure it does not exist

  const Exiv2::URational xres{72, 1};
  const Exiv2::URational yres{72, 1};

  EXPECT_ANY_THROW(thumb.setJpegThumbnail(missing.string(), xres, yres, /*unit*/ 2));
}

TEST_F(ExifThumbSetJpegThumbnailPathTest_770, DirectoryPathThrows_770) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumb thumb(exif);

  const auto dir = MakeUniquePath("exiv2_exifthumb_770_dir");
  std::error_code ec;
  std::filesystem::create_directories(dir, ec);
  ASSERT_TRUE(std::filesystem::exists(dir));

  const Exiv2::URational xres{72, 1};
  const Exiv2::URational yres{72, 1};

  EXPECT_ANY_THROW(thumb.setJpegThumbnail(dir.string(), xres, yres, /*unit*/ 2));

  std::filesystem::remove_all(dir, ec);
}

TEST_F(ExifThumbSetJpegThumbnailPathTest_770, CallingTwiceWithDifferentFilesUpdatesObservableThumbnailIfAccessible_770) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumb thumb(exif);

  const auto p1 = MakeUniquePath("exiv2_exifthumb_770_a");
  const auto p2 = MakeUniquePath("exiv2_exifthumb_770_b");

  // Two different byte payloads.
  const std::vector<unsigned char> jpegA = {0xFF, 0xD8, 0x01, 0x02, 0x03, 0xFF, 0xD9};
  const std::vector<unsigned char> jpegB = {0xFF, 0xD8, 0x10, 0x20, 0x30, 0x40, 0x50, 0xFF, 0xD9};

  WriteFile(p1, jpegA);
  WriteFile(p2, jpegB);

  const Exiv2::URational xres{100, 1};
  const Exiv2::URational yres{200, 1};
  const std::uint16_t unit = 2;

  ASSERT_NO_THROW(thumb.setJpegThumbnail(p1.string(), xres, yres, unit));
  const Exiv2::DataBuf t1 = TryGetThumbData(thumb);

  ASSERT_NO_THROW(thumb.setJpegThumbnail(p2.string(), xres, yres, unit));
  const Exiv2::DataBuf t2 = TryGetThumbData(thumb);

  // If there is a public way to read thumbnail bytes, verify the second call changes the observable bytes/size.
  if (!t1.empty() && !t2.empty()) {
    EXPECT_NE(t1.size(), t2.size());
  }

  // Resolution tags remain consistent with the last call's parameters (same in this test).
  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.XResolution"));
  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.YResolution"));
  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.ResolutionUnit"));

  EXPECT_EQ(exif["Exif.Thumbnail.XResolution"].toRational().first, xres.first);
  EXPECT_EQ(exif["Exif.Thumbnail.YResolution"].toRational().first, yres.first);
  EXPECT_EQ(static_cast<std::uint32_t>(exif["Exif.Thumbnail.ResolutionUnit"].toUint32()),
            static_cast<std::uint32_t>(unit));

  std::error_code ec;
  std::filesystem::remove(p1, ec);
  std::filesystem::remove(p2, ec);
}

TEST_F(ExifThumbSetJpegThumbnailPathTest_770, EraseRemovesThumbnailRelatedTags_770) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumb thumb(exif);

  const auto p = MakeUniquePath("exiv2_exifthumb_770_erase");
  const std::vector<unsigned char> jpegBytes = {0xFF, 0xD8, 0xAA, 0xBB, 0xCC, 0xFF, 0xD9};
  WriteFile(p, jpegBytes);

  const Exiv2::URational xres{72, 1};
  const Exiv2::URational yres{72, 1};
  ASSERT_NO_THROW(thumb.setJpegThumbnail(p.string(), xres, yres, /*unit*/ 2));

  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.XResolution"));
  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.YResolution"));
  ASSERT_TRUE(KeyExists(exif, "Exif.Thumbnail.ResolutionUnit"));

  ASSERT_NO_THROW(thumb.erase());

  // Observable behavior: tags previously created should no longer be present.
  EXPECT_FALSE(KeyExists(exif, "Exif.Thumbnail.XResolution"));
  EXPECT_FALSE(KeyExists(exif, "Exif.Thumbnail.YResolution"));
  EXPECT_FALSE(KeyExists(exif, "Exif.Thumbnail.ResolutionUnit"));

  std::error_code ec;
  std::filesystem::remove(p, ec);
}

}  // namespace