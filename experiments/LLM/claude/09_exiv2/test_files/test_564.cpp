#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>

#include "exiv2/basicio.hpp"

namespace {

// Helper to create a temporary file with given content
class TempFile {
 public:
  explicit TempFile(const std::string& name, const std::string& content = "")
      : path_(name) {
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

class FileIoTest_564 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that constructing FileIo with a path stores the path correctly
TEST_F(FileIoTest_564, ConstructorStoresPath_564) {
  std::string testPath = "test_file_constructor_564.tmp";
  Exiv2::FileIo fileIo(testPath);
  EXPECT_EQ(fileIo.path(), testPath);
}

// Test that path() returns the correct path after construction
TEST_F(FileIoTest_564, PathReturnsCorrectPath_564) {
  std::string testPath = "another_path_564.tmp";
  Exiv2::FileIo fileIo(testPath);
  EXPECT_EQ(fileIo.path(), testPath);
}

// Test that isopen() returns false before open
TEST_F(FileIoTest_564, IsOpenReturnsFalseBeforeOpen_564) {
  Exiv2::FileIo fileIo("nonexistent_file_564.tmp");
  EXPECT_FALSE(fileIo.isopen());
}

// Test that open() on a nonexistent file returns non-zero
TEST_F(FileIoTest_564, OpenNonexistentFileReturnsError_564) {
  Exiv2::FileIo fileIo("definitely_nonexistent_file_564.tmp");
  int result = fileIo.open();
  // Opening a nonexistent file for reading should fail
  EXPECT_NE(result, 0);
}

// Test open and close on an existing file
TEST_F(FileIoTest_564, OpenAndCloseExistingFile_564) {
  TempFile tmp("test_open_close_564.tmp", "hello");
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_TRUE(fileIo.isopen());
  EXPECT_EQ(fileIo.close(), 0);
  EXPECT_FALSE(fileIo.isopen());
}

// Test open with explicit mode
TEST_F(FileIoTest_564, OpenWithExplicitMode_564) {
  TempFile tmp("test_open_mode_564.tmp", "test data");
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open("rb"), 0);
  EXPECT_TRUE(fileIo.isopen());
  fileIo.close();
}

// Test size() returns correct file size
TEST_F(FileIoTest_564, SizeReturnsCorrectFileSize_564) {
  std::string content = "hello world";
  TempFile tmp("test_size_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.size(), content.size());
  fileIo.close();
}

// Test size() for empty file
TEST_F(FileIoTest_564, SizeReturnsZeroForEmptyFile_564) {
  TempFile tmp("test_empty_size_564.tmp", "");
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.size(), 0u);
  fileIo.close();
}

// Test read(byte*, size_t) reads correct data
TEST_F(FileIoTest_564, ReadBufferReadsCorrectData_564) {
  std::string content = "hello world";
  TempFile tmp("test_read_buf_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte buf[64] = {};
  size_t bytesRead = fileIo.read(buf, content.size());
  EXPECT_EQ(bytesRead, content.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), content);
  
  fileIo.close();
}

// Test read(byte*, size_t) when requesting more than available
TEST_F(FileIoTest_564, ReadBufferMoreThanAvailable_564) {
  std::string content = "short";
  TempFile tmp("test_read_more_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte buf[1024] = {};
  size_t bytesRead = fileIo.read(buf, 1024);
  EXPECT_EQ(bytesRead, content.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), content);
  
  fileIo.close();
}

// Test read(byte*, size_t) returns 0 when file is not open
TEST_F(FileIoTest_564, ReadBufferReturnsZeroWhenNotOpen_564) {
  Exiv2::FileIo fileIo("nonexistent_read_564.tmp");
  
  Exiv2::byte buf[64] = {};
  size_t bytesRead = fileIo.read(buf, 64);
  EXPECT_EQ(bytesRead, 0u);
}

// Test read(size_t) returns DataBuf with correct data
TEST_F(FileIoTest_564, ReadDataBufReturnsCorrectData_564) {
  std::string content = "DataBuf test content";
  TempFile tmp("test_read_databuf_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::DataBuf data = fileIo.read(content.size());
  EXPECT_EQ(data.size(), content.size());
  EXPECT_EQ(std::memcmp(data.c_data(), content.data(), content.size()), 0);
  
  fileIo.close();
}

// Test read(byte*, size_t) with zero count
TEST_F(FileIoTest_564, ReadZeroBytes_564) {
  std::string content = "some data";
  TempFile tmp("test_read_zero_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte buf[64] = {};
  size_t bytesRead = fileIo.read(buf, 0);
  EXPECT_EQ(bytesRead, 0u);
  
  fileIo.close();
}

// Test tell() returns correct position after read
TEST_F(FileIoTest_564, TellAfterRead_564) {
  std::string content = "0123456789";
  TempFile tmp("test_tell_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte buf[5];
  fileIo.read(buf, 5);
  EXPECT_EQ(fileIo.tell(), 5u);
  
  fileIo.close();
}

// Test seek from beginning
TEST_F(FileIoTest_564, SeekFromBeginning_564) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_beg_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.seek(5, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(fileIo.tell(), 5u);
  
  fileIo.close();
}

// Test seek from current position
TEST_F(FileIoTest_564, SeekFromCurrent_564) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_cur_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  fileIo.seek(3, Exiv2::BasicIo::beg);
  EXPECT_EQ(fileIo.seek(2, Exiv2::BasicIo::cur), 0);
  EXPECT_EQ(fileIo.tell(), 5u);
  
  fileIo.close();
}

// Test seek from end
TEST_F(FileIoTest_564, SeekFromEnd_564) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_end_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.seek(0, Exiv2::BasicIo::end), 0);
  EXPECT_EQ(fileIo.tell(), content.size());
  
  fileIo.close();
}

// Test getb() reads one byte at a time
TEST_F(FileIoTest_564, GetbReadsOneByte_564) {
  std::string content = "AB";
  TempFile tmp("test_getb_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.getb(), 'A');
  EXPECT_EQ(fileIo.getb(), 'B');
  
  fileIo.close();
}

// Test getb() returns EOF at end of file
TEST_F(FileIoTest_564, GetbReturnsEofAtEnd_564) {
  std::string content = "X";
  TempFile tmp("test_getb_eof_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.getb(), 'X');
  int result = fileIo.getb();
  EXPECT_EQ(result, EOF);
  
  fileIo.close();
}

// Test eof() returns true after reading past end
TEST_F(FileIoTest_564, EofAfterReadingPastEnd_564) {
  std::string content = "data";
  TempFile tmp("test_eof_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte buf[64];
  fileIo.read(buf, 64);  // Read more than available
  EXPECT_TRUE(fileIo.eof());
  
  fileIo.close();
}

// Test eof() returns false when not at end
TEST_F(FileIoTest_564, EofReturnsFalseWhenNotAtEnd_564) {
  std::string content = "more data here";
  TempFile tmp("test_eof_false_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte buf[4];
  fileIo.read(buf, 4);
  EXPECT_FALSE(fileIo.eof());
  
  fileIo.close();
}

// Test error() returns 0 on normal operation
TEST_F(FileIoTest_564, ErrorReturnsZeroOnNormalOperation_564) {
  std::string content = "test";
  TempFile tmp("test_error_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.error(), 0);
  
  fileIo.close();
}

// Test write(const byte*, size_t) writes data correctly
TEST_F(FileIoTest_564, WriteDataAndReadBack_564) {
  std::string filePath = "test_write_564.tmp";
  {
    Exiv2::FileIo fileIo(filePath);
    EXPECT_EQ(fileIo.open("w+b"), 0);
    
    std::string data = "written data";
    size_t written = fileIo.write(
        reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(written, data.size());
    fileIo.close();
  }
  
  // Read back and verify
  {
    Exiv2::FileIo fileIo(filePath);
    EXPECT_EQ(fileIo.open(), 0);
    
    Exiv2::byte buf[64] = {};
    size_t bytesRead = fileIo.read(buf, 64);
    EXPECT_EQ(bytesRead, 12u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), "written data");
    fileIo.close();
  }
  
  std::remove(filePath.c_str());
}

// Test putb() writes a single byte
TEST_F(FileIoTest_564, PutbWritesSingleByte_564) {
  std::string filePath = "test_putb_564.tmp";
  {
    Exiv2::FileIo fileIo(filePath);
    EXPECT_EQ(fileIo.open("w+b"), 0);
    EXPECT_EQ(fileIo.putb('Z'), 0);
    fileIo.close();
  }
  
  {
    Exiv2::FileIo fileIo(filePath);
    EXPECT_EQ(fileIo.open(), 0);
    EXPECT_EQ(fileIo.getb(), 'Z');
    fileIo.close();
  }
  
  std::remove(filePath.c_str());
}

// Test setPath changes the path
TEST_F(FileIoTest_564, SetPathChangesPath_564) {
  Exiv2::FileIo fileIo("original_path_564.tmp");
  EXPECT_EQ(fileIo.path(), "original_path_564.tmp");
  
  fileIo.setPath("new_path_564.tmp");
  EXPECT_EQ(fileIo.path(), "new_path_564.tmp");
}

// Test close on an already closed file
TEST_F(FileIoTest_564, CloseAlreadyClosedFile_564) {
  TempFile tmp("test_double_close_564.tmp", "data");
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.close(), 0);
  // Closing again - should handle gracefully
  int result = fileIo.close();
  // Result may be 0 or non-zero depending on implementation, but shouldn't crash
  (void)result;
}

// Test sequential reads
TEST_F(FileIoTest_564, SequentialReads_564) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("test_seq_read_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte buf1[5] = {};
  Exiv2::byte buf2[5] = {};
  
  EXPECT_EQ(fileIo.read(buf1, 5), 5u);
  EXPECT_EQ(fileIo.read(buf2, 5), 5u);
  
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf1), 5), "ABCDE");
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf2), 5), "FGHIJ");
  
