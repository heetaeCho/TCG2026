// File: compiler_star_test.cc

#include <gtest/gtest.h>

#include "re2/compile.h"   // or the appropriate header that declares re2::Compiler, Frag, PatchList
                           // If there's no single header, include the specific ones used in your build.

namespace re2 {

class CompilerStarTest_295 : public ::testing::Test {
protected:
  // Helper to build a simple Frag with chosen fields.
  static Frag MakeFrag(uint32_t begin, PatchList end, bool nullable) {
    return Frag(begin, end, nullable);
  }
};

// ===============
// Nullable branch:
// ===============

TEST_F(CompilerStarTest_295, Nullable_DelegatesToPlusThenQuest_GreedyFalse_295) {
  Compiler c;

  // Prepare an input Frag that is already nullable so Star should return Quest(Plus(a), ...).
  Frag a = MakeFrag(/*begin=*/123, PatchList::Mk(7), /*nullable=*/true);

  // Compute the reference result strictly via the public interface:
  // expected = Quest(Plus(a, /*nongreedy=*/false), /*nongreedy=*/false)
  Frag expected = c.Quest(c.Plus(a, /*nongreedy=*/false), /*nongreedy=*/false);

  // Star should delegate in this case.
  Frag got = c.Star(a, /*nongreedy=*/false);

  // Compare observable fields.
  EXPECT_EQ(got.begin, expected.begin);
  EXPECT_EQ(got.end.head, expected.end.head);
  EXPECT_EQ(got.end.tail, expected.end.tail);
  EXPECT_EQ(got.nullable, expected.nullable);
}

TEST_F(CompilerStarTest_295, Nullable_DelegatesToPlusThenQuest_NonGreedyTrue_295) {
  Compiler c;

  Frag a = MakeFrag(/*begin=*/456, PatchList::Mk(3), /*nullable=*/true);

  Frag expected = c.Quest(c.Plus(a, /*nongreedy=*/true), /*nongreedy=*/true);
  Frag got = c.Star(a, /*nongreedy=*/true);

  EXPECT_EQ(got.begin, expected.begin);
  EXPECT_EQ(got.end.head, expected.end.head);
  EXPECT_EQ(got.end.tail, expected.end.tail);
  EXPECT_EQ(got.nullable, expected.nullable);
}

// =====================
// Non-nullable branches
// =====================
//
// For non-nullable input, Star allocates a new instruction (id), sets an Alt,
// patches a.end to id, and returns Frag(id, Mk( ... ), true).
//
// We cannot (and do not) inspect internal instruction state.
// However, the returned Frag.begin is that allocated id, and Star constructs the
// PatchList end using that id and the nongreedy flag:
//
//   nongreedy == false -> end = PatchList::Mk( (id << 1) | 1 )
//   nongreedy == true  -> end = PatchList::Mk( (id << 1) )
//
// Therefore, we can validate the returned PatchList using only returned.begin.

TEST_F(CompilerStarTest_295, NonNullable_GreedyFalse_EndPatchListMatchesFormula_295) {
  Compiler c;

  Frag a = MakeFrag(/*begin=*/10, PatchList::Mk(5), /*nullable=*/false);

  // nongreedy=false (i.e., greedy)
  Frag got = c.Star(a, /*nongreedy=*/false);

  // Star must return a nullable fragment.
  EXPECT_TRUE(got.nullable);

  // The end patchlist must be Mk((begin<<1)|1) where begin == allocated id.
  PatchList expected_pl = PatchList::Mk((got.begin << 1) | 1);
  EXPECT_EQ(got.end.head, expected_pl.head);
  EXPECT_EQ(got.end.tail, expected_pl.tail);
}

TEST_F(CompilerStarTest_295, NonNullable_NonGreedyTrue_EndPatchListMatchesFormula_295) {
  Compiler c;

  Frag a = MakeFrag(/*begin=*/77, PatchList::Mk(11), /*nullable=*/false);

  // nongreedy=true
  Frag got = c.Star(a, /*nongreedy=*/true);

  EXPECT_TRUE(got.nullable);

  // The end patchlist must be Mk((begin<<1)) where begin == allocated id.
  PatchList expected_pl = PatchList::Mk((got.begin << 1));
  EXPECT_EQ(got.end.head, expected_pl.head);
  EXPECT_EQ(got.end.tail, expected_pl.tail);
}

}  // namespace re2
