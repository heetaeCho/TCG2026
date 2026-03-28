#include "gtest/gtest.h"
#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class FilteredRE2Test_474 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that default constructor creates a valid FilteredRE2 with no regexps
TEST_F(FilteredRE2Test_474, DefaultConstructor_474) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test that constructor with min_atom_len creates a valid FilteredRE2
TEST_F(FilteredRE2Test_474, ConstructorWithMinAtomLen_474) {
  FilteredRE2 f(3);
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test Add returns success and assigns an id
TEST_F(FilteredRE2Test_474, AddSinglePattern_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  RE2::ErrorCode code = f.Add("hello", opts, &id);
  EXPECT_EQ(code, RE2::NoError);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f.NumRegexps(), 1);
}

// Test Add multiple patterns assigns incremental ids
TEST_F(FilteredRE2Test_474, AddMultiplePatterns_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1, id2;
  EXPECT_EQ(f.Add("hello", opts, &id0), RE2::NoError);
  EXPECT_EQ(f.Add("world", opts, &id1), RE2::NoError);
  EXPECT_EQ(f.Add("foo.*bar", opts, &id2), RE2::NoError);
  EXPECT_EQ(id0, 0);
  EXPECT_EQ(id1, 1);
  EXPECT_EQ(id2, 2);
  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test Add with invalid pattern returns an error code
TEST_F(FilteredRE2Test_474, AddInvalidPattern_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  RE2::ErrorCode code = f.Add("(unclosed", opts, &id);
  EXPECT_NE(code, RE2::NoError);
}

// Test GetRE2 returns the correct RE2 object
TEST_F(FilteredRE2Test_474, GetRE2_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  const RE2& re = f.GetRE2(id);
  EXPECT_EQ(re.pattern(), "hello");
}

// Test SlowFirstMatch returns the index of the first matching pattern
TEST_F(FilteredRE2Test_474, SlowFirstMatchFindsFirst_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  int match = f.SlowFirstMatch("hello world");
  EXPECT_EQ(match, 0);
}

// Test SlowFirstMatch returns second pattern when first doesn't match
TEST_F(FilteredRE2Test_474, SlowFirstMatchFindsSecond_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  int match = f.SlowFirstMatch("world");
  EXPECT_EQ(match, 1);
}

// Test SlowFirstMatch returns -1 when no pattern matches
TEST_F(FilteredRE2Test_474, SlowFirstMatchNoMatch_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  int match = f.SlowFirstMatch("foobar");
  EXPECT_EQ(match, -1);
}

// Test SlowFirstMatch with empty text
TEST_F(FilteredRE2Test_474, SlowFirstMatchEmptyText_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  int match = f.SlowFirstMatch("");
  EXPECT_EQ(match, -1);
}

// Test SlowFirstMatch with no regexps added
TEST_F(FilteredRE2Test_474, SlowFirstMatchNoRegexps_474) {
  FilteredRE2 f;
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  int match = f.SlowFirstMatch("anything");
  EXPECT_EQ(match, -1);
}

// Test SlowFirstMatch with a regex that matches empty string
TEST_F(FilteredRE2Test_474, SlowFirstMatchEmptyPattern_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add(".*", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  int match = f.SlowFirstMatch("anything");
  EXPECT_EQ(match, 0);
}

// Test SlowFirstMatch with a regex that matches empty string on empty input
TEST_F(FilteredRE2Test_474, SlowFirstMatchEmptyPatternEmptyText_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add(".*", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  int match = f.SlowFirstMatch("");
  EXPECT_EQ(match, 0);
}

// Test Compile produces atoms
TEST_F(FilteredRE2Test_474, CompileProducesAtoms_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // atoms may or may not be empty depending on patterns, but Compile should not crash
}

// Test FirstMatch with atoms
TEST_F(FilteredRE2Test_474, FirstMatchWithAtoms_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  // Build atom index: mark all atoms as matched
  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }
  
  int match = f.FirstMatch("hello world", matched_atoms);
  EXPECT_GE(match, 0);
  EXPECT_LT(match, f.NumRegexps());
}

// Test FirstMatch returns -1 when no match
TEST_F(FilteredRE2Test_474, FirstMatchNoMatch_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  // Empty atoms means no potential matches
  std::vector<int> empty_atoms;
  int match = f.FirstMatch("foobar", empty_atoms);
  EXPECT_EQ(match, -1);
}

// Test AllMatches finds multiple matches
TEST_F(FilteredRE2Test_474, AllMatchesMultiple_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  f.Add("foobar", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  // Mark all atoms as matched
  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }
  
  std::vector<int> matching_regexps;
  bool result = f.AllMatches("hello world", matched_atoms, &matching_regexps);
  // Should find at least hello and world
  EXPECT_TRUE(result);
  EXPECT_GE(matching_regexps.size(), 2u);
}

// Test AllMatches with no matches
TEST_F(FilteredRE2Test_474, AllMatchesNoMatch_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  std::vector<int> empty_atoms;
  std::vector<int> matching_regexps;
  bool result = f.AllMatches("nomatch", empty_atoms, &matching_regexps);
  EXPECT_FALSE(result);
  EXPECT_TRUE(matching_regexps.empty());
}

// Test AllPotentials
TEST_F(FilteredRE2Test_474, AllPotentials_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  // Mark all atoms as matched
  std::vector<int> matched_atoms;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    matched_atoms.push_back(i);
  }
  
  std::vector<int> potential_regexps;
  f.AllPotentials(matched_atoms, &potential_regexps);
  // With all atoms matched, all patterns should be potential
  EXPECT_GE(potential_regexps.size(), 2u);
}

// Test move constructor
TEST_F(FilteredRE2Test_474, MoveConstructor_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  FilteredRE2 f2(std::move(f));
  EXPECT_EQ(f2.NumRegexps(), 2);
  
  int match = f2.SlowFirstMatch("hello");
  EXPECT_EQ(match, 0);
}

// Test move assignment
TEST_F(FilteredRE2Test_474, MoveAssignment_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  FilteredRE2 f2;
  f2 = std::move(f);
  EXPECT_EQ(f2.NumRegexps(), 1);
  
  int match = f2.SlowFirstMatch("hello");
  EXPECT_EQ(match, 0);
}

// Test NumRegexps increments with each Add
TEST_F(FilteredRE2Test_474, NumRegexpsIncrement_474) {
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

// Test SlowFirstMatch with complex regex patterns
TEST_F(FilteredRE2Test_474, SlowFirstMatchComplexPatterns_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("[0-9]+", opts, &id);
  f.Add("[a-z]+", opts, &id);
  f.Add("\\d{3}-\\d{4}", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  // "123-4567" should match pattern 0 ([0-9]+), and potentially pattern 2
  int match = f.SlowFirstMatch("123-4567");
  EXPECT_EQ(match, 0);
}

// Test SlowFirstMatch returns first matching among overlapping patterns
TEST_F(FilteredRE2Test_474, SlowFirstMatchOverlapping_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("abc", opts, &id);    // id=0
  f.Add("abcdef", opts, &id); // id=1
  f.Add("ab", opts, &id);     // id=2
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  // "abcdef" should match pattern 0 first (it's checked first)
  int match = f.SlowFirstMatch("abcdef");
  EXPECT_EQ(match, 0);
}

// Test GetRE2 for multiple patterns
TEST_F(FilteredRE2Test_474, GetRE2MultiplePatterns_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1;
  f.Add("pattern_one", opts, &id0);
  f.Add("pattern_two", opts, &id1);
  
  EXPECT_EQ(f.GetRE2(id0).pattern(), "pattern_one");
  EXPECT_EQ(f.GetRE2(id1).pattern(), "pattern_two");
}

// Test SlowFirstMatch with partial match (substring)
TEST_F(FilteredRE2Test_474, SlowFirstMatchPartialMatch_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("needle", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  // PartialMatch should find "needle" inside the text
  int match = f.SlowFirstMatch("haystackneedlehaystack");
  EXPECT_EQ(match, 0);
}

// Test SlowFirstMatch with case-sensitive patterns (default)
TEST_F(FilteredRE2Test_474, SlowFirstMatchCaseSensitive_474) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("Hello", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  EXPECT_EQ(f.SlowFirstMatch("Hello"), 0);
  EXPECT_EQ(f.SlowFirstMatch("hello"), -1);
}

// Test SlowFirstMatch with case-insensitive option
TEST_F(FilteredRE2Test_474, SlowFirstMatchCaseInsensitive_474) {
  FilteredRE2 f;
  RE2::Options opts;
  opts.set_case_sensitive(false);
  int id;
  f.Add("Hello", opts, &id);
  
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  
  EXPECT_EQ(f.SlowFirstMatch("hello"), 0);
  EXPECT_EQ(f.SlowFirstMatch("HELLO"), 0);
}

}  // namespace re2
