// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::ExifThumbC (black-box)
//
// File: test_exifthumbc_766.cpp
//
// Constraints respected:
// - No re-implementation / no inference of internal logic.
// - Tests only observable behavior via public API.
// - No private state access.
// - Uses real Exiv2 I/O where needed; no mocking of internal statics.
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#endif

namespace {

#if defined(fs)
static fs::path TempFilePath(const std::string& base) {
  fs::path dir = fs::temp_directory_path();
  fs::path p = dir / base;
  // Make it a bit more unique.
  p += "_" + std::to_string(::getpid()) + ".bin";
  return p;
}
#endif

static bool FileExists(const std::string& path) {
  std::ifstream ifs(path.c_str(), std::ios::binary);
  return ifs.good();
}

static std::size_t FileSize(const std::string& path) {
  std::ifstream ifs(path.c_str(), std::ios::binary | std::ios::ate);
  if (!ifs.good()) return 0;
  return static_cast<std::size_t>(ifs.tellg());
}

// ---- DataBuf "introspection" helpers (robust across minor API variations) ----
template <typename T>
auto DataBufSizeImpl(const T& b, int) -> decltype(b.size_, std::size_t{}) {
  return static_cast<std::size_t>(b.size_);
}
template <typename T>
auto DataBufSizeImpl(const T& b, long) -> decltype(b.size(), std::size_t{}) {
  return static_cast<std::size_t>(b.size());
}
template <typename T>
std::size_t DataBufSize(const T& b) {
  return DataBufSizeImpl(b, 0);
}

template <typename T>
auto DataBufDataImpl(const T& b, int) -> decltype(b.pData_, (const unsigned char*)nullptr) {
  return reinterpret_cast<const unsigned char*>(b.pData_);
}
template <typename T>
auto DataBufDataImpl(const T& b, long) -> decltype(b.data(), (const unsigned char*)nullptr) {
  return reinterpret_cast<const unsigned char*>(b.data());
}
template <typename T>
const unsigned char* DataBufData(const T& b) {
  return DataBufDataImpl(b, 0);
}

// Try to locate a thumbnail-bearing test image from common Exiv2 test-data names.
// If none exist in the working tree, we skip thumbnail-present tests.
static std::string FindExistingTestImagePath() {
  const std::vector<std::string> candidates = {
      // common repo layouts
      "test/data/exiv2-bug884.jpg",
      "test/data/exiv2-gc.jpg",
      "test/data/exiv2-kodak-dc210.jpg",
      "tests/data/exiv2-bug884.jpg",
      "tests/data/exiv2-gc.jpg",
      "tests/data/exiv2-kodak-dc210.jpg",
      "data/exiv2-bug884.jpg",
      "data/exiv2-gc.jpg",
      "data/exiv2-kodak-dc210.jpg",
      // generic fallbacks
      "test/data/thumbnail.jpg",
      "tests/data/thumbnail.jpg",
      "data/thumbnail.jpg",
  };

  for (const auto& c : candidates) {
    if (FileExists(c)) return c;
  }
  return {};
}

static Exiv2::ExifData ReadExifDataFromImageOrSkip() {
  const std::string path = FindExistingTestImagePath();
  if (path.empty()) {
    GTEST_SKIP() << "No known test image found in working tree; skipping thumbnail-present tests.";
  }

  Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(path);
  ASSERT_TRUE(image.get() != nullptr) << "Failed to open candidate image: " << path;

  image->readMetadata();
  return image->exifData();  // copy out (keeps test self-contained)
}

static void ExpectWriteFileFailsGracefully(const Exiv2::ExifThumbC& thumb, const std::string& outPath) {
  // Observable behavior requirement: it either reports failure via return value
  // or via an exception. In either case, it must not leave a non-empty file.
  std::size_t n = 0;
  bool threw = false;
  try {
    n = thumb.writeFile(outPath);
  } catch (const std::exception&) {
    threw = true;
  }

  if (!threw) {
    EXPECT_EQ(n, 0u);
  }

  if (FileExists(outPath)) {
    EXPECT_EQ(FileSize(outPath), 0u);
    (void)std::remove(outPath.c_str());
  }
}

}  // namespace

// ============================================================================
// TESTS
// ============================================================================

class ExifThumbCTest_766 : public ::testing::Test {};

