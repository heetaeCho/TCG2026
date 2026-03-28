// ============================================================================
// Copyright ...
// Unit tests for Exiv2::FileIo::close()
// TEST_ID: 562
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

std::string makeTempFilePath_562(const std::string& prefix) {
  namespace fs = std::filesystem;
  const auto dir = fs::temp_directory_path();
  const auto name =
      prefix + "_" + std::to_string(static_cast<unsigned long long>(std::rand())) + ".bin";
  return (dir / name).string();
}

void writeFile_562(const std::string& path, const std::string& contents) {
  std::ofstream os(path, std::ios::binary);
  ASSERT_TRUE(os.good());
  os.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  ASSERT_TRUE(os.good());
}

// Force munmap() return code via virtual dispatch (munmap is declared override => virtual).
class FileIoMunmapOverride_562 : public Exiv2::FileIo {
 public:
  explicit FileIoMunmapOverride_562(const std::string& path)
      : Exiv2::FileIo(path) {}

  void setMunmapRc(int rc) { munmapRc_ = rc; }

  int munmap() override { return munmapRc_; }

 private:
  int munmapRc_{0};
};

class FileIoCloseTest_562 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (!tmpPath_.empty()) {
      std::error_code ec;
      std::filesystem::remove(tmpPath_, ec);
    }
  }

  std::string tmpPath_;
};

}  // namespace

TEST_F(FileIoCloseTest_562, CloseOnFreshObjectReturnsZeroWhenMunmapSucceeds_562) {
  tmpPath_ = makeTempFilePath_562("exiv2_fileio_close_fresh");
  writeFile_562(tmpPath_, "abc");

  FileIoMunmapOverride_562 io(tmpPath_);
  io.setMunmapRc(0);

  // Behavior under test: close() returns rc that reflects munmap/fclose outcomes.
  const int rc = io.close();
  EXPECT_EQ(0, rc);
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoCloseTest_562, CloseAfterOpenClosesAndReturnsZeroOnSuccess_562) {
  tmpPath_ = makeTempFilePath_562("exiv2_fileio_close_open");
  writeFile_562(tmpPath_, "hello");

  FileIoMunmapOverride_562 io(tmpPath_);
  io.setMunmapRc(0);

  ASSERT_EQ(0, io.open("rb"));
  EXPECT_TRUE(io.isopen());

  const int rc = io.close();
  EXPECT_EQ(0, rc);
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoCloseTest_562, ClosePropagatesMunmapFailureBit_562) {
  tmpPath_ = makeTempFilePath_562("exiv2_fileio_close_munmapfail");
  writeFile_562(tmpPath_, "data");

  FileIoMunmapOverride_562 io(tmpPath_);
  io.setMunmapRc(1);  // Non-zero => close() should set rc=2 (bit for munmap failure)

  // Open or not, close() calls munmap() first; use open() to also exercise normal open/close flow.
  ASSERT_EQ(0, io.open("rb"));
  EXPECT_TRUE(io.isopen());

  const int rc = io.close();

  // Only require the observable contract from the provided implementation: bit 2 is set.
  EXPECT_EQ(2, (rc & 2));
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoCloseTest_562, CloseIsSafeToCallTwiceAndKeepsClosedState_562) {
  tmpPath_ = makeTempFilePath_562("exiv2_fileio_close_twice");
  writeFile_562(tmpPath_, "xyz");

  FileIoMunmapOverride_562 io(tmpPath_);
  io.setMunmapRc(0);

  ASSERT_EQ(0, io.open("rb"));
  ASSERT_TRUE(io.isopen());

  const int first = io.close();
  EXPECT_EQ(0, first);
  EXPECT_FALSE(io.isopen());

  const int second = io.close();
  EXPECT_EQ(0, second);
  EXPECT_FALSE(io.isopen());
}

TEST_F(FileIoCloseTest_562, CloseDoesNotPreventReopenAfterClose_562) {
  tmpPath_ = makeTempFilePath_562("exiv2_fileio_close_reopen");
  writeFile_562(tmpPath_, "reopen");

  FileIoMunmapOverride_562 io(tmpPath_);
  io.setMunmapRc(0);

  ASSERT_EQ(0, io.open("rb"));
  ASSERT_TRUE(io.isopen());
  ASSERT_EQ(0, io.close());
  ASSERT_FALSE(io.isopen());

  // Reopen should be possible after a successful close.
  ASSERT_EQ(0, io.open("rb"));
  EXPECT_TRUE(io.isopen());
  EXPECT_EQ(0, io.close());
  EXPECT_FALSE(io.isopen());
}