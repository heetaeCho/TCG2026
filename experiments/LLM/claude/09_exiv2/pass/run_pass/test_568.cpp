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

class FileIoTest_568 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that path() returns the path used in construction
TEST_F(FileIoTest_568, PathReturnsConstructedPath_568) {
  std::string testPath = "test_file_path_568.tmp";
  Exiv2::FileIo io(testPath);
  EXPECT_EQ(io.path(), testPath);
}

// Test that path() returns empty string when constructed with empty path
TEST_F(FileIoTest_568, PathReturnsEmptyWhenConstructedWithEmpty_568) {
  Exiv2::FileIo io("");
  EXPECT_EQ(io.path(), "");
}

// Test that path() returns path with special characters
TEST_F(FileIoTest_568, PathWithSpecialCharacters_568) {
  std::string specialPath = "/tmp/test file (1) [copy].jpg";
  Exiv2::FileIo io(specialPath);
  EXPECT_EQ(io.path(), specialPath);
}

// Test open on a file that exists
TEST_F(FileIoTest_568, OpenExistingFile_568) {
  TempFile tmp("fileio_test_open_568.tmp", "hello");
  Exiv2::FileIo io(tmp.path());
  int result = io.open();
  EXPECT_EQ(result, 0);
  io.close();
}

// Test open on a file that does not exist
TEST_F(FileIoTest_568, OpenNonExistingFile_568) {
  Exiv2::FileIo io("non_existing_file_568.tmp");
  int result = io.open();
  EXPECT_NE(result, 0);
}

// Test open with mode string
TEST_F(FileIoTest_568, OpenWithModeRead_568) {
  TempFile tmp("fileio_test_openmode_568.tmp", "test content");
  Exiv2::FileIo io(tmp.path());
  int result = io.open("rb");
  EXPECT_EQ(result, 0);
  io.close();
}

// Test open with write mode creates file
TEST_F(FileIoTest_568, OpenWithModeWrite_568) {
  std::string path = "fileio_test_write_mode_568.tmp";
  {
    Exiv2::FileIo io(path);
    int result = io.open("wb");
    EXPECT_EQ(result, 0);
    io.close();
  }
  // Cleanup
  std::remove(path.c_str());
}

// Test isopen returns false before open
TEST_F(FileIoTest_568, IsOpenReturnsFalseBeforeOpen_568) {
  Exiv2::FileIo io("some_file_568.tmp");
  EXPECT_FALSE(io.isopen());
}

// Test isopen returns true after open
TEST_F(FileIoTest_568, IsOpenReturnsTrueAfterOpen_568) {
  TempFile tmp("fileio_test_isopen_568.tmp", "data");
  Exiv2::FileIo io(tmp.path());
  io.open();
  EXPECT_TRUE(io.isopen());
  io.close();
}

// Test isopen returns false after close
TEST_F(FileIoTest_568, IsOpenReturnsFalseAfterClose_568) {
  TempFile tmp("fileio_test_close_568.tmp", "data");
  Exiv2::FileIo io(tmp.path());
  io.open();
  io.close();
  EXPECT_FALSE(io.isopen());
}

// Test close on unopened file
TEST_F(FileIoTest_568, CloseOnUnopenedFile_568) {
  Exiv2::FileIo io("some_path_568.tmp");
  int result = io.close();
  EXPECT_EQ(result, 0);
}

