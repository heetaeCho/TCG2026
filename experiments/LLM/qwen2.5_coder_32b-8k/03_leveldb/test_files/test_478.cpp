#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "db/skiplist.h"



namespace leveldb {

class MockComparator {

public:

    MOCK_METHOD2(Compare, int(const Key& a, const Key& b));

};



class SkipListTest_478 : public ::testing::Test {

protected:

    MockComparator mock_comparator;

    Arena arena;

    SkipList<Key, MockComparator> skiplist;



    SkipListTest_478() : skiplist(mock_comparator, &arena) {}

};



TEST_F(SkipListTest_478, InsertAndContains_NormalOperation_478) {

    Key key1 = "key1";

    Key key2 = "key2";



    EXPECT_CALL(mock_comparator, Compare(key1, _)).WillOnce(::testing::Return(-1));

    skiplist.Insert(key1);



    EXPECT_TRUE(skiplist.Contains(key1));



    EXPECT_CALL(mock_comparator, Compare(key2, _)).WillOnce(::testing::Return(1));

    skiplist.Insert(key2);



    EXPECT_TRUE(skiplist.Contains(key2));

}



TEST_F(SkipListTest_478, Insert_DuplicateKey_478) {

    Key key = "key";



    EXPECT_CALL(mock_comparator, Compare(key, _)).WillOnce(::testing::Return(-1));

    skiplist.Insert(key);



    EXPECT_CALL(mock_comparator, Compare(key, _)).WillOnce(::testing::Return(0));

    skiplist.Insert(key); // Inserting the same key again



    EXPECT_TRUE(skiplist.Contains(key));

}



TEST_F(SkipListTest_478, Contains_EmptyList_478) {

    Key key = "key";



    EXPECT_CALL(mock_comparator, Compare(_, _)).Times(0);

    EXPECT_FALSE(skiplist.Contains(key));

}



TEST_F(SkipListTest_478, Iterator_SeekToFirst_478) {

    Key key1 = "key1";

    Key key2 = "key2";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    skiplist.Insert(key1);



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(1));

    skiplist.Insert(key2);



    SkipList<Key, MockComparator>::Iterator iter(&skiplist);

    iter.SeekToFirst();



    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(key1, iter.key());



    iter.Next();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(key2, iter.key());

}



TEST_F(SkipListTest_478, Iterator_SeekToLast_478) {

    Key key1 = "key1";

    Key key2 = "key2";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    skiplist.Insert(key1);



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(1));

    skiplist.Insert(key2);



    SkipList<Key, MockComparator>::Iterator iter(&skiplist);

    iter.SeekToLast();



    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(key2, iter.key());



    iter.Prev();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(key1, iter.key());

}



TEST_F(SkipListTest_478, Iterator_Seek_ValidKey_478) {

    Key key1 = "key1";

    Key key2 = "key2";

    Key target = "key1";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    skiplist.Insert(key1);



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(1));

    skiplist.Insert(key2);



    SkipList<Key, MockComparator>::Iterator iter(&skiplist);

    iter.Seek(target);



    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(key1, iter.key());

}



TEST_F(SkipListTest_478, Iterator_Seek_MissingKey_478) {

    Key key1 = "key1";

    Key key2 = "key2";

    Key target = "key3";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    skiplist.Insert(key1);



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(1));

    skiplist.Insert(key2);



    SkipList<Key, MockComparator>::Iterator iter(&skiplist);

    iter.Seek(target);



    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_478, Iterator_Next_BoundaryConditions_478) {

    Key key1 = "key1";

    Key key2 = "key2";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    skiplist.Insert(key1);



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(1));

    skiplist.Insert(key2);



    SkipList<Key, MockComparator>::Iterator iter(&skiplist);

    iter.SeekToFirst();



    EXPECT_TRUE(iter.Valid());

    iter.Next();

    EXPECT_TRUE(iter.Valid());



    iter.Next();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_478, Iterator_Prev_BoundaryConditions_478) {

    Key key1 = "key1";

    Key key2 = "key2";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    skiplist.Insert(key1);



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(1));

    skiplist.Insert(key2);



    SkipList<Key, MockComparator>::Iterator iter(&skiplist);

    iter.SeekToLast();



    EXPECT_TRUE(iter.Valid());

    iter.Prev();

    EXPECT_TRUE(iter.Valid());



    iter.Prev();

    EXPECT_FALSE(iter.Valid());

}



}  // namespace leveldb
