#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

// Mock Iterator for testing
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

class IteratorWrapperTest_377 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

TEST_F(IteratorWrapperTest_377, DefaultConstructorCreatesInvalidWrapper_377) {
  IteratorWrapper wrapper;
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_377, ExplicitConstructorWithNullptr_377) {
  IteratorWrapper wrapper(nullptr);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_377, ExplicitConstructorWithValidIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("hello")));

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "hello");
}

TEST_F(IteratorWrapperTest_377, SetWithNullptrMakesInvalid_377) {
  IteratorWrapper wrapper;
  wrapper.Set(nullptr);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_377, SetWithValidIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("key1")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  EXPECT_EQ(wrapper.iter(), mock);
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key1");
}

TEST_F(IteratorWrapperTest_377, SetDeletesPreviousIterator_377) {
  // First iterator
  MockIterator* mock1 = new MockIterator();
  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock1, key()).WillRepeatedly(::testing::Return(Slice("key1")));

  // Second iterator
  MockIterator* mock2 = new MockIterator();
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock2, key()).WillRepeatedly(::testing::Return(Slice("key2")));

  IteratorWrapper wrapper;
  wrapper.Set(mock1);
  EXPECT_EQ(wrapper.iter(), mock1);

  // Setting a new iterator should delete the old one
  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

TEST_F(IteratorWrapperTest_377, SetWithInvalidIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  EXPECT_EQ(wrapper.iter(), mock);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_377, SeekToFirstDelegatesToIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))  // Initial Set when invalid
      .WillOnce(::testing::Return(true));   // After SeekToFirst
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("first")));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "first");
}

TEST_F(IteratorWrapperTest_377, SeekToLastDelegatesToIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("last")));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "last");
}

TEST_F(IteratorWrapperTest_377, SeekDelegatesToIterator_377) {
  MockIterator* mock = new MockIterator();
  Slice target("target");
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("target")));

  IteratorWrapper wrapper(mock);
  wrapper.Seek(target);
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "target");
}

TEST_F(IteratorWrapperTest_377, NextDelegatesToIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(true))   // Initial Set
      .WillOnce(::testing::Return(true));   // After Next
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(Slice("key1")))
      .WillOnce(::testing::Return(Slice("key2")));

  IteratorWrapper wrapper(mock);
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

TEST_F(IteratorWrapperTest_377, PrevDelegatesToIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, Prev()).Times(1);
  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(Slice("key2")))
      .WillOnce(::testing::Return(Slice("key1")));

  IteratorWrapper wrapper(mock);
  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key1");
}

TEST_F(IteratorWrapperTest_377, ValueDelegatesToIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("key")));
  EXPECT_CALL(*mock, value()).WillOnce(::testing::Return(Slice("value")));

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.value().ToString(), "value");
}

TEST_F(IteratorWrapperTest_377, StatusDelegatesToIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status()).WillOnce(::testing::Return(Status::OK()));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_377, StatusReturnsErrorFromIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status())
      .WillOnce(::testing::Return(Status::Corruption("corrupted")));

  IteratorWrapper wrapper(mock);
  Status s = wrapper.status();
  EXPECT_TRUE(s.IsCorruption());
}

TEST_F(IteratorWrapperTest_377, NextMakesInvalidWhenIteratorExhausted_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(true))    // Initial Set
      .WillOnce(::testing::Return(false));   // After Next (exhausted)
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("key1")));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.Valid());
  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_377, SetReplacesIteratorAndUpdatesValidity_377) {
  MockIterator* mock1 = new MockIterator();
  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock1, key()).WillRepeatedly(::testing::Return(Slice("a")));

  MockIterator* mock2 = new MockIterator();
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock1);
  EXPECT_TRUE(wrapper.Valid());

  wrapper.Set(mock2);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), mock2);
}

TEST_F(IteratorWrapperTest_377, DestructorDeletesIterator_377) {
  // We can't directly verify deletion, but we can ensure no crash/leak
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  {
    IteratorWrapper wrapper(mock);
    // wrapper goes out of scope, should delete mock
  }
  // If this doesn't crash or leak, the test passes
}

TEST_F(IteratorWrapperTest_377, KeyReturnsCachedKey_377) {
  // The wrapper caches the key to avoid virtual function call overhead.
  // Verify that key() returns the correct value.
  MockIterator* mock = new MockIterator();
  std::string key_data = "cached_key";
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice(key_data)));

  IteratorWrapper wrapper(mock);
  Slice k = wrapper.key();
  EXPECT_EQ(k.ToString(), "cached_key");
}

TEST_F(IteratorWrapperTest_377, IterReturnsUnderlyingIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_377, IterReturnsNullWhenNoIteratorSet_377) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_377, SetToNullAfterValidIterator_377) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("key")));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.Valid());

  wrapper.Set(nullptr);
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_377, MultipleSeekOperations_377) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  
  // Initial construction - invalid
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false));
  
  // SeekToFirst
  EXPECT_CALL(*mock, SeekToFirst());
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("aaa")));
  
  // Seek to specific key
  EXPECT_CALL(*mock, Seek(::testing::_));
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("bbb")));
  
  // SeekToLast
  EXPECT_CALL(*mock, SeekToLast());
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("zzz")));

  IteratorWrapper wrapper(mock);
  EXPECT_FALSE(wrapper.Valid());

  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "aaa");

  wrapper.Seek(Slice("bbb"));
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "bbb");

  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "zzz");
}

}  // namespace leveldb
