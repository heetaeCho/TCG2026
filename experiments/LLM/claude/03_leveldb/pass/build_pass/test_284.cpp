#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/c.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <cstdlib>
#include <cstring>
#include <string>

// We need access to the C API
extern "C" {
// These are declared in leveldb/c.h
typedef struct leveldb_env_t leveldb_env_t;
leveldb_env_t* leveldb_create_default_env();
void leveldb_env_destroy(leveldb_env_t* env);
char* leveldb_env_get_test_directory(leveldb_env_t* env);
void leveldb_free(void* ptr);
}

class LevelDBCEnvGetTestDirectory_284 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = leveldb_create_default_env();
    ASSERT_NE(env_, nullptr);
  }

  void TearDown() override {
    if (env_) {
      leveldb_env_destroy(env_);
    }
  }

  leveldb_env_t* env_ = nullptr;
};

// Test that GetTestDirectory returns a non-null string for the default env
TEST_F(LevelDBCEnvGetTestDirectory_284, ReturnsNonNullForDefaultEnv_284) {
  char* dir = leveldb_env_get_test_directory(env_);
  ASSERT_NE(dir, nullptr);
  // The returned string should have non-zero length
  EXPECT_GT(std::strlen(dir), 0u);
  std::free(dir);
}

// Test that the returned string is a valid null-terminated C string
TEST_F(LevelDBCEnvGetTestDirectory_284, ReturnsNullTerminatedString_284) {
  char* dir = leveldb_env_get_test_directory(env_);
  ASSERT_NE(dir, nullptr);
  // strlen should work without issues on a properly null-terminated string
  size_t len = std::strlen(dir);
  EXPECT_GT(len, 0u);
  EXPECT_EQ(dir[len], '\0');
  std::free(dir);
}

// Test that calling GetTestDirectory multiple times returns consistent results
TEST_F(LevelDBCEnvGetTestDirectory_284, ConsistentResultsOnMultipleCalls_284) {
  char* dir1 = leveldb_env_get_test_directory(env_);
  char* dir2 = leveldb_env_get_test_directory(env_);
  ASSERT_NE(dir1, nullptr);
  ASSERT_NE(dir2, nullptr);
  // Both calls should return the same directory path
  EXPECT_STREQ(dir1, dir2);
  // But they should be different allocations
  EXPECT_NE(dir1, dir2);
  std::free(dir1);
  std::free(dir2);
}

// Test that the returned directory path contains a reasonable path string
TEST_F(LevelDBCEnvGetTestDirectory_284, ReturnsReasonablePath_284) {
  char* dir = leveldb_env_get_test_directory(env_);
  ASSERT_NE(dir, nullptr);
  std::string path(dir);
  // The test directory should contain "test" somewhere or at least be a path
  // (this is a soft check - the default env typically returns something like /tmp/leveldbtest-XXXX)
  EXPECT_FALSE(path.empty());
  std::free(dir);
}

// Test with a mock env that returns failure from GetTestDirectory
namespace {

class FailingEnv : public leveldb::Env {
 public:
  leveldb::Status NewSequentialFile(const std::string& fname,
                                     leveldb::SequentialFile** result) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status NewRandomAccessFile(const std::string& fname,
                                       leveldb::RandomAccessFile** result) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status NewWritableFile(const std::string& fname,
                                   leveldb::WritableFile** result) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status NewAppendableFile(const std::string& fname,
                                     leveldb::WritableFile** result) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  bool FileExists(const std::string& fname) override { return false; }
  leveldb::Status GetChildren(const std::string& dir,
                               std::vector<std::string>* result) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status RemoveFile(const std::string& fname) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status CreateDir(const std::string& dirname) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status RemoveDir(const std::string& dirname) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status GetFileSize(const std::string& fname,
                               uint64_t* file_size) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status RenameFile(const std::string& src,
                              const std::string& target) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status LockFile(const std::string& fname,
                            leveldb::FileLock** lock) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  leveldb::Status UnlockFile(leveldb::FileLock* lock) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  void Schedule(void (*function)(void*), void* arg) override {}
  void StartThread(void (*function)(void*), void* arg) override {}
  leveldb::Status GetTestDirectory(std::string* path) override {
    return leveldb::Status::IOError("test failure");
  }
  leveldb::Status NewLogger(const std::string& fname,
                             leveldb::Logger** result) override {
    return leveldb::Status::NotSupported("not implemented");
  }
  uint64_t NowMicros() override { return 0; }
  void SleepForMicroseconds(int micros) override {}
};

// We need to access the internal structure to create a custom env wrapper.
// Since leveldb_env_t is defined in c.cc, we replicate it here for testing.
struct leveldb_env_t_test {
  leveldb::Env* rep;
  bool is_default;
};

}  // namespace

