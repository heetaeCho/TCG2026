// File: memtable_iterator_prev_test.cc
#include <gtest/gtest.h>

//
// Minimal fakes to observe external interactions.
// These live in the same namespace/types that the CUT expects,
// but only provide what's necessary for compilation & verification.
//
namespace leveldb {

// Forward declaration of the class under test so we can construct it.
class MemTableIterator;

// Fake MemTable and nested Table::Iterator collaborator to observe calls.
struct MemTable {
  struct Table {
    // Count how many times Prev() is invoked on the underlying iterator.
    int prev_calls = 0;

    struct Iterator {
      explicit Iterator(Table* t) : table_(t) {}
      void Prev() { if (table_) table_->prev_calls++; }

     private:
      Table* table_;
    };
  };
};

// Forward declare only the bits of MemTableIterator we use in the tests.
// The real definitions are provided by the production unit being tested.
class MemTableIterator {
 public:
  explicit MemTableIterator(MemTable::Table* table);
  void Prev();
};

}  // namespace leveldb

using leveldb::MemTable;

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

// Verifies that a single call to MemTableIterator::Prev() delegates exactly once
// to the underlying collaborator's Prev().
TEST(MemTableIteratorTest_362, PrevDelegatesOnce_362) {
  MemTable::Table table;                // fake external collaborator
  leveldb::MemTableIterator it(&table); // construct CUT with collaborator

  EXPECT_EQ(table.prev_calls, 0);
  it.Prev();
  EXPECT_EQ(table.prev_calls, 1);
}

// Verifies that multiple calls to MemTableIterator::Prev() delegate one-for-one
// to the underlying collaborator.
TEST(MemTableIteratorTest_362, PrevDelegatesMultipleTimes_362) {
  MemTable::Table table;
  leveldb::MemTableIterator it(&table);

  for (int i = 1; i <= 5; ++i) {
    it.Prev();
    EXPECT_EQ(table.prev_calls, i) << "Prev() should delegate exactly once per call";
  }
}
