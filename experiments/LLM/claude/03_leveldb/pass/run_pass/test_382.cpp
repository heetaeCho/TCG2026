#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class MockIterator : public Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(Slice, key, (), (const, override));
  MOCK_METHOD(Slice, value, (), (const, override));
  MOCK_METHOD(Status, status, (), (const, override));
};

class IteratorWrapperTest_382 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(IteratorWrapperTest_382, DefaultConstructor_382) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, ExplicitConstructorWithIterator_382) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_382, SetIterator_382) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  
  wrapper.Set(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_382, SetNullIterator_382) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
  
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, ValidWhenIteratorIsValid_382) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("key1")));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, ValidWhenIteratorIsInvalid_382) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, KeyReturnsCachedKey_382) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "test_key";
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice(key_data)));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "test_key");
}

TEST_F(IteratorWrapperTest_382, ValueDelegatesToIterator_382) {
  MockIterator* mock = new MockIterator();
  std::string val_data = "test_value";
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("key")));
  EXPECT_CALL(*mock, value()).WillRepeatedly(::testing::Return(Slice(val_data)));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.value().ToString(), "test_value");
}

TEST_F(IteratorWrapperTest_382, StatusDelegatesToIterator_382) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status()).WillRepeatedly(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_382, StatusReturnsError_382) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status()).WillRepeatedly(::testing::Return(Status::Corruption("bad data")));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.status().IsCorruption());
}

TEST_F(IteratorWrapperTest_382, NextCallsDelegateAndUpdates_382) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  // SeekToFirst
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("key1")));
  
  // Next
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("key2")));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key1");
  
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

TEST_F(IteratorWrapperTest_382, NextToEnd_382) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("key1")));
  
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  
  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, PrevCallsDelegateAndUpdates_382) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("key3")));
  
  EXPECT_CALL(*mock, Prev()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("key2")));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key3");
  
  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

TEST_F(IteratorWrapperTest_382, SeekCallsDelegateAndUpdates_382) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  EXPECT_CALL(*mock, Seek(Slice("target"))).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("target")));
  
  IteratorWrapper wrapper(mock);
  wrapper.Seek(Slice("target"));
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "target");
}

TEST_F(IteratorWrapperTest_382, SeekNotFound_382) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  EXPECT_CALL(*mock, Seek(Slice("nonexistent"))).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.Seek(Slice("nonexistent"));
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, SeekToFirstOnEmpty_382) {
  MockIterator* mock = new MockIterator();
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, SeekToLastOnEmpty_382) {
  MockIterator* mock = new MockIterator();
  
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, SetReplacesIterator_382) {
  MockIterator* mock1 = new MockIterator();
  MockIterator* mock2 = new MockIterator();
  
  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock1, key()).WillRepeatedly(::testing::Return(Slice("key_from_1")));
  EXPECT_CALL(*mock1, SeekToFirst()).Times(1);
  
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock2, key()).WillRepeatedly(::testing::Return(Slice("key_from_2")));
  EXPECT_CALL(*mock2, SeekToFirst()).Times(1);
  
  IteratorWrapper wrapper(mock1);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "key_from_1");
  
  // Set replaces the iterator (and should delete the old one)
  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "key_from_2");
}

TEST_F(IteratorWrapperTest_382, IterReturnsCurrentIterator_382) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_382, IterReturnsNullForDefault_382) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_382, MultipleNextCalls_382) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("a")));
  
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("b")));
  
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("c")));
  
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");
  
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "b");
  
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "c");
  
  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_382, SeekToFirstThenSeekToLast_382) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("first")));
  
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("last")));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "first");
  
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "last");
}

TEST_F(IteratorWrapperTest_382, PrevToBeginning_382) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("z")));
  
  EXPECT_CALL(*mock, Prev()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "z");
  
  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

}  // namespace leveldb
