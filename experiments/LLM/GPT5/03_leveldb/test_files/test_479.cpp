// File: db/skiplist_constructor_test.cc

#include "gtest/gtest.h"
#include <functional>
#include <string>
#include <type_traits>

// Headers under test
#include "db/skiplist.h"
#include "util/arena.h"

namespace {

struct IntLess {
  bool operator()(const int& a, const int& b) const { return a < b; }
};

struct IntGreater {
  bool operator()(const int& a, const int& b) const { return a > b; }
};

struct StringLess {
  bool operator()(const std::string& a, const std::string& b) const { return a < b; }
};

} // namespace

// --- Construction smoke tests (normal operation) ---

TEST(SkipListCtorTest_479, ConstructWithStdLess_IntKey_479) {
  leveldb::Arena arena;
  // Construction should succeed without throwing or crashing.
  ASSERT_NO_FATAL_FAILURE({
    leveldb::SkipList<int, std::less<int>> list(std::less<int>{}, &arena);
    (void)list;  // unused
  });
}

TEST(SkipListCtorTest_479, ConstructWithCustomComparator_IntKey_479) {
  leveldb::Arena arena;
  ASSERT_NO_FATAL_FAILURE({
    leveldb::SkipList<int, IntGreater> list(IntGreater{}, &arena);
    (void)list;
  });
}

TEST(SkipListCtorTest_479, ConstructWithStringKey_479) {
  leveldb::Arena arena;
  ASSERT_NO_FATAL_FAILURE({
    leveldb::SkipList<std::string, StringLess> list(StringLess{}, &arena);
    (void)list;
  });
}

// --- Multiple independent constructions (boundary-ish: repeated use) ---

TEST(SkipListCtorTest_479, MultipleIndependentConstructions_479) {
  leveldb::Arena arena1;
  leveldb::Arena arena2;

  ASSERT_NO_FATAL_FAILURE({
    leveldb::SkipList<int, IntLess> list1(IntLess{}, &arena1);
    leveldb::SkipList<int, IntLess> list2(IntLess{}, &arena2);
    (void)list1;
    (void)list2;
  });
}

// --- Type traits (interface-level properties) ---

TEST(SkipListCtorTest_479, IsNotCopyConstructible_479) {
  // Copy construction is deleted in the interface.
  using SL = leveldb::SkipList<int, IntLess>;
  static_assert(!std::is_copy_constructible<SL>::value,
                "SkipList must not be copy-constructible");
  SUCCEED();
}

TEST(SkipListCtorTest_479, IsNotCopyAssignable_479) {
  // Copy assignment is deleted in the interface.
  using SL = leveldb::SkipList<int, IntLess>;
  static_assert(!std::is_copy_assignable<SL>::value,
                "SkipList must not be copy-assignable");
  SUCCEED();
}
