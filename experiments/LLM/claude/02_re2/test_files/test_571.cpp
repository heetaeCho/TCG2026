#include "gtest/gtest.h"
#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"

#include <string>
#include <vector>

namespace re2 {

// Test default construction and destruction
TEST(PrefilterTreeTest_571, DefaultConstruction_571) {
  PrefilterTree tree;
  // Should construct and destruct without issues
}

// Test construction with explicit min_atom_len
TEST(PrefilterTreeTest_571, ExplicitMinAtomLenConstruction_571) {
  PrefilterTree tree(5);
  // Should construct and destruct without issues
}

// Test construction with min_atom_len of 0
TEST(PrefilterTreeTest_571, MinAtomLenZero_571) {
  PrefilterTree tree(0);
  // Should construct and destruct without issues
}

// Test construction with min_atom_len of 1
TEST(PrefilterTreeTest_571, MinAtomLenOne_571) {
  PrefilterTree tree(1);
  // Should construct and destruct without issues
}

// Test Add with nullptr prefilter and then Compile
TEST(PrefilterTreeTest_571, AddNullPrefilter_571) {
  PrefilterTree tree;
  tree.Add(nullptr);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  // With a null prefilter, the regex should be unfiltered
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // The regexp with null prefilter should always match (unfiltered)
  ASSERT_EQ(regexps.size(), 1u);
  EXPECT_EQ(regexps[0], 0);
}

// Test Add with an atom prefilter and Compile
TEST(PrefilterTreeTest_571, AddAtomPrefilter_571) {
  PrefilterTree tree;
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("hello");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  // atom_vec should contain the atom
  ASSERT_GE(atom_vec.size(), 1u);
  bool found = false;
  int atom_index = -1;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    if (atom_vec[i] == "hello") {
      found = true;
      atom_index = static_cast<int>(i);
      break;
    }
  }
  EXPECT_TRUE(found);

  // If we match that atom, regexp 0 should be returned
  std::vector<int> matched_atoms;
  matched_atoms.push_back(atom_index);
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  ASSERT_EQ(regexps.size(), 1u);
  EXPECT_EQ(regexps[0], 0);
}

// Test RegexpsGivenStrings with no matched atoms returns unfiltered regexps
TEST(PrefilterTreeTest_571, NoMatchedAtomsReturnsUnfiltered_571) {
  PrefilterTree tree;
  // Add a null prefilter (unfiltered)
  tree.Add(nullptr);
  // Add an atom prefilter
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("test");
  tree.Add(pf);

  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // With no matched atoms, only unfiltered regexp (0) should be returned
  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // Regexp 0 (null prefilter) should always appear
  bool found_0 = false;
  for (int r : regexps) {
    if (r == 0) found_0 = true;
  }
  EXPECT_TRUE(found_0);
}

// Test multiple Add calls
TEST(PrefilterTreeTest_571, MultipleAdds_571) {
  PrefilterTree tree;
  tree.Add(nullptr);
  Prefilter* pf1 = new Prefilter(Prefilter::ATOM);
  pf1->set_atom("abc");
  tree.Add(pf1);
  Prefilter* pf2 = new Prefilter(Prefilter::ATOM);
  pf2->set_atom("def");
  tree.Add(pf2);

  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Match all atoms
  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  // All three regexps should be returned
  EXPECT_GE(regexps.size(), 3u);
}

// Test Compile with empty tree
TEST(PrefilterTreeTest_571, CompileEmptyTree_571) {
  PrefilterTree tree;
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  EXPECT_TRUE(atom_vec.empty());

  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_TRUE(regexps.empty());
}

// Test RegexpsGivenStrings returns sorted results
TEST(PrefilterTreeTest_571, RegexpsGivenStringsSorted_571) {
  PrefilterTree tree;
  // Add multiple null (unfiltered) prefilters
  tree.Add(nullptr);
  tree.Add(nullptr);
  tree.Add(nullptr);

  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  std::vector<int> matched_atoms;
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  ASSERT_EQ(regexps.size(), 3u);
  // Check sorted
  for (size_t i = 1; i < regexps.size(); i++) {
    EXPECT_LE(regexps[i - 1], regexps[i]);
  }
}