  fileIo.close();
}

// Test seek and then read
TEST_F(FileIoTest_564, SeekThenRead_564) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_read_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.seek(7, Exiv2::BasicIo::beg), 0);
  
  Exiv2::byte buf[3] = {};
  EXPECT_EQ(fileIo.read(buf, 3), 3u);
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 3), "789");
  
  fileIo.close();
}

// Test reading from an empty file
TEST_F(FileIoTest_564, ReadFromEmptyFile_564) {
  TempFile tmp("test_empty_read_564.tmp", "");
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte buf[64] = {};
  size_t bytesRead = fileIo.read(buf, 64);
  EXPECT_EQ(bytesRead, 0u);
  
  fileIo.close();
}

// Test write followed by seek and read (read-write mode)
TEST_F(FileIoTest_564, WriteSeekRead_564) {
  std::string filePath = "test_write_seek_read_564.tmp";
  Exiv2::FileIo fileIo(filePath);
  
  EXPECT_EQ(fileIo.open("w+b"), 0);
  
  std::string data = "Hello, World!";
  fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  
  // Seek back to beginning
  EXPECT_EQ(fileIo.seek(0, Exiv2::BasicIo::beg), 0);
  
  Exiv2::byte buf[64] = {};
  size_t bytesRead = fileIo.read(buf, 64);
  EXPECT_EQ(bytesRead, data.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), data);
  
  fileIo.close();
  std::remove(filePath.c_str());
}

