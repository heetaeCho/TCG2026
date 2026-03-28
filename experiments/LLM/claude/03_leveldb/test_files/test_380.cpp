#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

// Mock Iterator for testing IteratorWrapper
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

class IteratorWrapperTest_380 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates an invalid wrapper
TEST_F(IteratorWrapperTest_380, DefaultConstructorCreatesInvalidWrapper_380) {
  IteratorWrapper wrapper;
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

// Test explicit constructor with a valid iterator
TEST_F(IteratorWrapperTest_380, ExplicitConstructorSetsIterator_380) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  EXPECT_EQ(wrapper.iter(), mock_iter);
}

// Test Set method replaces the iterator
TEST_F(IteratorWrapperTest_380, SetReplacesIterator_380) {
  MockIterator* mock_iter1 = new MockIterator();
  MockIterator* mock_iter2 = new MockIterator();
  
  EXPECT_CALL(*mock_iter1, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock_iter2, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper;
  wrapper.Set(mock_iter1);
  EXPECT_EQ(wrapper.iter(), mock_iter1);
  
  wrapper.Set(mock_iter2);
  EXPECT_EQ(wrapper.iter(), mock_iter2);
}

// Test Set with nullptr
TEST_F(IteratorWrapperTest_380, SetWithNullptrMakesInvalid_380) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("key")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.Set(nullptr);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

// Test Valid returns true when underlying iterator is valid
TEST_F(IteratorWrapperTest_380, ValidReturnsTrueWhenIteratorValid_380) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("testkey")));
  
  IteratorWrapper wrapper(mock_iter);
  // Need to trigger an operation that calls Update
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
}

// Test Valid returns false when underlying iterator is not valid
TEST_F(IteratorWrapperTest_380, ValidReturnsFalseWhenIteratorInvalid_380) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

// Test SeekToFirst delegates to underlying iterator
TEST_F(IteratorWrapperTest_380, SeekToFirstDelegates_380) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("first")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
}

// Test SeekToLast delegates to underlying iterator
TEST_F(IteratorWrapperTest_380, SeekToLastDelegates_380) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, SeekToLast()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("last")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
}

// Test Seek delegates to underlying iterator
TEST_F(IteratorWrapperTest_380, SeekDelegates_380) {
  MockIterator* mock_iter = new MockIterator();
  Slice target("target");
  EXPECT_CALL(*mock_iter, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("target")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.Seek(target);
  EXPECT_TRUE(wrapper.Valid());
}

// Test Next delegates to underlying iterator
TEST_F(IteratorWrapperTest_380, NextDelegates_380) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Next()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("key2")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
}

// Test Prev delegates to underlying iterator
TEST_F(IteratorWrapperTest_380, PrevDelegates_380) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToLast()).Times(1);
  EXPECT_CALL(*mock_iter, Prev()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("key1")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToLast();
  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
}

// Test key returns the cached key
TEST_F(IteratorWrapperTest_380, KeyReturnsCachedKey_380) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("mykey")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "mykey");
}

// Test value delegates to underlying iterator
TEST_F(IteratorWrapperTest_380, ValueDelegatesToIterator_380) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("key")));
  EXPECT_CALL(*mock_iter, value()).WillOnce(::testing::Return(Slice("myvalue")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.value().ToString(), "myvalue");
}

// Test status delegates to underlying iterator
TEST_F(IteratorWrapperTest_380, StatusDelegatesToIterator_380) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock_iter, status()).WillOnce(::testing::Return(Status::OK()));
  
  IteratorWrapper wrapper(mock_iter);
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  wrapper.SeekToFirst();
  
  Status s = wrapper.status();
  EXPECT_TRUE(s.ok());
}

// Test status returns error from underlying iterator
TEST_F(IteratorWrapperTest_380, StatusReturnsErrorFromIterator_380) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock_iter, status()).WillOnce(::testing::Return(Status::Corruption("corrupted")));
  
  IteratorWrapper wrapper(mock_iter);
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  wrapper.SeekToFirst();
  
  Status s = wrapper.status();
  EXPECT_TRUE(s.IsCorruption());
}

// Test that Next updates validity when iterator becomes invalid
TEST_F(IteratorWrapperTest_380, NextUpdatesValidityWhenBecomesInvalid_380) {
  MockIterator* mock_iter = new MockIterator();
  
  // First SeekToFirst: valid with key
  // After Next: becomes invalid
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Next()).Times(1);
  EXPECT_CALL(*mock_iter, Valid())
      .WillOnce(::testing::Return(true))   // after SeekToFirst
      .WillOnce(::testing::Return(false));  // after Next
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("only_key")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  
  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

// Test iteration over multiple elements
TEST_F(IteratorWrapperTest_380, IterationOverMultipleElements_380) {
  MockIterator* mock_iter = new MockIterator();
  
  ::testing::InSequence seq;
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("key1")));
  
  EXPECT_CALL(*mock_iter, Next()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("key2")));
  
  EXPECT_CALL(*mock_iter, Next()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("key3")));
  
  EXPECT_CALL(*mock_iter, Next()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key1");
  
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
  
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key3");
  
  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

// Test destructor deletes the owned iterator
TEST_F(IteratorWrapperTest_380, DestructorDeletesIterator_380) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  {
    IteratorWrapper wrapper(mock_iter);
    // wrapper goes out of scope, should delete mock_iter
  }
  // If the destructor doesn't delete, there will be a memory leak
  // Google Test with sanitizers would catch this
}

// Test that iter() returns the set iterator
TEST_F(IteratorWrapperTest_380, IterReturnsCurrentIterator_380) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  wrapper.Set(mock_iter);
  EXPECT_EQ(wrapper.iter(), mock_iter);
  
  // Clean up by setting to nullptr (Set should delete previous)
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
}

// Test Seek with empty slice
TEST_F(IteratorWrapperTest_380, SeekWithEmptySlice_380) {
  MockIterator* mock_iter = new MockIterator();
  Slice empty_target("");
  
  EXPECT_CALL(*mock_iter, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillRepeatedly(::testing::Return(Slice("")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.Seek(empty_target);
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "");
}

// Test key caching - key() should not call iter_->key() repeatedly
TEST_F(IteratorWrapperTest_380, KeyIsCached_380) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  // key() should be called once during Update after SeekToFirst
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).Times(1).WillOnce(::testing::Return(Slice("cached_key")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  
  // Multiple calls to key() should use the cached value
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
}

}  // namespace leveldb
