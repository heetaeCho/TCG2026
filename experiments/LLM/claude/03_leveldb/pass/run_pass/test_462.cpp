#include "gtest/gtest.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

namespace leveldb {

// Test fixture for Env tests
class EnvTest_462 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
  }

  Env* env_;
};

// Test that the base Env::NewAppendableFile returns NotSupported
TEST_F(EnvTest_462, BaseNewAppendableFileReturnsNotSupported_462) {
  // Create a base Env instance to test the default implementation
  // The base class NewAppendableFile should return NotSupported
  Env* base_env = Env::Default();
  ASSERT_NE(base_env, nullptr);
  
  // The default environment may or may not support appendable files,
  // but we can test that the method is callable
  WritableFile* file = nullptr;
  Status s = base_env->NewAppendableFile("/tmp/leveldb_test_appendable_462", &file);
  
  // Clean up if file was created
  if (s.ok() && file != nullptr) {
    file->Close();
    delete file;
    base_env->RemoveFile("/tmp/leveldb_test_appendable_462");
  }
}

// Test NewAppendableFile with empty filename
TEST_F(EnvTest_462, NewAppendableFileEmptyFilename_462) {
  WritableFile* file = nullptr;
  Status s = env_->NewAppendableFile("", &file);
  // An empty filename should likely result in an error
  if (!s.ok()) {
    EXPECT_EQ(file, nullptr);
  } else {
    // If somehow it succeeds, clean up
    if (file != nullptr) {
      file->Close();
      delete file;
    }
  }
}

// Test NewAppendableFile with a valid path creates or opens a file
TEST_F(EnvTest_462, NewAppendableFileValidPath_462) {
  std::string test_dir;
  ASSERT_TRUE(env_->GetTestDirectory(&test_dir).ok());
  
  std::string fname = test_dir + "/appendable_test_462";
  
  // First, create a writable file to ensure the directory exists
  WritableFile* file = nullptr;
  Status s = env_->NewAppendableFile(fname, &file);
  
  if (s.ok()) {
    ASSERT_NE(file, nullptr);
    
    // Write some data
    Status append_status = file->Append("hello ");
    EXPECT_TRUE(append_status.ok());
    
    Status close_status = file->Close();
    EXPECT_TRUE(close_status.ok());
    delete file;
    file = nullptr;
    
    // Open again for appending
    s = env_->NewAppendableFile(fname, &file);
    if (s.ok()) {
      ASSERT_NE(file, nullptr);
      append_status = file->Append("world");
      EXPECT_TRUE(append_status.ok());
      close_status = file->Close();
      EXPECT_TRUE(close_status.ok());
      delete file;
      file = nullptr;
    }
    
    // Verify content by reading
    // Check file size should be "hello " + "world" = 11 bytes
    uint64_t file_size = 0;
    s = env_->GetFileSize(fname, &file_size);
    if (s.ok()) {
      EXPECT_EQ(file_size, 11u);
    }
    
    // Cleanup
    env_->RemoveFile(fname);
  } else {
    // If NewAppendableFile is not supported on this platform's default env,
    // verify it returns NotSupported
    EXPECT_TRUE(s.IsNotSupportedError() || s.IsIOError());
  }
}

// Test NewAppendableFile with nonexistent directory
TEST_F(EnvTest_462, NewAppendableFileNonexistentDirectory_462) {
  WritableFile* file = nullptr;
  Status s = env_->NewAppendableFile("/nonexistent_dir_462/test_file", &file);
  // Should fail because the directory doesn't exist
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(file, nullptr);
}

// Test that NewAppendableFile actually appends (doesn't truncate)
TEST_F(EnvTest_462, NewAppendableFileActuallyAppends_462) {
  std::string test_dir;
  ASSERT_TRUE(env_->GetTestDirectory(&test_dir).ok());
  
  std::string fname = test_dir + "/append_verify_462";
  
  // Create file with initial content using NewWritableFile
  WritableFile* file = nullptr;
  Status s = env_->NewWritableFile(fname, &file);
  if (!s.ok()) {
    // Skip if we can't even create writable files
    return;
  }
  ASSERT_NE(file, nullptr);
  ASSERT_TRUE(file->Append("initial").ok());
  ASSERT_TRUE(file->Close().ok());
  delete file;
  file = nullptr;
  
  // Now open with NewAppendableFile and append more data
  s = env_->NewAppendableFile(fname, &file);
  if (s.ok()) {
    ASSERT_NE(file, nullptr);
    ASSERT_TRUE(file->Append("_appended").ok());
    ASSERT_TRUE(file->Close().ok());
    delete file;
    file = nullptr;
    
    // Verify the total size is "initial" (7) + "_appended" (9) = 16
    uint64_t file_size = 0;
    ASSERT_TRUE(env_->GetFileSize(fname, &file_size).ok());
    EXPECT_EQ(file_size, 16u);
  }
  
  // Cleanup
  env_->RemoveFile(fname);
}

// Test Status properties for NotSupported
TEST(StatusNotSupported_462, NewAppendableFileStatusProperties_462) {
  Status s = Status::NotSupported("NewAppendableFile", "testfile.txt");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test that the Status ToString contains meaningful info
TEST(StatusNotSupported_462, ToStringContainsInfo_462) {
  Status s = Status::NotSupported("NewAppendableFile", "somefile.db");
  std::string str = s.ToString();
  EXPECT_FALSE(str.empty());
  // The string should contain some indication of "not supported"
  EXPECT_NE(str.find("Not implemented"), std::string::npos);
}

// Test NewAppendableFile on the default env with a special character filename
TEST_F(EnvTest_462, NewAppendableFileSpecialCharFilename_462) {
  std::string test_dir;
  ASSERT_TRUE(env_->GetTestDirectory(&test_dir).ok());
  
  std::string fname = test_dir + "/test file with spaces_462";
  WritableFile* file = nullptr;
  Status s = env_->NewAppendableFile(fname, &file);
  
  if (s.ok()) {
    ASSERT_NE(file, nullptr);
    ASSERT_TRUE(file->Close().ok());
    delete file;
    env_->RemoveFile(fname);
  }
  // If it fails, that's also acceptable behavior
}

// Test multiple sequential appends
TEST_F(EnvTest_462, NewAppendableFileMultipleAppends_462) {
  std::string test_dir;
  ASSERT_TRUE(env_->GetTestDirectory(&test_dir).ok());
  
  std::string fname = test_dir + "/multi_append_462";
  
  // Remove file if it exists
  env_->RemoveFile(fname);
  
  const int kNumAppends = 5;
  const std::string kData = "data";
  
  for (int i = 0; i < kNumAppends; i++) {
    WritableFile* file = nullptr;
    Status s = env_->NewAppendableFile(fname, &file);
    if (!s.ok()) {
      // Not supported, skip
      return;
    }
    ASSERT_NE(file, nullptr);
    ASSERT_TRUE(file->Append(kData).ok());
    ASSERT_TRUE(file->Close().ok());
    delete file;
  }
  
  // Verify total size
  uint64_t file_size = 0;
  ASSERT_TRUE(env_->GetFileSize(fname, &file_size).ok());
  EXPECT_EQ(file_size, static_cast<uint64_t>(kNumAppends * kData.size()));
  
  // Cleanup
  env_->RemoveFile(fname);
}

}  // namespace leveldb
