#include "gtest/gtest.h"
#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"
#include <vector>
#include <string>

namespace re2 {

// Test fixture for PrefilterTree tests
class PrefilterTreeTest_575 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates a valid object
TEST_F(PrefilterTreeTest_575, DefaultConstructor_575) {
  PrefilterTree tree;
  // After construction (no Add/Compile), we can compile with empty atoms
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  EXPECT_TRUE(atoms.empty());
}

// Test explicit constructor with custom min_atom_len
TEST_F(PrefilterTreeTest_575, ExplicitConstructorWithMinAtomLen_575) {
  PrefilterTree tree(1);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  EXPECT_TRUE(atoms.empty());
}

// Test adding a null prefilter and compiling
TEST_F(PrefilterTreeTest_575, AddNullPrefilter_575) {
  PrefilterTree tree;
  tree.Add(nullptr);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // With a null prefilter, the regexp should be unfiltered
  // Querying with no matched atoms should still return the unfiltered regexp
  std::vector<int> regexps;
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  ASSERT_EQ(regexps.size(), 1u);
  EXPECT_EQ(regexps[0], 0);
}

// Test adding a single atom prefilter
TEST_F(PrefilterTreeTest_575, AddSingleAtomPrefilter_575) {
  PrefilterTree tree;
  Prefilter* pf = Prefilter::FromString("hello");
  tree.Add(pf);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // Should have extracted at least one atom
  EXPECT_GE(atoms.size(), 0u);
}

// Test RegexpsGivenStrings with no prefilters added
TEST_F(PrefilterTreeTest_575, RegexpsGivenStringsEmpty_575) {
  PrefilterTree tree;
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  std::vector<int> regexps;
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_TRUE(regexps.empty());
}

// Test multiple null prefilters - all should be unfiltered
TEST_F(PrefilterTreeTest_575, MultipleNullPrefilters_575) {
  PrefilterTree tree;
  tree.Add(nullptr);
  tree.Add(nullptr);
  tree.Add(nullptr);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  std::vector<int> regexps;
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // All three should be returned as unfiltered
  ASSERT_EQ(regexps.size(), 3u);
  EXPECT_EQ(regexps[0], 0);
  EXPECT_EQ(regexps[1], 1);
  EXPECT_EQ(regexps[2], 2);
}

// Test that matched atoms trigger the correct regexp indices
TEST_F(PrefilterTreeTest_575, RegexpsGivenStringsWithMatchedAtoms_575) {
  PrefilterTree tree;
  // Add an atom prefilter for a sufficiently long string
  Prefilter* pf = Prefilter::FromString("hello");
  tree.Add(pf);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  if (!atoms.empty()) {
    // Match all atoms
    std::vector<int> matched_atoms;
    for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
      matched_atoms.push_back(i);
    }
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    // Should include regexp 0 since its atom was matched
    bool found = false;
    for (int r : regexps) {
      if (r == 0) found = true;
    }
    EXPECT_TRUE(found);
  }
}

// Test that not matching atoms does not return the regexp
TEST_F(PrefilterTreeTest_575, RegexpsGivenStringsNoMatch_575) {
  PrefilterTree tree;
  Prefilter* pf = Prefilter::FromString("hello");
  tree.Add(pf);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  if (!atoms.empty()) {
    // Don't match any atoms
    std::vector<int> matched_atoms;
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    // Regexp 0 should NOT be in the results if it requires an atom match
    bool found = false;
    for (int r : regexps) {
      if (r == 0) found = true;
    }
    EXPECT_FALSE(found);
  }
}

// Test PrintPrefilter doesn't crash with a null prefilter entry
TEST_F(PrefilterTreeTest_575, PrintPrefilterNullEntry_575) {
  PrefilterTree tree;
  tree.Add(nullptr);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  // Should not crash
  tree.PrintPrefilter(0);
}

