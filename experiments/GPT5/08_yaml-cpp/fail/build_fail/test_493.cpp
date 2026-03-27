// File: ./TestProjects/yaml-cpp/test/emitterstate_setboolcaseformat_test.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/emitterstate.h"

namespace {

class EmitterStateTest_493 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  // Avoid assuming concrete FmtScope enumerators (names vary across forks/versions).
  // We only need a value to pass through the public interface.
  static constexpr YAML::FmtScope::value kScope0 =
      static_cast<YAML::FmtScope::value>(0);
  static constexpr YAML::FmtScope::value kScope1 =
      static_cast<YAML::FmtScope::value>(1);
};

TEST_F(EmitterStateTest_493, SetBoolCaseFormatAcceptsUpperCase_493) {
  const bool ok = state.SetBoolCaseFormat(YAML::UpperCase, kScope0);
  EXPECT_TRUE(ok);
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormatAcceptsLowerCase_493) {
  const bool ok = state.SetBoolCaseFormat(YAML::LowerCase, kScope0);
  EXPECT_TRUE(ok);
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::LowerCase);
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormatAcceptsCamelCase_493) {
  const bool ok = state.SetBoolCaseFormat(YAML::CamelCase, kScope0);
  EXPECT_TRUE(ok);
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::CamelCase);
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormatRejectsNonCaseManipAndDoesNotChange_493) {
  // Establish a known prior value.
  ASSERT_TRUE(state.SetBoolCaseFormat(YAML::UpperCase, kScope0));
  ASSERT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);

  // Try several clearly non-case manipulators; each should be rejected.
  EXPECT_FALSE(state.SetBoolCaseFormat(YAML::Auto, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);

  EXPECT_FALSE(state.SetBoolCaseFormat(YAML::TrueFalseBool, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);

  EXPECT_FALSE(state.SetBoolCaseFormat(YAML::LongBool, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);

  EXPECT_FALSE(state.SetBoolCaseFormat(YAML::Hex, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormatLastWriteWinsWhenValid_493) {
  ASSERT_TRUE(state.SetBoolCaseFormat(YAML::UpperCase, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);

  ASSERT_TRUE(state.SetBoolCaseFormat(YAML::LowerCase, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::LowerCase);

  ASSERT_TRUE(state.SetBoolCaseFormat(YAML::CamelCase, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::CamelCase);
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormatInvalidDoesNotOverrideLaterValid_493) {
  ASSERT_TRUE(state.SetBoolCaseFormat(YAML::LowerCase, kScope0));
  ASSERT_EQ(state.GetBoolCaseFormat(), YAML::LowerCase);

  EXPECT_FALSE(state.SetBoolCaseFormat(YAML::OnOffBool, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::LowerCase);

  EXPECT_TRUE(state.SetBoolCaseFormat(YAML::UpperCase, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);
}

TEST_F(EmitterStateTest_493, SetBoolCaseFormatWorksWithDifferentScopeValues_493) {
  // We don't assume what scopes mean internally; we only verify:
  // - accepted values return true for different scope inputs
  // - resulting observable getter matches the last accepted set.
  EXPECT_TRUE(state.SetBoolCaseFormat(YAML::UpperCase, kScope0));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::UpperCase);

  EXPECT_TRUE(state.SetBoolCaseFormat(YAML::LowerCase, kScope1));
  EXPECT_EQ(state.GetBoolCaseFormat(), YAML::LowerCase);
}

}  // namespace