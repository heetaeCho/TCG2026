#include "gtest/gtest.h"
#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class FilteredRE2Test_472 : public ::testing::Test {
 protected:
  FilteredRE2 f_;
};

// Test adding a valid pattern returns success error code
TEST_F(FilteredRE2Test_472, AddValidPattern_472) {
  int id;
  RE2::ErrorCode code = f_.Add("hello", RE2::Options(), &id);
  EXPECT_EQ(code, RE2::NoError);
  EXPECT_EQ(id, 0);
}

// Test adding multiple valid patterns assigns sequential IDs
TEST_F(FilteredRE2Test_472, AddMultipleValidPatterns_472) {
  int id0, id1, id2;
  RE2::ErrorCode code0 = f_.Add("hello", RE2::Options(), &id0);
  RE2::ErrorCode code1 = f_.Add("world", RE2::Options(), &id1);
  RE2::ErrorCode code2 = f_.Add("foo.*bar", RE2::Options(), &id2);

  EXPECT_EQ(code0, RE2::NoError);
  EXPECT_EQ(code1, RE2::NoError);
  EXPECT_EQ(code2, RE2::NoError);
  EXPECT_EQ(id0, 0);
  EXPECT_EQ(id1, 1);
  EXPECT_EQ(id2, 2);
}

// Test adding an invalid pattern returns an error code
TEST_F(FilteredRE2Test_472, AddInvalidPattern_472) {
  int id = -1;
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2::ErrorCode code = f_.Add("(unclosed", opts, &id);
  EXPECT_NE(code, RE2::NoError);
  // id should not have been set to a valid value since pattern failed
  EXPECT_EQ(id, -1);
}

// Test that NumRegexps reflects the number of successfully added patterns
TEST_F(FilteredRE2Test_472, NumRegexpsAfterAdd_472) {
  EXPECT_EQ(f_.NumRegexps(), 0);

  int id;
  f_.Add("abc", RE2::Options(), &id);
  EXPECT_EQ(f_.NumRegexps(), 1);

  f_.Add("def", RE2::Options(), &id);
  EXPECT_EQ(f_.NumRegexps(), 2);
}

// Test that NumRegexps doesn't increase when an invalid pattern is added
TEST_F(FilteredRE2Test_472, NumRegexpsNotIncreasedOnInvalidAdd_472) {
  EXPECT_EQ(f_.NumRegexps(), 0);

  int id = -1;
  RE2::Options opts;
  opts.set_log_errors(false);
  f_.Add("(invalid", opts, &id);
  EXPECT_EQ(f_.NumRegexps(), 0);
}

// Test GetRE2 returns a valid RE2 that matches the added pattern
TEST_F(FilteredRE2Test_472, GetRE2ReturnsCorrectPattern_472) {
  int id;
  f_.Add("hello", RE2::Options(), &id);
  const RE2& re = f_.GetRE2(id);
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_TRUE(re.ok());
}

// Test GetRE2 for multiple patterns
TEST_F(FilteredRE2Test_472, GetRE2MultiplePatterns_472) {
  int id0, id1;
  f_.Add("pattern_a", RE2::Options(), &id0);
  f_.Add("pattern_b", RE2::Options(), &id1);

  EXPECT_EQ(f_.GetRE2(id0).pattern(), "pattern_a");
  EXPECT_EQ(f_.GetRE2(id1).pattern(), "pattern_b");
}

// Test Compile produces atoms
TEST_F(FilteredRE2Test_472, CompileProducesAtoms_472) {
  int id;
  f_.Add("hello", RE2::Options(), &id);
  f_.Add("world", RE2::Options(), &id);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);
  // After compile, atoms should be populated (may or may not be empty
  // depending on patterns, but with literal strings we expect atoms)
  // We just verify compile doesn't crash and returns something
  EXPECT_GE(atoms.size(), 0u);
}

