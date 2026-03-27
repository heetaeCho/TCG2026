// File: parse_lookup_perl_group_test.cc

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

// Include the definitions for UGroup table symbols.
// (Only public symbols are referenced; no private state is touched.)
#include "re2/unicode_groups.h"

// IMPORTANT: LookupPerlGroup is 'static' in parse.cc. To test it, we include
// the implementation file in this test translation unit. Ensure your build
// does NOT also link a separate object for parse.cc to avoid ODR/link errors.
#include "re2/parse.cc"

namespace re2 {

class LookupPerlGroupTest_523 : public ::testing::Test {};

// --- Normal operation: well-known Perl group names ---

TEST_F(LookupPerlGroupTest_523, ReturnsGroupForDigitLowercase_523) {
  const UGroup* g = LookupPerlGroup("d");
  EXPECT_NE(g, nullptr);
}

TEST_F(LookupPerlGroupTest_523, ReturnsGroupForDigitUppercase_523) {
  const UGroup* g = LookupPerlGroup("D");
  EXPECT_NE(g, nullptr);
}

TEST_F(LookupPerlGroupTest_523, ReturnsGroupForWordAndSpaceVariants_523) {
  EXPECT_NE(LookupPerlGroup("w"), nullptr);
  EXPECT_NE(LookupPerlGroup("W"), nullptr);
  EXPECT_NE(LookupPerlGroup("s"), nullptr);
  EXPECT_NE(LookupPerlGroup("S"), nullptr);
}

// --- Boundary / distinction checks ---

TEST_F(LookupPerlGroupTest_523, UppercaseAndLowercaseAreDistinctGroups_523) {
  // Expect different pointers for negated vs non-negated (e.g., 'd' vs 'D').
  const UGroup* lower_d = LookupPerlGroup("d");
  const UGroup* upper_D = LookupPerlGroup("D");
  ASSERT_NE(lower_d, nullptr);
  ASSERT_NE(upper_D, nullptr);
  EXPECT_NE(lower_d, upper_D);

  const UGroup* lower_w = LookupPerlGroup("w");
  const UGroup* upper_W = LookupPerlGroup("W");
  ASSERT_NE(lower_w, nullptr);
  ASSERT_NE(upper_W, nullptr);
  EXPECT_NE(lower_w, upper_W);

  const UGroup* lower_s = LookupPerlGroup("s");
  const UGroup* upper_S = LookupPerlGroup("S");
  ASSERT_NE(lower_s, nullptr);
  ASSERT_NE(upper_S, nullptr);
  EXPECT_NE(lower_s, upper_S);
}

// --- Error / exceptional observable behavior ---

TEST_F(LookupPerlGroupTest_523, ReturnsNullForUnknownName_523) {
  EXPECT_EQ(LookupPerlGroup("q"), nullptr);   // Not a Perl group
  EXPECT_EQ(LookupPerlGroup(""), nullptr);    // Empty name
  EXPECT_EQ(LookupPerlGroup(" d"), nullptr);  // Leading space should not match
  EXPECT_EQ(LookupPerlGroup("dd"), nullptr);  // Extra characters should not match
}

// --- External interaction consistency (observable equivalence) ---

TEST_F(LookupPerlGroupTest_523, MatchesLookupGroupWithPerlTables_523) {
  // This verifies the observable equivalence with the public LookupGroup +
  // the publicly declared perl_groups/num_perl_groups table symbols.
  // It does NOT rely on or reimplement internal logic.
  const char* names[] = {"d", "D", "w", "W", "s", "S", "q", "", " dd"};
  for (const char* n : names) {
    absl::string_view name(n);
    const UGroup* via_helper = LookupPerlGroup(name);
    const UGroup* via_generic = LookupGroup(name, perl_groups, num_perl_groups);
    EXPECT_EQ(via_helper, via_generic) << "Mismatch for name: '" << name << "'";
  }
}

}  // namespace re2
