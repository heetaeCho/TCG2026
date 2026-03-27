// File: emitterstate_curindent_test_447.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <cstddef>

#include "emitterstate.h"

namespace {

class EmitterStateTest_447 : public ::testing::Test {};

TEST_F(EmitterStateTest_447, CurIndent_ReturnTypeIsSizeT_447) {
  // Compile-time contract: the interface returns std::size_t.
  static_assert(std::is_same_v<decltype(std::declval<const YAML::EmitterState&>().CurIndent()),
                               std::size_t>,
                "CurIndent() must return std::size_t");
}

TEST_F(EmitterStateTest_447, CurIndent_CanBeCalledOnConstObject_447) {
  const YAML::EmitterState state;
  // Observable behavior: callable on const object, returns a value.
  const std::size_t indent = state.CurIndent();
  (void)indent;  // No assumptions about the numeric value.
}

TEST_F(EmitterStateTest_447, CurIndent_IsStableAcrossRepeatedCallsWithoutChanges_447) {
  const YAML::EmitterState state;

  const std::size_t first = state.CurIndent();
  const std::size_t second = state.CurIndent();
  const std::size_t third = state.CurIndent();

  // Observable behavior: calling a const getter repeatedly should not mutate state.
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(EmitterStateTest_447, CurIndent_DoesNotThrowAfterCommonStateCalls_447) {
  YAML::EmitterState state;

  // We do not assume these calls affect indent; we only verify CurIndent remains callable
  // and the object remains usable through its public interface.
  EXPECT_NO_THROW(state.SetAnchor());
  EXPECT_NO_THROW(state.SetAlias());
  EXPECT_NO_THROW(state.SetTag());
  EXPECT_NO_THROW(state.SetNonContent());
  EXPECT_NO_THROW(state.StartedDoc());
  EXPECT_NO_THROW(state.StartedScalar());
  EXPECT_NO_THROW(state.EndedDoc());
  EXPECT_NO_THROW(state.SetError("test error"));

  EXPECT_NO_THROW({
    const std::size_t indent = state.CurIndent();
    (void)indent;
  });
}

}  // namespace