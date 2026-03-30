#include <gtest/gtest.h>

#include "db/skiplist.h"

#include <string>



using namespace leveldb;



class StringComparator {

public:

    int operator()(const std::string& a, const std::string& b) const {

        return a.compare(b);

    }

};



class SkipListTest_97 : public ::testing::Test {

protected:

    Arena arena;

    StringComparator comparator;

    SkipList<std::string, StringComparator> skiplist;



    SkipListTest_97() : skiplist(comparator, &arena) {}



    void InsertKeys(const std::vector<std::string>& keys) {

        for (const auto& key : keys) {

            skiplist.Insert(key);

        }

    }



    SkipList<std::string, StringComparator>::Iterator CreateIterator() {

        return skiplist.Iterator(&skiplist);

    }

};



TEST_F(SkipListTest_97, EmptySkiplistIteratorInvalid_97) {

    auto it = CreateIterator();

    EXPECT_FALSE(it.Valid());

}



TEST_F(SkipListTest_97, SingleElementInsertAndRetrieve_97) {

    skiplist.Insert("key1");

    auto it = CreateIterator();

    it.SeekToFirst();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key1");

}



TEST_F(SkipListTest_97, MultipleElementsInsertAndIterateInOrder_97) {

    std::vector<std::string> keys = {"key2", "key1", "key3"};

    InsertKeys(keys);

    auto it = CreateIterator();

    it.SeekToFirst();



    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key1");

    it.Next();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key2");

    it.Next();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key3");

    it.Next();

    EXPECT_FALSE(it.Valid());

}



TEST_F(SkipListTest_97, SeekToKeyInSkiplist_97) {

    std::vector<std::string> keys = {"key2", "key1", "key3"};

    InsertKeys(keys);

    auto it = CreateIterator();



    it.Seek("key2");

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key2");



    it.Seek("key4");  // Non-existent key

    EXPECT_FALSE(it.Valid());



    it.SeekToFirst();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key1");

}



TEST_F(SkipListTest_97, PrevNavigation_97) {

    std::vector<std::string> keys = {"key2", "key1", "key3"};

    InsertKeys(keys);

    auto it = CreateIterator();

    it.SeekToLast();



    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key3");

    it.Prev();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key2");

    it.Prev();

    EXPECT_TRUE(it.Valid());

    EXPECT_EQ(it.key(), "key1");

    it.Prev();

    EXPECT_FALSE(it.Valid());

}



TEST_F(SkipListTest_97, IteratorBoundaryConditions_97) {

    std::vector<std::string> keys = {"key2", "key1"};

    InsertKeys(keys);

    auto it = CreateIterator();



    it.SeekToFirst();

    EXPECT_TRUE(it.Valid());

    it.Prev();  // Invalidates iterator

    EXPECT_FALSE(it.Valid());



    it.Seek("key3");  // Non-existent key, should invalidate iterator

    EXPECT_FALSE(it.Valid());



    it.SeekToLast();

    EXPECT_TRUE(it.Valid());

    it.Next();  // Invalidates iterator as we are beyond the last element

    EXPECT_FALSE(it.Valid());

}



TEST_F(SkipListTest_97, ContainsKeyInSkiplist_97) {

    std::vector<std::string> keys = {"key2", "key1"};

    InsertKeys(keys);



    EXPECT_TRUE(skiplist.Contains("key1"));

    EXPECT_TRUE(skiplist.Contains("key2"));

    EXPECT_FALSE(skiplist.Contains("key3"));  // Non-existent key

}