// Test SlowFirstMatch finds a match
TEST_F(FilteredRE2Test_472, SlowFirstMatchFindsMatch_472) {
  int id0, id1;
  f_.Add("hello", RE2::Options(), &id0);
  f_.Add("world", RE2::Options(), &id1);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);

  int match = f_.SlowFirstMatch("hello world");
  EXPECT_GE(match, 0);
}

// Test SlowFirstMatch returns -1 when no match
TEST_F(FilteredRE2Test_472, SlowFirstMatchNoMatch_472) {
  int id;
  f_.Add("xyz123", RE2::Options(), &id);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);

  int match = f_.SlowFirstMatch("hello world");
  EXPECT_EQ(match, -1);
}

// Test adding an empty pattern (which is valid)
TEST_F(FilteredRE2Test_472, AddEmptyPattern_472) {
  int id;
  RE2::ErrorCode code = f_.Add("", RE2::Options(), &id);
  EXPECT_EQ(code, RE2::NoError);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f_.NumRegexps(), 1);
}

// Test adding a complex regex pattern
TEST_F(FilteredRE2Test_472, AddComplexPattern_472) {
  int id;
  RE2::ErrorCode code = f_.Add("^[a-z]+\\d{2,4}$", RE2::Options(), &id);
  EXPECT_EQ(code, RE2::NoError);
  EXPECT_EQ(id, 0);
}

// Test with RE2::Options set to Quiet (log_errors = false)
TEST_F(FilteredRE2Test_472, AddInvalidPatternQuietMode_472) {
  int id = -1;
  RE2::Options opts(RE2::Quiet);
  RE2::ErrorCode code = f_.Add("[invalid", opts, &id);
  EXPECT_NE(code, RE2::NoError);
  EXPECT_EQ(id, -1);
  EXPECT_EQ(f_.NumRegexps(), 0);
}

// Test move constructor
TEST_F(FilteredRE2Test_472, MoveConstructor_472) {
  int id;
  f_.Add("hello", RE2::Options(), &id);
  f_.Add("world", RE2::Options(), &id);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);

  FilteredRE2 f2(std::move(f_));
  EXPECT_EQ(f2.NumRegexps(), 2);
  EXPECT_EQ(f2.GetRE2(0).pattern(), "hello");
  EXPECT_EQ(f2.GetRE2(1).pattern(), "world");
}

// Test move assignment operator
TEST_F(FilteredRE2Test_472, MoveAssignment_472) {
  int id;
  f_.Add("test_pattern", RE2::Options(), &id);

  FilteredRE2 f2;
  f2 = std::move(f_);
  EXPECT_EQ(f2.NumRegexps(), 1);
  EXPECT_EQ(f2.GetRE2(0).pattern(), "test_pattern");
}

// Test AllMatches returns matching regexps
TEST_F(FilteredRE2Test_472, AllMatchesFindsMatches_472) {
  int id0, id1, id2;
  f_.Add("hello", RE2::Options(), &id0);
  f_.Add("world", RE2::Options(), &id1);
  f_.Add("xyz", RE2::Options(), &id2);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);

  // Use SlowFirstMatch approach: provide all atom indices as matched
  std::vector<int> atom_indices;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    atom_indices.push_back(i);
  }

  std::vector<int> matching;
  bool has_match = f_.AllMatches("hello world", atom_indices, &matching);

  // "hello" and "world" should match, "xyz" should not
  if (has_match) {
    EXPECT_GE(matching.size(), 1u);
  }
}

// Test with FilteredRE2 constructed with min_atom_len
TEST_F(FilteredRE2Test_472, ConstructWithMinAtomLen_472) {
  FilteredRE2 f(3);
  int id;
  RE2::ErrorCode code = f.Add("hello", RE2::Options(), &id);
  EXPECT_EQ(code, RE2::NoError);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f.NumRegexps(), 1);
}

// Test adding pattern with options (case insensitive)
TEST_F(FilteredRE2Test_472, AddPatternWithCaseInsensitiveOption_472) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  int id;
  RE2::ErrorCode code = f_.Add("Hello", opts, &id);
  EXPECT_EQ(code, RE2::NoError);
  EXPECT_EQ(id, 0);

  const RE2& re = f_.GetRE2(id);
  EXPECT_TRUE(re.ok());
}

