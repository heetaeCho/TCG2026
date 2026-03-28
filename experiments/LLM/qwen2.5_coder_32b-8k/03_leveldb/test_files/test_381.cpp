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

    MOCK_METHOD0(key, const Slice());

    MOCK_METHOD0(value, const Slice());

    MOCK_METHOD0(status, Status());

};



class IteratorWrapperTest_381 : public ::testing::Test {

protected:

    MockIterator mock_iter;

    IteratorWrapper wrapper;



    void SetUp() override {

        wrapper.Set(&mock_iter);

    }

};



TEST_F(IteratorWrapperTest_381, ValidReturnsFalseInitially_381) {

    EXPECT_CALL(mock_iter, Valid()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(wrapper.Valid());

}



TEST_F(IteratorWrapperTest_381, ValidDelegatesToIterator_381) {

    EXPECT_CALL(mock_iter, Valid()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(wrapper.Valid());

}



TEST_F(IteratorWrapperTest_381, KeyDelegatesToIterator_381) {

    const Slice expected_key = "test_key";

    EXPECT_CALL(mock_iter, key()).WillOnce(::testing::Return(expected_key));

    EXPECT_EQ(expected_key, wrapper.key());

}



TEST_F(IteratorWrapperTest_381, ValueDelegatesToIterator_381) {

    const Slice expected_value = "test_value";

    EXPECT_CALL(mock_iter, value()).WillOnce(::testing::Return(expected_value));

    EXPECT_EQ(expected_value, wrapper.value());

}



TEST_F(IteratorWrapperTest_381, StatusDelegatesToIterator_381) {

    Status expected_status = Status::OK();

    EXPECT_CALL(mock_iter, status()).WillOnce(::testing::Return(expected_status));

    EXPECT_EQ(expected_status, wrapper.status());

}



TEST_F(IteratorWrapperTest_381, NextDelegatesToIterator_381) {

    EXPECT_CALL(mock_iter, Next());

    wrapper.Next();

}



TEST_F(IteratorWrapperTest_381, PrevDelegatesToIterator_381) {

    EXPECT_CALL(mock_iter, Prev());

    wrapper.Prev();

}



TEST_F(IteratorWrapperTest_381, SeekDelegatesToIterator_381) {

    const Slice target = "seek_target";

    EXPECT_CALL(mock_iter, Seek(target));

    wrapper.Seek(target);

}



TEST_F(IteratorWrapperTest_381, SeekToFirstDelegatesToIterator_381) {

    EXPECT_CALL(mock_iter, SeekToFirst());

    wrapper.SeekToFirst();

}



TEST_F(IteratorWrapperTest_381, SeekToLastDelegatesToIterator_381) {

    EXPECT_CALL(mock_iter, SeekToLast());

    wrapper.SeekToLast();

}



TEST_F(IteratorWrapperTest_381, StatusReturnsErrorWhenIteratorIsNull_381) {

    wrapper.Set(nullptr);

    EXPECT_EQ(wrapper.status().IsInvalidArgument(), true);

}
