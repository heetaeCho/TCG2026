#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Include the C API header or recreate the necessary struct
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Forward declare the function under test
extern "C" {
void leveldb_iter_seek_to_last(leveldb_iterator_t* iter);
}

// If the function isn't declared extern "C", use the actual declaration:
// void leveldb_iter_seek_to_last(leveldb_iterator_t* iter);

// Mock Iterator to verify SeekToLast is called
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

class LevelDBIterSeekToLastTest_237 : public ::testing::Test {
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

// Test that SeekToLast is called exactly once on the underlying iterator
TEST_F(LevelDBIterSeekToLastTest_237, CallsSeekToLastOnRep_237) {
  EXPECT_CALL(*mock_iter_, SeekToLast()).Times(1);
  leveldb_iter_seek_to_last(&iter_);
}

// Test that calling SeekToLast multiple times calls the underlying method each time
TEST_F(LevelDBIterSeekToLastTest_237, MultipleCallsInvokeSeekToLastEachTime_237) {
  EXPECT_CALL(*mock_iter_, SeekToLast()).Times(3);
  leveldb_iter_seek_to_last(&iter_);
  leveldb_iter_seek_to_last(&iter_);
  leveldb_iter_seek_to_last(&iter_);
}

// Test that SeekToLast delegates correctly and no other methods are called
TEST_F(LevelDBIterSeekToLastTest_237, OnlySeekToLastIsCalled_237) {
  EXPECT_CALL(*mock_iter_, SeekToLast()).Times(1);
  EXPECT_CALL(*mock_iter_, SeekToFirst()).Times(0);
  EXPECT_CALL(*mock_iter_, Next()).Times(0);
  EXPECT_CALL(*mock_iter_, Prev()).Times(0);
  EXPECT_CALL(*mock_iter_, Seek(::testing::_)).Times(0);
  leveldb_iter_seek_to_last(&iter_);
}

// Test with a different mock instance to ensure the function uses the rep pointer correctly
TEST_F(LevelDBIterSeekToLastTest_237, UsesCorrectRepPointer_237) {
  MockIterator another_mock;
  leveldb_iterator_t another_iter;
  another_iter.rep = &another_mock;

  // The original mock should NOT be called
  EXPECT_CALL(*mock_iter_, SeekToLast()).Times(0);
  // The new mock should be called
  EXPECT_CALL(another_mock, SeekToLast()).Times(1);

  leveldb_iter_seek_to_last(&another_iter);
}
