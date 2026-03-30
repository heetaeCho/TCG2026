// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_orfimage_factory_1555.cpp
//
// Unit tests for Exiv2::newOrfInstance factory (./src/orfimage.cpp)
//
// Constraints honored:
// - Treat implementation as black box: only assert on observable return values / public API.
// - No access to private state.
// - No re-implementation/inference of internal logic.
// - Use real BasicIo implementations; no mocking of internals.

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/orfimage.hpp>

#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#if __has_include(<filesystem>)
#include <filesystem>
#define EXIV2_TEST_HAS_FILESYSTEM 1
#else
#define EXIV2_TEST_HAS_FILESYSTEM 0
#endif

namespace {

class OrfImageFactoryTest_1555 : public ::testing::Test {
 protected:
  static bool FileExists(const std::string& path) {
    std::ifstream ifs(path, std::ios::binary);
    return ifs.good();
  }

  // Best-effort: try common Exiv2 test-data locations and (if available) scan a few directories for *.orf.
  static std::string FindAnyOrfSamplePath() {
    const std::vector<std::string> candidates = {
        // Common layouts used by Exiv2 test trees
        "tests/data/test.orf",
        "test/data/test.orf",
        "data/test.orf",
        "tests/data/1.orf",
        "test/data/1.orf",
        "tests/data/orf/1.orf",
        "test/data/orf/1.orf",
        "tests/data/exiv2.orf",
        "test/data/exiv2.orf",
    };

    for (const auto& p : candidates) {
      if (FileExists(p)) return p;
    }

#if EXIV2_TEST_HAS_FILESYSTEM
    namespace fs = std::filesystem;
    const std::vector<std::string> dirs = {
        "tests/data",
        "test/data",
        "data",
        "tests/data/orf",
        "test/data/orf",
    };

    for (const auto& d : dirs) {
      std::error_code ec;
      if (!fs::exists(d, ec) || ec) continue;

      for (const auto& entry : fs::directory_iterator(d, ec)) {
        if (ec) break;
        if (!entry.is_regular_file(ec) || ec) continue;

        const auto ext = entry.path().extension().string();
        if (ext == ".orf" || ext == ".ORF") {
          const auto path = entry.path().string();
          if (FileExists(path)) return path;
        }
      }
    }
#endif

    return {};
  }
};

TEST_F(OrfImageFactoryTest_1555, EmptyMemIoReturnsNullWhenCreateFalse_1555) {
  // Boundary: empty buffer.
  std::vector<Exiv2::byte> bytes;
  auto io = std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size());

  ASSERT_TRUE(io);  // sanity
  Exiv2::Image::UniquePtr image = Exiv2::newOrfInstance(std::move(io), /*create=*/false);

  // Observable behavior from factory: nullptr when resulting image isn't "good".
  EXPECT_EQ(image, nullptr);
}

TEST_F(OrfImageFactoryTest_1555, EmptyMemIoReturnsNullWhenCreateTrue_1555) {
  // Boundary: empty buffer with create=true should still be safe to call; result is observable via pointer.
  std::vector<Exiv2::byte> bytes;
  auto io = std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size());

  ASSERT_TRUE(io);
  Exiv2::Image::UniquePtr image = Exiv2::newOrfInstance(std::move(io), /*create=*/true);

  EXPECT_EQ(image, nullptr);
}

TEST_F(OrfImageFactoryTest_1555, SmallGarbageMemIoReturnsNull_1555) {
  // Boundary: small non-empty buffer (garbage).
  std::vector<Exiv2::byte> bytes(16, static_cast<Exiv2::byte>(0xFF));
  auto io = std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size());

  ASSERT_TRUE(io);
  Exiv2::Image::UniquePtr image = Exiv2::newOrfInstance(std::move(io), /*create=*/false);

  EXPECT_EQ(image, nullptr);
}

TEST_F(OrfImageFactoryTest_1555, ValidOrfSampleFileCreatesGoodImageOrSkips_1555) {
  const std::string sample = FindAnyOrfSamplePath();
  if (sample.empty()) {
    GTEST_SKIP() << "No .orf sample file found in common test-data locations; skipping.";
  }

  auto io = std::make_unique<Exiv2::FileIo>(sample);
  ASSERT_TRUE(io);

  Exiv2::Image::UniquePtr image = Exiv2::newOrfInstance(std::move(io), /*create=*/false);

  // Factory contract: returns nullptr if not good; otherwise non-null.
  ASSERT_NE(image, nullptr);

  // Observable behavior through public API.
  EXPECT_TRUE(image->good());

  // Additional light-touch observable checks (do not assume specific strings).
  const std::string mime = image->mimeType();
  EXPECT_FALSE(mime.empty());
}

}  // namespace