// File: compaction_edit_test_80.cc

#include <gtest/gtest.h>
#include "db/version_set.h"  // Provides leveldb::Compaction and VersionEdit

namespace leveldb {

class CompactionTest_80 : public ::testing::Test {
protected:
  // Keep tests minimal and black-box: just construct and use the public API.
  Compaction compaction_;  // Assumes default-constructible per provided interface snippet
};

// [Normal] edit() returns a non-null pointer.
TEST_F(CompactionTest_80, EditReturnsNonNull_80) {
  VersionEdit* e = compaction_.edit();
  ASSERT_NE(e, nullptr);
}

// [Normal] Multiple calls to edit() return the same pointer (stable handle).
TEST_F(CompactionTest_80, EditReturnsSamePointerOnMultipleCalls_80) {
  VersionEdit* first = compaction_.edit();
  VersionEdit* second = compaction_.edit();
  ASSERT_NE(first, nullptr);
  ASSERT_NE(second, nullptr);
  EXPECT_EQ(first, second);
}

// [Boundary/Robustness] The pointer remains valid across repeated accesses.
// (We only verify pointer stability without asserting on VersionEdit internals.)
TEST_F(CompactionTest_80, EditPointerRemainsStableAfterNoOpUse_80) {
  VersionEdit* e = compaction_.edit();
  ASSERT_NE(e, nullptr);

  // Perform repeated accesses; we do not depend on VersionEdit internals.
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(e, compaction_.edit());
  }
}

}  // namespace leveldb
