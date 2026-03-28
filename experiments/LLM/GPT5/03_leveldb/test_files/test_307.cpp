// File: db_impl_newiterator_test_307.cc

#include <gtest/gtest.h>
#include "db/db_impl.h"
#include "leveldb/options.h"
#include "db/snapshot.h"

namespace leveldb {

// ---------- Test seam for NewDBIterator (external collaborator) ----------
static DBImpl*        g_captured_db         = nullptr;
static const Comparator* g_captured_ucmp    = nullptr;
static Iterator*      g_captured_child_iter = nullptr;
static SequenceNumber g_captured_seq        = 0;
static uint32_t       g_captured_seed       = 0;

// A tiny dummy iterator we can safely return from the seam.
class DummyIterator : public Iterator {
 public:
  DummyIterator() = default;
  ~DummyIterator() override = default;
  bool Valid() const override { return false; }
  void SeekToFirst() override {}
  void SeekToLast() override {}
  void Seek(const Slice&) override {}
  void Next() override {}
  void Prev() override {}
  Slice key() const override { return Slice(); }
  Slice value() const override { return Slice(); }
  Status status() const override { return Status::OK(); }
};

// Singleton dummy to return from our seam.
static DummyIterator g_return_iter;

// Link seam: capture parameters that NewIterator forwards to NewDBIterator,
// and return a stable Iterator* that our tests can compare against.
Iterator* NewDBIterator(DBImpl* db,
                        const Comparator* ucmp,
                        Iterator* child,
                        SequenceNumber seq,
                        uint32_t seed) {
  g_captured_db         = db;
  g_captured_ucmp       = ucmp;
  g_captured_child_iter = child;
  g_captured_seq        = seq;
  g_captured_seed       = seed;
  return &g_return_iter;
}

}  // namespace leveldb

namespace {

using namespace leveldb;

class DBImplNewIteratorTest_307 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Clear captured globals before each test.
    g_captured_db         = nullptr;
    g_captured_ucmp       = nullptr;
    g_captured_child_iter = nullptr;
    g_captured_seq        = 0;
    g_captured_seed       = 0;
  }
};

// TEST_ID: 307
TEST_F(DBImplNewIteratorTest_307, ReturnsWhatNewDBIteratorReturns_307) {
  // Arrange
  Options opts;
  // A lightweight dbname. We don't open files; just construct the object.
  const std::string dbname = "NewIterator_ReturnsThrough_307";
  DBImpl db(opts, dbname);

  ReadOptions ro;           // default: snapshot == nullptr

  // Act
  Iterator* it = db.NewIterator(ro);

  // Assert
  // NewIterator should return exactly what the external NewDBIterator returned.
  EXPECT_EQ(it, &g_return_iter);

  // We can also sanity-check that we captured this DB and a comparator.
  EXPECT_EQ(g_captured_db, &db);
  EXPECT_NE(g_captured_ucmp, nullptr);
  // The child iterator should be whatever NewInternalIterator produced.
  // We don't assert its identity, but we do expect a non-null observable.
  EXPECT_NE(g_captured_child_iter, nullptr);
}

// TEST_ID: 307
TEST_F(DBImplNewIteratorTest_307, UsesExplicitSnapshotWhenProvided_307) {
  // Arrange
  Options opts;
  const std::string dbname = "NewIterator_UsesSnapshot_307";
  DBImpl db(opts, dbname);

  // Provide a snapshot with a known sequence number.
  const SequenceNumber kSeq = 1234567;
  SnapshotImpl snap(kSeq);
  ReadOptions ro;
  ro.snapshot = &snap;

  // Act
  Iterator* it = db.NewIterator(ro);

  // Assert
  EXPECT_EQ(it, &g_return_iter) << "Return value should come from NewDBIterator seam";
  EXPECT_EQ(g_captured_db, &db) << "DB pointer should be forwarded";
  EXPECT_NE(g_captured_ucmp, nullptr) << "Comparator should be provided";
  EXPECT_NE(g_captured_child_iter, nullptr) << "Internal iterator should be forwarded";

  // Critical behavior: when ReadOptions::snapshot is set, NewIterator must
  // forward that snapshot's sequence_number() to NewDBIterator.
  EXPECT_EQ(g_captured_seq, kSeq) << "Sequence number must come from provided snapshot";
  // Seed is opaque; we just verify it was forwarded as some value.
  // (No assertion on exact value, as it's an internal detail.)
}

// TEST_ID: 307
TEST_F(DBImplNewIteratorTest_307, ForwardsChildIteratorAndComparator_307) {
  // Arrange
  Options opts;
  const std::string dbname = "NewIterator_ForwardsChildAndCmp_307";
  DBImpl db(opts, dbname);

  ReadOptions ro;

  // Act
  (void)db.NewIterator(ro);

  // Assert
  // We only check observable forwarding behavior to the external collaborator.
  EXPECT_EQ(g_captured_db, &db);
  EXPECT_NE(g_captured_ucmp, nullptr) << "User comparator must be forwarded";
  EXPECT_NE(g_captured_child_iter, nullptr) << "Child iterator from NewInternalIterator must be forwarded";
  // No assertion on g_captured_seq here because with snapshot == nullptr,
  // NewIterator uses latest_snapshot from internal code, which is an internal detail.
}

}  // namespace
