#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

// Mock iterator to simulate Iterator behavior
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

class IteratorWrapperTest_384 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates an invalid wrapper
TEST_F(IteratorWrapperTest_384, DefaultConstructorCreatesInvalidWrapper_384) {
  IteratorWrapper wrapper;
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

// Test constructor with iterator argument
TEST_F(IteratorWrapperTest_384, ConstructorWithIterator_384) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  EXPECT_EQ(wrapper.iter(), mock_iter);
}

// Test Set method with a new iterator
TEST_F(IteratorWrapperTest_384, SetIterator_384) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  
  wrapper.Set(mock_iter);
  EXPECT_EQ(wrapper.iter(), mock_iter);
}

// Test Set method replaces existing iterator
TEST_F(IteratorWrapperTest_384, SetReplacesExistingIterator_384) {
  MockIterator* mock_iter1 = new MockIterator();
  MockIterator* mock_iter2 = new MockIterator();
  EXPECT_CALL(*mock_iter1, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock_iter2, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter1);
  EXPECT_EQ(wrapper.iter(), mock_iter1);
  
  wrapper.Set(mock_iter2);
  EXPECT_EQ(wrapper.iter(), mock_iter2);
}

// Test Set with nullptr
TEST_F(IteratorWrapperTest_384, SetNullptr_384) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

// Test Valid reflects underlying iterator's valid state after SeekToFirst
TEST_F(IteratorWrapperTest_384, ValidAfterSeekToFirst_384) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("key1")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
}

// Test Valid returns false when underlying iterator is not valid
TEST_F(IteratorWrapperTest_384, InvalidAfterSeekToFirstOnEmptyIterator_384) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

// Test Seek calls underlying iterator's Seek
TEST_F(IteratorWrapperTest_384, SeekCallsUnderlyingSeek_384) {
  MockIterator* mock_iter = new MockIterator();
  Slice target("target_key");
  
  EXPECT_CALL(*mock_iter, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("target_key")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.Seek(target);
  EXPECT_TRUE(wrapper.Valid());
}

// Test Seek with key not found (iterator becomes invalid)
TEST_F(IteratorWrapperTest_384, SeekKeyNotFound_384) {
  MockIterator* mock_iter = new MockIterator();
  Slice target("nonexistent");
  
  EXPECT_CALL(*mock_iter, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.Seek(target);
  EXPECT_FALSE(wrapper.Valid());
}

// Test SeekToLast
TEST_F(IteratorWrapperTest_384, SeekToLast_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToLast()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("last_key")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
}

// Test Next advances iterator
TEST_F(IteratorWrapperTest_384, NextAdvancesIterator_384) {
  MockIterator* mock_iter = new MockIterator();
  
  // SeekToFirst
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Next()).Times(1);
  EXPECT_CALL(*mock_iter, Valid())
      .WillOnce(::testing::Return(true))   // after SeekToFirst
      .WillOnce(::testing::Return(true));   // after Next
  EXPECT_CALL(*mock_iter, key())
      .WillOnce(::testing::Return(Slice("key1")))   // after SeekToFirst
      .WillOnce(::testing::Return(Slice("key2")));   // after Next
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key1");
  
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

// Test Prev moves iterator backward
TEST_F(IteratorWrapperTest_384, PrevMovesBackward_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToLast()).Times(1);
  EXPECT_CALL(*mock_iter, Prev()).Times(1);
  EXPECT_CALL(*mock_iter, Valid())
      .WillOnce(::testing::Return(true))   // after SeekToLast
      .WillOnce(::testing::Return(true));   // after Prev
  EXPECT_CALL(*mock_iter, key())
      .WillOnce(::testing::Return(Slice("key2")))   // after SeekToLast
      .WillOnce(::testing::Return(Slice("key1")));   // after Prev
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
  
  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key1");
}

// Test key returns cached key from wrapper
TEST_F(IteratorWrapperTest_384, KeyReturnsCachedKey_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("test_key")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  
  Slice k = wrapper.key();
  EXPECT_EQ(k.ToString(), "test_key");
}

// Test value delegates to underlying iterator
TEST_F(IteratorWrapperTest_384, ValueDelegatesToUnderlyingIterator_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("key")));
  EXPECT_CALL(*mock_iter, value()).WillOnce(::testing::Return(Slice("value")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  
  Slice v = wrapper.value();
  EXPECT_EQ(v.ToString(), "value");
}

// Test status delegates to underlying iterator
TEST_F(IteratorWrapperTest_384, StatusDelegatesToUnderlyingIterator_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, status()).WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  Status s = wrapper.status();
  EXPECT_TRUE(s.ok());
}

