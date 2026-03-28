// File: ./TestProjects/yaml-cpp/test/emitterstate_setnullformat_test_494.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/emitterstate.h>
#include <yaml-cpp/emittermanip.h>

namespace {

class EmitterStateTest_494 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
  static constexpr YAML::FmtScope::value kScope0 =
      static_cast<YAML::FmtScope::value>(0);
  static constexpr YAML::FmtScope::value kScope1 =
      static_cast<YAML::FmtScope::value>(1);
};

TEST_F(EmitterStateTest_494, AcceptsLowerNull_494) {
  EXPECT_TRUE(state.SetNullFormat(YAML::LowerNull, kScope0));
  EXPECT_EQ(state.GetNullFormat(), YAML::LowerNull);
}

TEST_F(EmitterStateTest_494, AcceptsUpperNull_494) {
  EXPECT_TRUE(state.SetNullFormat(YAML::UpperNull, kScope0));
  EXPECT_EQ(state.GetNullFormat(), YAML::UpperNull);
}

TEST_F(EmitterStateTest_494, AcceptsCamelNull_494) {
  EXPECT_TRUE(state.SetNullFormat(YAML::CamelNull, kScope0));
  EXPECT_EQ(state.GetNullFormat(), YAML::CamelNull);
}

TEST_F(EmitterStateTest_494, AcceptsTildeNull_494) {
  EXPECT_TRUE(state.SetNullFormat(YAML::TildeNull, kScope0));
  EXPECT_EQ(state.GetNullFormat(), YAML::TildeNull);
}

TEST_F(EmitterStateTest_494, RejectsNonNullManipulatorsAndDoesNotChangeValue_494) {
  // Establish a known baseline.
  ASSERT_TRUE(state.SetNullFormat(YAML::LowerNull, kScope0));
  const YAML::EMITTER_MANIP before = state.GetNullFormat();

  // A few representative non-null manipulators (different "categories").
  EXPECT_FALSE(state.SetNullFormat(YAML::Auto, kScope0));
  EXPECT_EQ(state.GetNullFormat(), before);

  EXPECT_FALSE(state.SetNullFormat(YAML::TrueFalseBool, kScope0));
  EXPECT_EQ(state.GetNullFormat(), before);

  EXPECT_FALSE(state.SetNullFormat(YAML::Dec, kScope0));
  EXPECT_EQ(state.GetNullFormat(), before);

  EXPECT_FALSE(state.SetNullFormat(YAML::Key, kScope0));
  EXPECT_EQ(state.GetNullFormat(), before);
}

TEST_F(EmitterStateTest_494, SuccessfulSetUpdatesValueForDifferentScopes_494) {
  EXPECT_TRUE(state.SetNullFormat(YAML::LowerNull, kScope0));
  EXPECT_EQ(state.GetNullFormat(), YAML::LowerNull);

  // Whatever the scope semantics are, a successful set should be observable via GetNullFormat().
  EXPECT_TRUE(state.SetNullFormat(YAML::UpperNull, kScope1));
  EXPECT_EQ(state.GetNullFormat(), YAML::UpperNull);

  EXPECT_TRUE(state.SetNullFormat(YAML::TildeNull, kScope0));
  EXPECT_EQ(state.GetNullFormat(), YAML::TildeNull);
}

TEST_F(EmitterStateTest_494, RejectsNonNullManipulatorForDifferentScope_494) {
  ASSERT_TRUE(state.SetNullFormat(YAML::CamelNull, kScope0));
  const YAML::EMITTER_MANIP before = state.GetNullFormat();

  EXPECT_FALSE(state.SetNullFormat(YAML::Hex, kScope1));
  EXPECT_EQ(state.GetNullFormat(), before);
}

}  // namespace