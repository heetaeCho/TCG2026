// File: db/c_iter_valid_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Bring in the C wrapper symbol and iterator handle type.
// If you have a header for the C API, include it instead of these forward decls.
extern "C" {
  #include <stdint.h>
  struct leveldb_iterator_t;  // forward
  uint8_t leveldb_iter_valid(const leveldb_iterator_t* iter);
}

// Bring in the Iterator interface (provided in the prompt).
// If your project exposes it via <leveldb/iterator.h>, include that.
#include "leveldb/iterator.h"

using ::testing::Return;
using ::testing::Exactly;

namespace {

// The C API handle, as declared in the provided snippet.
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// A strict mock for leveldb::Iterator.
// We only care about Valid(), but we provide mocks for all virtuals to
// satisfy the interface without assuming internal behavior.
class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(const bool, Valid, (), (override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(const leveldb::Slice, key, (), (override));
  MOCK_METHOD(const leveldb::Slice, value, (), (override));
  MOCK_METHOD(const leveldb::Status, status, (), (override));
  ~MockIterator() override = default;
};

class IterValidTest_235 : public ::testing::Test {
 protected:
  IterValidTest_235() {
    handle_.rep = &mock_;
  }

  leveldb_iterator_t handle_{};
  MockIterator mock_;
};

}  // namespace

// [Normal operation] When the underlying iterator reports valid,
// the wrapper should return 1 (as a uint8_t).
TEST_F(IterValidTest_235, Returns1WhenIteratorIsValid_235) {
  EXPECT_CALL(mock_, Valid()).Times(Exactly(1)).WillOnce(Return(true));

  const uint8_t result = leveldb_iter_valid(&handle_);
  EXPECT_EQ(result, static_cast<uint8_t>(1));
}

// [Normal operation] When the underlying iterator reports NOT valid,
// the wrapper should return 0.
TEST_F(IterValidTest_235, Returns0WhenIteratorIsNotValid_235) {
  EXPECT_CALL(mock_, Valid()).Times(Exactly(1)).WillOnce(Return(false));

  const uint8_t result = leveldb_iter_valid(&handle_);
  EXPECT_EQ(result, static_cast<uint8_t>(0));
}

// [Interaction verification] Ensure the wrapper forwards exactly one call
// to Iterator::Valid() and does not perform any other observable work.
TEST_F(IterValidTest_235, CallsValidExactlyOnce_235) {
  EXPECT_CALL(mock_, Valid()).Times(Exactly(1)).WillOnce(Return(true));

  (void)leveldb_iter_valid(&handle_);
  // No further expectations; the Times(1) above verifies single delegation.
}
