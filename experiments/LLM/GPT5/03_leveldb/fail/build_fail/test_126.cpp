// max_grandparent_overlap_bytes_test_126.cc

#include <cstdint>
#include "gtest/gtest.h"

// Only rely on the public interface: Options and the function under test.
#include "leveldb/options.h"

// Forward declaration of the function under test, as exposed by the module.
namespace leveldb {
int64_t MaxGrandParentOverlapBytes(const Options* options);
}  // namespace leveldb

namespace leveldb {

class MaxGrandParentOverlapBytesTest_126 : public ::testing::Test {};

// Normal operation: uses default Options values.
TEST_F(MaxGrandParentOverlapBytesTest_126, ReturnsExpectedForDefaultOptions_126) {
  Options opt;  // Uses default max_file_size = 2 * 1024 * 1024 (2 MiB)
  // Expect 10 × TargetFileSize(options). Treating TargetFileSize as part of the module's observable behavior
  // through MaxGrandParentOverlapBytes, we compute expectation via Options' public knobs.
  const int64_t expected = static_cast<int64_t>(10) *
                           static_cast<int64_t>(opt.max_file_size);
  EXPECT_EQ(MaxGrandParentOverlapBytes(&opt), expected);
}

// Boundary: zero-sized target (if caller configures it).
TEST_F(MaxGrandParentOverlapBytesTest_126, ReturnsZeroWhenMaxFileSizeIsZero_126) {
  Options opt;
  opt.max_file_size = 0;
  EXPECT_EQ(MaxGrandParentOverlapBytes(&opt), 0);
}

// Boundary: smallest non-zero size.
TEST_F(MaxGrandParentOverlapBytesTest_126, HandlesSmallMaxFileSize_126) {
  Options opt;
  opt.max_file_size = 1;  // minimal non-zero
  EXPECT_EQ(MaxGrandParentOverlapBytes(&opt), 10);  // 10 * 1
}

// Normal operation: a custom, larger size.
TEST_F(MaxGrandParentOverlapBytesTest_126, RespectsCustomMaxFileSize_126) {
  Options opt;
  opt.max_file_size = 8 * 1024 * 1024;  // 8 MiB
  const int64_t expected = static_cast<int64_t>(10) *
                           static_cast<int64_t>(opt.max_file_size);  // 80 MiB
  EXPECT_EQ(MaxGrandParentOverlapBytes(&opt), expected);
}

// Large-value case near int64 range (but safely within it to avoid overflow).
TEST_F(MaxGrandParentOverlapBytesTest_126, LargeValueNearInt64Limit_126) {
  Options opt;
  // Choose a value such that 10 * value stays within int64_t.
  const int64_t safe = INT64_C(9223372036854775807) / 10;  // INT64_MAX / 10
  opt.max_file_size = static_cast<size_t>(safe);
  const int64_t expected = safe * 10;
  EXPECT_EQ(MaxGrandParentOverlapBytes(&opt), expected);
}

}  // namespace leveldb
