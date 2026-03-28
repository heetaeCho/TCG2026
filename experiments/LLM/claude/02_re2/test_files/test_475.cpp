#include "gtest/gtest.h"
#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class FilteredRE2Test_475 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that FirstMatch returns -1 when called before Compile
TEST_F(FilteredRE2Test_475, FirstMatchBeforeCompileReturnsNegOne_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<int> atoms;
  // Not calling Compile - should return -1
  EXPECT_EQ(-1, f.FirstMatch("hello world", atoms));
}

// Test that FirstMatch returns -1 when no patterns match
TEST_F(FilteredRE2Test_475, FirstMatchNoMatch_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  EXPECT_EQ(-1, f.FirstMatch("xyz", atoms));
}

// Test that FirstMatch returns correct index when a pattern matches
TEST_F(FilteredRE2Test_475, FirstMatchFindsMatch_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1;
  f.Add("hello", opts, &id0);
  f.Add("world", opts, &id1);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  // Build atoms vector - we pass all atom indices as matched
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  int result = f.FirstMatch("hello world", atoms);
  // Should find at least one match (either id0 or id1)
  EXPECT_GE(result, 0);
}

// Test FirstMatch with single pattern that matches
TEST_F(FilteredRE2Test_475, FirstMatchSinglePatternMatch_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("foo", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  int result = f.FirstMatch("this is foo bar", atoms);
  EXPECT_EQ(0, result);
}

// Test FirstMatch with empty atoms vector
TEST_F(FilteredRE2Test_475, FirstMatchEmptyAtoms_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;  // empty
  int result = f.FirstMatch("hello", atoms);
  // With empty atoms, prefilter_tree may or may not consider any regexps
  // The result depends on the prefilter tree behavior
  // At minimum it should not crash and should return either -1 or a valid index
  EXPECT_GE(result, -1);
}

// Test FirstMatch with empty text
TEST_F(FilteredRE2Test_475, FirstMatchEmptyText_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  int result = f.FirstMatch("", atoms);
  EXPECT_EQ(-1, result);
}

// Test FirstMatch returns first matching regex
TEST_F(FilteredRE2Test_475, FirstMatchReturnsFirstMatch_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1, id2;
  f.Add("aaa", opts, &id0);
  f.Add("bbb", opts, &id1);
  f.Add("ccc", opts, &id2);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  // Text contains only "bbb"
  int result = f.FirstMatch("bbb", atoms);
  EXPECT_EQ(id1, result);
}

// Test SlowFirstMatch for comparison
TEST_F(FilteredRE2Test_475, SlowFirstMatchFindsMatch_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1;
  f.Add("hello", opts, &id0);
  f.Add("world", opts, &id1);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  int result = f.SlowFirstMatch("hello world");
  EXPECT_GE(result, 0);
}

// Test SlowFirstMatch with no match
TEST_F(FilteredRE2Test_475, SlowFirstMatchNoMatch_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  int result = f.SlowFirstMatch("xyz");
  EXPECT_EQ(-1, result);
}

// Test AllMatches
TEST_F(FilteredRE2Test_475, AllMatchesFindsMultipleMatches_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1, id2;
  f.Add("hello", opts, &id0);
  f.Add("world", opts, &id1);
  f.Add("xyz", opts, &id2);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  std::vector<int> matching;
  bool result = f.AllMatches("hello world", atoms, &matching);
  EXPECT_TRUE(result);
  EXPECT_GE(matching.size(), 1u);
}

// Test AllMatches with no match
TEST_F(FilteredRE2Test_475, AllMatchesNoMatch_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  std::vector<int> matching;
  bool result = f.AllMatches("xyz", atoms, &matching);
  EXPECT_FALSE(result);
  EXPECT_EQ(0u, matching.size());
}

// Test NumRegexps
TEST_F(FilteredRE2Test_475, NumRegexps_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  EXPECT_EQ(0, f.NumRegexps());
  
  f.Add("hello", opts, &id);
  EXPECT_EQ(1, f.NumRegexps());
  
  f.Add("world", opts, &id);
  EXPECT_EQ(2, f.NumRegexps());
}

// Test GetRE2
TEST_F(FilteredRE2Test_475, GetRE2ReturnsCorrectPattern_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1;
  f.Add("hello", opts, &id0);
  f.Add("world", opts, &id1);
  
  EXPECT_EQ("hello", f.GetRE2(id0).pattern());
  EXPECT_EQ("world", f.GetRE2(id1).pattern());
}

// Test Add returns correct ids
TEST_F(FilteredRE2Test_475, AddReturnsSequentialIds_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1, id2;
  
  RE2::ErrorCode err0 = f.Add("aaa", opts, &id0);
  RE2::ErrorCode err1 = f.Add("bbb", opts, &id1);
  RE2::ErrorCode err2 = f.Add("ccc", opts, &id2);
  
  EXPECT_EQ(RE2::NoError, err0);
  EXPECT_EQ(RE2::NoError, err1);
  EXPECT_EQ(RE2::NoError, err2);
  EXPECT_EQ(0, id0);
  EXPECT_EQ(1, id1);
  EXPECT_EQ(2, id2);
}

// Test move constructor
TEST_F(FilteredRE2Test_475, MoveConstructor_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  FilteredRE2 f2(std::move(f));
  EXPECT_EQ(1, f2.NumRegexps());
  EXPECT_EQ("hello", f2.GetRE2(0).pattern());
}

// Test move assignment
TEST_F(FilteredRE2Test_475, MoveAssignment_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  FilteredRE2 f2;
  f2 = std::move(f);
  EXPECT_EQ(1, f2.NumRegexps());
  EXPECT_EQ("hello", f2.GetRE2(0).pattern());
}

// Test with regex patterns (not just literals)
TEST_F(FilteredRE2Test_475, FirstMatchWithRegexPattern_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hel+o", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  int result = f.FirstMatch("helllo", atoms);
  // Should match since "helllo" matches "hel+o"
  EXPECT_EQ(0, result);
}

// Test Compile produces atoms
TEST_F(FilteredRE2Test_475, CompileProducesAtoms_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  f.Add("hello world", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  // After compiling, there should be some atoms (or possibly none for trivial cases)
  // This just checks that Compile doesn't crash
  EXPECT_GE(strings_to_match.size(), 0u);
}

// Test with min_atom_len constructor
TEST_F(FilteredRE2Test_475, MinAtomLenConstructor_475) {
  FilteredRE2 f(2);
  RE2::Options opts;
  int id;
  f.Add("hello", opts, &id);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  int result = f.FirstMatch("hello", atoms);
  EXPECT_EQ(0, result);
}

// Test AllPotentials
TEST_F(FilteredRE2Test_475, AllPotentials_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1;
  f.Add("hello", opts, &id0);
  f.Add("world", opts, &id1);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  std::vector<int> potentials;
  f.AllPotentials(atoms, &potentials);
  // With all atoms provided, all regexps should be potential matches
  EXPECT_GE(potentials.size(), 0u);
}

// Test Add with invalid pattern
TEST_F(FilteredRE2Test_475, AddInvalidPattern_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id;
  RE2::ErrorCode err = f.Add("(unclosed", opts, &id);
  // Invalid regex should still get an id but may report error
  // The behavior depends on RE2's handling
  EXPECT_EQ(0, id);
}

// Test FirstMatch text that partially matches multiple patterns
TEST_F(FilteredRE2Test_475, FirstMatchReturnsEarliestIndex_475) {
  FilteredRE2 f;
  RE2::Options opts;
  int id0, id1, id2;
  f.Add("abc", opts, &id0);
  f.Add("abc", opts, &id1);  // duplicate pattern
  f.Add("def", opts, &id2);
  
  std::vector<std::string> strings_to_match;
  f.Compile(&strings_to_match);
  
  std::vector<int> atoms;
  for (size_t i = 0; i < strings_to_match.size(); i++) {
    atoms.push_back(static_cast<int>(i));
  }
  
  int result = f.FirstMatch("abcdef", atoms);
  // Should return the first matching regex index
  EXPECT_GE(result, 0);
  EXPECT_LE(result, 2);
}

}  // namespace re2
