// File: db/db_impl_getsnapshot_test.cc

#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "gtest/gtest.h"

#include <cstdio>
#include <cstdlib>
#include <string>

using leveldb::DB;
using leveldb::Options;
using leveldb::ReadOptions;
using leveldb::Slice;
using leveldb::Status;
using leveldb::WriteOptions;

namespace {

std::string TempDir309() {
#ifdef _WIN32
  const char* tmp = std::getenv("TEMP");
  std::string base = tmp ? tmp : ".";
  return base + "\\leveldb_gs_309_" + std::to_string(::testing::UnitTest::GetInstance()->random_seed());
#else
  const char* tmp = std::getenv("TMPDIR");
  std::string base = tmp ? tmp : "/tmp";
  return base + "/leveldb_gs_309_" + std::to_string(::testing::UnitTest::GetInstance()->random_seed());
#endif
}

void AssertOk309(const Status& s) {
  ASSERT_TRUE(s.ok()) << s.ToString();
}

class GetSnapshotTest_309 : public ::testing::Test {
protected:
  void SetUp() override {
    dbpath_ = TempDir309();
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, dbpath_, &db_);
    AssertOk309(s);
    ASSERT_NE(db_, nullptr);
  }

  void TearDown() override {
    delete db_;
    db_ = nullptr;
    // Best-effort cleanup; LevelDB typically provides DestroyDB, but we
    // avoid relying on it since it's not guaranteed in the snippet.
    // The test runner environment can clean temp dirs if needed.
  }

  DB* db_ = nullptr;
  std::string dbpath_;
};

} // namespace

// 1) Basic contract: returns a non-null snapshot pointer that can be released.
TEST_F(GetSnapshotTest_309, ReturnsNonNullAndReleasable_309) {
  const leveldb::Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);
  db_->ReleaseSnapshot(snap);
}

// 2) Snapshot provides read-your-snapshot isolation: later writes are invisible.
TEST_F(GetSnapshotTest_309, ProvidesStableView_309) {
  WriteOptions wo;
  AssertOk309(db_->Put(wo, Slice("k"), Slice("v1")));

  const leveldb::Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  // Mutate after taking the snapshot.
  AssertOk309(db_->Put(wo, Slice("k"), Slice("v2")));

  // Read at the snapshot should see the old value.
  std::string v_snapshot;
  ReadOptions ro_snapshot;
  ro_snapshot.snapshot = snap;
  AssertOk309(db_->Get(ro_snapshot, Slice("k"), &v_snapshot));
  EXPECT_EQ(v_snapshot, "v1");

  // Read without a snapshot should see the latest.
  std::string v_latest;
  ReadOptions ro_latest;
  AssertOk309(db_->Get(ro_latest, Slice("k"), &v_latest));
  EXPECT_EQ(v_latest, "v2");

  db_->ReleaseSnapshot(snap);
}

// 3) Distinct snapshots and isolation across them.
TEST_F(GetSnapshotTest_309, DistinctSnapshotsReflectDifferentPointsInTime_309) {
  WriteOptions wo;
  AssertOk309(db_->Put(wo, Slice("k"), Slice("v1")));

  const leveldb::Snapshot* s1 = db_->GetSnapshot();
  ASSERT_NE(s1, nullptr);

  AssertOk309(db_->Put(wo, Slice("k"), Slice("v2")));

  const leveldb::Snapshot* s2 = db_->GetSnapshot();
  ASSERT_NE(s2, nullptr);
  // Not required by the public API, but typical: two snapshots are different pointers.
  // This checks only identity of returned handles (observable).
  EXPECT_NE(s1, s2);

  // Read at s1 → v1
  std::string v1;
  ReadOptions r1;
  r1.snapshot = s1;
  AssertOk309(db_->Get(r1, Slice("k"), &v1));
  EXPECT_EQ(v1, "v1");

  // Read at s2 → v2
  std::string v2;
  ReadOptions r2;
  r2.snapshot = s2;
  AssertOk309(db_->Get(r2, Slice("k"), &v2));
  EXPECT_EQ(v2, "v2");

  db_->ReleaseSnapshot(s2);
  db_->ReleaseSnapshot(s1);
}

// 4) Boundary: snapshot of an empty DB sees absence even after later writes.
TEST_F(GetSnapshotTest_309, EmptyDatabaseSnapshotDoesNotSeeFutureWrites_309) {
  const leveldb::Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  // After taking the snapshot, write a key.
  WriteOptions wo;
  AssertOk309(db_->Put(wo, Slice("k"), Slice("v")));

  // Reading at the old snapshot should report NotFound.
  std::string v_snap;
  ReadOptions ro;
  ro.snapshot = snap;
  Status s = db_->Get(ro, Slice("k"), &v_snap);
  EXPECT_FALSE(s.ok()) << "Expected NotFound at the snapshot for a key written later";
  // Avoid asserting specific internal code; just ensure it isn't OK.

  // Current view should see it.
  std::string v_now;
  AssertOk309(db_->Get(ReadOptions{}, Slice("k"), &v_now));
  EXPECT_EQ(v_now, "v");

  db_->ReleaseSnapshot(snap);
}

// 5) Delete after snapshot: snapshot still sees the old value; latest does not.
TEST_F(GetSnapshotTest_309, DeleteAfterSnapshotKeepsOldValueVisibleInSnapshot_309) {
  WriteOptions wo;
  AssertOk309(db_->Put(wo, Slice("k"), Slice("v1")));

  const leveldb::Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  AssertOk309(db_->Delete(wo, Slice("k")));

  // Snapshot read should still return the original value.
  std::string v_snap;
  ReadOptions ro;
  ro.snapshot = snap;
  AssertOk309(db_->Get(ro, Slice("k"), &v_snap));
  EXPECT_EQ(v_snap, "v1");

  // Latest read should report not found.
  std::string v_now;
  Status s_now = db_->Get(ReadOptions{}, Slice("k"), &v_now);
  EXPECT_FALSE(s_now.ok()) << "Expected NotFound for latest view after Delete";

  db_->ReleaseSnapshot(snap);
}
