// File: emitterstate_test_444.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/emitterstate.h"

namespace {

class EmitterStateTest_444 : public ::testing::Test {};

TEST_F(EmitterStateTest_444, DefaultConstructedObjectIsGood_444) {
  YAML::EmitterState state;

  // Common expectation for an "EmitterState": a fresh state should be usable.
  // If the implementation defines otherwise, this test will reveal it.
  EXPECT_TRUE(state.good());
}

TEST_F(EmitterStateTest_444, GoodIsStableAcrossRepeatedCalls_444) {
  YAML::EmitterState state;

  const bool first = state.good();
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(first, state.good());
  }
}

TEST_F(EmitterStateTest_444, GoodCanBeCalledOnConstInstance_444) {
  const YAML::EmitterState state;
  EXPECT_NO_THROW({
    const bool v = state.good();
    (void)v;
  });
}

TEST_F(EmitterStateTest_444, CopyPreservesObservableGoodValue_444) {
  YAML::EmitterState original;
  const bool before = original.good();

  YAML::EmitterState copy = original;
  EXPECT_EQ(before, copy.good());

  // Also ensure calling good() on the copy doesn't affect the original's observable result.
  (void)copy.good();
  EXPECT_EQ(before, original.good());
}

}  // namespace