// File: db/c_env_get_test_directory_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/env.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"   // Needed to construct non-OK Status values
#include <cstring>
#include <string>

// Declaration under test (from db/c.cc)
extern "C" {
  struct leveldb_env_t {
    leveldb::Env* rep;
    bool is_default;
  };

  // Function under test
  char* leveldb_env_get_test_directory(leveldb_env_t* env);
}

// Mock Env that only cares about GetTestDirectory
class MockEnv : public leveldb::Env {
 public:
  MOCK_METHOD(leveldb::Status, GetTestDirectory,
              (std::string* path), (override));

  // Prevent accidental use of other Env methods by making them crash if called
  // (not required, but helps ensure black-box interaction is limited).
  // We rely solely on GetTestDirectory in these tests.
};

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;

class EnvGetTestDirectoryTest_284 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
  leveldb_env_t c_env_{&mock_env_, /*is_default=*/false};

  // Helper: safely free result buffer returned by the C API
  static void FreeIfNotNull(char* p) {
    if (p) std::free(p);
  }
};

// [Normal] Returns allocated C-string with the directory on success.
TEST_F(EnvGetTestDirectoryTest_284, ReturnsPathOnSuccess_284) {
  const std::string kPath = "/tmp/leveldb-test-dir";
  EXPECT_CALL(mock_env_, GetTestDirectory(_))
      .WillOnce(DoAll(SetArgPointee<0>(kPath), Return(leveldb::Status::OK())));

  char* out = leveldb_env_get_test_directory(&c_env_);
  ASSERT_NE(out, nullptr);

  // Content matches
  EXPECT_STREQ(out, kPath.c_str());
  // Null-terminated
  EXPECT_EQ(out[kPath.size()], '\0');

  FreeIfNotNull(out);
}

// [Exceptional] Returns nullptr when Env::GetTestDirectory reports failure.
TEST_F(EnvGetTestDirectoryTest_284, ReturnsNullOnFailure_284) {
  // Create a non-OK status (e.g., IOError)
  leveldb::Status err = leveldb::Status::IOError(leveldb::Slice("boom"));
  ASSERT_FALSE(err.ok());

  EXPECT_CALL(mock_env_, GetTestDirectory(_))
      .WillOnce(Return(err));

  char* out = leveldb_env_get_test_directory(&c_env_);
  EXPECT_EQ(out, nullptr);
}

// [Boundary] Handles empty path (allocates a 1-byte string: "\0").
TEST_F(EnvGetTestDirectoryTest_284, EmptyPathHandled_284) {
  const std::string kEmpty = "";
  EXPECT_CALL(mock_env_, GetTestDirectory(_))
      .WillOnce(DoAll(SetArgPointee<0>(kEmpty), Return(leveldb::Status::OK())));

  char* out = leveldb_env_get_test_directory(&c_env_);
  ASSERT_NE(out, nullptr);

  // Should be an empty C-string
  EXPECT_STREQ(out, "");
  EXPECT_EQ(std::strlen(out), 0u);
  // Explicitly check the first (and only) byte is '\0'
  EXPECT_EQ(out[0], '\0');

  FreeIfNotNull(out);
}

// [Boundary] Ensures exact copy and terminating null for non-trivial strings.
TEST_F(EnvGetTestDirectoryTest_284, CopiesExactlyAndNullTerminates_284) {
  const std::string kPath = "a/relatively/longer/test/directory/path/with123";
  EXPECT_CALL(mock_env_, GetTestDirectory(_))
      .WillOnce(DoAll(SetArgPointee<0>(kPath), Return(leveldb::Status::OK())));

  char* out = leveldb_env_get_test_directory(&c_env_);
  ASSERT_NE(out, nullptr);

  // Exact content match
  EXPECT_EQ(std::string(out), kPath);
  // Ensure the byte immediately after content is '\0'
  EXPECT_EQ(out[kPath.size()], '\0');
  // And strlen equals original length
  EXPECT_EQ(std::strlen(out), kPath.size());

  FreeIfNotNull(out);
}