TEST(LevelDBCEnvGetTestDirectoryFailure_284, ReturnsNullOnFailure_284) {
  FailingEnv failing_env;
  // Create a leveldb_env_t manually with the failing env
  // Since leveldb_env_t has public members rep and is_default, we can
  // cast through the equivalent struct
  leveldb_env_t_test env_wrapper;
  env_wrapper.rep = &failing_env;
  env_wrapper.is_default = false;

  // Cast to leveldb_env_t* (the structs should be layout-compatible)
  leveldb_env_t* env = reinterpret_cast<leveldb_env_t*>(&env_wrapper);
  char* dir = leveldb_env_get_test_directory(env);
  EXPECT_EQ(dir, nullptr);
}

// Test with a mock env that returns success with a specific path
namespace {

class SuccessEnv : public FailingEnv {
 public:
  explicit SuccessEnv(const std::string& test_dir) : test_dir_(test_dir) {}
  leveldb::Status GetTestDirectory(std::string* path) override {
    *path = test_dir_;
    return leveldb::Status::OK();
  }

 private:
  std::string test_dir_;
};

}  // namespace

TEST(LevelDBCEnvGetTestDirectoryCustom_284, ReturnsExpectedPath_284) {
  SuccessEnv success_env("/custom/test/path");
  leveldb_env_t_test env_wrapper;
  env_wrapper.rep = &success_env;
  env_wrapper.is_default = false;

  leveldb_env_t* env = reinterpret_cast<leveldb_env_t*>(&env_wrapper);
  char* dir = leveldb_env_get_test_directory(env);
  ASSERT_NE(dir, nullptr);
  EXPECT_STREQ(dir, "/custom/test/path");
  std::free(dir);
}

TEST(LevelDBCEnvGetTestDirectoryCustom_284, ReturnsEmptyPath_284) {
  // Edge case: env returns OK but empty string
  SuccessEnv success_env("");
  leveldb_env_t_test env_wrapper;
  env_wrapper.rep = &success_env;
  env_wrapper.is_default = false;

  leveldb_env_t* env = reinterpret_cast<leveldb_env_t*>(&env_wrapper);
  char* dir = leveldb_env_get_test_directory(env);
  ASSERT_NE(dir, nullptr);
  EXPECT_STREQ(dir, "");
  EXPECT_EQ(std::strlen(dir), 0u);
  std::free(dir);
}

TEST(LevelDBCEnvGetTestDirectoryCustom_284, PathWithSpecialCharacters_284) {
  SuccessEnv success_env("/path/with spaces/and-special_chars.123");
  leveldb_env_t_test env_wrapper;
  env_wrapper.rep = &success_env;
  env_wrapper.is_default = false;

  leveldb_env_t* env = reinterpret_cast<leveldb_env_t*>(&env_wrapper);
  char* dir = leveldb_env_get_test_directory(env);
  ASSERT_NE(dir, nullptr);
  EXPECT_STREQ(dir, "/path/with spaces/and-special_chars.123");
  std::free(dir);
}

TEST(LevelDBCEnvGetTestDirectoryCustom_284, LongPath_284) {
  // Test with a very long path
  std::string long_path(4096, 'a');
  SuccessEnv success_env(long_path);
  leveldb_env_t_test env_wrapper;
  env_wrapper.rep = &success_env;
  env_wrapper.is_default = false;

  leveldb_env_t* env = reinterpret_cast<leveldb_env_t*>(&env_wrapper);
  char* dir = leveldb_env_get_test_directory(env);
  ASSERT_NE(dir, nullptr);
  EXPECT_EQ(std::strlen(dir), 4096u);
  EXPECT_EQ(std::string(dir), long_path);
  std::free(dir);
}

TEST(LevelDBCEnvGetTestDirectoryCustom_284, PathWithNullByteInMiddle_284) {
  // std::string can contain null bytes; the memcpy should copy them
  std::string path_with_null("abc");
  path_with_null.push_back('\0');
  path_with_null.append("def");
  // The string has length 7: 'a','b','c','\0','d','e','f'
  
  SuccessEnv success_env(path_with_null);
  leveldb_env_t_test env_wrapper;
  env_wrapper.rep = &success_env;
  env_wrapper.is_default = false;

  leveldb_env_t* env = reinterpret_cast<leveldb_env_t*>(&env_wrapper);
  char* dir = leveldb_env_get_test_directory(env);
  ASSERT_NE(dir, nullptr);
  // strlen will stop at the first null byte
  EXPECT_EQ(std::strlen(dir), 3u);
  // But the full content should be copied (7 bytes + terminator)
  EXPECT_EQ(std::memcmp(dir, path_with_null.data(), path_with_null.size()), 0);
  EXPECT_EQ(dir[path_with_null.size()], '\0');
  std::free(dir);
}
