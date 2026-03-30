// File: ./TestProjects/re2/re2/prefilter_tree_regexps_given_strings_test.cc

#include "re2/prefilter_tree.h"
#include <gtest/gtest.h>
#include <vector>

namespace re2 {

class PrefilterTreeTest_574 : public ::testing::Test {
protected:
  PrefilterTree tree_;  // default-constructed, i.e., not compiled yet
};

// When not compiled and with no prefilters added, output should be empty and
// previous contents of the output vector must be cleared.
TEST_F(PrefilterTreeTest_574, ReturnsEmptyWhenUncompiledAndNoPrefilters_574) {
  std::vector<int> matched_atoms = {1, 2, 3};  // arbitrary; ignored before compile
  std::vector<int> regexps = {42, 99};         // should be cleared by the call

  tree_.RegexpsGivenStrings(matched_atoms, &regexps);

  EXPECT_TRUE(regexps.empty());
}

// When not compiled but prefilters exist, it should return all indices [0..N-1],
// sorted, regardless of matched_atoms input, and clear previous contents.
TEST_F(PrefilterTreeTest_574, ReturnsAllIndicesWhenUncompiledAndHasPrefilters_574) {
  // We do not rely on Prefilter internals; we only use the public Add API.
  // Passing nullptr is acceptable here because we are not compiling, and we
  // only need to observe that entries exist via public behavior.
  tree_.Add(nullptr);
  tree_.Add(nullptr);
  tree_.Add(nullptr);

  std::vector<int> matched_atoms = {};     // arbitrary; ignored before compile
  std::vector<int> regexps = {7, 8, 9};    // should be cleared and replaced

  tree_.RegexpsGivenStrings(matched_atoms, &regexps);

  // Expect indices [0,1,2] in sorted order.
  std::vector<int> expected{0, 1, 2};
  EXPECT_EQ(regexps, expected);
}

// Ensure that a non-empty matched_atoms input is ignored in the uncompiled path
// and that the results are still full [0..N-1] indices sorted.
TEST_F(PrefilterTreeTest_574, IgnoresMatchedAtomsBeforeCompile_574) {
  PrefilterTree t;

  // Add two entries to observe indices 0 and 1.
  t.Add(nullptr);
  t.Add(nullptr);

  // Provide some arbitrary matched atoms; should not affect output before compile.
  std::vector<int> matched_atoms = {10, 20, 30};
  std::vector<int> regexps;

  t.RegexpsGivenStrings(matched_atoms, &regexps);

  std::vector<int> expected{0, 1};
  EXPECT_EQ(regexps, expected);
}

}  // namespace re2
