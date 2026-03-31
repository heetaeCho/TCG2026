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

class IteratorWrapperTest_386 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(IteratorWrapperTest_386, DefaultConstructor_386) {
  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_386, ExplicitConstructorWithIterator_386) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));
  EXPECT_CALL(*mock, SeekToFirst()).Times(0);

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_386, SetIterator_386) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));

  IteratorWrapper wrapper;
  EXPECT_EQ(wrapper.iter(), nullptr);
  
  wrapper.Set(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_386, SetNullIterator_386) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.Set(nullptr);
  EXPECT_EQ(wrapper.iter(), nullptr);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_386, SeekToFirst_386) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "first_key";
  Slice key_slice(key_data);

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "first_key");
}

TEST_F(IteratorWrapperTest_386, SeekToLast_386) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "last_key";
  Slice key_slice(key_data);

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "last_key");
}

TEST_F(IteratorWrapperTest_386, SeekToTarget_386) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "target_key";
  Slice key_slice(key_data);
  Slice target("target_key");

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, Seek(testing::Eq(target))).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.Seek(target);
  
  EXPECT_TRUE(wrapper.Valid());
  EXPECT_EQ(wrapper.key().ToString(), "target_key");
}

TEST_F(IteratorWrapperTest_386, Next_386) {
  MockIterator* mock = new MockIterator();
  std::string key1 = "key1";
  std::string key2 = "key2";
  Slice key_slice1(key1);
  Slice key_slice2(key2);

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, key())
      .WillOnce(Return(key_slice1))
      .WillRepeatedly(Return(key_slice2));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "key1");

  wrapper.Next();
  EXPECT_EQ(wrapper.key().ToString(), "key2");
}

TEST_F(IteratorWrapperTest_386, Prev_386) {
  MockIterator* mock = new MockIterator();
  std::string key1 = "key1";
  std::string key2 = "key2";
  Slice key_slice1(key1);
  Slice key_slice2(key2);

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Prev()).Times(1);
  EXPECT_CALL(*mock, key())
      .WillOnce(Return(key_slice2))
      .WillRepeatedly(Return(key_slice1));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_EQ(wrapper.key().ToString(), "key2");

  wrapper.Prev();
  EXPECT_EQ(wrapper.key().ToString(), "key1");
}

TEST_F(IteratorWrapperTest_386, Value_386) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "key";
  std::string val_data = "value";
  Slice key_slice(key_data);
  Slice val_slice(val_data);

  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));
  EXPECT_CALL(*mock, value()).WillRepeatedly(Return(val_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  EXPECT_EQ(wrapper.value().ToString(), "value");
}

TEST_F(IteratorWrapperTest_386, Status_386) {
  MockIterator* mock = new MockIterator();
  
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));
  EXPECT_CALL(*mock, status()).WillRepeatedly(Return(Status::OK()));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.status().ok());
}

TEST_F(IteratorWrapperTest_386, StatusWithError_386) {
  MockIterator* mock = new MockIterator();
  
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));
  EXPECT_CALL(*mock, status()).WillRepeatedly(
      Return(Status::Corruption("data corruption")));

  IteratorWrapper wrapper(mock);
  EXPECT_TRUE(wrapper.status().IsCorruption());
}

TEST_F(IteratorWrapperTest_386, ValidBecomesFalseAfterEndReached_386) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "only_key";
  Slice key_slice(key_data);

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Next()).Times(1);
  EXPECT_CALL(*mock, Valid())
      .WillOnce(Return(true))   // after SeekToFirst
      .WillOnce(Return(false)); // after Next
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_TRUE(wrapper.Valid());

  wrapper.Next();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_386, SetReplacesIterator_386) {
  MockIterator* mock1 = new MockIterator();
  MockIterator* mock2 = new MockIterator();
  std::string key1 = "key_from_iter1";
  std::string key2 = "key_from_iter2";
  Slice key_slice1(key1);
  Slice key_slice2(key2);

  EXPECT_CALL(*mock1, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock1, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock1, key()).WillRepeatedly(Return(key_slice1));

  EXPECT_CALL(*mock2, Valid()).WillRepeatedly(Return(true));
  EXPECT_CALL(*mock2, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock2, key()).WillRepeatedly(Return(key_slice2));

  IteratorWrapper wrapper(mock1);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "key_from_iter1");

  wrapper.Set(mock2);
  EXPECT_EQ(wrapper.iter(), mock2);
  wrapper.SeekToFirst();
  EXPECT_EQ(wrapper.key().ToString(), "key_from_iter2");
}

