#include <gtest/gtest.h>

#include "table/iterator_wrapper.h"

#include "leveldb/iterator.h"



using namespace leveldb;



class MockIterator : public Iterator {

public:

    MOCK_METHOD0(Valid, bool());

    MOCK_METHOD0(SeekToFirst, void());

    MOCK_METHOD0(SeekToLast, void());

    MOCK_METHOD1(Seek, void(const Slice& target));

    MOCK_METHOD0(Next, void());

    MOCK_METHOD0(Prev, void());

    MOCK_METHOD0(key, Slice());

    MOCK_METHOD0(value, Slice());

    MOCK_METHOD0(status, Status());

};



class IteratorWrapperTest_489 : public ::testing::Test {

protected:

    MockIterator mock_iterator_;

    IteratorWrapper iterator_wrapper_;



    IteratorWrapperTest_489() : iterator_wrapper_(nullptr) {}

};



TEST_F(IteratorWrapperTest_489, SetValidatesIterator_489) {

    EXPECT_CALL(mock_iterator_, Valid()).WillOnce(::testing::Return(true));

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_TRUE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_489, SetNullptrIterator_489) {

    iterator_wrapper_.Set(nullptr);

    EXPECT_FALSE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_489, ValidAfterSeekToFirst_489) {

    EXPECT_CALL(mock_iterator_, SeekToFirst()).Times(1);

    EXPECT_CALL(mock_iterator_, Valid()).WillOnce(::testing::Return(true));

    iterator_wrapper_.Set(&mock_iterator_);

    iterator_wrapper_.SeekToFirst();

    EXPECT_TRUE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_489, ValidAfterSeekToLast_489) {

    EXPECT_CALL(mock_iterator_, SeekToLast()).Times(1);

    EXPECT_CALL(mock_iterator_, Valid()).WillOnce(::testing::Return(true));

    iterator_wrapper_.Set(&mock_iterator_);

    iterator_wrapper_.SeekToLast();

    EXPECT_TRUE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_489, SeekWithTarget_489) {

    Slice target("target");

    EXPECT_CALL(mock_iterator_, Seek(target)).Times(1);

    iterator_wrapper_.Set(&mock_iterator_);

    iterator_wrapper_.Seek(target);

}



TEST_F(IteratorWrapperTest_489, NextOperation_489) {

    EXPECT_CALL(mock_iterator_, Next()).Times(1);

    iterator_wrapper_.Set(&mock_iterator_);

    iterator_wrapper_.Next();

}



TEST_F(IteratorWrapperTest_489, PrevOperation_489) {

    EXPECT_CALL(mock_iterator_, Prev()).Times(1);

    iterator_wrapper_.Set(&mock_iterator_);

    iterator_wrapper_.Prev();

}



TEST_F(IteratorWrapperTest_489, KeyRetrieval_489) {

    Slice expected_key("expected_key");

    EXPECT_CALL(mock_iterator_, key()).WillOnce(::testing::Return(expected_key));

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_EQ(iterator_wrapper_.key(), expected_key);

}



TEST_F(IteratorWrapperTest_489, ValueRetrieval_489) {

    Slice expected_value("expected_value");

    EXPECT_CALL(mock_iterator_, value()).WillOnce(::testing::Return(expected_value));

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_EQ(iterator_wrapper_.value(), expected_value);

}



TEST_F(IteratorWrapperTest_489, StatusRetrieval_489) {

    Status expected_status;

    EXPECT_CALL(mock_iterator_, status()).WillOnce(::testing::Return(expected_status));

    iterator_wrapper_.Set(&mock_iterator_);

    EXPECT_EQ(iterator_wrapper_.status(), expected_status);

}
