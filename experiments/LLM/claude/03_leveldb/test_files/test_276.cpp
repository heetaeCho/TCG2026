#include "gtest/gtest.h"

// Include necessary headers
#include "leveldb/c.h"
#include "leveldb/options.h"

// We need access to the internal structs for testing purposes
// These are defined in db/c.cc, so we replicate their definitions here
// as they are part of the C API bridge layer

namespace leveldb {
class Snapshot {};
}  // namespace leveldb

struct leveldb_snapshot_t {
  const leveldb::Snapshot* rep;
};

struct leveldb_readoptions_t {
  leveldb::ReadOptions rep;
};

// Declaration of the function under test
extern "C" {
void leveldb_readoptions_set_snapshot(leveldb_readoptions_t* opt,
                                      const leveldb_snapshot_t* snap);
}

class ReadOptionsSetSnapshotTest_276 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_.rep.snapshot = nullptr;
  }

  leveldb_readoptions_t opt_;
};

// Test that setting a valid snapshot correctly assigns the snapshot pointer
TEST_F(ReadOptionsSetSnapshotTest_276, SetValidSnapshot_276) {
  leveldb::Snapshot fake_snapshot;
  leveldb_snapshot_t snap;
  snap.rep = &fake_snapshot;

  leveldb_readoptions_set_snapshot(&opt_, &snap);

  EXPECT_EQ(opt_.rep.snapshot, &fake_snapshot);
}

// Test that passing nullptr for snapshot sets the internal snapshot to nullptr
TEST_F(ReadOptionsSetSnapshotTest_276, SetNullSnapshot_276) {
  // First set a valid snapshot
  leveldb::Snapshot fake_snapshot;
  leveldb_snapshot_t snap;
  snap.rep = &fake_snapshot;
  leveldb_readoptions_set_snapshot(&opt_, &snap);
  ASSERT_EQ(opt_.rep.snapshot, &fake_snapshot);

  // Now set to null
  leveldb_readoptions_set_snapshot(&opt_, nullptr);

  EXPECT_EQ(opt_.rep.snapshot, nullptr);
}

// Test that snapshot is initially nullptr and remains nullptr after setting null
TEST_F(ReadOptionsSetSnapshotTest_276, InitiallyNullThenSetNull_276) {
  ASSERT_EQ(opt_.rep.snapshot, nullptr);

  leveldb_readoptions_set_snapshot(&opt_, nullptr);

  EXPECT_EQ(opt_.rep.snapshot, nullptr);
}

// Test overwriting one snapshot with another
TEST_F(ReadOptionsSetSnapshotTest_276, OverwriteSnapshotWithAnother_276) {
  leveldb::Snapshot fake_snapshot1;
  leveldb::Snapshot fake_snapshot2;

  leveldb_snapshot_t snap1;
  snap1.rep = &fake_snapshot1;

  leveldb_snapshot_t snap2;
  snap2.rep = &fake_snapshot2;

  leveldb_readoptions_set_snapshot(&opt_, &snap1);
  EXPECT_EQ(opt_.rep.snapshot, &fake_snapshot1);

  leveldb_readoptions_set_snapshot(&opt_, &snap2);
  EXPECT_EQ(opt_.rep.snapshot, &fake_snapshot2);
}

// Test that when snapshot_t has a nullptr rep, it is correctly assigned
TEST_F(ReadOptionsSetSnapshotTest_276, SnapshotWithNullRep_276) {
  leveldb_snapshot_t snap;
  snap.rep = nullptr;

  leveldb_readoptions_set_snapshot(&opt_, &snap);

  // snap is not nullptr, but snap->rep is nullptr
  // The code does: snap ? snap->rep : nullptr
  // Since snap is not null, it should assign snap->rep which is nullptr
  EXPECT_EQ(opt_.rep.snapshot, nullptr);
}

// Test setting the same snapshot twice
TEST_F(ReadOptionsSetSnapshotTest_276, SetSameSnapshotTwice_276) {
  leveldb::Snapshot fake_snapshot;
  leveldb_snapshot_t snap;
  snap.rep = &fake_snapshot;

  leveldb_readoptions_set_snapshot(&opt_, &snap);
  EXPECT_EQ(opt_.rep.snapshot, &fake_snapshot);

  leveldb_readoptions_set_snapshot(&opt_, &snap);
  EXPECT_EQ(opt_.rep.snapshot, &fake_snapshot);
}

// Test setting snapshot, clearing it, then setting again
TEST_F(ReadOptionsSetSnapshotTest_276, SetClearAndSetAgain_276) {
  leveldb::Snapshot fake_snapshot;
  leveldb_snapshot_t snap;
  snap.rep = &fake_snapshot;

  leveldb_readoptions_set_snapshot(&opt_, &snap);
  EXPECT_EQ(opt_.rep.snapshot, &fake_snapshot);

  leveldb_readoptions_set_snapshot(&opt_, nullptr);
  EXPECT_EQ(opt_.rep.snapshot, nullptr);

  leveldb_readoptions_set_snapshot(&opt_, &snap);
  EXPECT_EQ(opt_.rep.snapshot, &fake_snapshot);
}
