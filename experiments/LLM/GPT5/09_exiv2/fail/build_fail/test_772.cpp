// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifthum_setjpegthumbnail_path_772.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/exifdata.hpp>
#include <exiv2/error.hpp>

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

class ExifThumbPathOverloadTest_772 : public ::testing::Test {
 protected:
  ExifThumbPathOverloadTest_772() : exifData_(), thumb_(exifData_) {}

  static fs::path MakeUniquePath(const std::string& stem) {
    const auto base = fs::temp_directory_path();
    // Keep it simple and deterministic-ish: include PID-ish via address.
    std::string name = stem + "_" + std::to_string(reinterpret_cast<std::uintptr_t>(&stem)) + ".jpg";
    return base / name;
  }

  static void WriteBinaryFile(const fs::path& p, const std::vector<uint8_t>& bytes) {
    std::ofstream os(p, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(os.is_open()) << "Failed to open temp file for writing: " << p.string();
    if (!bytes.empty()) {
      os.write(reinterpret_cast<const char*>(bytes.data()),
               static_cast<std::streamsize>(bytes.size()));
    }
    ASSERT_TRUE(os.good()) << "Failed while writing temp file: " << p.string();
    os.close();
  }

  static std::vector<uint8_t> MinimalJpegBytes() {
    // Minimal JPEG markers (SOI + EOI). Kept intentionally tiny.
    return {0xFF, 0xD8, 0xFF, 0xD9};
  }

  Exiv2::ExifData exifData_;
  Exiv2::ExifThumb thumb_;
};

TEST_F(ExifThumbPathOverloadTest_772, SetJpegThumbnailWithValidFileDoesNotThrow_772) {
  const fs::path p = MakeUniquePath("exiv2_exifthum_772_valid");
  WriteBinaryFile(p, MinimalJpegBytes());

  EXPECT_NO_THROW(thumb_.setJpegThumbnail(p.string()));

  std::error_code ec;
  fs::remove(p, ec);
}

TEST_F(ExifThumbPathOverloadTest_772, SetJpegThumbnailWithMissingFileThrows_772) {
  const fs::path p = MakeUniquePath("exiv2_exifthum_772_missing");
  std::error_code ec;
  fs::remove(p, ec);  // ensure it doesn't exist

  EXPECT_THROW(thumb_.setJpegThumbnail(p.string()), Exiv2::Error);
}

TEST_F(ExifThumbPathOverloadTest_772, SetJpegThumbnailWithEmptyPathThrows_772) {
  // Observable behavior: readFile(path) may throw; empty path should be invalid on all platforms.
  EXPECT_THROW(thumb_.setJpegThumbnail(std::string{}), Exiv2::Error);
}

TEST_F(ExifThumbPathOverloadTest_772, SetJpegThumbnailWithDirectoryPathThrows_772) {
  const fs::path dir = fs::temp_directory_path();  // definitely a directory
  EXPECT_THROW(thumb_.setJpegThumbnail(dir.string()), Exiv2::Error);
}

TEST_F(ExifThumbPathOverloadTest_772, SetJpegThumbnailCanBeCalledTwiceWithDifferentFiles_772) {
  const fs::path p1 = MakeUniquePath("exiv2_exifthum_772_twice_1");
  const fs::path p2 = MakeUniquePath("exiv2_exifthum_772_twice_2");
  WriteBinaryFile(p1, MinimalJpegBytes());
  WriteBinaryFile(p2, MinimalJpegBytes());

  EXPECT_NO_THROW(thumb_.setJpegThumbnail(p1.string()));
  EXPECT_NO_THROW(thumb_.setJpegThumbnail(p2.string()));

  std::error_code ec;
  fs::remove(p1, ec);
  fs::remove(p2, ec);
}

TEST_F(ExifThumbPathOverloadTest_772, EraseAfterSetDoesNotThrow_772) {
  const fs::path p = MakeUniquePath("exiv2_exifthum_772_erase");
  WriteBinaryFile(p, MinimalJpegBytes());

  ASSERT_NO_THROW(thumb_.setJpegThumbnail(p.string()));
  EXPECT_NO_THROW(thumb_.erase());

  std::error_code ec;
  fs::remove(p, ec);
}

TEST_F(ExifThumbPathOverloadTest_772, EraseWithoutPriorSetDoesNotThrow_772) {
  // Boundary/robustness: calling erase on a fresh ExifThumb should be safe if supported.
  EXPECT_NO_THROW(thumb_.erase());
}

}  // namespace