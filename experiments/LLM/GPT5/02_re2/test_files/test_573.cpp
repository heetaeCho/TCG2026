// File: prefilter_tree_compile_test_573.cc
#include <gtest/gtest.h>
#include <vector>
#include <string>

// SUT headers
#include "re2/prefilter_tree.h"

namespace re2 {

class PrefilterTreeTest_573 : public ::testing::Test {
 protected:
  // Helpers to build simple, easily-checkable vectors.
  static std::vector<std::string> MakeVec(std::initializer_list<const char*> il) {
    std::vector<std::string> v;
    for (const char* s : il) v.emplace_back(s);
    return v;
  }
};

// [573] When there are no prefilters added, Compile should be a no-op and must
// not touch the provided atom_vec (AssignUniqueIds is not called per interface behavior).
TEST_F(PrefilterTreeTest_573, CompileDoesNothingWhenNoPrefilters_573) {
  PrefilterTree tree;

  std::vector<std::string> atom_vec = MakeVec({"a", "b", "c"});
  // Keep originals for later comparison.
  const auto original = atom_vec;

  // No prefilters have been added; Compile should return immediately.
  tree.Compile(&atom_vec);

  // Observable effect: atom_vec should remain unchanged.
  EXPECT_EQ(atom_vec, original);
}

// [573] After the tree has been compiled once (with at least one prefilter),
// calling Compile again should return early and must not touch the new atom_vec
// passed to the second call. We don't assume anything about the first call's
// behavior on its atom_vec; we only assert the second call leaves its argument untouched.
TEST_F(PrefilterTreeTest_573, SecondCompileDoesNotTouchArgWhenAlreadyCompiled_573) {
  PrefilterTree tree;

  // Add a prefilter to ensure the first Compile actually proceeds to "compiled" state.
  // We pass nullptr as a placeholder; we are not asserting any behavior of Add itself,
  // only using the public interface to make the prefilter list non-empty.
  tree.Add(nullptr);

  // First compile with some vector. We don't make assertions on how it changes.
  std::vector<std::string> first = MakeVec({"x"});
  tree.Compile(&first);

  // Now call Compile again with a *different* vector and assert it is untouched,
  // exercising the "already compiled" early-return path in Compile().
  std::vector<std::string> second = MakeVec({"sentinel1", "sentinel2"});
  const auto second_original = second;

  tree.Compile(&second);

  // Since Compile should return immediately when already compiled, it must not
  // have modified the provided atom_vec argument.
  EXPECT_EQ(second, second_original);
}

}  // namespace re2
