// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 549
//
// Unit tests for Exiv2::FileIo::munmap()
// File: ./TestProjects/exiv2/src/basicio.cpp (partial)
// Interface: exiv2/basicio.hpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;

class FileIoMunmapTest_549 : public ::testing::Test {
 protected:
  void SetUp() override {
    tempPath_ = MakeTempFilePath();
    WriteFile(tempPath_, InitialBytes());
  }

  void TearDown() override {
    // Best-effort cleanup
    std::error_code ec;
    fs::remove(tempPath_, ec);
  }

  static fs::path MakeTempFilePath() {
    const auto base = fs::temp_directory_path();
    // Use a reasonably unique name without relying on randomness APIs.
    const auto name =
        std::string("exiv2_fileio_munmap_test_549_") + std::to_string(::getpid()) + ".bin";
    return base / name;
  }

  static std::vector<unsigned char> InitialBytes() {
    // Non-empty file so mmap has something to map.
    return std::vector<unsigned char>{0x10, 0x20, 0x30, 0x40, 0x50};
  }

  static void WriteFile(const fs::path& p, const std::vector<unsigned char>& bytes) {
    std::ofstream ofs(p, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(ofs.is_open());
    ofs.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    ofs.close();
  }

  // Tries a few common open modes, since the exact accepted strings are not part of this snippet.
  static int OpenBestEffort(Exiv2::FileIo& io, bool wantWrite) {
    if (wantWrite) {
      // Try read/write binary first.
      int rc = io.open("r+b");
      if (rc == 0) return rc;
      rc = io.open("rb+");
      if (rc == 0) return rc;
      // Fall back to default open (may open read/write depending on Exiv2 build).
      return io.open();
    }

    int rc = io.open("rb");
    if (rc == 0) return rc;
    return io.open();
  }

  fs::path tempPath_;
};

TEST_F(FileIoMunmapTest_549, MunmapWithoutPriorMmapReturnsZero_549) {
  Exiv2::FileIo io(tempPath_.string());
  ASSERT_EQ(OpenBestEffort(io, /*wantWrite=*/false), 0);

  // Observable behavior: munmap() returns an int status.
  EXPECT_EQ(io.munmap(), 0);

  EXPECT_EQ(io.close(), 0);
}

TEST_F(FileIoMunmapTest_549, MunmapAfterReadOnlyMmapIsSuccessfulAndIdempotent_549) {
  Exiv2::FileIo io(tempPath_.string());
  ASSERT_EQ(OpenBestEffort(io, /*wantWrite=*/false), 0);

  Exiv2::byte* mapped = io.mmap(/*isWriteable=*/false);
  if (mapped == nullptr) {
    // If mmap is unsupported/disabled in this build, we can only validate munmap() on the empty state.
    EXPECT_EQ(io.munmap(), 0);
    (void)io.close();
    GTEST_SKIP() << "mmap() returned nullptr in this build/environment";
  }

  EXPECT_EQ(io.munmap(), 0);

  // Boundary/robustness: calling munmap() again should not crash and should return a defined status.
  EXPECT_EQ(io.munmap(), 0);

  EXPECT_EQ(io.close(), 0);
}

TEST_F(FileIoMunmapTest_549, MunmapAfterWriteableMmapAllowsSubsequentIoOperations_549) {
  Exiv2::FileIo io(tempPath_.string());
  ASSERT_EQ(OpenBestEffort(io, /*wantWrite=*/true), 0);

  Exiv2::byte* mapped = io.mmap(/*isWriteable=*/true);
  if (mapped == nullptr) {
    // If mmap is unsupported/disabled, we cannot verify writeable mapping.
    (void)io.close();
    GTEST_SKIP() << "mmap(true) returned nullptr in this build/environment";
  }

  // Perform a minimal write to the mapped area (do not assume persistence semantics).
  // This is just to exercise the writeable-mapping path before munmap().
  mapped[0] = static_cast<Exiv2::byte>(mapped[0] ^ 0xFF);

  EXPECT_EQ(io.munmap(), 0);

  // Observable follow-up behavior: basic operations should remain usable after munmap().
  // (We do not assert on internal mode switching; only that calls succeed and return sensible results.)
  EXPECT_EQ(io.seek(0, Exiv2::BasicIo::beg), 0);

  std::vector<Exiv2::byte> buf(1);
  const size_t n = io.read(buf.data(), buf.size());
  EXPECT_EQ(n, 1u);

  EXPECT_EQ(io.close(), 0);
}

}  // namespace