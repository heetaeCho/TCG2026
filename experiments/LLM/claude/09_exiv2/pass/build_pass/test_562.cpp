#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

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

class FileIoTest_562 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that path() returns the path given at construction
TEST_F(FileIoTest_562, PathReturnsConstructedPath_562) {
  Exiv2::FileIo fio("test_path_562.tmp");
  EXPECT_EQ(fio.path(), "test_path_562.tmp");
}

// Test that isopen() returns false before opening
TEST_F(FileIoTest_562, IsOpenReturnsFalseBeforeOpen_562) {
  Exiv2::FileIo fio("nonexistent_562.tmp");
  EXPECT_FALSE(fio.isopen());
}

// Test that open() on a nonexistent file returns non-zero
TEST_F(FileIoTest_562, OpenNonexistentFileReturnsError_562) {
  Exiv2::FileIo fio("definitely_does_not_exist_562.tmp");
  int rc = fio.open();
  // Opening a nonexistent file for reading should fail
  EXPECT_NE(rc, 0);
}

// Test open and close on an existing file
TEST_F(FileIoTest_562, OpenAndCloseExistingFile_562) {
  TempFile tmp("fileio_test_open_close_562.tmp", "hello");
  Exiv2::FileIo fio(tmp.path());
  
  int rc = fio.open();
  EXPECT_EQ(rc, 0);
  EXPECT_TRUE(fio.isopen());
  
  rc = fio.close();
  EXPECT_EQ(rc, 0);
  EXPECT_FALSE(fio.isopen());
}

// Test open with mode string
TEST_F(FileIoTest_562, OpenWithModeString_562) {
  TempFile tmp("fileio_test_mode_562.tmp", "data");
  Exiv2::FileIo fio(tmp.path());
  
  int rc = fio.open("rb");
  EXPECT_EQ(rc, 0);
  EXPECT_TRUE(fio.isopen());
  
  fio.close();
}

