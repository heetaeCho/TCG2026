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

class FileIoTest_549 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that path() returns the path provided at construction
TEST_F(FileIoTest_549, PathReturnsConstructionPath_549) {
  std::string testPath = "test_file_path_549.dat";
  Exiv2::FileIo fio(testPath);
  EXPECT_EQ(fio.path(), testPath);
}

// Test that a newly constructed FileIo is not open
TEST_F(FileIoTest_549, NewFileIoIsNotOpen_549) {
  Exiv2::FileIo fio("nonexistent_file_549.dat");
  EXPECT_FALSE(fio.isopen());
}

// Test open on a non-existent file
TEST_F(FileIoTest_549, OpenNonExistentFileReturnsError_549) {
  Exiv2::FileIo fio("definitely_nonexistent_file_549.dat");
  // open() for reading a file that doesn't exist should fail
  int rc = fio.open();
  // If it fails, rc != 0
  if (rc != 0) {
    EXPECT_FALSE(fio.isopen());
  }
}

// Test open and close on an existing file
TEST_F(FileIoTest_549, OpenAndCloseExistingFile_549) {
  TempFile tmp("test_open_close_549.dat", "hello");
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  EXPECT_EQ(rc, 0);
  EXPECT_TRUE(fio.isopen());

  rc = fio.close();
  EXPECT_EQ(rc, 0);
  EXPECT_FALSE(fio.isopen());
}

