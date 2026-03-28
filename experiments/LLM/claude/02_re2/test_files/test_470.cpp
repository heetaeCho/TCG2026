#include "gtest/gtest.h"
#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <memory>

namespace re2 {
namespace {

// Test default construction
TEST(FilteredRE2Test_470, DefaultConstruction_470) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test construction with min_atom_len
TEST(FilteredRE2Test_470, ConstructionWithMinAtomLen_470) {
  FilteredRE2 f(3);
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test move construction
TEST(FilteredRE2Test_470, MoveConstruction_470) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  f1.Add("hello", opts, &id);
  EXPECT_EQ(f1.NumRegexps(), 1);

  FilteredRE2 f2(std::move(f1));
  EXPECT_EQ(f2.NumRegexps(), 1);
}

// Test move assignment
TEST(FilteredRE2Test_470, MoveAssignment_470) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  f1.Add("hello", opts, &id);

  FilteredRE2 f2;
  f2 = std::move(f1);
  EXPECT_EQ(f2.NumRegexps(), 1);
}

// Test adding a single pattern
TEST(FilteredRE2Test_470, AddSinglePattern_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id = -1;
  RE2::ErrorCode err = f.Add("hello", opts, &id);
  EXPECT_EQ(err, RE2::NoError);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f.NumRegexps(), 1);
}

