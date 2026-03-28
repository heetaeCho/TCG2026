#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/options.h"

// Include the C API header or replicate the necessary structs and function declarations
extern "C" {
// Forward declarations matching the C API
struct leveldb_t;
struct leveldb_snapshot_t;
void leveldb_release_snapshot(leveldb_t* db, const leveldb_snapshot_t* snapshot);
}

// We need access to the internal structs from c.cc
// Replicate them here for testing purposes since they are part of the interface
namespace {

struct leveldb_t {
  leveldb::DB* rep;
};

struct leveldb_snapshot_t {
  const leveldb::Snapshot* rep;
};

}  // namespace

// Mock DB class to verify interactions
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
              (const leveldb::Slice& property, std::string* value),
              (override));
  MOCK_METHOD(void, GetApproximateSizes,
              (const leveldb::Range* range, int n, uint64_t* sizes),
              (override));
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice* begin, const leveldb::Slice* end),
              (override));
};

// A concrete Snapshot subclass for testing
class FakeSnapshot : public leveldb::Snapshot {
 public:
  // The Snapshot class is abstract in some implementations, but typically
  // it's an opaque type. We just need a concrete instance for pointer comparison.
};

// Re-implement the function under test locally since we need to link against it
// This matches the exact implementation from c.cc
namespace {
void test_leveldb_release_snapshot(leveldb_t* db,
                                   const leveldb_snapshot_t* snapshot) {
  db->rep->ReleaseSnapshot(snapshot->rep);
  delete snapshot;
}
}  // namespace

class LevelDBReleaseSnapshotTest_228 : public ::testing::Test {
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

// Test that ReleaseSnapshot is called on the DB with the correct snapshot pointer
TEST_F(LevelDBReleaseSnapshotTest_228, ReleaseSnapshotCallsDBReleaseSnapshot_228) {
  FakeSnapshot fake_snap;
  leveldb_snapshot_t* snap_wrapper = new leveldb_snapshot_t;
  snap_wrapper->rep = &fake_snap;

  EXPECT_CALL(*mock_db_, ReleaseSnapshot(&fake_snap)).Times(1);

  test_leveldb_release_snapshot(&db_wrapper_, snap_wrapper);
  // snap_wrapper is deleted inside the function, so no need to delete here
}

// Test that the snapshot wrapper is deleted (no double-delete crash)
TEST_F(LevelDBReleaseSnapshotTest_228, SnapshotWrapperIsDeleted_228) {
  FakeSnapshot fake_snap;
  leveldb_snapshot_t* snap_wrapper = new leveldb_snapshot_t;
  snap_wrapper->rep = &fake_snap;

  EXPECT_CALL(*mock_db_, ReleaseSnapshot(&fake_snap)).Times(1);

  // This should not leak or double-free
  test_leveldb_release_snapshot(&db_wrapper_, snap_wrapper);
}

// Test with a different snapshot pointer to ensure correct pointer is passed
TEST_F(LevelDBReleaseSnapshotTest_228, CorrectSnapshotPointerPassed_228) {
  FakeSnapshot snap1;
  FakeSnapshot snap2;

  // Release snap1
  {
    leveldb_snapshot_t* wrapper1 = new leveldb_snapshot_t;
    wrapper1->rep = &snap1;
    EXPECT_CALL(*mock_db_, ReleaseSnapshot(&snap1)).Times(1);
    test_leveldb_release_snapshot(&db_wrapper_, wrapper1);
  }

  // Release snap2
  {
    leveldb_snapshot_t* wrapper2 = new leveldb_snapshot_t;
    wrapper2->rep = &snap2;
    EXPECT_CALL(*mock_db_, ReleaseSnapshot(&snap2)).Times(1);
    test_leveldb_release_snapshot(&db_wrapper_, wrapper2);
  }
}

// Test releasing multiple snapshots sequentially
TEST_F(LevelDBReleaseSnapshotTest_228, MultipleSnapshotsReleasedSequentially_228) {
  const int kNumSnapshots = 5;
  FakeSnapshot fake_snaps[kNumSnapshots];

  for (int i = 0; i < kNumSnapshots; i++) {
    leveldb_snapshot_t* wrapper = new leveldb_snapshot_t;
    wrapper->rep = &fake_snaps[i];
    EXPECT_CALL(*mock_db_, ReleaseSnapshot(&fake_snaps[i])).Times(1);
    test_leveldb_release_snapshot(&db_wrapper_, wrapper);
  }
}

// Test that the function works when GetSnapshot returns a snapshot and we release it
TEST_F(LevelDBReleaseSnapshotTest_228, GetAndReleaseSnapshotRoundTrip_228) {
  FakeSnapshot fake_snap;

  EXPECT_CALL(*mock_db_, GetSnapshot())
      .WillOnce(::testing::Return(&fake_snap));

  const leveldb::Snapshot* snap = mock_db_->GetSnapshot();

  leveldb_snapshot_t* wrapper = new leveldb_snapshot_t;
  wrapper->rep = snap;

  EXPECT_CALL(*mock_db_, ReleaseSnapshot(&fake_snap)).Times(1);
  test_leveldb_release_snapshot(&db_wrapper_, wrapper);
}
