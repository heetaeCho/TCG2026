#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>

// Declaration of the function under test
bool Truncate(const std::string& path, size_t size, std::string* err);

class TruncateTest_159 : public ::testing::Test {
 protected:
  void SetUp() override {
    test_file_ = "truncate_test_file_159.tmp";
    // Clean up any leftover file
    std::remove(test_file_.c_str());
  }

  void TearDown() override {
    std::remove(test_file_.c_str());
  }

  void CreateFileWithContent(const std::string& content) {
    std::ofstream ofs(test_file_, std::ios::binary);
    ofs << content;
    ofs.close();
  }

  size_t GetFileSize(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) == 0)
      return static_cast<size_t>(st.st_size);
    return static_cast<size_t>(-1);
  }

  std::string ReadFileContent(const std::string& path) {
    std::ifstream ifs(path, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(ifs)),
                       std::istreambuf_iterator<char>());
  }

  std::string test_file_;
};

TEST_F(TruncateTest_159, TruncateExistingFileToSmallerSize_159) {
  CreateFileWithContent("Hello, World!");
  std::string err;
  bool result = Truncate(test_file_, 5, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(5u, GetFileSize(test_file_));
  EXPECT_EQ("Hello", ReadFileContent(test_file_));
}

TEST_F(TruncateTest_159, TruncateExistingFileToZero_159) {
  CreateFileWithContent("Some content here");
  std::string err;
  bool result = Truncate(test_file_, 0, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(0u, GetFileSize(test_file_));
}

TEST_F(TruncateTest_159, TruncateExistingFileToSameSize_159) {
  std::string content = "Exact size";
  CreateFileWithContent(content);
  size_t original_size = content.size();
  std::string err;
  bool result = Truncate(test_file_, original_size, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(original_size, GetFileSize(test_file_));
  EXPECT_EQ(content, ReadFileContent(test_file_));
}

TEST_F(TruncateTest_159, TruncateExistingFileToLargerSize_159) {
  std::string content = "Short";
  CreateFileWithContent(content);
  std::string err;
  size_t new_size = 100;
  bool result = Truncate(test_file_, new_size, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(new_size, GetFileSize(test_file_));
  // The first bytes should still be the original content
  std::string read_content = ReadFileContent(test_file_);
  EXPECT_EQ(new_size, read_content.size());
  EXPECT_EQ(content, read_content.substr(0, content.size()));
}

TEST_F(TruncateTest_159, TruncateNonExistentFileCreatesFile_159) {
  // On some platforms, truncate on a non-existent file may fail.
  // On Windows with _sopen and _O_CREAT, it creates the file.
  std::string non_existent = "non_existent_truncate_test_159.tmp";
  std::remove(non_existent.c_str());
  std::string err;
  bool result = Truncate(non_existent, 10, &err);
#ifdef _WIN32
  // On Windows, _sopen with _O_CREAT should create the file
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(10u, GetFileSize(non_existent));
  std::remove(non_existent.c_str());
#else
  // On POSIX, truncate() on a non-existent file typically fails
  if (!result) {
    EXPECT_FALSE(err.empty());
  }
  std::remove(non_existent.c_str());
#endif
}

TEST_F(TruncateTest_159, TruncateInvalidPathReturnsError_159) {
  // Use a path that should not be writable/creatable
  std::string invalid_path = "/nonexistent_dir_159/subdir/file.tmp";
  std::string err;
  bool result = Truncate(invalid_path, 0, &err);
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

TEST_F(TruncateTest_159, TruncateEmptyFileToZero_159) {
  CreateFileWithContent("");
  std::string err;
  bool result = Truncate(test_file_, 0, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(0u, GetFileSize(test_file_));
}

TEST_F(TruncateTest_159, TruncatePreservesContentBeforeTruncationPoint_159) {
  std::string content = "ABCDEFGHIJKLMNOP";
  CreateFileWithContent(content);
  std::string err;
  size_t truncate_point = 8;
  bool result = Truncate(test_file_, truncate_point, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  std::string read_content = ReadFileContent(test_file_);
  EXPECT_EQ("ABCDEFGH", read_content);
}

TEST_F(TruncateTest_159, TruncateToOneByteFile_159) {
  CreateFileWithContent("Multiple bytes of content");
  std::string err;
  bool result = Truncate(test_file_, 1, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(1u, GetFileSize(test_file_));
  EXPECT_EQ("M", ReadFileContent(test_file_));
}

TEST_F(TruncateTest_159, MultipleTruncateCallsOnSameFile_159) {
  CreateFileWithContent("Hello, this is a longer string for testing");
  std::string err;

  EXPECT_TRUE(Truncate(test_file_, 20, &err));
  EXPECT_EQ(20u, GetFileSize(test_file_));

  EXPECT_TRUE(Truncate(test_file_, 10, &err));
  EXPECT_EQ(10u, GetFileSize(test_file_));

  EXPECT_TRUE(Truncate(test_file_, 0, &err));
  EXPECT_EQ(0u, GetFileSize(test_file_));
}

TEST_F(TruncateTest_159, ErrorStringIsSetOnFailure_159) {
  std::string err;
  bool result = Truncate("/root/no_permission_159/impossible_file.tmp", 0, &err);
  if (!result) {
    EXPECT_FALSE(err.empty());
    // The error string should be a meaningful system error message
    EXPECT_GT(err.size(), 0u);
  }
}
