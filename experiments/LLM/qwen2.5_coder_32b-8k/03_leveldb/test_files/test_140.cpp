#include <gtest/gtest.h>

#include "db/version_set.h"



using namespace leveldb;



class LevelFileNumIteratorTest_140 : public ::testing::Test {

protected:

    InternalKeyComparator icmp;

    std::vector<FileMetaData*> flist;

    LevelFileNumIterator iterator;



    LevelFileNumIteratorTest_140() : iterator(icmp, &flist) {}

};



TEST_F(LevelFileNumIteratorTest_140, PrevDecrementsIndex_140) {

    flist.push_back(new FileMetaData);

    flist.push_back(new FileMetaData);

    iterator.SeekToLast();



    EXPECT_TRUE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 2);



    iterator.Prev();

    EXPECT_TRUE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 1);



    iterator.Prev();

    EXPECT_TRUE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 0);



    iterator.Prev(); // This should mark it as invalid

    EXPECT_FALSE(iterator.Valid());

}



TEST_F(LevelFileNumIteratorTest_140, PrevOnEmptyListDoesNothing_140) {

    iterator.SeekToLast();



    EXPECT_FALSE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 0);



    iterator.Prev();

    EXPECT_FALSE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 0);

}



TEST_F(LevelFileNumIteratorTest_140, PrevOnSingleElementListMarksAsInvalid_140) {

    flist.push_back(new FileMetaData);

    iterator.SeekToLast();



    EXPECT_TRUE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 1);



    iterator.Prev();

    EXPECT_FALSE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 0);

}



TEST_F(LevelFileNumIteratorTest_140, PrevBoundaryCondition_140) {

    flist.push_back(new FileMetaData);

    iterator.SeekToLast();



    EXPECT_TRUE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 1);



    iterator.Prev();

    EXPECT_FALSE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 0);

}



TEST_F(LevelFileNumIteratorTest_140, PrevOnAlreadyInvalidStateDoesNothing_140) {

    iterator.SeekToFirst(); // This should mark it as invalid since the list is empty



    EXPECT_FALSE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 0);



    iterator.Prev();

    EXPECT_FALSE(iterator.Valid());

    EXPECT_EQ(iterator.index_, 0);

}
