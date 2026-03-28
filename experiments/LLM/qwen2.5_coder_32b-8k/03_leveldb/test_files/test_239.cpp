#include <gtest/gtest.h>

#include "leveldb/iterator.h"

#include "db/c.cc"



// Mock class for Iterator to verify interactions

class MockIterator : public leveldb::Iterator {

public:

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(bool, Valid, (), (const, override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const leveldb::Slice &), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(leveldb::Slice, key, (), (const, override));

    MOCK_METHOD(leveldb::Slice, value, (), (const, override));

    MOCK_METHOD(leveldb::Status, status, (), (const, override));

};



// Test fixture for leveldb_iter_next function

class LeveldbIterNextTest_239 : public ::testing::Test {

protected:

    MockIterator* mock_iterator;

    leveldb_iterator_t iter;



    void SetUp() override {

        mock_iterator = new MockIterator();

        iter.rep = mock_iterator;

    }



    void TearDown() override {

        delete mock_iterator;

    }

};



// Test normal operation of leveldb_iter_next

TEST_F(LeveldbIterNextTest_239, CallsNextOnIterator_239) {

    EXPECT_CALL(*mock_iterator, Next()).Times(1);

    leveldb_iter_next(&iter);

}



// Test boundary condition when iterator is invalid

TEST_F(LeveldbIterNextTest_239, IteratorInvalidDoesNotThrow_239) {

    EXPECT_CALL(*mock_iterator, Valid()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_iterator, Next()).Times(1);

    leveldb_iter_next(&iter);

}



// Test external interaction - ensuring Next is called on the iterator

TEST_F(LeveldbIterNextTest_239, VerifiesNextIsCalled_239) {

    EXPECT_CALL(*mock_iterator, Next()).Times(1);

    leveldb_iter_next(&iter);

}
