// File: add_folded_range_latin1_test.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

// Pull in the tested static helper into this translation unit.
// This mirrors how RE2 tests often reach static helpers.
#include "re2/parse.cc"  // contains re2::AddFoldedRangeLatin1

namespace re2 {

class AddFoldedRangeLatin1Test_487 : public ::testing::Test {
protected:
  // Utility: verify Contains() for a list of runes.
  static void ExpectContainsAll(CharClassBuilder* cc, const std::string& chars) {
    for (unsigned char ch : chars) {
      EXPECT_TRUE(cc->Contains(static_cast<Rune>(ch)))
          << "Expected class to contain rune '" << ch << "' (" << int(ch) << ")";
    }
  }
  static void ExpectContainsNone(CharClassBuilder* cc, const std::string& chars) {
    for (unsigned char ch : chars) {
      EXPECT_FALSE(cc->Contains(static_cast<Rune>(ch)))
          << "Expected class NOT to contain rune '" << ch << "' (" << int(ch) << ")";
    }
  }
};

// Normal operation: uppercase range folds to include lowercase counterparts.
TEST_F(AddFoldedRangeLatin1Test_487, UppercaseRangeAddsBothCases_487) {
  CharClassBuilder cc;
  // Before: nothing present
  ExpectContainsNone(&cc, "ABCabc");

  AddFoldedRangeLatin1(&cc, 'A', 'C');

  // After: both A..C and a..c must be present
  ExpectContainsAll(&cc, "ABC");
  ExpectContainsAll(&cc, "abc");

  // Characters outside the range remain absent
  ExpectContainsNone(&cc, "Ddef");
}

// Boundary: single lowercase letter folds to include its uppercase.
TEST_F(AddFoldedRangeLatin1Test_487, SingleLowercaseFoldsWithUppercase_487) {
  CharClassBuilder cc;

  AddFoldedRangeLatin1(&cc, 'z', 'z');

  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_TRUE(cc->Contains('Z'));  // folded counterpart
  // Neighboring letters not included
  EXPECT_FALSE(cc->Contains('y'));
  EXPECT_FALSE(cc->Contains('Y'));
}

// Non-letter range: digits do not fold; only themselves are added.
TEST_F(AddFoldedRangeLatin1Test_487, NonLetterRangeAddsOnlyItself_487) {
  CharClassBuilder cc;

  AddFoldedRangeLatin1(&cc, '0', '2');

  ExpectContainsAll(&cc, "012");
  // No extra letters should appear
  ExpectContainsNone(&cc, "AaBb");
}

// Mixed range: punctuation plus letter — punctuation added as-is; letters fold.
TEST_F(AddFoldedRangeLatin1Test_487, MixedRangePunctuationAndLetters_487) {
  CharClassBuilder cc;

  // '/' (47), '0' (48), '1' (49), 'A' (65)
  AddFoldedRangeLatin1(&cc, '/', 'A');

  // Punctuation and digits inside range are added as-is
  ExpectContainsAll(&cc, "/01");
  // 'A' is in range, so both 'A' and 'a' are included via folding
  EXPECT_TRUE(cc->Contains('A'));
  EXPECT_TRUE(cc->Contains('a'));

  // Something just outside range should be absent
  EXPECT_FALSE(cc->Contains('B'));
  EXPECT_FALSE(cc->Contains('b'));
}

// Edge/exceptional case observable via API: empty range (lo > hi) adds nothing.
TEST_F(AddFoldedRangeLatin1Test_487, EmptyRangeNoOpWhenLoGreaterThanHi_487) {
  CharClassBuilder cc;

  // Intentionally reverse-ordered range; loop should not execute.
  AddFoldedRangeLatin1(&cc, 'B', 'A');

  // Spot-check a few characters to confirm no additions occurred.
  ExpectContainsNone(&cc, "AaBb0/");
}

}  // namespace re2
