// TEST_ID: 503
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateTest_503 : public ::testing::Test {
 protected:
  YAML::EmitterState state;

  static constexpr std::size_t kMaxDigits10 =
      std::numeric_limits<double>::max_digits10;

  // If yaml-cpp exposes different scope names in your version, adjust here.
  static constexpr YAML::FmtScope::value kLocal = YAML::FmtScope::Local;
  static constexpr YAML::FmtScope::value kGlobal = YAML::FmtScope::Global;
};

TEST_F(EmitterStateTest_503, SetDoublePrecisionAcceptsZero_Local_503) {
  const std::size_t before = state.GetDoublePrecision();

  EXPECT_TRUE(state.SetDoublePrecision(0u, kLocal));
  EXPECT_EQ(state.GetDoublePrecision(), 0u);

  // Sanity: the value actually changed if it differed before (not required, but
  // avoids relying on any presumed defaults).
  (void)before;
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionAcceptsMaxDigits10_Local_503) {
  EXPECT_TRUE(state.SetDoublePrecision(kMaxDigits10, kLocal));
  EXPECT_EQ(state.GetDoublePrecision(), kMaxDigits10);
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionRejectsAboveMaxDigits10_Local_503) {
  const std::size_t before = state.GetDoublePrecision();

  EXPECT_FALSE(state.SetDoublePrecision(kMaxDigits10 + 1u, kLocal));
  // If the setter reports failure, the observable precision should remain unchanged.
  EXPECT_EQ(state.GetDoublePrecision(), before);
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionRejectsSizeTMax_Local_503) {
  const std::size_t before = state.GetDoublePrecision();

  EXPECT_FALSE(state.SetDoublePrecision(std::numeric_limits<std::size_t>::max(), kLocal));
  EXPECT_EQ(state.GetDoublePrecision(), before);
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionAcceptsOne_Global_503) {
  EXPECT_TRUE(state.SetDoublePrecision(1u, kGlobal));
  EXPECT_EQ(state.GetDoublePrecision(), 1u);
}

TEST_F(EmitterStateTest_503, SetDoublePrecisionBoundaryAndThenFailure_DoesNotOverwrite_Global_503) {
  EXPECT_TRUE(state.SetDoublePrecision(kMaxDigits10, kGlobal));
  EXPECT_EQ(state.GetDoublePrecision(), kMaxDigits10);

  const std::size_t before = state.GetDoublePrecision();
  EXPECT_FALSE(state.SetDoublePrecision(kMaxDigits10 + 1u, kGlobal));
  EXPECT_EQ(state.GetDoublePrecision(), before);
}

}  // namespace