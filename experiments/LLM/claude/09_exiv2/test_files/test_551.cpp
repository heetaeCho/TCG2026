#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <filesystem>

#include "exiv2/basicio.hpp"

namespace {

// Helper to create a temporary file with given content
class TempFile {
 public:
  explicit TempFile(const std::string& filename, const std::string& content = "") 
      : path_(filename) {
    std::ofstream ofs(path_, std::ios::binary);
    if (!content.empty()) {
      ofs.write(content.data(), content.size());
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

class FileIoTest_551 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
    // Clean up any leftover temp files
    for (auto& f : cleanup_files_) {
      std::remove(f.c_str());
    }
  }

  void addCleanup(const std::string& path) {
    cleanup_files_.push_back(path);
  }

  std::vector<std::string> cleanup_files_;
};

// Test that constructor sets the path correctly
TEST_F(FileIoTest_551, ConstructorSetsPath_551) {
  std::string testPath = "test_constructor_551.tmp";
  Exiv2::FileIo fileIo(testPath);
  EXPECT_EQ(fileIo.path(), testPath);
}

// Test that setPath updates the path
TEST_F(FileIoTest_551, SetPathUpdatesPath_551) {
  std::string initialPath = "initial_path_551.tmp";
  std::string newPath = "new_path_551.tmp";
  
  Exiv2::FileIo fileIo(initialPath);
  EXPECT_EQ(fileIo.path(), initialPath);
  
  fileIo.setPath(newPath);
  EXPECT_EQ(fileIo.path(), newPath);
}

// Test that setPath closes the file if open
TEST_F(FileIoTest_551, SetPathClosesOpenFile_551) {
  std::string testPath = "test_setpath_close_551.tmp";
  std::string newPath = "test_setpath_new_551.tmp";
  addCleanup(testPath);
  addCleanup(newPath);
  
  // Create the file
  {
    std::ofstream ofs(testPath);
    ofs << "test data";
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  EXPECT_TRUE(fileIo.isopen());
  
  fileIo.setPath(newPath);
  EXPECT_FALSE(fileIo.isopen());
  EXPECT_EQ(fileIo.path(), newPath);
}

// Test open and close
TEST_F(FileIoTest_551, OpenAndClose_551) {
  std::string testPath = "test_open_close_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath);
    ofs << "hello";
  }
  
  Exiv2::FileIo fileIo(testPath);
  EXPECT_FALSE(fileIo.isopen());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_TRUE(fileIo.isopen());
  
  EXPECT_EQ(fileIo.close(), 0);
  EXPECT_FALSE(fileIo.isopen());
}

// Test open with mode
TEST_F(FileIoTest_551, OpenWithMode_551) {
  std::string testPath = "test_open_mode_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath);
    ofs << "test";
  }
  
  Exiv2::FileIo fileIo(testPath);
  EXPECT_EQ(fileIo.open("r"), 0);
  EXPECT_TRUE(fileIo.isopen());
  fileIo.close();
}

// Test open nonexistent file returns error
TEST_F(FileIoTest_551, OpenNonexistentFileReturnsError_551) {
  std::string testPath = "nonexistent_file_551_that_should_not_exist.tmp";
  Exiv2::FileIo fileIo(testPath);
  
  // Opening a non-existent file for reading should fail
  EXPECT_NE(fileIo.open("r"), 0);
  EXPECT_FALSE(fileIo.isopen());
}

// Test write data and read back
TEST_F(FileIoTest_551, WriteAndRead_551) {
  std::string testPath = "test_write_read_551.tmp";
  addCleanup(testPath);
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open("w+b"), 0);
  
  const std::string data = "Hello, World!";
  size_t written = fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.c_str()), data.size());
  EXPECT_EQ(written, data.size());
  
  // Seek back to beginning
  EXPECT_EQ(fileIo.seek(0, Exiv2::BasicIo::beg), 0);
  
  Exiv2::byte buf[64] = {};
  size_t bytesRead = fileIo.read(buf, data.size());
  EXPECT_EQ(bytesRead, data.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), data);
  
  fileIo.close();
}

// Test size
TEST_F(FileIoTest_551, Size_551) {
  std::string testPath = "test_size_551.tmp";
  addCleanup(testPath);
  
  const std::string content = "1234567890";
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs << content;
  }
  
  Exiv2::FileIo fileIo(testPath);
  EXPECT_EQ(fileIo.size(), static_cast<size_t>(content.size()));
}

