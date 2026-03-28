// TEST_ID: 445
#include <gtest/gtest.h>

#include "emitterstate.h"

namespace {

class EmitterStateTest_445 : public ::testing::Test {};

TEST_F(EmitterStateTest_445, GetLastError_DefaultConstructedIsEmpty_445) {
  YAML::EmitterState state;
  const std::string err = state.GetLastError();

  // For a freshly constructed state, last error is expected to be empty.
  EXPECT_TRUE(err.empty());
}

TEST_F(EmitterStateTest_445, GetLastError_CanBeCalledOnConstObject_445) {
  const YAML::EmitterState state;

  const std::string err = state.GetLastError();
  (void)err;  // Just verify it compiles/works on const; assert basic validity below.

  EXPECT_GE(err.size(), 0u);
}

TEST_F(EmitterStateTest_445, GetLastError_RepeatedCallsAreStable_445) {
  YAML::EmitterState state;

  const std::string first = state.GetLastError();
  const std::string second = state.GetLastError();

  EXPECT_EQ(first, second);
}

TEST_F(EmitterStateTest_445, GetLastError_DoesNotThrow_445) {
  YAML::EmitterState state;

  EXPECT_NO_THROW({
    const std::string err = state.GetLastError();
    (void)err;
  });
}

}  // namespace