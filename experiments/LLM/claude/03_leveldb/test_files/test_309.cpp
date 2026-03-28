#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <set>

namespace leveldb {

class DBImplGetSnapshotTest_309 : public testing::Test {
 protected:
  void SetUp() override {
    dbname_ = testing::TempDir() + "db_impl_snapshot_test_309";
    DestroyDB(dbname_, Options());
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, Options());
  }

  std::string dbname_;
  DB* db_ = nullptr;
};

// Test that GetSnapshot returns a non-null pointer
TEST_F(DBImplGetSnapshotTest_309, GetSnapshotReturnsNonNull_309) {
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);
  db_->ReleaseSnapshot(snap);
}

// Test that multiple snapshots can be taken and are all non-null
TEST_F(DBImplGetSnapshotTest_309, MultipleSnapshotsAreNonNull_309) {
  const Snapshot* snap1 = db_->GetSnapshot();
  const Snapshot* snap2 = db_->GetSnapshot();
  const Snapshot* snap3 = db_->GetSnapshot();
  ASSERT_NE(snap1, nullptr);
  ASSERT_NE(snap2, nullptr);
  ASSERT_NE(snap3, nullptr);
  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
  db_->ReleaseSnapshot(snap3);
}

// Test that multiple snapshots return distinct pointers
TEST_F(DBImplGetSnapshotTest_309, MultipleSnapshotsAreDistinct_309) {
  const Snapshot* snap1 = db_->GetSnapshot();
  const Snapshot* snap2 = db_->GetSnapshot();
  EXPECT_NE(snap1, snap2);
  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
}

// Test that a snapshot taken before a write can still read old data
TEST_F(DBImplGetSnapshotTest_309, SnapshotSeesDataBeforeWrite_309) {
  // Write a key
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value1").ok());

  // Take a snapshot
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  // Overwrite the key
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value2").ok());

  // Read with snapshot should see old value
  ReadOptions read_opts;
  read_opts.snapshot = snap;
  std::string value;
  Status s = db_->Get(read_opts, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "value1");

  // Read without snapshot should see new value
  s = db_->Get(ReadOptions(), "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "value2");

  db_->ReleaseSnapshot(snap);
}

// Test that a snapshot taken on empty DB works
TEST_F(DBImplGetSnapshotTest_309, SnapshotOnEmptyDB_309) {
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  // Write after snapshot
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value1").ok());

  // Reading with the snapshot should not find the key
  ReadOptions read_opts;
  read_opts.snapshot = snap;
  std::string value;
  Status s = db_->Get(read_opts, "key1", &value);
  EXPECT_TRUE(s.IsNotFound());

  db_->ReleaseSnapshot(snap);
}

// Test that ReleaseSnapshot works without crashing
TEST_F(DBImplGetSnapshotTest_309, ReleaseSnapshotWorks_309) {
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);
  // Should not crash or fail
  db_->ReleaseSnapshot(snap);
}

// Test snapshot isolation with deletes
TEST_F(DBImplGetSnapshotTest_309, SnapshotIsolationWithDelete_309) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value1").ok());

  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  // Delete the key after snapshot
  ASSERT_TRUE(db_->Delete(WriteOptions(), "key1").ok());

  // With snapshot, the key should still be visible
  ReadOptions read_opts;
  read_opts.snapshot = snap;
  std::string value;
  Status s = db_->Get(read_opts, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "value1");

  // Without snapshot, the key should be deleted
  s = db_->Get(ReadOptions(), "key1", &value);
  EXPECT_TRUE(s.IsNotFound());

  db_->ReleaseSnapshot(snap);
}

// Test that snapshots taken at different points see different data
TEST_F(DBImplGetSnapshotTest_309, SnapshotsAtDifferentPoints_309) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "v1").ok());
  const Snapshot* snap1 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "v2").ok());
  const Snapshot* snap2 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "v3").ok());

  // snap1 should see v1
  ReadOptions ro1;
  ro1.snapshot = snap1;
  std::string value;
  ASSERT_TRUE(db_->Get(ro1, "key1", &value).ok());
  EXPECT_EQ(value, "v1");

  // snap2 should see v2
  ReadOptions ro2;
  ro2.snapshot = snap2;
  ASSERT_TRUE(db_->Get(ro2, "key1", &value).ok());
  EXPECT_EQ(value, "v2");

  // Current should see v3
  ASSERT_TRUE(db_->Get(ReadOptions(), "key1", &value).ok());
  EXPECT_EQ(value, "v3");

  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
}

// Test creating many snapshots
TEST_F(DBImplGetSnapshotTest_309, ManySnapshots_309) {
  std::vector<const Snapshot*> snapshots;
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(db_->Put(WriteOptions(), "key", std::to_string(i)).ok());
    snapshots.push_back(db_->GetSnapshot());
    ASSERT_NE(snapshots.back(), nullptr);
  }

  // Verify each snapshot sees the correct value
  for (int i = 0; i < 100; i++) {
    ReadOptions ro;
    ro.snapshot = snapshots[i];
    std::string value;
    ASSERT_TRUE(db_->Get(ro, "key", &value).ok());
    EXPECT_EQ(value, std::to_string(i));
  }

  // Release all snapshots
  for (auto* snap : snapshots) {
    db_->ReleaseSnapshot(snap);
  }
}

// Test iterator with snapshot
TEST_F(DBImplGetSnapshotTest_309, IteratorWithSnapshot_309) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());

  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());
  ASSERT_TRUE(db_->Delete(WriteOptions(), "a").ok());

  ReadOptions ro;
  ro.snapshot = snap;
  Iterator* iter = db_->NewIterator(ro);
  iter->SeekToFirst();

  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");
  EXPECT_EQ(iter->value().ToString(), "1");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");
  EXPECT_EQ(iter->value().ToString(), "2");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  db_->ReleaseSnapshot(snap);
}

// Test snapshot after batch write
TEST_F(DBImplGetSnapshotTest_309, SnapshotAfterBatchWrite_309) {
  WriteBatch batch;
  batch.Put("k1", "v1");
  batch.Put("k2", "v2");
  batch.Put("k3", "v3");
  ASSERT_TRUE(db_->Write(WriteOptions(), &batch).ok());

  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  // Overwrite
  ASSERT_TRUE(db_->Put(WriteOptions(), "k2", "v2_new").ok());

  ReadOptions ro;
  ro.snapshot = snap;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "k2", &value).ok());
  EXPECT_EQ(value, "v2");

  db_->ReleaseSnapshot(snap);
}

}  // namespace leveldb
