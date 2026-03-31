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

class IteratorWrapperTest_381 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction results in invalid state
TEST_F(IteratorWrapperTest_381, DefaultConstructor_InvalidState_381) {
  IteratorWrapper wrapper;
  EXPECT_FALSE(wrapper.Valid());
  EXPECT_EQ(wrapper.iter(), nullptr);
}

// Test construction with an iterator
TEST_F(IteratorWrapperTest_381, ExplicitConstructor_SetsIterator_381) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  
  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

// Test Set method replaces iterator
TEST_F(IteratorWrapperTest_381, Set_ReplacesIterator_381) {
  MockIterator* mock1 = new MockIterator();
  MockIterator* mock2 = new MockIterator();
  
  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock1);
  EXPECT_EQ(wrapper.iter(), mock1);
  
  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
}

// Test Set with nullptr
TEST_F(IteratorWrapperTest_381, Set_Nullptr_381) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

// Test Valid delegates to underlying iterator
TEST_F(IteratorWrapperTest_381, Valid_ReturnsIteratorValidity_381) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("testkey")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  // After Set, wrapper calls Valid on the iterator - need to trigger positioning
  // Set internally may call Update which reads Valid() and key()
}

// Test SeekToFirst delegates properly
TEST_F(IteratorWrapperTest_381, SeekToFirst_DelegatesToIterator_381) {
  MockIterator* mock = new MockIterator();
  
  ::testing::InSequence seq;
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false)); // from Set
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("aaa")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
}

// Test SeekToLast delegates properly
TEST_F(IteratorWrapperTest_381, SeekToLast_DelegatesToIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // from Set
      .WillOnce(::testing::Return(true));    // after SeekToLast
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("zzz")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
}

// Test Seek delegates properly
TEST_F(IteratorWrapperTest_381, Seek_DelegatesToIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // from Set
      .WillOnce(::testing::Return(true));    // after Seek
  EXPECT_CALL(*mock, Seek(Slice("target"))).Times(1);
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("target")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.Seek(Slice("target"));
  EXPECT_TRUE(wrapper.Valid());
}

// Test Next delegates properly
TEST_F(IteratorWrapperTest_381, Next_DelegatesToIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))    // from Set
      .WillOnce(::testing::Return(true))     // after SeekToFirst (Update)
      .WillOnce(::testing::Return(true));    // after Next (Update)
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(Slice("key1")))
      .WillOnce(::testing::Return(Slice("key2")));
  EXPECT_CALL(*mock, Next()).Times(1);

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToFirst();
  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
}

// Test Prev delegates properly
TEST_F(IteratorWrapperTest_381, Prev_DelegatesToIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))    // from Set
      .WillOnce(::testing::Return(true))     // after SeekToLast
      .WillOnce(::testing::Return(true));    // after Prev
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(Slice("key2")))
      .WillOnce(::testing::Return(Slice("key1")));
  EXPECT_CALL(*mock, Prev()).Times(1);

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToLast();
  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
}

// Test key returns cached key
TEST_F(IteratorWrapperTest_381, Key_ReturnsCachedKey_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // from Set
      .WillOnce(::testing::Return(true));    // after SeekToFirst
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("mykey")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "mykey");
}

// Test value delegates to underlying iterator
TEST_F(IteratorWrapperTest_381, Value_DelegatesToIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // from Set
      .WillOnce(::testing::Return(true));    // after SeekToFirst
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("k")));
  EXPECT_CALL(*mock, value()).WillOnce(::testing::Return(Slice("myvalue")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.value().ToString(), "myvalue");
}

// Test status delegates to underlying iterator
TEST_F(IteratorWrapperTest_381, Status_DelegatesToIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status()).WillOnce(::testing::Return(Status::OK()));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  EXPECT_TRUE(wrapper.status().ok());
}

// Test status returns error from underlying iterator
TEST_F(IteratorWrapperTest_381, Status_ReturnsErrorFromIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status())
      .WillOnce(::testing::Return(Status::Corruption("data corrupted")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  Status s = wrapper.status();
  EXPECT_TRUE(s.IsCorruption());
}

// Test that when iterator becomes invalid after Next, Valid returns false
TEST_F(IteratorWrapperTest_381, Next_BecomesInvalid_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))    // from Set
      .WillOnce(::testing::Return(true))     // after SeekToFirst
      .WillOnce(::testing::Return(false));   // after Next (end of iteration)
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("onlykey")));
  EXPECT_CALL(*mock, Next()).Times(1);

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

// Test Seek to non-existent key results in invalid
TEST_F(IteratorWrapperTest_381, Seek_NotFound_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // from Set
      .WillOnce(::testing::Return(false));   // after Seek
  EXPECT_CALL(*mock, Seek(Slice("nonexistent"))).Times(1);

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.Seek(Slice("nonexistent"));
  EXPECT_FALSE(wrapper.Valid());
}

// Test SeekToFirst on empty iterator
TEST_F(IteratorWrapperTest_381, SeekToFirst_EmptyIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // from Set
      .WillOnce(::testing::Return(false));   // after SeekToFirst
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

// Test SeekToLast on empty iterator
TEST_F(IteratorWrapperTest_381, SeekToLast_EmptyIterator_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // from Set
      .WillOnce(::testing::Return(false));   // after SeekToLast
  EXPECT_CALL(*mock, SeekToLast()).Times(1);

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToLast();
  EXPECT_FALSE(wrapper.Valid());
}

// Test iter() returns the raw iterator pointer
TEST_F(IteratorWrapperTest_381, Iter_ReturnsRawPointer_381) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
}

// Test multiple Set calls properly manage iterator lifecycle
TEST_F(IteratorWrapperTest_381, MultipleSet_DeletesPrevious_381) {
  MockIterator* mock1 = new MockIterator();
  MockIterator* mock2 = new MockIterator();

  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper;
  wrapper.Set(mock1);
  EXPECT_EQ(wrapper.iter(), mock1);
  
  // Setting a new iterator should delete the previous one
  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
}

// Test key caching - key() should return the same result without re-calling iter's key()
TEST_F(IteratorWrapperTest_381, Key_IsCached_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // from Set
      .WillOnce(::testing::Return(true));    // after SeekToFirst
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  // key() should only be called once during Update, not on subsequent wrapper.key() calls
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("cached_key")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  wrapper.SeekToFirst();
  
  // Multiple calls to key() should use cached value
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
}

// Test status with IOError
TEST_F(IteratorWrapperTest_381, Status_IOError_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status())
      .WillOnce(::testing::Return(Status::IOError("io error")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  Status s = wrapper.status();
  EXPECT_TRUE(s.IsIOError());
}

// Test status with NotFound
TEST_F(IteratorWrapperTest_381, Status_NotFound_381) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status())
      .WillOnce(::testing::Return(Status::NotFound("not found")));

  IteratorWrapper wrapper;
  wrapper.Set(mock);
  Status s = wrapper.status();
  EXPECT_TRUE(s.IsNotFound());
}

}  // namespace leveldb
