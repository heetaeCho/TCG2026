// TEST_ID: 461
#include <gtest/gtest.h>

#include <limits>

#include "emitterstate.h"  // from ./TestProjects/yaml-cpp/src/emitterstate.h

namespace {

class EmitterStateTest_461 : public ::testing::Test {
 protected:
  YAML::EmitterState state_;
};

TEST_F(EmitterStateTest_461, GetPreCommentIndent_IsStableAcrossMultipleCalls_461) {
  const std::size_t first = state_.GetPreCommentIndent();
  const std::size_t second = state_.GetPreCommentIndent();
  const std::size_t third = state_.GetPreCommentIndent();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(EmitterStateTest_461, GetPreCommentIndent_DefaultValueIsDeterministicAcrossInstances_461) {
  YAML::EmitterState other;
  EXPECT_EQ(state_.GetPreCommentIndent(), other.GetPreCommentIndent());
}

TEST_F(EmitterStateTest_461, SetPreCommentIndent_WhenAccepted_UpdatesGetter_LocalScope_461) {
  const std::size_t before = state_.GetPreCommentIndent();

  const std::size_t desired = before + 1;
  const bool ok = state_.SetPreCommentIndent(desired, YAML::FmtScope::LOCAL);

  if (ok) {
    EXPECT_EQ(state_.GetPreCommentIndent(), desired);
  } else {
    // Observable behavior: if not accepted, it should not claim it changed.
    EXPECT_EQ(state_.GetPreCommentIndent(), before);
  }
}

TEST_F(EmitterStateTest_461, SetPreCommentIndent_WhenAccepted_UpdatesGetter_GlobalScope_461) {
  const std::size_t before = state_.GetPreCommentIndent();

  const std::size_t desired = before + 2;
  const bool ok = state_.SetPreCommentIndent(desired, YAML::FmtScope::GLOBAL);

  if (ok) {
    EXPECT_EQ(state_.GetPreCommentIndent(), desired);
  } else {
    EXPECT_EQ(state_.GetPreCommentIndent(), before);
  }
}

TEST_F(EmitterStateTest_461, SetPreCommentIndent_BoundaryValueZero_461) {
  const std::size_t before = state_.GetPreCommentIndent();

  const bool ok = state_.SetPreCommentIndent(0u, YAML::FmtScope::LOCAL);

  if (ok) {
    EXPECT_EQ(state_.GetPreCommentIndent(), 0u);
  } else {
    EXPECT_EQ(state_.GetPreCommentIndent(), before);
  }
}

TEST_F(EmitterStateTest_461, SetPreCommentIndent_BoundaryValueMaxSizeT_461) {
  const std::size_t before = state_.GetPreCommentIndent();

  const std::size_t maxv = (std::numeric_limits<std::size_t>::max)();
  const bool ok = state_.SetPreCommentIndent(maxv, YAML::FmtScope::LOCAL);

  if (ok) {
    EXPECT_EQ(state_.GetPreCommentIndent(), maxv);
  } else {
    EXPECT_EQ(state_.GetPreCommentIndent(), before);
  }
}

TEST_F(EmitterStateTest_461, SetPreCommentIndent_RepeatedSets_LastAcceptedValueWins_461) {
  const std::size_t initial = state_.GetPreCommentIndent();

  const bool ok1 = state_.SetPreCommentIndent(1u, YAML::FmtScope::LOCAL);
  const std::size_t after1 = state_.GetPreCommentIndent();

  const bool ok2 = state_.SetPreCommentIndent(2u, YAML::FmtScope::LOCAL);
  const std::size_t after2 = state_.GetPreCommentIndent();

  // Only assert what is observable and safe:
  // - If a set call returns true, getter must reflect that exact value.
  // - If it returns false, getter must remain unchanged from immediately before that call.
  if (ok1) {
    EXPECT_EQ(after1, 1u);
  } else {
    EXPECT_EQ(after1, initial);
  }

  if (ok2) {
    EXPECT_EQ(after2, 2u);
  } else {
    EXPECT_EQ(after2, after1);
  }
}

}  // namespace