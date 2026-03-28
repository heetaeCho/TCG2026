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
  explicit TempFile(const std::string& content = "", const std::string& suffix = ".tmp") {
    path_ = std::filesystem::temp_directory_path() / ("exiv2_test_565_" + std::to_string(counter_++) + suffix);
    if (!content.empty()) {
      std::ofstream ofs(path_, std::ios::binary);
      ofs.write(content.data(), content.size());
      ofs.close();
    }
  }

  ~TempFile() {
    std::filesystem::remove(path_);
  }

  std::string path() const { return path_.string(); }

 private:
  std::filesystem::path path_;
  static int counter_;
};

int TempFile::counter_ = 0;

}  // namespace

class FileIoTest_565 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that path() returns the path provided in constructor
TEST_F(FileIoTest_565, PathReturnsConstructorPath_565) {
  std::string testPath = "/some/test/path.jpg";
  Exiv2::FileIo io(testPath);
  EXPECT_EQ(io.path(), testPath);
}

// Test that a newly constructed FileIo is not open
TEST_F(FileIoTest_565, NewFileIoIsNotOpen_565) {
  TempFile tmp("hello");
  Exiv2::FileIo io(tmp.path());
  EXPECT_FALSE(io.isopen());
}

// Test open() and close() on an existing file
TEST_F(FileIoTest_565, OpenAndCloseExistingFile_565) {
  TempFile tmp("test content");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_TRUE(io.isopen());
  EXPECT_EQ(io.close(), 0);
  EXPECT_FALSE(io.isopen());
}

// Test open() on a non-existent file returns error
TEST_F(FileIoTest_565, OpenNonExistentFileReturnsError_565) {
  Exiv2::FileIo io("/non/existent/path/file_565.dat");
  EXPECT_NE(io.open(), 0);
  EXPECT_FALSE(io.isopen());
}

// Test open with mode string
TEST_F(FileIoTest_565, OpenWithModeString_565) {
  TempFile tmp("content");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("rb"), 0);
  EXPECT_TRUE(io.isopen());
  io.close();
}

// Test size() returns correct file size
TEST_F(FileIoTest_565, SizeReturnsCorrectValue_565) {
  std::string content = "Hello, World!";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.size(), content.size());
  io.close();
}

// Test tell() returns 0 after open
TEST_F(FileIoTest_565, TellReturnsZeroAfterOpen_565) {
  TempFile tmp("some data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.tell(), 0u);
  io.close();
}

// Test getb() reads bytes sequentially
TEST_F(FileIoTest_565, GetbReadsSequentially_565) {
  std::string content = "ABC";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.getb(), 'A');
  EXPECT_EQ(io.getb(), 'B');
  EXPECT_EQ(io.getb(), 'C');
  io.close();
}

// Test getb() returns EOF at end of file
TEST_F(FileIoTest_565, GetbReturnsEofAtEnd_565) {
  std::string content = "X";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.getb(), 'X');
  EXPECT_EQ(io.getb(), EOF);
  io.close();
}

// Test getb() returns EOF on empty file
TEST_F(FileIoTest_565, GetbReturnsEofOnEmptyFile_565) {
  TempFile tmp("");
  // Create an empty file
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.close();
  }
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.getb(), EOF);
  io.close();
}

// Test read(byte*, size_t) reads correct data
TEST_F(FileIoTest_565, ReadBufferReadsCorrectData_565) {
  std::string content = "Hello, Exiv2!";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  Exiv2::byte buf[64] = {};
  size_t bytesRead = io.read(buf, content.size());
  EXPECT_EQ(bytesRead, content.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), content);
  io.close();
}

// Test read(size_t) returns DataBuf with correct content
TEST_F(FileIoTest_565, ReadDataBufReturnsCorrectContent_565) {
  std::string content = "DataBuf test";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  Exiv2::DataBuf buf = io.read(content.size());
  EXPECT_EQ(buf.size(), content.size());
  EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.c_data()), buf.size()), content);
  io.close();
}

