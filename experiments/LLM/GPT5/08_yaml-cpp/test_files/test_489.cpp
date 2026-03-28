// File: emitterstate_setoutputcharset_test.cpp
#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"
#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateSetOutputCharsetTest_489 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  // We don't assume which enumerators exist for FmtScope; scope is not validated
  // by SetOutputCharset per the provided implementation (it is just forwarded).
  static YAML::FmtScope::value Scope0() { return static_cast<YAML::FmtScope::value>(0); }
  static YAML::FmtScope::value Scope1() { return static_cast<YAML::FmtScope::value>(1); }
};

TEST_F(EmitterStateSetOutputCharsetTest_489, SetOutputCharset_AcceptsEmitNonAscii_489) {
  const auto before = state.GetOutputCharset();

  EXPECT_TRUE(state.SetOutputCharset(YAML::EmitNonAscii, Scope0()));
  EXPECT_EQ(state.GetOutputCharset(), YAML::EmitNonAscii);

  // Sanity: it should be allowed to change away from whatever the previous value was.
  (void)before;
}

TEST_F(EmitterStateSetOutputCharsetTest_489, SetOutputCharset_AcceptsEscapeNonAscii_489) {
  EXPECT_TRUE(state.SetOutputCharset(YAML::EscapeNonAscii, Scope1()));
  EXPECT_EQ(state.GetOutputCharset(), YAML::EscapeNonAscii);
}

TEST_F(EmitterStateSetOutputCharsetTest_489, SetOutputCharset_AcceptsEscapeAsJson_489) {
  EXPECT_TRUE(state.SetOutputCharset(YAML::EscapeAsJson, Scope0()));
  EXPECT_EQ(state.GetOutputCharset(), YAML::EscapeAsJson);
}

TEST_F(EmitterStateSetOutputCharsetTest_489, SetOutputCharset_RejectsDisallowedManipAndDoesNotChange_489) {
  // Put it into a known allowed state first.
  ASSERT_TRUE(state.SetOutputCharset(YAML::EmitNonAscii, Scope0()));
  const auto before = state.GetOutputCharset();
  ASSERT_EQ(before, YAML::EmitNonAscii);

  // Disallowed values per the switch default branch.
  EXPECT_FALSE(state.SetOutputCharset(YAML::Auto, Scope0()));
  EXPECT_EQ(state.GetOutputCharset(), before);

  EXPECT_FALSE(state.SetOutputCharset(YAML::SingleQuoted, Scope1()));
  EXPECT_EQ(state.GetOutputCharset(), before);

  EXPECT_FALSE(state.SetOutputCharset(YAML::Hex, Scope0()));
  EXPECT_EQ(state.GetOutputCharset(), before);
}

TEST_F(EmitterStateSetOutputCharsetTest_489, SetOutputCharset_RejectsOutOfRangeEnumValues_489) {
  // Put it into a known allowed state first.
  ASSERT_TRUE(state.SetOutputCharset(YAML::EscapeAsJson, Scope1()));
  const auto before = state.GetOutputCharset();
  ASSERT_EQ(before, YAML::EscapeAsJson);

  // Boundary/error-like inputs: enum values outside the defined set.
  EXPECT_FALSE(state.SetOutputCharset(static_cast<YAML::EMITTER_MANIP>(-1), Scope0()));
  EXPECT_EQ(state.GetOutputCharset(), before);

  EXPECT_FALSE(state.SetOutputCharset(static_cast<YAML::EMITTER_MANIP>(999999), Scope1()));
  EXPECT_EQ(state.GetOutputCharset(), before);
}

TEST_F(EmitterStateSetOutputCharsetTest_489, SetOutputCharset_AllowsChangingBetweenAllowedValues_489) {
  ASSERT_TRUE(state.SetOutputCharset(YAML::EmitNonAscii, Scope0()));
  EXPECT_EQ(state.GetOutputCharset(), YAML::EmitNonAscii);

  ASSERT_TRUE(state.SetOutputCharset(YAML::EscapeNonAscii, Scope0()));
  EXPECT_EQ(state.GetOutputCharset(), YAML::EscapeNonAscii);

  ASSERT_TRUE(state.SetOutputCharset(YAML::EscapeAsJson, Scope1()));
  EXPECT_EQ(state.GetOutputCharset(), YAML::EscapeAsJson);
}

}  // namespace