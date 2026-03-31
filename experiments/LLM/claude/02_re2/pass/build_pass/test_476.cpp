#include "gtest/gtest.h"
#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class FilteredRE2Test_476 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction of FilteredRE2
TEST_F(FilteredRE2Test_476, DefaultConstruction_476) {
  FilteredRE2 f;
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test construction with min_atom_len
TEST_F(FilteredRE2Test_476, ConstructionWithMinAtomLen_476) {
  FilteredRE2 f(4);
  EXPECT_EQ(f.NumRegexps(), 0);
}

// Test adding a single pattern
TEST_F(FilteredRE2Test_476, AddSinglePattern_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  RE2::ErrorCode err = f.Add("hello", opts, &id);
  EXPECT_EQ(err, RE2::NoError);
  EXPECT_EQ(id, 0);
  EXPECT_EQ(f.NumRegexps(), 1);
}

// Test adding multiple patterns
TEST_F(FilteredRE2Test_476, AddMultiplePatterns_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  EXPECT_EQ(f.Add("hello", opts, &id), RE2::NoError);
  EXPECT_EQ(id, 0);

  EXPECT_EQ(f.Add("world", opts, &id), RE2::NoError);
  EXPECT_EQ(id, 1);

  EXPECT_EQ(f.Add("foo.*bar", opts, &id), RE2::NoError);
  EXPECT_EQ(id, 2);

  EXPECT_EQ(f.NumRegexps(), 3);
}

// Test Compile produces atom strings
TEST_F(FilteredRE2Test_476, CompileProducesAtoms_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);
  // After compile, atoms may or may not be empty depending on patterns
  // but the system should not crash
  EXPECT_GE(f.NumRegexps(), 2);
}

