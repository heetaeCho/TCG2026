#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "table/iterator_wrapper.h"

#include "leveldb/iterator.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;

using ::testing::Invoke;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(bool, Valid, (), (override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const Slice& target), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(Slice, key, (), (const, override));

    MOCK_METHOD(Slice, value, (), (const, override));

    MOCK_METHOD(Status, status, (), (const, override));

};



class IteratorWrapperTest_385 : public ::testing::Test {

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



TEST_F(IteratorWrapperTest_385, SeekToFirst_CallsSeekToFirstOnIterator_385) {

    EXPECT_CALL(*mock_iter_, SeekToFirst());

    wrapper_.SeekToFirst();

}



TEST_F(IteratorWrapperTest_385, Valid_ReturnsTrueWhenIteratorIsValid_385) {

    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(Return(true));

    EXPECT_TRUE(wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_385, Valid_ReturnsFalseWhenIteratorIsInvalid_385) {

    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(Return(false));

    EXPECT_FALSE(wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_385, Key_DelegatesToIterator_385) {

    Slice expected_key = "expected_key";

    EXPECT_CALL(*mock_iter_, key()).WillOnce(Return(expected_key));

    EXPECT_EQ(wrapper_.key(), expected_key);

}



TEST_F(IteratorWrapperTest_385, Value_DelegatesToIterator_385) {

    Slice expected_value = "expected_value";

    EXPECT_CALL(*mock_iter_, value()).WillOnce(Return(expected_value));

    EXPECT_EQ(wrapper_.value(), expected_value);

}



TEST_F(IteratorWrapperTest_385, Status_DelegatesToIterator_385) {

    Status expected_status = Status::OK();

    EXPECT_CALL(*mock_iter_, status()).WillOnce(Return(expected_status));

    EXPECT_EQ(wrapper_.status(), expected_status);

}



TEST_F(IteratorWrapperTest_385, Seek_CallsSeekOnIterator_385) {

    Slice target = "target_key";

    EXPECT_CALL(*mock_iter_, Seek(target));

    wrapper_.Seek(target);

}



TEST_F(IteratorWrapperTest_385, SeekToLast_CallsSeekToLastOnIterator_385) {

    EXPECT_CALL(*mock_iter_, SeekToLast());

    wrapper_.SeekToLast();

}



TEST_F(IteratorWrapperTest_385, Next_CallsNextOnIterator_385) {

    EXPECT_CALL(*mock_iter_, Next());

    wrapper_.Next();

}



TEST_F(IteratorWrapperTest_385, Prev_CallsPrevOnIterator_385) {

    EXPECT_CALL(*mock_iter_, Prev());

    wrapper_.Prev();

}