// Test size of a file
TEST_F(FileIoTest_568, SizeReturnsCorrectFileSize_568) {
  std::string content = "Hello, World!";
  TempFile tmp("fileio_test_size_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  EXPECT_EQ(io.size(), content.size());
  io.close();
}

// Test size of empty file
TEST_F(FileIoTest_568, SizeReturnsZeroForEmptyFile_568) {
  TempFile tmp("fileio_test_empty_size_568.tmp", "");
  Exiv2::FileIo io(tmp.path());
  io.open();
  EXPECT_EQ(io.size(), 0u);
  io.close();
}

// Test tell returns 0 at beginning
TEST_F(FileIoTest_568, TellReturnsZeroAtBeginning_568) {
  TempFile tmp("fileio_test_tell_568.tmp", "some data here");
  Exiv2::FileIo io(tmp.path());
  io.open();
  EXPECT_EQ(io.tell(), 0u);
  io.close();
}

// Test write and read roundtrip
TEST_F(FileIoTest_568, WriteAndReadRoundtrip_568) {
  std::string path = "fileio_test_roundtrip_568.tmp";
  const std::string data = "Test data for roundtrip";

  {
    Exiv2::FileIo io(path);
    io.open("wb");
    size_t written = io.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(written, data.size());
    io.close();
  }

  {
    Exiv2::FileIo io(path);
    io.open("rb");
    Exiv2::DataBuf buf = io.read(data.size());
    EXPECT_EQ(buf.size(), data.size());
    std::string readBack(reinterpret_cast<const char*>(buf.c_data()), buf.size());
    EXPECT_EQ(readBack, data);
    io.close();
  }

  std::remove(path.c_str());
}

// Test read into buffer
TEST_F(FileIoTest_568, ReadIntoBuffer_568) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("fileio_test_readbuf_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  std::vector<Exiv2::byte> buf(content.size());
  size_t bytesRead = io.read(buf.data(), buf.size());
  EXPECT_EQ(bytesRead, content.size());
  std::string result(buf.begin(), buf.end());
  EXPECT_EQ(result, content);
  io.close();
}

// Test read more than available
TEST_F(FileIoTest_568, ReadMoreThanAvailable_568) {
  std::string content = "short";
  TempFile tmp("fileio_test_readmore_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  std::vector<Exiv2::byte> buf(100);
  size_t bytesRead = io.read(buf.data(), 100);
  EXPECT_EQ(bytesRead, content.size());
  io.close();
}

// Test getb reads one byte at a time
TEST_F(FileIoTest_568, GetbReadsSingleByte_568) {
  std::string content = "AB";
  TempFile tmp("fileio_test_getb_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  int b1 = io.getb();
  EXPECT_EQ(b1, 'A');
  int b2 = io.getb();
  EXPECT_EQ(b2, 'B');
  io.close();
}

// Test getb returns EOF at end
TEST_F(FileIoTest_568, GetbReturnsEofAtEnd_568) {
  TempFile tmp("fileio_test_getb_eof_568.tmp", "X");
  Exiv2::FileIo io(tmp.path());
  io.open();
  io.getb();  // read 'X'
  int result = io.getb();
  EXPECT_EQ(result, EOF);
  io.close();
}

// Test putb writes a single byte
TEST_F(FileIoTest_568, PutbWritesSingleByte_568) {
  std::string path = "fileio_test_putb_568.tmp";
  {
    Exiv2::FileIo io(path);
    io.open("wb");
    int result = io.putb(0x42);
    EXPECT_EQ(result, 0x42);
    io.close();
  }

  {
    Exiv2::FileIo io(path);
    io.open("rb");
    int b = io.getb();
    EXPECT_EQ(b, 0x42);
    io.close();
  }

  std::remove(path.c_str());
}

// Test seek from beginning
TEST_F(FileIoTest_568, SeekFromBeginning_568) {
  std::string content = "0123456789";
  TempFile tmp("fileio_test_seek_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  int result = io.seek(5, Exiv2::BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(io.tell(), 5u);
  int b = io.getb();
  EXPECT_EQ(b, '5');
  io.close();
}

// Test seek from current position
TEST_F(FileIoTest_568, SeekFromCurrent_568) {
  std::string content = "0123456789";
  TempFile tmp("fileio_test_seekcur_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  io.seek(3, Exiv2::BasicIo::beg);
  io.seek(2, Exiv2::BasicIo::cur);
  EXPECT_EQ(io.tell(), 5u);
  io.close();
}

// Test seek from end
TEST_F(FileIoTest_568, SeekFromEnd_568) {
  std::string content = "0123456789";
  TempFile tmp("fileio_test_seekend_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  io.seek(-3, Exiv2::BasicIo::end);
  EXPECT_EQ(io.tell(), 7u);
  int b = io.getb();
  EXPECT_EQ(b, '7');
  io.close();
}

// Test eof returns false when not at end
TEST_F(FileIoTest_568, EofReturnsFalseWhenNotAtEnd_568) {
  std::string content = "data";
  TempFile tmp("fileio_test_eof_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  EXPECT_FALSE(io.eof());
  io.close();
}

// Test eof returns true after reading past end
TEST_F(FileIoTest_568, EofReturnsTrueAtEnd_568) {
  std::string content = "X";
  TempFile tmp("fileio_test_eof2_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  io.getb();  // read 'X'
  io.getb();  // attempt to read past end
  EXPECT_TRUE(io.eof());
  io.close();
}

// Test error returns 0 on normal operation
TEST_F(FileIoTest_568, ErrorReturnsZeroOnNormalOp_568) {
  TempFile tmp("fileio_test_error_568.tmp", "data");
  Exiv2::FileIo io(tmp.path());
  io.open();
  EXPECT_EQ(io.error(), 0);
  io.close();
}

// Test setPath changes the path
TEST_F(FileIoTest_568, SetPathChangesPath_568) {
  Exiv2::FileIo io("original_path_568.tmp");
  EXPECT_EQ(io.path(), "original_path_568.tmp");
  io.setPath("new_path_568.tmp");
  EXPECT_EQ(io.path(), "new_path_568.tmp");
}

// Test writing with write(BasicIo&)
TEST_F(FileIoTest_568, WriteFromAnotherIo_568) {
  std::string srcContent = "source content for copy";
  TempFile srcTmp("fileio_test_src_568.tmp", srcContent);
  std::string dstPath = "fileio_test_dst_568.tmp";

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
    Exiv2::DataBuf buf = dstIo.read(srcContent.size());
    std::string readBack(reinterpret_cast<const char*>(buf.c_data()), buf.size());
    EXPECT_EQ(readBack, srcContent);
    dstIo.close();
  }

  std::remove(dstPath.c_str());
}

// Test mmap and munmap
TEST_F(FileIoTest_568, MmapAndMunmap_568) {
  std::string content = "mmap test data";
  TempFile tmp("fileio_test_mmap_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();

  Exiv2::byte* mapped = io.mmap(false);
  ASSERT_NE(mapped, nullptr);
  std::string mappedStr(reinterpret_cast<const char*>(mapped), content.size());
  EXPECT_EQ(mappedStr, content);

  int unmapResult = io.munmap();
  EXPECT_EQ(unmapResult, 0);
  io.close();
}

// Test transfer from one FileIo to another
TEST_F(FileIoTest_568, TransferFromAnotherFileIo_568) {
  std::string srcContent = "transfer test content";
  TempFile srcTmp("fileio_test_transfer_src_568.tmp", srcContent);
  std::string dstPath = "fileio_test_transfer_dst_568.tmp";

  {
    // Create destination file
    std::ofstream ofs(dstPath);
    ofs.close();
  }

  {
    Exiv2::FileIo srcIo(srcTmp.path());
    Exiv2::FileIo dstIo(dstPath);
    dstIo.transfer(srcIo);

    dstIo.open("rb");
    Exiv2::DataBuf buf = dstIo.read(srcContent.size());
    std::string readBack(reinterpret_cast<const char*>(buf.c_data()), buf.size());
    EXPECT_EQ(readBack, srcContent);
    dstIo.close();
  }

  std::remove(dstPath.c_str());
}

// Test reading zero bytes
TEST_F(FileIoTest_568, ReadZeroBytes_568) {
  TempFile tmp("fileio_test_readzero_568.tmp", "some data");
  Exiv2::FileIo io(tmp.path());
  io.open();
  Exiv2::DataBuf buf = io.read(0);
  EXPECT_EQ(buf.size(), 0u);
  io.close();
}

// Test writing zero bytes
TEST_F(FileIoTest_568, WriteZeroBytes_568) {
  std::string path = "fileio_test_writezero_568.tmp";
  Exiv2::FileIo io(path);
  io.open("wb");
  Exiv2::byte dummy = 0;
  size_t written = io.write(&dummy, 0);
  EXPECT_EQ(written, 0u);
  io.close();
  std::remove(path.c_str());
}

// Test path with long filename
TEST_F(FileIoTest_568, LongPath_568) {
  std::string longPath(200, 'a');
  longPath += ".tmp";
  Exiv2::FileIo io(longPath);
  EXPECT_EQ(io.path(), longPath);
}

// Test multiple open/close cycles
TEST_F(FileIoTest_568, MultipleOpenCloseCycles_568) {
  TempFile tmp("fileio_test_multi_568.tmp", "cycle data");
  Exiv2::FileIo io(tmp.path());

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(io.open(), 0);
    EXPECT_TRUE(io.isopen());
    EXPECT_EQ(io.close(), 0);
    EXPECT_FALSE(io.isopen());
  }
}

// Test tell after write
TEST_F(FileIoTest_568, TellAfterWrite_568) {
  std::string path = "fileio_test_tellwrite_568.tmp";
  Exiv2::FileIo io(path);
  io.open("wb");
  std::string data = "12345";
  io.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  EXPECT_EQ(io.tell(), data.size());
  io.close();
  std::remove(path.c_str());
}

// Test seek to position 0
TEST_F(FileIoTest_568, SeekToZero_568) {
  std::string content = "0123456789";
  TempFile tmp("fileio_test_seekzero_568.tmp", content);
  Exiv2::FileIo io(tmp.path());
  io.open();
  io.seek(5, Exiv2::BasicIo::beg);
  io.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(io.tell(), 0u);
  io.close();
}
