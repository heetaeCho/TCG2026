#include "db/skiplist.h"

#include <gtest/gtest.h>

#include <string>



// Mock Comparator for testing purposes

class MockComparator {

public:

    bool operator()(const std::string& a, const std::string& b) const {

        return a < b;

    }

};



class SkipListTest_96 : public ::testing::Test {

protected:

    leveldb::SkipList<std::string, MockComparator> skiplist_;

    MockComparator comparator_;



    void SetUp() override {

        // Initialize the skiplist with some elements for testing

        skiplist_.Insert("key1");

        skiplist_.Insert("key2");

        skiplist_.Insert("key3");

    }

};



TEST_F(SkipListTest_96, IteratorStartsInvalidWhenEmpty_96) {

    leveldb::SkipList<std::string, MockComparator> empty_skiplist;

    leveldb::SkipList<std::string, MockComparator>::Iterator iter(&empty_skiplist);

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_96, IteratorStartsValidAfterSeekToFirst_96) {

    leveldb::SkipList<std::string, MockComparator>::Iterator iter(&skiplist_);

    iter.SeekToFirst();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key1", iter.key());

}



TEST_F(SkipListTest_96, IteratorStartsValidAfterSeekToLast_96) {

    leveldb::SkipList<std::string, MockComparator>::Iterator iter(&skiplist_);

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key3", iter.key());

}



TEST_F(SkipListTest_96, IteratorNextTraversesCorrectly_96) {

    leveldb::SkipList<std::string, MockComparator>::Iterator iter(&skiplist_);

    iter.SeekToFirst();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key1", iter.key());



    iter.Next();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key2", iter.key());



    iter.Next();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key3", iter.key());



    iter.Next();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_96, IteratorSeekFindsKey_96) {

    leveldb::SkipList<std::string, MockComparator>::Iterator iter(&skiplist_);

    iter.Seek("key2");

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key2", iter.key());



    iter.Seek("key3");

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key3", iter.key());



    iter.Seek("key1");

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key1", iter.key());

}



TEST_F(SkipListTest_96, IteratorSeekToNonExistentKeyGoesToNextHigher_96) {

    leveldb::SkipList<std::string, MockComparator>::Iterator iter(&skiplist_);

    iter.Seek("key2.5");

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key3", iter.key());



    iter.Seek("key0");

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key1", iter.key());



    iter.Seek("key4");

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_96, IteratorBoundaryConditions_96) {

    leveldb::SkipList<std::string, MockComparator>::Iterator iter(&skiplist_);

    

    // Seek to first and check boundaries

    iter.SeekToFirst();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key1", iter.key());



    iter.Prev();

    EXPECT_FALSE(iter.Valid());



    // Seek to last and check boundaries

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ("key3", iter.key());



    iter.Next();

    EXPECT_FALSE(iter.Valid());

}
