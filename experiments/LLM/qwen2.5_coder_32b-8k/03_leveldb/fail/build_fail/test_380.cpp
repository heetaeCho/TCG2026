#include <gtest/gtest.h>

#include "table/iterator_wrapper.h"

#include "leveldb/iterator.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(bool, Valid, (), (const override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const Slice & target), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(Slice, key, (), (const override));

    MOCK_METHOD(Slice, value, (), (const override));

    MOCK_METHOD(Status, status, (), (const override));

};



class IteratorWrapperTest_380 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_iter = std::make_unique<MockIterator>();

        wrapper.Set(mock_iter.get());

    }



    std::unique_ptr<MockIterator> mock_iter;

    IteratorWrapper wrapper;

};



TEST_F(IteratorWrapperTest_380, Valid_ReturnsTrueWhenUnderlyingIsValid_380) {

    EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(true));

    EXPECT_TRUE(wrapper.Valid());

}



TEST_F(IteratorWrapperTest_380, Valid_ReturnsFalseWhenUnderlyingIsInvalid_380) {

    EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(false));

    EXPECT_FALSE(wrapper.Valid());

}



TEST_F(IteratorWrapperTest_380, SeekToFirst_DelegatesToUnderlying_380) {

    EXPECT_CALL(*mock_iter, SeekToFirst());

    wrapper.SeekToFirst();

}



TEST_F(IteratorWrapperTest_380, SeekToLast_DelegatesToUnderlying_380) {

    EXPECT_CALL(*mock_iter, SeekToLast());

    wrapper.SeekToLast();

}



TEST_F(IteratorWrapperTest_380, Seek_DelegatesToUnderlyingWithTarget_380) {

    Slice target("target_key");

    EXPECT_CALL(*mock_iter, Seek(target));

    wrapper.Seek(target);

}



TEST_F(IteratorWrapperTest_380, Next_DelegatesToUnderlying_380) {

    EXPECT_CALL(*mock_iter, Next());

    wrapper.Next();

}



TEST_F(IteratorWrapperTest_380, Prev_DelegatesToUnderlying_380) {

    EXPECT_CALL(*mock_iter, Prev());

    wrapper.Prev();

}



TEST_F(IteratorWrapperTest_380, Key_ReturnsKeyFromUnderlying_380) {

    Slice expected_key("expected_key");

    EXPECT_CALL(*mock_iter, key()).WillOnce(Return(expected_key));

    EXPECT_EQ(wrapper.key(), expected_key);

}



TEST_F(IteratorWrapperTest_380, Value_ReturnsValueFromUnderlying_380) {

    Slice expected_value("expected_value");

    EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(Return(true));

    EXPECT_CALL(*mock_iter, value()).WillOnce(Return(expected_value));

    EXPECT_EQ(wrapper.value(), expected_value);

}



TEST_F(IteratorWrapperTest_380, Status_ReturnsStatusFromUnderlying_380) {

    Status expected_status;

    EXPECT_CALL(*mock_iter, status()).WillOnce(Return(expected_status));

    EXPECT_EQ(wrapper.status(), expected_status);

}
