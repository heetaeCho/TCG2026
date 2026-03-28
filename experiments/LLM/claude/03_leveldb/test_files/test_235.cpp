#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Include the C API header or replicate the necessary struct
// We need the struct definition and the function declaration
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

extern "C" {
uint8_t leveldb_iter_valid(const leveldb_iterator_t* iter);
}

// Mock Iterator to control behavior
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

class LeveldbIterValidTest_235 : public ::testing::Test {
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

// Test that leveldb_iter_valid returns non-zero (true) when the underlying
// iterator is valid.
TEST_F(LeveldbIterValidTest_235, ReturnsNonZeroWhenValid_235) {
  EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(true));
  uint8_t result = leveldb_iter_valid(&iter_);
  EXPECT_NE(result, 0);
}

// Test that leveldb_iter_valid returns zero (false) when the underlying
// iterator is not valid.
TEST_F(LeveldbIterValidTest_235, ReturnsZeroWhenNotValid_235) {
  EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(false));
  uint8_t result = leveldb_iter_valid(&iter_);
  EXPECT_EQ(result, 0);
}

// Test that leveldb_iter_valid returns 1 when Valid() returns true.
TEST_F(LeveldbIterValidTest_235, ReturnsOneWhenTrue_235) {
  EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(true));
  uint8_t result = leveldb_iter_valid(&iter_);
  EXPECT_EQ(result, 1);
}

// Test that leveldb_iter_valid returns 0 when Valid() returns false.
TEST_F(LeveldbIterValidTest_235, ReturnsExactlyZeroWhenFalse_235) {
  EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(false));
  uint8_t result = leveldb_iter_valid(&iter_);
  EXPECT_EQ(result, 0);
}

// Test that multiple consecutive calls to leveldb_iter_valid correctly
// delegate to the underlying iterator each time.
TEST_F(LeveldbIterValidTest_235, MultipleCallsDelegateCorrectly_235) {
  EXPECT_CALL(*mock_iter_, Valid())
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true));

  EXPECT_NE(leveldb_iter_valid(&iter_), 0);
  EXPECT_EQ(leveldb_iter_valid(&iter_), 0);
  EXPECT_NE(leveldb_iter_valid(&iter_), 0);
}

// Test that the function can be called with a const pointer to the
// iterator struct (verifying const-correctness).
TEST_F(LeveldbIterValidTest_235, WorksWithConstPointer_235) {
  EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(true));
  const leveldb_iterator_t* const_iter = &iter_;
  uint8_t result = leveldb_iter_valid(const_iter);
  EXPECT_NE(result, 0);
}

// Test that the return value is a uint8_t (fits in one byte) for both states.
TEST_F(LeveldbIterValidTest_235, ReturnValueFitsInUint8_235) {
  EXPECT_CALL(*mock_iter_, Valid()).WillOnce(::testing::Return(true));
  uint8_t result = leveldb_iter_valid(&iter_);
  EXPECT_LE(result, 255);
  EXPECT_GE(result, 0);
}
