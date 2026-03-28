// TEST_ID 565
// Unit tests for Exiv2::FileIo::getb()
// File: basicio_fileio_getb_test_565.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

namespace {

class FileIoGetbTest_565 : public ::testing::Test {
 protected:
  static std::string MakeTempPath_565() {
    // Use tmpnam for portability in constrained CI environments.
    // The returned path is immediately used for creation by the test.
    char buf[L_tmpnam];
#if defined(_MSC_VER)
    ASSERT_NE(tmpnam_s(buf), 0) << "tmpnam_s failed";
#else
    ASSERT_NE(std::tmpnam(buf), nullptr) << "tmpnam failed";
#endif
    return std::string(buf);
  }

  static void WriteBinaryFile_565(const std::string& path, const std::vector<unsigned char>& bytes) {
    std::ofstream os(path, std::ios::binary);
    ASSERT_TRUE(os.is_open()) << "Failed to open temp file for writing: " << path;
    if (!bytes.empty()) {
      os.write(reinterpret_cast<const char*>(bytes.data()),
               static_cast<std::streamsize>(bytes.size()));
    }
    ASSERT_TRUE(os.good()) << "Failed writing to temp file: " << path;
    os.close();
  }

  static void RemoveFileNoThrow_565(const std::string& path) {
    (void)std::remove(path.c_str());
  }
};

TEST_F(FileIoGetbTest_565, ReadsFirstByte_565) {
  const std::string path = MakeTempPath_565();
  const std::vector<unsigned char> bytes = {0x41, 0x42, 0x43};  // 'A', 'B', 'C'
  WriteBinaryFile_565(path, bytes);

  Exiv2::FileIo io(path);
  ASSERT_EQ(0, io.open()) << "open() should succeed for an existing file";

  const int b = io.getb();
  EXPECT_EQ(0x41, b);

  EXPECT_EQ(0, io.close());
  RemoveFileNoThrow_565(path);
}

TEST_F(FileIoGetbTest_565, ReadsSequentialBytesInOrder_565) {
  const std::string path = MakeTempPath_565();
  const std::vector<unsigned char> bytes = {0x00, 0x7F, 0x80, 0xFF};
  WriteBinaryFile_565(path, bytes);

  Exiv2::FileIo io(path);
  ASSERT_EQ(0, io.open()) << "open() should succeed for an existing file";

  for (size_t i = 0; i < bytes.size(); ++i) {
    const int b = io.getb();
    EXPECT_EQ(static_cast<int>(bytes[i]), b) << "Mismatch at index " << i;
  }

  EXPECT_EQ(0, io.close());
  RemoveFileNoThrow_565(path);
}

TEST_F(FileIoGetbTest_565, ReturnsEOFAtEndOfFile_565) {
  const std::string path = MakeTempPath_565();
  const std::vector<unsigned char> bytes = {0x10, 0x20};
  WriteBinaryFile_565(path, bytes);

  Exiv2::FileIo io(path);
  ASSERT_EQ(0, io.open()) << "open() should succeed for an existing file";

  EXPECT_EQ(0x10, io.getb());
  EXPECT_EQ(0x20, io.getb());

  // Boundary: reading past end should yield EOF (observable contract of getc/EOF).
  EXPECT_EQ(EOF, io.getb());
  // Repeated EOF reads should remain EOF.
  EXPECT_EQ(EOF, io.getb());

  EXPECT_EQ(0, io.close());
  RemoveFileNoThrow_565(path);
}

TEST_F(FileIoGetbTest_565, EmptyFileReturnsEOF_565) {
  const std::string path = MakeTempPath_565();
  const std::vector<unsigned char> bytes = {};  // empty
  WriteBinaryFile_565(path, bytes);

  Exiv2::FileIo io(path);
  ASSERT_EQ(0, io.open()) << "open() should succeed for an existing (empty) file";

  EXPECT_EQ(EOF, io.getb());
  EXPECT_EQ(EOF, io.getb());  // still EOF

  EXPECT_EQ(0, io.close());
  RemoveFileNoThrow_565(path);
}

}  // namespace