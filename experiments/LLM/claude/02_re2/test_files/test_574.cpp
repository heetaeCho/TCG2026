#include "gtest/gtest.h"
#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"
#include <vector>
#include <string>
#include <algorithm>

namespace re2 {

// Test fixture for PrefilterTree tests
class PrefilterTreeTest_574 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default constructor creates a valid PrefilterTree
TEST_F(PrefilterTreeTest_574, DefaultConstructor_574) {
  PrefilterTree tree;
  // Should be able to create without crashing
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  // Before compile, with no prefilters added, should return empty
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_TRUE(regexps.empty());
}

// Test: Constructor with min_atom_len parameter
TEST_F(PrefilterTreeTest_574, ConstructorWithMinAtomLen_574) {
  PrefilterTree tree(4);
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_TRUE(regexps.empty());
}

// Test: RegexpsGivenStrings on empty tree (no prefilters, not compiled)
TEST_F(PrefilterTreeTest_574, EmptyTreeNotCompiled_574) {
  PrefilterTree tree;
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_TRUE(regexps.empty());
}

// Test: RegexpsGivenStrings clears the output vector
TEST_F(PrefilterTreeTest_574, RegexpsGivenStringsClearsOutput_574) {
  PrefilterTree tree;
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  regexps.push_back(42);
  regexps.push_back(99);
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_TRUE(regexps.empty());
}

// Test: Add a null prefilter and compile - should be unfiltered
TEST_F(PrefilterTreeTest_574, AddNullPrefilterAndCompile_574) {
  PrefilterTree tree;
  tree.Add(nullptr);  // null prefilter means the regex is unfiltered
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // Null prefilter should make regex 0 unfiltered, so it always matches
  ASSERT_EQ(regexps.size(), 1u);
  EXPECT_EQ(regexps[0], 0);
}

// Test: Add multiple null prefilters - all should be unfiltered
TEST_F(PrefilterTreeTest_574, AddMultipleNullPrefilters_574) {
  PrefilterTree tree;
  tree.Add(nullptr);
  tree.Add(nullptr);
  tree.Add(nullptr);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  ASSERT_EQ(regexps.size(), 3u);
  EXPECT_EQ(regexps[0], 0);
  EXPECT_EQ(regexps[1], 1);
  EXPECT_EQ(regexps[2], 2);
}

// Test: Add an atom prefilter, compile, and match it
TEST_F(PrefilterTreeTest_574, AddAtomPrefilterAndMatch_574) {
  PrefilterTree tree;
  // Create an atom prefilter for "hello"
  Prefilter* pf = Prefilter::FromString("hello");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Find the atom index for "hello"
  int atom_index = -1;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    if (atom_vec[i] == "hello") {
      atom_index = static_cast<int>(i);
      break;
    }
  }

  if (atom_index >= 0) {
    std::vector<int> matched_atoms;
    matched_atoms.push_back(atom_index);
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    // Should match regex 0
    ASSERT_GE(regexps.size(), 1u);
    EXPECT_TRUE(std::find(regexps.begin(), regexps.end(), 0) != regexps.end());
  }
}

// Test: Add an atom prefilter, compile, and don't match it
TEST_F(PrefilterTreeTest_574, AddAtomPrefilterNoMatch_574) {
  PrefilterTree tree;
  Prefilter* pf = Prefilter::FromString("hello");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Don't pass any matched atoms
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // Should not match regex 0 (unless it's unfiltered)
  // With an atom prefilter, it should require the atom to match
  EXPECT_TRUE(std::find(regexps.begin(), regexps.end(), 0) == regexps.end());
}

// Test: Compiled tree with empty matched_atoms returns only unfiltered
TEST_F(PrefilterTreeTest_574, CompiledTreeEmptyMatchedAtoms_574) {
  PrefilterTree tree;
  Prefilter* pf = Prefilter::FromString("test");
  tree.Add(pf);
  tree.Add(nullptr);  // regex 1 is unfiltered
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // Only regex 1 (unfiltered) should appear
  ASSERT_EQ(regexps.size(), 1u);
  EXPECT_EQ(regexps[0], 1);
}

// Test: Output is sorted
TEST_F(PrefilterTreeTest_574, OutputIsSorted_574) {
  PrefilterTree tree;
  tree.Add(nullptr);
  tree.Add(nullptr);
  tree.Add(nullptr);
  tree.Add(nullptr);
  tree.Add(nullptr);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  ASSERT_EQ(regexps.size(), 5u);
  EXPECT_TRUE(std::is_sorted(regexps.begin(), regexps.end()));
}