// Test GetRE2 returns valid reference
TEST_F(FilteredRE2Test_476, GetRE2ReturnsValidPattern_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  std::vector<std::string> atoms;
  f.Compile(&atoms);

  const RE2& re = f.GetRE2(0);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

// Test SlowFirstMatch with matching text
TEST_F(FilteredRE2Test_476, SlowFirstMatchFindsMatch_476) {
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

// Test SlowFirstMatch with non-matching text
TEST_F(FilteredRE2Test_476, SlowFirstMatchNoMatch_476) {
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

// Test AllMatches with atoms that lead to matches
TEST_F(FilteredRE2Test_476, AllMatchesFindsMultipleMatches_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);
  f.Add("nothere", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Build atom indices - we need to figure out which atoms match.
  // For a proper test, use SlowFirstMatch to confirm, then test AllMatches
  // with all atom indices provided.
  std::vector<int> atom_ids;
  for (size_t i = 0; i < atoms.size(); i++) {
    atom_ids.push_back(static_cast<int>(i));
  }

  std::vector<int> matching;
  bool found = f.AllMatches("hello world", atom_ids, &matching);

  // "hello" and "world" should match "hello world"
  EXPECT_TRUE(found);
  EXPECT_GE(matching.size(), 2u);
}

// Test AllMatches returns false when no matches
TEST_F(FilteredRE2Test_476, AllMatchesNoMatch_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // Provide all atoms but text doesn't match
  std::vector<int> atom_ids;
  for (size_t i = 0; i < atoms.size(); i++) {
    atom_ids.push_back(static_cast<int>(i));
  }

  std::vector<int> matching;
  bool found = f.AllMatches("xyz", atom_ids, &matching);
  EXPECT_FALSE(found);
  EXPECT_TRUE(matching.empty());
}

// Test AllMatches with empty atoms vector
TEST_F(FilteredRE2Test_476, AllMatchesEmptyAtoms_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> empty_atoms;
  std::vector<int> matching;
  bool found = f.AllMatches("hello", empty_atoms, &matching);
  // With no atoms provided, behavior depends on whether patterns are "unfiltered"
  // We just check it doesn't crash and returns a valid result
  (void)found;
}

// Test AllMatches clears the output vector
TEST_F(FilteredRE2Test_476, AllMatchesClearsOutputVector_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> atom_ids;
  for (size_t i = 0; i < atoms.size(); i++) {
    atom_ids.push_back(static_cast<int>(i));
  }

  std::vector<int> matching;
  matching.push_back(999);  // Pre-fill with garbage
  matching.push_back(888);

  f.AllMatches("xyz_no_match", atom_ids, &matching);
  // The output should have been cleared
  // If no match, it should be empty
  // matching should not contain 999 or 888
  for (int m : matching) {
    EXPECT_NE(m, 999);
    EXPECT_NE(m, 888);
  }
}

// Test FirstMatch with atoms
TEST_F(FilteredRE2Test_476, FirstMatchWithAtoms_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> atom_ids;
  for (size_t i = 0; i < atoms.size(); i++) {
    atom_ids.push_back(static_cast<int>(i));
  }

  int match = f.FirstMatch("hello", atom_ids);
  EXPECT_GE(match, 0);
}

// Test FirstMatch returns -1 when no match
TEST_F(FilteredRE2Test_476, FirstMatchNoMatch_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> atom_ids;
  for (size_t i = 0; i < atoms.size(); i++) {
    atom_ids.push_back(static_cast<int>(i));
  }

  int match = f.FirstMatch("xyz", atom_ids);
  EXPECT_EQ(match, -1);
}

// Test AllPotentials
TEST_F(FilteredRE2Test_476, AllPotentials_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> atom_ids;
  for (size_t i = 0; i < atoms.size(); i++) {
    atom_ids.push_back(static_cast<int>(i));
  }

  std::vector<int> potentials;
  f.AllPotentials(atom_ids, &potentials);
  // With all atoms, all regexps should be potential
  EXPECT_GE(potentials.size(), 2u);
}

// Test AllPotentials with empty atoms
TEST_F(FilteredRE2Test_476, AllPotentialsEmptyAtoms_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> empty_atoms;
  std::vector<int> potentials;
  f.AllPotentials(empty_atoms, &potentials);
  // Should not crash; may or may not have potentials
}

// Test move constructor
TEST_F(FilteredRE2Test_476, MoveConstructor_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);
  f.Add("world", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  FilteredRE2 f2(std::move(f));
  EXPECT_EQ(f2.NumRegexps(), 2);
  EXPECT_TRUE(f2.GetRE2(0).ok());
}

// Test move assignment
TEST_F(FilteredRE2Test_476, MoveAssignment_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  FilteredRE2 f2;
  f2 = std::move(f);
  EXPECT_EQ(f2.NumRegexps(), 1);
}

// Test adding invalid pattern
TEST_F(FilteredRE2Test_476, AddInvalidPattern_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  RE2::ErrorCode err = f.Add("[invalid", opts, &id);
  // An invalid pattern should still be added (RE2 handles errors gracefully)
  // but the error code may not be NoError
  // The id should still be assigned
  EXPECT_EQ(id, 0);
}

// Test with regex containing alternation
TEST_F(FilteredRE2Test_476, AlternationPattern_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello|world", opts, &id);
  EXPECT_EQ(id, 0);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("world");
  EXPECT_EQ(match, 0);
}

// Test with empty text
TEST_F(FilteredRE2Test_476, EmptyText_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("");
  EXPECT_EQ(match, -1);
}

// Test with pattern that matches empty string
TEST_F(FilteredRE2Test_476, PatternMatchingEmptyString_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add(".*", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  // .* should match any text including empty
  int match = f.SlowFirstMatch("");
  EXPECT_EQ(match, 0);
}

// Test SlowFirstMatch returns first matching index
TEST_F(FilteredRE2Test_476, SlowFirstMatchReturnsFirst_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("abc", opts, &id);
  f.Add("def", opts, &id);
  f.Add("abc", opts, &id);  // duplicate

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("abc");
  EXPECT_EQ(match, 0);  // Should return the first matching regexp
}

// Test with many patterns
TEST_F(FilteredRE2Test_476, ManyPatterns_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    EXPECT_EQ(f.Add(pattern, opts, &id), RE2::NoError);
    EXPECT_EQ(id, i);
  }

  EXPECT_EQ(f.NumRegexps(), 100);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("pattern42");
  EXPECT_GE(match, 0);
}

// Test that AllMatches returns sorted indices
TEST_F(FilteredRE2Test_476, AllMatchesReturnsSorted_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("test", opts, &id);
  f.Add(".*", opts, &id);
  f.Add("test_string", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  std::vector<int> atom_ids;
  for (size_t i = 0; i < atoms.size(); i++) {
    atom_ids.push_back(static_cast<int>(i));
  }

  std::vector<int> matching;
  f.AllMatches("test_string", atom_ids, &matching);

  // Check that results are in increasing order
  for (size_t i = 1; i < matching.size(); i++) {
    EXPECT_GT(matching[i], matching[i - 1]);
  }
}

// Test with case-insensitive option
TEST_F(FilteredRE2Test_476, CaseInsensitive_476) {
  FilteredRE2 f;
  RE2::Options opts;
  opts.set_case_sensitive(false);
  int id;

  f.Add("hello", opts, &id);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  int match = f.SlowFirstMatch("HELLO");
  EXPECT_EQ(match, 0);
}

// Test NumRegexps after compile
TEST_F(FilteredRE2Test_476, NumRegexpsAfterCompile_476) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;

  f.Add("a", opts, &id);
  f.Add("b", opts, &id);
  f.Add("c", opts, &id);

  EXPECT_EQ(f.NumRegexps(), 3);

  std::vector<std::string> atoms;
  f.Compile(&atoms);

  EXPECT_EQ(f.NumRegexps(), 3);
}

}  // namespace re2
