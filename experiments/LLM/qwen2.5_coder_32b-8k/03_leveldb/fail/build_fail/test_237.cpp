#include <gtest/gtest.h>

#include "leveldb/iterator.h"

#include "db/c.cc"



class IteratorTest_237 : public ::testing::Test {

protected:

    leveldb_iterator_t* iter;



    void SetUp() override {

        iter = new leveldb_iterator_t();

        iter->rep = new leveldb::Iterator();

    }



    void TearDown() override {

        delete iter->rep;

        delete iter;

    }

};



TEST_F(IteratorTest_237, SeekToLast_NormalOperation_237) {

    // Assuming SeekToLast modifies the iterator to a valid state

    leveldb_iter_seek_to_last(iter);

    EXPECT_TRUE(iter->rep->Valid());

}



// Boundary condition: No elements in the database

TEST_F(IteratorTest_237, SeekToLast_EmptyDatabase_237) {

    // Assuming SeekToLast on an empty database results in invalid state

    leveldb_iter_seek_to_last(iter);

    EXPECT_FALSE(iter->rep->Valid());

}



// Exceptional case: Iterator is already deleted or not properly initialized

TEST_F(IteratorTest_237, SeekToLast_InvalidIterator_237) {

    delete iter->rep;

    iter->rep = nullptr;



    // Assuming calling SeekToLast on an invalid iterator does not crash and returns gracefully

    leveldb_iter_seek_to_last(iter);

    EXPECT_EQ(iter->rep, nullptr);

}
