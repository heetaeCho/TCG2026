#include "gtest/gtest.h"
#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

// Test fixture for FilteredRE2
class FilteredRE2Test_473 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(FilteredRE2Test_473, DefaultConstruction_473) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test construction with min_atom_len
TEST_F(FilteredRE2Test_473, ConstructionWithMinAtomLen_473) {
  FilteredRE2 f(4);
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test Compile with no regexps added (empty)
TEST_F(FilteredRE2Test_473, CompileWithNoRegexps_473) {
  FilteredRE2 f;
  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // Should return without error; atoms should be empty or unchanged
  EXPECT_TRUE(atoms.empty());
}

// Test Add single pattern
TEST_F(FilteredRE2Test_473, AddSinglePattern_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  RE2::ErrorCode err = f.Add("hello", opts, &id);
  EXPECT_EQ(err, RE2::NoError);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f.NumRegexps(), 1);
}

// Test Add multiple patterns
TEST_F(FilteredRE2Test_473, AddMultiplePatterns_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  RE2::ErrorCode err1 = f.Add("hello", opts, &id);
  EXPECT_EQ(err1, RE2::NoError);
  EXPECT_EQ(id, 0);

  RE2::ErrorCode err2 = f.Add("world", opts, &id);
  EXPECT_EQ(err2, RE2::NoError);
  EXPECT_EQ(id, 1);

  RE2::ErrorCode err3 = f.Add("foo.*bar", opts, &id);
  EXPECT_EQ(err3, RE2::NoError);
  EXPECT_EQ(id, 2);

  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test Compile with regexps added
TEST_F(FilteredRE2Test_473, CompileWithRegexps_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // After compile, atoms should have been populated (or at least the call should succeed)
  // The exact content depends on internal prefilter logic, but we can verify it doesn't crash
}

// Test Compile clears atoms vector
TEST_F(FilteredRE2Test_473, CompileClearsAtoms_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  atoms.push_back("pre-existing");
  f.Compile(&atoms);
  // atoms should have been cleared before being populated
  // The pre-existing value should be gone
  for (const auto& a : atoms) {
    EXPECT_NE(a, "pre-existing");
  }
}

// Test double Compile is a no-op (logs error but doesn't crash)
TEST_F(FilteredRE2Test_473, DoubleCompileDoesNotCrash_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<std::string> atoms2;
  // Second compile should log error and return without crashing
  f.Compile(&atoms2);
}

// Test GetRE2 returns correct regex
TEST_F(FilteredRE2Test_473, GetRE2ReturnsCorrectRegex_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  const RE2& re0 = f.GetRE2(0);
  EXPECT_EQ(re0.pattern(), "hello");

  const RE2& re1 = f.GetRE2(1);
  EXPECT_EQ(re1.pattern(), "world");
}

// Test SlowFirstMatch with matching text
TEST_F(FilteredRE2Test_473, SlowFirstMatchFindsMatch_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("hello world");
  // Should find at least one match (likely index 0 for "hello")
  EXPECT_GE(match, 0);
}

// Test SlowFirstMatch with no matching text
TEST_F(FilteredRE2Test_473, SlowFirstMatchNoMatch_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("zzzzz");
  EXPECT_EQ(match, -1);
}

// Test FirstMatch with atoms
TEST_F(FilteredRE2Test_473, FirstMatchWithAtoms_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Simulate all atoms matched
  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atoms.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }

  int match = f.FirstMatch("hello world", matched_atoms);
  EXPECT_GE(match, 0);
}

// Test FirstMatch with empty atoms
TEST_F(FilteredRE2Test_473, FirstMatchWithEmptyAtoms_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;  // empty
  int match = f.FirstMatch("hello", matched_atoms);
  // With no atoms matched, might return -1 unless unfiltered
  // We just check it doesn't crash
  (void)match;
}

// Test AllMatches
TEST_F(FilteredRE2Test_473, AllMatchesFindsMultiple_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  f.Add("zzzznothere", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atoms.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }

  std::vector<int> matching_regexps;
  bool result = f.AllMatches("hello world", matched_atoms, &matching_regexps);
  // Should find matches for "hello" and "world" but not "zzzznothere"
  // At minimum, we verify the call succeeds
  (void)result;
}

