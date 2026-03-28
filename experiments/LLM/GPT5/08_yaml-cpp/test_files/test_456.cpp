// TEST_ID: 456
#include <gtest/gtest.h>

#include "emitterstate.h"

#include <type_traits>
#include <utility>

namespace {

class EmitterStateBoolLengthFormatTest_456 : public ::testing::Test {};

TEST_F(EmitterStateBoolLengthFormatTest_456, DefaultConstruction_ReturnsStableValue_456) {
  YAML::EmitterState state;

  YAML::EMITTER_MANIP v1{};
  YAML::EMITTER_MANIP v2{};
  EXPECT_NO_THROW(v1 = state.GetBoolLengthFormat());
  EXPECT_NO_THROW(v2 = state.GetBoolLengthFormat());

  // Observable behavior: repeated calls should be consistent for an unmodified object.
  EXPECT_EQ(v1, v2);
}

TEST_F(EmitterStateBoolLengthFormatTest_456, CanBeCalledOnConstInstance_456) {
  const YAML::EmitterState state;

  YAML::EMITTER_MANIP v1{};
  YAML::EMITTER_MANIP v2{};
  EXPECT_NO_THROW(v1 = state.GetBoolLengthFormat());
  EXPECT_NO_THROW(v2 = state.GetBoolLengthFormat());

  EXPECT_EQ(v1, v2);
}

TEST_F(EmitterStateBoolLengthFormatTest_456, CopyConstruction_PreservesReturnedValue_456) {
  YAML::EmitterState original;
  const YAML::EMITTER_MANIP before = original.GetBoolLengthFormat();

  YAML::EmitterState copied(original);
  const YAML::EMITTER_MANIP after = copied.GetBoolLengthFormat();

  EXPECT_EQ(before, after);
}

TEST_F(EmitterStateBoolLengthFormatTest_456, MoveConstruction_MovedToPreservesReturnedValue_456) {
  YAML::EmitterState original;
  const YAML::EMITTER_MANIP before = original.GetBoolLengthFormat();

  YAML::EmitterState moved_to(std::move(original));
  const YAML::EMITTER_MANIP after = moved_to.GetBoolLengthFormat();

  EXPECT_EQ(before, after);

  // Moved-from objects should remain in a valid state per C++ conventions; at minimum,
  // calling a const getter should not throw.
  EXPECT_NO_THROW((void)original.GetBoolLengthFormat());
}

}  // namespace