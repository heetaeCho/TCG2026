// File: filtered_re2_compile_test_473.cc
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include headers as provided by the project.
#include "re2/filtered_re2.h"

namespace re2 {

class FilteredRE2_CompileTest_473 : public ::testing::Test {};

// [Boundary] When no regexps have been added, Compile should be a no-op and
// must not modify the caller-provided atoms vector.
TEST_F(FilteredRE2_CompileTest_473, NoRegexps_LeavesAtomsUnchanged_473) {
  FilteredRE2 fr;  // default-constructed; treat as black box

  std::vector<std::string> atoms = {"preexisting", "values"};
  // Call: no regexps were added; per implementation path, this should early-return.
  fr.Compile(&atoms);

  // Observable expectation: atoms remain untouched.
  ASSERT_EQ(atoms.size(), 2u);
  EXPECT_EQ(atoms[0], "preexisting");
  EXPECT_EQ(atoms[1], "values");
}

// [Boundary/Safety] Passing a nullptr for atoms must be safely ignored when no
// regexps exist (the function returns before dereferencing).
TEST_F(FilteredRE2_CompileTest_473, NoRegexps_NullAtomsPointerIsIgnored_473) {
  FilteredRE2 fr;

  // Should not crash or dereference atoms when there are no regexps.
  // This validates defensive behavior on the early-return path.
  std::vector<std::string>* atoms_ptr = nullptr;
  fr.Compile(atoms_ptr);

  SUCCEED();  // Reaching here means no crash/UB was observed.
}

// [Idempotence on empty state] Calling Compile multiple times without adding
// any regexps should remain a no-op with no side effects on atoms.
TEST_F(FilteredRE2_CompileTest_473, CompileTwice_NoRegexps_NoSideEffects_473) {
  FilteredRE2 fr;

  std::vector<std::string> atoms = {"keep", "me"};
  fr.Compile(&atoms);  // first call: early-return
  fr.Compile(&atoms);  // second call: still early-return

  ASSERT_EQ(atoms.size(), 2u);
  EXPECT_EQ(atoms[0], "keep");
  EXPECT_EQ(atoms[1], "me");
}

}  // namespace re2
