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
      : path_(std::filesystem::temp_directory_path() / filename) {
    std::ofstream ofs(path_.string(), std::ios::binary);
    if (!content.empty()) {
      ofs.write(content.data(), content.size());
    }
    ofs.close();
  }

  ~TempFile() {
    std::filesystem::remove(path_);
  }

  std::string path() const { return path_.string(); }

 private:
  std::filesystem::path path_;
};

class FileIoTest_567 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Path Tests ====================

TEST_F(FileIoTest_567, ConstructorSetsPath_567) {
  TempFile tmp("test_path_567.dat", "hello");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(fio.path(), tmp.path());
}

TEST_F(FileIoTest_567, SetPathChangesPath_567) {
  TempFile tmp1("test_setpath1_567.dat", "data1");
  TempFile tmp2("test_setpath2_567.dat", "data2");
  Exiv2::FileIo fio(tmp1.path());
  fio.setPath(tmp2.path());
  EXPECT_EQ(fio.path(), tmp2.path());
}

// ==================== Open / Close / IsOpen Tests ====================

TEST_F(FileIoTest_567, IsOpenReturnsFalseInitially_567) {
  TempFile tmp("test_isopen_567.dat", "hello");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_FALSE(fio.isopen());
}

TEST_F(FileIoTest_567, OpenReturnsZeroOnSuccess_567) {
  TempFile tmp("test_open_567.dat", "hello");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(0, fio.open());
  EXPECT_TRUE(fio.isopen());
  fio.close();
}

TEST_F(FileIoTest_567, OpenWithModeReturnsZeroOnSuccess_567) {
  TempFile tmp("test_openmode_567.dat", "hello");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(0, fio.open("rb"));
  EXPECT_TRUE(fio.isopen());
  fio.close();
}

TEST_F(FileIoTest_567, CloseReturnsZeroOnSuccess_567) {
  TempFile tmp("test_close_567.dat", "hello");
  Exiv2::FileIo fio(tmp.path());
  fio.open();
  EXPECT_EQ(0, fio.close());
  EXPECT_FALSE(fio.isopen());
}

TEST_F(FileIoTest_567, OpenNonExistentFileReturnsNonZero_567) {
  Exiv2::FileIo fio("/nonexistent/path/to/file_567.dat");
  // open() for reading a non-existent file should fail
  int result = fio.open();
  EXPECT_NE(0, result);
}

// ==================== Size Tests ====================

