// File: db/c_iter_seek_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstddef>
#include <cstring>

// Minimal LevelDB includes for types used by the public interface
#include "leveldb/slice.h"
#include "leveldb/iterator.h"

// C API under test
extern "C" {
  // Mirror the C wrapper's iterator struct as exposed in db/c.cc
  struct leveldb_iterator_t { leveldb::Iterator* rep; };

  // Function under test
  void leveldb_iter_seek(leveldb_iterator_t* iter, const char* k, size_t klen);
}

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Truly;

// Custom matcher to check the Slice has the expected bytes + length
inline ::testing::Matcher<const leveldb::Slice&>
SliceEq(const void* expected_data, size_t expected_len) {
  return Truly([expected_data, expected_len](const leveldb::Slice& s) -> bool {
    return s.size() == expected_len &&
           (expected_len == 0 || std::memcmp(s.data(), expected_data, expected_len) == 0);
  });
}

// Mock Iterator that only cares about Seek (we don't infer any internals)
class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));

  // The rest are inherited virtuals; we leave them as-is and never call them.
  // We must still provide destructibility.
  ~MockIterator() override = default;
};

// Test fixture
class LeveldbIterSeekTest_238 : public ::testing::Test {
 protected:
  leveldb_iterator_t c_iter{};
  NiceMock<MockIterator> mock_iter;

  void SetUp() override { c_iter.rep = &mock_iter; }
  void TearDown() override { c_iter.rep = nullptr; }
};

// --- Tests ---

// Normal operation: forwards the exact bytes and length to Iterator::Seek
TEST_F(LeveldbIterSeekTest_238, ForwardsExactKeyAndLength_238) {
  const char key[] = "hello"; // length 5 (no trailing NUL counted)
  EXPECT_CALL(mock_iter, Seek(SliceEq(key, 5))).Times(1);

  leveldb_iter_seek(&c_iter, key, 5);
}

// Boundary: zero-length key should still call Seek with an empty Slice
TEST_F(LeveldbIterSeekTest_238, AllowsEmptyKey_238) {
  const char key[] = "ignored";
  EXPECT_CALL(mock_iter, Seek(SliceEq(key, 0))).Times(1);

  leveldb_iter_seek(&c_iter, key, 0);
}

// Binary data: embedded NULs must be respected (length-driven, not strlen)
TEST_F(LeveldbIterSeekTest_238, HandlesEmbeddedNullBytes_238) {
  const char key_with_nuls[] = {'a', 'b', '\0', 'd', 'e', '\0', 'g'};
  constexpr size_t kLen = sizeof(key_with_nuls); // 7
  EXPECT_CALL(mock_iter, Seek(SliceEq(key_with_nuls, kLen))).Times(1);

  leveldb_iter_seek(&c_iter, key_with_nuls, kLen);
}

// Defensive check: when klen is shorter than the buffer up to NUL, length must prevail
TEST_F(LeveldbIterSeekTest_238, UsesProvidedLengthOverStrlen_238) {
  // "abc\0def": strlen would be 3, but we pass full 7 bytes
  const char key[] = {'a','b','c','\0','d','e','f'};
  EXPECT_CALL(mock_iter, Seek(SliceEq(key, 7))).Times(1);

  leveldb_iter_seek(&c_iter, key, 7);
}