TEST_F(IteratorWrapperTest_386, SeekToEmptyIterator_386) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_386, SeekToLastOnEmptyIterator_386) {
  MockIterator* mock = new MockIterator();

  EXPECT_CALL(*mock, SeekToLast()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToLast();
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_386, SeekNonExistentKey_386) {
  MockIterator* mock = new MockIterator();
  Slice target("nonexistent");

  EXPECT_CALL(*mock, Seek(testing::Eq(target))).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));

  IteratorWrapper wrapper(mock);
  wrapper.Seek(target);
  EXPECT_FALSE(wrapper.Valid());
}

TEST_F(IteratorWrapperTest_386, KeyCachingAfterSeek_386) {
  MockIterator* mock = new MockIterator();
  std::string key_data = "cached_key";
  Slice key_slice(key_data);

  EXPECT_CALL(*mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(true));
  // key() should be called during Update, but cached afterwards
  EXPECT_CALL(*mock, key()).WillRepeatedly(Return(key_slice));

  IteratorWrapper wrapper(mock);
  wrapper.SeekToFirst();
  
  // Multiple calls to key() should return consistent results
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
  EXPECT_EQ(wrapper.key().ToString(), "cached_key");
}

TEST_F(IteratorWrapperTest_386, IterReturnsCurrentIterator_386) {
  MockIterator* mock = new MockIterator();
  EXPECT_CALL(*mock, Valid()).WillRepeatedly(Return(false));

  IteratorWrapper wrapper(mock);
  EXPECT_EQ(wrapper.iter(), mock);
}

TEST_F(IteratorWrapperTest_386, DestructorDeletesIterator_386) {
  // This test verifies that when IteratorWrapper goes out of scope,
  // or Set(nullptr) is called, the old iterator is deleted.
  // We use a flag to detect deletion.
  bool deleted = false;
  
  class DeletionTrackingIterator : public Iterator {
   public:
    bool* deleted_;
    explicit DeletionTrackingIterator(bool* d) : deleted_(d) {}
    ~DeletionTrackingIterator() override { *deleted_ = true; }
    bool Valid() const override { return false; }
    void SeekToFirst() override {}
    void SeekToLast() override {}
    void Seek(const Slice&) override {}
    void Next() override {}
    void Prev() override {}
    Slice key() const override { return Slice(); }
    Slice value() const override { return Slice(); }
    Status status() const override { return Status::OK(); }
  };

  {
    IteratorWrapper wrapper(new DeletionTrackingIterator(&deleted));
    EXPECT_FALSE(deleted);
  }
  EXPECT_TRUE(deleted);
}

TEST_F(IteratorWrapperTest_386, SetDeletesOldIterator_386) {
  bool deleted = false;
  
  class DeletionTrackingIterator : public Iterator {
   public:
    bool* deleted_;
    explicit DeletionTrackingIterator(bool* d) : deleted_(d) {}
    ~DeletionTrackingIterator() override { *deleted_ = true; }
    bool Valid() const override { return false; }
    void SeekToFirst() override {}
    void SeekToLast() override {}
    void Seek(const Slice&) override {}
    void Next() override {}
    void Prev() override {}
    Slice key() const override { return Slice(); }
    Slice value() const override { return Slice(); }
    Status status() const override { return Status::OK(); }
  };

  IteratorWrapper wrapper(new DeletionTrackingIterator(&deleted));
  EXPECT_FALSE(deleted);
  
  wrapper.Set(nullptr);
  EXPECT_TRUE(deleted);
}

}  // namespace leveldb
