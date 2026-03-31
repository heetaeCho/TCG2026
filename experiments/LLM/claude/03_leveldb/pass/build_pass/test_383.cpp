#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

// Mock Iterator to use as a collaborator
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

class IteratorWrapperTest_383 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates invalid wrapper with null iter
TEST_F(IteratorWrapperTest_383, DefaultConstructor_383) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

// Test explicit constructor with an iterator
TEST_F(IteratorWrapperTest_383, ExplicitConstructorWithIterator_383) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

// Test Set method replaces iterator
TEST_F(IteratorWrapperTest_383, SetReplacesIterator_383) {
  MockIterator* mock1 = new MockIterator();
  MockIterator* mock2 = new MockIterator();

  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper;
  wrapper.Set(mock1);
  EXPECT_EQ(wrapper.iter(), mock1);

  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
}

// Test Set with nullptr
TEST_F(IteratorWrapperTest_383, SetWithNullptr_383) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

// Test Valid returns true when underlying iterator is valid
TEST_F(IteratorWrapperTest_383, ValidWhenIteratorIsValid_383) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "testkey";
  Slice key_slice(key_data);

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(key_slice));

  IteratorWrapper wrapper(mock);
  // After construction with Set inside constructor, Update is called
  // We need to trigger an operation to update
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  wrapper.SeekToFirst();

  EXPECT_TRUE(wrapper.Valid());
}

// Test Valid returns false when underlying iterator is invalid
TEST_F(IteratorWrapperTest_383, InvalidWhenIteratorIsInvalid_383) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  wrapper.SeekToFirst();

  EXPECT_FALSE(wrapper.Valid());
}

// Test SeekToFirst delegates to underlying iterator
TEST_F(IteratorWrapperTest_383, SeekToFirstDelegates_383) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "first";
  Slice key_slice(key_data);

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();

  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "first");
}

// Test SeekToLast delegates to underlying iterator
TEST_F(IteratorWrapperTest_383, SeekToLastDelegates_383) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "last";
  Slice key_slice(key_data);

  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();

  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "last");
}

// Test Seek delegates to underlying iterator
TEST_F(IteratorWrapperTest_383, SeekDelegates_383) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "target";
  Slice key_slice(key_data);
  Slice target("target");

  EXPECT_CALL(*mock, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.Seek(target);

  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "target");
}

// Test Next delegates to underlying iterator
TEST_F(IteratorWrapperTest_383, NextDelegates_383) {
  MockIterator* mock = new MockIterator();
  std::string key1 = "key1";
  std::string key2 = "key2";
  Slice key1_slice(key1);
  Slice key2_slice(key2);

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(key1_slice))   // After SeekToFirst
      .WillRepeatedly(::testing::Return(key2_slice));  // After Next

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "key1");

  wrapper.Next();
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

// Test Prev delegates to underlying iterator
TEST_F(IteratorWrapperTest_383, PrevDelegates_383) {
  MockIterator* mock = new MockIterator();
  std::string key1 = "key1";
  std::string key2 = "key2";
  Slice key1_slice(key1);
  Slice key2_slice(key2);

  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Prev()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(key2_slice))   // After SeekToLast
      .WillRepeatedly(::testing::Return(key1_slice));  // After Prev

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_EQ(wrapper.key().ToString(), "key2");

  wrapper.Prev();
  EXPECT_EQ(wrapper.key().ToString(), "key1");
}

// Test value delegates to underlying iterator
TEST_F(IteratorWrapperTest_383, ValueDelegates_383) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "key";
  std::string value_data = "value";
  Slice key_slice(key_data);
  Slice value_slice(value_data);

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(key_slice));
  EXPECT_CALL(*mock, value()).WillRepeatedly(::testing::Return(value_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();

  EXPECT_EQ(wrapper.value().ToString(), "value");
}

// Test status delegates to underlying iterator
TEST_F(IteratorWrapperTest_383, StatusDelegates_383) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status()).WillRepeatedly(::testing::Return(Status::OK()));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.status().ok());
}

// Test status returns error status from underlying iterator
TEST_F(IteratorWrapperTest_383, StatusReturnsError_383) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status()).WillRepeatedly(
      ::testing::Return(Status::Corruption("test error")));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.status().IsCorruption());
}

// Test iteration sequence: SeekToFirst, multiple Next, until invalid
TEST_F(IteratorWrapperTest_383, FullForwardIteration_383) {
  MockIterator* mock = new MockIterator();
  std::string key1 = "a";
  std::string key2 = "b";
  std::string key3 = "c";
  Slice key1_slice(key1);
  Slice key2_slice(key2);
  Slice key3_slice(key3);

  // Valid sequence: true, true, true, false (after 3 items)
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Next()).Times(3);
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(true))   // after SeekToFirst
      .WillOnce(::testing::Return(true))   // after Next 1
      .WillOnce(::testing::Return(true))   // after Next 2
      .WillOnce(::testing::Return(false)); // after Next 3

  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(key1_slice))
      .WillOnce(::testing::Return(key2_slice))
      .WillOnce(::testing::Return(key3_slice));

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

// Test key caching - key() should return cached key without calling iter_->key() repeatedly
TEST_F(IteratorWrapperTest_383, KeyCaching_383) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "cached_key";
  Slice key_slice(key_data);

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  // key() should be called only during Update, not on every wrapper.key() call
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();

  // Multiple calls to key() should use cached value
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
}

// Test Seek with empty slice
TEST_F(IteratorWrapperTest_383, SeekWithEmptySlice_383) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "";
  Slice key_slice(key_data);
  Slice target("");

  EXPECT_CALL(*mock, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.Seek(target);

  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "");
}

// Test that Set deletes the old iterator
TEST_F(IteratorWrapperTest_383, SetDeletesOldIterator_383) {
  // We can't directly test deletion, but we can verify the new iterator is set
  MockIterator* mock1 = new MockIterator();
  MockIterator* mock2 = new MockIterator();

  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper;
  wrapper.Set(mock1);
  EXPECT_EQ(wrapper.iter(), mock1);

  // Setting a new iterator should delete mock1
  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
  // mock1 should be deleted at this point - if not, it would be a memory leak
}

// Test SeekToFirst on empty iterator (Valid returns false)
TEST_F(IteratorWrapperTest_383, SeekToFirstOnEmptyIterator_383) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();

  EXPECT_FALSE(wrapper.Valid());
}

// Test SeekToLast on empty iterator (Valid returns false)
TEST_F(IteratorWrapperTest_383, SeekToLastOnEmptyIterator_383) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();

  EXPECT_FALSE(wrapper.Valid());
}

// Test iter() accessor
TEST_F(IteratorWrapperTest_383, IterAccessor_383) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

// Test default wrapper iter() returns nullptr
TEST_F(IteratorWrapperTest_383, DefaultWrapperIterReturnsNull_383) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
}

}  // namespace leveldb
