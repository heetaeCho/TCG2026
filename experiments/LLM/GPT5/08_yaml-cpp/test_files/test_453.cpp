// TEST_ID: 453
#include <gtest/gtest.h>

#include "emitterstate.h"

// Some builds expose common emitter manipulators via yaml-cpp headers.
// We avoid assuming SetOutputCharset must accept any specific manipulator:
// if SetOutputCharset(value, scope) returns true, we verify the getter reflects it;
// otherwise we verify the getter did not change.
namespace {

class EmitterStateTest_453 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_453, GetOutputCharset_IsStableAcrossCalls_453) {
  const auto first = state.GetOutputCharset();
  EXPECT_EQ(state.GetOutputCharset(), first);
  EXPECT_EQ(state.GetOutputCharset(), first);
}

TEST_F(EmitterStateTest_453, GetOutputCharset_CanBeCalledOnConstObject_453) {
  const YAML::EmitterState& cref = state;
  const auto v1 = cref.GetOutputCharset();
  const auto v2 = cref.GetOutputCharset();
  EXPECT_EQ(v1, v2);
}

TEST_F(EmitterStateTest_453, SetOutputCharset_IfAcceptedGetterReflectsNewValue_453) {
  const auto original = state.GetOutputCharset();

  // These are commonly available charset-related manipulators in yaml-cpp.
  // If your build exposes different ones, adjust accordingly.
  const YAML::EMITTER_MANIP candidate1 = YAML::EscapeNonAscii;
  const YAML::EMITTER_MANIP candidate2 = YAML::EmitNonAscii;

  // Try candidate1 at GLOBAL scope.
  {
    const bool ok = state.SetOutputCharset(candidate1, YAML::FmtScope::GLOBAL);
    if (ok) {
      EXPECT_EQ(state.GetOutputCharset(), candidate1);
    } else {
      EXPECT_EQ(state.GetOutputCharset(), original);
    }
  }

  // Try candidate2 at LOCAL scope.
  {
    const auto before = state.GetOutputCharset();
    const bool ok = state.SetOutputCharset(candidate2, YAML::FmtScope::LOCAL);
    if (ok) {
      EXPECT_EQ(state.GetOutputCharset(), candidate2);
    } else {
      EXPECT_EQ(state.GetOutputCharset(), before);
    }
  }
}

TEST_F(EmitterStateTest_453, SetOutputCharset_SameValueDoesNotChangeGetter_453) {
  const auto before = state.GetOutputCharset();

  const bool ok = state.SetOutputCharset(before, YAML::FmtScope::GLOBAL);
  // Regardless of whether the setter reports success, the observable getter value
  // should remain equal to what we attempted to (re)set it to.
  EXPECT_EQ(state.GetOutputCharset(), before);

  // If the setter reports failure, we still require no observable change.
  if (!ok) {
    EXPECT_EQ(state.GetOutputCharset(), before);
  }
}

}  // namespace