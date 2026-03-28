#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <cstring>
#include <string>

// Forward declarations matching the C API structures
extern "C" {

struct leveldb_t {
  leveldb::DB* rep;
};

struct leveldb_writeoptions_t {
  leveldb::WriteOptions rep;
};

void leveldb_put(leveldb_t* db, const leveldb_writeoptions_t* options,
                 const char* key, size_t keylen, const char* val,
                 size_t vallen, char** errptr);

}  // extern "C"

// From c.cc - we need the SaveError helper behavior:
// SaveError sets *errptr to nullptr on OK, or to a strdup'd error message on failure.

namespace {

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;

// Mock DB to intercept Put calls
class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(leveldb::Status, Put,
              (const leveldb::WriteOptions& options, const leveldb::Slice& key,
               const leveldb::Slice& value),
              (override));
  MOCK_METHOD(leveldb::Status, Delete,
              (const leveldb::WriteOptions& options, const leveldb::Slice& key),
              (override));
  MOCK_METHOD(leveldb::Status, Write,
              (const leveldb::WriteOptions& options,
               leveldb::WriteBatch* updates),
              (override));
  MOCK_METHOD(leveldb::Status, Get,
              (const leveldb::ReadOptions& options, const leveldb::Slice& key,
               std::string* value),
              (override));
  MOCK_METHOD(leveldb::Iterator*, NewIterator,
              (const leveldb::ReadOptions& options), (override));
  MOCK_METHOD(const leveldb::Snapshot*, GetSnapshot, (), (override));
  MOCK_METHOD(void, ReleaseSnapshot, (const leveldb::Snapshot* snapshot),
              (override));
  MOCK_METHOD(bool, GetProperty,
              (const leveldb::Slice& property, std::string* value), (override));
  MOCK_METHOD(void, GetApproximateSizes,
              (const leveldb::Range* range, int n, uint64_t* sizes),
              (override));
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice* begin, const leveldb::Slice* end),
              (override));
};

class LevelDBPutTest_222 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new MockDB();
    db_wrapper_.rep = mock_db_;
    write_options_ = new leveldb_writeoptions_t();
  }

  void TearDown() override {
    delete mock_db_;
    delete write_options_;
  }

  MockDB* mock_db_;
  leveldb_t db_wrapper_;
  leveldb_writeoptions_t* write_options_;
};

// Test that a successful Put does not set errptr
TEST_F(LevelDBPutTest_222, PutSuccess_NoError_222) {
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Put(_, _, _))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, "key", 3, "value", 5, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test that a failed Put sets errptr to a non-null error message
TEST_F(LevelDBPutTest_222, PutFailure_SetsError_222) {
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Put(_, _, _))
      .WillOnce(Return(leveldb::Status::IOError("disk full")));

  leveldb_put(&db_wrapper_, write_options_, "key", 3, "value", 5, &errptr);

  ASSERT_NE(errptr, nullptr);
  EXPECT_TRUE(std::string(errptr).find("disk full") != std::string::npos);
  free(errptr);
}

