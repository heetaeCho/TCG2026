// File: prefilter_tree_add_test_572.cc

#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"

// We only rely on public behavior:
// - Calling Add() after Compile() should trigger a DFATAL death due to ABSL_LOG(DFATAL).
// - Adding nullptr before Compile() should be accepted and not crash; Compile() should still succeed.
// - Multiple Add(nullptr) before Compile() should also be fine and Compile() should succeed.

namespace re2 {

TEST(PrefilterTreeAddTest_572, AddAfterCompileTriggersDFatal_572) {
  PrefilterTree tree;
  std::vector<std::string> atoms;
  tree.Compile(&atoms);

  // Expect the DFATAL in Add() after Compile() to terminate the process.
  // The log text in the implementation is: "Add called after Compile."
  EXPECT_DEATH(
      {
        // Use a non-null pointer to ensure we exercise the same early-return path.
        // We don't assert anything about Prefilter internals.
        Prefilter* pf = nullptr;  // nullptr is enough since DFATAL happens first.
        tree.Add(pf);
      },
      "Add called after Compile\\.");
}

TEST(PrefilterTreeAddTest_572, AddNullBeforeCompileNoCrash_572) {
  PrefilterTree tree;

  // Adding a nullptr should not crash or throw.
  ASSERT_NO_FATAL_FAILURE(tree.Add(nullptr));

  // Compiling afterwards should still succeed without crashing.
  std::vector<std::string> atoms;
  EXPECT_NO_FATAL_FAILURE(tree.Compile(&atoms));
}

TEST(PrefilterTreeAddTest_572, AddMultipleNullsBeforeCompileNoCrash_572) {
  PrefilterTree tree;

  ASSERT_NO_FATAL_FAILURE(tree.Add(nullptr));
  ASSERT_NO_FATAL_FAILURE(tree.Add(nullptr));
  ASSERT_NO_FATAL_FAILURE(tree.Add(nullptr));

  std::vector<std::string> atoms;
  EXPECT_NO_FATAL_FAILURE(tree.Compile(&atoms));
}

}  // namespace re2