// Test: Not compiled with prefilters added returns all indices
TEST_F(PrefilterTreeTest_574, NotCompiledWithPrefiltersReturnsAll_574) {
  PrefilterTree tree;
  // We can't easily test the "not compiled but has prefilters" path
  // because Add takes ownership and the prefilter_vec_ is populated.
  // We'd need to Add prefilters without calling Compile.
  // This tests the error logging path.
  Prefilter* pf1 = Prefilter::FromString("abc");
  Prefilter* pf2 = Prefilter::FromString("def");
  tree.Add(pf1);
  tree.Add(pf2);
  // Don't compile - this should trigger error log and return all indices
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  ASSERT_EQ(regexps.size(), 2u);
  EXPECT_EQ(regexps[0], 0);
  EXPECT_EQ(regexps[1], 1);
}

// Test: Mix of atom prefilters and null prefilters
TEST_F(PrefilterTreeTest_574, MixedPrefilters_574) {
  PrefilterTree tree;
  Prefilter* pf0 = Prefilter::FromString("alpha");
  tree.Add(pf0);            // regex 0: has atom
  tree.Add(nullptr);         // regex 1: unfiltered
  Prefilter* pf2 = Prefilter::FromString("beta");
  tree.Add(pf2);            // regex 2: has atom
  tree.Add(nullptr);         // regex 3: unfiltered

  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Match only one atom
  int alpha_index = -1;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    if (atom_vec[i] == "alpha") {
      alpha_index = static_cast<int>(i);
      break;
    }
  }

  std::vector<int> matched_atoms;
  if (alpha_index >= 0) {
    matched_atoms.push_back(alpha_index);
  }
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);

  // Should contain unfiltered regexps (1 and 3) at minimum
  EXPECT_TRUE(std::find(regexps.begin(), regexps.end(), 1) != regexps.end());
  EXPECT_TRUE(std::find(regexps.begin(), regexps.end(), 3) != regexps.end());

  // If alpha matched, regex 0 should also be present
  if (alpha_index >= 0) {
    EXPECT_TRUE(std::find(regexps.begin(), regexps.end(), 0) != regexps.end());
  }

  // Result should be sorted
  EXPECT_TRUE(std::is_sorted(regexps.begin(), regexps.end()));
}

// Test: Compile produces atoms in atom_vec
TEST_F(PrefilterTreeTest_574, CompileProducesAtoms_574) {
  PrefilterTree tree;
  Prefilter* pf = Prefilter::FromString("teststring");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  // After compiling with an atom prefilter, atom_vec should have at least one entry
  EXPECT_GE(atom_vec.size(), 1u);
}

// Test: Compile with no prefilters produces empty atom_vec
TEST_F(PrefilterTreeTest_574, CompileNoPrefiltersEmptyAtoms_574) {
  PrefilterTree tree;
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  EXPECT_TRUE(atom_vec.empty());
}

// Test: Compile with only null prefilters produces empty atom_vec
TEST_F(PrefilterTreeTest_574, CompileOnlyNullPrefiltersEmptyAtoms_574) {
  PrefilterTree tree;
  tree.Add(nullptr);
  tree.Add(nullptr);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  EXPECT_TRUE(atom_vec.empty());
}

// Test: RegexpsGivenStrings called multiple times on compiled tree
TEST_F(PrefilterTreeTest_574, MultipleCallsToRegexpsGivenStrings_574) {
  PrefilterTree tree;
  tree.Add(nullptr);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  for (int i = 0; i < 5; i++) {
    std::vector<int> matched_atoms;
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    ASSERT_EQ(regexps.size(), 1u);
    EXPECT_EQ(regexps[0], 0);
  }
}

// Test: All atoms matched should return all filtered regexps
TEST_F(PrefilterTreeTest_574, AllAtomsMatched_574) {
  PrefilterTree tree;
  Prefilter* pf0 = Prefilter::FromString("aaa");
  Prefilter* pf1 = Prefilter::FromString("bbb");
  tree.Add(pf0);
  tree.Add(pf1);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Match all atoms
  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // Both regexps should be matched
  EXPECT_TRUE(std::find(regexps.begin(), regexps.end(), 0) != regexps.end());
  EXPECT_TRUE(std::find(regexps.begin(), regexps.end(), 1) != regexps.end());
  EXPECT_TRUE(std::is_sorted(regexps.begin(), regexps.end()));
}

}  // namespace re2