// Test that the correct key is passed to DB::Put
TEST_F(LevelDBPutTest_222, PutPassesCorrectKey_222) {
  char* errptr = nullptr;
  const char* key = "mykey";
  size_t keylen = 5;

  EXPECT_CALL(*mock_db_, Put(_, leveldb::Slice(key, keylen), _))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, key, keylen, "val", 3, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test that the correct value is passed to DB::Put
TEST_F(LevelDBPutTest_222, PutPassesCorrectValue_222) {
  char* errptr = nullptr;
  const char* val = "myvalue";
  size_t vallen = 7;

  EXPECT_CALL(*mock_db_, Put(_, _, leveldb::Slice(val, vallen)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, "k", 1, val, vallen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test with empty key and value
TEST_F(LevelDBPutTest_222, PutEmptyKeyAndValue_222) {
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Put(_, leveldb::Slice("", 0), leveldb::Slice("", 0)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, "", 0, "", 0, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test with empty key but non-empty value
TEST_F(LevelDBPutTest_222, PutEmptyKeyNonEmptyValue_222) {
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_,
              Put(_, leveldb::Slice("", 0), leveldb::Slice("value", 5)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, "", 0, "value", 5, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test with non-empty key but empty value
TEST_F(LevelDBPutTest_222, PutNonEmptyKeyEmptyValue_222) {
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_,
              Put(_, leveldb::Slice("key", 3), leveldb::Slice("", 0)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, "key", 3, "", 0, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test that a previous error string is freed/replaced on new error
TEST_F(LevelDBPutTest_222, PutOverwritesPreviousError_222) {
  char* errptr = strdup("previous error");

  EXPECT_CALL(*mock_db_, Put(_, _, _))
      .WillOnce(Return(leveldb::Status::IOError("new error")));

  leveldb_put(&db_wrapper_, write_options_, "key", 3, "val", 3, &errptr);

  ASSERT_NE(errptr, nullptr);
  EXPECT_TRUE(std::string(errptr).find("new error") != std::string::npos);
  free(errptr);
}

// Test that write options sync flag is properly passed through
TEST_F(LevelDBPutTest_222, PutWithSyncOption_222) {
  char* errptr = nullptr;
  write_options_->rep.sync = true;

  EXPECT_CALL(*mock_db_, Put(_, _, _))
      .WillOnce(Invoke([](const leveldb::WriteOptions& opt,
                           const leveldb::Slice& key,
                           const leveldb::Slice& val) -> leveldb::Status {
        EXPECT_TRUE(opt.sync);
        return leveldb::Status::OK();
      }));

  leveldb_put(&db_wrapper_, write_options_, "key", 3, "val", 3, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test with binary data containing null bytes in key and value
TEST_F(LevelDBPutTest_222, PutBinaryDataWithNullBytes_222) {
  char* errptr = nullptr;
  const char key[] = "ke\0y";
  size_t keylen = 4;
  const char val[] = "va\0l";
  size_t vallen = 4;

  EXPECT_CALL(*mock_db_,
              Put(_, leveldb::Slice(key, keylen), leveldb::Slice(val, vallen)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, key, keylen, val, vallen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test with large key and value
TEST_F(LevelDBPutTest_222, PutLargeKeyAndValue_222) {
  char* errptr = nullptr;
  std::string large_key(10000, 'K');
  std::string large_val(100000, 'V');

  EXPECT_CALL(*mock_db_,
              Put(_, leveldb::Slice(large_key.data(), large_key.size()),
                  leveldb::Slice(large_val.data(), large_val.size())))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, large_key.data(), large_key.size(),
              large_val.data(), large_val.size(), &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test NotFound error type
TEST_F(LevelDBPutTest_222, PutNotFoundError_222) {
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Put(_, _, _))
      .WillOnce(Return(leveldb::Status::NotFound("not found msg")));

  leveldb_put(&db_wrapper_, write_options_, "key", 3, "val", 3, &errptr);

  ASSERT_NE(errptr, nullptr);
  EXPECT_TRUE(std::string(errptr).find("not found") != std::string::npos ||
              std::string(errptr).find("Not found") != std::string::npos);
  free(errptr);
}

// Test Corruption error type
TEST_F(LevelDBPutTest_222, PutCorruptionError_222) {
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Put(_, _, _))
      .WillOnce(Return(leveldb::Status::Corruption("corruption msg")));

  leveldb_put(&db_wrapper_, write_options_, "key", 3, "val", 3, &errptr);

  ASSERT_NE(errptr, nullptr);
  EXPECT_TRUE(std::string(errptr).find("corruption") != std::string::npos ||
              std::string(errptr).find("Corruption") != std::string::npos);
  free(errptr);
}

// Test that errptr is cleared on success even if it had a previous value
TEST_F(LevelDBPutTest_222, PutClearsPreviousErrorOnSuccess_222) {
  char* errptr = strdup("old error");

  EXPECT_CALL(*mock_db_, Put(_, _, _))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&db_wrapper_, write_options_, "key", 3, "val", 3, &errptr);

  // On success, SaveError should free the old error and set to nullptr
  // (or just set to nullptr - depends on implementation)
  // Based on typical SaveError implementation, errptr should be nullptr on success
  // Note: The old string may have been freed
  EXPECT_EQ(errptr, nullptr);
}

}  // namespace
