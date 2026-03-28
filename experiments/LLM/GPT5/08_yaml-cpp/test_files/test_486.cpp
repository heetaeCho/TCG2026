// File: ./TestProjects/yaml-cpp/test/emitterstate_lastindent_test_486.cpp

#include <gtest/gtest.h>

#include <cstddef>

// Try the most likely public header path first; if your build uses a different include
// path, adjust this include accordingly.
#include "emitterstate.h"

namespace {

using YAML::EmitterState;

// Helper: pick two distinct GroupType::value values without assuming specific enum names.
static YAML::GroupType::value GroupType0() {
  return static_cast<YAML::GroupType::value>(0);
}
static YAML::GroupType::value GroupType1() {
  return static_cast<YAML::GroupType::value>(1);
}

class EmitterStateLastIndentTest_486 : public ::testing::Test {
 protected:
  EmitterState state;
};

TEST_F(EmitterStateLastIndentTest_486, DefaultIsZero_486) {
  // With the initial state, LastIndent() should be 0 (boundary: <= 1 group).
  EXPECT_EQ(state.LastIndent(), static_cast<std::size_t>(0));
}

TEST_F(EmitterStateLastIndentTest_486, OneExtraGroupComputesDifference_486) {
  // Capture the current (parent) group indent before starting a nested group.
  const std::size_t parent_group_indent = state.CurGroupIndent();

  state.StartedGroup(GroupType0());

  // Observable expectation based on the interface: after entering a new group,
  // LastIndent should reflect the current indent relative to the previous group's indent.
  const std::size_t cur_indent = state.CurIndent();
  EXPECT_EQ(state.LastIndent(), cur_indent - parent_group_indent);

  // Clean up to keep state well-formed for future operations.
  state.EndedGroup(GroupType0());
}

TEST_F(EmitterStateLastIndentTest_486, NestedGroupUsesImmediateParentIndent_486) {
  // Enter first nested group.
  state.StartedGroup(GroupType0());
  const std::size_t parent1_indent = state.CurGroupIndent();

  // Enter second nested group; immediate parent is the first nested group.
  state.StartedGroup(GroupType1());

  const std::size_t cur_indent = state.CurIndent();
  EXPECT_EQ(state.LastIndent(), cur_indent - parent1_indent);

  // Clean up nesting.
  state.EndedGroup(GroupType1());
  state.EndedGroup(GroupType0());
}

TEST_F(EmitterStateLastIndentTest_486, AfterEndingBackToRootReturnsZero_486) {
  EXPECT_EQ(state.LastIndent(), static_cast<std::size_t>(0));

  state.StartedGroup(GroupType0());
  (void)state.LastIndent();  // should be safe to call while nested

  state.EndedGroup(GroupType0());

  // Back to the initial boundary condition (<= 1 group): LastIndent() should be 0.
  EXPECT_EQ(state.LastIndent(), static_cast<std::size_t>(0));
}

TEST_F(EmitterStateLastIndentTest_486, LastIndentDoesNotThrow_486) {
  EXPECT_NO_THROW((void)state.LastIndent());

  state.StartedGroup(GroupType0());
  EXPECT_NO_THROW((void)state.LastIndent());
  state.EndedGroup(GroupType0());

  EXPECT_NO_THROW((void)state.LastIndent());
}

}  // namespace