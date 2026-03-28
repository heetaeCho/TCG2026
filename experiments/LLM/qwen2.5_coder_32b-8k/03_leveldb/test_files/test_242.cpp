#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"

#include "db/c.cc"



using namespace leveldb;

using testing::Return;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(const bool, Valid, (), (override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const Slice &), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(const Slice, key, (), (override));

    MOCK_METHOD(const Slice, value, (), (override));

    MOCK_METHOD(const Status, status, (), (override));

};



class LeveldbIterValueTest_242 : public ::testing::Test {

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



TEST_F(LeveldbIterValueTest_242, ValueReturnsCorrectDataAndLength_242) {

    const char expected_data[] = "test_value";

    size_t expected_length = sizeof(expected_data) - 1;

    Slice expected_slice(expected_data);



    EXPECT_CALL(*mock_iter, value())

        .WillOnce(Return(expected_slice));



    size_t vlen;

    const char* result = leveldb_iter_value(&iter_t, &vlen);



    ASSERT_EQ(vlen, expected_length);

    ASSERT_STREQ(result, expected_data);

}



TEST_F(LeveldbIterValueTest_242, ValueReturnsEmptyDataAndLength_242) {

    Slice empty_slice;



    EXPECT_CALL(*mock_iter, value())

        .WillOnce(Return(empty_slice));



    size_t vlen;

    const char* result = leveldb_iter_value(&iter_t, &vlen);



    ASSERT_EQ(vlen, 0);

    ASSERT_EQ(result, nullptr);

}
