#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/slice.h"
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/iterator.h"
#include "leveldb/write_batch.h"

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>

// Recreate the C API struct as defined in db/c.cc
struct leveldb_t {
  leveldb::DB* rep;
};

// Forward declare the C function under test
extern "C" {
void leveldb_approximate_sizes(leveldb_t* db, int num_ranges,
                               const char* const* range_start_key,
                               const size_t* range_start_key_len,
                               const char* const* range_limit_key,
                               const size_t* range_limit_key_len,
                               uint64_t* sizes);
}

// Mock DB to intercept GetApproximateSizes calls
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

class ApproximateSizesTest_230 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new MockDB();
    db_.rep = mock_db_;
  }

  void TearDown() override {
    delete mock_db_;
  }

  MockDB* mock_db_;
  leveldb_t db_;
};

// Test with a single range
TEST_F(ApproximateSizesTest_230, SingleRange_230) {
  const char* start_keys[] = {"a"};
  size_t start_key_lens[] = {1};
  const char* limit_keys[] = {"z"};
  size_t limit_key_lens[] = {1};
  uint64_t sizes[1] = {0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 1, ::testing::_))
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        ASSERT_EQ(n, 1);
        EXPECT_EQ(ranges[0].start.ToString(), "a");
        EXPECT_EQ(ranges[0].limit.ToString(), "z");
        sizes[0] = 12345;
      });

  leveldb_approximate_sizes(&db_, 1, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], 12345u);
}

// Test with multiple ranges
TEST_F(ApproximateSizesTest_230, MultipleRanges_230) {
  const char* start_keys[] = {"a", "m", "x"};
  size_t start_key_lens[] = {1, 1, 1};
  const char* limit_keys[] = {"f", "r", "z"};
  size_t limit_key_lens[] = {1, 1, 1};
  uint64_t sizes[3] = {0, 0, 0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 3, ::testing::_))
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        ASSERT_EQ(n, 3);
        EXPECT_EQ(ranges[0].start.ToString(), "a");
        EXPECT_EQ(ranges[0].limit.ToString(), "f");
        EXPECT_EQ(ranges[1].start.ToString(), "m");
        EXPECT_EQ(ranges[1].limit.ToString(), "r");
        EXPECT_EQ(ranges[2].start.ToString(), "x");
        EXPECT_EQ(ranges[2].limit.ToString(), "z");
        sizes[0] = 100;
        sizes[1] = 200;
        sizes[2] = 300;
      });

  leveldb_approximate_sizes(&db_, 3, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], 100u);
  EXPECT_EQ(sizes[1], 200u);
  EXPECT_EQ(sizes[2], 300u);
}

// Test with keys that have embedded null bytes (binary keys)
TEST_F(ApproximateSizesTest_230, BinaryKeys_230) {
  const char start_key_data[] = {'a', '\0', 'b'};
  const char limit_key_data[] = {'x', '\0', 'y'};
  const char* start_keys[] = {start_key_data};
  size_t start_key_lens[] = {3};
  const char* limit_keys[] = {limit_key_data};
  size_t limit_key_lens[] = {3};
  uint64_t sizes[1] = {0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 1, ::testing::_))
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        ASSERT_EQ(n, 1);
        EXPECT_EQ(ranges[0].start.size(), 3u);
        EXPECT_EQ(ranges[0].start.data()[0], 'a');
        EXPECT_EQ(ranges[0].start.data()[1], '\0');
        EXPECT_EQ(ranges[0].start.data()[2], 'b');
        EXPECT_EQ(ranges[0].limit.size(), 3u);
        EXPECT_EQ(ranges[0].limit.data()[0], 'x');
        EXPECT_EQ(ranges[0].limit.data()[1], '\0');
        EXPECT_EQ(ranges[0].limit.data()[2], 'y');
        sizes[0] = 999;
      });

  leveldb_approximate_sizes(&db_, 1, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], 999u);
}

// Test with empty key strings (zero-length keys)
TEST_F(ApproximateSizesTest_230, EmptyKeys_230) {
  const char* start_keys[] = {""};
  size_t start_key_lens[] = {0};
  const char* limit_keys[] = {""};
  size_t limit_key_lens[] = {0};
  uint64_t sizes[1] = {0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 1, ::testing::_))
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        ASSERT_EQ(n, 1);
        EXPECT_EQ(ranges[0].start.size(), 0u);
        EXPECT_EQ(ranges[0].limit.size(), 0u);
        sizes[0] = 0;
      });

  leveldb_approximate_sizes(&db_, 1, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], 0u);
}