// Test read more bytes than available
TEST_F(FileIoTest_565, ReadMoreThanAvailable_565) {
  std::string content = "Short";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  Exiv2::byte buf[100] = {};
  size_t bytesRead = io.read(buf, 100);
  EXPECT_EQ(bytesRead, content.size());
  io.close();
}

// Test write and read back
TEST_F(FileIoTest_565, WriteAndReadBack_565) {
  TempFile tmp;
  // Create the file first
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.close();
  }
  
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);
  
  std::string data = "Written data";
  size_t written = io.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  EXPECT_EQ(written, data.size());
  
  // Seek back to beginning and read
  EXPECT_EQ(io.seek(0, Exiv2::BasicIo::beg), 0);
  
  Exiv2::byte buf[64] = {};
  size_t bytesRead = io.read(buf, data.size());
  EXPECT_EQ(bytesRead, data.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), data);
  
  io.close();
}

// Test putb writes a single byte
TEST_F(FileIoTest_565, PutbWritesSingleByte_565) {
  TempFile tmp;
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.close();
  }
  
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);
  
  EXPECT_EQ(io.putb(0x42), 0x42);
  
  EXPECT_EQ(io.seek(0, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(io.getb(), 0x42);
  
  io.close();
}

// Test seek to various positions
TEST_F(FileIoTest_565, SeekFromBeginning_565) {
  std::string content = "0123456789";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  EXPECT_EQ(io.seek(5, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(io.tell(), 5u);
  EXPECT_EQ(io.getb(), '5');
  
  io.close();
}

TEST_F(FileIoTest_565, SeekFromCurrent_565) {
  std::string content = "0123456789";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  EXPECT_EQ(io.seek(3, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(io.seek(2, Exiv2::BasicIo::cur), 0);
  EXPECT_EQ(io.tell(), 5u);
  EXPECT_EQ(io.getb(), '5');
  
  io.close();
}

TEST_F(FileIoTest_565, SeekFromEnd_565) {
  std::string content = "0123456789";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  EXPECT_EQ(io.seek(-1, Exiv2::BasicIo::end), 0);
  EXPECT_EQ(io.getb(), '9');
  
  io.close();
}

// Test eof() returns true after reading past end
TEST_F(FileIoTest_565, EofReturnsTrueAfterReadingPastEnd_565) {
  std::string content = "AB";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  Exiv2::byte buf[10] = {};
  io.read(buf, 10);
  EXPECT_TRUE(io.eof());
  
  io.close();
}

// Test eof() returns false when not at end
TEST_F(FileIoTest_565, EofReturnsFalseWhenNotAtEnd_565) {
  std::string content = "Hello";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  io.getb();
  EXPECT_FALSE(io.eof());
  
  io.close();
}

// Test error() returns 0 on successful operations
TEST_F(FileIoTest_565, ErrorReturnsZeroOnSuccess_565) {
  std::string content = "test";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.error(), 0);
  io.close();
}

// Test close on already closed file
TEST_F(FileIoTest_565, CloseOnAlreadyClosedFile_565) {
  TempFile tmp("data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.close(), 0);
  // Closing again should not crash; behavior may vary
  EXPECT_EQ(io.close(), 0);
}

// Test setPath changes the path
TEST_F(FileIoTest_565, SetPathChangesPath_565) {
  TempFile tmp("data");
  Exiv2::FileIo io(tmp.path());
  std::string newPath = "/new/path/file.jpg";
  io.setPath(newPath);
  EXPECT_EQ(io.path(), newPath);
}

// Test write with zero count
TEST_F(FileIoTest_565, WriteZeroBytes_565) {
  TempFile tmp;
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.close();
  }
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);
  
  Exiv2::byte data = 0;
  size_t written = io.write(&data, 0);
  EXPECT_EQ(written, 0u);
  
  io.close();
}

// Test read with zero count
TEST_F(FileIoTest_565, ReadZeroBytes_565) {
  std::string content = "Some content";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  Exiv2::byte buf[10] = {};
  size_t bytesRead = io.read(buf, 0);
  EXPECT_EQ(bytesRead, 0u);
  EXPECT_EQ(io.tell(), 0u);
  
  io.close();
}

// Test size on empty file
TEST_F(FileIoTest_565, SizeOfEmptyFile_565) {
  TempFile tmp;
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.close();
  }
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.size(), 0u);
  io.close();
}

// Test mmap and munmap
TEST_F(FileIoTest_565, MmapAndMunmap_565) {
  std::string content = "mmap test data";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  Exiv2::byte* mapped = io.mmap(false);
  ASSERT_NE(mapped, nullptr);
  
  // Verify mapped data matches content
  for (size_t i = 0; i < content.size(); ++i) {
    EXPECT_EQ(mapped[i], static_cast<Exiv2::byte>(content[i]));
  }
  
  EXPECT_EQ(io.munmap(), 0);
  io.close();
}

// Test transfer from another FileIo
TEST_F(FileIoTest_565, TransferFromAnotherFileIo_565) {
  std::string srcContent = "Source file content";
  TempFile srcTmp(srcContent);
  TempFile dstTmp;
  {
    std::ofstream ofs(dstTmp.path(), std::ios::binary);
    ofs.close();
  }
  
  Exiv2::FileIo src(srcTmp.path());
  Exiv2::FileIo dst(dstTmp.path());
  
  EXPECT_EQ(src.open(), 0);
  dst.transfer(src);
  
  // Now read from dst
  EXPECT_EQ(dst.open(), 0);
  Exiv2::DataBuf buf = dst.read(srcContent.size());
  EXPECT_EQ(buf.size(), srcContent.size());
  EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.c_data()), buf.size()), srcContent);
  dst.close();
}

