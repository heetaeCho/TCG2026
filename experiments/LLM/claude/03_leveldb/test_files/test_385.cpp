#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;

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

class IteratorWrapperTest_385 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(IteratorWrapperTest_385, DefaultConstructor_385) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_385, ExplicitConstructorWithIterator_385) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));
  
  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_385, SetIterator_385) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));
  
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  
  wrapper.Set(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_385, SetNullIterator_385) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));
  
  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
  
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_385, SeekToFirstCallsUnderlyingIterator_385) {
  MockIterator* mock = new MockIterator();
  std::string key_str = "hello";
  Slice key_slice(key_str);
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "hello");
}

TEST_F(IteratorWrapperTest_385, SeekToLastCallsUnderlyingIterator_385) {
  MockIterator* mock = new MockIterator();
  std::string key_str = "world";
  Slice key_slice(key_str);
  
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "world");
}

TEST_F(IteratorWrapperTest_385, SeekCallsUnderlyingIterator_385) {
  MockIterator* mock = new MockIterator();
  std::string key_str = "target";
  Slice target_slice(key_str);
  std::string found_key = "target";
  Slice found_slice(found_key);
  
  EXPECT_CALL(*mock, Seek(target_slice)).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(found_slice));
  
  IteratorWrapper wrapper(mock);
  wrapper.Seek(target_slice);
  
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "target");
}

TEST_F(IteratorWrapperTest_385, NextCallsUnderlyingIterator_385) {
  MockIterator* mock = new MockIterator();
  std::string key1 = "aaa";
  std::string key2 = "bbb";
  Slice slice1(key1);
  Slice slice2(key2);
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(Return(true))   // after SeekToFirst
                              .WillOnce(Return(true)); // after Next
  EXPECT_CALL(*mock, key()).WillOnce(Return(slice1))
                           .WillOnce(Return(slice2));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "aaa");
  
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "bbb");
}

TEST_F(IteratorWrapperTest_385, PrevCallsUnderlyingIterator_385) {
  MockIterator* mock = new MockIterator();
  std::string key1 = "bbb";
  std::string key2 = "aaa";
  Slice slice1(key1);
  Slice slice2(key2);
  
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Prev()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(Return(true))
                              .WillOnce(Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(Return(slice1))
                           .WillOnce(Return(slice2));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "bbb");
  
  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "aaa");
}

TEST_F(IteratorWrapperTest_385, ValidReturnsFalseWhenIteratorInvalid_385) {
  MockIterator* mock = new MockIterator();
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_385, ValueDelegatesToUnderlyingIterator_385) {
  MockIterator* mock = new MockIterator();
  std::string key_str = "key";
  std::string val_str = "value";
  Slice key_slice(key_str);
  Slice val_slice(val_str);
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));
  EXPECT_CALL(*mock, value()).WillOnce(Return(val_slice));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  EXPECT_EQ(wrapper.value().ToString(), "value");
}

TEST_F(IteratorWrapperTest_385, StatusDelegatesToUnderlyingIterator_385) {
  MockIterator* mock = new MockIterator();
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(Slice("key")));
  EXPECT_CALL(*mock, status()).WillOnce(Return(Status::OK()));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_385, StatusReturnsErrorFromUnderlyingIterator_385) {
  MockIterator* mock = new MockIterator();
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));
  EXPECT_CALL(*mock, status()).WillOnce(Return(Status::Corruption("corrupt")));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  EXPECT_TRUE(wrapper.status().IsCorruption());
}

TEST_F(IteratorWrapperTest_385, SetReplacesOldIterator_385) {
  MockIterator* mock1 = new MockIterator();
  MockIterator* mock2 = new MockIterator();
  
  std::string key1 = "first";
  std::string key2 = "second";
  Slice slice1(key1);
  Slice slice2(key2);
  
  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock1, key()).WillRepeatedly(Return(slice1));
  EXPECT_CALL(*mock1, SeekToFirst()).Times(1);
  
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock2, key()).WillRepeatedly(Return(slice2));
  EXPECT_CALL(*mock2, SeekToFirst()).Times(1);
  
  IteratorWrapper wrapper(mock1);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "first");
  
  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
  
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "second");
}

TEST_F(IteratorWrapperTest_385, NextTransitionsToInvalid_385) {
  MockIterator* mock = new MockIterator();
  std::string key_str = "only_key";
  Slice key_slice(key_str);
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(Return(true))   // after SeekToFirst
                              .WillOnce(Return(false)); // after Next
  EXPECT_CALL(*mock, key()).WillOnce(Return(key_slice));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "only_key");
  
  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_385, SeekToFirstOnEmptyIterator_385) {
  MockIterator* mock = new MockIterator();
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_385, SeekToNonexistentKey_385) {
  MockIterator* mock = new MockIterator();
  Slice target("nonexistent");
  
  EXPECT_CALL(*mock, Seek(target)).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(Return(false));
  
  IteratorWrapper wrapper(mock);
  wrapper.Seek(target);
  
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_385, KeyCachingBehavior_385) {
  MockIterator* mock = new MockIterator();
  std::string key_str = "cached_key";
  Slice key_slice(key_str);
  
  // key() on the underlying iterator should be called during Update(),
  // but cached thereafter. We verify the wrapper returns the correct key.
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(Return(key_slice));
  
  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  // Multiple calls to key() should return the same cached value
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
}

TEST_F(IteratorWrapperTest_385, MultipleSeekOperations_385) {
  MockIterator* mock = new MockIterator();
  std::string key1 = "alpha";
  std::string key2 = "beta";
  std::string key3 = "gamma";
  Slice slice1(key1);
  Slice slice2(key2);
  Slice slice3(key3);
  
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Seek(_)).Times(1);
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(Return(slice1))
                           .WillOnce(Return(slice2))
                           .WillOnce(Return(slice3));
  
  IteratorWrapper wrapper(mock);
  
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "alpha");
  
  wrapper.Seek(Slice("beta"));
  EXPECT_EQ(wrapper.key().ToString(), "beta");
  
  wrapper.SeekToLast();
  EXPECT_EQ(wrapper.key().ToString(), "gamma");
}

}  // namespace leveldb