// Test tell
TEST_F(FileIoTest_551, Tell_551) {
  std::string testPath = "test_tell_551.tmp";
  addCleanup(testPath);
  
  const std::string content = "ABCDEFGHIJ";
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs << content;
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  
  EXPECT_EQ(fileIo.tell(), 0u);
  
  Exiv2::byte buf[5];
  fileIo.read(buf, 5);
  EXPECT_EQ(fileIo.tell(), 5u);
  
  fileIo.close();
}

// Test seek from beginning, current, end
TEST_F(FileIoTest_551, SeekPositions_551) {
  std::string testPath = "test_seek_551.tmp";
  addCleanup(testPath);
  
  const std::string content = "0123456789";
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs << content;
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  
  // Seek from beginning
  EXPECT_EQ(fileIo.seek(3, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(fileIo.tell(), 3u);
  
  // Seek from current
  EXPECT_EQ(fileIo.seek(2, Exiv2::BasicIo::cur), 0);
  EXPECT_EQ(fileIo.tell(), 5u);
  
  // Seek from end
  EXPECT_EQ(fileIo.seek(-2, Exiv2::BasicIo::end), 0);
  EXPECT_EQ(fileIo.tell(), 8u);
  
  fileIo.close();
}

// Test getb
TEST_F(FileIoTest_551, Getb_551) {
  std::string testPath = "test_getb_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs.put('A');
    ofs.put('B');
    ofs.put('C');
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  
  EXPECT_EQ(fileIo.getb(), 'A');
  EXPECT_EQ(fileIo.getb(), 'B');
  EXPECT_EQ(fileIo.getb(), 'C');
  
  fileIo.close();
}

// Test putb
TEST_F(FileIoTest_551, Putb_551) {
  std::string testPath = "test_putb_551.tmp";
  addCleanup(testPath);
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open("w+b"), 0);
  
  EXPECT_EQ(fileIo.putb('X'), 0);
  EXPECT_EQ(fileIo.putb('Y'), 0);
  
  fileIo.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(fileIo.getb(), 'X');
  EXPECT_EQ(fileIo.getb(), 'Y');
  
  fileIo.close();
}

// Test eof
TEST_F(FileIoTest_551, Eof_551) {
  std::string testPath = "test_eof_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs.put('A');
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  
  fileIo.getb();  // Read the single byte
  fileIo.getb();  // Read past end
  
  EXPECT_TRUE(fileIo.eof());
  
  fileIo.close();
}

// Test error on unopened file
TEST_F(FileIoTest_551, ErrorOnUnopenedFile_551) {
  std::string testPath = "test_error_551.tmp";
  Exiv2::FileIo fileIo(testPath);
  
  // Error should be 0 when not open (no file operation error)
  EXPECT_EQ(fileIo.error(), 0);
}

// Test read with DataBuf
TEST_F(FileIoTest_551, ReadDataBuf_551) {
  std::string testPath = "test_databuf_551.tmp";
  addCleanup(testPath);
  
  const std::string content = "DataBufTest";
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs << content;
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  
  Exiv2::DataBuf buf = fileIo.read(content.size());
  EXPECT_EQ(buf.size(), content.size());
  EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.c_data()), buf.size()), content);
  
  fileIo.close();
}

// Test close on already closed file
TEST_F(FileIoTest_551, CloseAlreadyClosedFile_551) {
  std::string testPath = "test_close_twice_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath);
    ofs << "data";
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.close(), 0);
  
  // Closing again should be safe
  EXPECT_EQ(fileIo.close(), 0);
}

// Test setPath with empty string
TEST_F(FileIoTest_551, SetPathEmptyString_551) {
  std::string testPath = "test_empty_path_551.tmp";
  Exiv2::FileIo fileIo(testPath);
  
  fileIo.setPath("");
  EXPECT_EQ(fileIo.path(), "");
}

// Test setPath multiple times
TEST_F(FileIoTest_551, SetPathMultipleTimes_551) {
  Exiv2::FileIo fileIo("path1_551.tmp");
  EXPECT_EQ(fileIo.path(), "path1_551.tmp");
  
  fileIo.setPath("path2_551.tmp");
  EXPECT_EQ(fileIo.path(), "path2_551.tmp");
  
  fileIo.setPath("path3_551.tmp");
  EXPECT_EQ(fileIo.path(), "path3_551.tmp");
}

