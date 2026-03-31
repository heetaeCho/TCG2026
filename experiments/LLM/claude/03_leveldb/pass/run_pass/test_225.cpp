#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <cstring>
#include <string>

// Forward declarations for C API structures and function
extern "C" {

struct leveldb_t {
  leveldb::DB* rep;
};

struct leveldb_readoptions_t {
  leveldb::ReadOptions rep;
};

char* leveldb_get(leveldb_t* db, const leveldb_readoptions_t* options,
                  const char* key, size_t keylen, size_t* vallen,
                  char** errptr);

}

// We need to redeclare these since the C file has them as static helpers
// But since they are internal, we re-declare the function under test.
// The actual CopyString and SaveError are internal to c.cc, so we need
// to link against the actual c.cc object.

using namespace leveldb;

// Mock DB class to control Get behavior
class MockDB : public DB {
 public:
  MOCK_METHOD(Status, Put, (const WriteOptions& options, const Slice& key, const Slice& value), (override));
  MOCK_METHOD(Status, Delete, (const WriteOptions& options, const Slice& key), (override));
  MOCK_METHOD(Status, Write, (const WriteOptions& options, WriteBatch* updates), (override));
  MOCK_METHOD(Status, Get, (const ReadOptions& options, const Slice& key, std::string* value), (override));
  MOCK_METHOD(Iterator*, NewIterator, (const ReadOptions& options), (override));
  MOCK_METHOD(const Snapshot*, GetSnapshot, (), (override));
  MOCK_METHOD(void, ReleaseSnapshot, (const Snapshot* snapshot), (override));
  MOCK_METHOD(bool, GetProperty, (const Slice& property, std::string* value), (override));
  MOCK_METHOD(void, GetApproximateSizes, (const Range* range, int n, uint64_t* sizes), (override));
  MOCK_METHOD(void, CompactRange, (const Slice* begin, const Slice* end), (override));
};

class LeveldbGetTest_225 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new MockDB();
    db_wrapper_.rep = mock_db_;
    read_options_ = leveldb_readoptions_t();
    errptr_ = nullptr;
    vallen_ = 0;
  }

  void TearDown() override {
    delete mock_db_;
    if (errptr_) {
      free(errptr_);
      errptr_ = nullptr;
    }
  }

  MockDB* mock_db_;
  leveldb_t db_wrapper_;
  leveldb_readoptions_t read_options_;
  char* errptr_;
  size_t vallen_;
};

// Test: Successful get returns correct value and length
TEST_F(LeveldbGetTest_225, GetExistingKeyReturnsValue_225) {
  std::string expected_value = "hello_world";
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<2>(expected_value),
          ::testing::Return(Status::OK())));

  const char* key = "mykey";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(vallen_, expected_value.size());
  EXPECT_EQ(std::string(result, vallen_), expected_value);
  EXPECT_EQ(errptr_, nullptr);
  free(result);
}

// Test: Key not found returns nullptr, vallen=0, no error
TEST_F(LeveldbGetTest_225, GetNonExistingKeyReturnsNull_225) {
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("key not found")));

  const char* key = "missing_key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(vallen_, 0u);
  EXPECT_EQ(errptr_, nullptr);
}

// Test: IO Error returns nullptr, vallen=0, and sets error
TEST_F(LeveldbGetTest_225, GetIOErrorSetsError_225) {
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("disk failure")));

  const char* key = "some_key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(vallen_, 0u);
  ASSERT_NE(errptr_, nullptr);
  EXPECT_TRUE(std::string(errptr_).find("disk failure") != std::string::npos ||
              std::string(errptr_).find("IO error") != std::string::npos);
}

// Test: Corruption error returns nullptr, vallen=0, and sets error
TEST_F(LeveldbGetTest_225, GetCorruptionErrorSetsError_225) {
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::Corruption("bad data")));

  const char* key = "corrupt_key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(vallen_, 0u);
  ASSERT_NE(errptr_, nullptr);
}

// Test: Empty value returned successfully
TEST_F(LeveldbGetTest_225, GetEmptyValueReturnsEmptyResult_225) {
  std::string expected_value = "";
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<2>(expected_value),
          ::testing::Return(Status::OK())));

  const char* key = "empty_val_key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(vallen_, 0u);
  EXPECT_EQ(errptr_, nullptr);
  free(result);
}

