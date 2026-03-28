// File: emitterstate_set_bool_length_format_test_492.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/emitterstate.h>
#include <yaml-cpp/emittermanip.h>

namespace {

class EmitterStateSetBoolLengthFormatTest_492 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;

  // We don't assume any specific named enumerators exist for FmtScope::value.
  // Using numeric casts keeps the test focused on observable behavior.
  static constexpr YAML::FmtScope::value kScope0 =
      static_cast<YAML::FmtScope::value>(0);
  static constexpr YAML::FmtScope::value kScope1 =
      static_cast<YAML::FmtScope::value>(1);
};

TEST_F(EmitterStateSetBoolLengthFormatTest_492, AcceptsLongBoolAndUpdatesGetter_492) {
  const bool ok = state_.SetBoolLengthFormat(YAML::LongBool, kScope0);
  EXPECT_TRUE(ok);
  EXPECT_EQ(state_.GetBoolLengthFormat(), YAML::LongBool);
}

TEST_F(EmitterStateSetBoolLengthFormatTest_492, AcceptsShortBoolAndUpdatesGetter_492) {
  const bool ok = state_.SetBoolLengthFormat(YAML::ShortBool, kScope0);
  EXPECT_TRUE(ok);
  EXPECT_EQ(state_.GetBoolLengthFormat(), YAML::ShortBool);
}

TEST_F(EmitterStateSetBoolLengthFormatTest_492, RejectsNonBoolLengthManipAndDoesNotChangeValue_492) {
  // Establish a known value first.
  ASSERT_TRUE(state_.SetBoolLengthFormat(YAML::LongBool, kScope0));
  const auto before = state_.GetBoolLengthFormat();

  // Use a clearly unrelated manip.
  const bool ok = state_.SetBoolLengthFormat(YAML::Auto, kScope0);
  EXPECT_FALSE(ok);
  EXPECT_EQ(state_.GetBoolLengthFormat(), before);
}

TEST_F(EmitterStateSetBoolLengthFormatTest_492, RejectsAnotherNonBoolLengthManipAndDoesNotChangeValue_492) {
  ASSERT_TRUE(state_.SetBoolLengthFormat(YAML::ShortBool, kScope0));
  const auto before = state_.GetBoolLengthFormat();

  // Another unrelated manip.
  const bool ok = state_.SetBoolLengthFormat(YAML::YesNoBool, kScope0);
  EXPECT_FALSE(ok);
  EXPECT_EQ(state_.GetBoolLengthFormat(), before);
}

TEST_F(EmitterStateSetBoolLengthFormatTest_492, MultipleSuccessfulCallsLastOneWins_492) {
  ASSERT_TRUE(state_.SetBoolLengthFormat(YAML::LongBool, kScope0));
  EXPECT_EQ(state_.GetBoolLengthFormat(), YAML::LongBool);

  ASSERT_TRUE(state_.SetBoolLengthFormat(YAML::ShortBool, kScope0));
  EXPECT_EQ(state_.GetBoolLengthFormat(), YAML::ShortBool);
}

TEST_F(EmitterStateSetBoolLengthFormatTest_492, WorksAcrossDifferentScopesObservableValueUpdates_492) {
  // We do not assume scope semantics beyond "it is accepted by the interface".
  ASSERT_TRUE(state_.SetBoolLengthFormat(YAML::LongBool, kScope0));
  EXPECT_EQ(state_.GetBoolLengthFormat(), YAML::LongBool);

  ASSERT_TRUE(state_.SetBoolLengthFormat(YAML::ShortBool, kScope1));
  EXPECT_EQ(state_.GetBoolLengthFormat(), YAML::ShortBool);
}

}  // namespace