// File: charclassbuilder_addcharclass_test.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::CharClassBuilder;

// Small helpers that only use public interface (black-box)
static void ExpectContainsAll(CharClassBuilder* ccb, std::initializer_list<int> runes) {
  for (int r : runes) {
    EXPECT_TRUE(ccb->Contains(r)) << "Expected to contain rune " << r;
  }
}

static void ExpectContainsNone(CharClassBuilder* ccb, std::initializer_list<int> runes) {
  for (int r : runes) {
    EXPECT_FALSE(ccb->Contains(r)) << "Expected NOT to contain rune " << r;
  }
}

class CharClassBuilderAddCharClassTest_371 : public ::testing::Test {
protected:
  // Helper to create a class with given closed intervals [lo, hi]
  static CharClassBuilder MakeWithRanges(std::initializer_list<std::pair<int,int>> ranges) {
    CharClassBuilder ccb;
    for (auto& p : ranges) {
      // Do not infer internal validation; just call the API
      (void)ccb.AddRange(p.first, p.second);
    }
    return ccb;
  }
};

// Normal case: copies disjoint ranges from source into empty destination.
TEST_F(CharClassBuilderAddCharClassTest_371, CopiesDisjointRangesIntoEmpty_371) {
  CharClassBuilder dst;  // empty
  CharClassBuilder src = MakeWithRanges({{10,12}, {20,21}});

  dst.AddCharClass(&src);

  ExpectContainsAll(&dst, {10,11,12,20,21});
  // A few outside probes to confirm no unintended additions
  ExpectContainsNone(&dst, {9,13,19,22});
}

// Ensures existing destination ranges are preserved while adding from source.
TEST_F(CharClassBuilderAddCharClassTest_371, PreservesExistingWhileAdding_371) {
  CharClassBuilder dst = MakeWithRanges({{100,100}});
  CharClassBuilder src = MakeWithRanges({{200,200}});

  dst.AddCharClass(&src);

  ExpectContainsAll(&dst, {100,200});
  ExpectContainsNone(&dst, {99,101,199,201});
}

// Boundary behavior: endpoints are included (closed intervals).
TEST_F(CharClassBuilderAddCharClassTest_371, BoundariesAreInclusive_371) {
  CharClassBuilder dst;
  CharClassBuilder src = MakeWithRanges({{50,50}});  // single-point range

  dst.AddCharClass(&src);

  ExpectContainsAll(&dst, {50});
  ExpectContainsNone(&dst, {49,51});
}

// Overlapping and adjacent ranges in source still yield containment across the covered span.
// (We do NOT assert on internal range merging; only on Contains behavior.)
TEST_F(CharClassBuilderAddCharClassTest_371, OverlappingAndAdjacentSourceRanges_371) {
  CharClassBuilder dst;  // empty
  // Overlap: [5,10] and [8,15]; Adjacent: [15,16] via [16,16]
  CharClassBuilder src = MakeWithRanges({{5,10}, {8,15}, {16,16}});

  dst.AddCharClass(&src);

  // Everything in the combined coverage should be contained
  ExpectContainsAll(&dst, {5,6,7,8,9,10,11,12,13,14,15,16});
  // Outside probes
  ExpectContainsNone(&dst, {4,17});
}

// Edge case: empty source should not change destination.
TEST_F(CharClassBuilderAddCharClassTest_371, EmptySourceNoChange_371) {
  CharClassBuilder dst = MakeWithRanges({{1,1}});
  CharClassBuilder empty_src;  // no ranges

  dst.AddCharClass(&empty_src);

  ExpectContainsAll(&dst, {1});
  ExpectContainsNone(&dst, {0,2});
}
