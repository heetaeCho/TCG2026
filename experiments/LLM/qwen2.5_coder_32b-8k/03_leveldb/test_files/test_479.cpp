#include <gtest/gtest.h>

#include "db/skiplist.h"

#include "util/arena.h"



namespace leveldb {



class ComparatorMock : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Key& a, const Key& b));

    MOCK_CONST_METHOD1(Name, const char*());

};



class SkipListTest_479 : public ::testing::Test {

protected:

    Arena arena;

    ComparatorMock comparator;

    SkipList<int, ComparatorMock> skiplist;



    SkipListTest_479() : skiplist(comparator, &arena) {}

};



TEST_F(SkipListTest_479, InsertAndContains_NormalOperation_479) {

    skiplist.Insert(10);

    EXPECT_TRUE(skiplist.Contains(10));

}



TEST_F(SkipListTest_479, Contains_NonInsertedKey_ReturnsFalse_479) {

    EXPECT_FALSE(skiplist.Contains(20));

}



TEST_F(SkipListTest_479, Insert_MultipleKeys_479) {

    skiplist.Insert(5);

    skiplist.Insert(15);

    skiplist.Insert(25);



    EXPECT_TRUE(skiplist.Contains(5));

    EXPECT_TRUE(skiplist.Contains(15));

    EXPECT_TRUE(skiplist.Contains(25));

}



TEST_F(SkipListTest_479, Insert_DuplicateKey_Idempotent_479) {

    skiplist.Insert(30);

    skiplist.Insert(30);



    EXPECT_EQ(1, static_cast<int>(skiplist.Contains(30)));

}



TEST_F(SkipListTest_479, Contains_BoundaryCondition_LowerBound_479) {

    skiplist.Insert(INT_MIN);

    EXPECT_TRUE(skiplist.Contains(INT_MIN));

}



TEST_F(SkipListTest_479, Contains_BoundaryCondition_UpperBound_479) {

    skiplist.Insert(INT_MAX);

    EXPECT_TRUE(skiplist.Contains(INT_MAX));

}



}  // namespace leveldb
