#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/iterator.h"

#include "table/iterator_wrapper.h"



using namespace leveldb;

using ::testing::_;

using ::testing::NiceMock;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(bool, Valid, (), (const, override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const Slice&), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(Slice, key, (), (const, override));

    MOCK_METHOD(Slice, value, (), (const, override));

    MOCK_METHOD(Status, status, (), (const, override));

};



class IteratorWrapperTest_377 : public ::testing::Test {

protected:

    NiceMock<MockIterator> mock_iterator_;

    IteratorWrapper iterator_wrapper_;

};



TEST_F(IteratorWrapperTest_377, SetWithValidIterator_377) {

    EXPECT_CALL(mock_iterator_, Valid()).WillOnce(::testing::Return(true));

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_TRUE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_377, SetWithNullptr_377) {

    iterator_wrapper_.Set(nullptr);

    EXPECT_FALSE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_377, ValidReturnsFalseWhenNotSet_377) {

    EXPECT_FALSE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_377, SeekToFirstDelegatesToIterator_377) {

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_CALL(mock_iterator_, SeekToFirst()).Times(1);

    iterator_wrapper_.SeekToFirst();

}



TEST_F(IteratorWrapperTest_377, SeekToLastDelegatesToIterator_377) {

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_CALL(mock_iterator_, SeekToLast()).Times(1);

    iterator_wrapper_.SeekToLast();

}



TEST_F(IteratorWrapperTest_377, SeekDelegatesToIterator_377) {

    Slice target;

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_CALL(mock_iterator_, Seek(target)).Times(1);

    iterator_wrapper_.Seek(target);

}



TEST_F(IteratorWrapperTest_377, NextDelegatesToIterator_377) {

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_CALL(mock_iterator_, Next()).Times(1);

    iterator_wrapper_.Next();

}



TEST_F(IteratorWrapperTest_377, PrevDelegatesToIterator_377) {

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_CALL(mock_iterator_, Prev()).Times(1);

    iterator_wrapper_.Prev();

}



TEST_F(IteratorWrapperTest_377, KeyDelegatesToIterator_377) {

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_CALL(mock_iterator_, key()).WillOnce(::testing::Return(Slice()));

    Slice key = iterator_wrapper_.key();

}



TEST_F(IteratorWrapperTest_377, ValueDelegatesToIterator_377) {

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_CALL(mock_iterator_, value()).WillOnce(::testing::Return(Slice()));

    Slice value = iterator_wrapper_.value();

}



TEST_F(IteratorWrapperTest_377, StatusDelegatesToIterator_377) {

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_CALL(mock_iterator_, status()).WillOnce(::testing::Return(Status::OK()));

    Status status = iterator_wrapper_.status();

}
