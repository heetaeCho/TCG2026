#include "gmock/gmock.h"

#include "gtest/gtest.h"

#include "table/iterator_wrapper.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockIterator : public Iterator {

public:

    MOCK_METHOD(void, Seek, (const Slice& k), (override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(bool, Valid, (), (const, override));

    MOCK_METHOD(Slice, key, (), (const, override));

    MOCK_METHOD(Slice, value, (), (const, override));

    MOCK_METHOD(Status, status, (), (const, override));

};



class IteratorWrapperTest_378 : public ::testing::Test {

protected:

    std::unique_ptr<MockIterator> mock_iter_;

    IteratorWrapper iterator_wrapper_;



    void SetUp() override {

        mock_iter_ = std::make_unique<MockIterator>();

        iterator_wrapper_.Set(mock_iter_.get());

    }

};



TEST_F(IteratorWrapperTest_378, ValidInitiallyFalse_378) {

    EXPECT_FALSE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_378, SetChangesIterator_378) {

    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(Return(true));

    iterator_wrapper_.Set(mock_iter_.get());

    EXPECT_TRUE(iterator_wrapper_.Valid());

}



TEST_F(IteratorWrapperTest_378, SeekDelegatesToIterator_378) {

    Slice key("test_key");

    EXPECT_CALL(*mock_iter_, Seek(key));

    iterator_wrapper_.Seek(key);

}



TEST_F(IteratorWrapperTest_378, SeekToFirstDelegatesToIterator_378) {

    EXPECT_CALL(*mock_iter_, SeekToFirst());

    iterator_wrapper_.SeekToFirst();

}



TEST_F(IteratorWrapperTest_378, SeekToLastDelegatesToIterator_378) {

    EXPECT_CALL(*mock_iter_, SeekToLast());

    iterator_wrapper_.SeekToLast();

}



TEST_F(IteratorWrapperTest_378, NextDelegatesToIterator_378) {

    EXPECT_CALL(*mock_iter_, Next());

    iterator_wrapper_.Next();

}



TEST_F(IteratorWrapperTest_378, PrevDelegatesToIterator_378) {

    EXPECT_CALL(*mock_iter_, Prev());

    iterator_wrapper_.Prev();

}



TEST_F(IteratorWrapperTest_378, KeyDelegatesToIterator_378) {

    Slice expected_key("expected_key");

    EXPECT_CALL(*mock_iter_, key()).WillOnce(Return(expected_key));

    EXPECT_EQ(iterator_wrapper_.key(), expected_key);

}



TEST_F(IteratorWrapperTest_378, ValueDelegatesToIterator_378) {

    Slice expected_value("expected_value");

    EXPECT_CALL(*mock_iter_, value()).WillOnce(Return(expected_value));

    EXPECT_EQ(iterator_wrapper_.value(), expected_value);

}



TEST_F(IteratorWrapperTest_378, StatusDelegatesToIterator_378) {

    Status expected_status = Status::OK();

    EXPECT_CALL(*mock_iter_, status()).WillOnce(Return(expected_status));

    EXPECT_EQ(iterator_wrapper_.status(), expected_status);

}
