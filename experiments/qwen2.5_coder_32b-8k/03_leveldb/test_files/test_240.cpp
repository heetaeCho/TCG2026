#include <gtest/gtest.h>

#include "leveldb/iterator.h"

#include "db/c.cc"



// Mocking the Iterator class to verify interactions

class MockIterator : public leveldb::Iterator {

public:

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(bool, Valid, (), (const override));

};



TEST_F(WriteBatchTest_240, PrevValidatesIterator_240) {

    MockIterator mock_iter;

    leveldb_iterator_t iter = {&mock_iter};



    EXPECT_CALL(mock_iter, Prev());

    leveldb_iter_prev(&iter);

}



TEST_F(WriteBatchTest_240, PrevCallsPrevOnRep_240) {

    MockIterator mock_iter;

    leveldb_iterator_t iter = {&mock_iter};



    EXPECT_CALL(mock_iter, Prev()).Times(1);

    leveldb_iter_prev(&iter);

}
