// File: patchlist_append_test_287.cc
#include <gtest/gtest.h>
#include "re2/prog.h"   // for re2::Prog::Inst
// If PatchList is in a public header, include it here as well.
// Otherwise, the build should already make re2::PatchList visible.

namespace re2 {

class PatchListAppendTest_287 : public ::testing::Test {
protected:
  // Helper to make a small instruction array we can patch.
  // We initialize only the indices we care about in each test.
  std::vector<Prog::Inst> insts_;
  void SetUp() override { insts_.resize(4); }
  Prog::Inst* base() { return insts_.data(); }
};

// Appends with non-empty l1 and l2; l1.tail even -> patches out()
TEST_F(PatchListAppendTest_287, PatchesOutOnEvenTail_287) {
  // Target instruction index = (tail >> 1) = 1  => tail = 2 (even)
  insts_[1].InitAlt(/*out=*/100, /*out1=*/200);

  PatchList l1{/*head=*/10u, /*tail=*/2u};
  PatchList l2{/*head=*/20u, /*tail=*/30u};

  PatchList r = PatchList::Append(base(), l1, l2);

  // Should have updated out() only, preserved out1()
  EXPECT_EQ(insts_[1].out(), 20);
  EXPECT_EQ(insts_[1].out1(), 200);

  // Return value should carry l1.head and l2.tail
  EXPECT_EQ(r.head, 10u);
  EXPECT_EQ(r.tail, 30u);
}

// Appends with non-empty l1 and l2; l1.tail odd -> patches out1()
TEST_F(PatchListAppendTest_287, PatchesOut1OnOddTail_287) {
  // Target instruction index = 1, tail = (1 << 1) | 1 = 3 (odd)
  insts_[1].InitAlt(/*out=*/101, /*out1=*/201);

  PatchList l1{/*head=*/11u, /*tail=*/3u};
  PatchList l2{/*head=*/21u, /*tail=*/31u};

  PatchList r = PatchList::Append(base(), l1, l2);

  // Should have updated out1() only, preserved out()
  EXPECT_EQ(insts_[1].out(), 101);
  EXPECT_EQ(insts_[1].out1(), 21);

  // Return value should carry l1.head and l2.tail
  EXPECT_EQ(r.head, 11u);
  EXPECT_EQ(r.tail, 31u);
}

// If l1 is empty (head == 0), Append returns l2 and does not patch anything
TEST_F(PatchListAppendTest_287, ReturnsL2WhenL1Empty_287) {
  insts_[1].InitAlt(/*out=*/300, /*out1=*/400);

  PatchList l1{/*head=*/0u, /*tail=*/3u};   // tail irrelevant when head==0
  PatchList l2{/*head=*/22u, /*tail=*/32u};

  PatchList r = PatchList::Append(base(), l1, l2);

  // No mutation expected
  EXPECT_EQ(insts_[1].out(), 300);
  EXPECT_EQ(insts_[1].out1(), 400);

  // Should return l2 verbatim
  EXPECT_EQ(r.head, 22u);
  EXPECT_EQ(r.tail, 32u);
}

// If l2 is empty (head == 0), Append returns l1 and does not patch anything
TEST_F(PatchListAppendTest_287, ReturnsL1WhenL2Empty_287) {
  insts_[1].InitAlt(/*out=*/500, /*out1=*/600);

  PatchList l1{/*head=*/33u, /*tail=*/2u};
  PatchList l2{/*head=*/0u, /*tail=*/0u};

  PatchList r = PatchList::Append(base(), l1, l2);

  // No mutation expected
  EXPECT_EQ(insts_[1].out(), 500);
  EXPECT_EQ(insts_[1].out1(), 600);

  // Should return l1 verbatim
  EXPECT_EQ(r.head, 33u);
  EXPECT_EQ(r.tail, 2u);
}

// Both empty: returns empty and does not patch anything
TEST_F(PatchListAppendTest_287, BothEmptyReturnsEmpty_287) {
  insts_[0].InitAlt(/*out=*/700, /*out1=*/701);

  PatchList l1{/*head=*/0u, /*tail=*/0u};
  PatchList l2{/*head=*/0u, /*tail=*/0u};

  PatchList r = PatchList::Append(base(), l1, l2);

  EXPECT_EQ(insts_[0].out(), 700);
  EXPECT_EQ(insts_[0].out1(), 701);
  EXPECT_EQ(r.head, 0u);
  EXPECT_EQ(r.tail, 0u);
}

// Verifies the patched instruction index is (l1.tail >> 1) — only that one changes
TEST_F(PatchListAppendTest_287, PatchesCorrectIndex_287) {
  // Prepare two different instructions to detect accidental cross-updates
  insts_[0].InitAlt(/*out=*/1000, /*out1=*/1001);
  insts_[1].InitAlt(/*out=*/2000, /*out1=*/2001);

  // Choose to patch index 0, even tail -> patch out() of insts_[0]
  PatchList l1{/*head=*/44u, /*tail=*/0u};       // (0 >> 1) = 0
  PatchList l2{/*head=*/777u, /*tail=*/888u};

  PatchList r = PatchList::Append(base(), l1, l2);

  // Only insts_[0] should be affected (out() changed)
  EXPECT_EQ(insts_[0].out(), 777);
  EXPECT_EQ(insts_[0].out1(), 1001);
  EXPECT_EQ(insts_[1].out(), 2000);
  EXPECT_EQ(insts_[1].out1(), 2001);

  EXPECT_EQ(r.head, 44u);
  EXPECT_EQ(r.tail, 888u);
}

}  // namespace re2
