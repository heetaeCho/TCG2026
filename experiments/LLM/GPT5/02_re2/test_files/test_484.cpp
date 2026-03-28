// File: lookup_casefold_test.cc
#include <gtest/gtest.h>
#include <cstdint>

namespace re2 {

// Minimal public-facing declarations needed by the interface under test.
// (We are NOT re-implementing logic; just providing the types used by the function.)
using Rune = int;

struct CaseFold {
  // Public fields used by the function (observable via the interface).
  // Only the presence and ordering of these fields matters for constructing inputs.
  Rune lo;
  Rune hi;
  int32_t delta;  // Unused by LookupCaseFold but part of the known struct.
};

// Function under test (defined in the production source).
const CaseFold* LookupCaseFold(const CaseFold* f, int n, Rune r);

}  // namespace re2

using re2::CaseFold;
using re2::LookupCaseFold;
using re2::Rune;

class LookupCaseFoldTest_484 : public ::testing::Test {
protected:
  // Helper to build a small, sorted table of disjoint ranges.
  // Ranges: [1,3], [5,5], [10,12], [20,25]
  static void BuildTable(std::vector<CaseFold>& out) {
    out = {
      {1, 3, 0},
      {5, 5, 0},
      {10, 12, 0},
      {20, 25, 0},
    };
  }
};

// Normal hit in the middle of a range.
TEST_F(LookupCaseFoldTest_484, ReturnsPointerWhenRuneInsideRange_484) {
  std::vector<CaseFold> tbl;
  BuildTable(tbl);

  const CaseFold* p = LookupCaseFold(tbl.data(), static_cast<int>(tbl.size()), /*r=*/11);
  ASSERT_NE(p, nullptr);
  // The observable contract (based on interface use) is that it returns a pointer
  // to the matching range entry when r lies within [lo, hi].
  EXPECT_LE(p->lo, 11);
  EXPECT_GE(p->hi, 11);
}

// Boundary: r exactly equals lo of an entry.
TEST_F(LookupCaseFoldTest_484, ReturnsPointerWhenRuneEqualsLo_484) {
  std::vector<CaseFold> tbl;
  BuildTable(tbl);

  const CaseFold* p = LookupCaseFold(tbl.data(), static_cast<int>(tbl.size()), /*r=*/10);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p->lo, 10);
  EXPECT_EQ(p->hi, 12);
}

// Boundary: r exactly equals hi of an entry.
TEST_F(LookupCaseFoldTest_484, ReturnsPointerWhenRuneEqualsHi_484) {
  std::vector<CaseFold> tbl;
  BuildTable(tbl);

  const CaseFold* p = LookupCaseFold(tbl.data(), static_cast<int>(tbl.size()), /*r=*/3);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p->lo, 1);
  EXPECT_EQ(p->hi, 3);
}

// Miss: r smaller than all ranges -> returns pointer to first entry (insertion point at begin).
TEST_F(LookupCaseFoldTest_484, ReturnsFirstEntryWhenRuneBeforeAllRanges_484) {
  std::vector<CaseFold> tbl;
  BuildTable(tbl);

  const CaseFold* p = LookupCaseFold(tbl.data(), static_cast<int>(tbl.size()), /*r=*/-5);
  ASSERT_NE(p, nullptr);  // Not found, but insertion point is at the beginning.
  EXPECT_EQ(p, &tbl[0]);
  // Confirm r is not within that returned entry.
  EXPECT_FALSE(p->lo <= -5 && -5 <= p->hi);
}

// Miss: r between two ranges -> returns pointer to the first entry whose lo > r (next range).
TEST_F(LookupCaseFoldTest_484, ReturnsNextEntryWhenRuneBetweenRanges_484) {
  std::vector<CaseFold> tbl;
  BuildTable(tbl);

  // Between [5,5] and [10,12]
  const CaseFold* p = LookupCaseFold(tbl.data(), static_cast<int>(tbl.size()), /*r=*/7);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p, &tbl[2]);  // Next higher entry starts at lo=10
  EXPECT_FALSE(p->lo <= 7 && 7 <= p->hi);
}

// Miss: r greater than all ranges -> returns nullptr (no insertion point inside the table).
TEST_F(LookupCaseFoldTest_484, ReturnsNullptrWhenRuneAfterAllRanges_484) {
  std::vector<CaseFold> tbl;
  BuildTable(tbl);

  const CaseFold* p = LookupCaseFold(tbl.data(), static_cast<int>(tbl.size()), /*r=*/100);
  EXPECT_EQ(p, nullptr);
}

// Edge case: empty table -> cannot match; should return nullptr.
TEST_F(LookupCaseFoldTest_484, ReturnsNullptrOnEmptyTable_484) {
  std::vector<CaseFold> tbl;  // empty
  const CaseFold* p = LookupCaseFold(tbl.data(), 0, /*r=*/10);
  EXPECT_EQ(p, nullptr);
}

// Single-entry table: hit case.
TEST_F(LookupCaseFoldTest_484, SingleEntryMatch_484) {
  const CaseFold one[] = { {42, 50, 0} };
  const CaseFold* p = LookupCaseFold(one, 1, /*r=*/45);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p->lo, 42);
  EXPECT_EQ(p->hi, 50);
}

// Single-entry table: miss before -> insertion point at first (non-nullptr).
TEST_F(LookupCaseFoldTest_484, SingleEntryMissBefore_484) {
  const CaseFold one[] = { {42, 50, 0} };
  const CaseFold* p = LookupCaseFold(one, 1, /*r=*/10);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p, &one[0]);
  EXPECT_FALSE(p->lo <= 10 && 10 <= p->hi);
}

// Single-entry table: miss after -> nullptr.
TEST_F(LookupCaseFoldTest_484, SingleEntryMissAfter_484) {
  const CaseFold one[] = { {42, 50, 0} };
  const CaseFold* p = LookupCaseFold(one, 1, /*r=*/99);
  EXPECT_EQ(p, nullptr);
}
