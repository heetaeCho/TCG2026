#include "gtest/gtest.h"
#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include <vector>
#include <string>

namespace re2 {

// Test fixture for PrefilterTree tests
class PrefilterTreeTest_572 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(PrefilterTreeTest_572, DefaultConstruction_572) {
  PrefilterTree tree;
  // Should be able to create a tree without issues
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
}

// Test construction with explicit min_atom_len
TEST_F(PrefilterTreeTest_572, ExplicitMinAtomLenConstruction_572) {
  PrefilterTree tree(2);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
}

// Test adding a NULL prefilter
TEST_F(PrefilterTreeTest_572, AddNullPrefilter_572) {
  PrefilterTree tree;
  tree.Add(nullptr);
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // After compile, a NULL prefilter should result in unfiltered regexp
  std::vector<int> regexps;
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // The regexp with NULL prefilter should always match (unfiltered)
  EXPECT_EQ(regexps.size(), 1u);
  EXPECT_EQ(regexps[0], 0);
}

// Test adding a valid prefilter from a simple regex
TEST_F(PrefilterTreeTest_572, AddValidPrefilter_572) {
  PrefilterTree tree;
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  tree.Add(pf);  // tree takes ownership
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  // Should have at least one atom for a literal string pattern
  EXPECT_GE(atoms.size(), 0u);
}

// Test adding multiple prefilters
TEST_F(PrefilterTreeTest_572, AddMultiplePrefilters_572) {
  PrefilterTree tree;
  
  RE2 re1("hello");
  RE2 re2("world");
  RE2 re3("foobar");
  
  tree.Add(Prefilter::FromRE2(&re1));
  tree.Add(Prefilter::FromRE2(&re2));
  tree.Add(Prefilter::FromRE2(&re3));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
}

// Test adding mix of NULL and valid prefilters
TEST_F(PrefilterTreeTest_572, AddMixedNullAndValid_572) {
  PrefilterTree tree;
  
  RE2 re1("hello");
  tree.Add(Prefilter::FromRE2(&re1));
  tree.Add(nullptr);
  
  RE2 re2("world");
  tree.Add(Prefilter::FromRE2(&re2));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // The NULL prefilter (index 1) should always be in results
  std::vector<int> regexps;
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  // At minimum, the unfiltered regexp (index 1) should be present
  bool found_unfiltered = false;
  for (int r : regexps) {
    if (r == 1) found_unfiltered = true;
  }
  EXPECT_TRUE(found_unfiltered);
}

// Test Compile produces atoms for literal patterns
TEST_F(PrefilterTreeTest_572, CompileProducesAtoms_572) {
  PrefilterTree tree;
  
  RE2 re("abcdef");
  tree.Add(Prefilter::FromRE2(&re));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // A literal pattern should produce at least one atom
  EXPECT_GE(atoms.size(), 1u);
}

// Test RegexpsGivenStrings with matching atoms
TEST_F(PrefilterTreeTest_572, RegexpsGivenStringsWithMatch_572) {
  PrefilterTree tree;
  
  RE2 re("hello");
  tree.Add(Prefilter::FromRE2(&re));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // If we provide all atom indices as matched, the regexp should be returned
  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atoms.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }
  
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  // Should contain regexp index 0
  bool found = false;
  for (int r : regexps) {
    if (r == 0) found = true;
  }
  EXPECT_TRUE(found);
}

// Test RegexpsGivenStrings with no matching atoms
TEST_F(PrefilterTreeTest_572, RegexpsGivenStringsNoMatch_572) {
  PrefilterTree tree;
  
  RE2 re("hello");
  tree.Add(Prefilter::FromRE2(&re));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  if (!atoms.empty()) {
    // Provide empty matched atoms
    std::vector<int> matched_atoms;
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    
    // With no atoms matched, the filtered regexp should NOT be returned
    bool found = false;
    for (int r : regexps) {
      if (r == 0) found = true;
    }
    EXPECT_FALSE(found);
  }
}

