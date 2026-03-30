// TEST_ID: 436
#include <gtest/gtest.h>

#include <string>

#include "setting.h"

namespace {

class SettingTest_436 : public ::testing::Test {};

TEST_F(SettingTest_436, DefaultConstructedGetReturnsDefaultValue_436) {
  YAML::Setting<int> s_int;
  EXPECT_EQ(s_int.get(), int{});

  YAML::Setting<bool> s_bool;
  EXPECT_EQ(s_bool.get(), bool{});

  YAML::Setting<std::string> s_str;
  EXPECT_EQ(s_str.get(), std::string{});
}

TEST_F(SettingTest_436, RestoreCopiesValueFromOldSetting_Int_436) {
  YAML::Setting<int> old_setting;
  (void)old_setting.set(123);

  YAML::Setting<int> current;
  (void)current.set(-7);

  EXPECT_NO_THROW(current.restore(old_setting));
  EXPECT_EQ(current.get(), old_setting.get());
  EXPECT_EQ(current.get(), 123);
}

TEST_F(SettingTest_436, RestoreDoesNotModifyOldSetting_Int_436) {
  YAML::Setting<int> old_setting;
  (void)old_setting.set(42);

  YAML::Setting<int> current;
  (void)current.set(0);

  current.restore(old_setting);

  // Old setting remains unchanged by restore().
  EXPECT_EQ(old_setting.get(), 42);
  EXPECT_EQ(current.get(), 42);
}

TEST_F(SettingTest_436, RestoreFromDefaultSettingResetsToDefault_Int_436) {
  YAML::Setting<int> default_setting;  // default value

  YAML::Setting<int> current;
  (void)current.set(999);

  current.restore(default_setting);
  EXPECT_EQ(current.get(), int{});
}

TEST_F(SettingTest_436, SelfRestoreKeepsValue_String_436) {
  YAML::Setting<std::string> s;
  (void)s.set(std::string("hello"));

  // Restoring from itself should leave the value as-is.
  EXPECT_NO_THROW(s.restore(s));
  EXPECT_EQ(s.get(), "hello");
}

TEST_F(SettingTest_436, RestoreCopiesValueFromOldSetting_String_436) {
  YAML::Setting<std::string> old_setting;
  (void)old_setting.set(std::string("old"));

  YAML::Setting<std::string> current;
  (void)current.set(std::string("new"));

  current.restore(old_setting);
  EXPECT_EQ(current.get(), "old");
  EXPECT_EQ(old_setting.get(), "old");
}

TEST_F(SettingTest_436, RestoreCopiesValueFromOldSetting_Bool_436) {
  YAML::Setting<bool> old_setting;
  (void)old_setting.set(true);

  YAML::Setting<bool> current;
  (void)current.set(false);

  current.restore(old_setting);
  EXPECT_EQ(current.get(), true);
  EXPECT_EQ(old_setting.get(), true);
}

}  // namespace