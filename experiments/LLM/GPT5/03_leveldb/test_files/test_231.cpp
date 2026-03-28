// File: db_c_compact_range_test_231.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstddef>
#include <cstring>
#include <memory>
#include <string>

using ::testing::_;
using ::testing::Invoke;
using ::testing::NiceMock;

// --- Minimal public interfaces from the prompt ---

namespace leveldb {

class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  // Only the accessors we need for black-box checks:
  const char* data() const { return data_; }
  size_t size() const { return size_; }
 private:
  const char* data_;
  size_t size_;
};

class Options;
class WriteOptions;
class ReadOptions;
class Snapshot;
class Iterator;
class Range;
class Status;
class WriteBatch;

class DB {
 public:
  DB() = default;
  DB(const DB&) = delete;
  DB& operator=(const DB&) = delete;
  virtual ~DB() = default;

  // We only need the CompactRange signature for mocking here.
  virtual void CompactRange(const Slice* begin, const Slice* end) {}
};

}  // namespace leveldb

// C wrapper-side struct from the prompt
struct leveldb_t {
 public:
  leveldb::DB* rep;
};

// Function under test (from db/c.cc). We declare it here to call it.
extern "C" void leveldb_compact_range(leveldb_t* db,
                                      const char* start_key,
                                      size_t start_key_len,
                                      const char* limit_key,
                                      size_t limit_key_len);

// --- Mock & Test Fixture ---

class MockDB_231 : public leveldb::DB {
 public:
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice* begin, const leveldb::Slice* end),
              (override));
};

class CompactRange_CApiTest_231 : public ::testing::Test {
 protected:
  NiceMock<MockDB_231> mock_db_;
  leveldb_t c_db_{&mock_db_};
};

// --- Tests ---

// Verifies that passing nullptr for both start and limit forwards nullptrs
// to DB::CompactRange.
TEST_F(CompactRange_CApiTest_231, BothKeysNull_231) {
  EXPECT_CALL(mock_db_, CompactRange(nullptr, nullptr))
      .Times(1);

  leveldb_compact_range(&c_db_, /*start_key=*/nullptr, /*start_key_len=*/0,
                        /*limit_key=*/nullptr, /*limit_key_len=*/0);
}

// Verifies that providing only a start key forwards a non-null begin slice
// with the correct length and data, and a null end.
TEST_F(CompactRange_CApiTest_231, StartOnly_231) {
  const char kStart[] = "alpha";
  EXPECT_CALL(mock_db_, CompactRange(_, nullptr))
      .WillOnce(Invoke([&](const leveldb::Slice* begin,
                           const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        EXPECT_EQ(begin->size(), sizeof(kStart) - 1u);
        EXPECT_EQ(std::memcmp(begin->data(), kStart, begin->size()), 0);
        EXPECT_EQ(end, nullptr);
      }));

  leveldb_compact_range(&c_db_, kStart, sizeof(kStart) - 1u,
                        /*limit_key=*/nullptr, /*limit_key_len=*/0);
}

// Verifies that providing only a limit key forwards a non-null end slice
// with the correct length and data, and a null begin.
TEST_F(CompactRange_CApiTest_231, LimitOnly_231) {
  const char kLimit[] = "omega";
  EXPECT_CALL(mock_db_, CompactRange(nullptr, _))
      .WillOnce(Invoke([&](const leveldb::Slice* begin,
                           const leveldb::Slice* end) {
        EXPECT_EQ(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(end->size(), sizeof(kLimit) - 1u);
        EXPECT_EQ(std::memcmp(end->data(), kLimit, end->size()), 0);
      }));

  leveldb_compact_range(&c_db_, /*start_key=*/nullptr, /*start_key_len=*/0,
                        kLimit, sizeof(kLimit) - 1u);
}

// Verifies that providing both keys forwards two non-null slices,
// each with the correct lengths and data.
TEST_F(CompactRange_CApiTest_231, BothKeysProvided_231) {
  const char kStart[] = "a_key";
  const char kLimit[] = "z_key";
  EXPECT_CALL(mock_db_, CompactRange(_, _))
      .WillOnce(Invoke([&](const leveldb::Slice* begin,
                           const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(begin->size(), sizeof(kStart) - 1u);
        EXPECT_EQ(end->size(), sizeof(kLimit) - 1u);
        EXPECT_EQ(std::memcmp(begin->data(), kStart, begin->size()), 0);
        EXPECT_EQ(std::memcmp(end->data(), kLimit, end->size()), 0);
      }));

  leveldb_compact_range(&c_db_, kStart, sizeof(kStart) - 1u,
                        kLimit, sizeof(kLimit) - 1u);
}

// Boundary case: start key pointer is non-null but length is zero.
// We only assert that a non-null begin slice is forwarded with size()==0,
// and that end is nullptr (no assumptions about data() when size==0).
TEST_F(CompactRange_CApiTest_231, ZeroLengthStart_231) {
  const char* kStart = "ignored_because_len_zero";
  EXPECT_CALL(mock_db_, CompactRange(_, nullptr))
      .WillOnce(Invoke([&](const leveldb::Slice* begin,
                           const leveldb::Slice* end) {
        ASSERT_NE(begin, nullptr);
        EXPECT_EQ(begin->size(), 0u);
        EXPECT_EQ(end, nullptr);
      }));

  leveldb_compact_range(&c_db_, kStart, /*start_key_len=*/0,
                        /*limit_key=*/nullptr, /*limit_key_len=*/0);
}

// Boundary case: limit key pointer is non-null but length is zero.
// We assert that a non-null end slice is forwarded with size()==0,
// and that begin is nullptr (no assumptions about data() when size==0).
TEST_F(CompactRange_CApiTest_231, ZeroLengthLimit_231) {
  const char* kLimit = "ignored_because_len_zero";
  EXPECT_CALL(mock_db_, CompactRange(nullptr, _))
      .WillOnce(Invoke([&](const leveldb::Slice* begin,
                           const leveldb::Slice* end) {
        EXPECT_EQ(begin, nullptr);
        ASSERT_NE(end, nullptr);
        EXPECT_EQ(end->size(), 0u);
      }));

  leveldb_compact_range(&c_db_, /*start_key=*/nullptr, /*start_key_len=*/0,
                        kLimit, /*limit_key_len=*/0);
}
