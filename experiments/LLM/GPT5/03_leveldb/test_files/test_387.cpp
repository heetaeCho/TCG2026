// File: table/merger_test.cc

#include "gtest/gtest.h"

#include "leveldb/iterator.h"
#include "leveldb/comparator.h"

// Some builds expose NewMergingIterator via a header; if not, declare it here.
namespace leveldb {
Iterator* NewMergingIterator(const Comparator* comparator, Iterator** children, int n);
}

// --- Minimal collaborators (black-box friendly stubs) ---

namespace leveldb {

// A minimal Comparator that satisfies the interface without asserting behavior.
class TestComparator final : public Comparator {
 public:
  ~TestComparator() override = default;

  // Return 0 for simplicity; tests below never rely on ordering semantics.
  int Compare(const Slice& a, const Slice& b) const override { return 0; }

  const char* Name() const override { return "TestComparator"; }

  void FindShortestSeparator(std::string* start, const Slice& limit) const override {}
  void FindShortSuccessor(std::string* key) const override {}
};

// A minimal Iterator that is always invalid; methods are no-ops.
// We only depend on the interface shape (e.g., pointer identity), not behavior.
class DummyIterator final : public Iterator {
 public:
  DummyIterator() = default;
  ~DummyIterator() override = default;

  bool Valid() const override { return false; }
  void SeekToFirst() override {}
  void SeekToLast() override {}
  void Seek(const Slice& /*target*/) override {}
  void Next() override {}
  void Prev() override {}
  Slice key() const override { return Slice(); }
  Slice value() const override { return Slice(); }
  Status status() const override { return Status(); }
};

}  // namespace leveldb

using namespace leveldb;

class NewMergingIteratorTest_387 : public ::testing::Test {
 protected:
  TestComparator cmp_;
};

// [Behavior] n == 0 → returns a non-null iterator representing "empty".
// We only assert non-null and that Valid() is false (observable via interface).
TEST_F(NewMergingIteratorTest_387, ReturnsEmptyIteratorWhenNoChildren_387) {
  Iterator* result = NewMergingIterator(&cmp_, /*children=*/nullptr, /*n=*/0);
  ASSERT_NE(result, nullptr);
  // Empty iterator should be invalid to begin with.
  EXPECT_FALSE(result->Valid());
  delete result;  // NewEmptyIterator() should be deletable by caller.
}

// [Behavior] n == 1 → returns the same pointer as children[0] (no wrapper).
TEST_F(NewMergingIteratorTest_387, ReturnsChildWhenSingle_387) {
  Iterator* child = new DummyIterator();
  Iterator* children[1] = {child};

  Iterator* result = NewMergingIterator(&cmp_, children, /*n=*/1);
  // Must be exactly the same pointer, not a new wrapper.
  EXPECT_EQ(result, child);

  // Caller should delete the returned iterator (which is the child).
  delete result;
}

// [Behavior] n >= 2 → returns a NEW iterator (wrapper/merging impl), not any child.
TEST_F(NewMergingIteratorTest_387, ReturnsNewIteratorWhenMultipleChildren_387) {
  Iterator* child0 = new DummyIterator();
  Iterator* child1 = new DummyIterator();
  Iterator* children[2] = {child0, child1};

  Iterator* result = NewMergingIterator(&cmp_, children, /*n=*/2);
  ASSERT_NE(result, nullptr);
  EXPECT_NE(result, child0);
  EXPECT_NE(result, child1);

  // IMPORTANT: Ownership of children for the merging case is implementation-defined.
  // To avoid double-deletes, only delete `result`. Implementations commonly take
  // ownership of children, but the test does not rely on that detail.
  delete result;
  // If your implementation does NOT take ownership of children, and you detect leaks,
  // move the deletes below the line above *and* remove the delete of `result`.
  // (We avoid assuming either ownership model per the constraints.)
  // delete child0;
  // delete child1;
}
