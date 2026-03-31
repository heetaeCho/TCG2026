#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/compile.cc"

namespace re2 {

// Test that Mk creates a PatchList with both head and tail set to the given value
TEST(PatchListTest_285, MkSetsHeadAndTail_285) {
  PatchList pl = PatchList::Mk(42);
  EXPECT_EQ(pl.head, 42u);
  EXPECT_EQ(pl.tail, 42u);
}

// Test Mk with zero value
TEST(PatchListTest_285, MkWithZero_285) {
  PatchList pl = PatchList::Mk(0);
  EXPECT_EQ(pl.head, 0u);
  EXPECT_EQ(pl.tail, 0u);
}

// Test Mk with maximum uint32_t value
TEST(PatchListTest_285, MkWithMaxUint32_285) {
  PatchList pl = PatchList::Mk(0xFFFFFFFF);
  EXPECT_EQ(pl.head, 0xFFFFFFFF);
  EXPECT_EQ(pl.tail, 0xFFFFFFFF);
}

// Test Mk with value 1
TEST(PatchListTest_285, MkWithOne_285) {
  PatchList pl = PatchList::Mk(1);
  EXPECT_EQ(pl.head, 1u);
  EXPECT_EQ(pl.tail, 1u);
}

// Test Mk with a large value
TEST(PatchListTest_285, MkWithLargeValue_285) {
  PatchList pl = PatchList::Mk(1000000);
  EXPECT_EQ(pl.head, 1000000u);
  EXPECT_EQ(pl.tail, 1000000u);
}

// Test that head and tail are equal after Mk
TEST(PatchListTest_285, MkHeadEqualsTail_285) {
  for (uint32_t v : {0u, 1u, 100u, 65535u, 0x80000000u, 0xFFFFFFFFu}) {
    PatchList pl = PatchList::Mk(v);
    EXPECT_EQ(pl.head, pl.tail);
  }
}

// Test that two separate Mk calls produce independent PatchLists
TEST(PatchListTest_285, MkProducesIndependentInstances_285) {
  PatchList pl1 = PatchList::Mk(10);
  PatchList pl2 = PatchList::Mk(20);
  EXPECT_EQ(pl1.head, 10u);
  EXPECT_EQ(pl1.tail, 10u);
  EXPECT_EQ(pl2.head, 20u);
  EXPECT_EQ(pl2.tail, 20u);
}

// Test Mk with power of 2 boundary values
TEST(PatchListTest_285, MkWithPowerOfTwoBoundaries_285) {
  PatchList pl = PatchList::Mk(0x80000000);
  EXPECT_EQ(pl.head, 0x80000000u);
  EXPECT_EQ(pl.tail, 0x80000000u);
}

}  // namespace re2
