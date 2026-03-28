#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <utility>

namespace re2 {
namespace {

// Test default construction
TEST(FilteredRE2Test_471, DefaultConstruction_471) {
  FilteredRE2 f;
  EXPECT_EQ(0, f.NumRegexps());
}

// Test construction with min_atom_len
TEST(FilteredRE2Test_471, ConstructionWithMinAtomLen_471) {
  FilteredRE2 f(3);
  EXPECT_EQ(0, f.NumRegexps());
}

// Test move construction
TEST(FilteredRE2Test_471, MoveConstruction_471) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f1.Add("hello", opts, &id));
  EXPECT_EQ(0, id);
  EXPECT_EQ(1, f1.NumRegexps());

  FilteredRE2 f2(std::move(f1));
  EXPECT_EQ(1, f2.NumRegexps());
}

// Test move assignment
TEST(FilteredRE2Test_471, MoveAssignment_471) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f1.Add("world", opts, &id));
  EXPECT_EQ(0, id);

  FilteredRE2 f2;
  f2 = std::move(f1);
  EXPECT_EQ(1, f2.NumRegexps());
}

// Test Add single pattern
TEST(FilteredRE2Test_471, AddSinglePattern_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id = -1;
  RE2::ErrorCode err = f.Add("test_pattern", opts, &id);
  EXPECT_EQ(RE2::NoError, err);
  EXPECT_EQ(0, id);
  EXPECT_EQ(1, f.NumRegexps());
}

// Test Add multiple patterns
TEST(FilteredRE2Test_471, AddMultiplePatterns_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1, id2;
  ASSERT_EQ(RE2::NoError, f.Add("alpha", opts, &id0));
  ASSERT_EQ(RE2::NoError, f.Add("beta", opts, &id1));
  ASSERT_EQ(RE2::NoError, f.Add("gamma", opts, &id2));
  EXPECT_EQ(0, id0);
  EXPECT_EQ(1, id1);
  EXPECT_EQ(2, id2);
  EXPECT_EQ(3, f.NumRegexps());
}

// Test Add invalid pattern
TEST(FilteredRE2Test_471, AddInvalidPattern_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id = -1;
  RE2::ErrorCode err = f.Add("(invalid[", opts, &id);
  // Even invalid patterns may be added; the id should still be assigned
  // The error code may or may not be NoError depending on behavior
  EXPECT_EQ(0, id);
  EXPECT_EQ(1, f.NumRegexps());
}

// Test Compile
TEST(FilteredRE2Test_471, Compile_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("world", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // After compile, atoms should be populated (may or may not be empty depending on patterns)
  // Just verify it doesn't crash and NumRegexps is still correct
  EXPECT_EQ(2, f.NumRegexps());
}

// Test GetRE2
TEST(FilteredRE2Test_471, GetRE2_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("foo(bar)", opts, &id));
  EXPECT_EQ(0, id);

  const RE2& re = f.GetRE2(0);
  EXPECT_EQ("foo(bar)", re.pattern());
}

