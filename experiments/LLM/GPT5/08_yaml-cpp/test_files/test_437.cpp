// TEST_ID: 437
#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "setting.h"

namespace {

using YAML::Setting;
using YAML::SettingChange;
using YAML::SettingChangeBase;

TEST(SettingChangeTest_437, SetReturnsNonNullChangeHandle_437) {
  Setting<int> s;
  auto change = s.set(123);
  ASSERT_NE(change, nullptr);
}

TEST(SettingChangeTest_437, PopRestoresPreviousValue_Int_437) {
  Setting<int> s;
  ASSERT_EQ(s.get(), 0);

  auto change = s.set(42);
  ASSERT_EQ(s.get(), 42);

  change->pop();
  EXPECT_EQ(s.get(), 0);
}

TEST(SettingChangeTest_437, PopRestoresPreviousValue_String_437) {
  Setting<std::string> s("alpha");
  ASSERT_EQ(s.get(), "alpha");

  auto change = s.set("beta");
  ASSERT_EQ(s.get(), "beta");

  change->pop();
  EXPECT_EQ(s.get(), "alpha");
}

TEST(SettingChangeTest_437, PopRestoresEvenIfSetToSameValue_437) {
  Setting<int> s(7);
  ASSERT_EQ(s.get(), 7);

  auto change = s.set(7);
  ASSERT_EQ(s.get(), 7);

  change->pop();
  EXPECT_EQ(s.get(), 7);
}

TEST(SettingChangeTest_437, SettingChangeIsNotCopyableOrMovable_437) {
  EXPECT_FALSE(std::is_copy_constructible_v<SettingChange<int>>);
  EXPECT_FALSE(std::is_copy_assignable_v<SettingChange<int>>);
  EXPECT_FALSE(std::is_move_constructible_v<SettingChange<int>>);
  EXPECT_FALSE(std::is_move_assignable_v<SettingChange<int>>);
}

TEST(SettingChangeTest_437, ChangeHandleIsPolymorphicBase_437) {
  Setting<int> s;
  std::unique_ptr<SettingChangeBase> change = s.set(1);
  ASSERT_NE(change, nullptr);

  // Only verifies that calling through the base is valid and observable.
  ASSERT_EQ(s.get(), 1);
  change->pop();
  EXPECT_EQ(s.get(), 0);
}

}  // namespace