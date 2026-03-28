#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <filesystem>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

namespace {

// Helper to create a temporary file with given content
class TempFile {
 public:
  explicit TempFile(const std::string& content, const std::string& suffix = ".tmp") {
    path_ = std::filesystem::temp_directory_path() / ("exiv2_test_563_" + std::to_string(counter_++) + suffix);
    std::ofstream ofs(path_, std::ios::binary);
    ofs.write(content.data(), static_cast<std::streamsize>(content.size()));
    ofs.close();
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

// Helper to create an empty temp file path (may or may not exist)
std::string nonExistentPath() {
  auto p = std::filesystem::temp_directory_path() / "exiv2_test_563_nonexistent_file.tmp";
  std::filesystem::remove(p);
  return p.string();
}

}  // namespace

class FileIoTest_563 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that constructor sets the path correctly
TEST_F(FileIoTest_563, ConstructorSetsPath_563) {
  std::string testPath = "/some/test/path.jpg";
  Exiv2::FileIo io(testPath);
  EXPECT_EQ(io.path(), testPath);
}

// Test that a newly constructed FileIo is not open
TEST_F(FileIoTest_563, NewFileIoIsNotOpen_563) {
  TempFile tmp("hello");
  Exiv2::FileIo io(tmp.path());
  EXPECT_FALSE(io.isopen());
}

// Test open and close on an existing file
TEST_F(FileIoTest_563, OpenAndClose_563) {
  TempFile tmp("test data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_TRUE(io.isopen());
  EXPECT_EQ(io.close(), 0);
  EXPECT_FALSE(io.isopen());
}

// Test open with mode string
TEST_F(FileIoTest_563, OpenWithMode_563) {
  TempFile tmp("test data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("rb"), 0);
  EXPECT_TRUE(io.isopen());
  io.close();
}

// Test open on a non-existent file returns error
TEST_F(FileIoTest_563, OpenNonExistentFileReturnsError_563) {
  std::string path = nonExistentPath();
  Exiv2::FileIo io(path);
  EXPECT_NE(io.open(), 0);
  EXPECT_FALSE(io.isopen());
}

// Test size returns correct file size
TEST_F(FileIoTest_563, SizeReturnsCorrectValue_563) {
  std::string content = "Hello, World!";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.size(), content.size());
  io.close();
}

// Test size of empty file
TEST_F(FileIoTest_563, SizeOfEmptyFile_563) {
  TempFile tmp("");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.size(), 0u);
  io.close();
}

// Test read with DataBuf return for normal case
TEST_F(FileIoTest_563, ReadDataBufNormal_563) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  Exiv2::DataBuf buf = io.read(5);
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_EQ(std::memcmp(buf.c_data(), "ABCDE", 5), 0);
  io.close();
}

// Test read entire file
TEST_F(FileIoTest_563, ReadEntireFile_563) {
  std::string content = "Complete file content";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  Exiv2::DataBuf buf = io.read(content.size());
  EXPECT_EQ(buf.size(), content.size());
  EXPECT_EQ(std::memcmp(buf.c_data(), content.data(), content.size()), 0);
  io.close();
}

// Test read with rcount larger than file size throws
TEST_F(FileIoTest_563, ReadMoreThanSizeThrows_563) {
  std::string content = "small";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  EXPECT_THROW(io.read(content.size() + 100), Exiv2::Error);
  io.close();
}

// Test read with byte buffer
TEST_F(FileIoTest_563, ReadByteBufNormal_563) {
  std::string content = "0123456789";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  Exiv2::byte buf[10];
  size_t count = io.read(buf, 5);
  EXPECT_EQ(count, 5u);
  EXPECT_EQ(std::memcmp(buf, "01234", 5), 0);
  io.close();
}

// Test sequential reads
TEST_F(FileIoTest_563, SequentialReads_563) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  Exiv2::byte buf1[5], buf2[5];
  size_t c1 = io.read(buf1, 5);
  size_t c2 = io.read(buf2, 5);
  EXPECT_EQ(c1, 5u);
  EXPECT_EQ(c2, 5u);
  EXPECT_EQ(std::memcmp(buf1, "ABCDE", 5), 0);
  EXPECT_EQ(std::memcmp(buf2, "FGHIJ", 5), 0);
  io.close();
}

