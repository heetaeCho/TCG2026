// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 552
//
// Unit tests for Exiv2::FileIo::write(const byte*, size_t)
//
// Constraints respected:
// - Treat implementation as black box (no private state access)
// - Test only via public interface (open/close/write/read/size/tell/isopen/path)
// - No mocking of internals

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;

static fs::path MakeTempPath(const std::string& prefix) {
  const fs::path dir = fs::temp_directory_path();
  // Good-enough uniqueness for unit tests.
  const auto salt = std::to_string(::getpid()) + "_" + std::to_string(std::rand());
  return dir / (prefix + "_" + salt + ".bin");
}

static void WriteAllBytesWithStdFile(const fs::path& p, const std::vector<Exiv2::byte>& bytes) {
  std::FILE* f = std::fopen(p.string().c_str(), "wb");
  ASSERT_NE(f, nullptr);
  if (!bytes.empty()) {
    ASSERT_EQ(std::fwrite(bytes.data(), 1, bytes.size(), f), bytes.size());
  }
  std::fclose(f);
}

static std::vector<Exiv2::byte> ReadAllBytesWithStdFile(const fs::path& p) {
  std::ifstream in(p, std::ios::binary);
  std::vector<Exiv2::byte> out;
  if (!in.is_open()) return out;

  in.seekg(0, std::ios::end);
  const std::streamoff len = in.tellg();
  in.seekg(0, std::ios::beg);

  if (len > 0) {
    out.resize(static_cast<size_t>(len));
    in.read(reinterpret_cast<char*>(out.data()), len);
  }
  return out;
}

class FileIoWriteTest_552 : public ::testing::Test {
 protected:
  void SetUp() override {
    path_ = MakeTempPath("exiv2_fileio_write_552");
  }

  void TearDown() override {
    // Best-effort cleanup.
    std::error_code ec;
    fs::remove(path_, ec);
  }

  fs::path path_;
};

}  // namespace

TEST_F(FileIoWriteTest_552, WriteAfterOpenWritesAllBytes_552) {
  Exiv2::FileIo io(path_.string());

  ASSERT_EQ(io.open("wb+"), 0);
  ASSERT_TRUE(io.isopen());

  const std::vector<Exiv2::byte> payload = {
      0x00, 0x01, 0x02, 0x7F, 0x80, 0xFE, 0xFF, 0x11, 0x22, 0x33};
  const size_t written = io.write(payload.data(), payload.size());

  EXPECT_EQ(written, payload.size());
  EXPECT_EQ(io.tell(), payload.size());
  EXPECT_EQ(io.size(), payload.size());

  ASSERT_EQ(io.close(), 0);

  const auto onDisk = ReadAllBytesWithStdFile(path_);
  EXPECT_EQ(onDisk, payload);
}

TEST_F(FileIoWriteTest_552, WriteZeroCountReturnsZeroAndDoesNotAdvanceTell_552) {
  Exiv2::FileIo io(path_.string());

  ASSERT_EQ(io.open("wb+"), 0);
  ASSERT_TRUE(io.isopen());

  const std::vector<Exiv2::byte> payload = {0xAA, 0xBB, 0xCC};
  ASSERT_EQ(io.write(payload.data(), payload.size()), payload.size());
  const size_t beforeTell = io.tell();
  const size_t beforeSize = io.size();

  // Boundary: wcount == 0. (Also safe even if data pointer were null.)
  const size_t writtenZero = io.write(payload.data(), 0);

  EXPECT_EQ(writtenZero, 0u);
  EXPECT_EQ(io.tell(), beforeTell);
  EXPECT_EQ(io.size(), beforeSize);

  ASSERT_EQ(io.close(), 0);
}

TEST_F(FileIoWriteTest_552, WriteOnReadOnlyOpenReturnsZeroAndKeepsFileUnchanged_552) {
  // Prepare an existing file with known contents.
  const std::vector<Exiv2::byte> initial = {0x10, 0x20, 0x30, 0x40, 0x50};
  WriteAllBytesWithStdFile(path_, initial);

  Exiv2::FileIo io(path_.string());

  ASSERT_EQ(io.open("rb"), 0);
  ASSERT_TRUE(io.isopen());

  const std::vector<Exiv2::byte> attempt = {0xDE, 0xAD, 0xBE, 0xEF};
  const size_t written = io.write(attempt.data(), attempt.size());

  // Observable error case: when opened read-only, writing should not succeed.
  EXPECT_EQ(written, 0u);

  ASSERT_EQ(io.close(), 0);

  const auto after = ReadAllBytesWithStdFile(path_);
  EXPECT_EQ(after, initial);
}

TEST_F(FileIoWriteTest_552, MultipleWritesAdvanceTellAndPersistConcatenatedContent_552) {
  Exiv2::FileIo io(path_.string());

  ASSERT_EQ(io.open("wb+"), 0);
  ASSERT_TRUE(io.isopen());

  const std::vector<Exiv2::byte> a = {0x01, 0x02, 0x03};
  const std::vector<Exiv2::byte> b = {0x00, 0xFF, 0x7E, 0x7F};

  ASSERT_EQ(io.write(a.data(), a.size()), a.size());
  EXPECT_EQ(io.tell(), a.size());

  ASSERT_EQ(io.write(b.data(), b.size()), b.size());
  EXPECT_EQ(io.tell(), a.size() + b.size());
  EXPECT_EQ(io.size(), a.size() + b.size());

  ASSERT_EQ(io.close(), 0);

  std::vector<Exiv2::byte> expected;
  expected.insert(expected.end(), a.begin(), a.end());
  expected.insert(expected.end(), b.begin(), b.end());

  const auto onDisk = ReadAllBytesWithStdFile(path_);
  EXPECT_EQ(onDisk, expected);
}