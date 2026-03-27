#include <gtest/gtest.h>

#include "table/iterator_wrapper.h"

#include "leveldb/slice.h"

#include "leveldb/status.h"



using namespace leveldb;



class IteratorWrapperTest_375 : public ::testing::Test {

protected:

    class MockIterator : public Iterator {

    public:

        MOCK_METHOD(void, Next, (), (override));

        MOCK_METHOD(void, Prev, (), (override));

        MOCK_METHOD(void, Seek, (const Slice& k), (override));

        MOCK_METHOD(void, SeekToFirst, (), (override));

        MOCK_METHOD(void, SeekToLast, (), (override));

        MOCK_METHOD(bool, Valid, (), (const, override));

        MOCK_METHOD(Slice, key, (), (const, override));

        MOCK_METHOD(Slice, value, (), (const, override));

        MOCK_METHOD(Status, status, (), (const, override));

    };



    MockIterator mock_iter;

    IteratorWrapper iter_wrapper;



    void SetUp() override {

        iter_wrapper.Set(&mock_iter);

    }



    void TearDown() override {

        iter_wrapper.Set(nullptr);

    }

};



TEST_F(IteratorWrapperTest_375, ValidReturnsFalseInitially_375) {

    EXPECT_CALL(mock_iter, Valid()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(iter_wrapper.Valid());

}



TEST_F(IteratorWrapperTest_375, KeyReturnsExpectedValue_375) {

    Slice expected_key("test_key");

    EXPECT_CALL(mock_iter, key()).WillOnce(::testing::Return(expected_key));

    EXPECT_EQ(expected_key.ToString(), iter_wrapper.key().ToString());

}



TEST_F(IteratorWrapperTest_375, ValueReturnsExpectedValue_375) {

    Slice expected_value("test_value");

    EXPECT_CALL(mock_iter, value()).WillOnce(::testing::Return(expected_value));

    EXPECT_EQ(expected_value.ToString(), iter_wrapper.value().ToString());

}



TEST_F(IteratorWrapperTest_375, StatusReturnsExpectedStatus_375) {

    Status expected_status(Status::OK());

    EXPECT_CALL(mock_iter, status()).WillOnce(::testing::Return(expected_status));

    EXPECT_EQ(expected_status.ToString(), iter_wrapper.status().ToString());

}



TEST_F(IteratorWrapperTest_375, NextDelegatesToMockIterator_375) {

    EXPECT_CALL(mock_iter, Next());

    iter_wrapper.Next();

}



TEST_F(IteratorWrapperTest_375, PrevDelegatesToMockIterator_375) {

    EXPECT_CALL(mock_iter, Prev());

    iter_wrapper.Prev();

}



TEST_F(IteratorWrapperTest_375, SeekDelegatesToMockIterator_375) {

    Slice key("seek_key");

    EXPECT_CALL(mock_iter, Seek(key));

    iter_wrapper.Seek(key);

}



TEST_F(IteratorWrapperTest_375, SeekToFirstDelegatesToMockIterator_375) {

    EXPECT_CALL(mock_iter, SeekToFirst());

    iter_wrapper.SeekToFirst();

}



TEST_F(IteratorWrapperTest_375, SeekToLastDelegatesToMockIterator_375) {

    EXPECT_CALL(mock_iter, SeekToLast());

    iter_wrapper.SeekToLast();

}
