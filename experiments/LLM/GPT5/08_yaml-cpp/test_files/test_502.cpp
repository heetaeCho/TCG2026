// TEST_ID: 502
#include <gtest/gtest.h>

#include <limits>

#include "emitterstate.h"

namespace {

class EmitterStateTest_502 : public ::testing::Test {
protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_502, SetFloatPrecisionAcceptsZero_502) {
  const std::size_t v = 0;
  EXPECT_TRUE(state.SetFloatPrecision(v, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetFloatPrecision(), v);
}

TEST_F(EmitterStateTest_502, SetFloatPrecisionAcceptsMaxDigits10_502) {
  const std::size_t maxv =
      static_cast<std::size_t>(std::numeric_limits<float>::max_digits10);

  EXPECT_TRUE(state.SetFloatPrecision(maxv, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetFloatPrecision(), maxv);
}

TEST_F(EmitterStateTest_502, SetFloatPrecisionRejectsAboveMaxDigits10_502) {
  const std::size_t maxv =
      static_cast<std::size_t>(std::numeric_limits<float>::max_digits10);
  const std::size_t invalid = maxv + 1;

  EXPECT_FALSE(state.SetFloatPrecision(invalid, YAML::FmtScope::Global));
}

TEST_F(EmitterStateTest_502, SetFloatPrecisionRejectDoesNotChangeExistingValue_502) {
  const std::size_t maxv =
      static_cast<std::size_t>(std::numeric_limits<float>::max_digits10);

  // Establish a known good value first.
  ASSERT_TRUE(state.SetFloatPrecision(maxv, YAML::FmtScope::Global));
  ASSERT_EQ(state.GetFloatPrecision(), maxv);

  // Attempt an invalid value; should fail and leave observable state unchanged.
  EXPECT_FALSE(state.SetFloatPrecision(maxv + 1, YAML::FmtScope::Global));
  EXPECT_EQ(state.GetFloatPrecision(), maxv);
}

TEST_F(EmitterStateTest_502, SetFloatPrecisionWorksWithLocalScope_502) {
  const std::size_t v = 3;

  EXPECT_TRUE(state.SetFloatPrecision(v, YAML::FmtScope::Local));
  EXPECT_EQ(state.GetFloatPrecision(), v);
}

}  // n