TEST_F(FileIoTest_567, SizeReturnsCorrectValue_567) {
  std::string content = "Hello, World!";
  TempFile tmp("test_size_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();
  EXPECT_EQ(content.size(), fio.size());
  fio.close();
}

TEST_F(FileIoTest_567, SizeOfEmptyFile_567) {
  TempFile tmp("test_emptysize_567.dat", "");
  Exiv2::FileIo fio(tmp.path());
  fio.open();
  EXPECT_EQ(0u, fio.size());
  fio.close();
}

// ==================== Read Tests ====================

TEST_F(FileIoTest_567, ReadIntoBuffer_567) {
  std::string content = "ABCDEFGH";
  TempFile tmp("test_read_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  Exiv2::byte buf[8];
  size_t bytesRead = fio.read(buf, 8);
  EXPECT_EQ(8u, bytesRead);
  EXPECT_EQ(0, std::memcmp(buf, content.data(), 8));
  fio.close();
}

TEST_F(FileIoTest_567, ReadDataBuf_567) {
  std::string content = "TestData";
  TempFile tmp("test_readbuf_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  Exiv2::DataBuf dbuf = fio.read(8);
  EXPECT_EQ(8u, dbuf.size());
  EXPECT_EQ(0, std::memcmp(dbuf.data(), content.data(), 8));
  fio.close();
}

TEST_F(FileIoTest_567, ReadMoreThanAvailable_567) {
  std::string content = "Short";
  TempFile tmp("test_readmore_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  Exiv2::byte buf[100];
  size_t bytesRead = fio.read(buf, 100);
  EXPECT_EQ(content.size(), bytesRead);
  fio.close();
}

// ==================== Getb Tests ====================

TEST_F(FileIoTest_567, GetbReturnsByteValue_567) {
  std::string content = "A";
  TempFile tmp("test_getb_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  int val = fio.getb();
  EXPECT_EQ('A', val);
  fio.close();
}

TEST_F(FileIoTest_567, GetbAtEofReturnsEof_567) {
  TempFile tmp("test_getbeof_567.dat", "");
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  int val = fio.getb();
  EXPECT_EQ(EOF, val);
  fio.close();
}

// ==================== Write Tests ====================

TEST_F(FileIoTest_567, WriteDataAndReadBack_567) {
  std::string tmpPath = (std::filesystem::temp_directory_path() / "test_write_567.dat").string();
  {
    Exiv2::FileIo fio(tmpPath);
    fio.open("wb");
    std::string data = "WrittenData";
    size_t written = fio.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(data.size(), written);
    fio.close();
  }
  {
    Exiv2::FileIo fio(tmpPath);
    fio.open("rb");
    Exiv2::byte buf[20];
    size_t bytesRead = fio.read(buf, 20);
    EXPECT_EQ(11u, bytesRead);
    EXPECT_EQ(0, std::memcmp(buf, "WrittenData", 11));
    fio.close();
  }
  std::filesystem::remove(tmpPath);
}

// ==================== Putb Tests ====================

TEST_F(FileIoTest_567, PutbWritesSingleByte_567) {
  std::string tmpPath = (std::filesystem::temp_directory_path() / "test_putb_567.dat").string();
  {
    Exiv2::FileIo fio(tmpPath);
    fio.open("wb");
    int result = fio.putb(0x42);
    EXPECT_EQ(0x42, result);
    fio.close();
  }
  {
    Exiv2::FileIo fio(tmpPath);
    fio.open("rb");
    int val = fio.getb();
    EXPECT_EQ(0x42, val);
    fio.close();
  }
  std::filesystem::remove(tmpPath);
}

// ==================== Seek / Tell Tests ====================

TEST_F(FileIoTest_567, SeekAndTell_567) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  EXPECT_EQ(0u, fio.tell());

  fio.seek(5, Exiv2::BasicIo::beg);
  EXPECT_EQ(5u, fio.tell());

  int val = fio.getb();
  EXPECT_EQ('5', val);
  EXPECT_EQ(6u, fio.tell());

  fio.close();
}

TEST_F(FileIoTest_567, SeekFromEnd_567) {
  std::string content = "0123456789";
  TempFile tmp("test_seekend_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  fio.seek(-1, Exiv2::BasicIo::end);
  int val = fio.getb();
  EXPECT_EQ('9', val);

  fio.close();
}

TEST_F(FileIoTest_567, SeekFromCurrent_567) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("test_seekcur_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  fio.seek(3, Exiv2::BasicIo::beg);
  fio.seek(2, Exiv2::BasicIo::cur);
  EXPECT_EQ(5u, fio.tell());

  int val = fio.getb();
  EXPECT_EQ('F', val);

  fio.close();
}

// ==================== EOF Tests ====================

TEST_F(FileIoTest_567, EofReturnsFalseBeforeEndOfFile_567) {
  std::string content = "Data";
  TempFile tmp("test_eof_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  EXPECT_FALSE(fio.eof());
  fio.close();
}

TEST_F(FileIoTest_567, EofReturnsTrueAfterReadingPastEnd_567) {
  std::string content = "X";
  TempFile tmp("test_eoftrue_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  fio.getb();  // read 'X'
  fio.getb();  // read past end
  EXPECT_TRUE(fio.eof());

  fio.close();
}

TEST_F(FileIoTest_567, EofOnEmptyFile_567) {
  TempFile tmp("test_eofempty_567.dat", "");
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  fio.getb();  // attempt read on empty file
  EXPECT_TRUE(fio.eof());

  fio.close();
}

// ==================== Error Tests ====================

TEST_F(FileIoTest_567, ErrorReturnsZeroOnNormalOperation_567) {
  std::string content = "Normal";
  TempFile tmp("test_error_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  EXPECT_EQ(0, fio.error());
  fio.close();
}

// ==================== Transfer Tests ====================

TEST_F(FileIoTest_567, TransferFromAnotherFileIo_567) {
  std::string content = "SourceContent";
  TempFile tmpSrc("test_transfer_src_567.dat", content);
  std::string dstPath = (std::filesystem::temp_directory_path() / "test_transfer_dst_567.dat").string();

  {
    Exiv2::FileIo src(tmpSrc.path());
    Exiv2::FileIo dst(dstPath);
    dst.transfer(src);
  }

  // Verify that the destination file has the content
  {
    Exiv2::FileIo dst(dstPath);
    dst.open("rb");
    Exiv2::byte buf[50];
    size_t bytesRead = dst.read(buf, 50);
    EXPECT_EQ(content.size(), bytesRead);
    EXPECT_EQ(0, std::memcmp(buf, content.data(), content.size()));
    dst.close();
  }
  std::filesystem::remove(dstPath);
}

// ==================== Write from BasicIo Tests ====================

TEST_F(FileIoTest_567, WriteFromBasicIo_567) {
  std::string content = "SourceData";
  TempFile tmpSrc("test_writesrc_567.dat", content);
  std::string dstPath = (std::filesystem::temp_directory_path() / "test_writedst_567.dat").string();

  {
    Exiv2::FileIo src(tmpSrc.path());
    src.open("rb");
    Exiv2::FileIo dst(dstPath);
    dst.open("wb");
    size_t written = dst.write(src);
    EXPECT_EQ(content.size(), written);
    dst.close();
    src.close();
  }

  {
    Exiv2::FileIo dst(dstPath);
    dst.open("rb");
    Exiv2::byte buf[50];
    size_t bytesRead = dst.read(buf, 50);
    EXPECT_EQ(content.size(), bytesRead);
    EXPECT_EQ(0, std::memcmp(buf, content.data(), content.size()));
    dst.close();
  }
  std::filesystem::remove(dstPath);
}

// ==================== Mmap / Munmap Tests ====================

TEST_F(FileIoTest_567, MmapAndMunmap_567) {
  std::string content = "MmapTest";
  TempFile tmp("test_mmap_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  Exiv2::byte* mapped = fio.mmap(false);
  ASSERT_NE(nullptr, mapped);
  EXPECT_EQ(0, std::memcmp(mapped, content.data(), content.size()));

  int result = fio.munmap();
  EXPECT_EQ(0, result);

  fio.close();
}

// ==================== Multiple Sequential Reads ====================

TEST_F(FileIoTest_567, SequentialReads_567) {
  std::string content = "ABCDEF";
  TempFile tmp("test_seqread_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  Exiv2::byte buf[2];
  size_t r1 = fio.read(buf, 2);
  EXPECT_EQ(2u, r1);
  EXPECT_EQ('A', buf[0]);
  EXPECT_EQ('B', buf[1]);

  size_t r2 = fio.read(buf, 2);
  EXPECT_EQ(2u, r2);
  EXPECT_EQ('C', buf[0]);
  EXPECT_EQ('D', buf[1]);

  size_t r3 = fio.read(buf, 2);
  EXPECT_EQ(2u, r3);
  EXPECT_EQ('E', buf[0]);
  EXPECT_EQ('F', buf[1]);

  fio.close();
}

// ==================== Seek to beginning resets position ====================

TEST_F(FileIoTest_567, SeekToBeginningResetsPosition_567) {
  std::string content = "ResetTest";
  TempFile tmp("test_seekbeg_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  fio.read(5);
  EXPECT_EQ(5u, fio.tell());

  fio.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(0u, fio.tell());

  int val = fio.getb();
  EXPECT_EQ('R', val);

  fio.close();
}

// ==================== Write zero bytes ====================

TEST_F(FileIoTest_567, WriteZeroBytes_567) {
  std::string tmpPath = (std::filesystem::temp_directory_path() / "test_writezero_567.dat").string();
  Exiv2::FileIo fio(tmpPath);
  fio.open("wb");
  size_t written = fio.write(reinterpret_cast<const Exiv2::byte*>(""), 0);
  EXPECT_EQ(0u, written);
  fio.close();
  std::filesystem::remove(tmpPath);
}

// ==================== Read zero bytes ====================

TEST_F(FileIoTest_567, ReadZeroBytes_567) {
  std::string content = "Something";
  TempFile tmp("test_readzero_567.dat", content);
  Exiv2::FileIo fio(tmp.path());
  fio.open();

  Exiv2::byte buf[1];
  size_t bytesRead = fio.read(buf, 0);
  EXPECT_EQ(0u, bytesRead);
  EXPECT_EQ(0u, fio.tell());

  fio.close();
}

// ==================== PopulateFakeData ====================

TEST_F(FileIoTest_567, PopulateFakeDataDoesNotCrash_567) {
  TempFile tmp("test_fakedata_567.dat", "test");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_NO_THROW(fio.populateFakeData());
}

}  // namespace