// Normal / boundary: empty ExifData -> no thumbnail -> copy() returns empty buffer.
TEST_F(ExifThumbCTest_766, CopyWithEmptyExifDataReturnsEmptyBuf_766) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumbC thumb(exif);

  const Exiv2::DataBuf buf = thumb.copy();

  EXPECT_EQ(DataBufSize(buf), 0u);
  // Data pointer may be nullptr or non-null depending on implementation; size==0 is the key observable.
}

// Boundary: calling copy() multiple times should be stable (doesn't crash; empty stays empty).
TEST_F(ExifThumbCTest_766, CopyIsRepeatableForNoThumbnail_766) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumbC thumb(exif);

  const Exiv2::DataBuf a = thumb.copy();
  const Exiv2::DataBuf b = thumb.copy();

  EXPECT_EQ(DataBufSize(a), 0u);
  EXPECT_EQ(DataBufSize(b), 0u);
}

// Error case (observable): writeFile when there is no thumbnail should fail gracefully.
TEST_F(ExifThumbCTest_766, WriteFileWithNoThumbnailFailsGracefully_766) {
  Exiv2::ExifData exif;
  Exiv2::ExifThumbC thumb(exif);

#if defined(fs)
  const std::string outPath = TempFilePath("exiv2_exifthubmc_no_thumb").string();
#else
  const std::string outPath = "exiv2_exifthubmc_no_thumb_766.bin";
#endif

  // Ensure it doesn't exist before.
  (void)std::remove(outPath.c_str());

  ExpectWriteFileFailsGracefully(thumb, outPath);
}

// Normal operation (if test data available): copy() returns non-empty thumbnail.
TEST_F(ExifThumbCTest_766, CopyFromImageWithThumbnailReturnsNonEmptyBuf_766) {
  Exiv2::ExifData exif = ReadExifDataFromImageOrSkip();
  Exiv2::ExifThumbC thumb(exif);

  const Exiv2::DataBuf buf = thumb.copy();

  EXPECT_GT(DataBufSize(buf), 0u);
  EXPECT_NE(DataBufData(buf), nullptr);
}

// Normal operation: mimeType() and extension() are usable when a thumbnail exists.
// (We only assert minimal observables: non-null and non-empty strings.)
TEST_F(ExifThumbCTest_766, MimeTypeAndExtensionNonEmptyWhenThumbnailExists_766) {
  Exiv2::ExifData exif = ReadExifDataFromImageOrSkip();
  Exiv2::ExifThumbC thumb(exif);

  const char* mt = nullptr;
  const char* ext = nullptr;

  ASSERT_NO_THROW(mt = thumb.mimeType());
  ASSERT_NO_THROW(ext = thumb.extension());

  ASSERT_NE(mt, nullptr);
  ASSERT_NE(ext, nullptr);

  EXPECT_NE(std::string(mt).size(), 0u);
  EXPECT_NE(std::string(ext).size(), 0u);
}

// Normal + boundary: writeFile writes >0 bytes and file size matches returned size.
TEST_F(ExifThumbCTest_766, WriteFileWritesThumbnailAndReturnsByteCount_766) {
  Exiv2::ExifData exif = ReadExifDataFromImageOrSkip();
  Exiv2::ExifThumbC thumb(exif);

#if defined(fs)
  const std::string outPath = TempFilePath("exiv2_exifthubmc_thumb").string();
#else
  const std::string outPath = "exiv2_exifthubmc_thumb_766.bin";
#endif

  (void)std::remove(outPath.c_str());

  std::size_t written = 0;
  ASSERT_NO_THROW(written = thumb.writeFile(outPath));

  EXPECT_GT(written, 0u);
  ASSERT_TRUE(FileExists(outPath));
  EXPECT_EQ(FileSize(outPath), written);

  (void)std::remove(outPath.c_str());
}

// Error case: writeFile to a path in a non-existent directory should fail gracefully.
TEST_F(ExifThumbCTest_766, WriteFileToNonexistentDirectoryFailsGracefully_766) {
  Exiv2::ExifData exif = ReadExifDataFromImageOrSkip();
  Exiv2::ExifThumbC thumb(exif);

#if defined(fs)
  fs::path bogusDir = fs::temp_directory_path() / "exiv2_nonexistent_dir_766" / "nested";
  fs::path out = bogusDir / "thumb.bin";
  const std::string outPath = out.string();
#else
  // Best-effort bogus path on non-filesystem builds.
  const std::string outPath = "this_dir_should_not_exist_766/nested/thumb.bin";
#endif

  ExpectWriteFileFailsGracefully(thumb, outPath);
}