#include <gtest/gtest.h>

#include "table/iterator_wrapper.h"

#include "leveldb/slice.h"

#include "leveldb/status.h"



using namespace leveldb;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(bool, Valid, (), (override));

    MOCK_METHOD(Slice, key, (), (const, override));

    MOCK_METHOD(Slice, value, (), (const, override));

    MOCK_METHOD(Status, status, (), (const, override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(void, Seek, (const Slice& target), (override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

};



class IteratorWrapperTest_379 : public ::testing::Test {

protected:

    MockIterator* mock_iter_;

    IteratorWrapper wrapper_;



    void SetUp() override {

        mock_iter_ = new MockIterator();

        wrapper_.Set(mock_iter_);

    }



    void TearDown() override {

        delete mock_iter_;

    }

};



TEST_F(IteratorWrapperTest_379, ValidDelegatesToIter_379) {

    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(wrapper_.Valid());



    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_379, KeyDelegatesToIter_379) {

    Slice expected_key("test_key");

    EXPECT_CALL(*mock_iter_, key()).WillOnce(::testing::Return(expected_key));

    EXPECT_EQ(expected_key, wrapper_.key());

}



TEST_F(IteratorWrapperTest_379, ValueDelegatesToIter_379) {

    Slice expected_value("test_value");

    EXPECT_CALL(*mock_iter_, value()).WillOnce(::testing::Return(expected_value));

    EXPECT_EQ(expected_value, wrapper_.value());

}



TEST_F(IteratorWrapperTest_379, StatusDelegatesToIter_379) {

    Status expected_status(Status::OK());

    EXPECT_CALL(*mock_iter_, status()).WillOnce(::testing::Return(expected_status));

    EXPECT_EQ(expected_status, wrapper_.status());

}



TEST_F(IteratorWrapperTest_379, NextDelegatesToIter_379) {

    EXPECT_CALL(*mock_iter_, Next());

    wrapper_.Next();

}



TEST_F(IteratorWrapperTest_379, PrevDelegatesToIter_379) {

    EXPECT_CALL(*mock_iter_, Prev());

    wrapper_.Prev();

}



TEST_F(IteratorWrapperTest_379, SeekDelegatesToIter_379) {

    Slice target("seek_target");

    EXPECT_CALL(*mock_iter_, Seek(target));

    wrapper_.Seek(target);

}



TEST_F(IteratorWrapperTest_379, SeekToFirstDelegatesToIter_379) {

    EXPECT_CALL(*mock_iter_, SeekToFirst());

    wrapper_.SeekToFirst();

}



TEST_F(IteratorWrapperTest_379, SeekToLastDelegatesToIter_379) {

    EXPECT_CALL(*mock_iter_, SeekToLast());

    wrapper_.SeekToLast();

}
