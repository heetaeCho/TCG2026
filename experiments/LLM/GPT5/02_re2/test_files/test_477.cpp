// File: filtered_re2_allpotentials_test_477.cc

#include <vector>
#include "gtest/gtest.h"
#include "re2/filtered_re2.h"

// --- Test seam: provide link-time test definitions for PrefilterTree methods used ---
// We DO NOT touch FilteredRE2 internals. We only define PrefilterTree symbols so we
// can observe calls made by FilteredRE2::AllPotentials and return deterministic data.

namespace re2 {

// Test-observable hooks (kept in the test TU scope)
static std::vector<int> g_last_matched_atoms_477;
static bool g_regexps_called_477 = false;

// Minimal constructors/destructor that FilteredRE2 expects to exist.
PrefilterTree::PrefilterTree() {}
PrefilterTree::PrefilterTree(int /*min_atom_len*/) {}
PrefilterTree::~PrefilterTree() {}

// The only behavior we need to observe for this test:
// capture the input atoms and write a deterministic output.
void PrefilterTree::RegexpsGivenStrings(const std::vector<int>& matched_atoms,
                                        std::vector<int>* regexps) const {
  g_regexps_called_477 = true;
  g_last_matched_atoms_477 = matched_atoms;
  if (regexps != nullptr) {
    // Deterministic, easy-to-assert payload
    regexps->clear();
    regexps->push_back(101);
    regexps->push_back(102);
  }
}

// Provide no-op definitions for other declared methods if the linker needs them.
void PrefilterTree::Add(Prefilter* /*prefilter*/) {}
void PrefilterTree::Compile(std::vector<std::string>* /*atom_vec*/) {}
void PrefilterTree::PrintPrefilter(int /*regexpid*/) {}

}  // namespace re2

// ---------------------- Tests ----------------------

class FilteredRE2_AllPotentialsTest_477 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset the test hooks before each test
    re2::g_last_matched_atoms_477.clear();
    re2::g_regexps_called_477 = false;
  }
};

// Normal operation: forwards atoms and writes results into output vector.
TEST_F(FilteredRE2_AllPotentialsTest_477, ForwardsAtomsAndWritesOutput_477) {
  re2::FilteredRE2 uut;  // uses default ctor (creates a PrefilterTree internally)

  const std::vector<int> atoms{3, 7, 11};
  std::vector<int> out{-1};  // pre-filled to ensure it gets replaced

  uut.AllPotentials(atoms, &out);

  // Verify collaborator interaction (observable via test seam)
  EXPECT_TRUE(re2::g_regexps_called_477);
  EXPECT_EQ(re2::g_last_matched_atoms_477, atoms);

  // Verify observable effect on the out-parameter
  std::vector<int> expected{101, 102};
  EXPECT_EQ(out, expected);
}

// Boundary: empty atoms vector should still forward correctly and produce output.
TEST_F(FilteredRE2_AllPotentialsTest_477, HandlesEmptyAtoms_477) {
  re2::FilteredRE2 uut;

  const std::vector<int> atoms;  // empty
  std::vector<int> out;

  uut.AllPotentials(atoms, &out);

  EXPECT_TRUE(re2::g_regexps_called_477);
  EXPECT_TRUE(re2::g_last_matched_atoms_477.empty());

  std::vector<int> expected{101, 102};
  EXPECT_EQ(out, expected);
}

// API guarantee: input atoms are const&; ensure they remain unchanged by the call.
TEST_F(FilteredRE2_AllPotentialsTest_477, DoesNotModifyInputVector_477) {
  re2::FilteredRE2 uut;

  std::vector<int> atoms{5, 6, 7};
  const std::vector<int> original = atoms;
  std::vector<int> out;

  uut.AllPotentials(atoms, &out);

  // The input vector should not be modified as per const& contract.
  EXPECT_EQ(atoms, original);

  std::vector<int> expected{101, 102};
  EXPECT_EQ(out, expected);
}
