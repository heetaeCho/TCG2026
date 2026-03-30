#include <gtest/gtest.h>

#include "db/skiplist.h"



namespace leveldb {



class SkipListTest_95 : public ::testing::Test {

protected:

    using Key = int;

    class Comparator {

    public:

        bool operator()(const Key& a, const Key& b) const { return a < b; }

    };



    SkipList<Key, Comparator> skiplist_;

    typename SkipList<Key, Comparator>::Iterator it_;



    SkipListTest_95() : it_(&skiplist_) {}



    void SetUp() override {

        skiplist_.Insert(1);

        skiplist_.Insert(3);

        skiplist_.Insert(5);

        it_ = skiplist_.Begin();

    }

};



TEST_F(SkipListTest_95, IteratorValidAtStart_95) {

    EXPECT_TRUE(it_.Valid());

}



TEST_F(SkipListTest_95, IteratorKeyAtStart_95) {

    EXPECT_EQ(it_.key(), 1);

}



TEST_F(SkipListTest_95, IteratorNext_95) {

    it_.Next();

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 3);



    it_.Next();

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 5);



    it_.Next();

    EXPECT_FALSE(it_.Valid());

}



TEST_F(SkipListTest_95, IteratorPrev_95) {

    it_.SeekToLast();

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 5);



    it_.Prev();

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 3);



    it_.Prev();

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 1);



    it_.Prev();

    EXPECT_FALSE(it_.Valid());

}



TEST_F(SkipListTest_95, IteratorSeekToFirst_95) {

    it_.SeekToLast();

    it_.SeekToFirst();

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 1);

}



TEST_F(SkipListTest_95, IteratorSeekToLast_95) {

    it_.SeekToFirst();

    it_.SeekToLast();

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 5);

}



TEST_F(SkipListTest_95, IteratorSeekExactMatch_95) {

    it_.Seek(3);

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 3);

}



TEST_F(SkipListTest_95, IteratorSeekNoExactMatch_95) {

    it_.Seek(2);

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 3);



    it_.Seek(4);

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 5);

}



TEST_F(SkipListTest_95, IteratorSeekBeyondLast_95) {

    it_.Seek(6);

    EXPECT_FALSE(it_.Valid());

}



TEST_F(SkipListTest_95, IteratorSeekBeforeFirst_95) {

    it_.Seek(0);

    EXPECT_TRUE(it_.Valid());

    EXPECT_EQ(it_.key(), 1);

}



} // namespace leveldb
