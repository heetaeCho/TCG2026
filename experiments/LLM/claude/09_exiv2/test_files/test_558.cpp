#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <filesystem>

#include "exiv2/basicio.hpp"

namespace {

// Helper to create a temporary file with specific content
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

}  // namespace

class FileIoTest_558 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that size() returns 0 for an empty file
TEST_F(FileIoTest_558, SizeOfEmptyFile_558) {
  TempFile tmp("test_empty_558.dat", "");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(0u, fio.size());
}

// Test that size() returns the correct size for a file with known content
TEST_F(FileIoTest_558, SizeOfNonEmptyFile_558) {
  std::string content = "Hello, World!";
  TempFile tmp("test_nonempty_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(content.size(), fio.size());
}

// Test that size() returns correct size when file is opened for reading
TEST_F(FileIoTest_558, SizeAfterOpenForReading_558) {
  std::string content = "Test data for reading";
  TempFile tmp("test_read_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("r"));
  EXPECT_EQ(content.size(), fio.size());
  fio.close();
}

// Test that size() returns correct size when file is opened for read+write
TEST_F(FileIoTest_558, SizeAfterOpenForReadWrite_558) {
  std::string content = "Read write data";
  TempFile tmp("test_rw_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("r+"));
  EXPECT_EQ(content.size(), fio.size());
  fio.close();
}

// Test size() after writing additional data to the file
TEST_F(FileIoTest_558, SizeAfterWrite_558) {
  std::string content = "Initial";
  TempFile tmp("test_write_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("r+b"));
  
  // Seek to end and write more data
  fio.seek(0, Exiv2::BasicIo::end);
  std::string extra = " extra data";
  fio.write(reinterpret_cast<const Exiv2::byte*>(extra.data()), extra.size());
  
  EXPECT_EQ(content.size() + extra.size(), fio.size());
  fio.close();
}

// Test that size() returns max for a nonexistent file (when not opened)
TEST_F(FileIoTest_558, SizeOfNonexistentFile_558) {
  Exiv2::FileIo fio("/tmp/nonexistent_file_558_xyz_abc.dat");
  // stat should fail for a nonexistent file, returning max
  size_t s = fio.size();
  EXPECT_EQ(std::numeric_limits<size_t>::max(), s);
}

// Test that path() returns the path used during construction
TEST_F(FileIoTest_558, PathReturnsConstructedPath_558) {
  std::string p = "/tmp/some_path_558.dat";
  Exiv2::FileIo fio(p);
  EXPECT_EQ(p, fio.path());
}

// Test open and close cycle
TEST_F(FileIoTest_558, OpenAndClose_558) {
  TempFile tmp("test_openclose_558.dat", "data");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_FALSE(fio.isopen());
  ASSERT_EQ(0, fio.open("r"));
  EXPECT_TRUE(fio.isopen());
  ASSERT_EQ(0, fio.close());
  EXPECT_FALSE(fio.isopen());
}

// Test default open (read mode)
TEST_F(FileIoTest_558, DefaultOpen_558) {
  TempFile tmp("test_defaultopen_558.dat", "some content");
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open());
  EXPECT_TRUE(fio.isopen());
  fio.close();
}

// Test read returns correct data
TEST_F(FileIoTest_558, ReadData_558) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp("test_readdata_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  
  Exiv2::byte buf[20] = {};
  size_t bytesRead = fio.read(buf, 10);
  EXPECT_EQ(10u, bytesRead);
  EXPECT_EQ(0, memcmp(buf, content.data(), 10));
  fio.close();
}

// Test read with DataBuf
TEST_F(FileIoTest_558, ReadDataBuf_558) {
  std::string content = "DataBuf test content";
  TempFile tmp("test_readbuf_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  
  Exiv2::DataBuf dbuf = fio.read(content.size());
  EXPECT_EQ(content.size(), dbuf.size());
  fio.close();
}

// Test tell() reports correct position
TEST_F(FileIoTest_558, TellPosition_558) {
  std::string content = "0123456789";
  TempFile tmp("test_tell_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  EXPECT_EQ(0u, fio.tell());
  
  Exiv2::byte buf[5];
  fio.read(buf, 5);
  EXPECT_EQ(5u, fio.tell());
  fio.close();
}

// Test seek from beginning
TEST_F(FileIoTest_558, SeekFromBeginning_558) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_beg_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  
  ASSERT_EQ(0, fio.seek(5, Exiv2::BasicIo::beg));
  EXPECT_EQ(5u, fio.tell());
  fio.close();
}

// Test seek from end
TEST_F(FileIoTest_558, SeekFromEnd_558) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_end_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  
  ASSERT_EQ(0, fio.seek(-3, Exiv2::BasicIo::end));
  EXPECT_EQ(7u, fio.tell());
  fio.close();
}

// Test seek from current position
TEST_F(FileIoTest_558, SeekFromCurrent_558) {
  std::string content = "0123456789";
  TempFile tmp("test_seek_cur_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  
  fio.seek(3, Exiv2::BasicIo::beg);
  ASSERT_EQ(0, fio.seek(2, Exiv2::BasicIo::cur));
  EXPECT_EQ(5u, fio.tell());
  fio.close();
}

// Test getb returns correct byte
TEST_F(FileIoTest_558, GetByte_558) {
  std::string content = "AB";
  TempFile tmp("test_getb_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  
  int b = fio.getb();
  EXPECT_EQ('A', b);
  b = fio.getb();
  EXPECT_EQ('B', b);
  fio.close();
}

// Test putb writes a byte
TEST_F(FileIoTest_558, PutByte_558) {
  TempFile tmp("test_putb_558.dat", "X");
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("r+b"));
  
  fio.seek(0, Exiv2::BasicIo::beg);
  EXPECT_EQ(0, fio.putb('Y'));
  
  fio.seek(0, Exiv2::BasicIo::beg);
  int b = fio.getb();
  EXPECT_EQ('Y', b);
  fio.close();
}

// Test eof returns true after reading past end
TEST_F(FileIoTest_558, EofAfterReadingPastEnd_558) {
  std::string content = "AB";
  TempFile tmp("test_eof_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  
  Exiv2::byte buf[10];
  fio.read(buf, 10);  // Read more than available
  EXPECT_TRUE(fio.eof());
  fio.close();
}

// Test eof returns false at beginning
TEST_F(FileIoTest_558, EofAtBeginning_558) {
  std::string content = "AB";
  TempFile tmp("test_eof_begin_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  EXPECT_FALSE(fio.eof());
  fio.close();
}

// Test error returns 0 for normal operations
TEST_F(FileIoTest_558, ErrorNormalOperation_558) {
  std::string content = "test";
  TempFile tmp("test_error_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  EXPECT_EQ(0, fio.error());
  fio.close();
}

// Test write with byte array
TEST_F(FileIoTest_558, WriteByteArray_558) {
  TempFile tmp("test_writearray_558.dat", "");
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("wb"));
  
  std::string data = "Hello Test";
  size_t written = fio.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  EXPECT_EQ(data.size(), written);
  fio.close();
  
  // Verify size
  EXPECT_EQ(data.size(), fio.size());
}

// Test setPath changes the path
TEST_F(FileIoTest_558, SetPath_558) {
  TempFile tmp("test_setpath_558.dat", "data");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(tmp.path(), fio.path());
  
  std::string newPath = "/tmp/new_path_558.dat";
  fio.setPath(newPath);
  EXPECT_EQ(newPath, fio.path());
}

// Test size of a large file
TEST_F(FileIoTest_558, SizeOfLargeFile_558) {
  std::string content(10000, 'X');
  TempFile tmp("test_large_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(10000u, fio.size());
}

// Test size after file opened with "w" (truncating)
TEST_F(FileIoTest_558, SizeAfterTruncatingOpen_558) {
  std::string content = "Some data here";
  TempFile tmp("test_trunc_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("wb"));
  // After opening with "w", the file should be truncated
  EXPECT_EQ(0u, fio.size());
  fio.close();
}

// Test size with a single byte file
TEST_F(FileIoTest_558, SizeOfSingleByteFile_558) {
  TempFile tmp("test_singlebyte_558.dat", "X");
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(1u, fio.size());
}

// Test multiple size calls are consistent
TEST_F(FileIoTest_558, MultipleSizeCallsConsistent_558) {
  std::string content = "consistent size";
  TempFile tmp("test_consistent_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  EXPECT_EQ(content.size(), fio.size());
  EXPECT_EQ(content.size(), fio.size());
  EXPECT_EQ(content.size(), fio.size());
}

// Test size reflects writes while file is open
TEST_F(FileIoTest_558, SizeReflectsWritesWhileOpen_558) {
  TempFile tmp("test_sizewrites_558.dat", "");
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("w+b"));
  
  EXPECT_EQ(0u, fio.size());
  
  std::string data = "12345";
  fio.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  EXPECT_EQ(5u, fio.size());
  
  std::string more = "67890";
  fio.write(reinterpret_cast<const Exiv2::byte*>(more.data()), more.size());
  EXPECT_EQ(10u, fio.size());
  
  fio.close();
}

// Test open on nonexistent file fails
TEST_F(FileIoTest_558, OpenNonexistentFileForReadFails_558) {
  Exiv2::FileIo fio("/tmp/nonexistent_opentest_558.dat");
  int result = fio.open("rb");
  EXPECT_NE(0, result);
  EXPECT_FALSE(fio.isopen());
}

// Test mmap and munmap
TEST_F(FileIoTest_558, MmapAndMunmap_558) {
  std::string content = "mmap test data";
  TempFile tmp("test_mmap_558.dat", content);
  Exiv2::FileIo fio(tmp.path());
  ASSERT_EQ(0, fio.open("rb"));
  
  Exiv2::byte* mapped = fio.mmap(false);
  ASSERT_NE(nullptr, mapped);
  EXPECT_EQ(0, memcmp(mapped, content.data(), content.size()));
  
  ASSERT_EQ(0, fio.munmap());
  fio.close();
}