// Test AllPotentials
TEST_F(FilteredRE2Test_473, AllPotentialsReturnsResults_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atoms.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }

  std::vector<int> potential_regexps;
  f.AllPotentials(matched_atoms, &potential_regexps);
  // Should return some potential regexps
  EXPECT_FALSE(potential_regexps.empty());
}

// Test move constructor
TEST_F(FilteredRE2Test_473, MoveConstructor_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  FilteredRE2 f2(std::move(f));
  EXPECT_EQ(f2.NumRegexps(), 2);
  EXPECT_EQ(f2.GetRE2(0).pattern(), "hello");
  EXPECT_EQ(f2.GetRE2(1).pattern(), "world");
}

// Test move assignment
TEST_F(FilteredRE2Test_473, MoveAssignment_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  FilteredRE2 f2;
  f2 = std::move(f);
  EXPECT_EQ(f2.NumRegexps(), 1);
  EXPECT_EQ(f2.GetRE2(0).pattern(), "hello");
}

// Test Add with invalid pattern
TEST_F(FilteredRE2Test_473, AddInvalidPattern_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  RE2::ErrorCode err = f.Add("(invalid[", opts, &id);
  // Invalid regex should still get an id but may report an error
  // The exact behavior depends on RE2, but it shouldn't crash
  (void)err;
}

// Test NumRegexps after adding patterns
TEST_F(FilteredRE2Test_473, NumRegexpsTracksAdds_473) {
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

// Test that Add assigns sequential IDs
TEST_F(FilteredRE2Test_473, AddAssignsSequentialIds_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1, id2;

  f.Add("alpha", opts, &id0);
  f.Add("beta", opts, &id1);
  f.Add("gamma", opts, &id2);

  EXPECT_EQ(id0, 0);
  EXPECT_EQ(id1, 1);
  EXPECT_EQ(id2, 2);
}

// Test SlowFirstMatch with empty text
TEST_F(FilteredRE2Test_473, SlowFirstMatchEmptyText_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("");
  EXPECT_EQ(match, -1);
}

// Test SlowFirstMatch where regex matches empty string
TEST_F(FilteredRE2Test_473, SlowFirstMatchRegexMatchesEmpty_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add(".*", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("");
  // ".*" should match empty string
  EXPECT_EQ(match, 0);
}

// Test AllMatches with empty text
TEST_F(FilteredRE2Test_473, AllMatchesEmptyText_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;
  std::vector<int> matching_regexps;
  bool result = f.AllMatches("", matched_atoms, &matching_regexps);
  // "hello" should not match empty text
  EXPECT_TRUE(matching_regexps.empty());
  (void)result;
}

// Test with complex regex patterns
TEST_F(FilteredRE2Test_473, ComplexPatterns_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("foo[0-9]+bar", opts, &id);
  EXPECT_EQ(id, 0);

  f.Add("(abc|def)ghi", opts, &id);
  EXPECT_EQ(id, 1);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("foo123bar");
  EXPECT_EQ(match, 0);

  match = f.SlowFirstMatch("abcghi");
  EXPECT_EQ(match, 1);

  match = f.SlowFirstMatch("no match here");
  EXPECT_EQ(match, -1);
}

// Test AllPotentials with empty atoms
TEST_F(FilteredRE2Test_473, AllPotentialsEmptyAtoms_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> matched_atoms;  // empty
  std::vector<int> potential_regexps;
  f.AllPotentials(matched_atoms, &potential_regexps);
  // Shouldn't crash; results depend on internal logic
}

// Test with patterns that have overlapping atoms
TEST_F(FilteredRE2Test_473, OverlappingAtoms_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("abcdef", opts, &id);
  f.Add("abcxyz", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("abcdef");
  EXPECT_EQ(match, 0);

  match = f.SlowFirstMatch("abcxyz");
  EXPECT_EQ(match, 1);
}

// Test Compile on moved-from object doesn't crash
TEST_F(FilteredRE2Test_473, MoveAndCompile_473) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("test", opts, &id);

  FilteredRE2 f2(std::move(f));

  std::vector<std::string> atoms;
  f2.Compile(&atoms);

  int match = f2.SlowFirstMatch("test");
  EXPECT_EQ(match, 0);
}

}  // namespace re2