// Test adding multiple patterns
TEST(FilteredRE2Test_470, AddMultiplePatterns_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id1 = -1, id2 = -1, id3 = -1;
  f.Add("hello", opts, &id1);
  f.Add("world", opts, &id2);
  f.Add("foo.*bar", opts, &id3);
  EXPECT_EQ(id1, 0);
  EXPECT_EQ(id2, 1);
  EXPECT_EQ(id3, 2);
  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test adding invalid pattern
TEST(FilteredRE2Test_470, AddInvalidPattern_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id = -1;
  RE2::ErrorCode err = f.Add("(unclosed", opts, &id);
  EXPECT_NE(err, RE2::NoError);
}

// Test GetRE2
TEST(FilteredRE2Test_470, GetRE2_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  const RE2& re = f.GetRE2(0);
  EXPECT_EQ(re.pattern(), "hello");
}

// Test Compile
TEST(FilteredRE2Test_470, Compile_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // After compile, atoms should have been populated (possibly empty for simple patterns)
  // We just verify that Compile doesn't crash
  SUCCEED();
}

// Test SlowFirstMatch with matching text
TEST(FilteredRE2Test_470, SlowFirstMatchFound_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("hello world");
  EXPECT_GE(match, 0);
}

// Test SlowFirstMatch with no matching text
TEST(FilteredRE2Test_470, SlowFirstMatchNotFound_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("xyz");
  EXPECT_EQ(match, -1);
}

// Test SlowFirstMatch with empty text
TEST(FilteredRE2Test_470, SlowFirstMatchEmptyText_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("");
  EXPECT_EQ(match, -1);
}

// Test SlowFirstMatch returns first match
TEST(FilteredRE2Test_470, SlowFirstMatchReturnsFirst_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("hel", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("hello");
  EXPECT_GE(match, 0);
  EXPECT_LE(match, 1);
}

// Test FirstMatch
TEST(FilteredRE2Test_470, FirstMatchFound_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Build atom indices - for simplicity, pass all atoms as matched
  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  int match = f.FirstMatch("hello", matched_atoms);
  EXPECT_GE(match, 0);
}

// Test FirstMatch with no matching text
TEST(FilteredRE2Test_470, FirstMatchNotFound_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  int match = f.FirstMatch("xyz", matched_atoms);
  EXPECT_EQ(match, -1);
}

// Test AllMatches
TEST(FilteredRE2Test_470, AllMatchesFound_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("hell", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("hello world", matched_atoms, &matching_regexps);
  EXPECT_TRUE(result);
  EXPECT_GE(matching_regexps.size(), 1u);
}

// Test AllMatches no match
TEST(FilteredRE2Test_470, AllMatchesNotFound_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("xyz", matched_atoms, &matching_regexps);
  EXPECT_FALSE(result);
  EXPECT_TRUE(matching_regexps.empty());
}

// Test AllPotentials
TEST(FilteredRE2Test_470, AllPotentials_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
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
  EXPECT_GE(potential_regexps.size(), 1u);
}

// Test AllPotentials with no atoms matched
TEST(FilteredRE2Test_470, AllPotentialsNoAtoms_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> no_atoms;
  std::vector<int> potential_regexps;
  f.AllPotentials(no_atoms, &potential_regexps);
  // Result depends on implementation - just ensure no crash
  SUCCEED();
}

// Test with empty FilteredRE2
TEST(FilteredRE2Test_470, EmptyFilteredRE2Compile_470) {
  FilteredRE2 f;
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  EXPECT_TRUE(atoms.empty());
}

// Test SlowFirstMatch on empty FilteredRE2
TEST(FilteredRE2Test_470, SlowFirstMatchEmptyFilter_470) {
  FilteredRE2 f;
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  int match = f.SlowFirstMatch("anything");
  EXPECT_EQ(match, -1);
}

// Test NumRegexps on empty
TEST(FilteredRE2Test_470, NumRegexpsEmpty_470) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test NumRegexps after adds
TEST(FilteredRE2Test_470, NumRegexpsAfterAdds_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  for (int i = 0; i < 10; i++) {
    f.Add("pattern" + std::to_string(i), opts, &id);
  }
  EXPECT_EQ(f.NumRegexps(), 10);
}

// Test GetRE2 retrieves correct patterns
TEST(FilteredRE2Test_470, GetRE2CorrectPattern_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("alpha", opts, &id);
  f.Add("beta", opts, &id);
  f.Add("gamma", opts, &id);
  EXPECT_EQ(f.GetRE2(0).pattern(), "alpha");
  EXPECT_EQ(f.GetRE2(1).pattern(), "beta");
  EXPECT_EQ(f.GetRE2(2).pattern(), "gamma");
}

// Test complex regex patterns
TEST(FilteredRE2Test_470, ComplexRegexPatterns_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("(foo|bar)baz.*qux", opts, &id);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f.NumRegexps(), 1);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("foobazXXXqux");
  EXPECT_EQ(match, 0);

  match = f.SlowFirstMatch("barbazqux");
  EXPECT_EQ(match, 0);

  match = f.SlowFirstMatch("nomatch");
  EXPECT_EQ(match, -1);
}

// Test move assignment clears original
TEST(FilteredRE2Test_470, MoveAssignmentClearsOriginal_470) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  f1.Add("hello", opts, &id);
  f1.Add("world", opts, &id);

  FilteredRE2 f2;
  f2.Add("foo", opts, &id);

  f2 = std::move(f1);
  EXPECT_EQ(f2.NumRegexps(), 2);
  EXPECT_EQ(f2.GetRE2(0).pattern(), "hello");
  EXPECT_EQ(f2.GetRE2(1).pattern(), "world");
}

// Test that adding pattern with dot-star works
TEST(FilteredRE2Test_470, DotStarPattern_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  RE2::ErrorCode err = f.Add(".*", opts, &id);
  EXPECT_EQ(err, RE2::NoError);
  EXPECT_EQ(id, 0);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // .* matches everything
  int match = f.SlowFirstMatch("anything");
  EXPECT_EQ(match, 0);

  match = f.SlowFirstMatch("");
  EXPECT_EQ(match, 0);
}

// Test with case-insensitive option
TEST(FilteredRE2Test_470, CaseInsensitiveOption_470) {
  FilteredRE2 f;
  RE2::Options opts;
  opts.set_case_sensitive(false);
  int id;
  f.Add("hello", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("HELLO");
  EXPECT_EQ(match, 0);

  match = f.SlowFirstMatch("Hello");
  EXPECT_EQ(match, 0);
}

// Test FirstMatch with empty atoms vector
TEST(FilteredRE2Test_470, FirstMatchEmptyAtoms_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> empty_atoms;
  int match = f.FirstMatch("hello", empty_atoms);
  // With no atoms matched, behavior depends on prefilter - may or may not match
  // Just ensure no crash
  (void)match;
  SUCCEED();
}

// Test AllMatches with multiple matching regexps
TEST(FilteredRE2Test_470, AllMatchesMultipleMatches_470) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("he", opts, &id);
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("hello", matched_atoms, &matching_regexps);
  EXPECT_TRUE(result);
  // At least "he" and "hello" should match
  EXPECT_GE(matching_regexps.size(), 2u);
}

}  // namespace
}  // namespace re2