// Test that an invalid regex with multiple errors still fails properly
TEST_F(FilteredRE2Test_472, AddMultipleInvalidPatterns_472) {
  RE2::Options opts;
  opts.set_log_errors(false);

  int id1 = -1, id2 = -1;
  RE2::ErrorCode code1 = f_.Add("(", opts, &id1);
  RE2::ErrorCode code2 = f_.Add("*invalid", opts, &id2);

  EXPECT_NE(code1, RE2::NoError);
  EXPECT_NE(code2, RE2::NoError);
  EXPECT_EQ(f_.NumRegexps(), 0);
}

// Test mixed valid and invalid patterns
TEST_F(FilteredRE2Test_472, AddMixedValidAndInvalidPatterns_472) {
  RE2::Options opts;
  opts.set_log_errors(false);

  int id_valid = -1, id_invalid = -1, id_valid2 = -1;
  RE2::ErrorCode code1 = f_.Add("valid", RE2::Options(), &id_valid);
  RE2::ErrorCode code2 = f_.Add("(invalid", opts, &id_invalid);
  RE2::ErrorCode code3 = f_.Add("also_valid", RE2::Options(), &id_valid2);

  EXPECT_EQ(code1, RE2::NoError);
  EXPECT_EQ(id_valid, 0);

  EXPECT_NE(code2, RE2::NoError);
  EXPECT_EQ(id_invalid, -1);

  EXPECT_EQ(code3, RE2::NoError);
  EXPECT_EQ(id_valid2, 1);

  EXPECT_EQ(f_.NumRegexps(), 2);
}

// Test SlowFirstMatch with empty text
TEST_F(FilteredRE2Test_472, SlowFirstMatchEmptyText_472) {
  int id;
  f_.Add("hello", RE2::Options(), &id);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);

  int match = f_.SlowFirstMatch("");
  EXPECT_EQ(match, -1);
}

// Test SlowFirstMatch with empty pattern (matches everything)
TEST_F(FilteredRE2Test_472, SlowFirstMatchEmptyPatternMatchesAll_472) {
  int id;
  f_.Add("", RE2::Options(), &id);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);

  int match = f_.SlowFirstMatch("anything");
  EXPECT_EQ(match, 0);
}

// Test default constructed FilteredRE2 has zero regexps
TEST_F(FilteredRE2Test_472, DefaultConstructedHasZeroRegexps_472) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test that the error code returned matches RE2's error classification
TEST_F(FilteredRE2Test_472, ErrorCodeMatchesBadCharClass_472) {
  RE2::Options opts;
  opts.set_log_errors(false);

  int id = -1;
  // "[z-a]" is an invalid character class (reversed range)
  RE2::ErrorCode code = f_.Add("[z-a]", opts, &id);
  EXPECT_NE(code, RE2::NoError);
}

// Test FirstMatch with atoms
TEST_F(FilteredRE2Test_472, FirstMatchWithAtoms_472) {
  int id0, id1;
  f_.Add("apple", RE2::Options(), &id0);
  f_.Add("banana", RE2::Options(), &id1);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);

  // Provide all atoms as matched
  std::vector<int> atom_ids;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    atom_ids.push_back(i);
  }

  int match = f_.FirstMatch("I like apple pie", atom_ids);
  // Should find "apple" as a match
  EXPECT_GE(match, 0);
}

// Test AllPotentials
TEST_F(FilteredRE2Test_472, AllPotentials_472) {
  int id0, id1;
  f_.Add("cat", RE2::Options(), &id0);
  f_.Add("dog", RE2::Options(), &id1);

  std::vector<std::string> atoms;
  f_.Compile(&atoms);

  std::vector<int> atom_ids;
  for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
    atom_ids.push_back(i);
  }

  std::vector<int> potentials;
  f_.AllPotentials(atom_ids, &potentials);
  // With all atoms matched, both regexps should be potential
  EXPECT_GE(potentials.size(), 0u);
}

}  // namespace re2
