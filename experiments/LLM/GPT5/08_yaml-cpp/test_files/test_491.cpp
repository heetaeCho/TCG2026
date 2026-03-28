// TEST_ID: 491
#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterStateSetBoolFormatTest_491 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

// Helper to avoid repeating checks.
static void ExpectSetBoolFormatUpdatesGetter_491(YAML::EmitterState& s, YAML::EMITTER_MANIP v,
                                                YAML::FmtScope::value scope) {
  EXPECT_TRUE(s.SetBoolFormat(v, scope));
  EXPECT_EQ(s.GetBoolFormat(), v);
}

}  // namespace

TEST_F(EmitterStateSetBoolFormatTest_491, AcceptsYesNoBoolAndUpdatesGetter_GlobalScope_491) {
  ExpectSetBoolFormatUpdatesGetter_491(state, YAML::YesNoBool, YAML::FmtScope::Global);
}

TEST_F(EmitterStateSetBoolFormatTest_491, AcceptsTrueFalseBoolAndUpdatesGetter_GlobalScope_491) {
  ExpectSetBoolFormatUpdatesGetter_491(state, YAML::TrueFalseBool, YAML::FmtScope::Global);
}

TEST_F(EmitterStateSetBoolFormatTest_491, AcceptsOnOffBoolAndUpdatesGetter_GlobalScope_491) {
  ExpectSetBoolFormatUpdatesGetter_491(state, YAML::OnOffBool, YAML::FmtScope::Global);
}

TEST_F(EmitterStateSetBoolFormatTest_491, AcceptsYesNoBoolAndUpdatesGetter_LocalScope_491) {
  ExpectSetBoolFormatUpdatesGetter_491(state, YAML::YesNoBool, YAML::FmtScope::Local);
}

TEST_F(EmitterStateSetBoolFormatTest_491, AcceptsTrueFalseBoolAndUpdatesGetter_LocalScope_491) {
  ExpectSetBoolFormatUpdatesGetter_491(state, YAML::TrueFalseBool, YAML::FmtScope::Local);
}

TEST_F(EmitterStateSetBoolFormatTest_491, AcceptsOnOffBoolAndUpdatesGetter_LocalScope_491) {
  ExpectSetBoolFormatUpdatesGetter_491(state, YAML::OnOffBool, YAML::FmtScope::Local);
}

TEST_F(EmitterStateSetBoolFormatTest_491, ReturnsFalseForNonBoolManipAndDoesNotChangeGetter_491) {
  // Establish a known, valid bool format first.
  ASSERT_TRUE(state.SetBoolFormat(YAML::TrueFalseBool, YAML::FmtScope::Global));
  const YAML::EMITTER_MANIP before = state.GetBoolFormat();

  // A few representative non-bool manipulators.
  EXPECT_FALSE(state.SetBoolFormat(YAML::Auto, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), before);

  EXPECT_FALSE(state.SetBoolFormat(YAML::UpperCase, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), before);

  EXPECT_FALSE(state.SetBoolFormat(YAML::Hex, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), before);

  EXPECT_FALSE(state.SetBoolFormat(YAML::BeginSeq, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), before);
}

TEST_F(EmitterStateSetBoolFormatTest_491, ReturnsFalseForValuesAdjacentToBoolEnumsAndDoesNotChange_491) {
  // Bool enum values in emittermanip.h are 13..15. Try neighbors 12 and 16.
  ASSERT_TRUE(state.SetBoolFormat(YAML::OnOffBool, YAML::FmtScope::Global));
  const YAML::EMITTER_MANIP before = state.GetBoolFormat();

  EXPECT_FALSE(state.SetBoolFormat(YAML::TildeNull, YAML::FmtScope::Global));  // 12
  EXPECT_EQ(state.GetBoolFormat(), before);

  EXPECT_FALSE(state.SetBoolFormat(YAML::UpperCase, YAML::FmtScope::Global));  // 16
  EXPECT_EQ(state.GetBoolFormat(), before);
}

TEST_F(EmitterStateSetBoolFormatTest_491, SettingSameValidValueTwiceKeepsGetterAndReturnsTrue_491) {
  EXPECT_TRUE(state.SetBoolFormat(YAML::YesNoBool, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), YAML::YesNoBool);

  EXPECT_TRUE(state.SetBoolFormat(YAML::YesNoBool, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetBoolFormat(), YAML::YesNoBool);
}