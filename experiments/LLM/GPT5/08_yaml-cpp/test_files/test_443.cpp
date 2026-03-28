// File: ./TestProjects/yaml-cpp/test/setting_changes_test_443.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "setting.h"  // adjust include path if your test target uses a different include style

namespace {

class SettingChangesTest_443 : public ::testing::Test {};

TEST_F(SettingChangesTest_443, TypeTraits_CopyDeleted_MoveEnabled_443) {
  using YAML::SettingChanges;

  EXPECT_FALSE(std::is_copy_constructible<SettingChanges>::value);
  EXPECT_FALSE(std::is_copy_assignable<SettingChanges>::value);

  EXPECT_TRUE(std::is_move_constructible<SettingChanges>::value);
  EXPECT_TRUE(std::is_move_assignable<SettingChanges>::value);
}

TEST_F(SettingChangesTest_443, DefaultConstructAndEmptyOperationsDoNotThrow_443) {
  YAML::SettingChanges changes;

  // Observable behavior: these should be safe on an empty container.
  EXPECT_NO_THROW(changes.clear());
  EXPECT_NO_THROW(changes.restore());

  // Idempotency-like checks (still black-box: just verify no exceptions).
  EXPECT_NO_THROW(changes.clear());
  EXPECT_NO_THROW(changes.restore());
}

TEST_F(SettingChangesTest_443, PushNullptrDoesNotThrow_443) {
  YAML::SettingChanges changes;

  std::unique_ptr<YAML::SettingChangeBase> nullChange;
  EXPECT_NO_THROW(changes.push(std::move(nullChange)));

  // After push, the source unique_ptr should be empty.
  EXPECT_EQ(nullChange.get(), nullptr);

  // Subsequent operations should remain safe.
  EXPECT_NO_THROW(changes.clear());
  EXPECT_NO_THROW(changes.restore());
}

TEST_F(SettingChangesTest_443, MoveConstructionLeavesBothObjectsOperable_443) {
  YAML::SettingChanges original;
  std::unique_ptr<YAML::SettingChangeBase> nullChange;
  ASSERT_NO_THROW(original.push(std::move(nullChange)));

  // Move-construct.
  YAML::SettingChanges moved(std::move(original));

  // Both objects should remain valid to call public API on.
  EXPECT_NO_THROW(moved.clear());
  EXPECT_NO_THROW(moved.restore());

  EXPECT_NO_THROW(original.clear());
  EXPECT_NO_THROW(original.restore());
}

TEST_F(SettingChangesTest_443, MoveAssignmentLeavesBothObjectsOperable_443) {
  YAML::SettingChanges src;
  YAML::SettingChanges dst;

  std::unique_ptr<YAML::SettingChangeBase> nullChange;
  ASSERT_NO_THROW(src.push(std::move(nullChange)));

  // Move-assign.
  EXPECT_NO_THROW(dst = std::move(src));

  // Both objects should remain valid to call public API on.
  EXPECT_NO_THROW(dst.clear());
  EXPECT_NO_THROW(dst.restore());

  EXPECT_NO_THROW(src.clear());
  EXPECT_NO_THROW(src.restore());
}

}  // namespace