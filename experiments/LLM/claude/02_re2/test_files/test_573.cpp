#include "gtest/gtest.h"
#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"
#include <vector>
#include <string>

namespace re2 {

class PrefilterTreeTest_573 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(PrefilterTreeTest_573, DefaultConstruction_573) {
  PrefilterTree tree;
  // Should be able to construct without crashing
  std::vector<std::string> atom_vec;
  // Compile on empty tree should work without crashing
  tree.Compile(&atom_vec);
  EXPECT_TRUE(atom_vec.empty());
}

// Test construction with explicit min_atom_len
TEST_F(PrefilterTreeTest_573, ExplicitMinAtomLenConstruction_573) {
  PrefilterTree tree(5);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  EXPECT_TRUE(atom_vec.empty());
}

// Test Compile on empty tree (no prefilters added)
TEST_F(PrefilterTreeTest_573, CompileEmptyTree_573) {
  PrefilterTree tree;
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  EXPECT_TRUE(atom_vec.empty());
}

// Test Add with null prefilter then Compile
TEST_F(PrefilterTreeTest_573, AddNullPrefilter_573) {
  PrefilterTree tree;
  tree.Add(nullptr);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  // After compile, RegexpsGivenStrings with empty atoms should give unfiltered results
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // The null prefilter regexp (id 0) should be in unfiltered set
  EXPECT_FALSE(regexps.empty());
  EXPECT_EQ(regexps[0], 0);
}

// Test Add with an ATOM prefilter then Compile
TEST_F(PrefilterTreeTest_573, AddAtomPrefilter_573) {
  PrefilterTree tree;
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("hello");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  // Should have at least one atom
  EXPECT_FALSE(atom_vec.empty());
  bool found = false;
  for (const auto& a : atom_vec) {
    if (a == "hello") {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test RegexpsGivenStrings when atoms match
TEST_F(PrefilterTreeTest_573, RegexpsGivenStringsMatch_573) {
  PrefilterTree tree;
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("test");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Find the index of "test" in atom_vec
  int test_idx = -1;
  for (int i = 0; i < static_cast<int>(atom_vec.size()); i++) {
    if (atom_vec[i] == "test") {
      test_idx = i;
      break;
    }
  }
  ASSERT_GE(test_idx, 0);

  std::vector<int> matched_atoms = {test_idx};
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // Regexp 0 should match
  ASSERT_FALSE(regexps.empty());
  bool found = false;
  for (int r : regexps) {
    if (r == 0) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test RegexpsGivenStrings when no atoms match
TEST_F(PrefilterTreeTest_573, RegexpsGivenStringsNoMatch_573) {
  PrefilterTree tree;
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("hello");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  std::vector<int> matched_atoms; // empty - no atoms matched
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // Since no atoms matched, regexp 0 should not be reported (unless unfiltered)
  bool found = false;
  for (int r : regexps) {
    if (r == 0) {
      found = true;
      break;
    }
  }
  EXPECT_FALSE(found);
}

// Test multiple prefilters added
TEST_F(PrefilterTreeTest_573, MultiplePrefilters_573) {
  PrefilterTree tree;
  
  Prefilter* pf1 = new Prefilter(Prefilter::ATOM);
  pf1->set_atom("alpha");
  tree.Add(pf1);
  
  Prefilter* pf2 = new Prefilter(Prefilter::ATOM);
  pf2->set_atom("bravo");
  tree.Add(pf2);
  
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  
  // Should have atoms for both
  EXPECT_GE(atom_vec.size(), 2u);
}

// Test RegexpsGivenStrings with multiple prefilters, only one matching
TEST_F(PrefilterTreeTest_573, MultiplePrefiltersPartialMatch_573) {
  PrefilterTree tree;
  
  Prefilter* pf1 = new Prefilter(Prefilter::ATOM);
  pf1->set_atom("alpha");
  tree.Add(pf1);
  
  Prefilter* pf2 = new Prefilter(Prefilter::ATOM);
  pf2->set_atom("bravo");
  tree.Add(pf2);
  
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  
  // Find index of "alpha"
  int alpha_idx = -1;
  for (int i = 0; i < static_cast<int>(atom_vec.size()); i++) {
    if (atom_vec[i] == "alpha") {
      alpha_idx = i;
      break;
    }
  }
  ASSERT_GE(alpha_idx, 0);
  
  std::vector<int> matched_atoms = {alpha_idx};
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  // Regexp 0 (alpha) should be in results
  bool found_0 = false;
  bool found_1 = false;
  for (int r : regexps) {
    if (r == 0) found_0 = true;
    if (r == 1) found_1 = true;
  }
  EXPECT_TRUE(found_0);
  EXPECT_FALSE(found_1);
}

// Test adding null prefilter makes it unfiltered
TEST_F(PrefilterTreeTest_573, NullPrefilterAlwaysMatches_573) {
  PrefilterTree tree;
  
  // Add a real prefilter
  Prefilter* pf1 = new Prefilter(Prefilter::ATOM);
  pf1->set_atom("hello");
  tree.Add(pf1);
  
  // Add a null prefilter - should always match
  tree.Add(nullptr);
  
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  
  // Even with no matched atoms, regexp 1 (null prefilter) should match
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  bool found_1 = false;
  for (int r : regexps) {
    if (r == 1) {
      found_1 = true;
      break;
    }
  }
  EXPECT_TRUE(found_1);
}

// Test Compile with AND prefilter
TEST_F(PrefilterTreeTest_573, AndPrefilter_573) {
  PrefilterTree tree;
  
  Prefilter* a1 = new Prefilter(Prefilter::ATOM);
  a1->set_atom("foo");
  Prefilter* a2 = new Prefilter(Prefilter::ATOM);
  a2->set_atom("bar");
  
  Prefilter* and_pf = new Prefilter(Prefilter::AND);
  and_pf->subs()->push_back(a1);
  and_pf->subs()->push_back(a2);
  
  tree.Add(and_pf);
  
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  
  // Both "foo" and "bar" should appear as atoms
  EXPECT_GE(atom_vec.size(), 2u);
}

// Test AND prefilter requires all atoms to match
TEST_F(PrefilterTreeTest_573, AndPrefilterRequiresAllAtoms_573) {
  PrefilterTree tree;
  
  Prefilter* a1 = new Prefilter(Prefilter::ATOM);
  a1->set_atom("foo");
  Prefilter* a2 = new Prefilter(Prefilter::ATOM);
  a2->set_atom("bar");
  
  Prefilter* and_pf = new Prefilter(Prefilter::AND);
  and_pf->subs()->push_back(a1);
  and_pf->subs()->push_back(a2);
  
  tree.Add(and_pf);
  
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  
  // Find indices
  int foo_idx = -1, bar_idx = -1;
  for (int i = 0; i < static_cast<int>(atom_vec.size()); i++) {
    if (atom_vec[i] == "foo") foo_idx = i;
    if (atom_vec[i] == "bar") bar_idx = i;
  }
  
  // Only matching "foo" should not trigger the regexp
  if (foo_idx >= 0) {
    std::vector<int> matched_atoms = {foo_idx};
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    bool found = false;
    for (int r : regexps) {
      if (r == 0) found = true;
    }
    EXPECT_FALSE(found);
  }
  
  // Matching both should trigger
  if (foo_idx >= 0 && bar_idx >= 0) {
    std::vector<int> matched_atoms = {foo_idx, bar_idx};
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    bool found = false;
    for (int r : regexps) {
      if (r == 0) found = true;
    }
    EXPECT_TRUE(found);
  }
}

// Test OR prefilter requires any atom to match
TEST_F(PrefilterTreeTest_573, OrPrefilterRequiresAnyAtom_573) {
  PrefilterTree tree;
  
  Prefilter* a1 = new Prefilter(Prefilter::ATOM);
  a1->set_atom("foo");
  Prefilter* a2 = new Prefilter(Prefilter::ATOM);
  a2->set_atom("bar");
  
  Prefilter* or_pf = new Prefilter(Prefilter::OR);
  or_pf->subs()->push_back(a1);
  or_pf->subs()->push_back(a2);
  
  tree.Add(or_pf);
  
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  
  int foo_idx = -1;
  for (int i = 0; i < static_cast<int>(atom_vec.size()); i++) {
    if (atom_vec[i] == "foo") foo_idx = i;
  }
  
  // Matching just "foo" should trigger the regexp with OR
  if (foo_idx >= 0) {
    std::vector<int> matched_atoms = {foo_idx};
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    bool found = false;
    for (int r : regexps) {
      if (r == 0) found = true;
    }
    EXPECT_TRUE(found);
  }
}

// Test PrintPrefilter doesn't crash
TEST_F(PrefilterTreeTest_573, PrintPrefilterNoCrash_573) {
  PrefilterTree tree;
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("test");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  // Should not crash
  tree.PrintPrefilter(0);
}

// Test min_atom_len filtering
TEST_F(PrefilterTreeTest_573, MinAtomLenFiltering_573) {
  PrefilterTree tree(5);  // min atom len of 5
  
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("ab");  // shorter than min_atom_len
  tree.Add(pf);
  
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  
  // The short atom might cause the regexp to be unfiltered
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // Should be in the unfiltered set (always matches)
  bool found = false;
  for (int r : regexps) {
    if (r == 0) found = true;
  }
  EXPECT_TRUE(found);
}

// Test compile called on tree with only null prefilters
TEST_F(PrefilterTreeTest_573, AllNullPrefilters_573) {
  PrefilterTree tree;
  tree.Add(nullptr);
  tree.Add(nullptr);
  tree.Add(nullptr);
  
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  
  // All should be unfiltered
  EXPECT_EQ(regexps.size(), 3u);
}

}  // namespace re2
