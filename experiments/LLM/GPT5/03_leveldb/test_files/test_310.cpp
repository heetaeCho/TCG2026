// File: db_impl_release_snapshot_test_310.cc
#include <gtest/gtest.h>
#include <string>

#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"

using namespace leveldb;

namespace {

class DBImplReleaseSnapshotTest_310 : public ::testing::Test {
protected:
  std::string dbname_;
  Options options_;
  DB* db_ = nullptr;

  void SetUp() override {
    // Use a per-test unique path under /tmp. This keeps things black-box and filesystem-only.
    dbname_ = "/tmp/leveldb_release_snapshot_310_" + ::testing::UnitTest::GetInstance()->current_test_info()->name();
    options_.create_if_missing = true;

    // Ensure a clean slate.
    DestroyDB(dbname_, options_);

    ASSERT_TRUE(DB::Open(options_, dbname_, &db_).ok());
    ASSERT_NE(db_, nullptr);
  }

  void TearDown() override {
    delete db_;
    db_ = nullptr;
    DestroyDB(dbname_, options_);
  }

  static std::string Get(DB* db, const ReadOptions& ro, const std::string& key) {
    std::string value;
    Status s = db->Get(ro, key, &value);
    return s.ok() ? value : std::string();
  }

  static void Put(DB* db, const std::string& k, const std::string& v) {
    ASSERT_TRUE(db->Put(WriteOptions(), k, v).ok());
  }
};

// Normal operation: using a snapshot freezes the view; releasing it lets subsequent
// non-snapshot reads observe the latest state.
TEST_F(DBImplReleaseSnapshotTest_310, ReleaseThenObserveLatest_310) {
  Put(db_, "a", "1");
  const Snapshot* s1 = db_->GetSnapshot();
  ASSERT_NE(s1, nullptr);

  Put(db_, "a", "2");

  ReadOptions ro_at_s1;
  ro_at_s1.snapshot = s1;
  EXPECT_EQ("1", Get(db_, ro_at_s1, "a")) << "Snapshot view should reflect the state at snapshot creation";

  // Release the snapshot — black-box expectation: no crash; future non-snapshot reads see latest.
  db_->ReleaseSnapshot(s1);

  ReadOptions ro_latest;  // no snapshot
  EXPECT_EQ("2", Get(db_, ro_latest, "a")) << "After releasing the snapshot, normal reads see the latest value";
}

// Multiple snapshots: independent views; releasing in reverse order should be fine.
TEST_F(DBImplReleaseSnapshotTest_310, MultipleSnapshots_ReverseReleaseOrder_310) {
  Put(db_, "k", "v0");
  const Snapshot* s1 = db_->GetSnapshot();
  ASSERT_NE(s1, nullptr);

  Put(db_, "k", "v1");
  const Snapshot* s2 = db_->GetSnapshot();
  ASSERT_NE(s2, nullptr);

  Put(db_, "k", "v2");

  ReadOptions ro_s1; ro_s1.snapshot = s1;
  ReadOptions ro_s2; ro_s2.snapshot = s2;
  ReadOptions ro_latest; // no snapshot

  // Check views frozen at each snapshot
  EXPECT_EQ("v0", Get(db_, ro_s1, "k")) << "s1 should see v0";
  EXPECT_EQ("v1", Get(db_, ro_s2, "k")) << "s2 should see v1";
  EXPECT_EQ("v2", Get(db_, ro_latest, "k")) << "Latest should see v2";

  // Release in reverse order; black-box expectation: safe sequence
  db_->ReleaseSnapshot(s2);
  db_->ReleaseSnapshot(s1);

  // Ensure DB is still usable after releases
  Put(db_, "k", "v3");
  EXPECT_EQ("v3", Get(db_, ro_latest, "k"));
}

// Boundary: take a snapshot on an empty DB (or with no relevant keys), release immediately,
// and ensure subsequent operations work normally.
TEST_F(DBImplReleaseSnapshotTest_310, ImmediateReleaseOnEmptyView_310) {
  const Snapshot* s = db_->GetSnapshot();
  ASSERT_NE(s, nullptr);

  db_->ReleaseSnapshot(s);  // Expect no errors/crash

  // DB remains fully usable
  Put(db_, "x", "y");
  ReadOptions ro_latest;
  EXPECT_EQ("y", Get(db_, ro_latest, "x"));
}

}  // namespace