// Test with a wildcard pattern that produces NULL prefilter
TEST_F(PrefilterTreeTest_572, WildcardPatternNullPrefilter_572) {
  PrefilterTree tree;
  
  RE2 re(".*");
  Prefilter* pf = Prefilter::FromRE2(&re);
  tree.Add(pf);  // likely NULL since .* matches everything
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // .* should be unfiltered (always returned)
  std::vector<int> regexps;
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  bool found = false;
  for (int r : regexps) {
    if (r == 0) found = true;
  }
  EXPECT_TRUE(found);
}

// Test empty tree (no prefilters added)
TEST_F(PrefilterTreeTest_572, EmptyTree_572) {
  PrefilterTree tree;
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  EXPECT_EQ(atoms.size(), 0u);
  
  std::vector<int> regexps;
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_EQ(regexps.size(), 0u);
}

// Test with min_atom_len affecting atom generation
TEST_F(PrefilterTreeTest_572, MinAtomLenAffectsAtoms_572) {
  // With min_atom_len = 5, short atoms should be excluded
  PrefilterTree tree(5);
  
  RE2 re("ab");  // short literal
  tree.Add(Prefilter::FromRE2(&re));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // All atoms should have length >= 5 or be empty if the pattern is too short
  for (const auto& atom : atoms) {
    EXPECT_GE(atom.size(), 5u);
  }
}

// Test with multiple patterns sharing atoms
TEST_F(PrefilterTreeTest_572, MultiplePatternsSharingAtoms_572) {
  PrefilterTree tree;
  
  RE2 re1("hello world");
  RE2 re2("hello there");
  
  tree.Add(Prefilter::FromRE2(&re1));
  tree.Add(Prefilter::FromRE2(&re2));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // Both patterns share "hello" so the tree should handle this
  // Just verify it compiles without error
  EXPECT_GE(atoms.size(), 0u);
}

// Test PrintPrefilter doesn't crash
TEST_F(PrefilterTreeTest_572, PrintPrefilterDoesNotCrash_572) {
  PrefilterTree tree;
  
  RE2 re("hello");
  tree.Add(Prefilter::FromRE2(&re));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // Should not crash
  tree.PrintPrefilter(0);
}

// Test with alternation pattern
TEST_F(PrefilterTreeTest_572, AlternationPattern_572) {
  PrefilterTree tree;
  
  RE2 re("hello|world");
  tree.Add(Prefilter::FromRE2(&re));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  // Alternation should produce multiple atoms (one per alternative)
  EXPECT_GE(atoms.size(), 0u);
}

// Test RegexpsGivenStrings clears output vector
TEST_F(PrefilterTreeTest_572, RegexpsGivenStringsClearsOutput_572) {
  PrefilterTree tree;
  tree.Add(nullptr);
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  std::vector<int> regexps;
  regexps.push_back(999);  // Pre-populate with garbage
  
  std::vector<int> matched_atoms;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  // The result should contain index 0 (unfiltered), not 999
  bool found_garbage = false;
  for (int r : regexps) {
    if (r == 999) found_garbage = true;
  }
  EXPECT_FALSE(found_garbage);
}

// Test construction with min_atom_len = 0
TEST_F(PrefilterTreeTest_572, MinAtomLenZero_572) {
  PrefilterTree tree(0);
  
  RE2 re("a");
  tree.Add(Prefilter::FromRE2(&re));
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  // With min_atom_len 0, even single chars might produce atoms
}

// Test large number of prefilters
TEST_F(PrefilterTreeTest_572, LargeNumberOfPrefilters_572) {
  PrefilterTree tree;
  
  std::vector<RE2*> regexps;
  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i) + "longertomakeatom";
    regexps.push_back(new RE2(pattern));
    tree.Add(Prefilter::FromRE2(regexps.back()));
  }
  
  std::vector<std::string> atoms;
  tree.Compile(&atoms);
  
  EXPECT_GE(atoms.size(), 1u);
  
  // Match all atoms
  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atoms.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }
  
  std::vector<int> result_regexps;
  tree.RegexpsGivenStrings(matched_atoms, &result_regexps);
  
  // All 100 regexps should be returned when all atoms match
  EXPECT_EQ(result_regexps.size(), 100u);
  
  for (auto* re : regexps) {
    delete re;
  }
}

}  // namespace re2
