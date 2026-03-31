#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/slice.h"
#include "leveldb/options.h"

// We need the C API struct definition
struct leveldb_t {
  leveldb::DB* rep;
};

// Forward declare the C function under test
extern "C" {
void leveldb_compact_range(leveldb_t* db, const char* start_key,
                           size_t start_key_len, const char* limit_key,
                           size_t limit_key_len);
}

// Mock DB class to verify CompactRange calls
class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(leveldb::Status, Put,
              (const leveldb::WriteOptions& options, const leveldb::Slice& key,
               const leveldb::Slice& value),
              (override));
  MOCK_METHOD(leveldb::Status, Delete,
              (const leveldb::WriteOptions& options, const leveldb::Slice& key),
              (override));
  MOCK_METHOD(leveldb::Status, Write,
              (const leveldb::WriteOptions& options,
               leveldb::WriteBatch* updates),
              (override));
  MOCK_METHOD(leveldb::Status, Get,
              (const leveldb::ReadOptions& options, const leveldb::Slice& key,
               std::string* value),
              (override));
  MOCK_METHOD(leveldb::Iterator*, NewIterator,
              (const leveldb::ReadOptions& options), (override));
  MOCK_METHOD(const leveldb::Snapshot*, GetSnapshot, (), (override));
  MOCK_METHOD(void, ReleaseSnapshot, (const leveldb::Snapshot* snapshot),
              (override));
  MOCK_METHOD(bool, GetProperty,
              (const leveldb::Slice& property, std::string* value), (override));
  MOCK_METHOD(void, GetApproximateSizes,
              (const leveldb::Range* range, int n, uint64_t* sizes),
              (override));
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice* begin, const leveldb::Slice* end),
              (override));
};

class LevelDBCompactRangeTest_231 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new MockDB();
    db_.rep = mock_db_;
  }

  void TearDown() override { delete mock_db_; }

  MockDB* mock_db_;
  leveldb_t db_;
};

// Test: Both start_key and limit_key are provided
TEST_F(LevelDBCompactRangeTest_231, BothKeysProvided_231) {
  const char* start = "abc";
  const char* limit = "xyz";

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(begin->ToString(), "abc");
        EXPECT_EQ(end->ToString(), "xyz");
      });

  leveldb_compact_range(&db_, start, 3, limit, 3);
}

// Test: Both start_key and limit_key are nullptr
TEST_F(LevelDBCompactRangeTest_231, BothKeysNull_231) {
  EXPECT_CALL(*mock_db_, CompactRange(::testing::IsNull(), ::testing::IsNull()))
      .Times(1);

  leveldb_compact_range(&db_, nullptr, 0, nullptr, 0);
}

// Test: start_key is nullptr but limit_key is provided
TEST_F(LevelDBCompactRangeTest_231, StartKeyNullLimitKeyProvided_231) {
  const char* limit = "xyz";

  EXPECT_CALL(*mock_db_, CompactRange(::testing::IsNull(), ::testing::NotNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        EXPECT_EQ(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(end->ToString(), "xyz");
      });

  leveldb_compact_range(&db_, nullptr, 0, limit, 3);
}

// Test: start_key is provided but limit_key is nullptr
TEST_F(LevelDBCompactRangeTest_231, StartKeyProvidedLimitKeyNull_231) {
  const char* start = "abc";

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::IsNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        EXPECT_EQ(begin->ToString(), "abc");
        EXPECT_EQ(end, nullptr);
      });

  leveldb_compact_range(&db_, start, 3, nullptr, 0);
}

// Test: Keys with embedded null bytes (binary keys)
TEST_F(LevelDBCompactRangeTest_231, BinaryKeysWithNullBytes_231) {
  const char start[] = {'a', '\0', 'b'};
  const char limit[] = {'x', '\0', 'y', '\0', 'z'};

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([&](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(begin->size(), 3u);
        EXPECT_EQ(end->size(), 5u);
        EXPECT_EQ(std::string(begin->data(), begin->size()),
                  std::string(start, 3));
        EXPECT_EQ(std::string(end->data(), end->size()),
                  std::string(limit, 5));
      });

  leveldb_compact_range(&db_, start, 3, limit, 5);
}

// Test: Empty keys (zero length but non-null pointers)
TEST_F(LevelDBCompactRangeTest_231, EmptyKeys_231) {
  const char* start = "";
  const char* limit = "";

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(begin->size(), 0u);
        EXPECT_EQ(end->size(), 0u);
      });

  leveldb_compact_range(&db_, start, 0, limit, 0);
}

// Test: Large key sizes
TEST_F(LevelDBCompactRangeTest_231, LargeKeys_231) {
  std::string large_start(10000, 'A');
  std::string large_limit(20000, 'Z');

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([&](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(begin->size(), 10000u);
        EXPECT_EQ(end->size(), 20000u);
        EXPECT_EQ(begin->ToString(), large_start);
        EXPECT_EQ(end->ToString(), large_limit);
      });

  leveldb_compact_range(&db_, large_start.data(), large_start.size(),
                        large_limit.data(), large_limit.size());
}

// Test: Single character keys
TEST_F(LevelDBCompactRangeTest_231, SingleCharKeys_231) {
  const char start = 'a';
  const char limit = 'z';

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(begin->size(), 1u);
        EXPECT_EQ(end->size(), 1u);
        EXPECT_EQ((*begin)[0], 'a');
        EXPECT_EQ((*end)[0], 'z');
      });

  leveldb_compact_range(&db_, &start, 1, &limit, 1);
}

// Test: Partial key length (length less than string length)
TEST_F(LevelDBCompactRangeTest_231, PartialKeyLength_231) {
  const char* start = "abcdef";
  const char* limit = "xyz123";

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(begin->size(), 3u);
        EXPECT_EQ(begin->ToString(), "abc");
        EXPECT_EQ(end->size(), 2u);
        EXPECT_EQ(end->ToString(), "xy");
      });

  leveldb_compact_range(&db_, start, 3, limit, 2);
}

// Test: Same start and limit key
TEST_F(LevelDBCompactRangeTest_231, SameStartAndLimitKey_231) {
  const char* key = "same_key";

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(begin->ToString(), "same_key");
        EXPECT_EQ(end->ToString(), "same_key");
      });

  leveldb_compact_range(&db_, key, 8, key, 8);
}

// Test: nullptr start_key with non-zero length (edge case, start_key still null)
TEST_F(LevelDBCompactRangeTest_231, NullStartKeyWithNonZeroLen_231) {
  const char* limit = "limit";

  EXPECT_CALL(*mock_db_, CompactRange(::testing::IsNull(), ::testing::NotNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        EXPECT_EQ(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(end->ToString(), "limit");
      });

  // Even though start_key_len is non-zero, start_key is null so begin should be null
  leveldb_compact_range(&db_, nullptr, 5, limit, 5);
}

// Test: nullptr limit_key with non-zero length (edge case, limit_key still null)
TEST_F(LevelDBCompactRangeTest_231, NullLimitKeyWithNonZeroLen_231) {
  const char* start = "start";

  EXPECT_CALL(*mock_db_, CompactRange(::testing::NotNull(), ::testing::IsNull()))
      .WillOnce([](const leveldb::Slice* begin, const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        EXPECT_EQ(begin->ToString(), "start");
        EXPECT_EQ(end, nullptr);
      });

  leveldb_compact_range(&db_, start, 5, nullptr, 10);
}
