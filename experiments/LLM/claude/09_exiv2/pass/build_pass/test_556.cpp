#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>

#include "exiv2/basicio.hpp"

namespace {

// Helper to create a temporary file with some content
class TempFile {
 public:
  explicit TempFile(const std::string& name, const std::string& content = "")
      : path_(name) {
    std::ofstream ofs(path_, std::ios::binary);
    if (!content.empty()) {
      ofs.write(content.data(), static_cast<std::streamsize>(content.size()));
    }
    ofs.close();
  }

  ~TempFile() {
    std::remove(path_.c_str());
  }

  const std::string& path() const { return path_; }

 private:
  std::string path_;
};

}  // namespace

class FileIoSeekTest_556 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temporary file with known content
    testContent_ = "Hello, World! This is test data for seek operations.";
    tempFile_ = std::make_unique<TempFile>("test_seek_556.tmp", testContent_);
  }

  void TearDown() override {
    tempFile_.reset();
  }

  std::string testContent_;
  std::unique_ptr<TempFile> tempFile_;
};

// Test seeking from the beginning of the file
TEST_F(FileIoSeekTest_556, SeekFromBeginning_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  int result = file.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 0u);

  file.close();
}

// Test seeking from the beginning to a specific offset
TEST_F(FileIoSeekTest_556, SeekFromBeginningWithOffset_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  int result = file.seek(5, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 5u);

  file.close();
}

// Test seeking from current position
TEST_F(FileIoSeekTest_556, SeekFromCurrent_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  // First seek to offset 10 from beginning
  file.seek(10, Exiv2::BasicIo::beg);
  EXPECT_EQ(file.tell(), 10u);

  // Then seek 5 more from current position
  int result = file.seek(5, Exiv2::BasicIo::cur);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 15u);

  file.close();
}

// Test seeking from the end of the file
TEST_F(FileIoSeekTest_556, SeekFromEnd_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  int result = file.seek(0, Exiv2::BasicIo::end);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), testContent_.size());

  file.close();
}

// Test seeking from the end with negative offset
TEST_F(FileIoSeekTest_556, SeekFromEndWithNegativeOffset_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  int result = file.seek(-5, Exiv2::BasicIo::end);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), testContent_.size() - 5);

  file.close();
}

// Test seeking to offset 0 from beginning (boundary)
TEST_F(FileIoSeekTest_556, SeekToZeroFromBeginning_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  // Move somewhere first
  file.seek(20, Exiv2::BasicIo::beg);
  EXPECT_EQ(file.tell(), 20u);

  // Seek back to beginning
  int result = file.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 0u);

  file.close();
}

// Test that seeking and reading works correctly together
TEST_F(FileIoSeekTest_556, SeekThenRead_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  // Seek to offset 7 ("World!...")
  int result = file.seek(7, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);

  // Read a few bytes and verify
  Exiv2::byte buf[5];
  size_t bytesRead = file.read(buf, 5);
  EXPECT_EQ(bytesRead, 5u);
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 5), "World");

  file.close();
}

// Test seeking with current position using negative offset
TEST_F(FileIoSeekTest_556, SeekBackwardFromCurrent_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  // Seek to offset 20
  file.seek(20, Exiv2::BasicIo::beg);
  EXPECT_EQ(file.tell(), 20u);

  // Seek back 10 from current
  int result = file.seek(-10, Exiv2::BasicIo::cur);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 10u);

  file.close();
}

// Test seeking to exact end of file
TEST_F(FileIoSeekTest_556, SeekToExactEnd_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  size_t fileSize = file.size();
  int result = file.seek(static_cast<int64_t>(fileSize), Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), fileSize);

  file.close();
}

// Test seeking beyond end of file (should succeed for seek, fseek allows it)
TEST_F(FileIoSeekTest_556, SeekBeyondEnd_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  size_t fileSize = file.size();
  int result = file.seek(static_cast<int64_t>(fileSize) + 100, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), fileSize + 100);

  file.close();
}

// Test multiple sequential seeks
TEST_F(FileIoSeekTest_556, MultipleSequentialSeeks_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  EXPECT_EQ(file.seek(5, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(file.tell(), 5u);

  EXPECT_EQ(file.seek(3, Exiv2::BasicIo::cur), 0);
  EXPECT_EQ(file.tell(), 8u);

  EXPECT_EQ(file.seek(-2, Exiv2::BasicIo::end), 0);
  EXPECT_EQ(file.tell(), testContent_.size() - 2);

  EXPECT_EQ(file.seek(0, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(file.tell(), 0u);

  file.close();
}

// Test seeking on a file opened for writing
TEST_F(FileIoSeekTest_556, SeekOnWriteMode_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open("r+b"), 0);

  int result = file.seek(10, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 10u);

  file.close();
}

// Test that path returns the correct path
TEST_F(FileIoSeekTest_556, PathReturnsCorrectPath_556) {
  Exiv2::FileIo file(tempFile_->path());
  EXPECT_EQ(file.path(), tempFile_->path());
}

// Test seeking on an empty file
TEST(FileIoSeekEmptyTest_556, SeekOnEmptyFile_556) {
  TempFile emptyFile("test_seek_empty_556.tmp", "");
  Exiv2::FileIo file(emptyFile.path());
  ASSERT_EQ(file.open(), 0);

  int result = file.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 0u);

  result = file.seek(0, Exiv2::BasicIo::end);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 0u);

  file.close();
}

// Test seeking from current with zero offset doesn't change position
TEST_F(FileIoSeekTest_556, SeekZeroFromCurrentNoChange_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  file.seek(15, Exiv2::BasicIo::beg);
  EXPECT_EQ(file.tell(), 15u);

  int result = file.seek(0, Exiv2::BasicIo::cur);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 15u);

  file.close();
}

// Test that tell returns 0 initially after open
TEST_F(FileIoSeekTest_556, TellReturnsZeroAfterOpen_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);
  EXPECT_EQ(file.tell(), 0u);
  file.close();
}

// Test seek after read moves position correctly
TEST_F(FileIoSeekTest_556, SeekAfterRead_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  // Read some bytes first
  Exiv2::byte buf[10];
  file.read(buf, 10);
  EXPECT_EQ(file.tell(), 10u);

  // Now seek from beginning
  int result = file.seek(3, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 3u);

  file.close();
}

// Test size returns correct file size
TEST_F(FileIoSeekTest_556, SizeReturnsCorrectValue_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);
  EXPECT_EQ(file.size(), testContent_.size());
  file.close();
}

// Test isopen returns correct state
TEST_F(FileIoSeekTest_556, IsOpenReturnsCorrectState_556) {
  Exiv2::FileIo file(tempFile_->path());
  EXPECT_FALSE(file.isopen());

  ASSERT_EQ(file.open(), 0);
  EXPECT_TRUE(file.isopen());

  file.close();
  EXPECT_FALSE(file.isopen());
}

// Test seek with large offset from beginning
TEST_F(FileIoSeekTest_556, SeekLargeOffsetFromBeginning_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  // Seek to a large offset (beyond file size, but fseek should allow it)
  int result = file.seek(1000000, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(file.tell(), 1000000u);

  file.close();
}

// Test negative seek from beginning (should fail)
TEST_F(FileIoSeekTest_556, NegativeSeekFromBeginning_556) {
  Exiv2::FileIo file(tempFile_->path());
  ASSERT_EQ(file.open(), 0);

  // Seeking to a negative position from beginning is invalid
  int result = file.seek(-1, Exiv2::BasicIo::beg);
  EXPECT_NE(result, 0);

  file.close();
}
