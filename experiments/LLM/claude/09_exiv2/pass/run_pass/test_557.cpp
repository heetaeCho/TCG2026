#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <filesystem>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace {

// Helper to create a temporary file with given content
class TempFile {
 public:
  explicit TempFile(const std::string& name, const std::string& content = "") : path_(name) {
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

class FileIoTest_557 : public ::testing::Test {
 protected:
  void SetUp() override {
  }
  void TearDown() override {
  }
};

// Test that path() returns the path passed to constructor
TEST_F(FileIoTest_557, PathReturnsConstructorPath_557) {
  std::string testPath = "test_path_file_557.tmp";
  Exiv2::FileIo fileIo(testPath);
  EXPECT_EQ(fileIo.path(), testPath);
}

// Test that isopen() returns false before opening
TEST_F(FileIoTest_557, IsNotOpenByDefault_557) {
  TempFile tmp("test_isopen_557.tmp", "data");
  Exiv2::FileIo fileIo(tmp.path());
  EXPECT_FALSE(fileIo.isopen());
}

// Test that open() works and isopen() returns true after opening
TEST_F(FileIoTest_557, OpenSucceeds_557) {
  TempFile tmp("test_open_557.tmp", "hello");
  Exiv2::FileIo fileIo(tmp.path());
  EXPECT_EQ(fileIo.open(), 0);
  EXPECT_TRUE(fileIo.isopen());
  fileIo.close();
}

// Test that open with mode succeeds
TEST_F(FileIoTest_557, OpenWithModeSucceeds_557) {
  TempFile tmp("test_open_mode_557.tmp", "hello");
  Exiv2::FileIo fileIo(tmp.path());
  EXPECT_EQ(fileIo.open("rb"), 0);
  EXPECT_TRUE(fileIo.isopen());
  fileIo.close();
}

// Test that close works
TEST_F(FileIoTest_557, CloseSucceeds_557) {
  TempFile tmp("test_close_557.tmp", "data");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  EXPECT_EQ(fileIo.close(), 0);
  EXPECT_FALSE(fileIo.isopen());
}

// Test that open fails for non-existent file
TEST_F(FileIoTest_557, OpenFailsForNonExistentFile_557) {
  Exiv2::FileIo fileIo("nonexistent_file_557_xyz.tmp");
  EXPECT_NE(fileIo.open(), 0);
}

// Test tell() returns 0 at beginning of file
TEST_F(FileIoTest_557, TellReturnsZeroAtStart_557) {
  TempFile tmp("test_tell_557.tmp", "hello world");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  EXPECT_EQ(fileIo.tell(), 0u);
  fileIo.close();
}

// Test tell() after reading
TEST_F(FileIoTest_557, TellAfterRead_557) {
  std::string content = "hello world";
  TempFile tmp("test_tell_read_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::byte buf[5];
  size_t bytesRead = fileIo.read(buf, 5);
  EXPECT_EQ(bytesRead, 5u);
  EXPECT_EQ(fileIo.tell(), 5u);
  fileIo.close();
}

// Test tell() after seek
TEST_F(FileIoTest_557, TellAfterSeek_557) {
  std::string content = "0123456789";
  TempFile tmp("test_tell_seek_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  fileIo.seek(7, Exiv2::BasicIo::beg);
  EXPECT_EQ(fileIo.tell(), 7u);
  fileIo.close();
}

// Test size() returns correct file size
TEST_F(FileIoTest_557, SizeReturnsCorrectValue_557) {
  std::string content = "hello world!";
  TempFile tmp("test_size_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  EXPECT_EQ(fileIo.size(), content.size());
  fileIo.close();
}

// Test size() for empty file
TEST_F(FileIoTest_557, SizeForEmptyFile_557) {
  TempFile tmp("test_size_empty_557.tmp", "");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  EXPECT_EQ(fileIo.size(), 0u);
  fileIo.close();
}

// Test read with DataBuf
TEST_F(FileIoTest_557, ReadDataBuf_557) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("test_read_databuf_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::DataBuf buf = fileIo.read(5);
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_EQ(std::memcmp(buf.data(), "ABCDE", 5), 0);
  fileIo.close();
}

// Test read into buffer
TEST_F(FileIoTest_557, ReadIntoBuffer_557) {
  std::string content = "0123456789";
  TempFile tmp("test_read_buf_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::byte buf[10];
  size_t n = fileIo.read(buf, 10);
  EXPECT_EQ(n, 10u);
  EXPECT_EQ(std::memcmp(buf, content.data(), 10), 0);
  fileIo.close();
}

// Test read beyond file size
TEST_F(FileIoTest_557, ReadBeyondFileSize_557) {
  std::string content = "short";
  TempFile tmp("test_read_beyond_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::byte buf[100];
  size_t n = fileIo.read(buf, 100);
  EXPECT_EQ(n, content.size());
  fileIo.close();
}

// Test getb() reads single byte
TEST_F(FileIoTest_557, GetbReadsSingleByte_557) {
  std::string content = "AB";
  TempFile tmp("test_getb_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  int b = fileIo.getb();
  EXPECT_EQ(b, 'A');
  b = fileIo.getb();
  EXPECT_EQ(b, 'B');
  fileIo.close();
}

// Test getb() at EOF returns EOF
TEST_F(FileIoTest_557, GetbAtEofReturnsEof_557) {
  TempFile tmp("test_getb_eof_557.tmp", "X");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  fileIo.getb();  // read 'X'
  int b = fileIo.getb();
  EXPECT_EQ(b, EOF);
  fileIo.close();
}

// Test eof() after reading to end
TEST_F(FileIoTest_557, EofAfterReadingToEnd_557) {
  TempFile tmp("test_eof_557.tmp", "AB");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::byte buf[10];
  fileIo.read(buf, 10);
  EXPECT_TRUE(fileIo.eof());
  fileIo.close();
}

// Test eof() before reaching end
TEST_F(FileIoTest_557, EofFalseBeforeEnd_557) {
  TempFile tmp("test_eof_false_557.tmp", "ABCDEF");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::byte buf[2];
  fileIo.read(buf, 2);
  EXPECT_FALSE(fileIo.eof());
  fileIo.close();
}

// Test error() returns 0 on normal operation
TEST_F(FileIoTest_557, ErrorReturnsZero_557) {
  TempFile tmp("test_error_557.tmp", "data");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  EXPECT_EQ(fileIo.error(), 0);
  fileIo.close();
}

// Test write data and then read back
TEST_F(FileIoTest_557, WriteAndReadBack_557) {
  std::string filePath = "test_write_557.tmp";
  {
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("wb");
    const Exiv2::byte data[] = "Hello, World!";
    size_t written = fileIo.write(data, 13);
    EXPECT_EQ(written, 13u);
    fileIo.close();
  }
  {
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("rb");
    Exiv2::byte buf[13];
    size_t n = fileIo.read(buf, 13);
    EXPECT_EQ(n, 13u);
    EXPECT_EQ(std::memcmp(buf, "Hello, World!", 13), 0);
    fileIo.close();
  }
  std::remove(filePath.c_str());
}

// Test putb writes a single byte
TEST_F(FileIoTest_557, PutbWritesSingleByte_557) {
  std::string filePath = "test_putb_557.tmp";
  {
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("wb");
    int result = fileIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    fileIo.close();
  }
  {
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("rb");
    int b = fileIo.getb();
    EXPECT_EQ(b, 0x42);
    fileIo.close();
  }
  std::remove(filePath.c_str());
}

// Test seek from beginning
TEST_F(FileIoTest_557, SeekFromBeginning_557) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_beg_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  int ret = fileIo.seek(5, Exiv2::BasicIo::beg);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(fileIo.tell(), 5u);
  fileIo.close();
}

// Test seek from current position
TEST_F(FileIoTest_557, SeekFromCurrent_557) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_cur_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  fileIo.seek(3, Exiv2::BasicIo::beg);
  int ret = fileIo.seek(2, Exiv2::BasicIo::cur);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(fileIo.tell(), 5u);
  fileIo.close();
}

// Test seek from end
TEST_F(FileIoTest_557, SeekFromEnd_557) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_end_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  int ret = fileIo.seek(-3, Exiv2::BasicIo::end);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(fileIo.tell(), 7u);
  fileIo.close();
}

// Test seek to position 0 (boundary)
TEST_F(FileIoTest_557, SeekToZero_557) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_zero_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  fileIo.seek(5, Exiv2::BasicIo::beg);
  fileIo.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(fileIo.tell(), 0u);
  fileIo.close();
}

// Test setPath changes the path
TEST_F(FileIoTest_557, SetPathChangesPath_557) {
  Exiv2::FileIo fileIo("original_path_557.tmp");
  EXPECT_EQ(fileIo.path(), "original_path_557.tmp");
  fileIo.setPath("new_path_557.tmp");
  EXPECT_EQ(fileIo.path(), "new_path_557.tmp");
}

// Test tell after multiple reads
TEST_F(FileIoTest_557, TellAfterMultipleReads_557) {
  std::string content = "ABCDEFGHIJKLMNOP";
  TempFile tmp("test_tell_multi_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();

  Exiv2::byte buf[4];
  fileIo.read(buf, 4);
  EXPECT_EQ(fileIo.tell(), 4u);

  fileIo.read(buf, 4);
  EXPECT_EQ(fileIo.tell(), 8u);

  fileIo.read(buf, 4);
  EXPECT_EQ(fileIo.tell(), 12u);

  fileIo.close();
}

// Test write from BasicIo source
TEST_F(FileIoTest_557, WriteFromBasicIoSource_557) {
  std::string srcContent = "SourceData";
  TempFile srcTmp("test_src_557.tmp", srcContent);
  std::string dstPath = "test_dst_557.tmp";

  {
    Exiv2::FileIo srcIo(srcTmp.path());
    srcIo.open("rb");

    Exiv2::FileIo dstIo(dstPath);
    dstIo.open("wb");
    size_t written = dstIo.write(srcIo);
    EXPECT_EQ(written, srcContent.size());
    dstIo.close();
    srcIo.close();
  }

  {
    Exiv2::FileIo dstIo(dstPath);
    dstIo.open("rb");
    Exiv2::byte buf[20];
    size_t n = dstIo.read(buf, 20);
    EXPECT_EQ(n, srcContent.size());
    EXPECT_EQ(std::memcmp(buf, srcContent.data(), n), 0);
    dstIo.close();
  }

  std::remove(dstPath.c_str());
}

// Test tell after write
TEST_F(FileIoTest_557, TellAfterWrite_557) {
  std::string filePath = "test_tell_write_557.tmp";
  Exiv2::FileIo fileIo(filePath);
  fileIo.open("wb");
  const Exiv2::byte data[] = "12345";
  fileIo.write(data, 5);
  EXPECT_EQ(fileIo.tell(), 5u);
  fileIo.close();
  std::remove(filePath.c_str());
}

// Test reading zero bytes
TEST_F(FileIoTest_557, ReadZeroBytes_557) {
  TempFile tmp("test_read_zero_557.tmp", "data");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::byte buf[1];
  size_t n = fileIo.read(buf, 0);
  EXPECT_EQ(n, 0u);
  EXPECT_EQ(fileIo.tell(), 0u);
  fileIo.close();
}

// Test writing zero bytes
TEST_F(FileIoTest_557, WriteZeroBytes_557) {
  std::string filePath = "test_write_zero_557.tmp";
  Exiv2::FileIo fileIo(filePath);
  fileIo.open("wb");
  const Exiv2::byte data[] = "";
  size_t written = fileIo.write(data, 0);
  EXPECT_EQ(written, 0u);
  fileIo.close();
  std::remove(filePath.c_str());
}

// Test that closing an already closed file doesn't crash
TEST_F(FileIoTest_557, CloseAlreadyClosed_557) {
  TempFile tmp("test_close_twice_557.tmp", "data");
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  fileIo.close();
  // Second close should not crash
  int result = fileIo.close();
  // Result may be 0 or an error, but should not crash
  (void)result;
}

// Test mmap and munmap
TEST_F(FileIoTest_557, MmapAndMunmap_557) {
  std::string content = "MmapTestData";
  TempFile tmp("test_mmap_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::byte* mapped = fileIo.mmap(false);
  ASSERT_NE(mapped, nullptr);
  EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);
  int ret = fileIo.munmap();
  EXPECT_EQ(ret, 0);
  fileIo.close();
}

// Test opening in write mode, writing, closing, then reading back verifies size
TEST_F(FileIoTest_557, WriteThenCheckSize_557) {
  std::string filePath = "test_write_size_557.tmp";
  {
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("wb");
    const Exiv2::byte data[] = "ABCDEFGHIJ";
    fileIo.write(data, 10);
    fileIo.close();
  }
  {
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("rb");
    EXPECT_EQ(fileIo.size(), 10u);
    fileIo.close();
  }
  std::remove(filePath.c_str());
}

// Test transfer from another FileIo
TEST_F(FileIoTest_557, TransferFromFileIo_557) {
  std::string srcContent = "TransferData";
  TempFile srcTmp("test_transfer_src_557.tmp", srcContent);
  std::string dstPath = "test_transfer_dst_557.tmp";

  // Create destination file first
  {
    std::ofstream ofs(dstPath);
    ofs << "old";
    ofs.close();
  }

  {
    Exiv2::FileIo srcIo(srcTmp.path());
    Exiv2::FileIo dstIo(dstPath);
    dstIo.transfer(srcIo);
  }

  {
    Exiv2::FileIo dstIo(dstPath);
    dstIo.open("rb");
    EXPECT_EQ(dstIo.size(), srcContent.size());
    Exiv2::byte buf[20];
    size_t n = dstIo.read(buf, 20);
    EXPECT_EQ(n, srcContent.size());
    EXPECT_EQ(std::memcmp(buf, srcContent.data(), n), 0);
    dstIo.close();
  }

  std::remove(dstPath.c_str());
}

// Test seek to beginning after reading entire file
TEST_F(FileIoTest_557, SeekToBeginningAfterFullRead_557) {
  std::string content = "FullRead";
  TempFile tmp("test_seek_begin_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  Exiv2::byte buf[100];
  fileIo.read(buf, 100);
  EXPECT_TRUE(fileIo.eof());
  fileIo.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(fileIo.tell(), 0u);
  fileIo.close();
}

// Test large file seek/tell consistency
TEST_F(FileIoTest_557, LargeSeekTellConsistency_557) {
  std::string content(10000, 'X');
  TempFile tmp("test_large_557.tmp", content);
  Exiv2::FileIo fileIo(tmp.path());
  fileIo.open();
  fileIo.seek(9999, Exiv2::BasicIo::beg);
  EXPECT_EQ(fileIo.tell(), 9999u);
  fileIo.close();
}
