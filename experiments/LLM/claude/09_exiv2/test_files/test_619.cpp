#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <filesystem>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

namespace fs = std::filesystem;

// Helper to create a temporary file with given content
class ReadFileTest_619 : public ::testing::Test {
 protected:
  std::string tempDir_;

  void SetUp() override {
    tempDir_ = fs::temp_directory_path().string();
  }

  std::string createTempFile(const std::string& name, const std::string& content) {
    std::string path = tempDir_ + "/" + name;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(content.data(), content.size());
    ofs.close();
    return path;
  }

  std::string createTempFile(const std::string& name, const std::vector<uint8_t>& content) {
    std::string path = tempDir_ + "/" + name;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
    ofs.close();
    return path;
  }

  void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
  }
};

// Test reading a normal file with known content
TEST_F(ReadFileTest_619, ReadNormalFile_619) {
  std::string content = "Hello, World!";
  std::string path = createTempFile("test_readfile_normal_619.bin", content);

  Exiv2::DataBuf buf = Exiv2::readFile(path);
  ASSERT_EQ(buf.size(), content.size());
  EXPECT_EQ(std::memcmp(buf.c_data(0), content.data(), content.size()), 0);

  removeTempFile(path);
}

// Test reading an empty file
TEST_F(ReadFileTest_619, ReadEmptyFile_619) {
  std::string content = "";
  std::string path = createTempFile("test_readfile_empty_619.bin", content);

  Exiv2::DataBuf buf = Exiv2::readFile(path);
  EXPECT_EQ(buf.size(), 0u);

  removeTempFile(path);
}

// Test reading a file that does not exist throws an error
TEST_F(ReadFileTest_619, ReadNonExistentFileThrows_619) {
  std::string path = tempDir_ + "/nonexistent_file_619.bin";
  // Make sure file doesn't exist
  std::remove(path.c_str());

  EXPECT_THROW(Exiv2::readFile(path), Exiv2::Error);
}

// Test reading a binary file with all byte values
TEST_F(ReadFileTest_619, ReadBinaryFile_619) {
  std::vector<uint8_t> content(256);
  for (int i = 0; i < 256; ++i) {
    content[i] = static_cast<uint8_t>(i);
  }
  std::string path = createTempFile("test_readfile_binary_619.bin", content);

  Exiv2::DataBuf buf = Exiv2::readFile(path);
  ASSERT_EQ(buf.size(), 256u);
  for (size_t i = 0; i < 256; ++i) {
    EXPECT_EQ(buf.read_uint8(i), static_cast<uint8_t>(i)) << "Mismatch at byte " << i;
  }

  removeTempFile(path);
}

// Test reading a file with a single byte
TEST_F(ReadFileTest_619, ReadSingleByteFile_619) {
  std::string content(1, '\x42');
  std::string path = createTempFile("test_readfile_singlebyte_619.bin", content);

  Exiv2::DataBuf buf = Exiv2::readFile(path);
  ASSERT_EQ(buf.size(), 1u);
  EXPECT_EQ(buf.read_uint8(0), 0x42);

  removeTempFile(path);
}

// Test reading a larger file
TEST_F(ReadFileTest_619, ReadLargerFile_619) {
  std::string content(10000, 'A');
  std::string path = createTempFile("test_readfile_large_619.bin", content);

  Exiv2::DataBuf buf = Exiv2::readFile(path);
  ASSERT_EQ(buf.size(), 10000u);
  EXPECT_EQ(std::memcmp(buf.c_data(0), content.data(), content.size()), 0);

  removeTempFile(path);
}

// Test reading a file with null bytes
TEST_F(ReadFileTest_619, ReadFileWithNullBytes_619) {
  std::vector<uint8_t> content = {0x00, 0x01, 0x00, 0x02, 0x00};
  std::string path = createTempFile("test_readfile_nullbytes_619.bin", content);

  Exiv2::DataBuf buf = Exiv2::readFile(path);
  ASSERT_EQ(buf.size(), 5u);
  EXPECT_EQ(buf.read_uint8(0), 0x00);
  EXPECT_EQ(buf.read_uint8(1), 0x01);
  EXPECT_EQ(buf.read_uint8(2), 0x00);
  EXPECT_EQ(buf.read_uint8(3), 0x02);
  EXPECT_EQ(buf.read_uint8(4), 0x00);

  removeTempFile(path);
}

