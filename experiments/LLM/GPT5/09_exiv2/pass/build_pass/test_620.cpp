// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_writefile_620.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace Exiv2 {
// The implementation lives in basicio.cpp; declare the interface for the unit test TU.
size_t writeFile(const DataBuf& buf, const std::string& path);
}  // namespace Exiv2

namespace {

class WriteFileTest_620 : public ::testing::Test {
 protected:
  static std::filesystem::path TempDir() {
    return std::filesystem::temp_directory_path();
  }

  static std::filesystem::path UniquePath(const std::string& stem) {
    // Make a reasonably-unique filename without relying on platform-specific APIs.
    const auto base = TempDir() / (stem + "_" + std::to_string(::testing::UnitTest::GetInstance()->random_seed()));
    std::filesystem::path p = base;
    // If it already exists, append a counter.
    for (int i = 0; std::filesystem::exists(p) && i < 1000; ++i) {
      p = base;
      p += ("_" + std::to_string(i));
    }
    return p;
  }

  static void WriteBytesToDataBuf(Exiv2::DataBuf& buf, const std::vector<uint8_t>& bytes) {
    buf.alloc(bytes.size());
    for (size_t i = 0; i < bytes.size(); ++i) {
      buf.write_uint8(i, bytes[i]);
    }
  }

  static std::vector<uint8_t> ReadAllBytes(const std::filesystem::path& p) {
    std::ifstream ifs(p, std::ios::binary);
    std::vector<uint8_t> out;
    if (!ifs) return out;

    ifs.seekg(0, std::ios::end);
    const std::streamoff len = ifs.tellg();
    if (len < 0) return out;
    ifs.seekg(0, std::ios::beg);

    out.resize(static_cast<size_t>(len));
    if (len > 0) {
      ifs.read(reinterpret_cast<char*>(out.data()), len);
      if (!ifs) out.clear();
    }
    return out;
  }

  void TearDown() override {
    // Best-effort cleanup of created files.
    for (const auto& p : cleanup_) {
      std::error_code ec;
      std::filesystem::remove(p, ec);
    }
    cleanup_.clear();
  }

  void TrackForCleanup(const std::filesystem::path& p) { cleanup_.push_back(p); }

 private:
  std::vector<std::filesystem::path> cleanup_;
};

TEST_F(WriteFileTest_620, WritesNonEmptyBufferAndReturnsWrittenSize_620) {
  const std::filesystem::path out = UniquePath("exiv2_writeFile_620.bin");
  TrackForCleanup(out);

  const std::vector<uint8_t> bytes = {0x00, 0x11, 0x22, 0x33, 0xFE, 0xFF};
  Exiv2::DataBuf buf;
  WriteBytesToDataBuf(buf, bytes);

  const size_t written = Exiv2::writeFile(buf, out.string());
  EXPECT_EQ(written, bytes.size());

  ASSERT_TRUE(std::filesystem::exists(out));
  EXPECT_EQ(std::filesystem::file_size(out), bytes.size());

  const std::vector<uint8_t> onDisk = ReadAllBytes(out);
  EXPECT_EQ(onDisk, bytes);
}

TEST_F(WriteFileTest_620, WritesEmptyBufferCreatesEmptyFileAndReturnsZero_620) {
  const std::filesystem::path out = UniquePath("exiv2_writeFile_empty_620.bin");
  TrackForCleanup(out);

  Exiv2::DataBuf empty;  // default constructed; should be empty per interface.
  EXPECT_TRUE(empty.empty());
  EXPECT_EQ(empty.size(), 0u);

  const size_t written = Exiv2::writeFile(empty, out.string());
  EXPECT_EQ(written, 0u);

  ASSERT_TRUE(std::filesystem::exists(out));
  EXPECT_EQ(std::filesystem::file_size(out), 0u);

  const std::vector<uint8_t> onDisk = ReadAllBytes(out);
  EXPECT_TRUE(onDisk.empty());
}

TEST_F(WriteFileTest_620, OverwritesExistingFileContent_620) {
  const std::filesystem::path out = UniquePath("exiv2_writeFile_overwrite_620.bin");
  TrackForCleanup(out);

  // First write
  {
    const std::vector<uint8_t> bytes1 = {0xAA, 0xBB, 0xCC};
    Exiv2::DataBuf buf1;
    WriteBytesToDataBuf(buf1, bytes1);

    const size_t written1 = Exiv2::writeFile(buf1, out.string());
    EXPECT_EQ(written1, bytes1.size());
    ASSERT_TRUE(std::filesystem::exists(out));
    EXPECT_EQ(ReadAllBytes(out), bytes1);
  }

  // Second write (different content + size)
  {
    const std::vector<uint8_t> bytes2 = {0x10, 0x20, 0x30, 0x40, 0x50};
    Exiv2::DataBuf buf2;
    WriteBytesToDataBuf(buf2, bytes2);

    const size_t written2 = Exiv2::writeFile(buf2, out.string());
    EXPECT_EQ(written2, bytes2.size());
    ASSERT_TRUE(std::filesystem::exists(out));
    EXPECT_EQ(std::filesystem::file_size(out), bytes2.size());
    EXPECT_EQ(ReadAllBytes(out), bytes2);
  }
}

TEST_F(WriteFileTest_620, ThrowsErrorWhenPathCannotBeOpened_620) {
  // Use a clearly non-existent parent directory so open("wb") should fail.
  const std::filesystem::path badDir = UniquePath("exiv2_writeFile_no_such_dir_620");
  const std::filesystem::path out = badDir / "file.bin";

  const std::vector<uint8_t> bytes = {0x01, 0x02, 0x03};
  Exiv2::DataBuf buf;
  WriteBytesToDataBuf(buf, bytes);

  EXPECT_THROW((void)Exiv2::writeFile(buf, out.string()), Exiv2::Error);
}

TEST_F(WriteFileTest_620, ThrowsErrorWhenPathIsADirectory_620) {
  // Writing to a directory path should fail to open as a file.
  const std::filesystem::path dir = UniquePath("exiv2_writeFile_dir_620");
  std::error_code ec;
  ASSERT_TRUE(std::filesystem::create_directories(dir, ec)) << "Failed to create temp directory for test";
  // Cleanup directory at end.
  TrackForCleanup(dir);

  const std::vector<uint8_t> bytes = {0xDE, 0xAD, 0xBE, 0xEF};
  Exiv2::DataBuf buf;
  WriteBytesToDataBuf(buf, bytes);

  EXPECT_THROW((void)Exiv2::writeFile(buf, dir.string()), Exiv2::Error);
}

}  // namespace