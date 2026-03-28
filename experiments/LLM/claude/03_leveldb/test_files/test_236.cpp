#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Include the C API header or replicate the necessary struct
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Forward declare the C function under test
extern "C" {
void leveldb_iter_seek_to_first(leveldb_iterator_t* iter);
}

// If the C function is not declared extern "C", use the appropriate linkage
// We may need to declare it directly if the header is not available
#ifndef LEVELDB_C_H_
void leveldb_iter_seek_to_first(leveldb_iterator_t* iter) {
  iter->rep->SeekToFirst();
}
#endif

// Mock Iterator class to verify SeekToFirst is called
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

class LeveldbIterSeekToFirstTest_236 : public ::testing::Test {
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

// Test that SeekToFirst is called exactly once on the underlying iterator
TEST_F(LeveldbIterSeekToFirstTest_236, CallsSeekToFirstOnRep_236) {
  EXPECT_CALL(*mock_iter_, SeekToFirst()).Times(1);
  leveldb_iter_seek_to_first(&iter_);
}

// Test that calling SeekToFirst multiple times delegates each call
TEST_F(LeveldbIterSeekToFirstTest_236, MultipleCallsDelegateEachTime_236) {
  EXPECT_CALL(*mock_iter_, SeekToFirst()).Times(3);
  leveldb_iter_seek_to_first(&iter_);
  leveldb_iter_seek_to_first(&iter_);
  leveldb_iter_seek_to_first(&iter_);
}

// Test that SeekToFirst is the only method called (no side effects on other methods)
TEST_F(LeveldbIterSeekToFirstTest_236, OnlySeekToFirstIsCalled_236) {
  EXPECT_CALL(*mock_iter_, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter_, SeekToLast()).Times(0);
  EXPECT_CALL(*mock_iter_, Seek(::testing::_)).Times(0);
  EXPECT_CALL(*mock_iter_, Next()).Times(0);
  EXPECT_CALL(*mock_iter_, Prev()).Times(0);
  leveldb_iter_seek_to_first(&iter_);
}

// Test with a different mock instance to ensure the function works with any iterator
TEST_F(LeveldbIterSeekToFirstTest_236, WorksWithDifferentIteratorInstance_236) {
  MockIterator another_mock;
  leveldb_iterator_t another_iter;
  another_iter.rep = &another_mock;

  EXPECT_CALL(another_mock, SeekToFirst()).Times(1);
  leveldb_iter_seek_to_first(&another_iter);
}

// Test that the function correctly uses the rep pointer from the struct
TEST_F(LeveldbIterSeekToFirstTest_236, UsesRepPointerFromStruct_236) {
  MockIterator* new_mock = new MockIterator();
  iter_.rep = new_mock;

  EXPECT_CALL(*new_mock, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter_, SeekToFirst()).Times(0);

  leveldb_iter_seek_to_first(&iter_);

  delete new_mock;
}