// Test size() returns correct file size
TEST_F(FileIoTest_562, SizeReturnsCorrectValue_562) {
  std::string content = "Hello, World!";
  TempFile tmp("fileio_test_size_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  EXPECT_EQ(fio.size(), content.size());
  fio.close();
}

// Test read returns correct data
TEST_F(FileIoTest_562, ReadReturnsCorrectData_562) {
  std::string content = "TestData562";
  TempFile tmp("fileio_test_read_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  Exiv2::DataBuf buf = fio.read(content.size());
  EXPECT_EQ(buf.size(), content.size());
  EXPECT_EQ(std::memcmp(buf.data(), content.data(), content.size()), 0);
  fio.close();
}

// Test read with byte buffer
TEST_F(FileIoTest_562, ReadIntoBuffer_562) {
  std::string content = "BufferRead562";
  TempFile tmp("fileio_test_readbuf_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  std::vector<Exiv2::byte> buf(content.size());
  size_t bytesRead = fio.read(buf.data(), buf.size());
  EXPECT_EQ(bytesRead, content.size());
  EXPECT_EQ(std::memcmp(buf.data(), content.data(), content.size()), 0);
  fio.close();
}

// Test reading more bytes than available
TEST_F(FileIoTest_562, ReadMoreThanAvailable_562) {
  std::string content = "Short";
  TempFile tmp("fileio_test_readmore_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  std::vector<Exiv2::byte> buf(100, 0);
  size_t bytesRead = fio.read(buf.data(), 100);
  EXPECT_EQ(bytesRead, content.size());
  fio.close();
}

// Test write and then read back
TEST_F(FileIoTest_562, WriteAndReadBack_562) {
  std::string filename = "fileio_test_write_562.tmp";
  {
    Exiv2::FileIo fio(filename);
    fio.open("wb");
    std::string data = "WriteTest562";
    size_t written = fio.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(written, data.size());
    fio.close();
  }
  
  {
    Exiv2::FileIo fio(filename);
    fio.open();
    Exiv2::DataBuf buf = fio.read(12);
    EXPECT_EQ(buf.size(), 12u);
    EXPECT_EQ(std::memcmp(buf.data(), "WriteTest562", 12), 0);
    fio.close();
  }
  
  std::remove(filename.c_str());
}

// Test tell() returns correct position
TEST_F(FileIoTest_562, TellReturnsCorrectPosition_562) {
  std::string content = "0123456789";
  TempFile tmp("fileio_test_tell_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  EXPECT_EQ(fio.tell(), 0u);
  
  std::vector<Exiv2::byte> buf(5);
  fio.read(buf.data(), 5);
  EXPECT_EQ(fio.tell(), 5u);
  fio.close();
}

// Test seek from beginning
TEST_F(FileIoTest_562, SeekFromBeginning_562) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("fileio_test_seek_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  int rc = fio.seek(5, Exiv2::BasicIo::beg);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(fio.tell(), 5u);
  
  int ch = fio.getb();
  EXPECT_EQ(ch, 'F');
  fio.close();
}

// Test seek from current position
TEST_F(FileIoTest_562, SeekFromCurrent_562) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("fileio_test_seekcur_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  fio.seek(3, Exiv2::BasicIo::beg);
  fio.seek(2, Exiv2::BasicIo::cur);
  EXPECT_EQ(fio.tell(), 5u);
  fio.close();
}

// Test seek from end
TEST_F(FileIoTest_562, SeekFromEnd_562) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("fileio_test_seekend_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  fio.seek(-3, Exiv2::BasicIo::end);
  EXPECT_EQ(fio.tell(), 7u);
  
  int ch = fio.getb();
  EXPECT_EQ(ch, 'H');
  fio.close();
}

// Test getb() reads one byte at a time
TEST_F(FileIoTest_562, GetbReadsOneByte_562) {
  std::string content = "XY";
  TempFile tmp("fileio_test_getb_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  EXPECT_EQ(fio.getb(), 'X');
  EXPECT_EQ(fio.getb(), 'Y');
  fio.close();
}

// Test getb at EOF returns EOF
TEST_F(FileIoTest_562, GetbAtEofReturnsEof_562) {
  std::string content = "A";
  TempFile tmp("fileio_test_getbeof_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  fio.getb();  // read 'A'
  int result = fio.getb();  // should be EOF
  EXPECT_EQ(result, EOF);
  fio.close();
}

// Test putb writes a byte
TEST_F(FileIoTest_562, PutbWritesByte_562) {
  std::string filename = "fileio_test_putb_562.tmp";
  {
    Exiv2::FileIo fio(filename);
    fio.open("wb");
    int rc = fio.putb(0x42);
    EXPECT_EQ(rc, 0x42);
    fio.close();
  }
  
  {
    Exiv2::FileIo fio(filename);
    fio.open();
    int ch = fio.getb();
    EXPECT_EQ(ch, 0x42);
    fio.close();
  }
  
  std::remove(filename.c_str());
}

// Test eof() after reading entire file
TEST_F(FileIoTest_562, EofAfterFullRead_562) {
  std::string content = "AB";
  TempFile tmp("fileio_test_eof_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  fio.read(content.size());
  // After reading all data, next read should trigger eof
  fio.getb();
  EXPECT_TRUE(fio.eof());
  fio.close();
}

// Test eof() is false at beginning of file
TEST_F(FileIoTest_562, EofFalseAtStart_562) {
  std::string content = "data";
  TempFile tmp("fileio_test_eoffalse_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  EXPECT_FALSE(fio.eof());
  fio.close();
}

// Test error() returns 0 for normal operations
TEST_F(FileIoTest_562, ErrorReturnsZeroNormally_562) {
  std::string content = "noerror";
  TempFile tmp("fileio_test_error_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  EXPECT_EQ(fio.error(), 0);
  fio.close();
}

// Test close() on an already closed file
TEST_F(FileIoTest_562, CloseAlreadyClosed_562) {
  TempFile tmp("fileio_test_doubleclose_562.tmp", "x");
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  int rc1 = fio.close();
  EXPECT_EQ(rc1, 0);
  
  // Closing again should not crash and should return 0
  int rc2 = fio.close();
  EXPECT_EQ(rc2, 0);
}

// Test size() on empty file
TEST_F(FileIoTest_562, SizeOfEmptyFile_562) {
  TempFile tmp("fileio_test_emptysize_562.tmp", "");
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  EXPECT_EQ(fio.size(), 0u);
  fio.close();
}

// Test reading zero bytes
TEST_F(FileIoTest_562, ReadZeroBytes_562) {
  std::string content = "data";
  TempFile tmp("fileio_test_readzero_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  Exiv2::DataBuf buf = fio.read(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_EQ(fio.tell(), 0u);
  fio.close();
}

// Test writing zero bytes
TEST_F(FileIoTest_562, WriteZeroBytes_562) {
  std::string filename = "fileio_test_writezero_562.tmp";
  Exiv2::FileIo fio(filename);
  fio.open("wb");
  Exiv2::byte dummy = 0;
  size_t written = fio.write(&dummy, 0);
  EXPECT_EQ(written, 0u);
  fio.close();
  std::remove(filename.c_str());
}

// Test setPath changes the path
TEST_F(FileIoTest_562, SetPathChangesPath_562) {
  Exiv2::FileIo fio("original_path_562.tmp");
  EXPECT_EQ(fio.path(), "original_path_562.tmp");
  
  fio.setPath("new_path_562.tmp");
  EXPECT_EQ(fio.path(), "new_path_562.tmp");
}

// Test mmap and munmap
TEST_F(FileIoTest_562, MmapAndMunmap_562) {
  std::string content = "MmapTest562";
  TempFile tmp("fileio_test_mmap_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  Exiv2::byte* mapped = fio.mmap(false);
  ASSERT_NE(mapped, nullptr);
  EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);
  
  int rc = fio.munmap();
  EXPECT_EQ(rc, 0);
  fio.close();
}

// Test close after mmap (close should call munmap internally)
TEST_F(FileIoTest_562, CloseAfterMmap_562) {
  std::string content = "CloseAfterMmap562";
  TempFile tmp("fileio_test_closemmap_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  fio.mmap(false);
  
  // close() should handle munmap internally
  int rc = fio.close();
  EXPECT_EQ(rc, 0);
  EXPECT_FALSE(fio.isopen());
}

// Test transfer from one FileIo to another
TEST_F(FileIoTest_562, TransferFromAnotherFileIo_562) {
  std::string srcContent = "TransferSource562";
  TempFile srcTmp("fileio_test_transfer_src_562.tmp", srcContent);
  std::string dstFilename = "fileio_test_transfer_dst_562.tmp";
  
  {
    // Create destination file
    std::ofstream ofs(dstFilename);
    ofs << "old content";
    ofs.close();
  }
  
  Exiv2::FileIo dst(dstFilename);
  Exiv2::FileIo src(srcTmp.path());
  
  src.open();
  dst.transfer(src);
  
  // After transfer, destination should have source content
  dst.open();
  Exiv2::DataBuf buf = dst.read(srcContent.size());
  EXPECT_EQ(buf.size(), srcContent.size());
  EXPECT_EQ(std::memcmp(buf.data(), srcContent.data(), srcContent.size()), 0);
  dst.close();
  
  std::remove(dstFilename.c_str());
}

// Test write from BasicIo source
TEST_F(FileIoTest_562, WriteFromBasicIoSource_562) {
  std::string srcContent = "SourceContent562";
  TempFile srcTmp("fileio_test_writesrc_562.tmp", srcContent);
  std::string dstFilename = "fileio_test_writedst_562.tmp";
  
  Exiv2::FileIo src(srcTmp.path());
  src.open();
  
  Exiv2::FileIo dst(dstFilename);
  dst.open("wb");
  size_t written = dst.write(src);
  EXPECT_EQ(written, srcContent.size());
  dst.close();
  src.close();
  
  // Verify written content
  Exiv2::FileIo verify(dstFilename);
  verify.open();
  Exiv2::DataBuf buf = verify.read(srcContent.size());
  EXPECT_EQ(buf.size(), srcContent.size());
  EXPECT_EQ(std::memcmp(buf.data(), srcContent.data(), srcContent.size()), 0);
  verify.close();
  
  std::remove(dstFilename.c_str());
}

// Test seek to position 0 after reading
TEST_F(FileIoTest_562, SeekToBeginningAfterRead_562) {
  std::string content = "RewindTest562";
  TempFile tmp("fileio_test_rewind_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  fio.read(5);
  EXPECT_EQ(fio.tell(), 5u);
  
  fio.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(fio.tell(), 0u);
  
  int ch = fio.getb();
  EXPECT_EQ(ch, 'R');
  fio.close();
}

// Test large write and read back
TEST_F(FileIoTest_562, LargeWriteAndRead_562) {
  std::string filename = "fileio_test_large_562.tmp";
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
    fio.open();
    EXPECT_EQ(fio.size(), dataSize);
    std::vector<Exiv2::byte> readBuf(dataSize);
    size_t bytesRead = fio.read(readBuf.data(), dataSize);
    EXPECT_EQ(bytesRead, dataSize);
    EXPECT_EQ(data, readBuf);
    fio.close();
  }
  
  std::remove(filename.c_str());
}

// Test multiple sequential reads
TEST_F(FileIoTest_562, MultipleSequentialReads_562) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("fileio_test_multread_562.tmp", content);
  Exiv2::FileIo fio(tmp.path());
  
  fio.open();
  
  Exiv2::DataBuf buf1 = fio.read(3);
  EXPECT_EQ(buf1.size(), 3u);
  EXPECT_EQ(std::memcmp(buf1.data(), "ABC", 3), 0);
  
  Exiv2::DataBuf buf2 = fio.read(3);
  EXPECT_EQ(buf2.size(), 3u);
  EXPECT_EQ(std::memcmp(buf2.data(), "DEF", 3), 0);
  
  Exiv2::DataBuf buf3 = fio.read(4);
  EXPECT_EQ(buf3.size(), 4u);
  EXPECT_EQ(std::memcmp(buf3.data(), "GHIJ", 4), 0);
  
  fio.close();
}

// Test isopen after destruction scenario (via scope)
TEST_F(FileIoTest_562, FileIoDestructorClosesFile_562) {
  std::string filename = "fileio_test_dtor_562.tmp";
  {
    std::ofstream ofs(filename);
    ofs << "dtor test";
  }
  
  {
    Exiv2::FileIo fio(filename);
    fio.open();
    EXPECT_TRUE(fio.isopen());
    // Destructor should handle cleanup
  }
  
  std::remove(filename.c_str());
}
