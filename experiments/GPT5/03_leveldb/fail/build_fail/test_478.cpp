// File: skiplist_iterator_test_478.cc
#include <gtest/gtest.h>

// The headers are partial; to keep the tests strictly black-box and
// avoid depending on unprovided internals (Arena, Node, etc.),
// we forward-declare the template and nested Iterator per the interface.
namespace leveldb {

template <typename Key, typename Comparator>
class SkipList {
 public:
  class Iterator {
   public:
    // We only need the constructor + Valid() as exposed in the snippets.
    explicit Iterator(const SkipList* list);
    bool Valid() const;
    // Other methods exist but are not used here to avoid depending on
    // unprovided implementation details.
  };
};

}  // namespace leveldb

// ---------- Test Fixture ----------
class SkipListIteratorTest_478 : public ::testing::Test {
 protected:
  // We use a minimal key/compare type to instantiate the template.
  struct IntCmp {
    int operator()(int a, int b) const {
      if (a < b) return -1;
      if (a > b) return 1;
      return 0;
    }
  };
  using List    = leveldb::SkipList<int, IntCmp>;
  using Iterator = typename List::Iterator;
};

// [Behavior Under Test]
// Iterator constructed with the given list pointer initializes in an invalid state
// because the constructor explicitly sets node_ to nullptr in the provided code snippet.

// TEST 1: Construction with nullptr list should not crash and should be invalid.
TEST_F(SkipListIteratorTest_478, ConstructWithNullList_IsInvalid_478) {
  const List* null_list = nullptr;

  // The constructor in the snippet stores the list pointer and sets node_ = nullptr.
  // This should be safe even if list is nullptr, and Valid() should report false.
  Iterator it(null_list);

  // Observable behavior: invalid immediately after construction.
  // (This aligns with node_ == nullptr from the provided constructor snippet.)
  EXPECT_FALSE(it.Valid());
}

// TEST 2: Construction with a non-null dummy pointer should still be invalid initially.
// We cannot instantiate a real SkipList due to missing dependencies (Arena, etc.).
// Instead, we use a non-null pointer value without dereferencing it; this is sufficient
// because the provided constructor does not dereference the list pointer.
TEST_F(SkipListIteratorTest_478, ConstructWithNonNullPointer_IsInvalid_478) {
  // Create a dummy, opaque address by reusing the null pointer then offsetting via cast.
  // We will NOT dereference it; it merely simulates a non-null list address.
  const auto dummy_addr = reinterpret_cast<const List*>(0x1);

  Iterator it(dummy_addr);
  EXPECT_FALSE(it.Valid());
}

// TEST 3: Multiple iterators constructed from different list pointers (including nullptr)
// should each start invalid; constructing them should not affect each other (no shared state assumed).
TEST_F(SkipListIteratorTest_478, MultipleIndependentIterators_StartInvalid_478) {
  const List* null_list = nullptr;
  const auto dummy_addr1 = reinterpret_cast<const List*>(0x11);
  const auto dummy_addr2 = reinterpret_cast<const List*>(0x22);

  Iterator it_null(null_list);
  Iterator it_a(dummy_addr1);
  Iterator it_b(dummy_addr2);

  EXPECT_FALSE(it_null.Valid());
  EXPECT_FALSE(it_a.Valid());
  EXPECT_FALSE(it_b.Valid());
}
