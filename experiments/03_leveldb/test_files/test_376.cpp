#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "table/iterator_wrapper.h"

#include "leveldb/status.h"



using namespace leveldb;

using ::testing::Return;

using ::testing::_;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(bool, Valid, (), (const override));

    MOCK_METHOD(void, Seek, (const Slice& target), (override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(Slice, key, (), (const override));

    MOCK_METHOD(Slice, value, (), (const override));

    MOCK_METHOD(Status, status, (), (const override));

};



class IteratorWrapperTest_376 : public ::testing::Test {

protected:

    std::unique_ptr<MockIterator> mock_iter_;

    IteratorWrapper wrapper_;



    void SetUp() override {

        mock_iter_ = std::make_unique<MockIterator>();

        wrapper_.Set(mock_iter_.get());

    }

};



TEST_F(IteratorWrapperTest_376, IterReturnsCorrectIterator_376) {

    EXPECT_EQ(wrapper_.iter(), mock_iter_.get());

}



TEST_F(IteratorWrapperTest_376, ValidDelegatesToUnderlyingIterator_376) {

    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(Return(true));

    EXPECT_TRUE(wrapper_.Valid());



    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(Return(false));

    EXPECT_FALSE(wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_376, KeyDelegatesToUnderlyingIterator_376) {

    Slice expected_key("test_key");

    EXPECT_CALL(*mock_iter_, key()).WillOnce(Return(expected_key));

    EXPECT_EQ(wrapper_.key(), expected_key);

}



TEST_F(IteratorWrapperTest_376, ValueDelegatesToUnderlyingIterator_376) {

    Slice expected_value("test_value");

    EXPECT_CALL(*mock_iter_, value()).WillOnce(Return(expected_value));

    EXPECT_EQ(wrapper_.value(), expected_value);

}



TEST_F(IteratorWrapperTest_376, StatusDelegatesToUnderlyingIterator_376) {

    Status expected_status = Status::OK();

    EXPECT_CALL(*mock_iter_, status()).WillOnce(Return(expected_status));

    EXPECT_EQ(wrapper_.status().ok(), true);



    expected_status = Status::NotFound("Not found");

    EXPECT_CALL(*mock_iter_, status()).WillOnce(Return(expected_status));

    EXPECT_EQ(wrapper_.status().IsNotFound(), true);

}



TEST_F(IteratorWrapperTest_376, NextDelegatesToUnderlyingIterator_376) {

    EXPECT_CALL(*mock_iter_, Next());

    wrapper_.Next();

}



TEST_F(IteratorWrapperTest_376, PrevDelegatesToUnderlyingIterator_376) {

    EXPECT_CALL(*mock_iter_, Prev());

    wrapper_.Prev();

}



TEST_F(IteratorWrapperTest_376, SeekDelegatesToUnderlyingIterator_376) {

    Slice target("target_key");

    EXPECT_CALL(*mock_iter_, Seek(target));

    wrapper_.Seek(target);

}



TEST_F(IteratorWrapperTest_376, SeekToFirstDelegatesToUnderlyingIterator_376) {

    EXPECT_CALL(*mock_iter_, SeekToFirst());

    wrapper_.SeekToFirst();

}



TEST_F(IteratorWrapperTest_376, SeekToLastDelegatesToUnderlyingIterator_376) {

    EXPECT_CALL(*mock_iter_, SeekToLast());

    wrapper_.SeekToLast();

}
