// File: ./TestProjects/yaml-cpp/test/emitterstate_setintformat_test_495.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/emitterstate.h"

namespace {

class EmitterStateSetIntFormatTest_495 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

// Normal operation: supported int formats should succeed and be observable via GetIntFormat().
TEST_F(EmitterStateSetIntFormatTest_495, SetDecGlobalUpdatesGetIntFormat_495) {
  EXPECT_TRUE(state.SetIntFormat(YAML::Dec, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), YAML::Dec);
}

TEST_F(EmitterStateSetIntFormatTest_495, SetHexGlobalUpdatesGetIntFormat_495) {
  EXPECT_TRUE(state.SetIntFormat(YAML::Hex, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), YAML::Hex);
}

TEST_F(EmitterStateSetIntFormatTest_495, SetOctGlobalUpdatesGetIntFormat_495) {
  EXPECT_TRUE(state.SetIntFormat(YAML::Oct, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), YAML::Oct);
}

// Boundary/consistency: repeated sets should succeed; last successful set should be observable.
TEST_F(EmitterStateSetIntFormatTest_495, MultipleValidSetsLastOneWins_495) {
  EXPECT_TRUE(state.SetIntFormat(YAML::Dec, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), YAML::Dec);

  EXPECT_TRUE(state.SetIntFormat(YAML::Hex, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), YAML::Hex);

  EXPECT_TRUE(state.SetIntFormat(YAML::Oct, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), YAML::Oct);
}

// Error cases: unsupported values should return false.
TEST_F(EmitterStateSetIntFormatTest_495, InvalidValueReturnsFalse_495) {
  EXPECT_FALSE(state.SetIntFormat(YAML::Auto, YAML::FmtScope::Global));
  EXPECT_FALSE(state.SetIntFormat(YAML::SingleQuoted, YAML::FmtScope::Global));
  EXPECT_FALSE(state.SetIntFormat(YAML::LongKey, YAML::FmtScope::Global));
}

// Error cases: failed call should not (observably) change the current int format.
TEST_F(EmitterStateSetIntFormatTest_495, InvalidValueDoesNotChangeGetIntFormat_495) {
  // Establish a known valid baseline first.
  ASSERT_TRUE(state.SetIntFormat(YAML::Hex, YAML::FmtScope::Global));
  const YAML::EMITTER_MANIP before = state.GetIntFormat();
  ASSERT_EQ(before, YAML::Hex);

  // Try an invalid value; must fail and not change observable state.
  EXPECT_FALSE(state.SetIntFormat(YAML::Auto, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetIntFormat(), before);
}

// Scope coverage (no assumptions beyond observable behavior): calling with Local should
// succeed for valid formats and reflect in GetIntFormat().
TEST_F(EmitterStateSetIntFormatTest_495, SetDecLocalUpdatesGetIntFormat_495) {
  EXPECT_TRUE(state.SetIntFormat(YAML::Dec, YAML::FmtScope::Local));
  EXPECT_EQ(state.GetIntFormat(), YAML::Dec);
}

TEST_F(EmitterStateSetIntFormatTest_495, SetHexLocalUpdatesGetIntFormat_495) {
  EXPECT_TRUE(state.SetIntFormat(YAML::Hex, YAML::FmtScope::Local));
  EXPECT_EQ(state.GetIntFormat(), YAML::Hex);
}

TEST_F(EmitterStateSetIntFormatTest_495, SetOctLocalUpdatesGetIntFormat_495) {
  EXPECT_TRUE(state.SetIntFormat(YAML::Oct, YAML::FmtScope::Local));
  EXPECT_EQ(state.GetIntFormat(), YAML::Oct);
}

}  // namespace