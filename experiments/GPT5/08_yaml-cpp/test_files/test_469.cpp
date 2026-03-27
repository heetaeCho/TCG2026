// File: ./TestProjects/yaml-cpp/test/emitterstate_setalias_test_469.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace YAML {

class EmitterStateTest_469 : public ::testing::Test {
protected:
  EmitterState state;
};

TEST_F(EmitterStateTest_469, SetAliasMakesHasAliasTrue_469) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_469, SetAliasIsIdempotentAndStaysTrue_469) {
  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());

  state.SetAlias();
  EXPECT_TRUE(state.HasAlias());
}

TEST_F(EmitterStateTest_469, SetAliasDoesNotThrow_469) {
  EXPECT_NO_THROW(state.SetAlias());
  EXPECT_TRUE(state.HasAlias());
}

}  // namespace YAML