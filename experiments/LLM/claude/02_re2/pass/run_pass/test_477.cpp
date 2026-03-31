#include "gtest/gtest.h"
#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include <vector>
#include <string>

namespace re2 {

class FilteredRE2Test_477 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(FilteredRE2Test_477, DefaultConstruction_477) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test construction with min_atom_len
TEST_F(FilteredRE2Test_477, ConstructionWithMinAtomLen_477) {
  FilteredRE2 f(4);
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test move construction
TEST_F(FilteredRE2Test_477, MoveConstruction_477) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  f1.Add("hello", opts, &id);
  EXPECT_EQ(f1.NumRegexps(), 1);

  FilteredRE2 f2(std::move(f1));
  EXPECT_EQ(f2.NumRegexps(), 1);
}

// Test move assignment
TEST_F(FilteredRE2Test_477, MoveAssignment_477) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  f1.Add("hello", opts, &id);

  FilteredRE2 f2;
  f2 = std::move(f1);
  EXPECT_EQ(f2.NumRegexps(), 1);
}

// Test Add returns success for valid pattern
TEST_F(FilteredRE2Test_477, AddValidPattern_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id = -1;
  RE2::ErrorCode err = f.Add("hello", opts, &id);
  EXPECT_EQ(err, RE2::NoError);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f.NumRegexps(), 1);
}

