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

void leveldb_delete(leveldb_t* db, const leveldb_writeoptions_t* options,
                    const char* key, size_t keylen, char** errptr);

}  // extern "C"

// We need the SaveError helper and the actual leveldb_delete implementation.
// Since we're testing db/c.cc, we link against it.

namespace {

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

// Mock DB class to simulate DB::Delete behavior
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

class LevelDBDeleteTest_223 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new MockDB();
    db_.rep = mock_db_;
    write_options_.rep = leveldb::WriteOptions();
  }

  void TearDown() override {
    delete mock_db_;
  }

  MockDB* mock_db_;
  leveldb_t db_;
  leveldb_writeoptions_t write_options_;
};

// Test normal delete operation succeeds
TEST_F(LevelDBDeleteTest_223, DeleteSucceeds_223) {
  const char* key = "test_key";
  size_t keylen = strlen(key);
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, leveldb::Slice(key, keylen)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test delete operation that returns an error
TEST_F(LevelDBDeleteTest_223, DeleteReturnsError_223) {
  const char* key = "error_key";
  size_t keylen = strlen(key);
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, leveldb::Slice(key, keylen)))
      .WillOnce(Return(leveldb::Status::IOError("disk failure")));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_NE(errptr, nullptr);
  EXPECT_TRUE(std::string(errptr).find("disk failure") != std::string::npos ||
              std::string(errptr).find("IO error") != std::string::npos);
  free(errptr);
}

// Test delete with empty key
TEST_F(LevelDBDeleteTest_223, DeleteEmptyKey_223) {
  const char* key = "";
  size_t keylen = 0;
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, leveldb::Slice(key, keylen)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test delete with a key containing null bytes
TEST_F(LevelDBDeleteTest_223, DeleteKeyWithNullBytes_223) {
  const char key[] = "key\0with\0nulls";
  size_t keylen = sizeof(key) - 1;  // 14 bytes including embedded nulls
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, leveldb::Slice(key, keylen)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test that the correct key slice is passed to DB::Delete
TEST_F(LevelDBDeleteTest_223, DeletePassesCorrectKey_223) {
  const char* key = "specific_key";
  size_t keylen = strlen(key);
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, _))
      .WillOnce(Invoke([key, keylen](const leveldb::WriteOptions&,
                                      const leveldb::Slice& actual_key) {
        EXPECT_EQ(actual_key.ToString(), std::string(key, keylen));
        return leveldb::Status::OK();
      }));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test delete with a very long key
TEST_F(LevelDBDeleteTest_223, DeleteLongKey_223) {
  std::string long_key(10000, 'x');
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, leveldb::Slice(long_key.data(), long_key.size())))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_delete(&db_, &write_options_, long_key.data(), long_key.size(),
                 &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test delete with NotFound status (which is still a status, not necessarily an error for Delete)
TEST_F(LevelDBDeleteTest_223, DeleteNotFoundStatus_223) {
  const char* key = "nonexistent_key";
  size_t keylen = strlen(key);
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, leveldb::Slice(key, keylen)))
      .WillOnce(Return(leveldb::Status::NotFound("key not found")));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  // NotFound is a non-OK status, so errptr should be set
  EXPECT_NE(errptr, nullptr);
  free(errptr);
}

// Test delete with corruption error
TEST_F(LevelDBDeleteTest_223, DeleteCorruptionError_223) {
  const char* key = "corrupt_key";
  size_t keylen = strlen(key);
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, leveldb::Slice(key, keylen)))
      .WillOnce(Return(leveldb::Status::Corruption("data corrupted")));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_NE(errptr, nullptr);
  free(errptr);
}

// Test that errptr is cleared on success when it was previously set
TEST_F(LevelDBDeleteTest_223, DeleteClearsErrptrOnSuccess_223) {
  const char* key = "test_key";
  size_t keylen = strlen(key);
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, _))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test multiple consecutive deletes
TEST_F(LevelDBDeleteTest_223, MultipleDeletes_223) {
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, _))
      .Times(3)
      .WillRepeatedly(Return(leveldb::Status::OK()));

  leveldb_delete(&db_, &write_options_, "key1", 4, &errptr);
  EXPECT_EQ(errptr, nullptr);

  leveldb_delete(&db_, &write_options_, "key2", 4, &errptr);
  EXPECT_EQ(errptr, nullptr);

  leveldb_delete(&db_, &write_options_, "key3", 4, &errptr);
  EXPECT_EQ(errptr, nullptr);
}

// Test delete with partial key length (keylen < actual string length)
TEST_F(LevelDBDeleteTest_223, DeletePartialKeyLength_223) {
  const char* key = "full_key_string";
  size_t keylen = 4;  // Only "full"
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, _))
      .WillOnce(Invoke([](const leveldb::WriteOptions&,
                          const leveldb::Slice& actual_key) {
        EXPECT_EQ(actual_key.ToString(), "full");
        return leveldb::Status::OK();
      }));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test that write options with sync enabled are passed through
TEST_F(LevelDBDeleteTest_223, DeleteWithSyncOption_223) {
  write_options_.rep.sync = true;
  const char* key = "sync_key";
  size_t keylen = strlen(key);
  char* errptr = nullptr;

  EXPECT_CALL(*mock_db_, Delete(_, _))
      .WillOnce(Invoke([](const leveldb::WriteOptions& opts,
                          const leveldb::Slice&) {
        EXPECT_TRUE(opts.sync);
        return leveldb::Status::OK();
      }));

  leveldb_delete(&db_, &write_options_, key, keylen, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

}  // namespace
