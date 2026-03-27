// File: filtered_re2_first_match_test_475.cc

#include <gtest/gtest.h>
#include "re2/filtered_re2.h"
#include "re2/re2.h"

using re2::FilteredRE2;
using re2::RE2;

namespace {

//
// These tests exercise only observable behavior of
// FilteredRE2::FirstMatch(text, atoms):
//  - If not compiled, it should return -1.
//  - If compiled but the provided atom IDs yield no candidate regexps,
//    it should return -1.
//  - If compiled and unrelated/unknown atom IDs are provided,
//    it should return -1 even if there are regexps added.
//
// We intentionally avoid any reliance on internal atom-ID mapping.
//

// Not compiled: should return -1.
TEST(FilteredRE2_FirstMatchTest_475, ReturnsMinus1WhenNotCompiled_475) {
  FilteredRE2 fr;
  const std::vector<int> atoms;  // empty is fine; we're checking "not compiled" behavior.
  int res = fr.FirstMatch("anything", atoms);
  EXPECT_EQ(res, -1);
}

// Compiled with no regexps added and empty atom set: still returns -1.
// This validates that calling Compile flips into "compiled" state (black-box),
// and that no candidates -> -1 (observable through return value).
TEST(FilteredRE2_FirstMatchTest_475, ReturnsMinus1WhenCompiledButNoRegexps_475) {
  FilteredRE2 fr;

  // Compile with an empty atom list (boundary case).
  std::vector<std::string> atom_strings;  // no atoms
  fr.Compile(&atom_strings);

  // Provide no matched atoms.
  const std::vector<int> atoms;
  int res = fr.FirstMatch("text", atoms);
  EXPECT_EQ(res, -1);
}

// Compiled with some regexps added, but provide unknown/irrelevant atom IDs:
// should yield no candidate regexps and return -1.
// We do NOT assert any positive match because atom-ID mapping is internal.
TEST(FilteredRE2_FirstMatchTest_475, ReturnsMinus1ForUnknownAtomIds_475) {
  FilteredRE2 fr;

  // Add a few patterns (normal operation path).
  RE2::Options opts;
  int id1 = -1, id2 = -1;
  // Use simple, obviously matchable patterns without assuming internal behavior.
  // (We do not depend on them matching; we only verify FirstMatch returns -1
  //  when atoms are irrelevant.)
  (void)fr.Add("abc", opts, &id1);
  (void)fr.Add("def", opts, &id2);

  // Compile with some atom strings (their mapping is internal/opaque).
  std::vector<std::string> atom_strings = {"abc", "def", "xyz"};
  fr.Compile(&atom_strings);

  // Supply atoms that are highly unlikely to correspond to any internal IDs.
  // This tests the "no candidate regexps" observable path.
  const std::vector<int> unknown_atoms = {999999, -42, 123456789};

  // Even though the text would match "abc", with irrelevant atom IDs
  // the implementation should consider no candidates and return -1.
  int res = fr.FirstMatch("xxabcxx", unknown_atoms);
  EXPECT_EQ(res, -1);
}

}  // namespace
