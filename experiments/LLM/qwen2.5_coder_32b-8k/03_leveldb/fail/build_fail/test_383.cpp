#include "gmock/gmock.h"

#include "gtest/gtest.h"

#include "leveldb/iterator.h"

#include "table/iterator_wrapper.h"



using namespace leveldb;

using ::testing::_;

using ::testing::MockFunction;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(bool, Valid, (), (const, override));

    MOCK_METHOD(Slice, key, (), (const, override));

    MOCK_METHOD(Slice, value, (), (const, override));

    MOCK_METHOD(Status, status, (), (const, override));

};



class IteratorWrapperTest_383 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_iter = std::make_unique<MockIterator>();

        wrapper.Set(mock_iter.get());

    }



    std::unique_ptr<MockIterator> mock_iter;

    IteratorWrapper wrapper;

};



TEST_F(IteratorWrapperTest_383, PrevCallsPrevOnIterator_383) {

    EXPECT_CALL(*mock_iter, Prev()).Times(1);

    wrapper.Prev();

}



TEST_F(IteratorWrapperTest_383, ValidReturnsIteratorValidState_383) {

    bool expected_valid = true;

    EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(expected_valid));

    EXPECT_EQ(wrapper.Valid(), expected_valid);

}



TEST_F(IteratorWrapperTest_383, KeyReturnsIteratorKey_383) {

    Slice expected_key("test_key");

    EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::ReturnRef(expected_key));

    EXPECT_EQ(wrapper.key().ToString(), expected_key.ToString());

}



TEST_F(IteratorWrapperTest_383, ValueReturnsIteratorValue_383) {

    Slice expected_value("test_value");

    EXPECT_CALL(*mock_iter, value()).WillOnce(::testing::ReturnRef(expected_value));

    EXPECT_EQ(wrapper.value().ToString(), expected_value.ToString());

}



TEST_F(IteratorWrapperTest_383, StatusReturnsIteratorStatus_383) {

    Status expected_status(Status::OK());

    EXPECT_CALL(*mock_iter, status()).WillOnce(::testing::Return(expected_status));

    EXPECT_EQ(wrapper.status().ok(), expected_status.ok());

}



TEST_F(IteratorWrapperTest_383, SeekCallsSeekOnIterator_383) {

    Slice target("target_key");

    EXPECT_CALL(*mock_iter, Seek(target)).Times(1);

    wrapper.Seek(target);

}



TEST_F(IteratorWrapperTest_383, SeekToFirstCallsSeekToFirstOnIterator_383) {

    EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);

    wrapper.SeekToFirst();

}



TEST_F(IteratorWrapperTest_383, SeekToLastCallsSeekToLastOnIterator_383) {

    EXPECT_CALL(*mock_iter, SeekToLast()).Times(1);

    wrapper.SeekToLast();

}