// Test write zero bytes
TEST_F(FileIoTest_551, WriteZeroBytes_551) {
  std::string testPath = "test_write_zero_551.tmp";
  addCleanup(testPath);
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open("w+b"), 0);
  
  Exiv2::byte data = 0;
  size_t written = fileIo.write(&data, 0);
  EXPECT_EQ(written, 0u);
  
  fileIo.close();
}

// Test read zero bytes
TEST_F(FileIoTest_551, ReadZeroBytes_551) {
  std::string testPath = "test_read_zero_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs << "data";
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  
  Exiv2::DataBuf buf = fileIo.read(0);
  EXPECT_EQ(buf.size(), 0u);
  
  fileIo.close();
}

// Test that size works on empty file
TEST_F(FileIoTest_551, SizeEmptyFile_551) {
  std::string testPath = "test_empty_file_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath, std::ios::binary);
    // Write nothing
  }
  
  Exiv2::FileIo fileIo(testPath);
  EXPECT_EQ(fileIo.size(), 0u);
}

// Test writing from another BasicIo
TEST_F(FileIoTest_551, WriteFromBasicIo_551) {
  std::string srcPath = "test_write_src_551.tmp";
  std::string dstPath = "test_write_dst_551.tmp";
  addCleanup(srcPath);
  addCleanup(dstPath);
  
  const std::string content = "source content for copy";
  {
    std::ofstream ofs(srcPath, std::ios::binary);
    ofs << content;
  }
  
  Exiv2::FileIo srcIo(srcPath);
  ASSERT_EQ(srcIo.open(), 0);
  
  Exiv2::FileIo dstIo(dstPath);
  ASSERT_EQ(dstIo.open("w+b"), 0);
  
  size_t written = dstIo.write(srcIo);
  EXPECT_EQ(written, content.size());
  
  srcIo.close();
  dstIo.close();
  
  // Verify content
  Exiv2::FileIo verifyIo(dstPath);
  ASSERT_EQ(verifyIo.open(), 0);
  Exiv2::DataBuf buf = verifyIo.read(content.size());
  EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.c_data()), buf.size()), content);
  verifyIo.close();
}

// Test path returns correct path after construction
TEST_F(FileIoTest_551, PathIsCorrectAfterConstruction_551) {
  std::string testPath = "/some/arbitrary/path_551.tmp";
  Exiv2::FileIo fileIo(testPath);
  EXPECT_EQ(fileIo.path(), testPath);
}

// Test isopen returns false before open
TEST_F(FileIoTest_551, IsOpenFalseBeforeOpen_551) {
  Exiv2::FileIo fileIo("some_file_551.tmp");
  EXPECT_FALSE(fileIo.isopen());
}

// Test large write and read
TEST_F(FileIoTest_551, LargeWriteAndRead_551) {
  std::string testPath = "test_large_551.tmp";
  addCleanup(testPath);
  
  const size_t dataSize = 100000;
  std::vector<Exiv2::byte> data(dataSize);
  for (size_t i = 0; i < dataSize; ++i) {
    data[i] = static_cast<Exiv2::byte>(i % 256);
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open("w+b"), 0);
  
  size_t written = fileIo.write(data.data(), dataSize);
  EXPECT_EQ(written, dataSize);
  
  fileIo.seek(0, Exiv2::BasicIo::beg);
  
  std::vector<Exiv2::byte> readBuf(dataSize);
  size_t bytesRead = fileIo.read(readBuf.data(), dataSize);
  EXPECT_EQ(bytesRead, dataSize);
  EXPECT_EQ(data, readBuf);
  
  fileIo.close();
}

// Test seek beyond end of file
TEST_F(FileIoTest_551, SeekBeyondEnd_551) {
  std::string testPath = "test_seek_beyond_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs << "short";
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open("r+b"), 0);
  
  // Seek beyond end - this should succeed (fseek allows it)
  int result = fileIo.seek(1000, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(fileIo.tell(), 1000u);
  
  fileIo.close();
}

// Test getb at EOF returns EOF
TEST_F(FileIoTest_551, GetbAtEofReturnsEof_551) {
  std::string testPath = "test_getb_eof_551.tmp";
  addCleanup(testPath);
  
  {
    std::ofstream ofs(testPath, std::ios::binary);
    ofs.put('Z');
  }
  
  Exiv2::FileIo fileIo(testPath);
  ASSERT_EQ(fileIo.open(), 0);
  
  EXPECT_EQ(fileIo.getb(), 'Z');
  int result = fileIo.getb();
  EXPECT_EQ(result, EOF);
  
  fileIo.close();
}
