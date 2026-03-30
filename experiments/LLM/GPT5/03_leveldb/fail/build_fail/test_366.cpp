// File: db/memtable_newiterator_test.cc
#include "db/memtable.h"
#include "db/dbformat.h"
#include "util/coding.h"
#include "gtest/gtest.h"

namespace leveldb {

class MemTableNewIteratorTest_366 : public ::testing::Test {
protected:
  // Helper: create a fresh MemTable for each test
  std::unique_ptr<MemTable> NewMemTable() {
    InternalKeyComparator ikc(BytewiseComparator());
    return std::unique_ptr<MemTable>(new MemTable(ikc));
  }

  // Helper: add a single put (value) entry
  void Put(MemTable* mem, SequenceNumber seq, const std::string& user_key,
           const std::string& value) {
    mem->Add(seq, kTypeValue, Slice(user_key), Slice(value));
  }
};

// --- Tests ---

// 1) Basic: NewIterator returns a non-null, usable Iterator
TEST_F(MemTableNewIteratorTest_366, NewIteratorReturnsNonNull_366) {
  auto mem = NewMemTable();

  std::unique_ptr<Iterator> it(mem->NewIterator());
  EXPECT_NE(it.get(), nullptr);

  // Newly created iterator should be invalid until positioned by Seek/SeekToFirst
  EXPECT_FALSE(it->Valid());
  // status() should be OK on a fresh iterator
  EXPECT_TRUE(it->status().ok());
}

// 2) Empty table: seeking should leave iterator invalid
TEST_F(MemTableNewIteratorTest_366, EmptyTableIterationIsInvalid_366) {
  auto mem = NewMemTable();
  std::unique_ptr<Iterator> it(mem->NewIterator());

  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());

  it->SeekToLast();
  EXPECT_FALSE(it->Valid());

  it->Seek(Slice("non-existent"));
  EXPECT_FALSE(it->Valid());

  // Next/Prev on invalid shouldn't crash; remain invalid
  it->Next();
  EXPECT_FALSE(it->Valid());
  it->Prev();
  EXPECT_FALSE(it->Valid());

  EXPECT_TRUE(it->status().ok());
}

// 3) After inserts: iterator can traverse exactly the number of inserted entries
// (We do NOT assert any ordering details; we only assert count and that keys/values are retrievable.)
TEST_F(MemTableNewIteratorTest_366, IterateCountMatchesAdds_366) {
  auto mem = NewMemTable();

  // Insert three entries with distinct user keys
  Put(mem.get(), /*seq=*/1, "a", "va");
  Put(mem.get(), /*seq=*/2, "b", "vb");
  Put(mem.get(), /*seq=*/3, "c", "vc");

  std::unique_ptr<Iterator> it(mem->NewIterator());
  it->SeekToFirst();

  size_t seen = 0;
  for (; it->Valid(); it->Next()) {
    // We only check that key() and value() are accessible while Valid()
    Slice k = it->key();
    Slice v = it->value();
    EXPECT_GT(k.size(), 0u);  // internal keys are non-empty
    // value should also be non-empty for kTypeValue entries
    EXPECT_GT(v.size(), 0u);
    seen++;
  }

  EXPECT_EQ(seen, 3u);
  EXPECT_TRUE(it->status().ok());
}

// 4) Iterator independence: two iterators over the same MemTable
//    should not affect each other's position/state.
TEST_F(MemTableNewIteratorTest_366, IteratorsAreIndependent_366) {
  auto mem = NewMemTable();

  Put(mem.get(), /*seq=*/10, "k1", "v1");
  Put(mem.get(), /*seq=*/20, "k2", "v2");
  Put(mem.get(), /*seq=*/30, "k3", "v3");

  std::unique_ptr<Iterator> it1(mem->NewIterator());
  std::unique_ptr<Iterator> it2(mem->NewIterator());

  it1->SeekToFirst();
  it2->SeekToFirst();

  ASSERT_TRUE(it1->Valid());
  ASSERT_TRUE(it2->Valid());

  // Capture the first key observed by it2
  std::string it2_first_key = it2->key().ToString();

  // Move only it1 forward
  it1->Next();

  // it2 should remain at its own position (first)
  ASSERT_TRUE(it2->Valid());
  EXPECT_EQ(it2->key().ToString(), it2_first_key);

  // Further advance it1 without changing it2
  it1->Next();
  ASSERT_TRUE(it2->Valid());
  EXPECT_EQ(it2->key().ToString(), it2_first_key);

  EXPECT_TRUE(it1->status().ok());
  EXPECT_TRUE(it2->status().ok());
}

// 5) Creating an iterator before/after inserts: both should be usable.
//    We do not enforce visibility guarantees; we only assert that both iterators are valid
//    and can iterate when positioned.
TEST_F(MemTableNewIteratorTest_366, IteratorsUsableRegardlessOfCreationTime_366) {
  auto mem = NewMemTable();

  // Create iterator #1 before any inserts
  std::unique_ptr<Iterator> it_before(mem->NewIterator());

  // Add data
  Put(mem.get(), 1, "x", "vx");
  Put(mem.get(), 2, "y", "vy");

  // Create iterator #2 after inserts
  std::unique_ptr<Iterator> it_after(mem->NewIterator());

  // Both should function when (re)positioned
  it_before->SeekToFirst();
  size_t count_before = 0;
  for (; it_before->Valid(); it_before->Next()) count_before++;

  it_after->SeekToFirst();
  size_t count_after = 0;
  for (; it_after->Valid(); it_after->Next()) count_after++;

  // At minimum, the iterator created after inserts should see the two entries.
  EXPECT_EQ(count_after, 2u);

  // We don't *require* a specific snapshot policy here; we only assert that
  // iterators are usable. So the "before" iterator must not crash and will
  // produce a finite count (possibly 0 or 2 depending on implementation).
  EXPECT_LE(count_before, 2u);

  EXPECT_TRUE(it_before->status().ok());
  EXPECT_TRUE(it_after->status().ok());
}

}  // namespace leveldb
