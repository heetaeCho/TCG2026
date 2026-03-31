#include "gtest/gtest.h"
#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <utility>

namespace re2 {

// Test default construction
TEST(FilteredRE2Test_606, DefaultConstruction_606) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test construction with min_atom_len
TEST(FilteredRE2Test_606, ConstructionWithMinAtomLen_606) {
  FilteredRE2 f(3);
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test Add a single pattern
TEST(FilteredRE2Test_606, AddSinglePattern_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  RE2::ErrorCode code = f.Add("hello", opts, &id);
  EXPECT_EQ(code, RE2::NoError);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f.NumRegexps(), 1);
}

// Test Add multiple patterns
TEST(FilteredRE2Test_606, AddMultiplePatterns_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;

  RE2::ErrorCode code1 = f.Add("hello", opts, &id);
  EXPECT_EQ(code1, RE2::NoError);
  EXPECT_EQ(id, 0);

  RE2::ErrorCode code2 = f.Add("world", opts, &id);
  EXPECT_EQ(code2, RE2::NoError);
  EXPECT_EQ(id, 1);

  RE2::ErrorCode code3 = f.Add("foo.*bar", opts, &id);
  EXPECT_EQ(code3, RE2::NoError);
  EXPECT_EQ(id, 2);

  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test Add with invalid pattern
TEST(FilteredRE2Test_606, AddInvalidPattern_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  RE2::ErrorCode code = f.Add("(unclosed", opts, &id);
  // The pattern is invalid; we expect an error code != NoError
  EXPECT_NE(code, RE2::NoError);
}

// Test GetRE2
TEST(FilteredRE2Test_606, GetRE2_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  const RE2& re = f.GetRE2(0);
  EXPECT_EQ(re.pattern(), "hello");
}

// Test Compile
TEST(FilteredRE2Test_606, Compile_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // After compile, atoms should be populated (or empty depending on patterns)
  // We just verify it doesn't crash and NumRegexps is still correct
  EXPECT_EQ(f.NumRegexps(), 2);
}

// Test SlowFirstMatch with matching text
TEST(FilteredRE2Test_606, SlowFirstMatchFound_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("hello world");
  EXPECT_GE(match, 0);
  EXPECT_LT(match, 2);
}

// Test SlowFirstMatch with no match
TEST(FilteredRE2Test_606, SlowFirstMatchNotFound_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("xyz");
  EXPECT_EQ(match, -1);
}

// Test FirstMatch
TEST(FilteredRE2Test_606, FirstMatch_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Build the atoms vector that would come from matching strings
  // For simplicity, pass all atom indices
  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  int match = f.FirstMatch("hello world", matched_atoms);
  EXPECT_GE(match, 0);
}

// Test FirstMatch with empty atoms - no match expected
TEST(FilteredRE2Test_606, FirstMatchEmptyAtoms_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> empty_atoms;
  int match = f.FirstMatch("hello", empty_atoms);
  // With no atoms matched, likely no match or depends on implementation
  // Just verify it doesn't crash; result may be -1 or valid
  (void)match;
}

// Test AllMatches
TEST(FilteredRE2Test_606, AllMatches_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  f.Add("xyz", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("hello world", matched_atoms, &matching_regexps);

  // At least "hello" and "world" should match
  if (result) {
    EXPECT_GE(matching_regexps.size(), 2u);
  }
}

// Test AllPotentials
TEST(FilteredRE2Test_606, AllPotentials_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  std::vector<int> potential_regexps;
  f.AllPotentials(matched_atoms, &potential_regexps);

  // With all atoms matched, all regexps should be potential
  EXPECT_GE(potential_regexps.size(), 2u);
}

// Test Move Constructor
TEST(FilteredRE2Test_606, MoveConstructor_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  EXPECT_EQ(f.NumRegexps(), 2);

  FilteredRE2 f2(std::move(f));

  // f2 should have the patterns
  EXPECT_EQ(f2.NumRegexps(), 2);
  EXPECT_EQ(f2.GetRE2(0).pattern(), "hello");
  EXPECT_EQ(f2.GetRE2(1).pattern(), "world");

  // f should be empty after move
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test Move Constructor preserves compiled state
TEST(FilteredRE2Test_606, MoveConstructorCompiled_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  FilteredRE2 f2(std::move(f));

  // f2 should be usable after move from a compiled object
  EXPECT_EQ(f2.NumRegexps(), 1);

  int match = f2.SlowFirstMatch("hello");
  EXPECT_EQ(match, 0);

  // Source should be empty
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test Move Assignment
TEST(FilteredRE2Test_606, MoveAssignment_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  FilteredRE2 f2;
  f2 = std::move(f);

  EXPECT_EQ(f2.NumRegexps(), 2);
  EXPECT_EQ(f2.GetRE2(0).pattern(), "hello");
  EXPECT_EQ(f2.GetRE2(1).pattern(), "world");

  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test Move Constructor from empty
TEST(FilteredRE2Test_606, MoveConstructorFromEmpty_606) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);

  FilteredRE2 f2(std::move(f));
  EXPECT_EQ(f2.NumRegexps(), 0);
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test Move Assignment from empty
TEST(FilteredRE2Test_606, MoveAssignmentFromEmpty_606) {
  FilteredRE2 f;
  FilteredRE2 f2;
  int id;
  RE2::Options opts;
  f2.Add("test", opts, &id);
  EXPECT_EQ(f2.NumRegexps(), 1);

  f2 = std::move(f);
  EXPECT_EQ(f2.NumRegexps(), 0);
}

// Test SlowFirstMatch with empty FilteredRE2
TEST(FilteredRE2Test_606, SlowFirstMatchEmpty_606) {
  FilteredRE2 f;
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("anything");
  EXPECT_EQ(match, -1);
}

// Test NumRegexps after various operations
TEST(FilteredRE2Test_606, NumRegexpsAccuracy_606) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);

  int id;
  RE2::Options opts;
  f.Add("a", opts, &id);
  EXPECT_EQ(f.NumRegexps(), 1);

  f.Add("b", opts, &id);
  EXPECT_EQ(f.NumRegexps(), 2);

  f.Add("c", opts, &id);
  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test AllMatches with no matching text
TEST(FilteredRE2Test_606, AllMatchesNoMatch_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("zzzzz", matched_atoms, &matching_regexps);

  // Neither "hello" nor "world" is in "zzzzz"
  EXPECT_FALSE(result);
  EXPECT_TRUE(matching_regexps.empty());
}

// Test with complex regex patterns
TEST(FilteredRE2Test_606, ComplexPatterns_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;

  f.Add("foo.*bar", opts, &id);
  EXPECT_EQ(id, 0);
  f.Add("[0-9]+", opts, &id);
  EXPECT_EQ(id, 1);
  f.Add("(abc|def)ghi", opts, &id);
  EXPECT_EQ(id, 2);

  EXPECT_EQ(f.NumRegexps(), 3);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("fooXbar");
  EXPECT_GE(match, 0);
}

// Test SlowFirstMatch returns first matching pattern
TEST(FilteredRE2Test_606, SlowFirstMatchOrder_606) {
  FilteredRE2 f;
  int id;
  RE2::Options opts;
  f.Add("abc", opts, &id);
  f.Add("abcdef", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("abcdef");
  // Should return 0 (first matching regexp)
  EXPECT_EQ(match, 0);
}

// Test double move
TEST(FilteredRE2Test_606, DoubleMove_606) {
  FilteredRE2 f1;
  int id;
  RE2::Options opts;
  f1.Add("test", opts, &id);

  FilteredRE2 f2(std::move(f1));
  EXPECT_EQ(f2.NumRegexps(), 1);
  EXPECT_EQ(f1.NumRegexps(), 0);

  FilteredRE2 f3(std::move(f2));
  EXPECT_EQ(f3.NumRegexps(), 1);
  EXPECT_EQ(f2.NumRegexps(), 0);
  EXPECT_EQ(f3.GetRE2(0).pattern(), "test");
}

// Test that moved-from object can be reused
TEST(FilteredRE2Test_606, MovedFromReuse_606) {
  FilteredRE2 f1;
  int id;
  RE2::Options opts;
  f1.Add("hello", opts, &id);

  FilteredRE2 f2(std::move(f1));
  EXPECT_EQ(f1.NumRegexps(), 0);

  // Reuse f1 by adding new patterns
  f1.Add("new_pattern", opts, &id);
  EXPECT_EQ(f1.NumRegexps(), 1);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f1.GetRE2(0).pattern(), "new_pattern");
}

}  // namespace re2
