// File: charclass_contains_test_379.cc
#include <gtest/gtest.h>

// Assume the project headers are available at these paths per prompt.
#include "re2/regexp.h"

namespace re2 {

class CharClassContainsTest_379 : public ::testing::Test {
protected:
  // Helper to allocate and return a fresh CharClass with capacity for `n` ranges.
  // Per provided interface, we use the factory and Delete() for lifecycle.
  CharClass* MakeWithCapacity(size_t n) {
    // Using the provided (qualified) factory per header snippet.
    // Treat as black box: we only rely on its signature/availability.
    return CharClass::New(n);
  }

  // RAII guard to ensure Delete() is called even on failures.
  struct Holder {
    CharClass* cls{nullptr};
    ~Holder() { if (cls) cls->Delete(); }
  };
};

// --- Normal operation ---

// Single closed interval range: hits at lo, mid, hi.
TEST_F(CharClassContainsTest_379, SingleRange_HitsAtBoundsAndMiddle_379) {
  Holder h;
  h.cls = MakeWithCapacity(1);
  ASSERT_NE(h.cls, nullptr);

  // Fill the single range via non-const iterator interface.
  // We do not assume any internal invariants other than: iterators exist and
  // we can assign a RuneRange (lo, hi).
  auto it = h.cls->begin();
  ASSERT_NE(it, h.cls->end());  // capacity is 1
  *it = RuneRange(10, 20);

  // Observable behavior: Contains reports membership inside [10,20].
  EXPECT_TRUE(h.cls->Contains(10));   // lo
  EXPECT_TRUE(h.cls->Contains(15));   // middle
  EXPECT_TRUE(h.cls->Contains(20));   // hi

  // Outside the range should be false.
  EXPECT_FALSE(h.cls->Contains(9));
  EXPECT_FALSE(h.cls->Contains(21));
}

// Multiple disjoint, sorted ranges: membership in any should be true.
TEST_F(CharClassContainsTest_379, MultipleDisjointRanges_ContainmentAcrossAll_379) {
  Holder h;
  h.cls = MakeWithCapacity(3);
  ASSERT_NE(h.cls, nullptr);

  // Provide three disjoint, sorted ranges.
  auto it = h.cls->begin();
  ASSERT_NE(it, h.cls->end());
  *it++ = RuneRange(1, 3);     // [1,3]
  ASSERT_NE(it, h.cls->end());
  *it++ = RuneRange(10, 10);   // [10,10]
  ASSERT_NE(it, h.cls->end());
  *it++ = RuneRange(100, 200); // [100,200]

  // Inside any of the ranges -> true
  EXPECT_TRUE(h.cls->Contains(1));
  EXPECT_TRUE(h.cls->Contains(3));
  EXPECT_TRUE(h.cls->Contains(10));
  EXPECT_TRUE(h.cls->Contains(150));
  EXPECT_TRUE(h.cls->Contains(200));

  // Between the ranges -> false
  EXPECT_FALSE(h.cls->Contains(0));
  EXPECT_FALSE(h.cls->Contains(4));
  EXPECT_FALSE(h.cls->Contains(9));
  EXPECT_FALSE(h.cls->Contains(11));
  EXPECT_FALSE(h.cls->Contains(99));
  EXPECT_FALSE(h.cls->Contains(201));
}

// --- Boundary conditions ---

// No ranges at all: Contains must always be false.
TEST_F(CharClassContainsTest_379, EmptyClass_NoRanges_AlwaysFalse_379) {
  Holder h;
  h.cls = MakeWithCapacity(0);
  ASSERT_NE(h.cls, nullptr);

  // With no ranges to populate, Contains should return false for any input.
  EXPECT_FALSE(h.cls->Contains(0));
  EXPECT_FALSE(h.cls->Contains(1234));
  EXPECT_FALSE(h.cls->Contains(-1));
}

// Adjacent (touching) ranges should cover their endpoints correctly.
TEST_F(CharClassContainsTest_379, AdjacentRanges_CoverageAtTouchingEndpoints_379) {
  Holder h;
  h.cls = MakeWithCapacity(2);
  ASSERT_NE(h.cls, nullptr);

  auto it = h.cls->begin();
  *it++ = RuneRange(5, 5);   // singleton [5,5]
  *it++ = RuneRange(6, 10);  // adjacent [6,10]

  EXPECT_TRUE(h.cls->Contains(5));   // in first
  EXPECT_TRUE(h.cls->Contains(6));   // in second, boundary
  EXPECT_TRUE(h.cls->Contains(10));  // end of second

  EXPECT_FALSE(h.cls->Contains(4));
  EXPECT_FALSE(h.cls->Contains(11));
}

// Negative and high rune values at boundaries (int domain usage).
TEST_F(CharClassContainsTest_379, NegativeAndHighValues_WithinAndOutside_379) {
  Holder h;
  h.cls = MakeWithCapacity(2);
  ASSERT_NE(h.cls, nullptr);

  auto it = h.cls->begin();
  *it++ = RuneRange(-100, -50); // negative span
  *it++ = RuneRange(100000, 100100); // large positive span

  // Inside negative range
  EXPECT_TRUE(h.cls->Contains(-100));
  EXPECT_TRUE(h.cls->Contains(-75));
  EXPECT_TRUE(h.cls->Contains(-50));

  // Inside large positive range
  EXPECT_TRUE(h.cls->Contains(100000));
  EXPECT_TRUE(h.cls->Contains(100050));
  EXPECT_TRUE(h.cls->Contains(100100));

  // Outside both
  EXPECT_FALSE(h.cls->Contains(-101));
  EXPECT_FALSE(h.cls->Contains(-49));
  EXPECT_FALSE(h.cls->Contains(99999));
  EXPECT_FALSE(h.cls->Contains(100101));
}

// --- Edge-ordering / search behavior ---

// Values strictly between ranges should be false even when ranges are far apart.
TEST_F(CharClassContainsTest_379, GapsBetweenRanges_ReturnFalse_379) {
  Holder h;
  h.cls = MakeWithCapacity(2);
  ASSERT_NE(h.cls, nullptr);

  auto it = h.cls->begin();
  *it++ = RuneRange(0, 0);       // [0,0]
  *it++ = RuneRange(1000, 1000); // [1000,1000]

  EXPECT_TRUE(h.cls->Contains(0));
  EXPECT_TRUE(h.cls->Contains(1000));
  EXPECT_FALSE(h.cls->Contains(1));
  EXPECT_FALSE(h.cls->Contains(999));
}

// Overlapping ranges (if provided) should still report true when covered.
TEST_F(CharClassContainsTest_379, OverlappingRanges_StillContain_379) {
  Holder h;
  h.cls = MakeWithCapacity(2);
  ASSERT_NE(h.cls, nullptr);

  auto it = h.cls->begin();
  *it++ = RuneRange(10, 20);
  *it++ = RuneRange(15, 25); // overlap

  EXPECT_TRUE(h.cls->Contains(10));
  EXPECT_TRUE(h.cls->Contains(15)); // in overlap
  EXPECT_TRUE(h.cls->Contains(20));
  EXPECT_TRUE(h.cls->Contains(25));

  EXPECT_FALSE(h.cls->Contains(9));
  EXPECT_FALSE(h.cls->Contains(26));
}

} // namespace re2
