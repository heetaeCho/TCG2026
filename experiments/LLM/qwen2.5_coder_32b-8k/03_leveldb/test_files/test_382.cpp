#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"

#include "table/iterator_wrapper.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(bool, Valid, (), (const override));

    MOCK_METHOD(Slice, key, (), (const override));

    MOCK_METHOD(Slice, value, (), (const override));

    MOCK_METHOD(Status, status, (), (const override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const Slice&), (override));

};



class IteratorWrapperTest_382 : public ::testing::Test {

protected:

    MockIterator* mock_iter;

    IteratorWrapper wrapper;



    void SetUp() override {

        mock_iter = new MockIterator();

        wrapper.Set(mock_iter);

    }



    void TearDown() override {

        delete mock_iter;

    }

};



TEST_F(IteratorWrapperTest_382, SetAssignsIterator_382) {

    EXPECT_EQ(wrapper.iter(), mock_iter);

}



TEST_F(IteratorWrapperTest_382, ValidDelegatesToIter_382) {

    EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(true));

    EXPECT_TRUE(wrapper.Valid());

}



TEST_F(IteratorWrapperTest_382, KeyDelegatesToIter_382) {

    Slice expected_key = "test_key";

    EXPECT_CALL(*mock_iter, key()).WillOnce(Return(expected_key));

    EXPECT_EQ(wrapper.key(), expected_key);

}



TEST_F(IteratorWrapperTest_382, ValueDelegatesToIter_382) {

    Slice expected_value = "test_value";

    EXPECT_CALL(*mock_iter, value()).WillOnce(Return(expected_value));

    EXPECT_EQ(wrapper.value(), expected_value);

}



TEST_F(IteratorWrapperTest_382, StatusDelegatesToIter_382) {

    Status expected_status;

    EXPECT_CALL(*mock_iter, status()).WillOnce(Return(expected_status));

    EXPECT_EQ(wrapper.status(), expected_status);

}



TEST_F(IteratorWrapperTest_382, NextCallsIterNext_382) {

    EXPECT_CALL(*mock_iter, Next());

    wrapper.Next();

}



TEST_F(IteratorWrapperTest_382, PrevCallsIterPrev_382) {

    EXPECT_CALL(*mock_iter, Prev());

    wrapper.Prev();

}



TEST_F(IteratorWrapperTest_382, SeekToFirstCallsIterSeekToFirst_382) {

    EXPECT_CALL(*mock_iter, SeekToFirst());

    wrapper.SeekToFirst();

}



TEST_F(IteratorWrapperTest_382, SeekToLastCallsIterSeekToLast_382) {

    EXPECT_CALL(*mock_iter, SeekToLast());

    wrapper.SeekToLast();

}



TEST_F(IteratorWrapperTest_382, SeekCallsIterSeekWithTarget_382) {

    Slice target = "target_key";

    EXPECT_CALL(*mock_iter, Seek(target));

    wrapper.Seek(target);

}