// Test tell after open is 0
TEST_F(FileIoTest_563, TellAtStartIsZero_563) {
  TempFile tmp("data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.tell(), 0u);
  io.close();
}

// Test tell advances after read
TEST_F(FileIoTest_563, TellAdvancesAfterRead_563) {
  std::string content = "1234567890";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  Exiv2::byte buf[4];
  io.read(buf, 4);
  EXPECT_EQ(io.tell(), 4u);
  io.close();
}

// Test seek from beginning
TEST_F(FileIoTest_563, SeekFromBeginning_563) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  EXPECT_EQ(io.seek(5, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(io.tell(), 5u);

  Exiv2::byte buf[5];
  size_t count = io.read(buf, 5);
  EXPECT_EQ(count, 5u);
  EXPECT_EQ(std::memcmp(buf, "FGHIJ", 5), 0);
  io.close();
}

// Test seek from current position
TEST_F(FileIoTest_563, SeekFromCurrent_563) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  io.seek(3, Exiv2::BasicIo::beg);
  io.seek(2, Exiv2::BasicIo::cur);
  EXPECT_EQ(io.tell(), 5u);
  io.close();
}

// Test seek from end
TEST_F(FileIoTest_563, SeekFromEnd_563) {
  std::string content = "ABCDEFGHIJ";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  io.seek(-3, Exiv2::BasicIo::end);
  Exiv2::byte buf[3];
  size_t count = io.read(buf, 3);
  EXPECT_EQ(count, 3u);
  EXPECT_EQ(std::memcmp(buf, "HIJ", 3), 0);
  io.close();
}

// Test getb reads one byte at a time
TEST_F(FileIoTest_563, GetbReadsSingleByte_563) {
  std::string content = "AB";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  int b1 = io.getb();
  int b2 = io.getb();
  EXPECT_EQ(b1, 'A');
  EXPECT_EQ(b2, 'B');
  io.close();
}

// Test getb returns EOF at end of file
TEST_F(FileIoTest_563, GetbReturnsEofAtEnd_563) {
  std::string content = "X";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  io.getb();  // read 'X'
  int b = io.getb();  // should be EOF
  EXPECT_EQ(b, EOF);
  io.close();
}

// Test eof
TEST_F(FileIoTest_563, EofDetection_563) {
  std::string content = "AB";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  Exiv2::byte buf[10];
  io.read(buf, 10);  // read past end
  EXPECT_TRUE(io.eof());
  io.close();
}

// Test write data
TEST_F(FileIoTest_563, WriteAndReadBack_563) {
  TempFile tmp("");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);

  const std::string data = "Hello, FileIo!";
  size_t written = io.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
  EXPECT_EQ(written, data.size());

  io.seek(0, Exiv2::BasicIo::beg);
  Exiv2::byte buf[20];
  size_t readCount = io.read(buf, data.size());
  EXPECT_EQ(readCount, data.size());
  EXPECT_EQ(std::memcmp(buf, data.data(), data.size()), 0);
  io.close();
}

// Test putb writes a single byte
TEST_F(FileIoTest_563, PutbWritesSingleByte_563) {
  TempFile tmp("");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);

  int result = io.putb(0x42);
  EXPECT_EQ(result, 0x42);

  io.seek(0, Exiv2::BasicIo::beg);
  int readByte = io.getb();
  EXPECT_EQ(readByte, 0x42);
  io.close();
}

// Test error returns 0 for a valid file operation
TEST_F(FileIoTest_563, ErrorReturnsZeroOnSuccess_563) {
  TempFile tmp("data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_EQ(io.error(), 0);
  io.close();
}

// Test setPath changes the path
TEST_F(FileIoTest_563, SetPathChangesPath_563) {
  TempFile tmp("data");
  Exiv2::FileIo io(tmp.path());
  std::string newPath = "/new/path/to/file.jpg";
  io.setPath(newPath);
  EXPECT_EQ(io.path(), newPath);
}

// Test reading from empty file with DataBuf throws
TEST_F(FileIoTest_563, ReadDataBufFromEmptyFileThrows_563) {
  TempFile tmp("");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  // rcount = 0 should satisfy rcount <= size(), but read 0 bytes -> readCount == 0 -> throws
  // Actually, size() == 0 and rcount == 0 means 0 > 0 is false, so no throw on first check.
  // Then DataBuf(0) is created, read(buf.data(), 0) is called.
  // If readCount == 0, it throws kerInputDataReadFailed.
  // But let's also test requesting non-zero from empty file.
  EXPECT_THROW(io.read(1), Exiv2::Error);
  io.close();
}

// Test read DataBuf with rcount = 0 from empty file
TEST_F(FileIoTest_563, ReadDataBufZeroFromEmptyFile_563) {
  TempFile tmp("");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  // rcount=0, size()=0, so 0 > 0 is false. DataBuf(0). read(data, 0) returns 0.
  // Then 0 == 0 -> throws kerInputDataReadFailed
  EXPECT_THROW(io.read(0), Exiv2::Error);
  io.close();
}

// Test close on already closed file
TEST_F(FileIoTest_563, CloseOnClosedFile_563) {
  TempFile tmp("data");
  Exiv2::FileIo io(tmp.path());
  // close without opening should not crash
  EXPECT_EQ(io.close(), 0);
}

// Test mmap and munmap
TEST_F(FileIoTest_563, MmapAndMunmap_563) {
  std::string content = "mmap test data";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  Exiv2::byte* mapped = io.mmap(false);
  ASSERT_NE(mapped, nullptr);
  EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);

  EXPECT_EQ(io.munmap(), 0);
  io.close();
}

