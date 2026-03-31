#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

// We need access to PatchList which is defined in compile.cc
// Since PatchList is internal to compile.cc, we need to test it indirectly
// or include the necessary headers. Let's test through the public RE2/Prog interface
// and also try to access PatchList directly.

// Since PatchList is defined in compile.cc and not exposed in a header,
// we'll test the observable behavior through compilation of regexps,
// which exercises PatchList::Patch, PatchList::Mk, and PatchList::Append internally.

namespace re2 {

// Forward declare PatchList from compile.cc
// We need to replicate the struct definition to test it
struct PatchList {
  uint32_t head;
  uint32_t tail;
  static PatchList Mk(uint32_t p);
  static void Patch(Prog::Inst* inst0, PatchList l, uint32_t p);
  static PatchList Append(Prog::Inst* inst0, PatchList l1, PatchList l2);
};

class PatchListTest_286 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Allocate a small array of instructions for testing
    memset(inst_, 0, sizeof(inst_));
  }

  Prog::Inst inst_[64];
};

// Test that Mk creates a PatchList with the given value as head and tail
TEST_F(PatchListTest_286, MkCreatesValidPatchList_286) {
  PatchList pl = PatchList::Mk(2);
  EXPECT_EQ(pl.head, 2u);
  EXPECT_EQ(pl.tail, 2u);
}

// Test Mk with zero
TEST_F(PatchListTest_286, MkWithZeroCreatesEmptyList_286) {
  PatchList pl = PatchList::Mk(0);
  EXPECT_EQ(pl.head, 0u);
  EXPECT_EQ(pl.tail, 0u);
}

// Test Mk with various values
TEST_F(PatchListTest_286, MkWithVariousValues_286) {
  PatchList pl1 = PatchList::Mk(4);
  EXPECT_EQ(pl1.head, 4u);
  EXPECT_EQ(pl1.tail, 4u);

  PatchList pl2 = PatchList::Mk(10);
  EXPECT_EQ(pl2.head, 10u);
  EXPECT_EQ(pl2.tail, 10u);
}

// Test Patch with an empty PatchList (head == 0) does nothing
TEST_F(PatchListTest_286, PatchEmptyListDoesNothing_286) {
  inst_[0].InitNop(0);
  PatchList empty;
  empty.head = 0;
  empty.tail = 0;
  // Should not crash or modify anything
  PatchList::Patch(inst_, empty, 5);
  // Verify instruction is unchanged
  EXPECT_EQ(inst_[0].out(), 0);
}

// Test Patch with a single element list using out (even head)
TEST_F(PatchListTest_286, PatchSingleElementOut_286) {
  // head value with bit 0 = 0 means we patch out()
  // head>>1 gives index, so head=2 => index=1
  inst_[1].InitNop(0);  // out = 0 initially
  PatchList pl = PatchList::Mk(2);  // head=2, index=1, even => patch out
  PatchList::Patch(inst_, pl, 42);
  EXPECT_EQ(inst_[1].out(), 42);
}

// Test Patch with a single element list using out1 (odd head)
TEST_F(PatchListTest_286, PatchSingleElementOut1_286) {
  // head value with bit 0 = 1 means we patch out1_
  // head=3 => index=1, odd => patch out1_
  inst_[1].InitAlt(0, 0);  // out=0, out1=0
  PatchList pl = PatchList::Mk(3);  // head=3, index=1, odd => patch out1
  PatchList::Patch(inst_, pl, 99);
  EXPECT_EQ(inst_[1].out1(), 99);
}

// Test Patch chains through multiple instructions via out
TEST_F(PatchListTest_286, PatchMultipleElementsViaOut_286) {
  // Create a chain: inst[1].out -> inst[2] -> 0 (end)
  // head=2 (index 1, even=out), inst[1].out should point to next in chain
  inst_[1].InitNop(4);   // out=4 => next head=4 (index 2, even=out)
  inst_[2].InitNop(0);   // out=0 => end of chain

  PatchList pl;
  pl.head = 2;
  pl.tail = 4;
  PatchList::Patch(inst_, pl, 77);
  EXPECT_EQ(inst_[1].out(), 77);
  EXPECT_EQ(inst_[2].out(), 77);
}

// Test Patch chains through mixed out and out1
TEST_F(PatchListTest_286, PatchMixedOutAndOut1_286) {
  // Chain: head=2 (index 1, even=out) -> 5 (index 2, odd=out1) -> 0 (end)
  inst_[1].InitNop(5);       // out=5 => next head=5 (index 2, odd=out1)
  inst_[2].InitAlt(0, 0);    // out1=0 => end of chain

  PatchList pl;
  pl.head = 2;
  pl.tail = 5;
  PatchList::Patch(inst_, pl, 33);
  EXPECT_EQ(inst_[1].out(), 33);
  EXPECT_EQ(inst_[2].out1(), 33);
}

