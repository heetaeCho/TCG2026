#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"



using namespace leveldb;

using testing::_;

using testing::Return;



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

    MOCK_METHOD0(status, const Status());

};



class IteratorTest_490 : public ::testing::Test {

protected:

    std::unique_ptr<MockIterator> mock_iterator;



    void SetUp() override {

        mock_iterator = std::make_unique<MockIterator>();

    }

};



TEST_F(IteratorTest_490, ValidReturnsFalseInitially_490) {

    EXPECT_CALL(*mock_iterator, Valid()).WillOnce(Return(false));

    EXPECT_FALSE(mock_iterator->Valid());

}



TEST_F(IteratorTest_490, SeekToFirstDoesNotThrow_490) {

    EXPECT_NO_THROW(mock_iterator->SeekToFirst());

}



TEST_F(IteratorTest_490, SeekToLastDoesNotThrow_490) {

    EXPECT_NO_THROW(mock_iterator->SeekToLast());

}



TEST_F(IteratorTest_490, SeekWithTargetDoesNotThrow_490) {

    Slice target("test");

    EXPECT_NO_THROW(mock_iterator->Seek(target));

}



TEST_F(IteratorTest_490, NextDoesNotThrow_490) {

    EXPECT_NO_THROW(mock_iterator->Next());

}



TEST_F(IteratorTest_490, PrevDoesNotThrow_490) {

    EXPECT_NO_THROW(mock_iterator->Prev());

}



TEST_F(IteratorTest_490, KeyReturnsEmptySliceInitially_490) {

    Slice empty_slice;

    EXPECT_CALL(*mock_iterator, key()).WillOnce(Return(empty_slice));

    EXPECT_EQ(mock_iterator->key().size(), 0);

}



TEST_F(IteratorTest_490, ValueReturnsEmptySliceInitially_490) {

    Slice empty_slice;

    EXPECT_CALL(*mock_iterator, value()).WillOnce(Return(empty_slice));

    EXPECT_EQ(mock_iterator->value().size(), 0);

}



TEST_F(IteratorTest_490, StatusReturnsOkInitially_490) {

    Status ok_status;

    EXPECT_CALL(*mock_iterator, status()).WillOnce(Return(ok_status));

    EXPECT_TRUE(mock_iterator->status().ok());

}
