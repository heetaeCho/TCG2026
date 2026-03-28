// File: test_fileio_error_566.cpp
// TEST_ID: 566

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

class FileIoErrorTest_566 : public ::testing::Test {
 protected:
  static std::string makeTempPath(const std::string& stem) {
    namespace fs = std::filesystem;
    const fs::path dir = fs::temp_directory_path();
    // Use a simple uniqueness strategy without relying on platform-specific mkstemp.
    static std::atomic<unsigned> counter{0};
    const unsigned c = ++counter;
    fs::path p = dir / (stem + "_" + std::to_string(c) + ".bin");
    return p.string();
  }

  static void writeFile(const std::string& path, const std::vector<unsigned char>& bytes) {
    std::ofstream os(path, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(os.is_open());
    os.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    ASSERT_TRUE(os.good());
  }

  void TearDown() override {
    // Best-effort cleanup for any paths created by tests (individual tests track their own).
  }
};

TEST_F(FileIoErrorTest_566, ErrorReturnsZeroWhenNotOpen_566) {
  const std::string path = makeTempPath("exiv2_fileio_error_notopen");
  // Do not create the file; we only care that the FileIo is not opened.
  Exiv2::FileIo io(path);

  // Observable behavior from provided implementation snippet:
  // error() returns 0 when underlying FILE* is null.
  EXPECT_EQ(0, io.error());
}

TEST_F(FileIoErrorTest_566, ErrorReturnsZeroAfterSuccessfulOpenWriteClose_566) {
  const std::string path = makeTempPath("exiv2_fileio_error_ok");
  writeFile(path, {0xAA, 0xBB, 0xCC});  // ensure path exists

  Exiv2::FileIo io(path);

  // Use explicit mode so the test is not dependent on FileIo::open() defaults.
  ASSERT_EQ(0, io.open("wb"));

  const Exiv2::byte data[] = {0x01, 0x02, 0x03, 0x04};
  const size_t written = io.write(data, sizeof(data));
  // We don't assume exact semantics, but for a writable stream we expect a full write.
  EXPECT_EQ(sizeof(data), written);

  // No error expected after normal operations.
  EXPECT_EQ(0, io.error());

  ASSERT_EQ(0, io.close());

  // After close(), implementations commonly null the FILE*. The provided snippet indicates
  // error() must return 0 when FILE* is null.
  EXPECT_EQ(0, io.error());

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoErrorTest_566, OpenNonexistentForReadFailsAndErrorRemainsZero_566) {
  const std::string path = makeTempPath("exiv2_fileio_error_missing");
  // Ensure it does not exist.
  std::error_code ec;
  std::filesystem::remove(path, ec);

  Exiv2::FileIo io(path);

  const int rc = io.open("rb");
  // We expect failure for a missing file, but we don't assume exact failure code.
  EXPECT_NE(0, rc);

  // From the provided implementation snippet: if FILE* is null, error() is 0.
  EXPECT_EQ(0, io.error());

  // close() may be a no-op or return an error if not open; we only verify it doesn't crash
  // and that error() remains observable as 0 when not open.
  (void)io.close();
  EXPECT_EQ(0, io.error());
}

TEST_F(FileIoErrorTest_566, ErrorIsStableAcrossRepeatedCallsWhenNotOpen_566) {
  const std::string path = makeTempPath("exiv2_fileio_error_repeat");
  Exiv2::FileIo io(path);

  EXPECT_EQ(0, io.error());
  EXPECT_EQ(0, io.error());
  EXPECT_EQ(0, io.error());
}

}  // namespace