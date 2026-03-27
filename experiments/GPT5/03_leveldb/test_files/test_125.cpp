// File: version_set_target_file_size_test_125.cc

#include <gtest/gtest.h>

// Use the public interface only.
#include "leveldb/options.h"

// Include the implementation unit so we can call the internal-static function
// without re-declaring it. This keeps us from re-implementing or inferring logic.
#include "db/version_set.cc"

namespace leveldb {

class TargetFileSizeTest_125 : public ::testing::Test {};

// [Normal] Returns whatever value is currently set in Options::max_file_size.
TEST_F(TargetFileSizeTest_125, ReturnsCurrentOptionValue_125) {
  Options opts;  // rely only on the public struct interface
  const size_t expected = opts.max_file_size;  // observable state

  const size_t actual = TargetFileSize(&opts);
  EXPECT_EQ(actual, expected);
}

// [Normal] If we change max_file_size, the return should reflect the change.
TEST_F(TargetFileSizeTest_125, ReflectsUpdatedMaxFileSize_125) {
  Options opts;
  opts.max_file_size = 8 * 1024 * 1024;  // 8 MiB (arbitrary test value)

  const size_t actual = TargetFileSize(&opts);
  EXPECT_EQ(actual, opts.max_file_size);
}

// [Boundary] Zero is a valid size_t; ensure it’s returned unchanged.
TEST_F(TargetFileSizeTest_125, AcceptsZeroBoundary_125) {
  Options opts;
  opts.max_file_size = 0;

  const size_t actual = TargetFileSize(&opts);
  EXPECT_EQ(actual, static_cast<size_t>(0));
}

// [Boundary] Large values should be passed through unchanged (no overflow/alteration).
TEST_F(TargetFileSizeTest_125, AcceptsLargeValues_125) {
  Options opts;
  // Use a large but representable size_t value without assuming exact platform max.
  const size_t large = static_cast<size_t>(1) << (sizeof(size_t) * 8 - 2); // 2^(N-2)
  opts.max_file_size = large;

  const size_t actual = TargetFileSize(&opts);
  EXPECT_EQ(actual, large);
}

// [Safety/Non-modifying] The function must not mutate Options.
TEST_F(TargetFileSizeTest_125, DoesNotModifyOptions_125) {
  Options opts;
  const size_t original = opts.max_file_size;

  (void)TargetFileSize(&opts);  // call for its observable return
  EXPECT_EQ(opts.max_file_size, original);  // still the same
}

}  // namespace leveldb
