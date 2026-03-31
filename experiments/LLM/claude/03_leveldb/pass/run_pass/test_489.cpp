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

class IteratorWrapperTest_489 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

TEST_F(IteratorWrapperTest_489, DefaultConstructor_489) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_489, ConstructorWithNullIterator_489) {
  IteratorWrapper wrapper(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_489, ConstructorWithValidIterator_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_489, SetIterator_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);

  wrapper.Set(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_489, SetReplacesIterator_489) {
  MockIterator* mock1 = new MockIterator();
  MockIterator* mock2 = new MockIterator();
  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock1);
  EXPECT_EQ(wrapper.iter(), mock1);

  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
}

TEST_F(IteratorWrapperTest_489, SetToNull_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_489, ValidWhenIteratorIsValid_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("testkey")));

  IteratorWrapper wrapper;
  // Need to trigger update after setting - use SeekToFirst
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  wrapper.Set(mock);
  // After Set, if the iterator is valid, wrapper should reflect that
  // But Set calls Update internally
  EXPECT_TRUE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_489, ValidWhenIteratorIsInvalid_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_489, SeekToFirst_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))   // During Set
      .WillOnce(::testing::Return(true))    // After SeekToFirst (Update)
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("first")));

  IteratorWrapper wrapper(mock);
  EXPECT_FALSE(wrapper.Valid());

  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "first");
}

TEST_F(IteratorWrapperTest_489, SeekToLast_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("last")));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "last");
}

TEST_F(IteratorWrapperTest_489, Seek_489) {
  MockIterator* mock = new MockIterator();
  Slice target("target");
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("target")));

  IteratorWrapper wrapper(mock);
  wrapper.Seek(target);
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "target");
}

TEST_F(IteratorWrapperTest_489, Next_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))     // Set
      .WillOnce(::testing::Return(true))      // After SeekToFirst (Update)
      .WillOnce(::testing::Return(true))      // After Next (Update)
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(Slice("key1")))
      .WillOnce(::testing::Return(Slice("key2")))
      .WillRepeatedly(::testing::Return(Slice("key2")));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "key1");

  wrapper.Next();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

TEST_F(IteratorWrapperTest_489, Prev_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))     // Set
      .WillOnce(::testing::Return(true))      // After SeekToLast (Update)
      .WillOnce(::testing::Return(true))      // After Prev (Update)
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Prev()).Times(1);
  EXPECT_CALL(*mock, key())
      .WillOnce(::testing::Return(Slice("key3")))
      .WillOnce(::testing::Return(Slice("key2")))
      .WillRepeatedly(::testing::Return(Slice("key2")));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_EQ(wrapper.key().ToString(), "key3");

  wrapper.Prev();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

TEST_F(IteratorWrapperTest_489, Value_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("key")));
  EXPECT_CALL(*mock, value()).WillRepeatedly(::testing::Return(Slice("value")));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.value().ToString(), "value");
}

TEST_F(IteratorWrapperTest_489, Status_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status()).WillRepeatedly(::testing::Return(Status::OK()));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_489, StatusWithError_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, status())
      .WillRepeatedly(::testing::Return(Status::Corruption("corrupted")));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.status().IsCorruption());
}

TEST_F(IteratorWrapperTest_489, NextMakesIteratorInvalid_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))     // Set
      .WillOnce(::testing::Return(true))      // After SeekToFirst
      .WillOnce(::testing::Return(false))     // After Next (end of iteration)
      .WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(::testing::Return(Slice("only")));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());

  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_489, SeekToFirstOnEmptyIterator_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_489, KeyIsCached_489) {
  // The wrapper caches the key, so key() on the underlying iterator
  // should not be called every time wrapper.key() is called
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid())
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  // key() should be called only once during Update after SeekToFirst
  EXPECT_CALL(*mock, key()).Times(1).WillOnce(::testing::Return(Slice("cached")));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();

  // Multiple calls to key() should use cached value
  EXPECT_EQ(wrapper.key().ToString(), "cached");
  EXPECT_EQ(wrapper.key().ToString(), "cached");
  EXPECT_EQ(wrapper.key().ToString(), "cached");
}

TEST_F(IteratorWrapperTest_489, IterReturnsUnderlyingIterator_489) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_489, DestructorDeletesIterator_489) {
  // We can verify this by checking that setting a new iterator
  // doesn't cause memory issues (basic sanity)
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(::testing::Return(false));

  {
    IteratorWrapper wrapper(mock);
    // mock will be deleted when wrapper goes out of scope
  }
  // If we reach here without crashes, the destructor handled cleanup
}

TEST_F(IteratorWrapperTest_489, MultipleSeekOperations_489) {
  MockIterator* mock = new MockIterator();
  ::testing::InSequence seq;

  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(false)); // Set

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("a")));

  EXPECT_CALL(*mock, Seek(::testing::_)).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("b")));

  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock, key()).WillOnce(::testing::Return(Slice("z")));

  IteratorWrapper wrapper(mock);

  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "a");

  wrapper.Seek(Slice("b"));
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "b");

  wrapper.SeekToLast();
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "z");
}

}  // namespace leveldb
