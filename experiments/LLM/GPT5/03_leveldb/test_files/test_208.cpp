// File: write_batch_internal_insert_into_test.cc

#include "db/write_batch_internal.h"
#include "leveldb/write_batch.h"
#include "db/memtable.h"
#include "db/dbformat.h"           // LookupKey, kMaxSequenceNumber
#include "util/coding.h"           // (indirect deps in some builds)
#include "util/comparator.h"       // BytewiseComparator()
#include "gtest/gtest.h"

namespace leveldb {

// Test fixture that provides a real MemTable and utilities to read values.
class WriteBatchInternalInsertIntoTest_208 : public ::testing::Test {
 protected:
  WriteBatchInternalInsertIntoTest_208()
      : cmp_(BytewiseComparator()), mem_(new MemTable(cmp_)) {
    mem_->Ref();  // MemTable requires manual ref-counting
  }

  ~WriteBatchInternalInsertIntoTest_208() override {
    mem_->Unref();
  }

  // Reads the latest visible value for `ukey`. Returns (found, value, status).
  struct ReadResult {
    bool called = false;     // MemTable::Get returned true/false
    std::string value;       // filled when a value is present
    Status status;           // OK / NotFound as set by MemTable
  };

  ReadResult Read(const Slice& ukey) {
    ReadResult r;
    LookupKey lkey(ukey, kMaxSequenceNumber);
    r.called = mem_->Get(lkey, &r.value, &r.status);
    return r;
  }

  InternalKeyComparator cmp_;
  MemTable* mem_;
};

// Normal operation: two Puts are inserted and retrievable.
TEST_F(WriteBatchInternalInsertIntoTest_208, InsertTwoPutsAndReadBack_208) {
  WriteBatch b;
  b.Put("a", "va");
  b.Put("b", "vb");
  WriteBatchInternal::SetSequence(&b, 100);

  Status s = WriteBatchInternal::InsertInto(&b, mem_);
  ASSERT_TRUE(s.ok());

  auto ra = Read("a");
  ASSERT_TRUE(ra.called);
  ASSERT_TRUE(ra.status.ok());
  EXPECT_EQ("va", ra.value);

  auto rb = Read("b");
  ASSERT_TRUE(rb.called);
  ASSERT_TRUE(rb.status.ok());
  EXPECT_EQ("vb", rb.value);
}

// Boundary: empty batch should change nothing and succeed.
TEST_F(WriteBatchInternalInsertIntoTest_208, InsertEmptyBatch_NoEffect_208) {
  WriteBatch empty;
  WriteBatchInternal::SetSequence(&empty, 50);

  Status s = WriteBatchInternal::InsertInto(&empty, mem_);
  ASSERT_TRUE(s.ok());

  // Reading an unknown key should not yield a value.
  auto rx = Read("unknown-key");
  // If MemTable finds nothing, it typically returns false, but do not assert
  // on exact boolean semantics; just assert we did not get an OK value.
  if (rx.called) {
    EXPECT_FALSE(rx.status.ok());   // Expect NotFound (or non-OK) if called
  } else {
    SUCCEED(); // Nothing found is acceptable as "no effect".
  }
}

// Delete behavior: Put then Delete; final read reports NotFound.
TEST_F(WriteBatchInternalInsertIntoTest_208, InsertDeleteMarksKeyNotFound_208) {
  // First insert a value
  {
    WriteBatch b1;
    b1.Put("k", "v1");
    WriteBatchInternal::SetSequence(&b1, 10);
    ASSERT_TRUE(WriteBatchInternal::InsertInto(&b1, mem_).ok());
  }

  // Then delete the same key
  {
    WriteBatch b2;
    b2.Delete("k");
    WriteBatchInternal::SetSequence(&b2, 11);
    ASSERT_TRUE(WriteBatchInternal::InsertInto(&b2, mem_).ok());
  }

  auto r = Read("k");
  // MemTable should report a logical deletion (latest op is delete).
  ASSERT_TRUE(r.called);           // Lookup performed
  EXPECT_TRUE(r.status.IsNotFound());
}

// Sequence propagation: later insertion with LOWER sequence must not override
// a higher-sequence value (even if inserted after).
TEST_F(WriteBatchInternalInsertIntoTest_208, HonorsBatchSequenceNumbers_208) {
  // Higher-sequence write
  {
    WriteBatch high;
    high.Put("x", "newer");
    WriteBatchInternal::SetSequence(&high, 200);
    ASSERT_TRUE(WriteBatchInternal::InsertInto(&high, mem_).ok());
  }

  // Lower-sequence write inserted afterward
  {
    WriteBatch low;
    low.Put("x", "older");
    WriteBatchInternal::SetSequence(&low, 100);
    ASSERT_TRUE(WriteBatchInternal::InsertInto(&low, mem_).ok());
  }

  auto r = Read("x");
  ASSERT_TRUE(r.called);
  ASSERT_TRUE(r.status.ok());
  EXPECT_EQ("newer", r.value);  // Must reflect the higher sequence, not order
}

// Same-key overwrite within one batch: last Put wins.
TEST_F(WriteBatchInternalInsertIntoTest_208, LastPutWinsWithinBatch_208) {
  WriteBatch b;
  b.Put("y", "v1");
  b.Put("y", "v2");   // same key again
  WriteBatchInternal::SetSequence(&b, 77);

  ASSERT_TRUE(WriteBatchInternal::InsertInto(&b, mem_).ok());

  auto r = Read("y");
  ASSERT_TRUE(r.called);
  ASSERT_TRUE(r.status.ok());
  EXPECT_EQ("v2", r.value);
}

}  // namespace leveldb
