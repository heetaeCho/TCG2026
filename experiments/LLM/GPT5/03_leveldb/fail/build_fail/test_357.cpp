// File: memtable_iterator_valid_test_357.cc
#include <gtest/gtest.h>

//
// Test-only fakes for the collaborator that MemTableIterator depends on.
// We do NOT re-implement MemTableIterator or any internal logic.
// We only provide a minimal MemTable::Table and its nested Iterator so that
// MemTableIterator can be constructed and its observable behavior (Valid())
// can be exercised.
//
namespace leveldb {

// Forward declarations for types used by the Iterator interface.
// We don't depend on their internals in these tests.
class Slice;
class Status;

// Test double for MemTable::Table with a nested Iterator whose Valid() is controllable.
struct FakeTable {
  bool valid_flag = false;  // Controlled by the tests to simulate iterator validity.
};

// Place this inside the same nested name as the real one,
// so MemTableIterator can use it via `MemTable::Table::Iterator`.
struct MemTable {
  using Table = FakeTable;

  // Nested Iterator that matches the name used by MemTableIterator’s iter_ type.
  struct TableIterator {
    explicit TableIterator(Table* t) : table_(t) {}
    bool Valid() const { return table_ && table_->valid_flag; }

    // The rest of the methods need not do anything for these tests,
    // but we keep the signatures minimal and harmless if ever called.
    void Seek(const Slice&) {}
    void SeekToFirst() {}
    void SeekToLast() {}
    void Next() {}
    void Prev() {}

   private:
    Table* table_;
  };
}

// Map the expected name `MemTable::Table::Iterator` used by the partial code
// to our test double above (MemTable::TableIterator).
// If your build already provides MemTable::Table::Iterator, remove this alias.
; // end previous struct

// Create an alias so the partial production code
// `class MemTable::Table::Iterator` resolves to our TableIterator in tests.
namespace MemTableAliasPatch {
  using Table = MemTable::Table;
  using Iterator = MemTable::TableIterator;
}

// Bring the alias into the exact nested name MemTableIterator expects.
class MemTableIterator; // forward (owned by production code)
} // namespace leveldb

// Include the production implementation snippet for Valid() if needed.
// Otherwise, make sure your build links against the real memtable.cc
// which defines `leveldb::MemTableIterator::Valid()` as:
//   bool MemTableIterator::Valid() const override { return iter_.Valid(); }
// (Do NOT re-implement it here.)

using namespace leveldb;

class MemTableIteratorTest_357 : public ::testing::Test {
protected:
  // Helper to construct a MemTableIterator given a FakeTable.
  // The constructor signature from the prompt is:
  //   explicit MemTableIterator(MemTable::Table* table)
  MemTableIterator MakeIterator(FakeTable* table);
};

// ---------- Tests ----------

// Normal operation: Valid() returns true when underlying iterator reports true.
TEST_F(MemTableIteratorTest_357, ValidReflectsUnderlyingTrue_357) {
  FakeTable table;
  table.valid_flag = true;

  MemTableIterator it = MakeIterator(&table);
  EXPECT_TRUE(it.Valid());
}

// Normal operation: Valid() returns false when underlying iterator reports false.
TEST_F(MemTableIteratorTest_357, ValidReflectsUnderlyingFalse_357) {
  FakeTable table;
  table.valid_flag = false;

  MemTableIterator it = MakeIterator(&table);
  EXPECT_FALSE(it.Valid());
}

// Boundary/observable change: When the underlying condition changes,
// Valid() reflects the change (as it forwards to the underlying iterator).
TEST_F(MemTableIteratorTest_357, ValidTracksUnderlyingChanges_357) {
  FakeTable table;

  // Start false
  table.valid_flag = false;
  MemTableIterator it = MakeIterator(&table);
  EXPECT_FALSE(it.Valid());

  // Flip to true
  table.valid_flag = true;
  EXPECT_TRUE(it.Valid());

  // Flip back to false
  table.valid_flag = false;
  EXPECT_FALSE(it.Valid());
}