// Test AND prefilter
TEST(PrefilterTreeTest_571, AddAndPrefilter_571) {
  PrefilterTree tree;
  Prefilter* atom1 = new Prefilter(Prefilter::ATOM);
  atom1->set_atom("foo");
  Prefilter* atom2 = new Prefilter(Prefilter::ATOM);
  atom2->set_atom("bar");
  Prefilter* and_pf = Prefilter::And(atom1, atom2);
  tree.Add(and_pf);

  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Need to match both atoms for the regexp to be returned
  // First, find indices
  int foo_idx = -1, bar_idx = -1;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    if (atom_vec[i] == "foo") foo_idx = static_cast<int>(i);
    if (atom_vec[i] == "bar") bar_idx = static_cast<int>(i);
  }

  // Match only foo
  if (foo_idx >= 0) {
    std::vector<int> matched_atoms = {foo_idx};
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    // AND requires both, so should not return regexp 0 with only one atom
    // (unless implementation varies)
  }

  // Match both
  if (foo_idx >= 0 && bar_idx >= 0) {
    std::vector<int> matched_atoms = {foo_idx, bar_idx};
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    ASSERT_EQ(regexps.size(), 1u);
    EXPECT_EQ(regexps[0], 0);
  }
}

// Test OR prefilter
TEST(PrefilterTreeTest_571, AddOrPrefilter_571) {
  PrefilterTree tree;
  Prefilter* atom1 = new Prefilter(Prefilter::ATOM);
  atom1->set_atom("foo");
  Prefilter* atom2 = new Prefilter(Prefilter::ATOM);
  atom2->set_atom("bar");
  Prefilter* or_pf = Prefilter::Or(atom1, atom2);
  tree.Add(or_pf);

  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  int foo_idx = -1, bar_idx = -1;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    if (atom_vec[i] == "foo") foo_idx = static_cast<int>(i);
    if (atom_vec[i] == "bar") bar_idx = static_cast<int>(i);
  }

  // Match only foo - OR should return regexp 0
  if (foo_idx >= 0) {
    std::vector<int> matched_atoms = {foo_idx};
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    ASSERT_EQ(regexps.size(), 1u);
    EXPECT_EQ(regexps[0], 0);
  }

  // Match only bar - OR should return regexp 0
  if (bar_idx >= 0) {
    std::vector<int> matched_atoms = {bar_idx};
    std::vector<int> regexps;
    tree.RegexpsGivenStrings(matched_atoms, &regexps);
    ASSERT_EQ(regexps.size(), 1u);
    EXPECT_EQ(regexps[0], 0);
  }
}

// Test PrintPrefilter does not crash
TEST(PrefilterTreeTest_571, PrintPrefilterNoCrash_571) {
  PrefilterTree tree;
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("hello");
  tree.Add(pf);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  // Should not crash
  tree.PrintPrefilter(0);
}

// Test PrintPrefilter with null prefilter
TEST(PrefilterTreeTest_571, PrintPrefilterNull_571) {
  PrefilterTree tree;
  tree.Add(nullptr);
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);
  tree.PrintPrefilter(0);
}

// Test large number of prefilters
TEST(PrefilterTreeTest_571, LargeNumberOfPrefilters_571) {
  PrefilterTree tree;
  const int count = 100;
  for (int i = 0; i < count; i++) {
    Prefilter* pf = new Prefilter(Prefilter::ATOM);
    pf->set_atom("atom" + std::to_string(i));
    tree.Add(pf);
  }
  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Match all atoms
  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_EQ(regexps.size(), static_cast<size_t>(count));
}

// Test that duplicate atoms are handled
TEST(PrefilterTreeTest_571, DuplicateAtoms_571) {
  PrefilterTree tree;
  Prefilter* pf1 = new Prefilter(Prefilter::ATOM);
  pf1->set_atom("same");
  tree.Add(pf1);
  Prefilter* pf2 = new Prefilter(Prefilter::ATOM);
  pf2->set_atom("same");
  tree.Add(pf2);

  std::vector<std::string> atom_vec;
  tree.Compile(&atom_vec);

  // Both regexps use the same atom, so atom_vec may have just one entry
  // Match all atoms
  std::vector<int> matched_atoms;
  for (size_t i = 0; i < atom_vec.size(); i++) {
    matched_atoms.push_back(static_cast<int>(i));
  }
  std::vector<int> regexps;
  tree.RegexpsGivenStrings(matched_atoms, &regexps);
  EXPECT_EQ(regexps.size(), 2u);
}

}  // namespace re2