// Test: Binary key with embedded null bytes
TEST_F(LeveldbGetTest_225, GetWithBinaryKeyContainingNulls_225) {
  std::string expected_value = "binary_result";
  const char key[] = "ke\0y";
  size_t keylen = 4;  // includes the embedded null

  EXPECT_CALL(*mock_db_, Get(::testing::_, Slice(key, keylen), ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<2>(expected_value),
          ::testing::Return(Status::OK())));

  char* result = leveldb_get(&db_wrapper_, &read_options_, key, keylen,
                             &vallen_, &errptr_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(vallen_, expected_value.size());
  EXPECT_EQ(std::string(result, vallen_), expected_value);
  EXPECT_EQ(errptr_, nullptr);
  free(result);
}

// Test: Binary value with embedded null bytes
TEST_F(LeveldbGetTest_225, GetReturnsBinaryValueWithNulls_225) {
  std::string expected_value("val\0ue", 6);
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<2>(expected_value),
          ::testing::Return(Status::OK())));

  const char* key = "binkey";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(vallen_, 6u);
  EXPECT_EQ(std::string(result, vallen_), expected_value);
  EXPECT_EQ(errptr_, nullptr);
  free(result);
}

// Test: Large value
TEST_F(LeveldbGetTest_225, GetLargeValueReturnsCorrectly_225) {
  std::string expected_value(100000, 'x');
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<2>(expected_value),
          ::testing::Return(Status::OK())));

  const char* key = "large_key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(vallen_, 100000u);
  EXPECT_EQ(std::string(result, vallen_), expected_value);
  EXPECT_EQ(errptr_, nullptr);
  free(result);
}

// Test: InvalidArgument error sets errptr
TEST_F(LeveldbGetTest_225, GetInvalidArgumentSetsError_225) {
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::InvalidArgument("bad arg")));

  const char* key = "key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(vallen_, 0u);
  ASSERT_NE(errptr_, nullptr);
}

// Test: Zero-length key
TEST_F(LeveldbGetTest_225, GetWithZeroLengthKey_225) {
  std::string expected_value = "value_for_empty_key";
  EXPECT_CALL(*mock_db_, Get(::testing::_, Slice("", 0), ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<2>(expected_value),
          ::testing::Return(Status::OK())));

  char* result = leveldb_get(&db_wrapper_, &read_options_, "", 0,
                             &vallen_, &errptr_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(vallen_, expected_value.size());
  EXPECT_EQ(std::string(result, vallen_), expected_value);
  EXPECT_EQ(errptr_, nullptr);
  free(result);
}

// Test: errptr is not modified on NotFound
TEST_F(LeveldbGetTest_225, GetNotFoundDoesNotSetErrptr_225) {
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("nope")));

  // Pre-set errptr to nullptr
  errptr_ = nullptr;
  const char* key = "nf_key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(vallen_, 0u);
  EXPECT_EQ(errptr_, nullptr);  // Should NOT be set for NotFound
}

// Test: NotSupported error sets errptr
TEST_F(LeveldbGetTest_225, GetNotSupportedSetsError_225) {
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::NotSupported("not supported")));

  const char* key = "ns_key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(vallen_, 0u);
  ASSERT_NE(errptr_, nullptr);
}

// Test: Result is a copy, not pointing to internal storage
TEST_F(LeveldbGetTest_225, GetResultIsIndependentCopy_225) {
  std::string expected_value = "copy_test";
  EXPECT_CALL(*mock_db_, Get(::testing::_, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<2>(expected_value),
          ::testing::Return(Status::OK())));

  const char* key = "copy_key";
  char* result = leveldb_get(&db_wrapper_, &read_options_, key, strlen(key),
                             &vallen_, &errptr_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(vallen_, expected_value.size());
  // Verify the content matches
  EXPECT_EQ(std::string(result, vallen_), expected_value);
  // Modifying result should not crash (it's a separate allocation)
  result[0] = 'Z';
  EXPECT_NE(result[0], expected_value[0]);
  free(result);
}
