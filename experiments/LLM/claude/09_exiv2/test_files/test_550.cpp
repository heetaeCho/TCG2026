#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

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

class FileIoTest_550 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that constructing a FileIo with a path stores the correct path
TEST_F(FileIoTest_550, ConstructorSetsPath_550) {
  Exiv2::FileIo io("test_path.dat");
  EXPECT_EQ(io.path(), "test_path.dat");
}

// Test that a newly constructed FileIo is not open
TEST_F(FileIoTest_550, InitiallyNotOpen_550) {
  Exiv2::FileIo io("nonexistent_file.dat");
  EXPECT_FALSE(io.isopen());
}

// Test open on a valid file
TEST_F(FileIoTest_550, OpenExistingFile_550) {
  TempFile tmp("fileio_test_open_550.dat", "hello");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_TRUE(io.isopen());
  io.close();
}

// Test open on a non-existent file returns error
TEST_F(FileIoTest_550, OpenNonExistentFile_550) {
  Exiv2::FileIo io("this_file_does_not_exist_550.dat");
  EXPECT_NE(io.open(), 0);
  EXPECT_FALSE(io.isopen());
}

// Test open with mode
TEST_F(FileIoTest_550, OpenWithMode_550) {
  TempFile tmp("fileio_test_mode_550.dat", "data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("r"), 0);
  EXPECT_TRUE(io.isopen());
  io.close();
}

// Test close on an opened file
TEST_F(FileIoTest_550, CloseFile_550) {
  TempFile tmp("fileio_test_close_550.dat", "data");
  Exiv2::FileIo io(tmp.path());
  io.open();
  EXPECT_EQ(io.close(), 0);
  EXPECT_FALSE(io.isopen());
}

// Test close on a file that is not open
TEST_F(FileIoTest_550, CloseNotOpenFile_550) {
  Exiv2::FileIo io("nonexistent_550.dat");
  // Closing a file that was never opened should not crash
  int result = io.close();
  // Result may be 0 or non-zero depending on implementation
  (void)result;
  EXPECT_FALSE(io.isopen());
}

// Test size on a known file
TEST_F(FileIoTest_550, SizeReturnsCorrectValue_550) {
  std::string content = "Hello, World!";
  TempFile tmp("fileio_test_size_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.size(), content.size());
  io.close();
}

// Test size on an empty file
TEST_F(FileIoTest_550, SizeOfEmptyFile_550) {
  TempFile tmp("fileio_test_empty_550.dat", "");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.size(), 0u);
  io.close();
}

// Test read with a buffer
TEST_F(FileIoTest_550, ReadIntoBuffer_550) {
  std::string content = "ABCDEF";
  TempFile tmp("fileio_test_read_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  Exiv2::byte buf[10] = {};
  size_t bytesRead = io.read(buf, 6);
  EXPECT_EQ(bytesRead, 6u);
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 6), "ABCDEF");
  io.close();
}

// Test read returning DataBuf
TEST_F(FileIoTest_550, ReadReturnsDataBuf_550) {
  std::string content = "TestData";
  TempFile tmp("fileio_test_readbuf_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  Exiv2::DataBuf dbuf = io.read(8);
  EXPECT_EQ(dbuf.size(), 8u);
  EXPECT_EQ(std::memcmp(dbuf.c_data(), content.data(), 8), 0);
  io.close();
}

// Test reading more bytes than available
TEST_F(FileIoTest_550, ReadMoreThanAvailable_550) {
  std::string content = "Short";
  TempFile tmp("fileio_test_readmore_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  Exiv2::byte buf[100] = {};
  size_t bytesRead = io.read(buf, 100);
  EXPECT_EQ(bytesRead, content.size());
  io.close();
}

// Test write data to a file
TEST_F(FileIoTest_550, WriteData_550) {
  TempFile tmp("fileio_test_write_550.dat", "");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);
  const std::string data = "Written data";
  size_t written = io.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  EXPECT_EQ(written, data.size());
  io.close();

  // Verify by reading back
  Exiv2::FileIo io2(tmp.path());
  EXPECT_EQ(io2.open(), 0);
  EXPECT_EQ(io2.size(), data.size());
  Exiv2::byte buf[50] = {};
  io2.read(buf, data.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), data.size()), data);
  io2.close();
}

