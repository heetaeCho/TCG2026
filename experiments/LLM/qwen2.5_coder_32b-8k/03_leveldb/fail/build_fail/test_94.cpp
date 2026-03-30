#include <gtest/gtest.h>

#include "db/skiplist.h"



namespace leveldb {



class SkipListTest_94 : public ::testing::Test {

protected:

    using Comparator = int; // Assuming a simple integer comparator for testing purposes

    SkipList<Comparator, Comparator> skiplist;

    typename SkipList<Comparator, Comparator>::Iterator iter;



    SkipListTest_94() : iter(&skiplist) {}

};



TEST_F(SkipListTest_94, IteratorInitiallyInvalid_94) {

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_94, SeekToFirstOnEmptyList_94) {

    iter.SeekToFirst();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_94, SeekToLastOnEmptyList_94) {

    iter.SeekToLast();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_94, NextOnEmptyList_94) {

    iter.Next();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_94, PrevOnEmptyList_94) {

    iter.Prev();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_94, SeekOnEmptyList_94) {

    iter.Seek(0);

    EXPECT_FALSE(iter.Valid());

}



// Assuming some insertions are possible to test further behaviors

class SkipListWithElementsTest_94 : public SkipListTest_94 {

protected:

    SkipListWithElementsTest_94() {

        skiplist.Insert(10);

        skiplist.Insert(20);

        skiplist.Insert(30);

    }

};



TEST_F(SkipListWithElementsTest_94, SeekToFirstValid_94) {

    iter.SeekToFirst();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(10, iter.key());

}



TEST_F(SkipListWithElementsTest_94, SeekToLastValid_94) {

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(30, iter.key());

}



TEST_F(SkipListWithElementsTest_94, SeekValid_94) {

    iter.Seek(20);

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(20, iter.key());

}



TEST_F(SkipListWithElementsTest_94, SeekToNonExistentKey_94) {

    iter.Seek(15);

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(20, iter.key());



    iter.Seek(25);

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(30, iter.key());

}



TEST_F(SkipListWithElementsTest_94, NextIteration_94) {

    iter.SeekToFirst();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(10, iter.key());



    iter.Next();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(20, iter.key());



    iter.Next();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(30, iter.key());



    iter.Next();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListWithElementsTest_94, PrevIteration_94) {

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(30, iter.key());



    iter.Prev();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(20, iter.key());



    iter.Prev();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(10, iter.key());



    iter.Prev();

    EXPECT_FALSE(iter.Valid());

}



} // namespace leveldb