// Test Add multiple patterns
TEST_F(FilteredRE2Test_477, AddMultiplePatterns_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id1, id2, id3;
  f.Add("hello", opts, &id1);
  f.Add("world", opts, &id2);
  f.Add("foo.*bar", opts, &id3);
  EXPECT_EQ(id1, 0);
  EXPECT_EQ(id2, 1);
  EXPECT_EQ(id3, 2);
  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test Add with invalid pattern
TEST_F(FilteredRE2Test_477, AddInvalidPattern_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id = -1;
  RE2::ErrorCode err = f.Add("(unclosed", opts, &id);
  // The pattern is invalid, error code should not be NoError
  EXPECT_NE(err, RE2::NoError);
}

// Test Compile produces atom strings
TEST_F(FilteredRE2Test_477, CompileProducesAtoms_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // After compilation, atoms vector should be populated (may or may not be empty
  // depending on patterns, but for literal patterns it should have entries)
  // We just verify it doesn't crash and compilation succeeds
}

// Test Compile with no patterns
TEST_F(FilteredRE2Test_477, CompileNoPatterns_477) {
  FilteredRE2 f;
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  EXPECT_TRUE(atoms.empty());
}

// Test GetRE2 returns valid reference
TEST_F(FilteredRE2Test_477, GetRE2Valid_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  const RE2& re = f.GetRE2(0);
  EXPECT_EQ(re.pattern(), "hello");
}

// Test SlowFirstMatch with matching text
TEST_F(FilteredRE2Test_477, SlowFirstMatchFound_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("hello world");
  EXPECT_GE(match, 0);
  EXPECT_LT(match, 2);
}

// Test SlowFirstMatch with no match
TEST_F(FilteredRE2Test_477, SlowFirstMatchNotFound_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("xyz");
  EXPECT_EQ(match, -1);
}

// Test FirstMatch with matching atoms
TEST_F(FilteredRE2Test_477, FirstMatchFound_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Build atoms list - match all atoms
  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  int match = f.FirstMatch("hello world", matched_atoms);
  EXPECT_GE(match, 0);
}

// Test FirstMatch with no matching text
TEST_F(FilteredRE2Test_477, FirstMatchNotFound_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Empty atoms means no atom matched
  std::vector<int> matched_atoms;
  int match = f.FirstMatch("xyz", matched_atoms);
  EXPECT_EQ(match, -1);
}

// Test AllMatches returns all matching regexps
TEST_F(FilteredRE2Test_477, AllMatchesMultiple_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("hel", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("hello", matched_atoms, &matching_regexps);
  // At least "hello" and "hel" should match
  EXPECT_GE(matching_regexps.size(), 1u);
}

// Test AllMatches with no matches
TEST_F(FilteredRE2Test_477, AllMatchesNone_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;  // no atoms matched
  std::vector<int> matching_regexps;
  bool result = f.AllMatches("xyz", matched_atoms, &matching_regexps);
  EXPECT_TRUE(matching_regexps.empty());
}

// Test AllPotentials with empty atoms
TEST_F(FilteredRE2Test_477, AllPotentialsEmptyAtoms_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  std::vector<int> potentials;
  f.AllPotentials(matched_atoms, &potentials);
  // With no matched atoms, potentials may contain unfiltered regexps
  // or be empty - just ensure no crash
}

// Test AllPotentials with all atoms matched
TEST_F(FilteredRE2Test_477, AllPotentialsAllAtoms_477) {
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

  std::vector<int> potentials;
  f.AllPotentials(matched_atoms, &potentials);
  // All regexps should be potential matches
  EXPECT_GE(potentials.size(), 1u);
}

// Test AllPotentials with pattern that has no atoms (e.g., ".*")
TEST_F(FilteredRE2Test_477, AllPotentialsUnfilteredPattern_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add(".*", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // ".*" likely produces no atoms, so it should always be a potential
  std::vector<int> matched_atoms;
  std::vector<int> potentials;
  f.AllPotentials(matched_atoms, &potentials);
  // The unfiltered regexp should appear as potential
  ASSERT_EQ(potentials.size(), 1u);
  EXPECT_EQ(potentials[0], 0);
}

// Test NumRegexps returns correct count
TEST_F(FilteredRE2Test_477, NumRegexpsCorrectCount_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  EXPECT_EQ(f.NumRegexps(), 0);
  f.Add("a", opts, &id);
  EXPECT_EQ(f.NumRegexps(), 1);
  f.Add("b", opts, &id);
  EXPECT_EQ(f.NumRegexps(), 2);
  f.Add("c", opts, &id);
  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test SlowFirstMatch with empty text
TEST_F(FilteredRE2Test_477, SlowFirstMatchEmptyText_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("");
  EXPECT_EQ(match, -1);
}

// Test SlowFirstMatch with empty text and pattern matching empty
TEST_F(FilteredRE2Test_477, SlowFirstMatchEmptyPatternEmptyText_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add(".*", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("");
  EXPECT_EQ(match, 0);
}

// Test FirstMatch returns first matching regexp index
TEST_F(FilteredRE2Test_477, FirstMatchReturnsFirst_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("abc", opts, &id);   // id 0
  f.Add("abcdef", opts, &id); // id 1

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }

  int match = f.FirstMatch("abcdef", matched_atoms);
  // Should return first matching
  EXPECT_GE(match, 0);
  EXPECT_LT(match, 2);
}

// Test Compile with complex patterns
TEST_F(FilteredRE2Test_477, CompileComplexPatterns_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("(foo|bar)baz", opts, &id);
  f.Add("abc[0-9]+xyz", opts, &id);
  f.Add("test\\d+end", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // Should not crash; atoms may or may not be populated
  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test move-assigned object works correctly
TEST_F(FilteredRE2Test_477, MoveAssignmentFunctionality_477) {
  FilteredRE2 f1;
  RE2::Options opts;
  int id;
  f1.Add("hello", opts, &id);
  f1.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f1.Compile(&atoms);

  FilteredRE2 f2;
  f2 = std::move(f1);

  EXPECT_EQ(f2.NumRegexps(), 2);
  int match = f2.SlowFirstMatch("hello");
  EXPECT_EQ(match, 0);
}

// Test AllMatches returns boolean correctly
TEST_F(FilteredRE2Test_477, AllMatchesReturnValue_477) {
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

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("hello world", matched_atoms, &matching_regexps);
  // Should find matches
  EXPECT_FALSE(matching_regexps.empty());
}

// Test with single character patterns
TEST_F(FilteredRE2Test_477, SingleCharPatterns_477) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  // Single character patterns likely produce no useful atoms (< min_atom_len=3)
  f.Add("a", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // "a" has atom length 1, less than default min_atom_len (3), 
  // so it should be unfiltered
  std::vector<int> matched_atoms;
  std::vector<int> potentials;
  f.AllPotentials(matched_atoms, &potentials);
  EXPECT_EQ(potentials.size(), 1u);
  EXPECT_EQ(potentials[0], 0);
}

}  // namespace re2
