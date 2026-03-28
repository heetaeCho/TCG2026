#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <filesystem>

#include "exiv2/basicio.hpp"

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

class FileIoTest_560 : public ::testing::Test {
 protected:
  void SetUp() override {
  }
  void TearDown() override {
  }
};

// Test that path() returns the path given at construction
TEST_F(FileIoTest_560, PathReturnsConstructedPath_560) {
  Exiv2::FileIo fio("test_path_file.txt");
  EXPECT_EQ(fio.path(), "test_path_file.txt");
}

// Test that isopen() returns false before opening
TEST_F(FileIoTest_560, IsOpenReturnsFalseBeforeOpen_560) {
  Exiv2::FileIo fio("nonexistent_file_560.txt");
  EXPECT_FALSE(fio.isopen());
}

// Test open with mode on an existing file returns 0
TEST_F(FileIoTest_560, OpenExistingFileReturnsZero_560) {
  TempFile tmp("test_open_560.txt", "hello");
  Exiv2::FileIo fio(tmp.path());
  int result = fio.open("rb");
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(fio.isopen());
  fio.close();
}

// Test open with mode on a non-existing file returns 1
TEST_F(FileIoTest_560, OpenNonExistingFileReturnsOne_560) {
  Exiv2::FileIo fio("this_file_does_not_exist_560.txt");
  int result = fio.open("rb");
  EXPECT_EQ(result, 1);
  EXPECT_FALSE(fio.isopen());
}

// Test close on an opened file
TEST_F(FileIoTest_560, CloseAfterOpenSucceeds_560) {
  TempFile tmp("test_close_560.txt", "data");
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  EXPECT_TRUE(fio.isopen());
  int result = fio.close();
  EXPECT_EQ(result, 0);
  EXPECT_FALSE(fio.isopen());
}

// Test close on a file that was never opened
TEST_F(FileIoTest_560, CloseWithoutOpenSucceeds_560) {
  Exiv2::FileIo fio("nonexistent_560.txt");
  int result = fio.close();
  EXPECT_EQ(result, 0);
}

