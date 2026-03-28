// File: ./TestProjects/yaml-cpp/test/settingchanges_test_440.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "setting.h"

namespace {

using YAML::SettingChanges;

// Compile-time interface/semantics verification (no private access, black-box friendly).
static_assert(std::is_default_constructible<SettingChanges>::value,
              "SettingChanges should be default constructible");

static_assert(!std::is_copy_constructible<SettingChanges>::value,
              "SettingChanges copy ctor must be deleted");
static_assert(!std::is_copy_assignable<SettingChanges>::value,
              "SettingChanges copy assignment must be deleted");

static_assert(std::is_move_constructible<SettingChanges>::value,
              "SettingChanges should be move constructible");
static_assert(std::is_move_assignable<SettingChanges>::value,
              "SettingChanges should be move assignable");

// clear() / restore() are declared YAML_CPP_NOEXCEPT in the provided dependency snippet.
// Verify they are noexcept at the call site.
static_assert(noexcept(std::declval<SettingChanges&>().clear()),
              "SettingChanges::clear() must be noexcept");
static_assert(noexcept(std::declval<SettingChanges&>().restore()),
              "SettingChanges::restore() must be noexcept");

// Move assignment is declared YAML_CPP_NOEXCEPT in the provided dependency snippet.
// Verify it is noexcept at the call site.
static_assert(noexcept(std::declval<SettingChanges&>() = std::declval<SettingChanges&&>()),
              "SettingChanges move assignment must be noexcept");

class SettingChangesTest_440 : public ::testing::Test {};

}  // namespace

TEST_F(SettingChangesTest_440, DefaultConstructAndClearNoThrow_440) {
  SettingChanges changes;
  EXPECT_NO_THROW(changes.clear());
}

TEST_F(SettingChangesTest_440, DefaultConstructAndRestoreNoThrow_440) {
  SettingChanges changes;
  EXPECT_NO_THROW(changes.restore());
}

TEST_F(SettingChangesTest_440, ClearIsIdempotentNoThrow_440) {
  SettingChanges changes;

  EXPECT_NO_THROW(changes.clear());
  EXPECT_NO_THROW(changes.clear());
  EXPECT_NO_THROW(changes.clear());
}

TEST_F(SettingChangesTest_440, RestoreOnEmptyNoThrow_440) {
  SettingChanges changes;

  // Boundary: restore with no prior pushes/changes.
  EXPECT_NO_THROW(changes.restore());
  EXPECT_NO_THROW(changes.restore());
}

TEST_F(SettingChangesTest_440, ClearThenRestoreNoThrow_440) {
  SettingChanges changes;

  EXPECT_NO_THROW(changes.clear());
  EXPECT_NO_THROW(changes.restore());
}

TEST_F(SettingChangesTest_440, MoveConstructThenOperationsNoThrow_440) {
  SettingChanges original;
  // Move construct (normal operation)
  SettingChanges moved(std::move(original));

  // Observable behavior here is that calls must not throw (noexcept contract).
  EXPECT_NO_THROW(moved.clear());
  EXPECT_NO_THROW(moved.restore());

  // Moved-from object should remain usable for these noexcept operations.
  EXPECT_NO_THROW(original.clear());
  EXPECT_NO_THROW(original.restore());
}

TEST_F(SettingChangesTest_440, MoveAssignThenOperationsNoThrow_440) {
  SettingChanges a;
  SettingChanges b;

  // Normal operation: move assignment
  EXPECT_NO_THROW(b = std::move(a));

  EXPECT_NO_THROW(b.clear());
  EXPECT_NO_THROW(b.restore());

  // Moved-from object should remain usable for these noexcept operations.
  EXPECT_NO_THROW(a.clear());
  EXPECT_NO_THROW(a.restore());
}

TEST_F(SettingChangesTest_440, SelfMoveAssignDoesNotThrowForNoexceptOps_440) {
  SettingChanges changes;

  // Self-move assignment is a boundary case. Behavior is not specified beyond compilation,
  // so we don't assert equivalence of state. We only assert that the object remains usable
  // for noexcept operations afterwards.
  changes = std::move(changes);

  EXPECT_NO_THROW(changes.clear());
  EXPECT_NO_THROW(changes.restore());
}