// Test multiple sequential getb calls advance tell
TEST_F(FileIoTest_565, GetbAdvancesTell_565) {
  std::string content = "ABCDEF";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  for (size_t i = 0; i < content.size(); ++i) {
    EXPECT_EQ(io.tell(), i);
    int b = io.getb();
    EXPECT_EQ(b, static_cast<int>(content[i]));
  }
  EXPECT_EQ(io.tell(), content.size());
  
  io.close();
}

// Test binary data with null bytes
TEST_F(FileIoTest_565, BinaryDataWithNullBytes_565) {
  std::string content;
  content.push_back('\0');
  content.push_back('A');
  content.push_back('\0');
  content.push_back('B');
  
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  
  EXPECT_EQ(io.getb(), 0);
  EXPECT_EQ(io.getb(), 'A');
  EXPECT_EQ(io.getb(), 0);
  EXPECT_EQ(io.getb(), 'B');
  EXPECT_EQ(io.getb(), EOF);
  
  io.close();
}

// Test writing from one BasicIo to another via write(BasicIo&)
TEST_F(FileIoTest_565, WriteFromBasicIo_565) {
  std::string srcContent = "source data for write";
  TempFile srcTmp(srcContent);
  TempFile dstTmp;
  {
    std::ofstream ofs(dstTmp.path(), std::ios::binary);
    ofs.close();
  }
  
  Exiv2::FileIo src(srcTmp.path());
  Exiv2::FileIo dst(dstTmp.path());
  
  EXPECT_EQ(src.open(), 0);
  EXPECT_EQ(dst.open("w+b"), 0);
  
  size_t written = dst.write(src);
  EXPECT_EQ(written, srcContent.size());
  
  dst.seek(0, Exiv2::BasicIo::beg);
  Exiv2::byte buf[64] = {};
  size_t bytesRead = dst.read(buf, srcContent.size());
  EXPECT_EQ(bytesRead, srcContent.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), srcContent);
  
  src.close();
  dst.close();
}