// Test reading with byte buffer more than available returns partial
TEST_F(FileIoTest_563, ReadByteBufPartialAtEnd_563) {
  std::string content = "short";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  Exiv2::byte buf[100];
  size_t count = io.read(buf, 100);
  EXPECT_EQ(count, content.size());
  EXPECT_EQ(std::memcmp(buf, content.data(), content.size()), 0);
  io.close();
}

// Test write from another BasicIo
TEST_F(FileIoTest_563, WriteFromBasicIo_563) {
  std::string content = "source content";
  TempFile srcFile(content);
  TempFile dstFile("");

  Exiv2::FileIo src(srcFile.path());
  Exiv2::FileIo dst(dstFile.path());

  EXPECT_EQ(src.open(), 0);
  EXPECT_EQ(dst.open("w+b"), 0);

  size_t written = dst.write(src);
  EXPECT_EQ(written, content.size());

  dst.seek(0, Exiv2::BasicIo::beg);
  Exiv2::byte buf[100];
  size_t readCount = dst.read(buf, content.size());
  EXPECT_EQ(readCount, content.size());
  EXPECT_EQ(std::memcmp(buf, content.data(), content.size()), 0);

  src.close();
  dst.close();
}

// Test multiple open calls
TEST_F(FileIoTest_563, MultipleOpenCalls_563) {
  TempFile tmp("data");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);
  EXPECT_TRUE(io.isopen());
  // Opening again should still work (or at least not crash)
  EXPECT_EQ(io.open(), 0);
  EXPECT_TRUE(io.isopen());
  io.close();
}

// Test read DataBuf returns correct size when reading partial at position
TEST_F(FileIoTest_563, ReadDataBufAfterSeek_563) {
  std::string content = "0123456789";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  io.seek(7, Exiv2::BasicIo::beg);
  // Remaining is 3 bytes. Request 3.
  Exiv2::DataBuf buf = io.read(3);
  EXPECT_EQ(buf.size(), 3u);
  EXPECT_EQ(std::memcmp(buf.c_data(), "789", 3), 0);
  io.close();
}

// Test that read(DataBuf) with request bigger than size from a seeked position throws
TEST_F(FileIoTest_563, ReadDataBufExceedsSizeFromMiddleThrows_563) {
  std::string content = "0123456789";
  TempFile tmp(content);
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open(), 0);

  // size() returns total file size (10), not remaining
  // So requesting 11 > 10 should throw kerInvalidMalloc
  EXPECT_THROW(io.read(11), Exiv2::Error);
  io.close();
}

// Test binary data read/write
TEST_F(FileIoTest_563, BinaryDataReadWrite_563) {
  TempFile tmp("");
  Exiv2::FileIo io(tmp.path());
  EXPECT_EQ(io.open("w+b"), 0);

  Exiv2::byte binaryData[] = {0x00, 0x01, 0xFF, 0xFE, 0x80, 0x7F};
  size_t written = io.write(binaryData, sizeof(binaryData));
  EXPECT_EQ(written, sizeof(binaryData));

  io.seek(0, Exiv2::BasicIo::beg);
  Exiv2::byte readBuf[6];
  size_t readCount = io.read(readBuf, sizeof(readBuf));
  EXPECT_EQ(readCount, sizeof(binaryData));
  EXPECT_EQ(std::memcmp(readBuf, binaryData, sizeof(binaryData)), 0);
  io.close();
}
