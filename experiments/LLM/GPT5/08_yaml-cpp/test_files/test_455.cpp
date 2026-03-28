// TEST_ID: 455
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "emitterstate.h"

namespace {

TEST(EmitterStateTest_455, GetBoolFormat_HasExpectedReturnType_455) {
  using YAML::EmitterState;

  // Verifies the getter is callable on a const object and returns EMITTER_MANIP.
  static_assert(
      std::is_same_v<decltype(std::declval<const EmitterState&>().GetBoolFormat()),
                     YAML::EMITTER_MANIP>,
      "GetBoolFormat() must return YAML::EMITTER_MANIP");
}

TEST(EmitterStateTest_455, GetBoolFormat_IsStableAcrossCalls_455) {
  YAML::EmitterState state;

  const auto first = state.GetBoolFormat();
  const auto second = state.GetBoolFormat();

  EXPECT_EQ(first, second);
}

TEST(EmitterStateTest_455, GetBoolFormat_OnConstObject_IsStableAcrossCalls_455) {
  const YAML::EmitterState state;

  const auto first = state.GetBoolFormat();
  const auto second = state.GetBoolFormat();

  EXPECT_EQ(first, second);
}

TEST(EmitterStateTest_455, CopyConstruction_PreservesBoolFormat_455) {
  YAML::EmitterState original;
  const auto original_fmt = original.GetBoolFormat();

  YAML::EmitterState copy = original;
  EXPECT_EQ(copy.GetBoolFormat(), original_fmt);
  EXPECT_EQ(copy.GetBoolFormat(), original.GetBoolFormat());
}

TEST(EmitterStateTest_455, CopyAssignment_PreservesBoolFormat_455) {
  YAML::EmitterState source;
  const auto source_fmt = source.GetBoolFormat();

  YAML::EmitterState target;
  target = source;

  EXPECT_EQ(target.GetBoolFormat(), source_fmt);
  EXPECT_EQ(target.GetBoolFormat(), source.GetBoolFormat());
}

TEST(EmitterStateTest_455, MoveConstruction_PreservesBoolFormatInMovedTo_455) {
  YAML::EmitterState original;
  const auto original_fmt = original.GetBoolFormat();

  YAML::EmitterState moved_to(std::move(original));
  EXPECT_EQ(moved_to.GetBoolFormat(), original_fmt);
}

TEST(EmitterStateTest_455, MoveAssignment_PreservesBoolFormatInMovedTo_455) {
  YAML::EmitterState source;
  const auto source_fmt = source.GetBoolFormat();

  YAML::EmitterState target;
  target = std::move(source);

  EXPECT_EQ(target.GetBoolFormat(), source_fmt);
}

}  // namespace