// Test with longer keys
TEST_F(ApproximateSizesTest_230, LongKeys_230) {
  std::string long_start(1000, 'a');
  std::string long_limit(1000, 'z');
  const char* start_keys[] = {long_start.c_str()};
  size_t start_key_lens[] = {long_start.size()};
  const char* limit_keys[] = {long_limit.c_str()};
  size_t limit_key_lens[] = {long_limit.size()};
  uint64_t sizes[1] = {0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 1, ::testing::_))
      .WillOnce([&](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        ASSERT_EQ(n, 1);
        EXPECT_EQ(ranges[0].start.size(), 1000u);
        EXPECT_EQ(ranges[0].limit.size(), 1000u);
        EXPECT_EQ(ranges[0].start.ToString(), long_start);
        EXPECT_EQ(ranges[0].limit.ToString(), long_limit);
        sizes[0] = 50000;
      });

  leveldb_approximate_sizes(&db_, 1, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], 50000u);
}

// Test that GetApproximateSizes is called exactly once regardless of num_ranges
TEST_F(ApproximateSizesTest_230, GetApproximateSizesCalledOnce_230) {
  const char* start_keys[] = {"a", "b", "c", "d", "e"};
  size_t start_key_lens[] = {1, 1, 1, 1, 1};
  const char* limit_keys[] = {"f", "g", "h", "i", "j"};
  size_t limit_key_lens[] = {1, 1, 1, 1, 1};
  uint64_t sizes[5] = {0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 5, ::testing::_))
      .Times(1)
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        for (int i = 0; i < n; i++) {
          sizes[i] = static_cast<uint64_t>(i * 100);
        }
      });

  leveldb_approximate_sizes(&db_, 5, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(sizes[i], static_cast<uint64_t>(i * 100));
  }
}

// Test that ranges are constructed correctly with partial key lengths
TEST_F(ApproximateSizesTest_230, PartialKeyLengths_230) {
  // Key data is "abcdef" but we only use the first 3 characters
  const char* start_keys[] = {"abcdef"};
  size_t start_key_lens[] = {3};  // only "abc"
  const char* limit_keys[] = {"xyzwvu"};
  size_t limit_key_lens[] = {3};  // only "xyz"
  uint64_t sizes[1] = {0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 1, ::testing::_))
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        ASSERT_EQ(n, 1);
        EXPECT_EQ(ranges[0].start.size(), 3u);
        EXPECT_EQ(ranges[0].start.ToString(), "abc");
        EXPECT_EQ(ranges[0].limit.size(), 3u);
        EXPECT_EQ(ranges[0].limit.ToString(), "xyz");
        sizes[0] = 42;
      });

  leveldb_approximate_sizes(&db_, 1, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], 42u);
}

// Test sizes output with large uint64_t values
TEST_F(ApproximateSizesTest_230, LargeOutputSizes_230) {
  const char* start_keys[] = {"a"};
  size_t start_key_lens[] = {1};
  const char* limit_keys[] = {"z"};
  size_t limit_key_lens[] = {1};
  uint64_t sizes[1] = {0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 1, ::testing::_))
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        sizes[0] = UINT64_MAX;
      });

  leveldb_approximate_sizes(&db_, 1, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], UINT64_MAX);
}

// Test with identical start and limit keys
TEST_F(ApproximateSizesTest_230, SameStartAndLimitKey_230) {
  const char* start_keys[] = {"same"};
  size_t start_key_lens[] = {4};
  const char* limit_keys[] = {"same"};
  size_t limit_key_lens[] = {4};
  uint64_t sizes[1] = {0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 1, ::testing::_))
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        ASSERT_EQ(n, 1);
        EXPECT_EQ(ranges[0].start.ToString(), "same");
        EXPECT_EQ(ranges[0].limit.ToString(), "same");
        sizes[0] = 0;
      });

  leveldb_approximate_sizes(&db_, 1, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], 0u);
}

// Test with mixed key lengths
TEST_F(ApproximateSizesTest_230, MixedKeyLengths_230) {
  const char* start_keys[] = {"a", "medium_key", "x"};
  size_t start_key_lens[] = {1, 10, 1};
  const char* limit_keys[] = {"bbb", "n", "zzzzzzzzzzz"};
  size_t limit_key_lens[] = {3, 1, 11};
  uint64_t sizes[3] = {0, 0, 0};

  EXPECT_CALL(*mock_db_, GetApproximateSizes(::testing::_, 3, ::testing::_))
      .WillOnce([](const leveldb::Range* ranges, int n, uint64_t* sizes) {
        ASSERT_EQ(n, 3);
        EXPECT_EQ(ranges[0].start.size(), 1u);
        EXPECT_EQ(ranges[0].limit.size(), 3u);
        EXPECT_EQ(ranges[1].start.size(), 10u);
        EXPECT_EQ(ranges[1].limit.size(), 1u);
        EXPECT_EQ(ranges[2].start.size(), 1u);
        EXPECT_EQ(ranges[2].limit.size(), 11u);
        sizes[0] = 10;
        sizes[1] = 20;
        sizes[2] = 30;
      });

  leveldb_approximate_sizes(&db_, 3, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  EXPECT_EQ(sizes[0], 10u);
  EXPECT_EQ(sizes[1], 20u);
  EXPECT_EQ(sizes[2], 30u);
}
