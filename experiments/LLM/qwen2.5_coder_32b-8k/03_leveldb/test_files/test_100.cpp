#include "gtest/gtest.h"

#include "db/skiplist.h"

#include <string>



using namespace leveldb;



class SkipListTest_100 : public ::testing::Test {

protected:

    struct Comparator {

        int Compare(const std::string& a, const std::string& b) const {

            return a.compare(b);

        }

        bool Equal(const std::string& a, const std::string& b) const {

            return a == b;

        }

    };



    Arena arena_;

    Comparator cmp_;

    SkipList<std::string, Comparator> skiplist_;



    SkipListTest_100() : skiplist_(cmp_, &arena_) {}

};



TEST_F(SkipListTest_100, InsertAndContains_100) {

    skiplist_.Insert("key1");

    EXPECT_TRUE(skiplist_.Contains("key1"));

    EXPECT_FALSE(skiplist_.Contains("key2"));

}



TEST_F(SkipListTest_100, IteratorSeekToLastEmptyList_100) {

    SkipList<std::string, Comparator>::Iterator iter(&skiplist_);

    iter.SeekToLast();

    EXPECT_FALSE(iter.Valid());

}



TEST_F(SkipListTest_100, IteratorSeekToLastSingleElement_100) {

    skiplist_.Insert("key1");

    SkipList<std::string, Comparator>::Iterator iter(&skiplist_);

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key1");

}



TEST_F(SkipListTest_100, IteratorSeekToLastMultipleElements_100) {

    skiplist_.Insert("key1");

    skiplist_.Insert("key2");

    skiplist_.Insert("key3");

    SkipList<std::string, Comparator>::Iterator iter(&skiplist_);

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key3");

}



TEST_F(SkipListTest_100, IteratorSeekToLastAfterRemovals_100) {

    skiplist_.Insert("key1");

    skiplist_.Insert("key2");

    SkipList<std::string, Comparator>::Iterator iter(&skiplist_);

    iter.SeekToFirst();

    iter.Next(); // Position at key2

    skiplist_.Insert("key3"); // Insert after current position

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key3");

}



TEST_F(SkipListTest_100, IteratorSeekToLastBoundaryConditions_100) {

    SkipList<std::string, Comparator>::Iterator iter(&skiplist_);

    iter.SeekToFirst(); // On empty list

    EXPECT_FALSE(iter.Valid());

    iter.SeekToLast();  // Still on empty list

    EXPECT_FALSE(iter.Valid());



    skiplist_.Insert("key1");

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key1");



    iter.Prev();

    EXPECT_FALSE(iter.Valid()); // Move out of bounds

}



TEST_F(SkipListTest_100, IteratorSeekToLastMultipleSeeks_100) {

    skiplist_.Insert("key1");

    skiplist_.Insert("key2");

    SkipList<std::string, Comparator>::Iterator iter(&skiplist_);

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key2");



    iter.Prev();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key1");



    iter.Next();

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key2");



    iter.SeekToLast(); // Seek again

    EXPECT_TRUE(iter.Valid());

    EXPECT_EQ(iter.key(), "key2");

}
