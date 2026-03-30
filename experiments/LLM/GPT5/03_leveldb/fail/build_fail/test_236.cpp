// File: leveldb_iter_seek_to_first_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Public LevelDB headers for the Iterator interface & related types
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Forward declarations matching the production code (no re-implementation).
struct leveldb_iterator_t { leveldb::Iterator* rep; };
void leveldb_iter_seek_to_first(leveldb_iterator_t* iter);

// ---- Mock for leveldb::Iterator ----
// We mock only to observe external interaction (method call). No internal logic is inferred.
class MockIterator : public leveldb::Iterator {
 public:
  // Signatures match the typical LevelDB Iterator API.
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

// Test fixture (kept minimal; no state needed).
class LeveldbIterSeekToFirstTest_236 : public ::testing::Test {};

// [Normal operation]
// Verifies the wrapper forwards the call to Iterator::SeekToFirst exactly once.
TEST_F(LeveldbIterSeekToFirstTest_236, ForwardsCallToRepSeekToFirst_236) {
  ::testing::StrictMock<MockIterator> mock_iter;
  leveldb_iterator_t c_iter{&mock_iter};

  EXPECT_CALL(mock_iter, SeekToFirst()).Times(1);

  leveldb_iter_seek_to_first(&c_iter);
}

// [Exceptional/error case: null top-level pointer]
// Passing a null iterator pointer is invalid; we assert the wrapper dies (e.g., via null deref).
#if GTEST_HAS_DEATH_TEST
TEST_F(LeveldbIterSeekToFirstTest_236, NullIteratorPointer_Death_236) {
  EXPECT_DEATH({ leveldb_iter_seek_to_first(nullptr); }, ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

// [Exceptional/error case: null rep]
// If the struct exists but rep is null, dereferencing it is invalid; assert death.
#if GTEST_HAS_DEATH_TEST
TEST_F(LeveldbIterSeekToFirstTest_236, NullRepPointerInStruct_Death_236) {
  leveldb_iterator_t c_iter{nullptr};
  EXPECT_DEATH({ leveldb_iter_seek_to_first(&c_iter); }, ".*");
}
#endif  // GTEST_HAS_DEATH_TEST
