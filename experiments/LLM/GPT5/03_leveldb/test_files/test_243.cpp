// File: db/leveldb_iter_get_error_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>
#include <cstring>

// LevelDB headers (interfaces only)
#include "leveldb/iterator.h"
#include "leveldb/status.h"

// C API function under test (declared in db/c.cc)
extern "C" {
  struct leveldb_iterator_t { leveldb::Iterator* rep; };
  void leveldb_iter_get_error(const leveldb_iterator_t* iter, char** errptr);
}

using ::testing::Return;

namespace {

// Minimal mock for leveldb::Iterator.
// We only care about status(), but Iterator has several pure virtuals,
// so we mock them to satisfy the interface without asserting on them.
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

// Test fixture just to keep construction helpers in one place.
class IterGetErrorTest_243 : public ::testing::Test {
 protected:
  leveldb_iterator_t Wrap(leveldb::Iterator* it) {
    leveldb_iterator_t w{it};
    return w;
  }
};

}  // namespace

// [Normal] OK status => errptr becomes nullptr (cleared)
// Verifies observable behavior that a success status does not produce an error string.
TEST_F(IterGetErrorTest_243, OkStatusClearsErrptr_243) {
  MockIterator mock;
  // Return an OK status
  EXPECT_CALL(mock, status()).WillOnce(Return(leveldb::Status::OK()));

  // Prepare an existing error buffer to ensure it gets cleared
  char* err = static_cast<char*>(std::malloc(8));
  std::strcpy(err, "old");

  auto wrapped = Wrap(&mock);
  leveldb_iter_get_error(&wrapped, &err);

  // On success, the C API should leave errptr as nullptr (no error).
  EXPECT_EQ(err, nullptr);
}

// [Error] Non-OK status => errptr becomes a non-null C string describing the error
// We do not assert the exact internal format; just that something non-empty is set.
TEST_F(IterGetErrorTest_243, NonOkStatusPopulatesErrString_243) {
  MockIterator mock;

  // Use a common non-OK status. The exact message/format is not asserted.
  leveldb::Status not_found = leveldb::Status::NotFound("missing key");
  EXPECT_CALL(mock, status()).WillOnce(Return(not_found));

  char* err = nullptr;
  auto wrapped = Wrap(&mock);
  leveldb_iter_get_error(&wrapped, &err);

  ASSERT_NE(err, nullptr);
  EXPECT_GT(std::strlen(err), 0u);

  // (Best-effort) Many LevelDB statuses include the type in ToString(); if present, great.
  // We do NOT depend on exact formatting — just check it contains a useful hint.
  // If the exact text isn't guaranteed in your build, feel free to drop this check.
  // e.g., EXPECT_THAT(std::string(err), ::testing::HasSubstr("NotFound"));

  std::free(err);
}

// [Boundary] errptr == nullptr is accepted and should be a no-op (no crash)
// We only verify that the call succeeds; no observable state change expected via errptr.
TEST_F(IterGetErrorTest_243, NullErrptrIsNoOp_243) {
  MockIterator mock;
  // Return an error to exercise the error path while errptr is null
  EXPECT_CALL(mock, status()).WillOnce(Return(leveldb::Status::Corruption("bad data")));

  auto wrapped = Wrap(&mock);

  // Should not crash; nothing to assert about errptr since it's nullptr.
  leveldb_iter_get_error(&wrapped, /*errptr=*/nullptr);
}

