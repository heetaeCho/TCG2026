// iterator_wrapper_test_376.cc
#include "table/iterator_wrapper.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;

namespace leveldb {

// A strict mock of the external collaborator: leveldb::Iterator.
// We verify only the calls/returns that are observable via IteratorWrapper's API.
class MockIterator : public Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, Seek, (const Slice& k), (override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(Slice, key, (), (const, override));
  MOCK_METHOD(Slice, value, (), (const, override));
  MOCK_METHOD(Status, status, (), (const, override));
};

class IteratorWrapperTest_376 : public ::testing::Test {};

TEST_F(IteratorWrapperTest_376, DefaultConstructed_IterIsNull_376) {
  IteratorWrapper w;
  EXPECT_EQ(w.iter(), nullptr);
}

TEST_F(IteratorWrapperTest_376, ConstructWithIter_ExposesSamePointer_376) {
  MockIterator it;
  IteratorWrapper w(&it);
  EXPECT_EQ(w.iter(), &it);
}

TEST_F(IteratorWrapperTest_376, Set_ReplacesIterPointer_376) {
  MockIterator it1;
  MockIterator it2;
  IteratorWrapper w(&it1);
  ASSERT_EQ(w.iter(), &it1);

  w.Set(&it2);
  EXPECT_EQ(w.iter(), &it2);
}

TEST_F(IteratorWrapperTest_376, Set_CanSetNullAndThenNonNull_376) {
  MockIterator it;
  IteratorWrapper w(&it);
  ASSERT_EQ(w.iter(), &it);

  w.Set(nullptr);
  EXPECT_EQ(w.iter(), nullptr);

  w.Set(&it);
  EXPECT_EQ(w.iter(), &it);
}

TEST_F(IteratorWrapperTest_376, Valid_ForwardsAndReturnsUnderlyingValue_376) {
  MockIterator it;
  IteratorWrapper w(&it);

  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_TRUE(w.Valid());

  EXPECT_CALL(it, Valid()).WillOnce(Return(false));
  EXPECT_FALSE(w.Valid());
}

TEST_F(IteratorWrapperTest_376, Status_ForwardsAndReturnsUnderlyingStatus_376) {
  MockIterator it;
  IteratorWrapper w(&it);

  EXPECT_CALL(it, status()).WillOnce(Return(Status::OK()));
  Status s1 = w.status();
  EXPECT_TRUE(s1.ok());

  Status some_err = Status::IOError("boom");
  EXPECT_CALL(it, status()).WillOnce(Return(some_err));
  Status s2 = w.status();
  EXPECT_FALSE(s2.ok());
}

TEST_F(IteratorWrapperTest_376, Next_ForwardsToUnderlying_376) {
  MockIterator it;
  IteratorWrapper w(&it);

  EXPECT_CALL(it, Next()).Times(1);
  w.Next();
}

TEST_F(IteratorWrapperTest_376, Prev_ForwardsToUnderlying_376) {
  MockIterator it;
  IteratorWrapper w(&it);

  EXPECT_CALL(it, Prev()).Times(1);
  w.Prev();
}

TEST_F(IteratorWrapperTest_376, Seek_ForwardsKeyToUnderlying_376) {
  MockIterator it;
  IteratorWrapper w(&it);
  Slice target("abc");

  EXPECT_CALL(it, Seek(_))
      .WillOnce(Invoke([&](const Slice& seen) {
        // Verify the parameter passed through without making assumptions about internal caching.
        EXPECT_EQ(seen.ToString(), target.ToString());
      }));
  w.Seek(target);
}

TEST_F(IteratorWrapperTest_376, SeekToFirst_ForwardsToUnderlying_376) {
  MockIterator it;
  IteratorWrapper w(&it);

  EXPECT_CALL(it, SeekToFirst()).Times(1);
  w.SeekToFirst();
}

TEST_F(IteratorWrapperTest_376, SeekToLast_ForwardsToUnderlying_376) {
  MockIterator it;
  IteratorWrapper w(&it);

  EXPECT_CALL(it, SeekToLast()).Times(1);
  w.SeekToLast();
}

}  // namespace leveldb