// Test that the returned DataBuf has correct data integrity
TEST_F(ReadFileTest_619, DataBufIntegrity_619) {
  std::string content = "EXIV2TEST";
  std::string path = createTempFile("test_readfile_integrity_619.bin", content);

  Exiv2::DataBuf buf = Exiv2::readFile(path);
  ASSERT_EQ(buf.size(), content.size());
  EXPECT_FALSE(buf.empty());

  // Compare using c_str
  EXPECT_EQ(std::string(buf.c_str(0), buf.size()), content);

  removeTempFile(path);
}

// Test reading with an empty path string throws
TEST_F(ReadFileTest_619, ReadEmptyPathThrows_619) {
  EXPECT_THROW(Exiv2::readFile(""), Exiv2::Error);
}

// FileIo specific tests

class FileIoTest_619 : public ::testing::Test {
 protected:
  std::string tempDir_;

  void SetUp() override {
    tempDir_ = fs::temp_directory_path().string();
  }

  std::string createTempFile(const std::string& name, const std::string& content) {
    std::string path = tempDir_ + "/" + name;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(content.data(), content.size());
    ofs.close();
    return path;
  }

  void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
  }
};

// Test FileIo constructor and path
TEST_F(FileIoTest_619, ConstructorAndPath_619) {
  std::string path = tempDir_ + "/test_fileio_path_619.bin";
  Exiv2::FileIo file(path);
  EXPECT_EQ(file.path(), path);
}

// Test FileIo open and close
TEST_F(FileIoTest_619, OpenAndClose_619) {
  std::string content = "test data";
  std::string path = createTempFile("test_fileio_openclose_619.bin", content);

  Exiv2::FileIo file(path);
  EXPECT_EQ(file.open("rb"), 0);
  EXPECT_TRUE(file.isopen());
  EXPECT_EQ(file.close(), 0);
  EXPECT_FALSE(file.isopen());

  removeTempFile(path);
}

// Test FileIo open nonexistent file
TEST_F(FileIoTest_619, OpenNonexistentFile_619) {
  std::string path = tempDir_ + "/nonexistent_fileio_619.bin";
  std::remove(path.c_str());

  Exiv2::FileIo file(path);
  EXPECT_NE(file.open("rb"), 0);
}

// Test FileIo read
TEST_F(FileIoTest_619, ReadData_619) {
  std::string content = "Hello FileIo";
  std::string path = createTempFile("test_fileio_read_619.bin", content);

  Exiv2::FileIo file(path);
  ASSERT_EQ(file.open("rb"), 0);

  uint8_t buf[20] = {};
  size_t bytesRead = file.read(buf, content.size());
  EXPECT_EQ(bytesRead, content.size());
  EXPECT_EQ(std::memcmp(buf, content.data(), content.size()), 0);

  file.close();
  removeTempFile(path);
}

// Test FileIo write and read back
TEST_F(FileIoTest_619, WriteAndReadBack_619) {
  std::string path = tempDir_ + "/test_fileio_write_619.bin";

  {
    Exiv2::FileIo file(path);
    ASSERT_EQ(file.open("wb"), 0);

    const uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    size_t written = file.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    file.close();
  }

  {
    Exiv2::FileIo file(path);
    ASSERT_EQ(file.open("rb"), 0);

    uint8_t buf[4] = {};
    size_t bytesRead = file.read(buf, 4);
    EXPECT_EQ(bytesRead, 4u);
    EXPECT_EQ(buf[0], 0xDE);
    EXPECT_EQ(buf[1], 0xAD);
    EXPECT_EQ(buf[2], 0xBE);
    EXPECT_EQ(buf[3], 0xEF);
    file.close();
  }

  removeTempFile(path);
}

// Test FileIo size
TEST_F(FileIoTest_619, FileSize_619) {
  std::string content = "1234567890";
  std::string path = createTempFile("test_fileio_size_619.bin", content);

  Exiv2::FileIo file(path);
  ASSERT_EQ(file.open("rb"), 0);
  EXPECT_EQ(file.size(), 10u);
  file.close();

  removeTempFile(path);
}