// Test status returns error when underlying iterator has error
TEST_F(IteratorWrapperTest_384, StatusReturnsErrorFromUnderlying_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, status())
      .WillOnce(::testing::Return(Status::Corruption("data corrupted")));
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  Status s = wrapper.status();
  EXPECT_TRUE(s.IsCorruption());
}

// Test Next past end makes iterator invalid
TEST_F(IteratorWrapperTest_384, NextPastEndMakesInvalid_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Next()).Times(1);
  EXPECT_CALL(*mock_iter, Valid())
      .WillOnce(::testing::Return(true))    // after SeekToFirst
      .WillOnce(::testing::Return(false));   // after Next (past end)
  EXPECT_CALL(*mock_iter, key())
      .WillOnce(::testing::Return(Slice("only_key")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  
  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

// Test Prev before beginning makes iterator invalid
TEST_F(IteratorWrapperTest_384, PrevBeforeBeginningMakesInvalid_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Prev()).Times(1);
  EXPECT_CALL(*mock_iter, Valid())
      .WillOnce(::testing::Return(true))    // after SeekToFirst
      .WillOnce(::testing::Return(false));   // after Prev (before beginning)
  EXPECT_CALL(*mock_iter, key())
      .WillOnce(::testing::Return(Slice("first_key")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  
  wrapper.Prev();
  EXPECT_FALSE(wrapper.Valid());
}

// Test Seek with empty key
TEST_F(IteratorWrapperTest_384, SeekWithEmptyKey_384) {
  MockIterator* mock_iter = new MockIterator();
  Slice empty_key("");
  
  EXPECT_CALL(*mock_iter, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key()).WillOnce(::testing::Return(Slice("a")));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.Seek(empty_key);
  EXPECT_TRUE(wrapper.Valid());
}

// Test multiple Seek operations
TEST_F(IteratorWrapperTest_384, MultipleSeekOperations_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, Seek(::testing::_)).Times(2);
  EXPECT_CALL(*mock_iter, Valid())
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_iter, key())
      .WillOnce(::testing::Return(Slice("key1")))
      .WillOnce(::testing::Return(Slice("key2")));
  
  IteratorWrapper wrapper(mock_iter);
  
  wrapper.Seek(Slice("key1"));
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key1");
  
  wrapper.Seek(Slice("key2"));
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

// Test SeekToLast on empty iterator
TEST_F(IteratorWrapperTest_384, SeekToLastOnEmpty_384) {
  MockIterator* mock_iter = new MockIterator();
  
  EXPECT_CALL(*mock_iter, SeekToLast()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(false));
  
  IteratorWrapper wrapper(mock_iter);
  wrapper.SeekToLast();
  EXPECT_FALSE(wrapper.Valid());
}

// Test iter() accessor returns the set iterator
TEST_F(IteratorWrapperTest_384, IterAccessor_384) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  
  wrapper.Set(mock_iter);
  EXPECT_EQ(wrapper.iter(), mock_iter);
}

// Test destructor cleans up the iterator (no crash)
TEST_F(IteratorWrapperTest_384, DestructorCleansUp_384) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_iter, Valid()).WillRepeatedly(::testing::Return(false));
  
  {
    IteratorWrapper wrapper(mock_iter);
    // wrapper goes out of scope, should delete mock_iter
  }
  // If we get here without crash, the test passes
}

}  // namespace leveldb
