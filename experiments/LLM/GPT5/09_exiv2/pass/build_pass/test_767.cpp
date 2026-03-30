// TEST_ID 767
// File: test_exifthumbc_writefile_767.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

class ExifThumbCTest_767 : public ::testing::Test {
 protected:
  static std::filesystem::path TempDir() {
    return std::filesystem::temp_directory_path();
  }

  static std::string UniqueBasePath(const std::string& stem) {
    const auto dir = TempDir();
    const auto unique =
        stem + "_" + std::to_string(static_cast<unsigned long long>(::testing::UnitTest::GetInstance()
                                                                        ->random_seed())) +
        "_" + std::to_string(static_cast<unsigned long long>(std::chrono::high_resolution_clock::now()
                                                                 .time_since_epoch()
                                                                 .count()));
    return (dir / unique).string();
  }

  static std::vector<Exiv2::byte> MinimalJpegBytes() {
    // Smallest "JPEG-like" byte sequence: SOI + EOI.
    return {static_cast<Exiv2::byte>(0xFF), static_cast<Exiv2::byte>(0xD8),
            static_cast<Exiv2::byte>(0xFF), static_cast<Exiv2::byte>(0xD9)};
  }

  static bool FileExists(const std::filesystem::path& p) {
    std::error_code ec;
    return std::filesystem::exists(p, ec) && std::filesystem::is_regular_file(p, ec);
  }

  static std::uintmax_t FileSize(const std::filesystem::path& p) {
    std::error_code ec;
    return std::filesystem::file_size(p, ec);
  }
};

TEST_F(ExifThumbCTest_767, WriteFile_NoThumbnail_ReturnsZero_767) {
  Exiv2::ExifData exif;  // empty => no thumbnail expected
  const Exiv2::ExifThumbC thumbC(exif);

  const std::string base = UniqueBasePath("exiv2_thumb_not_present");
  const size_t written = thumbC.writeFile(base);

  EXPECT_EQ(0u, written);

  // If an extension is reported, ensure no such file was created as a side effect.
  const char* ext = nullptr;
  try {
    ext = thumbC.extension();
  } catch (...) {
    // extension() may throw depending on implementation; that's fine for this test.
    ext = nullptr;
  }
  if (ext && *ext) {
    EXPECT_FALSE(FileExists(std::filesystem::path(base + std::string(ext))));
  }
}

TEST_F(ExifThumbCTest_767, WriteFile_WithJpegThumbnail_CreatesFileAndReturnsSize_767) {
  Exiv2::ExifData exif;

  // Set up a JPEG thumbnail using public API (black-box friendly).
  Exiv2::ExifThumb thumb(exif);
  const auto jpeg = MinimalJpegBytes();
  ASSERT_NO_THROW(thumb.setJpegThumbnail(jpeg.data(), jpeg.size()));

  const Exiv2::ExifThumbC thumbC(exif);

  const std::string base = UniqueBasePath("exiv2_thumb_present");
  const std::string ext = std::string(thumbC.extension());

  const std::filesystem::path expectedPath = std::filesystem::path(base + ext);

  const size_t written = thumbC.writeFile(base);

  EXPECT_GT(written, 0u);
  EXPECT_TRUE(FileExists(expectedPath));
  EXPECT_EQ(static_cast<std::uintmax_t>(written), FileSize(expectedPath));
}

TEST_F(ExifThumbCTest_767, WriteFile_AppendsExtensionToProvidedPath_767) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumb thumb(exif);
  const auto jpeg = MinimalJpegBytes();
  ASSERT_NO_THROW(thumb.setJpegThumbnail(jpeg.data(), jpeg.size()));

  const Exiv2::ExifThumbC thumbC(exif);
  const std::string ext = std::string(thumbC.extension());

  const std::string baseWithExistingExt = UniqueBasePath("exiv2_thumb_base") + ext;
  const std::filesystem::path expectedPath = std::filesystem::path(baseWithExistingExt + ext);

  const size_t written = thumbC.writeFile(baseWithExistingExt);

  EXPECT_GT(written, 0u);
  EXPECT_TRUE(FileExists(expectedPath));
  EXPECT_EQ(static_cast<std::uintmax_t>(written), FileSize(expectedPath));
}

TEST_F(ExifThumbCTest_767, WriteFile_NonExistentDirectory_ThrowsOrReturnsZero_767) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumb thumb(exif);
  const auto jpeg = MinimalJpegBytes();
  ASSERT_NO_THROW(thumb.setJpegThumbnail(jpeg.data(), jpeg.size()));

  const Exiv2::ExifThumbC thumbC(exif);
  const std::string ext = std::string(thumbC.extension());

  const std::filesystem::path bogusDir =
      std::filesystem::path(UniqueBasePath("exiv2_thumb_missing_dir")) / "definitely_missing_subdir";
  const std::string base = (bogusDir / "thumb_out").string();
  const std::filesystem::path expectedPath = std::filesystem::path(base + ext);

  try {
    const size_t written = thumbC.writeFile(base);
    // Accept either a clean failure (0) or an exception; both are observable contract-wise.
    EXPECT_EQ(0u, written);
    EXPECT_FALSE(FileExists(expectedPath));
  } catch (...) {
    SUCCEED();
    EXPECT_FALSE(FileExists(expectedPath));
  }
}

TEST_F(ExifThumbCTest_767, WriteFile_EmptyJpegThumbnail_BufferEmpty_ReturnsZeroOrThrows_767) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumb thumb(exif);

  // Attempt to set an empty thumbnail via public API; behavior may be reject/throw or accept-but-empty.
  try {
    thumb.setJpegThumbnail(nullptr, 0);
  } catch (...) {
    // If setting fails, we still want to ensure writeFile on "no usable thumbnail" returns 0.
  }

  const Exiv2::ExifThumbC thumbC(exif);
  const std::string base = UniqueBasePath("exiv2_thumb_empty");

  try {
    const size_t written = thumbC.writeFile(base);
    EXPECT_EQ(0u, written);
  } catch (...) {
    SUCCEED();
  }
}

}  // namespace