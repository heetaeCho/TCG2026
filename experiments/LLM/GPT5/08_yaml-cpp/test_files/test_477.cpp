// TEST_ID: 477
#include <gtest/gtest.h>

#include "yaml-cpp/emitterstate.h"

namespace YAML {

class EmitterStateTest_477 : public ::testing::Test {
 protected:
  EmitterState state;
};

TEST_F(EmitterStateTest_477, StartedScalarMarksBegunNode_477) {
  EXPECT_NO_THROW(state.StartedScalar());
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_477, StartedScalarMarksBegunContent_477) {
  EXPECT_NO_THROW(state.StartedScalar());
  EXPECT_TRUE(state.HasBegunContent());
}

TEST_F(EmitterStateTest_477, StartedScalarIsCallableMultipleTimes_477) {
  EXPECT_NO_THROW(state.StartedScalar());
  EXPECT_NO_THROW(state.StartedScalar());
  EXPECT_TRUE(state.HasBegunNode());
}

TEST_F(EmitterStateTest_477, StartedScalarDoesNotClearExistingError_477) {
  state.SetError("some error");
  const std::string before = state.GetLastError();

  EXPECT_NO_THROW(state.StartedScalar());

  EXPECT_EQ(state.GetLastError(), before);
}

}  // namespace YAML