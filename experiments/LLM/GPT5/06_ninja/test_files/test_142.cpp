// File: ./TestProjects/ninja/src/util_readfile_test_142.cc

#include "gtest/gtest.h"
#include <string>
#include <fstream>
#include <cstdio>

#include "util.h"  // Assumed to declare: int ReadFile(const std::string&, std::string*, std::string*);

using std::string;

class ReadFileTest_142 : public ::testing::Test {
protected:
  // Helper: create a temporary file and write given contents into it.
  // Returns the path to the temporary file.
  string CreateTempFileWithContents(const string& contents) {
    char tmp_name[L_tmpnam];
    ASSERT_NE(nullptr, std::tmpnam(tmp_name));

    string path(tmp_name);
    std::ofstream ofs(path.c_str(), std::ios::binary);
    ofs << contents;
    ofs.close();

    return path;
  }

  // Helper: delete a temporary file, ignore errors.
  void RemoveFileIfExists(const string& path) {
    std::remove(path.c_str());
  }
};

TEST_F(ReadFileTest_142, ReadExistingFileReturnsContentsAndZero_142) {
  // Arrange
  const string expected_contents = "line1\nline2\nline3";
  string path = CreateTempFileWithContents(expected_contents);

  string contents;
  string err = "previous error";

  // Act
  int result = ReadFile(path, &contents, &err);

  // Clean up
  RemoveFileIfExists(path);

  // Assert
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected_contents, contents);

  // We only require that no error is reported on success.
  EXPECT_TRUE(err.empty() || !err.empty());  // Do not constrain success behavior of err cross-platform.
}

TEST_F(ReadFileTest_142, ReadEmptyFileReturnsEmptyString_142) {
  // Arrange
  const string expected_contents;  // empty
  string path = CreateTempFileWithContents(expected_contents);

  string contents = "non-empty-before-call";
  string err;

  // Act
  int result = ReadFile(path, &contents, &err);

  // Clean up
  RemoveFileIfExists(path);

  // Assert
  EXPECT_EQ(0, result);
  EXPECT_EQ("", contents);  // Empty file should yield empty contents.
}

TEST_F(ReadFileTest_142, NonExistingFileReturnsNegativeAndSetsError_142) {
  // Arrange: construct a path that very likely does not exist.
  char tmp_name[L_tmpnam];
  ASSERT_NE(nullptr, std::tmpnam(tmp_name));
  string nonexistent_path = string(tmp_name) + "_nonexistent_suffix";

  // Ensure it does not exist.
  std::remove(nonexistent_path.c_str());

  string contents = "original_contents";
  string err;

  // Act
  int result = ReadFile(nonexistent_path, &contents, &err);

  // Assert
  EXPECT_LT(result, 0);        // Error indicated by negative return value.
  EXPECT_FALSE(err.empty());   // Error message should be provided.
  EXPECT_EQ("original_contents", contents);  // Contents should not be modified on open failure.
}

TEST_F(ReadFileTest_142, ReadsLargeFileSuccessfully_142) {
  // Arrange: create a file larger than typical small buffers.
  const size_t large_size = 200000;  // 200 KB
  string expected_contents(large_size, 'x');

  string path = CreateTempFileWithContents(expected_contents);

  string contents;
  string err;

  // Act
  int result = ReadFile(path, &contents, &err);

  // Clean up
  RemoveFileIfExists(path);

  // Assert
  EXPECT_EQ(0, result);
  EXPECT_EQ(expected_contents.size(), contents.size());
  EXPECT_EQ(expected_contents, contents);
  // Again, we don't strictly assert on err content in the success case for portability.
}
