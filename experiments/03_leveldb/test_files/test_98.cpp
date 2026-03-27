#include "gtest/gtest.h"

#include "db/skiplist.h"



using namespace leveldb;



class ComparatorMock : public Comparator {

public:

    MOCK_CONST_METHOD2(Compare, int(const Key& a, const Key& b));

};



class ArenaMock : public Arena {

public:

    MOCK_METHOD1(AllocateAligned, char*(size_t bytes));

};



template <typename Key, typename Comparator>

class SkipListTest : public ::testing::Test {

protected:

    SkipList<Key, Comparator> skiplist_;

    ArenaMock arena_mock_;

    ComparatorMock comparator_mock_;



    SkipListTest() : skiplist_(comparator_mock_, &arena_mock_) {}



    void InsertKeys(const std::vector<Key>& keys) {

        for (const auto& key : keys) {

            skiplist_.Insert(key);

        }

    }

};



using Key = int;



typedef SkipListTest<Key, ComparatorMock> SkipListTest_98;



TEST_F(SkipListTest_98, InsertAndContains_NormalOperation_98) {

    skiplist_.Insert(10);

    EXPECT_TRUE(skiplist_.Contains(10));

}



TEST_F(SkipListTest_98, Contains_ReturnsFalseForNonExistentKey_98) {

    EXPECT_FALSE(skiplist_.Contains(5));

}



TEST_F(SkipListTest_98, Iterator_SeekToFirst_NormalOperation_98) {

    InsertKeys({10, 20, 30});

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.SeekToFirst();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(10, it.key());

}



TEST_F(SkipListTest_98, Iterator_SeekToLast_NormalOperation_98) {

    InsertKeys({10, 20, 30});

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.SeekToLast();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(30, it.key());

}



TEST_F(SkipListTest_98, Iterator_Seek_NormalOperation_98) {

    InsertKeys({10, 20, 30});

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.Seek(20);

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(20, it.key());

}



TEST_F(SkipListTest_98, Iterator_Seek_OutOfBounds_98) {

    InsertKeys({10, 20, 30});

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.Seek(40);

    EXPECT_FALSE(it.Valid());

}



TEST_F(SkipListTest_98, Iterator_Next_NormalOperation_98) {

    InsertKeys({10, 20, 30});

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.SeekToFirst();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(10, it.key());

    it.Next();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(20, it.key());

}



TEST_F(SkipListTest_98, Iterator_Prev_NormalOperation_98) {

    InsertKeys({10, 20, 30});

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.SeekToLast();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(30, it.key());

    it.Prev();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(20, it.key());

}



TEST_F(SkipListTest_98, Iterator_Next_OutOfBounds_98) {

    InsertKeys({10});

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.SeekToFirst();

    EXPECT_TRUE(it.Valid());

    it.Next();

    EXPECT_FALSE(it.Valid());

}



TEST_F(SkipListTest_98, Iterator_Prev_OutOfBounds_98) {

    InsertKeys({10});

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.SeekToFirst();

    EXPECT_TRUE(it.Valid());

    it.Prev();

    EXPECT_FALSE(it.Valid());

}



TEST_F(SkipListTest_98, Iterator_Seek_EmptyList_98) {

    SkipList<int, ComparatorMock>::Iterator it(&skiplist_);

    it.Seek(10);

    EXPECT_FALSE(it.Valid());

}



TEST_F(SkipListTest_98, Insert_MultipleKeys_NormalOperation_98) {

    InsertKeys({5, 15, 25, 35});

    EXPECT_TRUE(skiplist_.Contains(5));

    EXPECT_TRUE(skiplist_.Contains(15));

    EXPECT_TRUE(skiplist_.Contains(25));

    EXPECT_TRUE(skiplist_.Contains(35));

}
