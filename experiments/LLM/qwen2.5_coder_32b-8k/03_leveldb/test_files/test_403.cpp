#include <gtest/gtest.h>

#include "table/iterator.h"

#include "leveldb/status.h"



namespace leveldb {



class IteratorTest_403 : public ::testing::Test {

protected:

    void SetUp() override {

        iterator = NewEmptyIterator();

    }



    void TearDown() override {

        delete iterator;

    }



    Iterator* iterator;

};



TEST_F(IteratorTest_403, ValidReturnsFalseInitially_403) {

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(IteratorTest_403, StatusIsOkInitially_403) {

    EXPECT_TRUE(iterator->status().ok());

}



TEST_F(IteratorTest_403, SeekToFirstDoesNothing_403) {

    iterator->SeekToFirst();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(IteratorTest_403, SeekToLastDoesNothing_403) {

    iterator->SeekToLast();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(IteratorTest_403, SeekWithKeyDoesNothing_403) {

    iterator->Seek("some_key");

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(IteratorTest_403, NextDoesNothing_403) {

    iterator->Next();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(IteratorTest_403, PrevDoesNothing_403) {

    iterator->Prev();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(IteratorTest_403, KeyReturnsEmptySliceWhenInvalid_403) {

    EXPECT_TRUE(iterator->key().empty());

}



TEST_F(IteratorTest_403, ValueReturnsEmptySliceWhenInvalid_403) {

    EXPECT_TRUE(iterator->value().empty());

}



}  // namespace leveldb