// Test putb and getb
TEST_F(FileIoTest_550, PutbAndGetb_550) {
  TempFile tmp("fileio_test_putb_550.dat", "");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);
  EXPECT_EQ(io.putb(0x42), 0);
  io.close();

  Exiv2::FileIo io2(tmp.path());
  EXPECT_EQ(io2.open(), 0);
  int val = io2.getb();
  EXPECT_EQ(val, 0x42);
  io2.close();
}

// Test seek and tell
TEST_F(FileIoTest_550, SeekAndTell_550) {
  std::string content = "0123456789";
  TempFile tmp("fileio_test_seek_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.tell(), 0u);
  EXPECT_EQ(io.seek(5, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(io.tell(), 5u);
  Exiv2::byte buf[1] = {};
  io.read(buf, 1);
  EXPECT_EQ(buf[0], '5');
  io.close();
}

// Test seek from current position
TEST_F(FileIoTest_550, SeekFromCurrent_550) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("fileio_test_seekcur_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  io.seek(2, Exiv2::BasicIo::beg);
  io.seek(3, Exiv2::BasicIo::cur);
  EXPECT_EQ(io.tell(), 5u);
  Exiv2::byte buf[1] = {};
  io.read(buf, 1);
  EXPECT_EQ(buf[0], 'F');
  io.close();
}

// Test seek from end
TEST_F(FileIoTest_550, SeekFromEnd_550) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("fileio_test_seekend_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  io.seek(-3, Exiv2::BasicIo::end);
  EXPECT_EQ(io.tell(), 7u);
  Exiv2::byte buf[1] = {};
  io.read(buf, 1);
  EXPECT_EQ(buf[0], 'H');
  io.close();
}

// Test eof detection
TEST_F(FileIoTest_550, EofDetection_550) {
  std::string content = "AB";
  TempFile tmp("fileio_test_eof_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  Exiv2::byte buf[10] = {};
  io.read(buf, 10);  // Read more than available to trigger EOF
  EXPECT_TRUE(io.eof());
  io.close();
}

// Test error after successful operations
TEST_F(FileIoTest_550, NoErrorAfterNormalOps_550) {
  std::string content = "Hello";
  TempFile tmp("fileio_test_error_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.error(), 0);
  Exiv2::byte buf[5] = {};
  io.read(buf, 5);
  EXPECT_EQ(io.error(), 0);
  io.close();
}

// Test setPath changes the path
TEST_F(FileIoTest_550, SetPathChangesPath_550) {
  Exiv2::FileIo io("original_path_550.dat");
  EXPECT_EQ(io.path(), "original_path_550.dat");
  io.setPath("new_path_550.dat");
  EXPECT_EQ(io.path(), "new_path_550.dat");
}

// Test mmap on a valid readable file
TEST_F(FileIoTest_550, MmapReadOnly_550) {
  std::string content = "MmapTestData";
  TempFile tmp("fileio_test_mmap_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  Exiv2::byte* mapped = io.mmap(false);
  ASSERT_NE(mapped, nullptr);
  EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);
  EXPECT_EQ(io.munmap(), 0);
  io.close();
}

// Test mmap writable
TEST_F(FileIoTest_550, MmapWritable_550) {
  std::string content = "WritableMmap";
  TempFile tmp("fileio_test_mmapw_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("r+b"), 0);
  Exiv2::byte* mapped = io.mmap(true);
  ASSERT_NE(mapped, nullptr);
  EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);
  // Modify through mmap
  mapped[0] = 'X';
  EXPECT_EQ(io.munmap(), 0);
  io.close();

  // Verify modification persisted
  Exiv2::FileIo io2(tmp.path());
  EXPECT_EQ(io2.open(), 0);
  Exiv2::byte buf[1] = {};
  io2.read(buf, 1);
  EXPECT_EQ(buf[0], 'X');
  io2.close();
}

// Test munmap without prior mmap should not fail
TEST_F(FileIoTest_550, MunmapWithoutMmap_550) {
  TempFile tmp("fileio_test_munmap_550.dat", "data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.munmap(), 0);
  io.close();
}

// Test multiple mmap/munmap cycles
TEST_F(FileIoTest_550, MultipleMmapCycles_550) {
  std::string content = "CycleData";
  TempFile tmp("fileio_test_mmapcy_550.dat", content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  for (int i = 0; i < 3; ++i) {
    Exiv2::byte* mapped = io.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);
    EXPECT_EQ(io.munmap(), 0);
  }

  io.close();
}

// Test write from one FileIo to another (write(BasicIo&))
TEST_F(FileIoTest_550, WriteFromBasicIo_550) {
  std::string content = "SourceContent";
  TempFile srcFile("fileio_test_wsrc_550.dat", content);
  TempFile dstFile("fileio_test_wdst_550.dat", "");

  Exiv2::FileIo src(srcFile.path());
  EXPECT_EQ(src.open(), 0);

  Exiv2::FileIo dst(dstFile.path());
  EXPECT_EQ(dst.open("w+b"), 0);

  size_t written = dst.write(src);
  EXPECT_EQ(written, content.size());

  dst.close();
  src.close();

  // Verify
  Exiv2::FileIo verify(dstFile.path());
  EXPECT_EQ(verify.open(), 0);
  EXPECT_EQ(verify.size(), content.size());
  Exiv2::byte buf[50] = {};
  verify.read(buf, content.size());
  EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), content.size()), content);
  verify.close();
}

// Test reading single byte with getb at EOF returns EOF
TEST_F(FileIoTest_550, GetbAtEofReturnsEof_550) {
  TempFile tmp("fileio_test_getbeof_550.dat", "A");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  int val = io.getb();
  EXPECT_EQ(val, 'A');
  val = io.getb();
  EXPECT_EQ(val, EOF);
  io.close();
}

// Test tell after writing
TEST_F(FileIoTest_550, TellAfterWrite_550) {
  TempFile tmp("fileio_test_tellw_550.dat", "");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);
  const std::string data = "12345";
  io.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  EXPECT_EQ(io.tell(), 5u);
  io.close();
}

// Test that path is accessible even when file is not open
TEST_F(FileIoTest_550, PathAccessibleWhenClosed_550) {
  Exiv2::FileIo io("some_path_550.dat");
  EXPECT_EQ(io.path(), "some_path_550.dat");
}

// Test reading zero bytes
TEST_F(FileIoTest_550, ReadZeroBytes_550) {
  TempFile tmp("fileio_test_readzero_550.dat", "content");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  Exiv2::byte buf[1] = {0xFF};
  size_t bytesRead = io.read(buf, 0);
  EXPECT_EQ(bytesRead, 0u);
  // Buffer should be untouched
  EXPECT_EQ(buf[0], 0xFF);
  io.close();
}

// Test writing zero bytes
TEST_F(FileIoTest_550, WriteZeroBytes_550) {
  TempFile tmp("fileio_test_writezero_550.dat", "");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);
  Exiv2::byte data = 0;
  size_t written = io.write(&data, 0);
  EXPECT_EQ(written, 0u);
  EXPECT_EQ(io.size(), 0u);
  io.close();
}

// Test transfer method
TEST_F(FileIoTest_550, TransferFromFileIo_550) {
  std::string content = "TransferMe";
  TempFile srcFile("fileio_test_tsrc_550.dat", content);
  TempFile dstFile("fileio_test_tdst_550.dat", "");

  Exiv2::FileIo src(srcFile.path());
  EXPECT_EQ(src.open(), 0);

  Exiv2::FileIo dst(dstFile.path());
  EXPECT_NO_THROW(dst.transfer(src));

  // Verify destination has the content
  Exiv2::FileIo verify(dst.path());
  EXPECT_EQ(verify.open(), 0);
  EXPECT_EQ(verify.size(), content.size());
  verify.close();
}
