// File: emitterstate_setstringformat_test.cpp
#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterStateSetStringFormatTest_490 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;

  static YAML::FmtScope::value Scope0() {
    return static_cast<YAML::FmtScope::value>(0);
  }
  static YAML::FmtScope::value Scope1() {
    return static_cast<YAML::FmtScope::value>(1);
  }
};

TEST_F(EmitterStateSetStringFormatTest_490, AcceptsAuto_490) {
  EXPECT_TRUE(state_.SetStringFormat(YAML::Auto, Scope0()));
  EXPECT_EQ(state_.GetStringFormat(), YAML::Auto);
}

TEST_F(EmitterStateSetStringFormatTest_490, AcceptsSingleQuoted_490) {
  EXPECT_TRUE(state_.SetStringFormat(YAML::SingleQuoted, Scope0()));
  EXPECT_EQ(state_.GetStringFormat(), YAML::SingleQuoted);
}

TEST_F(EmitterStateSetStringFormatTest_490, AcceptsDoubleQuoted_490) {
  EXPECT_TRUE(state_.SetStringFormat(YAML::DoubleQuoted, Scope0()));
  EXPECT_EQ(state_.GetStringFormat(), YAML::DoubleQuoted);
}

TEST_F(EmitterStateSetStringFormatTest_490, AcceptsLiteral_490) {
  EXPECT_TRUE(state_.SetStringFormat(YAML::Literal, Scope0()));
  EXPECT_EQ(state_.GetStringFormat(), YAML::Literal);
}

TEST_F(EmitterStateSetStringFormatTest_490, RejectsNonStringManipulators_ReturnsFalse_490) {
  // These are clearly not "string format" manipulators per the enum list.
  EXPECT_FALSE(state_.SetStringFormat(YAML::TagByKind, Scope0()));
  EXPECT_FALSE(state_.SetStringFormat(YAML::Newline, Scope0()));
  EXPECT_FALSE(state_.SetStringFormat(YAML::EmitNonAscii, Scope0()));
  EXPECT_FALSE(state_.SetStringFormat(YAML::EscapeNonAscii, Scope0()));
  EXPECT_FALSE(state_.SetStringFormat(YAML::EscapeAsJson, Scope0()));
  EXPECT_FALSE(state_.SetStringFormat(YAML::BeginSeq, Scope0()));
  EXPECT_FALSE(state_.SetStringFormat(YAML::BeginMap, Scope0()));
}

TEST_F(EmitterStateSetStringFormatTest_490, RejectsOutOfRangeEnumValues_ReturnsFalse_490) {
  EXPECT_FALSE(state_.SetStringFormat(static_cast<YAML::EMITTER_MANIP>(-1), Scope0()));
  EXPECT_FALSE(state_.SetStringFormat(static_cast<YAML::EMITTER_MANIP>(999999), Scope0()));
}

TEST_F(EmitterStateSetStringFormatTest_490, FailureDoesNotChangeExistingStringFormat_490) {
  ASSERT_TRUE(state_.SetStringFormat(YAML::DoubleQuoted, Scope0()));
  const YAML::EMITTER_MANIP before = state_.GetStringFormat();

  EXPECT_FALSE(state_.SetStringFormat(YAML::Hex, Scope0()));  // Not a string format manipulator.
  EXPECT_EQ(state_.GetStringFormat(), before);
}

TEST_F(EmitterStateSetStringFormatTest_490, CanSetUsingDifferentScopesWithoutError_490) {
  // We avoid assuming any precedence rules between scopes; we only verify calls succeed
  // for allowed values and that the state remains usable.
  EXPECT_TRUE(state_.SetStringFormat(YAML::SingleQuoted, Scope0()));
  (void)state_.GetStringFormat();

  EXPECT_TRUE(state_.SetStringFormat(YAML::Literal, Scope1()));
  (void)state_.GetStringFormat();
}

}  // namespace