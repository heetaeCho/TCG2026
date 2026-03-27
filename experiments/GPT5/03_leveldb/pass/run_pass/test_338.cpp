// File: version_edit_clear_test_338.cc
#include <gtest/gtest.h>
#include <string>

#include "db/version_edit.h"  // assuming this is the public header
// If the project uses a different include path, adjust accordingly.

namespace {

using leveldb::VersionEdit;

static std::string Encoded(const VersionEdit& e) {
  std::string out;
  e.EncodeTo(&out);
  return out;
}

static std::string DebugStr(const VersionEdit& e) {
  return e.DebugString();
}

class VersionEditClearTest_338 : public ::testing::Test {
 protected:
  VersionEdit baseline_;  // untouched "default" edit to compare against
};

// Clear after setting multiple fields should make the edit equivalent to a fresh default edit.
TEST_F(VersionEditClearTest_338, ClearResetsToDefaultEncoding_338) {
  VersionEdit e;
  e.SetComparatorName("bytewise");
  e.SetLogNumber(123);
  e.SetPrevLogNumber(122);
  e.SetNextFile(1000);
  e.SetLastSequence(9999);

  // Sanity: changed object should differ from baseline before Clear()
  EXPECT_NE(Encoded(e), Encoded(baseline_));
  EXPECT_NE(DebugStr(e), DebugStr(baseline_));

  // After Clear(), it should match a freshly constructed/default edit.
  e.Clear();
  EXPECT_EQ(Encoded(e), Encoded(baseline_));
  EXPECT_EQ(DebugStr(e), DebugStr(baseline_));
}

// After Clear(), the object should accept new values and encode identically
// to a freshly constructed object that was set with the same values.
TEST_F(VersionEditClearTest_338, ClearAllowsReconfigurationConsistently_338) {
  VersionEdit e1;
  e1.SetComparatorName("cmpA");
  e1.SetLogNumber(7);
  e1.SetPrevLogNumber(6);
  e1.SetNextFile(42);
  e1.SetLastSequence(12345);

  // Clear and then set to a different configuration.
  e1.Clear();
  e1.SetComparatorName("cmpB");
  e1.SetLogNumber(1001);
  e1.SetPrevLogNumber(1000);
  e1.SetNextFile(7777);
  e1.SetLastSequence(88888);

  // Fresh object configured with the same values as the "post-Clear" object.
  VersionEdit e2;
  e2.SetComparatorName("cmpB");
  e2.SetLogNumber(1001);
  e2.SetPrevLogNumber(1000);
  e2.SetNextFile(7777);
  e2.SetLastSequence(88888);

  EXPECT_EQ(Encoded(e1), Encoded(e2));
  EXPECT_EQ(DebugStr(e1), DebugStr(e2));
}

// Calling Clear() on an already-default object should be a no-op (idempotent).
TEST_F(VersionEditClearTest_338, ClearOnDefaultIsNoOp_338) {
  VersionEdit e;
  const std::string before_enc = Encoded(e);
  const std::string before_dbg = DebugStr(e);

  e.Clear();

  EXPECT_EQ(Encoded(e), before_enc);
  EXPECT_EQ(DebugStr(e), before_dbg);
  // And should match baseline as well.
  EXPECT_EQ(Encoded(e), Encoded(baseline_));
  EXPECT_EQ(DebugStr(e), DebugStr(baseline_));
}

// Clear() should be idempotent: multiple calls produce the same observable state.
TEST_F(VersionEditClearTest_338, ClearIsIdempotent_338) {
  VersionEdit e;
  e.SetComparatorName("x");
  e.SetLogNumber(1);
  e.SetPrevLogNumber(0);
  e.SetNextFile(2);
  e.SetLastSequence(3);

  e.Clear();
  const std::string after_first_enc = Encoded(e);
  const std::string after_first_dbg = DebugStr(e);

  e.Clear();
  EXPECT_EQ(Encoded(e), after_first_enc);
  EXPECT_EQ(DebugStr(e), after_first_dbg);
  EXPECT_EQ(Encoded(e), Encoded(baseline_));
  EXPECT_EQ(DebugStr(e), DebugStr(baseline_));
}

// Boundary-ish case: set only one field, then Clear() should wipe it back to default.
TEST_F(VersionEditClearTest_338, ClearAfterPartialEdit_338) {
  VersionEdit e;

  // Try each single-field case separately to avoid assuming any internal coupling.
  // 1) Only comparator
  e.SetComparatorName("only-cmp");
  EXPECT_NE(Encoded(e), Encoded(baseline_));
  e.Clear();
  EXPECT_EQ(Encoded(e), Encoded(baseline_));
  EXPECT_EQ(DebugStr(e), DebugStr(baseline_));

  // 2) Only log number
  e.SetLogNumber(55);
  EXPECT_NE(Encoded(e), Encoded(baseline_));
  e.Clear();
  EXPECT_EQ(Encoded(e), Encoded(baseline_));

  // 3) Only prev log number
  e.SetPrevLogNumber(54);
  EXPECT_NE(Encoded(e), Encoded(baseline_));
  e.Clear();
  EXPECT_EQ(Encoded(e), Encoded(baseline_));

  // 4) Only next file number
  e.SetNextFile(777);
  EXPECT_NE(Encoded(e), Encoded(baseline_));
  e.Clear();
  EXPECT_EQ(Encoded(e), Encoded(baseline_));

  // 5) Only last sequence
  e.SetLastSequence(999);
  EXPECT_NE(Encoded(e), Encoded(baseline_));
  e.Clear();
  EXPECT_EQ(Encoded(e), Encoded(baseline_));
}

}  // namespace