// Test size() on an existing file
TEST_F(FileIoTest_560, SizeReturnsCorrectFileSize_560) {
  std::string content = "hello world";
  TempFile tmp("test_size_560.txt", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  EXPECT_EQ(fio.size(), content.size());
  fio.close();
}

// Test size() on an empty file
TEST_F(FileIoTest_560, SizeReturnsZeroForEmptyFile_560) {
  TempFile tmp("test_empty_size_560.txt", "");
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  EXPECT_EQ(fio.size(), 0u);
  fio.close();
}

// Test write and read roundtrip
TEST_F(FileIoTest_560, WriteAndReadRoundtrip_560) {
  std::string filename = "test_write_read_560.txt";
  {
    Exiv2::FileIo fio(filename);
    fio.open("wb");
    const Exiv2::byte data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    size_t written = fio.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    fio.close();
  }
  {
    Exiv2::FileIo fio(filename);
    fio.open("rb");
    Exiv2::byte buf[5] = {};
    size_t bytesRead = fio.read(buf, 5);
    EXPECT_EQ(bytesRead, 5u);
    EXPECT_EQ(buf[0], 0x41);
    EXPECT_EQ(buf[1], 0x42);
    EXPECT_EQ(buf[2], 0x43);
    EXPECT_EQ(buf[3], 0x44);
    EXPECT_EQ(buf[4], 0x45);
    fio.close();
  }
  std::remove(filename.c_str());
}

// Test read with DataBuf overload
TEST_F(FileIoTest_560, ReadDataBufOverload_560) {
  std::string content = "ABCDEF";
  TempFile tmp("test_databuf_read_560.txt", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  Exiv2::DataBuf dbuf = fio.read(4);
  EXPECT_EQ(dbuf.size(), 4u);
  EXPECT_EQ(dbuf.data()[0], 'A');
  EXPECT_EQ(dbuf.data()[1], 'B');
  EXPECT_EQ(dbuf.data()[2], 'C');
  EXPECT_EQ(dbuf.data()[3], 'D');
  fio.close();
}

// Test tell() returns current position
TEST_F(FileIoTest_560, TellReturnsCurrentPosition_560) {
  std::string content = "0123456789";
  TempFile tmp("test_tell_560.txt", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  EXPECT_EQ(fio.tell(), 0u);
  Exiv2::byte buf[3];
  fio.read(buf, 3);
  EXPECT_EQ(fio.tell(), 3u);
  fio.close();
}

// Test seek from beginning
TEST_F(FileIoTest_560, SeekFromBeginning_560) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("test_seek_beg_560.txt", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  int result = fio.seek(5, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(fio.tell(), 5u);
  int ch = fio.getb();
  EXPECT_EQ(ch, 'F');
  fio.close();
}

// Test seek from current position
TEST_F(FileIoTest_560, SeekFromCurrent_560) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("test_seek_cur_560.txt", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  fio.seek(3, Exiv2::BasicIo::beg);
  fio.seek(2, Exiv2::BasicIo::cur);
  EXPECT_EQ(fio.tell(), 5u);
  fio.close();
}

// Test seek from end
TEST_F(FileIoTest_560, SeekFromEnd_560) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("test_seek_end_560.txt", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  fio.seek(-3, Exiv2::BasicIo::end);
  int ch = fio.getb();
  EXPECT_EQ(ch, 'H');
  fio.close();
}

// Test getb() returns EOF at end of file
TEST_F(FileIoTest_560, GetbReturnsEOFAtEnd_560) {
  TempFile tmp("test_getb_eof_560.txt", "A");
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  int ch = fio.getb();
  EXPECT_EQ(ch, 'A');
  ch = fio.getb();
  EXPECT_EQ(ch, EOF);
  fio.close();
}

// Test eof() after reading past end
TEST_F(FileIoTest_560, EofAfterReadingPastEnd_560) {
  TempFile tmp("test_eof_560.txt", "AB");
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  EXPECT_FALSE(fio.eof());
  Exiv2::byte buf[10];
  fio.read(buf, 10);
  EXPECT_TRUE(fio.eof());
  fio.close();
}

// Test error() returns 0 for normal operation
TEST_F(FileIoTest_560, ErrorReturnsZeroNormally_560) {
  TempFile tmp("test_error_560.txt", "data");
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  EXPECT_EQ(fio.error(), 0);
  fio.close();
}

// Test putb writes a single byte
TEST_F(FileIoTest_560, PutbWritesSingleByte_560) {
  std::string filename = "test_putb_560.txt";
  {
    Exiv2::FileIo fio(filename);
    fio.open("wb");
    int result = fio.putb(0x42);
    EXPECT_EQ(result, 0x42);
    fio.close();
  }
  {
    Exiv2::FileIo fio(filename);
    fio.open("rb");
    int ch = fio.getb();
    EXPECT_EQ(ch, 0x42);
    fio.close();
  }
  std::remove(filename.c_str());
}

// Test opening the same file multiple times (second open should close first)
TEST_F(FileIoTest_560, OpenClosesExistingBeforeReopening_560) {
  TempFile tmp("test_reopen_560.txt", "test data");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(fio.open("rb"), 0);
  EXPECT_TRUE(fio.isopen());
  // Opening again should close existing and reopen
  EXPECT_EQ(fio.open("rb"), 0);
  EXPECT_TRUE(fio.isopen());
  fio.close();
}

// Test write returns 0 when writing 0 bytes
TEST_F(FileIoTest_560, WriteZeroBytesReturnsZero_560) {
  std::string filename = "test_write_zero_560.txt";
  Exiv2::FileIo fio(filename);
  fio.open("wb");
  const Exiv2::byte data[] = {0x00};
  size_t written = fio.write(data, 0);
  EXPECT_EQ(written, 0u);
  fio.close();
  std::remove(filename.c_str());
}

// Test reading 0 bytes
TEST_F(FileIoTest_560, ReadZeroBytesReturnsZero_560) {
  TempFile tmp("test_read_zero_560.txt", "data");
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  Exiv2::byte buf[1];
  size_t bytesRead = fio.read(buf, 0);
  EXPECT_EQ(bytesRead, 0u);
  fio.close();
}

// Test setPath changes the path
TEST_F(FileIoTest_560, SetPathChangesPath_560) {
  Exiv2::FileIo fio("original_path_560.txt");
  EXPECT_EQ(fio.path(), "original_path_560.txt");
  fio.setPath("new_path_560.txt");
  EXPECT_EQ(fio.path(), "new_path_560.txt");
}

// Test open with write mode creates a new file
TEST_F(FileIoTest_560, OpenWriteModeCreatesFile_560) {
  std::string filename = "test_create_560.txt";
  std::remove(filename.c_str());  // ensure it doesn't exist
  Exiv2::FileIo fio(filename);
  int result = fio.open("wb");
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(fio.isopen());
  fio.close();
  // Verify file was created
  std::ifstream check(filename);
  EXPECT_TRUE(check.good());
  check.close();
  std::remove(filename.c_str());
}

// Test large write and read
TEST_F(FileIoTest_560, LargeWriteAndRead_560) {
  std::string filename = "test_large_560.txt";
  const size_t dataSize = 100000;
  std::vector<Exiv2::byte> data(dataSize);
  for (size_t i = 0; i < dataSize; ++i) {
    data[i] = static_cast<Exiv2::byte>(i % 256);
  }
  {
    Exiv2::FileIo fio(filename);
    fio.open("wb");
    size_t written = fio.write(data.data(), dataSize);
    EXPECT_EQ(written, dataSize);
    fio.close();
  }
  {
    Exiv2::FileIo fio(filename);
    fio.open("rb");
    EXPECT_EQ(fio.size(), dataSize);
    std::vector<Exiv2::byte> readBuf(dataSize);
    size_t bytesRead = fio.read(readBuf.data(), dataSize);
    EXPECT_EQ(bytesRead, dataSize);
    EXPECT_EQ(data, readBuf);
    fio.close();
  }
  std::remove(filename.c_str());
}

// Test that open with invalid mode string fails
TEST_F(FileIoTest_560, OpenWithInvalidModeString_560) {
  TempFile tmp("test_invalid_mode_560.txt", "data");
  Exiv2::FileIo fio(tmp.path());
  // "xyz" is not a valid fopen mode
  int result = fio.open("xyz");
  EXPECT_EQ(result, 1);
}

// Test reading more than available returns actual bytes read
TEST_F(FileIoTest_560, ReadMoreThanAvailable_560) {
  std::string content = "short";
  TempFile tmp("test_read_more_560.txt", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  Exiv2::byte buf[100] = {};
  size_t bytesRead = fio.read(buf, 100);
  EXPECT_EQ(bytesRead, content.size());
  EXPECT_EQ(buf[0], 's');
  EXPECT_EQ(buf[4], 't');
  fio.close();
}

// Test multiple sequential reads
TEST_F(FileIoTest_560, MultipleSequentialReads_560) {
  std::string content = "ABCDEF";
  TempFile tmp("test_seq_read_560.txt", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open("rb");
  
  Exiv2::byte buf1[3] = {};
  size_t r1 = fio.read(buf1, 3);
  EXPECT_EQ(r1, 3u);
  EXPECT_EQ(buf1[0], 'A');
  EXPECT_EQ(buf1[1], 'B');
  EXPECT_EQ(buf1[2], 'C');
  
  Exiv2::byte buf2[3] = {};
  size_t r2 = fio.read(buf2, 3);
  EXPECT_EQ(r2, 3u);
  EXPECT_EQ(buf2[0], 'D');
  EXPECT_EQ(buf2[1], 'E');
  EXPECT_EQ(buf2[2], 'F');
  
  fio.close();
}

// Test write from another BasicIo (FileIo as source)
TEST_F(FileIoTest_560, WriteFromAnotherBasicIo_560) {
  std::string srcContent = "source data for transfer";
  TempFile srcFile("test_src_560.txt", srcContent);
  std::string dstFilename = "test_dst_560.txt";
  
  Exiv2::FileIo src(srcFile.path());
  src.open("rb");
  
  Exiv2::FileIo dst(dstFilename);
  dst.open("wb");
  size_t written = dst.write(src);
  EXPECT_EQ(written, srcContent.size());
  dst.close();
  src.close();
  
  // Verify
  Exiv2::FileIo verify(dstFilename);
  verify.open("rb");
  EXPECT_EQ(verify.size(), srcContent.size());
  Exiv2::byte buf[100] = {};
  verify.read(buf, srcContent.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), srcContent.size()), srcContent);
  verify.close();
  
  std::remove(dstFilename.c_str());
}
