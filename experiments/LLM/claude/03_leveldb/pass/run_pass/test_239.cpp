#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Replicate the C wrapper struct as defined in db/c.cc
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Declare the C function under test
extern "C" {
void leveldb_iter_next(leveldb_iterator_t* iter);
}

// Mock Iterator to verify that Next() is called
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

class LeveldbIterNextTest_239 : public ::testing::Test {
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

// Test that leveldb_iter_next calls Next() on the underlying iterator exactly once
TEST_F(LeveldbIterNextTest_239, CallsNextOnUnderlyingIterator_239) {
  EXPECT_CALL(*mock_iter_, Next()).Times(1);
  leveldb_iter_next(&iter_);
}

// Test that calling leveldb_iter_next multiple times calls Next() each time
TEST_F(LeveldbIterNextTest_239, MultipleCallsInvokeNextMultipleTimes_239) {
  EXPECT_CALL(*mock_iter_, Next()).Times(3);
  leveldb_iter_next(&iter_);
  leveldb_iter_next(&iter_);
  leveldb_iter_next(&iter_);
}

// Test that Next() is called even when the iterator is not valid
TEST_F(LeveldbIterNextTest_239, CallsNextEvenWhenInvalid_239) {
  EXPECT_CALL(*mock_iter_, Valid()).WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(*mock_iter_, Next()).Times(1);
  leveldb_iter_next(&iter_);
}

// Test that no other methods are called besides Next()
TEST_F(LeveldbIterNextTest_239, OnlyNextIsCalled_239) {
  EXPECT_CALL(*mock_iter_, Next()).Times(1);
  EXPECT_CALL(*mock_iter_, Prev()).Times(0);
  EXPECT_CALL(*mock_iter_, SeekToFirst()).Times(0);
  EXPECT_CALL(*mock_iter_, SeekToLast()).Times(0);
  EXPECT_CALL(*mock_iter_, Seek(::testing::_)).Times(0);
  leveldb_iter_next(&iter_);
}

// Test sequential Next() calls verifying ordering via InSequence
TEST_F(LeveldbIterNextTest_239, SequentialNextCalls_239) {
  ::testing::InSequence seq;
  EXPECT_CALL(*mock_iter_, Next()).Times(1);
  EXPECT_CALL(*mock_iter_, Next()).Times(1);
  leveldb_iter_next(&iter_);
  leveldb_iter_next(&iter_);
}