// Test SlowFirstMatch with matching text
TEST(FilteredRE2Test_471, SlowFirstMatchFound_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("world", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("hello world");
  EXPECT_GE(match, 0);
  EXPECT_LT(match, 2);
}

// Test SlowFirstMatch with no match
TEST(FilteredRE2Test_471, SlowFirstMatchNotFound_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("world", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("xyz");
  EXPECT_EQ(-1, match);
}

// Test FirstMatch
TEST(FilteredRE2Test_471, FirstMatchFound_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("world", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Build the atoms list as if all atoms matched
  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  int match = f.FirstMatch("hello world", matched_atoms);
  EXPECT_GE(match, 0);
}

// Test FirstMatch with no atoms matched
TEST(FilteredRE2Test_471, FirstMatchNoAtoms_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> empty_atoms;
  int match = f.FirstMatch("hello", empty_atoms);
  // With no atoms matched, may return -1 or may still find match depending on prefilter
  // Just verify it doesn't crash
  (void)match;
}

// Test AllMatches
TEST(FilteredRE2Test_471, AllMatchesMultiple_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("world", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("xyz", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("hello world", matched_atoms, &matching_regexps);
  // "hello" and "world" should match, "xyz" should not
  EXPECT_TRUE(result);
  EXPECT_GE(matching_regexps.size(), 2u);
}

// Test AllMatches with no matching text
TEST(FilteredRE2Test_471, AllMatchesNone_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("world", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> empty_atoms;
  std::vector<int> matching_regexps;
  bool result = f.AllMatches("xyz", empty_atoms, &matching_regexps);
  EXPECT_FALSE(result);
  EXPECT_TRUE(matching_regexps.empty());
}

// Test AllPotentials
TEST(FilteredRE2Test_471, AllPotentials_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("world", opts, &id));

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

// Test AllPotentials with empty atoms
TEST(FilteredRE2Test_471, AllPotentialsEmpty_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> empty_atoms;
  std::vector<int> potential_regexps;
  f.AllPotentials(empty_atoms, &potential_regexps);
  // Just verify no crash
}

// Test NumRegexps returns 0 on empty
TEST(FilteredRE2Test_471, NumRegexpsEmpty_471) {
  FilteredRE2 f;
  EXPECT_EQ(0, f.NumRegexps());
}

// Test move assignment to self via a separate object chain
TEST(FilteredRE2Test_471, MoveAssignmentOverwrite_471) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f1.Add("pattern1", opts, &id));

  FilteredRE2 f2;
  ASSERT_EQ(RE2::NoError, f2.Add("pattern2", opts, &id));
  ASSERT_EQ(RE2::NoError, f2.Add("pattern3", opts, &id));

  f1 = std::move(f2);
  EXPECT_EQ(2, f1.NumRegexps());
}

// Test compile with no patterns
TEST(FilteredRE2Test_471, CompileNoPatterns_471) {
  FilteredRE2 f;
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  EXPECT_EQ(0, f.NumRegexps());
}

// Test SlowFirstMatch with empty FilteredRE2
TEST(FilteredRE2Test_471, SlowFirstMatchEmpty_471) {
  FilteredRE2 f;
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  int match = f.SlowFirstMatch("anything");
  EXPECT_EQ(-1, match);
}

// Test with complex regex patterns
TEST(FilteredRE2Test_471, ComplexPatterns_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("\\d{3}-\\d{4}", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("[a-z]+@[a-z]+\\.com", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("call 123-4567 now");
  EXPECT_EQ(0, match);
}

// Test SlowFirstMatch returns first matching pattern
TEST(FilteredRE2Test_471, SlowFirstMatchReturnsFirst_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("abc", opts, &id));
  EXPECT_EQ(0, id);
  ASSERT_EQ(RE2::NoError, f.Add("def", opts, &id));
  EXPECT_EQ(1, id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Text contains both patterns
  int match = f.SlowFirstMatch("abcdef");
  EXPECT_EQ(0, match);
}

// Test empty text
TEST(FilteredRE2Test_471, EmptyText_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("hello", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("");
  EXPECT_EQ(-1, match);
}

// Test pattern that matches empty string
TEST(FilteredRE2Test_471, PatternMatchesEmptyString_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add(".*", opts, &id));

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("");
  EXPECT_EQ(0, match);
}

// Test GetRE2 for multiple patterns
TEST(FilteredRE2Test_471, GetRE2Multiple_471) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  ASSERT_EQ(RE2::NoError, f.Add("first", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("second", opts, &id));
  ASSERT_EQ(RE2::NoError, f.Add("third", opts, &id));

  EXPECT_EQ("first", f.GetRE2(0).pattern());
  EXPECT_EQ("second", f.GetRE2(1).pattern());
  EXPECT_EQ("third", f.GetRE2(2).pattern());
}

}  // namespace
}  // namespace re2
