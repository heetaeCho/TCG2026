// TEST_ID: 499
// Unit tests for YAML::EmitterState::SetFlowType
//
// Notes:
// - These tests treat EmitterState as a black box.
// - We verify only observable behavior via return values and GetFlowType().

#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterStateSetFlowTypeTest_499 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  // Avoid relying on enum symbol names that may vary across versions/ports.
  static YAML::GroupType::value SeqType() {
    return static_cast<YAML::GroupType::value>(0);
  }
  static YAML::GroupType::value MapType() {
    return static_cast<YAML::GroupType::value>(1);
  }
  static YAML::FmtScope::value SomeScope() {
    return static_cast<YAML::FmtScope::value>(0);
  }
};

TEST_F(EmitterStateSetFlowTypeTest_499, ReturnsTrueForBlockAndFlow_499) {
  const auto scope = SomeScope();

  EXPECT_TRUE(state.SetFlowType(SeqType(), YAML::Block, scope));
  EXPECT_TRUE(state.SetFlowType(SeqType(), YAML::Flow, scope));

  EXPECT_TRUE(state.SetFlowType(MapType(), YAML::Block, scope));
  EXPECT_TRUE(state.SetFlowType(MapType(), YAML::Flow, scope));
}

TEST_F(EmitterStateSetFlowTypeTest_499, ReturnsFalseForNonFlowManipulators_499) {
  const auto scope = SomeScope();

  // Pick a few clearly non-FlowType manipulators.
  EXPECT_FALSE(state.SetFlowType(SeqType(), YAML::Auto, scope));
  EXPECT_FALSE(state.SetFlowType(SeqType(), YAML::BeginSeq, scope));
  EXPECT_FALSE(state.SetFlowType(SeqType(), YAML::BeginMap, scope));
  EXPECT_FALSE(state.SetFlowType(SeqType(), YAML::Key, scope));
  EXPECT_FALSE(state.SetFlowType(SeqType(), YAML::Value, scope));

  EXPECT_FALSE(state.SetFlowType(MapType(), YAML::Auto, scope));
  EXPECT_FALSE(state.SetFlowType(MapType(), YAML::BeginSeq, scope));
  EXPECT_FALSE(state.SetFlowType(MapType(), YAML::BeginMap, scope));
  EXPECT_FALSE(state.SetFlowType(MapType(), YAML::Key, scope));
  EXPECT_FALSE(state.SetFlowType(MapType(), YAML::Value, scope));
}

TEST_F(EmitterStateSetFlowTypeTest_499, SuccessfulCallUpdatesGetFlowTypeForSeq_499) {
  const auto scope = SomeScope();

  ASSERT_TRUE(state.SetFlowType(SeqType(), YAML::Block, scope));
  EXPECT_EQ(state.GetFlowType(SeqType()), YAML::Block);

  ASSERT_TRUE(state.SetFlowType(SeqType(), YAML::Flow, scope));
  EXPECT_EQ(state.GetFlowType(SeqType()), YAML::Flow);
}

TEST_F(EmitterStateSetFlowTypeTest_499, SuccessfulCallUpdatesGetFlowTypeForMap_499) {
  const auto scope = SomeScope();

  ASSERT_TRUE(state.SetFlowType(MapType(), YAML::Block, scope));
  EXPECT_EQ(state.GetFlowType(MapType()), YAML::Block);

  ASSERT_TRUE(state.SetFlowType(MapType(), YAML::Flow, scope));
  EXPECT_EQ(state.GetFlowType(MapType()), YAML::Flow);
}

TEST_F(EmitterStateSetFlowTypeTest_499, SeqAndMapFlowTypesAreIndependent_499) {
  const auto scope = SomeScope();

  ASSERT_TRUE(state.SetFlowType(SeqType(), YAML::Flow, scope));
  ASSERT_TRUE(state.SetFlowType(MapType(), YAML::Block, scope));

  EXPECT_EQ(state.GetFlowType(SeqType()), YAML::Flow);
  EXPECT_EQ(state.GetFlowType(MapType()), YAML::Block);

  // Flip them and re-check.
  ASSERT_TRUE(state.SetFlowType(SeqType(), YAML::Block, scope));
  ASSERT_TRUE(state.SetFlowType(MapType(), YAML::Flow, scope));

  EXPECT_EQ(state.GetFlowType(SeqType()), YAML::Block);
  EXPECT_EQ(state.GetFlowType(MapType()), YAML::Flow);
}

TEST_F(EmitterStateSetFlowTypeTest_499, FailedCallDoesNotChangeExistingFlowType_499) {
  const auto scope = SomeScope();

  // Establish a known state.
  ASSERT_TRUE(state.SetFlowType(SeqType(), YAML::Block, scope));
  ASSERT_TRUE(state.SetFlowType(MapType(), YAML::Flow, scope));
  const auto prevSeq = state.GetFlowType(SeqType());
  const auto prevMap = state.GetFlowType(MapType());

  // Attempt invalid updates.
  EXPECT_FALSE(state.SetFlowType(SeqType(), YAML::Auto, scope));
  EXPECT_FALSE(state.SetFlowType(MapType(), YAML::BeginSeq, scope));

  // Must remain unchanged.
  EXPECT_EQ(state.GetFlowType(SeqType()), prevSeq);
  EXPECT_EQ(state.GetFlowType(MapType()), prevMap);
}

}  // namespace