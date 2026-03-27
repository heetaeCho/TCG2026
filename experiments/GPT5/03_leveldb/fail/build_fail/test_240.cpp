// File: leveldb_iter_prev_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// The production function under test.
// (Forward-declare as C linkage; it is implemented in db/c.cc.)
extern "C" void leveldb_iter_prev(struct leveldb_iterator_t* iter);

// Mirror of the provided struct shape from db/c.cc (needed to pass a mock in).
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// A strict mock of leveldb::Iterator to verify only Prev() is called.
class StrictMockIterator : public leveldb::Iterator {
 public:
  // The LevelDB iterator API (declare all virtuals; only Prev() will be expected).
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(leveldb::Slice, key, (), (const, override));
  MOCK_METHOD(leveldb::Slice, value, (), (const, override));
  MOCK_METHOD(leveldb::Status, status, (), (const, override));
  MOCK_METHOD(void, RegisterCleanup,
              (CleanupFunction function, void* arg1, void* arg2), (override));
};

// Fixture (keeps naming consistent and clear).
class LeveldbIterPrevTest_240 : public ::testing::Test {
 protected:
  StrictMockIterator mock_;
  leveldb_iterator_t c_iter_{&mock_};
};

// [Normal] Calls Prev exactly once when invoked.
TEST_F(LeveldbIterPrevTest_240, CallsPrevOnce_240) {
  EXPECT_CALL(mock_, Prev()).Times(1);
  leveldb_iter_prev(&c_iter_);
}

// [Boundary] Multiple invocations lead to matching number of Prev() calls.
TEST_F(LeveldbIterPrevTest_240, CallsPrevMultipleTimes_240) {
  EXPECT_CALL(mock_, Prev()).Times(3);
  leveldb_iter_prev(&c_iter_);
  leveldb_iter_prev(&c_iter_);
  leveldb_iter_prev(&c_iter_);
}

// [Interaction Guard] Does not call any other Iterator methods.
TEST_F(LeveldbIterPrevTest_240, DoesNotInvokeOtherIteratorMethods_240) {
  // With StrictMock, setting only Prev() expectation ensures any other
  // unexpected call fails the test.
  EXPECT_CALL(mock_, Prev()).Times(1);
  leveldb_iter_prev(&c_iter_);
}
