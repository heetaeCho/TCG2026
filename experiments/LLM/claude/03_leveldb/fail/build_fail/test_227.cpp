#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"

#include <cstdint>
#include <string>

// Include the C API header
extern "C" {
#include "leveldb/c.h"
}

// We need access to the internal structs for testing
// These mirror the structs defined in db/c.cc
namespace leveldb {
class Snapshot {};
}

struct leveldb_t {
  leveldb::DB* rep;
};

struct leveldb_snapshot_t {
  const leveldb::Snapshot* rep;
};

// Declare the function under test
extern "C" {
const leveldb_snapshot_t* leveldb_create_snapshot(leveldb_t* db);
}

// Mock DB class to simulate GetSnapshot behavior
class MockDB : public leveldb::DB {
 public:
  MockDB() = default;
  ~MockDB() override = default;

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
              (const leveldb::Slice& property, std::string* value),
              (override));
  MOCK_METHOD(void, GetApproximateSizes,
              (const leveldb::Range* range, int n, uint64_t* sizes),
              (override));
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice* begin, const leveldb::Slice* end),
              (override));
};

class LevelDBCreateSnapshotTest_227 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new MockDB();
    db_wrapper_.rep = mock_db_;
  }

  void TearDown() override {
    delete mock_db_;
  }

  MockDB* mock_db_;
  leveldb_t db_wrapper_;
};

// Test that leveldb_create_snapshot returns a non-null result
TEST_F(LevelDBCreateSnapshotTest_227, ReturnsNonNullSnapshot_227) {
  leveldb::Snapshot dummy_snapshot;
  EXPECT_CALL(*mock_db_, GetSnapshot())
      .WillOnce(::testing::Return(&dummy_snapshot));

  const leveldb_snapshot_t* result = leveldb_create_snapshot(&db_wrapper_);

  ASSERT_NE(result, nullptr);
  delete result;
}

// Test that the returned snapshot contains the correct snapshot pointer from DB
TEST_F(LevelDBCreateSnapshotTest_227, SnapshotRepMatchesDBGetSnapshot_227) {
  leveldb::Snapshot dummy_snapshot;
  EXPECT_CALL(*mock_db_, GetSnapshot())
      .WillOnce(::testing::Return(&dummy_snapshot));

  const leveldb_snapshot_t* result = leveldb_create_snapshot(&db_wrapper_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->rep, &dummy_snapshot);
  delete result;
}

// Test that GetSnapshot is called exactly once on the DB
TEST_F(LevelDBCreateSnapshotTest_227, CallsGetSnapshotOnce_227) {
  leveldb::Snapshot dummy_snapshot;
  EXPECT_CALL(*mock_db_, GetSnapshot())
      .Times(1)
      .WillOnce(::testing::Return(&dummy_snapshot));

  const leveldb_snapshot_t* result = leveldb_create_snapshot(&db_wrapper_);

  ASSERT_NE(result, nullptr);
  delete result;
}

// Test when DB::GetSnapshot returns nullptr
TEST_F(LevelDBCreateSnapshotTest_227, HandlesNullSnapshotFromDB_227) {
  EXPECT_CALL(*mock_db_, GetSnapshot())
      .WillOnce(::testing::Return(nullptr));

  const leveldb_snapshot_t* result = leveldb_create_snapshot(&db_wrapper_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->rep, nullptr);
  delete result;
}

// Test multiple consecutive snapshot creations return distinct snapshot_t objects
TEST_F(LevelDBCreateSnapshotTest_227, MultipleSnapshotsAreDistinct_227) {
  leveldb::Snapshot dummy_snapshot1;
  leveldb::Snapshot dummy_snapshot2;

  EXPECT_CALL(*mock_db_, GetSnapshot())
      .WillOnce(::testing::Return(&dummy_snapshot1))
      .WillOnce(::testing::Return(&dummy_snapshot2));

  const leveldb_snapshot_t* result1 = leveldb_create_snapshot(&db_wrapper_);
  const leveldb_snapshot_t* result2 = leveldb_create_snapshot(&db_wrapper_);

  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  EXPECT_NE(result1, result2);
  EXPECT_EQ(result1->rep, &dummy_snapshot1);
  EXPECT_EQ(result2->rep, &dummy_snapshot2);

  delete result1;
  delete result2;
}

// Test that the same snapshot pointer can be returned multiple times
TEST_F(LevelDBCreateSnapshotTest_227, SameSnapshotPointerMultipleCalls_227) {
  leveldb::Snapshot dummy_snapshot;

  EXPECT_CALL(*mock_db_, GetSnapshot())
      .WillRepeatedly(::testing::Return(&dummy_snapshot));

  const leveldb_snapshot_t* result1 = leveldb_create_snapshot(&db_wrapper_);
  const leveldb_snapshot_t* result2 = leveldb_create_snapshot(&db_wrapper_);

  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  // Different wrapper objects
  EXPECT_NE(result1, result2);
  // But same underlying snapshot
  EXPECT_EQ(result1->rep, result2->rep);
  EXPECT_EQ(result1->rep, &dummy_snapshot);

  delete result1;
  delete result2;
}
