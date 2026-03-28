// File: db_c_create_snapshot_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/db.h"  // Uses the provided interface only

using ::testing::Return;
using ::testing::Exactly;

// Forward declarations of the C wrapper structs and function (from db/c.cc)
struct leveldb_t { leveldb::DB* rep; };
struct leveldb_snapshot_t { const leveldb::Snapshot* rep; };

// The function under test (provided by db/c.cc)
extern const leveldb_snapshot_t* leveldb_create_snapshot(leveldb_t* db);

// Minimal mock for the external collaborator (DB). We override only what we use.
class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(const leveldb::Snapshot*, GetSnapshot, (), (override));

  // The base has many virtuals; we don't use them. Provide benign stubs to avoid
  // pure-virtual linkage issues if needed by your build. These stick to the interface.
  // If your DB methods are not pure-virtual, you can omit these.
  // (Return default-constructed Status or nullptrs; not used by these tests.)
  leveldb::Status Put(const leveldb::WriteOptions&, const leveldb::Slice&, const leveldb::Slice&) override { return leveldb::Status(); }
  leveldb::Status Delete(const leveldb::WriteOptions&, const leveldb::Slice&) override { return leveldb::Status(); }
  leveldb::Status Write(const leveldb::WriteOptions&, leveldb::WriteBatch*) override { return leveldb::Status(); }
  leveldb::Status Get(const leveldb::ReadOptions&, const leveldb::Slice&, std::string*) override { return leveldb::Status(); }
  leveldb::Iterator* NewIterator(const leveldb::ReadOptions&) override { return nullptr; }
  void ReleaseSnapshot(const leveldb::Snapshot*) override {}
  bool GetProperty(const leveldb::Slice&, std::string*) override { return false; }
  void GetApproximateSizes(const leveldb::Range*, int, uint64_t*) override {}
  void CompactRange(const leveldb::Slice*, const leveldb::Slice*) override {}
  const leveldb::Snapshot* GetSnapshot() const { return nullptr; } // not used; keep linker happy
};

// ---------- Tests ----------

// Normal operation: wraps the pointer returned by DB::GetSnapshot and calls it exactly once.
TEST(LeveldbCreateSnapshot_227, CallsGetSnapshotOnceAndWrapsPointer_227) {
  MockDB mock_db;

  // Use a distinct, observable pointer value without constructing Snapshot.
  const leveldb::Snapshot* snapshot_ptr = reinterpret_cast<const leveldb::Snapshot*>(0x1A2B3C4D);

  EXPECT_CALL(mock_db, GetSnapshot())
      .Times(Exactly(1))
      .WillOnce(Return(snapshot_ptr));

  leveldb_t cdb{&mock_db};

  const leveldb_snapshot_t* out = leveldb_create_snapshot(&cdb);

  ASSERT_NE(out, nullptr) << "Should return a valid wrapper struct";
  EXPECT_EQ(out->rep, snapshot_ptr) << "Wrapper must expose the exact snapshot pointer";

  // Clean up the heap allocation done inside leveldb_create_snapshot
  delete const_cast<leveldb_snapshot_t*>(out);
}

// Boundary/observable edge case: DB::GetSnapshot returns nullptr; wrapper should still be allocated.
TEST(LeveldbCreateSnapshot_227, HandlesNullSnapshotPointer_227) {
  MockDB mock_db;

  EXPECT_CALL(mock_db, GetSnapshot())
      .Times(Exactly(1))
      .WillOnce(Return(nullptr));

  leveldb_t cdb{&mock_db};

  const leveldb_snapshot_t* out = leveldb_create_snapshot(&cdb);

  ASSERT_NE(out, nullptr) << "Wrapper struct should still be created";
  EXPECT_EQ(out->rep, nullptr) << "rep should reflect the nullptr returned by DB::GetSnapshot";

  delete const_cast<leveldb_snapshot_t*>(out);
}
