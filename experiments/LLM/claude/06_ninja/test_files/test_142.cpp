#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

// Declaration of the function under test
int ReadFile(const std::string& path, std::string* contents, std::string* err);

class ReadFileTest_142 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Clean up any leftover temp files
    cleanup_files_.clear();
  }

  void TearDown() override {
    for (const auto& f : cleanup_files_) {
      std::remove(f.c_str());
    }
  }

  std::string CreateTempFile(const std::string& name, const std::string& content) {
    std::string path = name;
    std::ofstream ofs(path, std::ios::binary);
    ofs << content;
    ofs.close();
    cleanup_files_.push_back(path);
    return path;
  }

  std::string CreateTempFileWithBytes(const std::string& name, const char* data, size_t len) {
    std::string path = name;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(data, len);
    ofs.close();
    cleanup_files_.push_back(path);
    return path;
  }

  std::vector<std::string> cleanup_files_;
};

// Test reading a non-existent file returns an error
TEST_F(ReadFileTest_142, NonExistentFileReturnsError_142) {
  std::string contents;
  std::string err;
  int result = ReadFile("non_existent_file_142.txt", &contents, &err);
  EXPECT_NE(0, result);
  EXPECT_FALSE(err.empty());
}

// Test reading an empty file succeeds and returns empty contents
TEST_F(ReadFileTest_142, EmptyFileReturnsEmptyContents_142) {
  std::string path = CreateTempFile("empty_file_142.txt", "");
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_TRUE(contents.empty());
  EXPECT_TRUE(err.empty());
}

// Test reading a small file returns correct contents
TEST_F(ReadFileTest_142, SmallFileReturnsCorrectContents_142) {
  std::string expected = "Hello, World!";
  std::string path = CreateTempFile("small_file_142.txt", expected);
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected, contents);
  EXPECT_TRUE(err.empty());
}

// Test reading a file with multiple lines
TEST_F(ReadFileTest_142, MultiLineFileReturnsCorrectContents_142) {
  std::string expected = "line1\nline2\nline3\n";
  std::string path = CreateTempFile("multiline_142.txt", expected);
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected, contents);
  EXPECT_TRUE(err.empty());
}

// Test reading a file with binary content (null bytes)
TEST_F(ReadFileTest_142, BinaryContentWithNullBytes_142) {
  const char data[] = "abc\0def\0ghi";
  size_t len = sizeof(data) - 1;  // exclude terminating null of string literal
  std::string path = CreateTempFileWithBytes("binary_file_142.bin", data, len);
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_EQ(len, contents.size());
  EXPECT_EQ(std::string(data, len), contents);
  EXPECT_TRUE(err.empty());
}

// Test reading a single byte file
TEST_F(ReadFileTest_142, SingleByteFile_142) {
  std::string expected = "X";
  std::string path = CreateTempFile("single_byte_142.txt", expected);
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected, contents);
  EXPECT_TRUE(err.empty());
}

// Test that error string is not empty when file doesn't exist
TEST_F(ReadFileTest_142, ErrorStringPopulatedOnMissingFile_142) {
  std::string contents;
  std::string err;
  ReadFile("definitely_does_not_exist_142.txt", &contents, &err);
  EXPECT_FALSE(err.empty());
}

// Test that the return value for non-existent file is negative
TEST_F(ReadFileTest_142, ReturnValueIsNegativeOnError_142) {
  std::string contents;
  std::string err;
  int result = ReadFile("no_such_file_142.txt", &contents, &err);
  EXPECT_LT(result, 0);
}

// Test reading a larger file (bigger than typical small buffers)
TEST_F(ReadFileTest_142, LargerFileReadsCorrectly_142) {
  // Create a file larger than a small buffer but smaller than 64KB
  std::string expected(50000, 'A');
  std::string path = CreateTempFile("large_file_142.txt", expected);
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected.size(), contents.size());
  EXPECT_EQ(expected, contents);
  EXPECT_TRUE(err.empty());
}

// Test reading a file larger than the internal buffer (64KB)
TEST_F(ReadFileTest_142, FileExceedingInternalBufferSize_142) {
  // Internal buffer is 64 << 10 = 65536 bytes; create file larger than that
  std::string expected(100000, 'B');
  for (size_t i = 0; i < expected.size(); ++i) {
    expected[i] = static_cast<char>('A' + (i % 26));
  }
  std::string path = CreateTempFile("very_large_file_142.txt", expected);
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected.size(), contents.size());
  EXPECT_EQ(expected, contents);
  EXPECT_TRUE(err.empty());
}

// Test reading file with special characters in content
TEST_F(ReadFileTest_142, SpecialCharactersInContent_142) {
  std::string expected = "\t\r\n\x01\x02\x03\xff\xfe";
  std::string path = CreateTempFileWithBytes("special_chars_142.bin", expected.data(), expected.size());
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected.size(), contents.size());
  EXPECT_EQ(expected, contents);
}

// Test reading the same file twice returns consistent results
TEST_F(ReadFileTest_142, ReadingTwiceGivesConsistentResults_142) {
  std::string expected = "consistent data";
  std::string path = CreateTempFile("consistent_142.txt", expected);

  std::string contents1, contents2;
  std::string err1, err2;
  int result1 = ReadFile(path, &contents1, &err1);
  int result2 = ReadFile(path, &contents2, &err2);

  EXPECT_EQ(0, result1);
  EXPECT_EQ(0, result2);
  EXPECT_EQ(contents1, contents2);
  EXPECT_EQ(expected, contents1);
}

// Test with empty path string
TEST_F(ReadFileTest_142, EmptyPathReturnsError_142) {
  std::string contents;
  std::string err;
  int result = ReadFile("", &contents, &err);
  EXPECT_NE(0, result);
  EXPECT_FALSE(err.empty());
}

// Test contents string is not cleared before appending (verifies pre-existing contents behavior)
// Actually, we should check that ReadFile replaces or appends. Based on implementation,
// it appears to append (no clear before read). Let's verify with a pre-filled contents string.
TEST_F(ReadFileTest_142, ContentsAreAppendedNotCleared_142) {
  std::string expected = "file data";
  std::string path = CreateTempFile("append_test_142.txt", expected);
  std::string contents = "pre-existing ";
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  // The implementation does contents->append(), so pre-existing data should remain
  EXPECT_EQ("pre-existing " + expected, contents);
}

// Test file exactly at internal buffer boundary (65536 bytes)
TEST_F(ReadFileTest_142, FileExactlyAtBufferBoundary_142) {
  size_t buf_size = 64 << 10;  // 65536
  std::string expected(buf_size, 'C');
  std::string path = CreateTempFile("boundary_142.txt", expected);
  std::string contents;
  std::string err;
  int result = ReadFile(path, &contents, &err);
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected.size(), contents.size());
  EXPECT_EQ(expected, contents);
}