// Test FileIo tell and seek
TEST_F(FileIoTest_619, TellAndSeek_619) {
  std::string content = "ABCDEFGHIJ";
  std::string path = createTempFile("test_fileio_seek_619.bin", content);

  Exiv2::FileIo file(path);
  ASSERT_EQ(file.open("rb"), 0);

  EXPECT_EQ(file.tell(), 0u);

  // Seek to position 5 from beginning
  EXPECT_EQ(file.seek(5, Exiv2::BasicIo::beg), 0);
  EXPECT_EQ(file.tell(), 5u);

  // Read one byte at position 5 ('F')
  int b = file.getb();
  EXPECT_EQ(b, 'F');
  EXPECT_EQ(file.tell(), 6u);

  // Seek from current position
  EXPECT_EQ(file.seek(2, Exiv2::BasicIo::cur), 0);
  EXPECT_EQ(file.tell(), 8u);

  // Seek from end
  EXPECT_EQ(file.seek(-3, Exiv2::BasicIo::end), 0);
  EXPECT_EQ(file.tell(), 7u);

  file.close();
  removeTempFile(path);
}

// Test FileIo eof
TEST_F(FileIoTest_619, EofDetection_619) {
  std::string content = "AB";
  std::string path = createTempFile("test_fileio_eof_619.bin", content);

  Exiv2::FileIo file(path);
  ASSERT_EQ(file.open("rb"), 0);

  uint8_t buf[10];
  file.read(buf, 10);  // Read more than available
  EXPECT_TRUE(file.eof());

  file.close();
  removeTempFile(path);
}

// Test FileIo putb
TEST_F(FileIoTest_619, PutByte_619) {
  std::string path = tempDir_ + "/test_fileio_putb_619.bin";

  {
    Exiv2::FileIo file(path);
    ASSERT_EQ(file.open("wb"), 0);
    EXPECT_EQ(file.putb(0x42), 0);
    EXPECT_EQ(file.putb(0x43), 0);
    file.close();
  }

  {
    Exiv2::FileIo file(path);
    ASSERT_EQ(file.open("rb"), 0);
    EXPECT_EQ(file.getb(), 0x42);
    EXPECT_EQ(file.getb(), 0x43);
    file.close();
  }

  removeTempFile(path);
}

// Test FileIo read returning DataBuf
TEST_F(FileIoTest_619, ReadDataBuf_619) {
  std::string content = "DataBuf test content";
  std::string path = createTempFile("test_fileio_readbuf_619.bin", content);

  Exiv2::FileIo file(path);
  ASSERT_EQ(file.open("rb"), 0);

  Exiv2::DataBuf buf = file.read(content.size());
  ASSERT_EQ(buf.size(), content.size());
  EXPECT_EQ(std::memcmp(buf.c_data(0), content.data(), content.size()), 0);

  file.close();
  removeTempFile(path);
}

// Test FileIo error returns 0 on success
TEST_F(FileIoTest_619, ErrorOnSuccess_619) {
  std::string content = "test";
  std::string path = createTempFile("test_fileio_error_619.bin", content);

  Exiv2::FileIo file(path);
  ASSERT_EQ(file.open("rb"), 0);
  EXPECT_EQ(file.error(), 0);
  file.close();

  removeTempFile(path);
}

// Test FileIo setPath
TEST_F(FileIoTest_619, SetPath_619) {
  std::string path1 = tempDir_ + "/test_fileio_setpath1_619.bin";
  std::string path2 = tempDir_ + "/test_fileio_setpath2_619.bin";

  Exiv2::FileIo file(path1);
  EXPECT_EQ(file.path(), path1);

  file.setPath(path2);
  EXPECT_EQ(file.path(), path2);
}

// Test reading zero bytes from FileIo
TEST_F(FileIoTest_619, ReadZeroBytes_619) {
  std::string content = "some content";
  std::string path = createTempFile("test_fileio_readzero_619.bin", content);

  Exiv2::FileIo file(path);
  ASSERT_EQ(file.open("rb"), 0);

  Exiv2::DataBuf buf = file.read(0);
  EXPECT_EQ(buf.size(), 0u);

  file.close();
  removeTempFile(path);
}
