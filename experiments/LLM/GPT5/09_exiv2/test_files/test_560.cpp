// File: test_fileio_open_560.cpp
// Unit tests for Exiv2::FileIo::open(const std::string& mode)
//
// Constraints honored:
// - Treat FileIo as a black box (no reliance on internals).
// - Test only observable behavior via the public interface.
// - No private state access.
// - Cover normal, boundary, and error cases.

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {

fs::path MakeUniquePath(const std::string& stem) {
  const auto base = fs::temp_directory_path();
  // Use PID-like entropy via address + time-ish counter by relying on unique_path when available.
#if defined(__cpp_lib_filesystem) && (__cpp_lib_filesystem >= 201703L)
  // unique_path is not standard everywhere; guard by try/catch and fallback.
  try {
    // NOTE: Some libstdc++ versions provide fs::unique_path as an extension, not standard.
    // We'll fallback if not available at link time by not referencing it.
  } catch (...) {
  }
#endif
  // Simple portable fallback
  static size_t counter = 0;
  ++counter;
  return base / (stem + "_" + std::to_string(counter) + ".bin");
}

void WriteFileBytes(const fs::path& p, const std::string& bytes) {
  std::ofstream os(p, std::ios::binary);
  os.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  os.close();
}

}  // namespace

class FileIoOpenTest_560 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Best-effort cleanup (ignore errors).
    if (!paths_to_cleanup_.empty()) {
      for (const auto& p : paths_to_cleanup_) {
        std::error_code ec;
        fs::remove(p, ec);
      }
    }
    if (!dirs_to_cleanup_.empty()) {
      for (const auto& d : dirs_to_cleanup_) {
        std::error_code ec;
        fs::remove_all(d, ec);
      }
    }
  }

  fs::path TrackFile(const fs::path& p) {
    paths_to_cleanup_.push_back(p);
    return p;
  }

  fs::path TrackDir(const fs::path& p) {
    dirs_to_cleanup_.push_back(p);
    return p;
  }

 private:
    std::vector<fs::path> paths_to_cleanup_;
    std::vector<fs::path> dirs_to_cleanup_;
};

// Normal operation: opening an existing file for reading should succeed.
TEST_F(FileIoOpenTest_560, OpenExistingFileReadModeSucceeds_560) {
  const fs::path p = TrackFile(MakeUniquePath("exiv2_fileio_open_read"));
  WriteFileBytes(p, "abc");

  Exiv2::FileIo io(p.string());

  const int rc = io.open("rb");
  EXPECT_EQ(0, rc);
  EXPECT_TRUE(io.isopen());

  // Close should leave it not open (observable).
  (void)io.close();
  EXPECT_FALSE(io.isopen());
}

// Normal operation: opening for writing should succeed and create the file.
TEST_F(FileIoOpenTest_560, OpenWriteModeCreatesFile_560) {
  const fs::path p = TrackFile(MakeUniquePath("exiv2_fileio_open_write"));

  // Ensure it does not exist beforehand.
  std::error_code ec;
  fs::remove(p, ec);

  Exiv2::FileIo io(p.string());

  const int rc = io.open("wb");
  EXPECT_EQ(0, rc);
  EXPECT_TRUE(io.isopen());

  (void)io.close();

  // File existence is an observable side-effect of opening with a write/create mode.
  EXPECT_TRUE(fs::exists(p));
}

// Boundary/error: opening a non-existent file in read mode should fail.
TEST_F(FileIoOpenTest_560, OpenNonexistentFileReadModeFails_560) {
  const fs::path p = TrackFile(MakeUniquePath("exiv2_fileio_open_missing"));

  // Ensure it does not exist.
  std::error_code ec;
  fs::remove(p, ec);

  Exiv2::FileIo io(p.string());

  const int rc = io.open("rb");
  EXPECT_NE(0, rc);
  EXPECT_FALSE(io.isopen());
}

// Boundary/error: empty mode string should fail (fopen should fail => observable via return/isopen).
TEST_F(FileIoOpenTest_560, OpenWithEmptyModeFails_560) {
  const fs::path p = TrackFile(MakeUniquePath("exiv2_fileio_open_empty_mode"));
  WriteFileBytes(p, "data");

  Exiv2::FileIo io(p.string());

  const int rc = io.open("");
  EXPECT_NE(0, rc);
  EXPECT_FALSE(io.isopen());
}

// Error case: trying to open a directory as a file for reading should fail.
TEST_F(FileIoOpenTest_560, OpenDirectoryPathFails_560) {
  const fs::path d = TrackDir(fs::temp_directory_path() / "exiv2_fileio_open_dir_560");
  std::error_code ec;
  fs::create_directories(d, ec);
  ASSERT_TRUE(fs::exists(d));

  Exiv2::FileIo io(d.string());

  const int rc = io.open("rb");
  EXPECT_NE(0, rc);
  EXPECT_FALSE(io.isopen());
}

// Normal/boundary: opening twice should be safe; second open should reflect the latest request.
// We only verify observable outcomes: no crash, and isopen is true when open succeeds.
TEST_F(FileIoOpenTest_560, OpenTwiceClosesPreviousAndReopens_560) {
  const fs::path p = TrackFile(MakeUniquePath("exiv2_fileio_open_twice"));
  WriteFileBytes(p, "payload");

  Exiv2::FileIo io(p.string());

  const int rc1 = io.open("rb");
  ASSERT_EQ(0, rc1);
  ASSERT_TRUE(io.isopen());

  const int rc2 = io.open("rb");  // Reopen same mode; should still succeed.
  EXPECT_EQ(0, rc2);
  EXPECT_TRUE(io.isopen());

  (void)io.close();
  EXPECT_FALSE(io.isopen());
}