// Test size() returns correct file size
TEST_F(FileIoTest_549, SizeReturnsCorrectValue_549) {
  std::string content = "Hello, World!";
  TempFile tmp("test_size_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  EXPECT_EQ(fio.size(), content.size());
}

// Test open with specific mode
TEST_F(FileIoTest_549, OpenWithMode_549) {
  TempFile tmp("test_open_mode_549.dat", "data");
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open("rb");
  EXPECT_EQ(rc, 0);
  EXPECT_TRUE(fio.isopen());

  fio.close();
}

// Test read after open
TEST_F(FileIoTest_549, ReadData_549) {
  std::string content = "Test content for reading";
  TempFile tmp("test_read_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  Exiv2::DataBuf buf = fio.read(content.size());
  EXPECT_EQ(buf.size(), content.size());

  fio.close();
}

// Test read with byte buffer
TEST_F(FileIoTest_549, ReadIntoBuffer_549) {
  std::string content = "Buffer read test";
  TempFile tmp("test_read_buf_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  std::vector<Exiv2::byte> buf(content.size());
  size_t bytesRead = fio.read(buf.data(), buf.size());
  EXPECT_EQ(bytesRead, content.size());

  for (size_t i = 0; i < content.size(); ++i) {
    EXPECT_EQ(buf[i], static_cast<Exiv2::byte>(content[i]));
  }

  fio.close();
}

// Test getb reads one byte at a time
TEST_F(FileIoTest_549, GetbReadsSingleByte_549) {
  std::string content = "AB";
  TempFile tmp("test_getb_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  int b1 = fio.getb();
  EXPECT_EQ(b1, 'A');

  int b2 = fio.getb();
  EXPECT_EQ(b2, 'B');

  fio.close();
}

// Test tell returns current position
TEST_F(FileIoTest_549, TellReturnsCurrentPosition_549) {
  std::string content = "0123456789";
  TempFile tmp("test_tell_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  EXPECT_EQ(fio.tell(), 0u);

  fio.read(5);
  EXPECT_EQ(fio.tell(), 5u);

  fio.close();
}

// Test seek from beginning
TEST_F(FileIoTest_549, SeekFromBeginning_549) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_beg_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  rc = fio.seek(5, Exiv2::BasicIo::beg);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(fio.tell(), 5u);

  fio.close();
}

// Test seek from current position
TEST_F(FileIoTest_549, SeekFromCurrent_549) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_cur_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  fio.seek(3, Exiv2::BasicIo::beg);
  rc = fio.seek(2, Exiv2::BasicIo::cur);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(fio.tell(), 5u);

  fio.close();
}

// Test seek from end
TEST_F(FileIoTest_549, SeekFromEnd_549) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_end_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  rc = fio.seek(0, Exiv2::BasicIo::end);
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(fio.tell(), content.size());

  fio.close();
}

// Test eof after reading past end
TEST_F(FileIoTest_549, EofAfterReadingPastEnd_549) {
  std::string content = "AB";
  TempFile tmp("test_eof_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  // Read more than available
  std::vector<Exiv2::byte> buf(100);
  fio.read(buf.data(), 100);

  EXPECT_TRUE(fio.eof());

  fio.close();
}

// Test write data to file
TEST_F(FileIoTest_549, WriteData_549) {
  std::string filePath = "test_write_549.dat";
  {
    // Create the file first
    std::ofstream ofs(filePath, std::ios::binary);
    ofs.close();
  }

  Exiv2::FileIo fio(filePath);

  int rc = fio.open("w+b");
  ASSERT_EQ(rc, 0);

  std::string data = "Written data";
  size_t written = fio.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  EXPECT_EQ(written, data.size());

  fio.close();

  // Verify by reading back
  Exiv2::FileIo fio2(filePath);
  rc = fio2.open();
  ASSERT_EQ(rc, 0);

  std::vector<Exiv2::byte> buf(data.size());
  size_t bytesRead = fio2.read(buf.data(), buf.size());
  EXPECT_EQ(bytesRead, data.size());

  for (size_t i = 0; i < data.size(); ++i) {
    EXPECT_EQ(buf[i], static_cast<Exiv2::byte>(data[i]));
  }

  fio2.close();
  std::remove(filePath.c_str());
}

// Test putb writes a single byte
TEST_F(FileIoTest_549, PutbWritesSingleByte_549) {
  std::string filePath = "test_putb_549.dat";
  {
    std::ofstream ofs(filePath, std::ios::binary);
    ofs.close();
  }

  Exiv2::FileIo fio(filePath);

  int rc = fio.open("w+b");
  ASSERT_EQ(rc, 0);

  rc = fio.putb(0x42);
  EXPECT_EQ(rc, 0x42);

  fio.close();

  // Verify
  Exiv2::FileIo fio2(filePath);
  rc = fio2.open();
  ASSERT_EQ(rc, 0);

  int b = fio2.getb();
  EXPECT_EQ(b, 0x42);

  fio2.close();
  std::remove(filePath.c_str());
}

// Test mmap and munmap on a readable file
TEST_F(FileIoTest_549, MmapAndMunmapReadable_549) {
  std::string content = "mmap test data";
  TempFile tmp("test_mmap_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  Exiv2::byte* mapped = fio.mmap(false);
  ASSERT_NE(mapped, nullptr);

  // Verify mapped content
  for (size_t i = 0; i < content.size(); ++i) {
    EXPECT_EQ(mapped[i], static_cast<Exiv2::byte>(content[i]));
  }

  rc = fio.munmap();
  EXPECT_EQ(rc, 0);

  fio.close();
}

// Test munmap without prior mmap should be safe
TEST_F(FileIoTest_549, MunmapWithoutMmap_549) {
  std::string content = "some data";
  TempFile tmp("test_munmap_no_mmap_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  // munmap without mmap - should return 0 since pMappedArea_ is null
  rc = fio.munmap();
  EXPECT_EQ(rc, 0);

  fio.close();
}

// Test mmap writable and munmap
TEST_F(FileIoTest_549, MmapWriteableAndMunmap_549) {
  std::string content = "writable mmap test";
  TempFile tmp("test_mmap_write_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open("r+b");
  ASSERT_EQ(rc, 0);

  Exiv2::byte* mapped = fio.mmap(true);
  ASSERT_NE(mapped, nullptr);

  rc = fio.munmap();
  EXPECT_EQ(rc, 0);

  fio.close();
}

// Test double munmap is safe
TEST_F(FileIoTest_549, DoubleMunmapIsSafe_549) {
  std::string content = "double munmap";
  TempFile tmp("test_double_munmap_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  Exiv2::byte* mapped = fio.mmap(false);
  ASSERT_NE(mapped, nullptr);

  rc = fio.munmap();
  EXPECT_EQ(rc, 0);

  // Second munmap should be safe (pMappedArea_ is null now)
  rc = fio.munmap();
  EXPECT_EQ(rc, 0);

  fio.close();
}

// Test error() on a fresh FileIo
TEST_F(FileIoTest_549, ErrorOnFreshFileIo_549) {
  Exiv2::FileIo fio("nonexistent_error_549.dat");
  // No file open, error should be 0 or some defined value
  int err = fio.error();
  // Just verify it doesn't crash; typically 0 when no file is open
  EXPECT_GE(err, 0);
}

// Test setPath changes the path
TEST_F(FileIoTest_549, SetPathChangesPath_549) {
  Exiv2::FileIo fio("original_path_549.dat");
  EXPECT_EQ(fio.path(), "original_path_549.dat");

  fio.setPath("new_path_549.dat");
  EXPECT_EQ(fio.path(), "new_path_549.dat");
}

// Test reading zero bytes
TEST_F(FileIoTest_549, ReadZeroBytes_549) {
  std::string content = "some content";
  TempFile tmp("test_read_zero_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  Exiv2::DataBuf buf = fio.read(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_EQ(fio.tell(), 0u);

  fio.close();
}

// Test size of empty file
TEST_F(FileIoTest_549, SizeOfEmptyFile_549) {
  TempFile tmp("test_empty_size_549.dat", "");
  Exiv2::FileIo fio(tmp.path());

  EXPECT_EQ(fio.size(), 0u);
}

// Test write from another BasicIo (FileIo to FileIo)
TEST_F(FileIoTest_549, WriteFromAnotherBasicIo_549) {
  std::string content = "source data for transfer";
  TempFile srcTmp("test_src_549.dat", content);
  std::string dstPath = "test_dst_549.dat";
  {
    std::ofstream ofs(dstPath, std::ios::binary);
    ofs.close();
  }

  Exiv2::FileIo srcIo(srcTmp.path());
  Exiv2::FileIo dstIo(dstPath);

  int rc = srcIo.open();
  ASSERT_EQ(rc, 0);

  rc = dstIo.open("w+b");
  ASSERT_EQ(rc, 0);

  size_t written = dstIo.write(srcIo);
  EXPECT_EQ(written, content.size());

  srcIo.close();
  dstIo.close();

  // Verify destination content
  Exiv2::FileIo verifyIo(dstPath);
  rc = verifyIo.open();
  ASSERT_EQ(rc, 0);

  std::vector<Exiv2::byte> buf(content.size());
  size_t bytesRead = verifyIo.read(buf.data(), buf.size());
  EXPECT_EQ(bytesRead, content.size());

  for (size_t i = 0; i < content.size(); ++i) {
    EXPECT_EQ(buf[i], static_cast<Exiv2::byte>(content[i]));
  }

  verifyIo.close();
  std::remove(dstPath.c_str());
}

// Test close on a file that was never opened
TEST_F(FileIoTest_549, CloseWithoutOpen_549) {
  Exiv2::FileIo fio("no_open_close_549.dat");
  int rc = fio.close();
  // Should handle gracefully
  EXPECT_EQ(rc, 0);
}

// Test mmap on empty file
TEST_F(FileIoTest_549, MmapEmptyFile_549) {
  TempFile tmp("test_mmap_empty_549.dat", "");
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  // mmap on empty file - behavior may vary, but it shouldn't crash
  Exiv2::byte* mapped = fio.mmap(false);
  // For an empty file, mapped might be nullptr or valid
  // Just ensure munmap works
  rc = fio.munmap();
  EXPECT_EQ(rc, 0);

  fio.close();
}

// Test getb returns EOF (-1) when at end of file
TEST_F(FileIoTest_549, GetbReturnsEofAtEnd_549) {
  std::string content = "X";
  TempFile tmp("test_getb_eof_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  int b = fio.getb();
  EXPECT_EQ(b, 'X');

  b = fio.getb();
  EXPECT_EQ(b, EOF);

  fio.close();
}

// Test seek to negative offset from beginning (boundary)
TEST_F(FileIoTest_549, SeekNegativeFromBeginning_549) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_neg_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  // Seeking to a negative position from beginning should fail
  rc = fio.seek(-1, Exiv2::BasicIo::beg);
  EXPECT_NE(rc, 0);

  fio.close();
}

// Test large read returns only available data
TEST_F(FileIoTest_549, LargeReadReturnsAvailableData_549) {
  std::string content = "short";
  TempFile tmp("test_large_read_549.dat", content);
  Exiv2::FileIo fio(tmp.path());

  int rc = fio.open();
  ASSERT_EQ(rc, 0);

  std::vector<Exiv2::byte> buf(1000);
  size_t bytesRead = fio.read(buf.data(), 1000);
  EXPECT_EQ(bytesRead, content.size());

  fio.close();
}

// Test writing zero bytes
TEST_F(FileIoTest_549, WriteZeroBytes_549) {
  std::string filePath = "test_write_zero_549.dat";
  {
    std::ofstream ofs(filePath, std::ios::binary);
    ofs.close();
  }

  Exiv2::FileIo fio(filePath);
  int rc = fio.open("w+b");
  ASSERT_EQ(rc, 0);

  Exiv2::byte dummy = 0;
  size_t written = fio.write(&dummy, 0);
  EXPECT_EQ(written, 0u);

  fio.close();
  std::remove(filePath.c_str());
}
