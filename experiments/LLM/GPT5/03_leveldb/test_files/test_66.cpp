// File: version_edit_set_compact_pointer_test.cc

#include "db/version_edit.h"
#include "db/dbformat.h"

#include <gtest/gtest.h>

namespace leveldb {

class VersionEditTest_66 : public ::testing::Test {
protected:
  VersionEdit ve_;
};

// [66] Normal operation: calling SetCompactPointer changes the observable state.
TEST_F(VersionEditTest_66, SetCompactPointer_ChangesDebugString_66) {
  const std::string before = ve_.DebugString();

  InternalKey key; // default-constructed; we do not assume any internal content
  ve_.SetCompactPointer(/*level=*/0, key);

  const std::string after = ve_.DebugString();
  EXPECT_NE(before, after);
}

// [66] Adding multiple compact pointers updates observable state each time.
TEST_F(VersionEditTest_66, MultipleSetCompactPointer_UpdatesDebugString_66) {
  InternalKey k1;
  InternalKey k2;

  const std::string s0 = ve_.DebugString();

  ve_.SetCompactPointer(0, k1);
  const std::string s1 = ve_.DebugString();
  EXPECT_NE(s0, s1);

  ve_.SetCompactPointer(2, k2);
  const std::string s2 = ve_.DebugString();
  EXPECT_NE(s1, s2);
}

// [66] Boundary-ish levels: negative and large levels are accepted by the interface
// and produce observable changes (we do not assert on specific formatting/content).
TEST_F(VersionEditTest_66, SetCompactPointer_WithBoundaryLevels_66) {
  const std::string before = ve_.DebugString();

  InternalKey k_neg, k_large;
  ve_.SetCompactPointer(-1, k_neg);       // negative level
  ve_.SetCompactPointer(1 << 20, k_large); // large level

  const std::string after = ve_.DebugString();
  EXPECT_NE(before, after);
}

// [66] Clear() removes previously recorded effects (observable via DebugString()).
TEST_F(VersionEditTest_66, Clear_RemovesCompactPointers_Effects_66) {
  InternalKey k;
  ve_.SetCompactPointer(0, k);

  const std::string with_ptrs = ve_.DebugString();
  EXPECT_NE(std::string(), with_ptrs); // sanity: something is recorded

  ve_.Clear();

  VersionEdit fresh; // baseline for comparison after Clear()
  EXPECT_EQ(fresh.DebugString(), ve_.DebugString());
}

} // namespace leveldb
