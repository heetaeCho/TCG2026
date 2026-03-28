#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Include the C API header or define the struct
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Forward declare the function under test
extern "C" {
void leveldb_iter_prev(leveldb_iterator_t* iter);
}

// Mock Iterator class
class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(leveldb::Slice, key, (), (const, override));
  MOCK_METHOD(leveldb::Slice, value, (), (const, override));
  MOCK_METHOD(leveldb::Status, status, (), (const, override));
};

class LeveldbIterPrevTest_240 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_iter_ = new MockIterator();
    iter_.rep = mock_iter_;
  }

  void TearDown() override {
    delete mock_iter_;
  }

  MockIterator* mock_iter_;
  leveldb_iterator_t iter_;
};

// Test that leveldb_iter_prev calls Prev() on the underlying iterator exactly once
TEST_F(LeveldbIterPrevTest_240, CallsPrevOnUnderlyingIterator_240) {
  EXPECT_CALL(*mock_iter_, Prev()).Times(1);
  leveldb_iter_prev(&iter_);
}

// Test that calling leveldb_iter_prev multiple times calls Prev() each time
TEST_F(LeveldbIterPrevTest_240, MultipleCallsInvokePrevMultipleTimes_240) {
  EXPECT_CALL(*mock_iter_, Prev()).Times(3);
  leveldb_iter_prev(&iter_);
  leveldb_iter_prev(&iter_);
  leveldb_iter_prev(&iter_);
}

// Test that Prev is called exactly once per invocation (not more, not less)
TEST_F(LeveldbIterPrevTest_240, PrevCalledExactlyOncePerCall_240) {
  {
    ::testing::InSequence seq;
    EXPECT_CALL(*mock_iter_, Prev()).Times(1);
  }
  leveldb_iter_prev(&iter_);
  ::testing::Mock::VerifyAndClearExpectations(mock_iter_);

  {
    ::testing::InSequence seq;
    EXPECT_CALL(*mock_iter_, Prev()).Times(1);
  }
  leveldb_iter_prev(&iter_);
  ::testing::Mock::VerifyAndClearExpectations(mock_iter_);
}

// Test that no other methods besides Prev are called on the iterator
TEST_F(LeveldbIterPrevTest_240, OnlyPrevIsCalled_240) {
  EXPECT_CALL(*mock_iter_, Prev()).Times(1);
  EXPECT_CALL(*mock_iter_, Next()).Times(0);
  EXPECT_CALL(*mock_iter_, SeekToFirst()).Times(0);
  EXPECT_CALL(*mock_iter_, SeekToLast()).Times(0);
  EXPECT_CALL(*mock_iter_, Seek(::testing::_)).Times(0);

  leveldb_iter_prev(&iter_);
}

// Test with a different mock instance to ensure the function delegates correctly
TEST_F(LeveldbIterPrevTest_240, DelegatesToCorrectIteratorInstance_240) {
  MockIterator another_mock;
  leveldb_iterator_t another_iter;
  another_iter.rep = &another_mock;

  EXPECT_CALL(another_mock, Prev()).Times(1);
  EXPECT_CALL(*mock_iter_, Prev()).Times(0);

  leveldb_iter_prev(&another_iter);
}
