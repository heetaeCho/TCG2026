// File: version_set_expanded_compaction_limit_test_127.cc

#include "gtest/gtest.h"

// Include the implementation unit to access internal static functions.
// This keeps us strictly black-box relative to observable behavior.
#include "db/version_set.cc"

namespace leveldb {

class VersionSetExpandedLimitTest_127 : public ::testing::Test {
 protected:
  Options opts_;  // Use default-constructed options; tests may tweak fields.
};

// [Normal] Default options keep the 25x relationship.
TEST_F(VersionSetExpandedLimitTest_127, DefaultOptions_Returns25xTargetFileSize_127) {
  const int64_t limit = ExpandedCompactionByteSizeLimit(&opts_);
  const uint64_t tf = static_cast<uint64_t>(TargetFileSize(&opts_));
  ASSERT_GE(tf, 0u);
  // Verify exact observable relationship: limit == 25 * TargetFileSize(options)
  EXPECT_EQ(limit, static_cast<int64_t>(25u * tf));
}

// [Boundary-ish] Changing options (various sizes) preserves the 25x relationship.
// We do not assume how TargetFileSize is derived; we only compare to it.
TEST_F(VersionSetExpandedLimitTest_127, OptionsChanges_Preserve25xRelationship_127) {
  // Try several representative magnitudes; safe from overflow.
  const uint64_t sizes[] = {
      1u,
      4u * 1024u,                // 4 KiB
      2u * 1024u * 1024u,        // 2 MiB
      64u * 1024u * 1024u        // 64 MiB
  };

  for (uint64_t s : sizes) {
    // We only tweak Options fields; we never assume how they're used by TargetFileSize.
    opts_.max_file_size = static_cast<size_t>(s);

    const uint64_t tf = static_cast<uint64_t>(TargetFileSize(&opts_));
    const int64_t limit = ExpandedCompactionByteSizeLimit(&opts_);

    // Observable behavior: limit equals 25x of TargetFileSize for the same Options.
    EXPECT_EQ(limit, static_cast<int64_t>(25u * tf)) << "Failed for size hint=" << s;
  }
}

// [Boundary] If TargetFileSize becomes very small, result scales accordingly.
// (We don't assert policy; we only verify the relationship holds.)
TEST_F(VersionSetExpandedLimitTest_127, VerySmallTargetSize_Still25x_127) {
  opts_.max_file_size = 0;  // Do not assume semantics; just observe behavior.
  const uint64_t tf = static_cast<uint64_t>(TargetFileSize(&opts_));
  const int64_t limit = ExpandedCompactionByteSizeLimit(&opts_);
  EXPECT_EQ(limit, static_cast<int64_t>(25u * tf));
}

}  // namespace leveldb
