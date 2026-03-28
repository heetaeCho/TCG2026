#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

#include <cstring>
#include <string>

// Recreate the C API structs as defined in db/c.cc
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Forward declare the C function we're testing
extern "C" {
void leveldb_iter_get_error(const leveldb_iterator_t* iter, char** errptr);
}

// If we can't link the actual SaveError/leveldb_iter_get_error, we need to
// replicate the minimal C API helpers. But since we're testing the actual
// implementation, we include the real one.
// However, since the prompt says to treat implementation as black box and
// write tests, let's mock the Iterator and test through the C interface.

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

class LevelDBIterGetErrorTest_243 : public ::testing::Test {
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

// Test that when status is OK, errptr remains nullptr
TEST_F(LevelDBIterGetErrorTest_243, OkStatusDoesNotSetError_243) {
  EXPECT_CALL(*mock_iter_, status())
      .WillOnce(::testing::Return(leveldb::Status::OK()));

  char* errptr = nullptr;
  leveldb_iter_get_error(&iter_, &errptr);

  EXPECT_EQ(errptr, nullptr);
}

// Test that when status is an error, errptr is set to a non-null string
TEST_F(LevelDBIterGetErrorTest_243, ErrorStatusSetsErrptr_243) {
  EXPECT_CALL(*mock_iter_, status())
      .WillOnce(::testing::Return(
          leveldb::Status::Corruption("test corruption")));

  char* errptr = nullptr;
  leveldb_iter_get_error(&iter_, &errptr);

  ASSERT_NE(errptr, nullptr);
  std::string err_msg(errptr);
  EXPECT_TRUE(err_msg.find("corruption") != std::string::npos ||
              err_msg.find("Corruption") != std::string::npos ||
              err_msg.find("test corruption") != std::string::npos);
  free(errptr);
}

// Test that when status is NotFound, errptr is set appropriately
TEST_F(LevelDBIterGetErrorTest_243, NotFoundStatusSetsErrptr_243) {
  EXPECT_CALL(*mock_iter_, status())
      .WillOnce(::testing::Return(
          leveldb::Status::NotFound("key not found")));

  char* errptr = nullptr;
  leveldb_iter_get_error(&iter_, &errptr);

  ASSERT_NE(errptr, nullptr);
  std::string err_msg(errptr);
  EXPECT_TRUE(err_msg.find("not found") != std::string::npos ||
              err_msg.find("Not found") != std::string::npos ||
              err_msg.find("NotFound") != std::string::npos ||
              err_msg.find("key not found") != std::string::npos);
  free(errptr);
}

// Test that when status is IOError, errptr is set
TEST_F(LevelDBIterGetErrorTest_243, IOErrorStatusSetsErrptr_243) {
  EXPECT_CALL(*mock_iter_, status())
      .WillOnce(::testing::Return(
          leveldb::Status::IOError("io failure")));

  char* errptr = nullptr;
  leveldb_iter_get_error(&iter_, &errptr);

  ASSERT_NE(errptr, nullptr);
  std::string err_msg(errptr);
  EXPECT_TRUE(err_msg.find("io failure") != std::string::npos ||
              err_msg.find("IO error") != std::string::npos ||
              err_msg.find("IOError") != std::string::npos);
  free(errptr);
}

// Test that calling with an already set errptr (non-null) - SaveError
// typically only writes if status is not OK and errptr was null.
// If errptr is already set, behavior depends on SaveError implementation.
// We test the common case where errptr starts as nullptr.
TEST_F(LevelDBIterGetErrorTest_243, MultipleCallsWithOkStatus_243) {
  EXPECT_CALL(*mock_iter_, status())
      .WillRepeatedly(::testing::Return(leveldb::Status::OK()));

  char* errptr = nullptr;
  leveldb_iter_get_error(&iter_, &errptr);
  EXPECT_EQ(errptr, nullptr);

  leveldb_iter_get_error(&iter_, &errptr);
  EXPECT_EQ(errptr, nullptr);
}

// Test that error message with empty string in status still sets errptr
TEST_F(LevelDBIterGetErrorTest_243, CorruptionWithEmptyMessage_243) {
  EXPECT_CALL(*mock_iter_, status())
      .WillOnce(::testing::Return(
          leveldb::Status::Corruption("")));

  char* errptr = nullptr;
  leveldb_iter_get_error(&iter_, &errptr);

  // Even with empty message, the status is not OK, so errptr should be set
  ASSERT_NE(errptr, nullptr);
  free(errptr);
}

// Test InvalidArgument error
TEST_F(LevelDBIterGetErrorTest_243, InvalidArgumentStatusSetsErrptr_243) {
  EXPECT_CALL(*mock_iter_, status())
      .WillOnce(::testing::Return(
          leveldb::Status::InvalidArgument("bad argument")));

  char* errptr = nullptr;
  leveldb_iter_get_error(&iter_, &errptr);

  ASSERT_NE(errptr, nullptr);
  std::string err_msg(errptr);
  EXPECT_FALSE(err_msg.empty());
  free(errptr);
}
