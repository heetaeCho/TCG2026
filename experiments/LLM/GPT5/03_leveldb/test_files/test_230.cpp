// approximate_sizes_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

using ::testing::_;
using ::testing::Invoke;
using ::testing::SaveArg;
using ::testing::StrictMock;

namespace leveldb {

// ---- Minimal interfaces from the provided partial code ----
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  explicit Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  explicit Slice(const char* s) : data_(s), size_(std::strlen(s)) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
 private:
  const char* data_;
  size_t size_;
};

struct Range {
  Slice start;
  Slice limit;
  Range() = default;
  Range(const Slice& s, const Slice& l) : start(s), limit(l) {}
};

class DB {
 public:
  virtual ~DB() = default;
  // We only need this one virtual for the tests.
  virtual void GetApproximateSizes(const Range* range, int n, uint64_t* sizes) {
    // Default no-op
  }
};

}  // namespace leveldb

// ---- C wrapper surface from db/c.cc (under test) ----
struct leveldb_t { leveldb::DB* rep; };

// Declaration of the function under test (from db/c.cc).
void leveldb_approximate_sizes(leveldb_t* db,
                               int num_ranges,
                               const char* const* range_start_key,
                               const size_t* range_start_key_len,
                               const char* const* range_limit_key,
                               const size_t* range_limit_key_len,
                               uint64_t* sizes);

// ---- Mock DB to verify external interactions ----
class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(void, GetApproximateSizes,
              (const leveldb::Range* range, int n, uint64_t* sizes),
              (override));
};

// ---- Test fixture ----
class ApproxSizesTest_230 : public ::testing::Test {
 protected:
  StrictMock<MockDB> mock_;
  leveldb_t c_db_{&mock_};
};

// Verifies that ranges and count are forwarded correctly and the Slices
// are constructed from (ptr,len) without inferring internal logic.
TEST_F(ApproxSizesTest_230, ForwardsRangesAndCount_230) {
  const char* starts[] = {"a", "k1"};
  const size_t starts_len[] = {1u, 2u};
  const char* limits[] = {"d", "z9"};
  const size_t limits_len[] = {1u, 2u};
  uint64_t sizes[2] = {0, 0};

  EXPECT_CALL(mock_, GetApproximateSizes(_, 2, _))
      .WillOnce(Invoke([&](const leveldb::Range* ranges, int n, uint64_t* out) {
        EXPECT_EQ(2, n);
        ASSERT_NE(nullptr, ranges);

        // Range 0
        EXPECT_EQ(starts_len[0], ranges[0].start.size());
        EXPECT_EQ(0, std::memcmp(starts[0], ranges[0].start.data(), starts_len[0]));
        EXPECT_EQ(limits_len[0], ranges[0].limit.size());
        EXPECT_EQ(0, std::memcmp(limits[0], ranges[0].limit.data(), limits_len[0]));

        // Range 1
        EXPECT_EQ(starts_len[1], ranges[1].start.size());
        EXPECT_EQ(0, std::memcmp(starts[1], ranges[1].start.data(), starts_len[1]));
        EXPECT_EQ(limits_len[1], ranges[1].limit.size());
        EXPECT_EQ(0, std::memcmp(limits[1], ranges[1].limit.data(), limits_len[1]));

        // Optionally write something to sizes to ensure pointer is usable.
        out[0] = 10;
        out[1] = 20;
      }));

  leveldb_approximate_sizes(&c_db_, /*num_ranges=*/2,
                            starts, starts_len, limits, limits_len, sizes);

  EXPECT_EQ(10u, sizes[0]);
  EXPECT_EQ(20u, sizes[1]);
}

// Verifies that a zero-range call is forwarded with n==0 and does not require
// valid range memory from the caller’s perspective.
TEST_F(ApproxSizesTest_230, ForwardsZeroRanges_230) {
  // Empty inputs
  const char* starts[] = {};
  const size_t starts_len[] = {};
  const char* limits[] = {};
  const size_t limits_len[] = {};
  uint64_t sizes[] = {0};  // single element; should be untouched by wrapper

  const leveldb::Range* captured_ranges = reinterpret_cast<const leveldb::Range*>(0x1); // sentinel
  EXPECT_CALL(mock_, GetApproximateSizes(_, 0, _))
      .WillOnce(Invoke([&](const leveldb::Range* ranges, int n, uint64_t* out) {
        EXPECT_EQ(0, n);
        // The wrapper may pass a non-null pointer even for 0, but must not dereference it.
        captured_ranges = ranges;
        // Do not write to out since n==0, just ensure no crash.
        (void)out;
      }));

  leveldb_approximate_sizes(&c_db_, /*num_ranges=*/0,
                            starts, starts_len, limits, limits_len, sizes);

  // We only verify it didn't crash and the expectation on n==0 held.
  // (No further observable effects are required/guaranteed.)
  (void)captured_ranges;
}

// Verifies that the sizes pointer is forwarded unchanged to the underlying DB.
TEST_F(ApproxSizesTest_230, ForwardsSizesPointer_230) {
  const char* starts[] = {"a"};
  const size_t starts_len[] = {1u};
  const char* limits[] = {"b"};
  const size_t limits_len[] = {1u};
  uint64_t sizes[1] = {0};

  uint64_t* captured_sizes_ptr = nullptr;
  EXPECT_CALL(mock_, GetApproximateSizes(_, 1, _))
      .WillOnce(DoAll(SaveArg<2>(&captured_sizes_ptr),
                      Invoke([](const leveldb::Range* ranges, int n, uint64_t* out) {
                        // Write via the received pointer to ensure the caller observes it.
                        out[0] = 123456u;
                      })));

  leveldb_approximate_sizes(&c_db_, /*num_ranges=*/1,
                            starts, starts_len, limits, limits_len, sizes);

  ASSERT_EQ(captured_sizes_ptr, sizes);
  EXPECT_EQ(123456u, sizes[0]);
}

// Verifies correct handling of binary keys (embedded NULs) using (ptr,len) inputs.
TEST_F(ApproxSizesTest_230, HandlesBinaryKeys_230) {
  const char s0[] = {'a', '\0', 'b'};  // len 3
  const char l0[] = {'c', '\0', 'd', '\0'};  // len 4
  const char* starts[] = {s0};
  const size_t starts_len[] = {sizeof(s0)};
  const char* limits[] = {l0};
  const size_t limits_len[] = {sizeof(l0)};
  uint64_t sizes[1] = {0};

  EXPECT_CALL(mock_, GetApproximateSizes(_, 1, _))
      .WillOnce(Invoke([&](const leveldb::Range* ranges, int n, uint64_t* out) {
        EXPECT_EQ(1, n);
        ASSERT_NE(nullptr, ranges);

        EXPECT_EQ(sizeof(s0), ranges[0].start.size());
        EXPECT_EQ(0, std::memcmp(s0, ranges[0].start.data(), sizeof(s0)));

        EXPECT_EQ(sizeof(l0), ranges[0].limit.size());
        EXPECT_EQ(0, std::memcmp(l0, ranges[0].limit.data(), sizeof(l0)));

        out[0] = 42u;  // arbitrary to confirm observability
      }));

  leveldb_approximate_sizes(&c_db_, /*num_ranges=*/1,
                            starts, starts_len, limits, limits_len, sizes);

  EXPECT_EQ(42u, sizes[0]);
}
