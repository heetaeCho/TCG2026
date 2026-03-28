// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 567
//
// Unit tests for Exiv2::FileIo::eof() based strictly on the public interface.
// We treat the implementation as a black box and only validate observable behavior.

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;

static fs::path makeUniqueTempPath(const std::string& stem) {
  const auto base = fs::temp_directory_path();
  // Good-enough uniqueness for unit tests.
  const auto unique =
      stem + "_" + std::to_string(static_cast<unsigned long long>(::getpid())) + "_" +
      std::to_string(static_cast<unsigned long long>(std::chrono::high_resolution_clock::now()
                                                         .time_since_epoch()
                                                         .count()));
  return base / (unique + ".bin");
}

static void writeFile(const fs::path& p, const std::vector<unsigned char>& bytes) {
  std::ofstream os(p, std::ios::binary | std::ios::trunc);
  ASSERT_TRUE(os.is_open()) << "Failed to create temp file: " << p.string();
  if (!bytes.empty()) {
    os.write(reinterpret_cast<const char*>(bytes.data()),
             static_cast<std::streamsize>(bytes.size()));
  }
  os.close();
  ASSERT_TRUE(os.good()) << "Failed writing temp file: " << p.string();
}

class FileIoEofTest_567 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (!tmp_.empty()) {
      std::error_code ec;
      fs::remove(tmp_, ec);
    }
  }

  fs::path tmp_;
};

}  // namespace

TEST_F(FileIoEofTest_567, NonEmptyFile_EofBecomesTrueOnlyAfterReadPastEnd_567) {
  tmp_ = makeUniqueTempPath("exiv2_fileio_eof_nonempty_567");
  const std::vector<unsigned char> payload = {0x10, 0x20, 0x30, 0x40, 0x55};
  writeFile(tmp_, payload);

  Exiv2::FileIo io(tmp_.string());
  ASSERT_EQ(0, io.open()) << "open() should succeed for an existing file";

  // Before any read attempt, EOF should be false.
  EXPECT_FALSE(io.eof());

  // Read exactly file size via getb(). While bytes are successfully returned,
  // eof() should remain false (C stdio feof is set only after reading past end).
  for (size_t i = 0; i < payload.size(); ++i) {
    const int b = io.getb();
    ASSERT_GE(b, 0) << "Expected a byte while within file length, index=" << i;
    EXPECT_FALSE(io.eof()) << "EOF should not be set while consuming last byte";
  }

  // One more read attempt should fail and EOF should become true.
  const int b_after = io.getb();
  EXPECT_LT(b_after, 0) << "Expected getb() to indicate end-of-file after reading past end";
  EXPECT_TRUE(io.eof());

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoEofTest_567, EmptyFile_EofBecomesTrueAfterFirstReadAttempt_567) {
  tmp_ = makeUniqueTempPath("exiv2_fileio_eof_empty_567");
  writeFile(tmp_, {});

  Exiv2::FileIo io(tmp_.string());
  ASSERT_EQ(0, io.open()) << "open() should succeed for an existing empty file";

  EXPECT_FALSE(io.eof()) << "EOF should be false before any read attempt";

  const int b = io.getb();
  EXPECT_LT(b, 0) << "Expected getb() to indicate end-of-file for empty file";
  EXPECT_TRUE(io.eof()) << "EOF should be true after attempting to read from empty file";

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoEofTest_567, ReadZeroBytes_DoesNotSetEof_567) {
  tmp_ = makeUniqueTempPath("exiv2_fileio_eof_read0_567");
  const std::vector<unsigned char> payload = {0xAB, 0xCD, 0xEF};
  writeFile(tmp_, payload);

  Exiv2::FileIo io(tmp_.string());
  ASSERT_EQ(0, io.open());

  EXPECT_FALSE(io.eof());

  Exiv2::byte buf[4] = {};
  const size_t n = io.read(buf, 0);
  EXPECT_EQ(0u, n) << "Reading 0 bytes should return 0";
  EXPECT_FALSE(io.eof()) << "EOF should not be set by a 0-byte read";

  EXPECT_EQ(0, io.close());
}

TEST_F(FileIoEofTest_567, EofIsIdempotentAfterEndOfFileReached_567) {
  tmp_ = makeUniqueTempPath("exiv2_fileio_eof_idempotent_567");
  const std::vector<unsigned char> payload = {0x01};
  writeFile(tmp_, payload);

  Exiv2::FileIo io(tmp_.string());
  ASSERT_EQ(0, io.open());

  // Consume the single byte.
  ASSERT_GE(io.getb(), 0);
  // Read past end to set EOF.
  ASSERT_LT(io.getb(), 0);
  ASSERT_TRUE(io.eof());

  // Multiple eof() calls should consistently report EOF.
  EXPECT_TRUE(io.eof());
  EXPECT_TRUE(io.eof());
  EXPECT_TRUE(io.eof());

  EXPECT_EQ(0, io.close());
}