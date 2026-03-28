// File: ./TestProjects/yaml-cpp/test/emitterstate_test_487.cpp

#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_487 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

// Sanity / error-case: should be safe to call on a fresh state (no prior modifications).
TEST_F(EmitterStateTest_487, ClearModifiedSettings_OnFreshState_DoesNotThrow_487) {
  EXPECT_NO_THROW(state.ClearModifiedSettings());
  EXPECT_NO_THROW(state.ClearModifiedSettings());  // idempotent safety check
}

// Observable behavior test (using public API only):
// If local setting changes are normally restored when ending a group, then clearing the modified
// settings before ending the group should prevent that restore from happening.
TEST_F(EmitterStateTest_487, ClearModifiedSettings_PreventsLocalIndentRestoreOnEndedGroup_487) {
  // Establish a known global indent baseline.
  ASSERT_TRUE(state.SetIndent(2, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetIndent(), 2u);

  // Start a document + group, change indent locally.
  state.StartedDoc();
  state.StartedGroup(YAML::GroupType::Seq);

  ASSERT_TRUE(state.SetIndent(4, YAML::FmtScope::Local));
  ASSERT_EQ(state.GetIndent(), 4u);

  // Clear the record of modified settings, then end the group.
  // Observable expectation: indent should remain at the locally-set value (no restore).
  state.ClearModifiedSettings();

  state.EndedGroup(YAML::GroupType::Seq);
  EXPECT_EQ(state.GetIndent(), 4u);

  state.EndedDoc();
}

// Control test for the above: without ClearModifiedSettings, local changes should restore
// after ending the group (if the interface implements local-scoped restore behavior).
TEST_F(EmitterStateTest_487, WithoutClearModifiedSettings_LocalIndentRestoresOnEndedGroup_487) {
  ASSERT_TRUE(state.SetIndent(2, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetIndent(), 2u);

  state.StartedDoc();
  state.StartedGroup(YAML::GroupType::Seq);

  ASSERT_TRUE(state.SetIndent(6, YAML::FmtScope::Local));
  ASSERT_EQ(state.GetIndent(), 6u);

  state.EndedGroup(YAML::GroupType::Seq);

  // Observable expectation: indent returns to the prior global value.
  EXPECT_EQ(state.GetIndent(), 2u);

  state.EndedDoc();
}

// Boundary-ish: multiple local modifications, then clear; after ending group, the last local value
// should remain if restores were cleared.
TEST_F(EmitterStateTest_487, ClearModifiedSettings_AfterMultipleLocalChanges_KeepsLastLocalIndent_487) {
  ASSERT_TRUE(state.SetIndent(1, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetIndent(), 1u);

  state.StartedDoc();
  state.StartedGroup(YAML::GroupType::Seq);

  ASSERT_TRUE(state.SetIndent(3, YAML::FmtScope::Local));
  ASSERT_EQ(state.GetIndent(), 3u);

  ASSERT_TRUE(state.SetIndent(5, YAML::FmtScope::Local));
  ASSERT_EQ(state.GetIndent(), 5u);

  state.ClearModifiedSettings();

  state.EndedGroup(YAML::GroupType::Seq);
  EXPECT_EQ(state.GetIndent(), 5u);

  state.EndedDoc();
}

// Error-case-ish sequencing: calling ClearModifiedSettings around doc/group operations should not throw.
TEST_F(EmitterStateTest_487, ClearModifiedSettings_WithDocAndGroupSequencing_DoesNotThrow_487) {
  EXPECT_NO_THROW(state.StartedDoc());
  EXPECT_NO_THROW(state.ClearModifiedSettings());
  EXPECT_NO_THROW(state.StartedGroup(YAML::GroupType::Seq));
  EXPECT_NO_THROW(state.ClearModifiedSettings());
  EXPECT_NO_THROW(state.EndedGroup(YAML::GroupType::Seq));
  EXPECT_NO_THROW(state.ClearModifiedSettings());
  EXPECT_NO_THROW(state.EndedDoc());
}

}  // namespace