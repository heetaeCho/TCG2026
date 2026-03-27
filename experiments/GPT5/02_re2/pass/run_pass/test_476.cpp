// File: filtered_re2_allmatches_tests_476.cc
#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <vector>

// Minimal absl shim for string_view used by the code under test.
namespace absl { using string_view = std::string_view; }

// ---- Test double for PrefilterTree (external collaborator) ----
// We only implement the parts needed by FilteredRE2::AllMatches.
// It deterministically returns no candidate regex indices, allowing
// us to test boundary behavior without relying on internal details.
namespace re2 {
class PrefilterTree {
 public:
  PrefilterTree() {}
  explicit PrefilterTree(int /*min_atom_len*/) {}
  // No-op compile; not used by the tests.
  void Compile(std::vector<std::string>* /*atom_vec*/) {}
  // Return no candidates; exercise AllMatches' empty-path behavior.
  void RegexpsGivenStrings(const std::vector<int>& /*matched_atoms*/,
                           std::vector<int>* regexps) const {
    regexps->clear();
  }
  // Unused by these tests, but keep signatures available.
  void Add(void* /*prefilter*/) {}
  void PrintPrefilter(int /*regexpid*/) {}
};
}  // namespace re2

// ---- Include the header under test after the test double so it links to it. ----
#include "TestProjects/re2/re2/filtered_re2.h"

// Test fixture (kept minimal for clarity)
class FilteredRE2_AllMatchesTest_476 : public ::testing::Test {
 protected:
  re2::FilteredRE2 sut_;  // system under test
};

// Verifies: output vector is cleared even if pre-populated; returns false when there are no candidate regexps.
TEST_F(FilteredRE2_AllMatchesTest_476, ClearsOutputAndReturnsFalseWhenNoCandidates_476) {
  std::vector<int> out = {42, 7, 999};  // pre-populated; should be cleared
  std::vector<int> atoms = {1, 2, 3};   // arbitrary; our PrefilterTree returns no candidates regardless

  const bool ok = sut_.AllMatches(absl::string_view("any text"), atoms, &out);

  EXPECT_FALSE(ok);               // no candidates -> no matches
  EXPECT_TRUE(out.empty());       // must clear caller-provided vector
}

// Verifies: handles empty atoms gracefully (boundary); still clears and returns false.
TEST_F(FilteredRE2_AllMatchesTest_476, HandlesEmptyAtoms_476) {
  std::vector<int> out = {1};
  std::vector<int> atoms;  // empty

  const bool ok = sut_.AllMatches(absl::string_view(""), atoms, &out);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(out.empty());
}

// Verifies: repeated calls are idempotent re: clearing behavior and return value under no-candidate condition.
TEST_F(FilteredRE2_AllMatchesTest_476, RepeatedCallsRemainConsistent_476) {
  std::vector<int> out = {123};
  std::vector<int> atoms = {10};

  // First call
  EXPECT_FALSE(sut_.AllMatches(absl::string_view("first"), atoms, &out));
  EXPECT_TRUE(out.empty());

  // Re-fill and call again with different inputs to ensure behavior is stable
  out = {5, 6};
  atoms = {20, 30};
  EXPECT_FALSE(sut_.AllMatches(absl::string_view("second"), atoms, &out));
  EXPECT_TRUE(out.empty());
}
