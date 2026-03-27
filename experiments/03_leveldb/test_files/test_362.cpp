#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/memtable.cc"  // Adjust the include path as necessary



namespace leveldb {



class MockIterator : public Iterator {

public:

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(bool, Valid, (), (const override));

    MOCK_METHOD(void, Seek, (const Slice& k), (override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(Slice, key, (), (const override));

    MOCK_METHOD(Slice, value, (), (const override));

    MOCK_METHOD(Status, status, (), (const override));

};



class MemTableIteratorTest_362 : public ::testing::Test {

protected:

    MockIterator* mock_iter_;

    MemTableIterator* memtable_iter_;



    void SetUp() override {

        mock_iter_ = new MockIterator();

        memtable_iter_ = new MemTableIterator(reinterpret_cast<MemTable::Table*>(mock_iter_));

    }



    void TearDown() override {

        delete memtable_iter_;

        delete mock_iter_;

    }

};



TEST_F(MemTableIteratorTest_362, PrevCallsInternalPrev_362) {

    EXPECT_CALL(*mock_iter_, Prev()).Times(1);

    memtable_iter_->Prev();

}



TEST_F(MemTableIteratorTest_362, ValidDelegatesToInternal_362) {

    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(memtable_iter_->Valid());



    EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(memtable_iter_->Valid());

}



TEST_F(MemTableIteratorTest_362, SeekDelegatesToInternal_362) {

    Slice key("test_key");

    EXPECT_CALL(*mock_iter_, Seek(key)).Times(1);

    memtable_iter_->Seek(key);

}



TEST_F(MemTableIteratorTest_362, SeekToFirstDelegatesToInternal_362) {

    EXPECT_CALL(*mock_iter_, SeekToFirst()).Times(1);

    memtable_iter_->SeekToFirst();

}



TEST_F(MemTableIteratorTest_362, SeekToLastDelegatesToInternal_362) {

    EXPECT_CALL(*mock_iter_, SeekToLast()).Times(1);

    memtable_iter_->SeekToLast();

}



TEST_F(MemTableIteratorTest_362, NextDelegatesToInternal_362) {

    EXPECT_CALL(*mock_iter_, Next()).Times(1);

    memtable_iter_->Next();

}



TEST_F(MemTableIteratorTest_362, KeyDelegatesToInternal_362) {

    Slice expected_key("expected_key");

    EXPECT_CALL(*mock_iter_, key()).WillOnce(::testing::Return(expected_key));

    EXPECT_EQ(memtable_iter_->key().ToString(), expected_key.ToString());

}



TEST_F(MemTableIteratorTest_362, ValueDelegatesToInternal_362) {

    Slice expected_value("expected_value");

    EXPECT_CALL(*mock_iter_, value()).WillOnce(::testing::Return(expected_value));

    EXPECT_EQ(memtable_iter_->value().ToString(), expected_value.ToString());

}



TEST_F(MemTableIteratorTest_362, StatusDelegatesToInternal_362) {

    Status expected_status;

    EXPECT_CALL(*mock_iter_, status()).WillOnce(::testing::Return(expected_status));

    EXPECT_EQ(memtable_iter_->status().ok(), expected_status.ok());

}



}  // namespace leveldb
