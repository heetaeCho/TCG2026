// File: db/c_writebatch_append_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// The C wrapper struct and function under test (matching the provided partial code).
struct leveldb_writebatch_t { leveldb::WriteBatch rep; };
void leveldb_writebatch_append(leveldb_writebatch_t* destination,
                               const leveldb_writebatch_t* source);

// Mock handler to observe the public iteration behavior.
class MockWBHandler : public leveldb::WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const leveldb::Slice& key, const leveldb::Slice& value), (override));
  MOCK_METHOD(void, Delete, (const leveldb::Slice& key), (override));
};

// -- Helpers ------------------------------------------------------------------

static leveldb::Status Iterate(leveldb::WriteBatch& wb, leveldb::WriteBatch::Handler* h) {
  return wb.Iterate(h);
}

static void AddOpsTo(leveldb::WriteBatch& wb) {
  wb.Put(leveldb::Slice("k1"), leveldb::Slice("v1"));
  wb.Delete(leveldb::Slice("k2"));
  wb.Put(leveldb::Slice("k3"), leveldb::Slice("v3"));
}

// -- Tests --------------------------------------------------------------------

// Normal operation: append a non-empty source to an empty destination.
TEST(WriteBatchAppendTest_250, Append_NonEmptySource_ToEmptyDestination_250) {
  leveldb_writebatch_t dest;
  leveldb_writebatch_t src;

  src.rep.Put(leveldb::Slice("a"), leveldb::Slice("1"));
  src.rep.Delete(leveldb::Slice("b"));
  src.rep.Put(leveldb::Slice("c"), leveldb::Slice("3"));

  // Call function under test.
  leveldb_writebatch_append(&dest, &src);

  // Expect to observe exactly the source operations, in order, when iterating destination.
  testing::InSequence seq;
  MockWBHandler handler;
  EXPECT_CALL(handler, Put(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="a"; }),
                           testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="1"; })));
  EXPECT_CALL(handler, Delete(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="b"; })));
  EXPECT_CALL(handler, Put(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="c"; }),
                           testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="3"; })));

  leveldb::Status st = Iterate(dest.rep, &handler);
  EXPECT_TRUE(st.ok());
}

// Boundary: append an empty source to a non-empty destination (no-op on content).
TEST(WriteBatchAppendTest_250, Append_EmptySource_ToNonEmptyDestination_250) {
  leveldb_writebatch_t dest;
  leveldb_writebatch_t src;  // empty

  dest.rep.Put(leveldb::Slice("x"), leveldb::Slice("10"));
  dest.rep.Delete(leveldb::Slice("y"));

  // Capture an approximate size before (should not decrease after append).
  const size_t before_size = dest.rep.ApproximateSize();

  leveldb_writebatch_append(&dest, &src);

  // Expect original destination ops only, in original order.
  testing::InSequence seq;
  MockWBHandler handler;
  EXPECT_CALL(handler, Put(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="x"; }),
                           testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="10"; })));
  EXPECT_CALL(handler, Delete(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="y"; })));

  leveldb::Status st = Iterate(dest.rep, &handler);
  EXPECT_TRUE(st.ok());

  // Approximate size should not shrink after appending an empty batch.
  EXPECT_GE(dest.rep.ApproximateSize(), before_size);
}

// Normal operation + order preservation: non-empty → non-empty.
TEST(WriteBatchAppendTest_250, Append_NonEmptySource_ToNonEmptyDestination_OrderPreserved_250) {
  leveldb_writebatch_t dest;
  leveldb_writebatch_t src;

  // Destination has A, B
  dest.rep.Put(leveldb::Slice("A"), leveldb::Slice("1"));
  dest.rep.Delete(leveldb::Slice("B"));

  // Source has C, D
  src.rep.Put(leveldb::Slice("C"), leveldb::Slice("3"));
  src.rep.Put(leveldb::Slice("D"), leveldb::Slice("4"));

  leveldb_writebatch_append(&dest, &src);

  // Expect A, B, C, D in that order.
  testing::InSequence seq;
  MockWBHandler handler;
  EXPECT_CALL(handler, Put(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="A"; }),
                           testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="1"; })));
  EXPECT_CALL(handler, Delete(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="B"; })));
  EXPECT_CALL(handler, Put(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="C"; }),
                           testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="3"; })));
  EXPECT_CALL(handler, Put(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="D"; }),
                           testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="4"; })));

  leveldb::Status st = Iterate(dest.rep, &handler);
  EXPECT_TRUE(st.ok());
}

// Boundary: append empty to empty (still empty; no handler calls).
TEST(WriteBatchAppendTest_250, Append_EmptySource_ToEmptyDestination_NoOps_250) {
  leveldb_writebatch_t dest;  // empty
  leveldb_writebatch_t src;   // empty

  leveldb_writebatch_append(&dest, &src);

  // No calls expected.
  MockWBHandler handler;
  leveldb::Status st = Iterate(dest.rep, &handler);
  EXPECT_TRUE(st.ok());
}

// Exceptional/edge (observable): source remains unchanged after append (non-mutating).
TEST(WriteBatchAppendTest_250, Append_DoesNotMutateSource_250) {
  leveldb_writebatch_t dest;
  leveldb_writebatch_t src;

  AddOpsTo(src.rep);  // some puts/deletes
  dest.rep.Put(leveldb::Slice("d_only"), leveldb::Slice("v"));

  // Record source approximate size before; after append, it should not shrink.
  const size_t src_before = src.rep.ApproximateSize();

  leveldb_writebatch_append(&dest, &src);

  // Iterate over source to verify its contents are still present (order as added).
  testing::InSequence seq;
  MockWBHandler handler;
  EXPECT_CALL(handler, Put(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="k1"; }),
                           testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="v1"; })));
  EXPECT_CALL(handler, Delete(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="k2"; })));
  EXPECT_CALL(handler, Put(testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="k3"; }),
                           testing::Truly([](const leveldb::Slice& s){ return s.ToString()=="v3"; })));

  leveldb::Status st = Iterate(src.rep, &handler);
  EXPECT_TRUE(st.ok());
  EXPECT_GE(src.rep.ApproximateSize(), src_before);
}