// Test Append of two empty lists
TEST_F(PatchListTest_286, AppendTwoEmptyLists_286) {
  PatchList l1 = {0, 0};
  PatchList l2 = {0, 0};
  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, 0u);
}

// Test Append with first list empty
TEST_F(PatchListTest_286, AppendFirstEmpty_286) {
  PatchList l1 = {0, 0};
  PatchList l2 = PatchList::Mk(4);
  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, l2.head);
  EXPECT_EQ(result.tail, l2.tail);
}

// Test Append with second list empty
TEST_F(PatchListTest_286, AppendSecondEmpty_286) {
  PatchList l1 = PatchList::Mk(2);
  inst_[1].InitNop(0);  // out=0 for the patch entry at index 1
  PatchList l2 = {0, 0};
  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, l1.head);
  EXPECT_EQ(result.tail, l1.tail);
}

// Test Append of two non-empty lists
TEST_F(PatchListTest_286, AppendTwoNonEmptyLists_286) {
  // l1: head=2 (index 1), tail=2 (index 1)
  // l2: head=4 (index 2), tail=4 (index 2)
  inst_[1].InitNop(0);  // out=0
  inst_[2].InitNop(0);  // out=0

  PatchList l1 = PatchList::Mk(2);
  PatchList l2 = PatchList::Mk(4);

  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, 2u);
  EXPECT_EQ(result.tail, 4u);

  // Now patch the combined list
  PatchList::Patch(inst_, result, 55);
  EXPECT_EQ(inst_[1].out(), 55);
  EXPECT_EQ(inst_[2].out(), 55);
}

// Test Append chains correctly through out1
TEST_F(PatchListTest_286, AppendChainsViaOut1_286) {
  // l1: head=3 (index 1, odd=out1), tail=3
  // l2: head=5 (index 2, odd=out1), tail=5
  inst_[1].InitAlt(0, 0);
  inst_[2].InitAlt(0, 0);

  PatchList l1 = PatchList::Mk(3);
  PatchList l2 = PatchList::Mk(5);

  PatchList result = PatchList::Append(inst_, l1, l2);
  EXPECT_EQ(result.head, 3u);
  EXPECT_EQ(result.tail, 5u);

  PatchList::Patch(inst_, result, 88);
  EXPECT_EQ(inst_[1].out1(), 88);
  EXPECT_EQ(inst_[2].out1(), 88);
}

// Integration test: compile a simple regex and verify program is created
TEST_F(PatchListTest_286, IntegrationSimpleRegex_286) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
}

// Integration test: compile alternation regex
TEST_F(PatchListTest_286, IntegrationAlternation_286) {
  RE2 re("a|b|c");
  EXPECT_TRUE(re.ok());
}

// Integration test: compile complex regex with captures
TEST_F(PatchListTest_286, IntegrationCaptures_286) {
  RE2 re("(a+)(b*)c");
  EXPECT_TRUE(re.ok());
}

// Integration test: compile regex with repetition
TEST_F(PatchListTest_286, IntegrationRepetition_286) {
  RE2 re("a*b+c?d{2,5}");
  EXPECT_TRUE(re.ok());
}

// Integration test: compile character class
TEST_F(PatchListTest_286, IntegrationCharClass_286) {
  RE2 re("[a-zA-Z0-9]+");
  EXPECT_TRUE(re.ok());
}

// Test Patch with large target value
TEST_F(PatchListTest_286, PatchWithLargeTarget_286) {
  inst_[1].InitNop(0);
  PatchList pl = PatchList::Mk(2);
  uint32_t large_val = 1000000;
  PatchList::Patch(inst_, pl, large_val);
  EXPECT_EQ(static_cast<uint32_t>(inst_[1].out()), large_val);
}

// Test multiple appends creating a longer chain
TEST_F(PatchListTest_286, MultipleAppends_286) {
  inst_[1].InitNop(0);
  inst_[2].InitNop(0);
  inst_[3].InitNop(0);

  PatchList l1 = PatchList::Mk(2);  // index 1
  PatchList l2 = PatchList::Mk(4);  // index 2
  PatchList l3 = PatchList::Mk(6);  // index 3

  PatchList combined = PatchList::Append(inst_, l1, l2);
  combined = PatchList::Append(inst_, combined, l3);

  EXPECT_EQ(combined.head, 2u);
  EXPECT_EQ(combined.tail, 6u);

  PatchList::Patch(inst_, combined, 123);
  EXPECT_EQ(inst_[1].out(), 123);
  EXPECT_EQ(inst_[2].out(), 123);
  EXPECT_EQ(inst_[3].out(), 123);
}

}  // namespace re2
