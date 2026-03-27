#include <gtest/gtest.h>

#include "table/iterator_wrapper.h"

#include "leveldb/iterator.h"

#include "gmock/gmock.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(void, Seek, (const Slice& target), (override));

    MOCK_METHOD(bool, Valid, (), (const, override));

    MOCK_METHOD(Slice, key, (), (const, override));

    MOCK_METHOD(Slice, value, (), (const, override));

    MOCK_METHOD(Status, status, (), (const, override));

};



class IteratorWrapperTest_384 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_iter = std::make_unique<MockIterator>();

        wrapper.Set(mock_iter.get());

    }



    void TearDown() override {}



    std::unique_ptr<MockIterator> mock_iter;

    IteratorWrapper wrapper;

};



TEST_F(IteratorWrapperTest_384, SeekCallsIterSeek_384) {

    Slice target("target_key");

    EXPECT_CALL(*mock_iter, Seek(target));

    wrapper.Seek(target);

}



TEST_F(IteratorWrapperTest_384, ValidDelegatesToIterValid_384) {

    EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(true));

    EXPECT_TRUE(wrapper.Valid());

}



TEST_F(IteratorWrapperTest_384, KeyDelegatesToIterKey_384) {

    Slice expected_key("expected_key");

    EXPECT_CALL(*mock_iter, key()).WillOnce(Return(expected_key));

    EXPECT_EQ(wrapper.key().ToString(), expected_key.ToString());

}



TEST_F(IteratorWrapperTest_384, ValueDelegatesToIterValue_384) {

    Slice expected_value("expected_value");

    EXPECT_CALL(*mock_iter, value()).WillOnce(Return(expected_value));

    EXPECT_EQ(wrapper.value().ToString(), expected_value.ToString());

}



TEST_F(IteratorWrapperTest_384, StatusDelegatesToIterStatus_384) {

    Status expected_status;

    EXPECT_CALL(*mock_iter, status()).WillOnce(Return(expected_status));

    EXPECT_EQ(wrapper.status(), expected_status);

}



TEST_F(IteratorWrapperTest_384, SeekToFirstCallsIterSeekToFirst_384) {

    EXPECT_CALL(*mock_iter, SeekToFirst());

    wrapper.SeekToFirst();

}



TEST_F(IteratorWrapperTest_384, SeekToLastCallsIterSeekToLast_384) {

    EXPECT_CALL(*mock_iter, SeekToLast());

    wrapper.SeekToLast();

}



TEST_F(IteratorWrapperTest_384, NextCallsIterNext_384) {

    EXPECT_CALL(*mock_iter, Next());

    wrapper.Next();

}



TEST_F(IteratorWrapperTest_384, PrevCallsIterPrev_384) {

    EXPECT_CALL(*mock_iter, Prev());

    wrapper.Prev();

}
