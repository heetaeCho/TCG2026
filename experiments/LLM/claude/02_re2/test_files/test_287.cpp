#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

// We need access to PatchList which is defined in compile.cc
// Since PatchList is internal to compile.cc, we need to test it through
// the compilation interface or recreate the struct for testing.
// However, based on the constraints, we test the observable behavior.

// Since PatchList is an internal struct in compile.cc and not directly
// exposed through a public header, we need to include compile.cc or
// use a workaround. Let's define the struct matching the known interface
// and test the Append function behavior.

namespace re2 {

// Forward declaration matching the actual struct
struct PatchList {
  uint32_t head;
  uint32_t tail;

  static PatchList Mk(uint32_t p);
  static void Patch(Prog::Inst* inst0, PatchList l, uint32_t p);
  static PatchList Append(Prog::Inst* inst0, PatchList l1, PatchList l2);
};

class PatchListTest_287 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize an array of instructions for testing
    for (int i = 0; i < kMaxInst; i++) {
      inst_[i].InitFail();
    }
  }

  static const int kMaxInst = 64;
  Prog::Inst inst_[64];
};

// Test that Append with both empty lists returns empty
TEST_F(PatchListTest_287, AppendBothEmpty_287) {
  PatchList l1 = {0, 0};
  PatchList l2 = {0, 0};
  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, 0u);
}

// Test that Append with first list empty returns second list
TEST_F(PatchListTest_287, AppendFirstEmpty_287) {
  PatchList l1 = {0, 0};
  PatchList l2 = {4, 6};  // non-empty
  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, l2.head);
  EXPECT_EQ(result.tail, l2.tail);
}

// Test that Append with second list empty returns first list
TEST_F(PatchListTest_287, AppendSecondEmpty_287) {
  PatchList l1 = {4, 6};  // non-empty
  PatchList l2 = {0, 0};
  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, l1.head);
  EXPECT_EQ(result.tail, l1.tail);
}

// Test that Append with two non-empty lists produces correct head and tail
// When tail is even (tail&1 == 0), set_out is called on inst_[tail>>1]
TEST_F(PatchListTest_287, AppendTwoNonEmptyEvenTail_287) {
  // Initialize instructions as Alt so they have out and out1 fields
  inst_[1].InitAlt(0, 0);  // index 1
  inst_[2].InitAlt(0, 0);  // index 2
  inst_[3].InitAlt(0, 0);  // index 3

  // l1 with even tail (tail&1 == 0) -> set_out path
  // tail>>1 gives the instruction index
  // tail = 2 means inst_[1], and tail&1 = 0 -> set_out
  PatchList l1 = {2, 2};   // head=2, tail=2 (even)
  PatchList l2 = {4, 6};   // head=4, tail=6

  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, l1.head);
  EXPECT_EQ(result.tail, l2.tail);

  // The instruction at index tail>>1 = 1 should have out set to l2.head
  EXPECT_EQ(static_cast<uint32_t>(inst_[1].out()), l2.head);
}

// Test that Append with odd tail sets out1_ field
TEST_F(PatchListTest_287, AppendTwoNonEmptyOddTail_287) {
  // Initialize instructions as Alt so they have out1 fields
  inst_[1].InitAlt(0, 0);  // index 1
  inst_[2].InitAlt(0, 0);  // index 2

  // l1 with odd tail (tail&1 == 1) -> out1_ path
  // tail = 3 means inst_[3>>1] = inst_[1], and tail&1 = 1 -> out1_
  PatchList l1 = {2, 3};   // head=2, tail=3 (odd)
  PatchList l2 = {4, 6};   // head=4, tail=6

  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, l1.head);
  EXPECT_EQ(result.tail, l2.tail);

  // The instruction at index tail>>1 = 1 should have out1_ set to l2.head
  EXPECT_EQ(inst_[1].out1_, l2.head);
}

// Test Mk creates a PatchList with head and tail both equal to the argument
TEST_F(PatchListTest_287, MkCreatesCorrectList_287) {
  PatchList pl = PatchList::Mk(10);
  EXPECT_EQ(pl.head, 10u);
  EXPECT_EQ(pl.tail, 10u);
}

// Test Mk with zero
TEST_F(PatchListTest_287, MkWithZero_287) {
  PatchList pl = PatchList::Mk(0);
  EXPECT_EQ(pl.head, 0u);
  EXPECT_EQ(pl.tail, 0u);
}

// Test Patch sets the target of all entries in the patch list
TEST_F(PatchListTest_287, PatchSetsTarget_287) {
  // Create a single-element patch list using even encoding
  // For a single element, Mk should create head==tail
  inst_[1].InitAlt(0, 0);

  PatchList pl = PatchList::Mk(2);  // points to inst_[1] via out (even)
  PatchList::Patch(inst_, pl, 42);

  EXPECT_EQ(static_cast<uint32_t>(inst_[1].out()), 42u);
}

// Test Patch with odd-encoded entry sets out1_
TEST_F(PatchListTest_287, PatchSetsOut1Target_287) {
  inst_[2].InitAlt(0, 0);

  PatchList pl = PatchList::Mk(5);  // 5>>1 = 2, 5&1 = 1 -> out1_ of inst_[2]
  PatchList::Patch(inst_, pl, 99);

  EXPECT_EQ(inst_[2].out1_, 99u);
}

// Test that Append correctly chains multiple lists
TEST_F(PatchListTest_287, AppendChainMultiple_287) {
  inst_[1].InitAlt(0, 0);
  inst_[2].InitAlt(0, 0);
  inst_[3].InitAlt(0, 0);

  PatchList l1 = PatchList::Mk(2);   // inst_[1] out
  PatchList l2 = PatchList::Mk(4);   // inst_[2] out
  PatchList l3 = PatchList::Mk(6);   // inst_[3] out

  PatchList combined = PatchList::Append(inst_, l1, l2);
  combined = PatchList::Append(inst_, combined, l3);

  EXPECT_EQ(combined.head, 2u);
  EXPECT_EQ(combined.tail, 6u);

  // Patch the entire chain
  PatchList::Patch(inst_, combined, 100);

  EXPECT_EQ(static_cast<uint32_t>(inst_[1].out()), static_cast<uint32_t>(l2.head));
  EXPECT_EQ(static_cast<uint32_t>(inst_[2].out()), static_cast<uint32_t>(l3.head));
  EXPECT_EQ(static_cast<uint32_t>(inst_[3].out()), 100u);
}

// Test Patch on empty list does nothing (no crash)
TEST_F(PatchListTest_287, PatchEmptyListNoOp_287) {
  PatchList empty = {0, 0};
  // Should not crash
  PatchList::Patch(inst_, empty, 42);
}

// Test Append preserves head of l1 and tail of l2
TEST_F(PatchListTest_287, AppendPreservesHeadAndTail_287) {
  inst_[5].InitAlt(0, 0);
  inst_[10].InitAlt(0, 0);

  PatchList l1 = {10, 10};  // even tail, inst_[5]
  PatchList l2 = {20, 20};  // even tail, inst_[10]

  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, 10u);
  EXPECT_EQ(result.tail, 20u);
}

}  // namespace re2