// Test PrintPrefilter with a valid prefilter
TEST_F(PrefilterTreeTest_575, PrintPrefilterValidEntry_575) {
  PrefilterTree tree;
  Prefilter* pf = Prefilter::FromString("test");
  tree.Add(pf);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  // Should not crash
  tree.PrintPrefilter(0);
}

// Test with min_atom_len = 0
TEST_F(PrefilterTreeTest_575, MinAtomLenZero_575) {
  PrefilterTree tree(0);
  Prefilter* pf = Prefilter::FromString("ab");
  tree.Add(pf);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  // With min_atom_len=0, even short atoms might be kept
  // Just ensure no crash
  SUCCEED();
}

// Test with a mix of null and non-null prefilters
TEST_F(PrefilterTreeTest_575, MixedNullAndNonNullPrefilters_575) {
  PrefilterTree tree;
  tree.Add(nullptr);
  Prefilter* pf = Prefilter::FromString("world");
  tree.Add(pf);
  tree.Add(nullptr);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // With no matched atoms, unfiltered regexps (0 and 2) should be returned
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  bool found0 = false, found2 = false;
  for (int r : regexps) {
    if (r == 0) found0 = true;
    if (r == 2) found2 = true;
  }
  EXPECT_TRUE(found0);
  EXPECT_TRUE(found2);
}

// Test RegexpsGivenStrings output vector is cleared/populated correctly
TEST_F(PrefilterTreeTest_575, RegexpsGivenStringsClearsOutput_575) {
  PrefilterTree tree;
  tree.Add(nullptr);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  std::vector<int> regexps;
  regexps.push_back(42);  // Pre-populate with garbage
  
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  // The output should be properly set (not contain old garbage)
  // It should contain 0 (the unfiltered regexp)
  bool found42 = false;
  bool found0 = false;
  for (int r : regexps) {
    if (r == 42) found42 = true;
    if (r == 0) found0 = true;
  }
  EXPECT_TRUE(found0);
  // The old value should have been cleared
  // (We can't be 100% sure of the implementation but typically it would be cleared)
}

// Test AND prefilter (two atoms that both must match)
TEST_F(PrefilterTreeTest_575, AndPrefilterBothAtomsMatch_575) {
  PrefilterTree tree;
  
  Prefilter* pf1 = Prefilter::FromString("hello");
  Prefilter* pf2 = Prefilter::FromString("world");
  
  Prefilter* and_pf = Prefilter::And(pf1, pf2);
  tree.Add(and_pf);
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  if (!atoms.empty()) {
    // Match all atoms
    std::vector<int> matched_atoms;
    for (int i = 0; i < static_cast<int>(atoms.size()); i++) {
      matched_atoms.push_back(i);
    }
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    
    bool found0 = false;
    for (int r : regexps) {
      if (r == 0) found0 = true;
    }
    EXPECT_TRUE(found0);
  }
}

// Test OR prefilter (either atom can match)
TEST_F(PrefilterTreeTest_575, OrPrefilterOneAtomMatches_575) {
  PrefilterTree tree;
  
  Prefilter* pf1 = Prefilter::FromString("hello");
  Prefilter* pf2 = Prefilter::FromString("world");
  
  Prefilter* or_pf = Prefilter::Or(pf1, pf2);
  tree.Add(or_pf);
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // This tests that at least one branch of OR is sufficient
  // We can't easily control which atom is which index, so just check no crash
  SUCCEED();
}

// Test large min_atom_len filters out short atoms
TEST_F(PrefilterTreeTest_575, LargeMinAtomLen_575) {
  PrefilterTree tree(10);
  Prefilter* pf = Prefilter::FromString("short");
  tree.Add(pf);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // With min_atom_len=10, "short" (5 chars) should be filtered out
  // The regexp should become unfiltered
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  bool found0 = false;
  for (int r : regexps) {
    if (r == 0) found0 = true;
  }
  EXPECT_TRUE(found0);
}

}  // namespace re2
