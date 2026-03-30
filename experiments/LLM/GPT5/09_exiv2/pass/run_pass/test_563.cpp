// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_fileio_read_563.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

class FileIoReadTest_563 : public ::testing::Test {
 protected:
  static std::filesystem::path MakeTempPath(const std::string& stem) {
    const auto base = std::filesystem::temp_directory_path();
    // Keep it simple and deterministic-ish; collisions are unlikely in unit test runs.
    return base / (stem + "_563.bin");
  }

  static void WriteFile(const std::filesystem::path& p, const std::vector<uint8_t>& bytes) {
    std::ofstream os(p, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(os.good());
    if (!bytes.empty()) {
      os.write(reinterpret_cast<const char*>(bytes.data()),
               static_cast<std::streamsize>(bytes.size()));
    }
    ASSERT_TRUE(os.good());
    os.close();
  }

  static void ExpectErrorCode(const Exiv2::Error& e, Exiv2::ErrorCode code) {
    // Exiv2::Error typically exposes code() returning ErrorCode (or int convertible).
    // This check stays on the public interface (no private state).
    EXPECT_EQ(static_cast<int>(e.code()), static_cast<int>(code));
  }
};

TEST_F(FileIoReadTest_563, ReadReturnsRequestedBytesWhenAvailable_563) {
  const auto path = MakeTempPath("fileio_read_requested");
  const std::vector<uint8_t> content = {'A', 'B', 'C', 'D', 'E'};
  WriteFile(path, content);

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("rb"));

  Exiv2::DataBuf buf = io.read(3);
  EXPECT_EQ(3u, buf.size());
  EXPECT_EQ('A', static_cast<char>(buf.read_uint8(0)));
  EXPECT_EQ('B', static_cast<char>(buf.read_uint8(1)));
  EXPECT_EQ('C', static_cast<char>(buf.read_uint8(2)));

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoReadTest_563, ReadWithExactSizeReadsWholeFile_563) {
  const auto path = MakeTempPath("fileio_read_exact_size");
  const std::vector<uint8_t> content = {1, 2, 3, 4};
  WriteFile(path, content);

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("rb"));

  const size_t fileSize = io.size();
  ASSERT_EQ(content.size(), fileSize);

  Exiv2::DataBuf buf = io.read(fileSize);
  EXPECT_EQ(fileSize, buf.size());
  for (size_t i = 0; i < fileSize; ++i) {
    EXPECT_EQ(content[i], buf.read_uint8(i));
  }

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoReadTest_563, ReadResizesToActualBytesNearEof_563) {
  const auto path = MakeTempPath("fileio_read_resize_near_eof");
  const std::vector<uint8_t> content = {'x', 'y', 'z', 'w'};
  WriteFile(path, content);

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("rb"));
  ASSERT_EQ(content.size(), io.size());

  // Move to the last 2 bytes, then request more than remains (but not more than size()).
  ASSERT_EQ(0, io.seek(2, Exiv2::BasicIo::beg));

  Exiv2::DataBuf buf = io.read(4);  // 4 <= size(), but only 2 bytes remain.
  EXPECT_EQ(2u, buf.size());
  EXPECT_EQ('z', static_cast<char>(buf.read_uint8(0)));
  EXPECT_EQ('w', static_cast<char>(buf.read_uint8(1)));

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoReadTest_563, ReadThrowsInvalidMallocWhenRequestExceedsSize_563) {
  const auto path = MakeTempPath("fileio_read_exceeds_size");
  const std::vector<uint8_t> content = {9, 8, 7};
  WriteFile(path, content);

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("rb"));
  const size_t fileSize = io.size();
  ASSERT_EQ(content.size(), fileSize);

  try {
    (void)io.read(fileSize + 1);
    FAIL() << "Expected Exiv2::Error";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCode(e, Exiv2::ErrorCode::kerInvalidMalloc);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error";
  }

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoReadTest_563, ReadThrowsInputDataReadFailedOnEof_563) {
  const auto path = MakeTempPath("fileio_read_eof_throws");
  const std::vector<uint8_t> content = {'p', 'q'};
  WriteFile(path, content);

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("rb"));

  // Seek to end so that a subsequent read produces 0 bytes read.
  ASSERT_EQ(0, io.seek(0, Exiv2::BasicIo::end));

  try {
    (void)io.read(1);
    FAIL() << "Expected Exiv2::Error";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCode(e, Exiv2::ErrorCode::kerInputDataReadFailed);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error";
  }

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

}  // namespace