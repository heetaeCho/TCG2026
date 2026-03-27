#include <gtest/gtest.h>

#include "db/skiplist.h"



namespace leveldb {



class SkipListTest_99 : public ::testing::Test {

protected:

    class MockComparator {

    public:

        MOCK_METHOD2(Compare, int(const std::string& a, const std::string& b));

    };



    Arena arena;

    MockComparator comparator;

    SkipList<std::string, MockComparator> skip_list;



    SkipListTest_99() : skip_list(comparator, &arena) {}

};



TEST_F(SkipListTest_99, InsertAndContains_NormalOperation_99) {

    EXPECT_FALSE(skip_list.Contains("key1"));

    skip_list.Insert("key1");

    EXPECT_TRUE(skip_list.Contains("key1"));

}



TEST_F(SkipListTest_99, Iterator_SeekToFirst_OnEmptyList_99) {

    SkipList<std::string, MockComparator>::Iterator iter(&skip_list);

    iter.SeekToFirst();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_99, Iterator_SeekToFirst_AfterInsertion_99) {

    skip_list.Insert("key1");

    SkipList<std::string, MockComparator>::Iterator iter(&skip_list);

    iter.SeekToFirst();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key1");

}



TEST_F(SkipListTest_99, Iterator_SeekToLast_OnEmptyList_99) {

    SkipList<std::string, MockComparator>::Iterator iter(&skip_list);

    iter.SeekToLast();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_99, Iterator_SeekToLast_AfterInsertion_99) {

    skip_list.Insert("key1");

    skip_list.Insert("key2");

    SkipList<std::string, MockComparator>::Iterator iter(&skip_list);

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key2");

}



TEST_F(SkipListTest_99, Iterator_Seek_ValidKey_99) {

    skip_list.Insert("key1");

    skip_list.Insert("key3");

    SkipList<std::string, MockComparator>::Iterator iter(&skip_list);

    iter.Seek("key2");

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key3");

}



TEST_F(SkipListTest_99, Iterator_Seek_OutOfBoundsKey_99) {

    skip_list.Insert("key1");

    skip_list.Insert("key2");

    SkipList<std::string, MockComparator>::Iterator iter(&skip_list);

    iter.Seek("key3");

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_99, Iterator_Next_PastEnd_99) {

    skip_list.Insert("key1");

    SkipList<std::string, MockComparator>::Iterator iter(&skip_list);

    iter.SeekToFirst();

    iter.Next();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_99, Iterator_Prev_BeforeStart_99) {

    skip_list.Insert("key1");

    SkipList<std::string, MockComparator>::Iterator iter(&skip_list);

    iter.SeekToLast();

    iter.Prev();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key1");

    iter.Prev();

    EXPECT_FALSE(iter.Valid());

}



}  // namespace leveldb
