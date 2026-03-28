#include <gtest/gtest.h>

#include "db/skiplist.h"

#include "util/comparator.h"



namespace leveldb {



class TestComparator : public Comparator {

public:

  int Compare(const Slice& a, const Slice& b) const override {

    return a.compare(b);

  }

  const char* Name() const override { return "TestComparator"; }

  void FindShortestSeparator(std::string*, const Slice&) const override {}

  void FindShortSuccessor(std::string*) const override {}

};



class SkipListTest_101 : public ::testing::Test {

protected:

  Arena arena;

  TestComparator cmp;

  SkipList<Slice, TestComparator> skiplist;



  SkipListTest_101() : skiplist(cmp, &arena) {}



  void CheckContains(const Slice& key, bool expected) {

    EXPECT_EQ(expected, skiplist.Contains(key)) << "Key: " << key.ToString();

  }

};



TEST_F(SkipListTest_101, InsertAndContainsBasic_101) {

  skiplist.Insert("key1");

  CheckContains("key1", true);

}



TEST_F(SkipListTest_101, InsertMultipleKeys_101) {

  skiplist.Insert("a");

  skiplist.Insert("b");

  skiplist.Insert("c");



  CheckContains("a", true);

  CheckContains("b", true);

  CheckContains("c", true);

}



TEST_F(SkipListTest_101, ContainsNonInsertedKey_101) {

  skiplist.Insert("key2");



  CheckContains("key3", false);

}



TEST_F(SkipListTest_101, BoundaryEmptyString_101) {

  skiplist.Insert("");



  CheckContains("", true);

}



TEST_F(SkipListTest_101, BoundaryLongKey_101) {

  std::string long_key(1024, 'a');

  skiplist.Insert(long_key);



  CheckContains(long_key, true);

}



} // namespace leveldb
