#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"

#include "db/c.cc"



using namespace leveldb;

using ::testing::Return;



// Mock class for Iterator

class MockIterator : public Iterator {

public:

    MOCK_METHOD(bool, Valid, (), (const override));

};



class LevelDBIterTest_235 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_iter = new MockIterator();

        iter_t.rep = mock_iter;

    }



    void TearDown() override {

        delete mock_iter;

    }



    leveldb_iterator_t iter_t;

    MockIterator* mock_iter;

};



TEST_F(LevelDBIterTest_235, IterValid_ReturnsTrue_235) {

    EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(true));

    ASSERT_EQ(leveldb_iter_valid(&iter_t), 1);

}



TEST_F(LevelDBIterTest_235, IterValid_ReturnsFalse_235) {

    EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(false));

    ASSERT_EQ(leveldb_iter_valid(&iter_t), 0);

}
