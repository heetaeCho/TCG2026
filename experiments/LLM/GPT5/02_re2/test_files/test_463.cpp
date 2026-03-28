// File: prefilter_subs_test_463.cc
#include <gtest/gtest.h>
#include <vector>
#include "re2/prefilter.h"

namespace {

using re2::Prefilter;

TEST(PrefilterSubsTest_463, SubsReturnsSamePointerForAND_463) {
  // Arrange: parent with AND op and a subs vector with two children
  Prefilter parent(Prefilter::AND);
  auto* children = new std::vector<Prefilter*>;
  children->push_back(new Prefilter(Prefilter::ATOM));
  children->push_back(new Prefilter(Prefilter::ATOM));
  parent.set_subs(children);

  // Act
  std::vector<Prefilter*>* returned = parent.subs();

  // Assert: pointer identity and observable contents match
  ASSERT_NE(returned, nullptr);
  EXPECT_EQ(returned, children);
  ASSERT_EQ(returned->size(), 2u);
  EXPECT_NE((*returned)[0], nullptr);
  EXPECT_NE((*returned)[1], nullptr);

  // NOTE: We intentionally avoid deleting to not assume ownership semantics.
}

TEST(PrefilterSubsTest_463, SubsReturnsSamePointerForOR_463) {
  // Arrange
  Prefilter parent(Prefilter::OR);
  auto* children = new std::vector<Prefilter*>;
  children->push_back(new Prefilter(Prefilter::ATOM));
  parent.set_subs(children);

  // Act
  std::vector<Prefilter*>* returned = parent.subs();

  // Assert
  ASSERT_NE(returned, nullptr);
  EXPECT_EQ(returned, children);
  ASSERT_EQ(returned->size(), 1u);
  EXPECT_NE((*returned)[0], nullptr);

  // NOTE: No deletes here; avoid assumptions about ownership.
}

TEST(PrefilterSubsTest_463, SubsHandlesEmptyVector_463) {
  // Arrange: AND with an empty subs vector
  Prefilter parent(Prefilter::AND);
  auto* empty_children = new std::vector<Prefilter*>;
  parent.set_subs(empty_children);

  // Act
  std::vector<Prefilter*>* returned = parent.subs();

  // Assert
  ASSERT_NE(returned, nullptr);
  EXPECT_EQ(returned, empty_children);
  EXPECT_TRUE(returned->empty());
}

// This test verifies the debug-check precondition on ops other than AND/OR.
// ABSL_DCHECK typically crashes in debug builds; in release it may be compiled out.
// ASSERT_DEATH_IF_SUPPORTED makes the test portable across build modes.
TEST(PrefilterSubsTest_463, SubsDebugDiesForNonAndOrOp_463) {
#if GTEST_HAS_DEATH_TEST
  Prefilter atom_node(Prefilter::ATOM);
  // We don't care about the exact message; just that it dies in debug-enabled runs.
  ASSERT_DEATH_IF_SUPPORTED({ (void)atom_node.subs(); }, "");
#else
  GTEST_SKIP() << "Death tests not supported on this platform/build.";
#endif
}

}  // namespace
