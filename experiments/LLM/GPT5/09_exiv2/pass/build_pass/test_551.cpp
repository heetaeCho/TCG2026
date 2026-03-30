// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_fileio_setpath_551.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

class FileIoSetPathTest_551 : public ::testing::Test {
 protected:
  std::filesystem::path tempDir_;

  void SetUp() override {
    tempDir_ = std::filesystem::temp_directory_path() / "exiv2_fileio_setpath_test_551";
    std::error_code ec;
    std::filesystem::create_directories(tempDir_, ec);
  }

  void TearDown() override {
    std::error_code ec;
    std::filesystem::remove_all(tempDir_, ec);
  }

  std::filesystem::path makeFile(const std::string& name, const std::vector<unsigned char>& bytes) {
    auto p = tempDir_ / name;
    std::ofstream os(p, std::ios::binary);
    EXPECT_TRUE(os.good());
    os.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    os.close();
    return p;
  }
};

TEST_F(FileIoSetPathTest_551, UpdatesPathWithoutOpening_551) {
  const auto p1 = makeFile("a_551.bin", {0x01, 0x02, 0x03});
  const auto p2 = makeFile("b_551.bin", {0x10, 0x20});

  Exiv2::FileIo io(p1.string());
  EXPECT_EQ(io.path(), p1.string());

  io.setPath(p2.string());
  EXPECT_EQ(io.path(), p2.string());

  // setPath() must not implicitly open the file.
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoSetPathTest_551, ClosingIsObservableWhenChangingPathWhileOpen_551) {
  const auto p1 = makeFile("open_then_setpath_551_a.bin", {0xAA, 0xBB});
  const auto p2 = makeFile("open_then_setpath_551_b.bin", {0xCC, 0xDD, 0xEE});

  Exiv2::FileIo io(p1.string());
  ASSERT_EQ(io.open("rb"), 0);
  ASSERT_TRUE(io.isopen());

  io.setPath(p2.string());

  // Observable behavior from the public interface: path changes and stream is not open anymore.
  EXPECT_EQ(io.path(), p2.string());
  EXPECT_FALSE(io.isopen());

  // The instance should be usable after switching path: opening the new path should succeed.
  EXPECT_EQ(io.open("rb"), 0);
  EXPECT_TRUE(io.isopen());
  EXPECT_EQ(io.close(), 0);
}

TEST_F(FileIoSetPathTest_551, SetPathToSameValueStillLeavesObjectClosed_551) {
  const auto p1 = makeFile("same_path_551.bin", {0x00});

  Exiv2::FileIo io(p1.string());
  ASSERT_EQ(io.open("rb"), 0);
  ASSERT_TRUE(io.isopen());

  io.setPath(p1.string());

  // Even if the path is the same, setPath() calls close() per the provided implementation.
  EXPECT_EQ(io.path(), p1.string());
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoSetPathTest_551, SetPathToEmptyStringIsAcceptedAndObjectRemainsClosed_551) {
  const auto p1 = makeFile("empty_path_before_551.bin", {0x11, 0x22});

  Exiv2::FileIo io(p1.string());
  ASSERT_EQ(io.open("rb"), 0);
  ASSERT_TRUE(io.isopen());

  io.setPath(std::string{});

  EXPECT_EQ(io.path(), std::string{});
  EXPECT_FALSE(io.isopen());

  // Opening an empty path should not succeed (portable expectation: it must not become open).
  (void)io.open("rb");
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoSetPathTest_551, NonexistentPathCanBeSetAndOpenReadFails_551) {
  const auto p1 = makeFile("existing_551.bin", {0xDE, 0xAD, 0xBE, 0xEF});
  const auto missing = (tempDir_ / "does_not_exist_551.bin").string();

  Exiv2::FileIo io(p1.string());
  EXPECT_EQ(io.path(), p1.string());

  io.setPath(missing);
  EXPECT_EQ(io.path(), missing);
  EXPECT_FALSE(io.isopen());

  // For a missing file, opening in read-only mode should fail, and the object should remain not open.
  const int rc = io.open("rb");
  EXPECT_NE(rc, 0);
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoSetPathTest_551, VeryLongPathStringCanBeSet_551) {
  const auto p1 = makeFile("base_551.bin", {0x01});

  Exiv2::FileIo io(p1.string());
  EXPECT_EQ(io.path(), p1.string());

  // Build a long (possibly non-existent) path string.
  std::string longName(240, 'x');
  const std::string longPath = (tempDir_ / (longName + "_551.bin")).string();

  io.setPath(longPath);
  EXPECT_EQ(io.path(), longPath);
  EXPECT_FALSE(io.isopen());
}

}  // namespace