// Test large read
TEST_F(FileIoTest_564, LargeFileRead_564) {
  std::string filePath = "test_large_read_564.tmp";
  std::string largeContent(10000, 'X');
  TempFile tmp(filePath, largeContent);
  
  Exiv2::FileIo fileIo(tmp.path());
  EXPECT_EQ(fileIo.open(), 0);
  
  std::vector<Exiv2::byte> buf(10000);
  size_t bytesRead = fileIo.read(buf.data(), 10000);
  EXPECT_EQ(bytesRead, 10000u);
  
  for (size_t i = 0; i < bytesRead; ++i) {
    EXPECT_EQ(buf[i], 'X') << "Mismatch at index " << i;
  }
  
  fileIo.close();
}

// Test that tell() is 0 right after open
TEST_F(FileIoTest_564, TellIsZeroAfterOpen_564) {
  std::string content = "test content";
  TempFile tmp("test_tell_zero_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.tell(), 0u);
  
  fileIo.close();
}

// Test mmap and munmap
TEST_F(FileIoTest_564, MmapAndMunmap_564) {
  std::string content = "mmap test data";
  TempFile tmp("test_mmap_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  
  Exiv2::byte* mapped = fileIo.mmap(false);
  EXPECT_NE(mapped, nullptr);
  EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);
  
  EXPECT_EQ(fileIo.munmap(), 0);
  fileIo.close();
}

// Test multiple open/close cycles
TEST_F(FileIoTest_564, MultipleOpenCloseCycles_564) {
  std::string content = "cycle test";
  TempFile tmp("test_cycle_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(fileIo.open(), 0);
    EXPECT_TRUE(fileIo.isopen());
    
    Exiv2::byte buf[64] = {};
    size_t bytesRead = fileIo.read(buf, 64);
    EXPECT_EQ(bytesRead, content.size());
    
    EXPECT_EQ(fileIo.close(), 0);
    EXPECT_FALSE(fileIo.isopen());
  }
}

// Test seek with negative offset from end
TEST_F(FileIoTest_564, SeekNegativeFromEnd_564) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_neg_end_564.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_EQ(fileIo.seek(-3, Exiv2::BasicIo::end), 0);
  EXPECT_EQ(fileIo.tell(), 7u);
  
  Exiv2::byte buf[3] = {};
  EXPECT_EQ(fileIo.read(buf, 3), 3u);
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 3), "789");
  
  fileIo.close();
}

// Test write from BasicIo (FileIo to FileIo)
TEST_F(FileIoTest_564, WriteFromBasicIo_564) {
  std::string srcContent = "source content";
  TempFile srcTmp("test_write_src_564.tmp", srcContent);
  std::string dstPath = "test_write_dst_564.tmp";
  
  Exiv2::FileIo srcIo(srcTmp.path());
  Exiv2::FileIo dstIo(dstPath);
  
  EXPECT_EQ(srcIo.open(), 0);
  EXPECT_EQ(dstIo.open("w+b"), 0);
  
  size_t written = dstIo.write(srcIo);
  EXPECT_EQ(written, srcContent.size());
  
  srcIo.close();
  
  // Verify written content
  dstIo.seek(0, Exiv2::BasicIo::beg);
  Exiv2::byte buf[64] = {};
  size_t bytesRead = dstIo.read(buf, 64);
  EXPECT_EQ(bytesRead, srcContent.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), srcContent);
  
  dstIo.close();
  std::remove(dstPath.c_str());
}
