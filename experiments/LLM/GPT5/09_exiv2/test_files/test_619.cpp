// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_readfile_619.cpp
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// readFile is implemented in ./TestProjects/exiv2/src/basicio.cpp
namespace Exiv2 {
DataBuf readFile(const std::string& path);
}  // namespace Exiv2

namespace {

class TempPathGuard final {
 public:
  explicit TempPathGuard(fs::path p) : p_(std::move(p)) {}
  TempPathGuard(const TempPathGuard&) = delete;
  TempPathGuard& operator=(const TempPathGuard&) = delete;
  ~TempPathGuard() {
    std::error_code ec;
    if (!p_.empty()) fs::remove_all(p_, ec);
  }
  const fs::path& path() const { return p_; }

 private:
  fs::path p_;
};

static fs::path MakeUniqueTempPath(const std::string& stem) {
  const fs::path base = fs::temp_directory_path();
  // Use a simple uniqueness strategy that doesn't require platform APIs.
  // If creation collides, try a few suffixes.
  for (int i = 0; i < 200; ++i) {
    fs::path p = base / (stem + "_" + std::to_string(::testing::UnitTest::GetInstance()->random_seed()) +
                         "_" + std::to_string(i));
    std::error_code ec;
    if (!fs::exists(p, ec)) return p;
  }
  // Fall back: let filesystem create something via a directory and a fixed file name.
  return base / (stem + "_fallback");
}

static void WriteBinaryFile(const fs::path& p, const std::vector<uint8_t>& bytes) {
  std::ofstream os(p, std::ios::binary | std::ios::trunc);
  ASSERT_TRUE(os.good());
  if (!bytes.empty()) {
    os.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
  }
  os.close();
  ASSERT_TRUE(os.good());
}

class ReadFileTest_619 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Ensure all created artifacts are cleaned up even if a test failed.
    guards_.clear();
  }

  const fs::path& CreateTempFile(const std::string& stem, const std::vector<uint8_t>& bytes) {
    fs::path p = MakeUniqueTempPath(stem);
    WriteBinaryFile(p, bytes);
    guards_.emplace_back(p);
    return guards_.back().path();
  }

  const fs::path& CreateTempDir(const std::string& stem) {
    fs::path p = MakeUniqueTempPath(stem);
    std::error_code ec;
    ASSERT_TRUE(fs::create_directories(p, ec));
    ASSERT_FALSE(ec);
    guards_.emplace_back(p);
    return guards_.back().path();
  }

 private:
  std::vector<TempPathGuard> guards_;
};

TEST_F(ReadFileTest_619, ReadsExactBytesFromSmallFile_619) {
  const std::vector<uint8_t> expected = {0x00, 0x01, 0x7f, 0x80, 0xff};
  const fs::path p = CreateTempFile("exiv2_readFile_small", expected);

  const Exiv2::DataBuf buf = Exiv2::readFile(p.string());

  ASSERT_EQ(buf.size(), expected.size());
  EXPECT_FALSE(buf.empty());
  // Compare byte-for-byte using the public interface.
  EXPECT_EQ(buf.cmpBytes(0, expected.data(), expected.size()), 0);
}

TEST_F(ReadFileTest_619, ReadsOneByteFile_619) {
  const std::vector<uint8_t> expected = {0x5a};
  const fs::path p = CreateTempFile("exiv2_readFile_onebyte", expected);

  const Exiv2::DataBuf buf = Exiv2::readFile(p.string());

  ASSERT_EQ(buf.size(), 1u);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.cmpBytes(0, expected.data(), expected.size()), 0);
}

TEST_F(ReadFileTest_619, ReadsEmptyFileReturnsEmptyBuffer_619) {
  const std::vector<uint8_t> expected = {};
  const fs::path p = CreateTempFile("exiv2_readFile_empty", expected);

  const Exiv2::DataBuf buf = Exiv2::readFile(p.string());

  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(ReadFileTest_619, NonexistentPathThrowsExiv2ErrorWithFileOpenFailed_619) {
  const fs::path p = MakeUniqueTempPath("exiv2_readFile_noexist");
  // Ensure it does not exist.
  std::error_code ec;
  fs::remove_all(p, ec);

  try {
    (void)Exiv2::readFile(p.string());
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFileOpenFailed);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}

TEST_F(ReadFileTest_619, DirectoryPathThrowsSomeException_619) {
  // Observable behavior: passing a directory is not a valid "file" to read.
  // The implementation may fail at open() (Exiv2::Error) or at file_size() (filesystem_error),
  // depending on platform/FS semantics.
  const fs::path dir = CreateTempDir("exiv2_readFile_dir");

  EXPECT_THROW((void)Exiv2::readFile(dir.string()), std::exception);
}

}  // namespace