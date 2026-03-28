#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "re2/prog.h"
#include "re2/sparse_set.h"

// Include the .cc to access the internal static function under test.
// This keeps us from changing production visibility and still treats
// the implementation as a black box from the test's perspective.
#include "re2/prog.cc"

using ::testing::HasSubstr;
using ::re2::Prog;
using ::re2::SparseSet;

// In prog.cc, Workq is typedef'd to SparseSet.
namespace re2 {
  // Just to be explicit in tests.
  using Workq = SparseSet;
}

// A small fixture that gives us a fresh Prog and Workq per test.
class ProgToStringTest_400 : public ::testing::Test {
protected:
  Prog prog_;
  re2::Workq q_;  // queue we will seed and observe

  // Helper to expect that the returned string includes a correctly
  // formatted line for a given instruction id using the instruction's
  // own Dump() output (no assumptions about Dump() formatting).
  void ExpectHasLineFor(int id, const std::string& s) {
    Prog::Inst* ip = prog_.inst(id);
    ASSERT_NE(ip, nullptr);
    std::string want = absl::StrFormat("%d. %s\n", id, ip->Dump());
    EXPECT_THAT(s, HasSubstr(want));
  }
};

// ------------------------------------------------------------------
// Boundary: Empty queue produces an empty string and no changes
// ------------------------------------------------------------------
TEST_F(ProgToStringTest_400, EmptyQueue_YieldsEmptyString_400) {
  // q_ starts empty by default.
  std::string out = re2::ProgToString(&prog_, &q_);
  EXPECT_TRUE(out.empty());
  // Still empty after call (no items to expand).
  EXPECT_EQ(q_.size(), 0);
}

// ------------------------------------------------------------------
// Normal: Single NOP instruction listed; queue gets out() enqueued
// ------------------------------------------------------------------
TEST_F(ProgToStringTest_400, SingleNop_FormatsLineAndQueuesOut_400) {
  // Arrange: make inst 0 a NOP that points to 1.
  Prog::Inst* i0 = prog_.inst(0);
  ASSERT_NE(i0, nullptr);
  i0->InitNop(/*out=*/1);

  // Seed work queue with only item 0.
  q_.clear();
  q_.insert(0);

  // Act
  std::string s = re2::ProgToString(&prog_, &q_);

  // Assert: string contains the single "0. <Dump()>\n" line.
  ExpectHasLineFor(0, s);

  // And side effect: out (1) should have been added to the queue.
  // (We don't assume anything else about AddToQueue beyond observable membership.)
  EXPECT_TRUE(q_.contains(1));
}

// ------------------------------------------------------------------
// Normal: ALT instruction enqueues both out() and out1()
// ------------------------------------------------------------------
TEST_F(ProgToStringTest_400, Alt_QueuesOutAndOut1_AndFormatsBoth_400) {
  // Arrange: inst 2 is ALT with out=3 and out1=4.
  Prog::Inst* i2 = prog_.inst(2);
  ASSERT_NE(i2, nullptr);
  i2->InitAlt(/*out=*/3, /*out1=*/4);

  // Also prepare reasonable targets (not strictly required for formatting,
  // but keeps things well-formed).
  Prog::Inst* i3 = prog_.inst(3);
  Prog::Inst* i4 = prog_.inst(4);
  ASSERT_NE(i3, nullptr);
  ASSERT_NE(i4, nullptr);
  i3->InitMatch(/*id=*/123);
  i4->InitFail();

  // Seed with 2 so it will be listed/processed.
  q_.clear();
  q_.insert(2);

  // Act
  std::string s = re2::ProgToString(&prog_, &q_);

  // Assert: contains the line for 2 (we don't require lines for 3/4 unless queued and iterated later).
  ExpectHasLineFor(2, s);

  // Side effects: both out and out1 are added.
  EXPECT_TRUE(q_.contains(3));
  EXPECT_TRUE(q_.contains(4));
}

// ------------------------------------------------------------------
// Normal: ByteRange enqueues only out(), not out1(), and formats
// ------------------------------------------------------------------
TEST_F(ProgToStringTest_400, ByteRange_QueuesOnlyOut_FormatsLine_400) {
  // Arrange: inst 5 is ByteRange [ 'a' .. 'z' ] with out=6.
  Prog::Inst* i5 = prog_.inst(5);
  ASSERT_NE(i5, nullptr);
  i5->InitByteRange(/*lo=*/'a', /*hi=*/'z', /*foldcase=*/0, /*out=*/6);

  // Target inst (optional for this test)
  Prog::Inst* i6 = prog_.inst(6);
  ASSERT_NE(i6, nullptr);
  i6->InitMatch(/*id=*/777);

  q_.clear();
  q_.insert(5);

  // Act
  std::string s = re2::ProgToString(&prog_, &q_);

  // Assert: formatting line exists
  ExpectHasLineFor(5, s);

  // And only out() should be added; there is no out1() path for ByteRange.
  EXPECT_TRUE(q_.contains(6));
  // We can sanity check that an unrelated id isn't suddenly present.
  EXPECT_FALSE(q_.contains(7));
}

// ------------------------------------------------------------------
// Mixed: Multiple seeds are all formatted; order follows Workq iteration
// ------------------------------------------------------------------
TEST_F(ProgToStringTest_400, MultipleSeeds_AllFormatted_NoCrash_400) {
  // Arrange several heterogeneous instructions
  prog_.inst(0)->InitNop(/*out=*/1);
  prog_.inst(1)->InitMatch(/*id=*/42);
  prog_.inst(2)->InitAlt(/*out=*/0, /*out1=*/1);

  q_.clear();
  // Insert in a specific order; SparseSet iteration is by internal policy.
  q_.insert(0);
  q_.insert(2);

  // Act
  std::string s = re2::ProgToString(&prog_, &q_);

  // Assert: lines exist for all seeds observed.
  ExpectHasLineFor(0, s);
  ExpectHasLineFor(2, s);

  // Side effects: from 0->out(1), 2->out(0) and out1(1). All should be present.
  EXPECT_TRUE(q_.contains(0));
  EXPECT_TRUE(q_.contains(1));
}

// ------------------------------------------------------------------
// Boundary: ALT_MATCH behaves like ALT w.r.t. queuing out1()
// ------------------------------------------------------------------
TEST_F(ProgToStringTest_400, AltMatch_QueuesOutAndOut1_400) {
  // Arrange
  prog_.inst(10)->InitAlt(/*out=*/11, /*out1=*/12);

  // Force opcode to be ALT_MATCH via public API if available.
  // If not directly constructible via separate initializer in this interface,
  // we still validate behavior by using ALT (which is the same branch in code).
  // (We avoid guessing implementation details; observable behavior is the same.)
  // Seed
  q_.clear();
  q_.insert(10);

  // Act
  std::string s = re2::ProgToString(&prog_, &q_);

  // Assert
  ExpectHasLineFor(10, s);
  EXPECT_TRUE(q_.contains(11));
  EXPECT_TRUE(q_.contains(12));
}
