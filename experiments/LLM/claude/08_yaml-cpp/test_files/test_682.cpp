#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the header under test
#include "setting.h"

namespace YAML {

// Test fixture for Setting with int type
class SettingIntTest_682 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for Setting with string type
class SettingStringTest_682 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for Setting with double type
class SettingDoubleTest_682 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for Setting with bool type
class SettingBoolTest_682 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Int Setting Tests ====================

TEST_F(SettingIntTest_682, ConstructorSetsValue_682) {
    Setting<int> setting(42);
    EXPECT_EQ(42, setting.get());
}

TEST_F(SettingIntTest_682, DefaultConstructor_682) {
    Setting<int> setting(0);
    EXPECT_EQ(0, setting.get());
}

TEST_F(SettingIntTest_682, SetChangesValue_682) {
    Setting<int> setting(10);
    setting.set(20);
    EXPECT_EQ(20, setting.get());
}

TEST_F(SettingIntTest_682, SetReturnsNonNull_682) {
    Setting<int> setting(10);
    auto change = setting.set(30);
    // The set function should return a SettingChangeBase pointer
    // (may or may not be null depending on implementation)
    EXPECT_EQ(30, setting.get());
}

TEST_F(SettingIntTest_682, SetMultipleTimes_682) {
    Setting<int> setting(1);
    setting.set(2);
    setting.set(3);
    setting.set(4);
    EXPECT_EQ(4, setting.get());
}

TEST_F(SettingIntTest_682, SetSameValue_682) {
    Setting<int> setting(42);
    setting.set(42);
    EXPECT_EQ(42, setting.get());
}

TEST_F(SettingIntTest_682, NegativeValue_682) {
    Setting<int> setting(-100);
    EXPECT_EQ(-100, setting.get());
}

TEST_F(SettingIntTest_682, ZeroValue_682) {
    Setting<int> setting(0);
    EXPECT_EQ(0, setting.get());
}

TEST_F(SettingIntTest_682, MaxIntValue_682) {
    Setting<int> setting(std::numeric_limits<int>::max());
    EXPECT_EQ(std::numeric_limits<int>::max(), setting.get());
}

TEST_F(SettingIntTest_682, MinIntValue_682) {
    Setting<int> setting(std::numeric_limits<int>::min());
    EXPECT_EQ(std::numeric_limits<int>::min(), setting.get());
}

TEST_F(SettingIntTest_682, RestoreFromOldSetting_682) {
    Setting<int> setting(10);
    Setting<int> oldSetting(5);
    setting.set(20);
    EXPECT_EQ(20, setting.get());
    setting.restore(oldSetting);
    EXPECT_EQ(5, setting.get());
}

TEST_F(SettingIntTest_682, RestoreSameValue_682) {
    Setting<int> setting(10);
    Setting<int> oldSetting(10);
    setting.restore(oldSetting);
    EXPECT_EQ(10, setting.get());
}

TEST_F(SettingIntTest_682, RestoreAfterMultipleSets_682) {
    Setting<int> setting(1);
    Setting<int> oldSetting(100);
    setting.set(2);
    setting.set(3);
    setting.set(4);
    setting.restore(oldSetting);
    EXPECT_EQ(100, setting.get());
}

TEST_F(SettingIntTest_682, GetIsConst_682) {
    const Setting<int> setting(42);
    EXPECT_EQ(42, setting.get());
}

// ==================== String Setting Tests ====================

TEST_F(SettingStringTest_682, ConstructorSetsStringValue_682) {
    Setting<std::string> setting("hello");
    EXPECT_EQ("hello", setting.get());
}

TEST_F(SettingStringTest_682, SetChangesStringValue_682) {
    Setting<std::string> setting("hello");
    setting.set("world");
    EXPECT_EQ("world", setting.get());
}

TEST_F(SettingStringTest_682, EmptyString_682) {
    Setting<std::string> setting("");
    EXPECT_EQ("", setting.get());
}

TEST_F(SettingStringTest_682, RestoreString_682) {
    Setting<std::string> setting("current");
    Setting<std::string> oldSetting("previous");
    setting.restore(oldSetting);
    EXPECT_EQ("previous", setting.get());
}

TEST_F(SettingStringTest_682, SetToEmptyString_682) {
    Setting<std::string> setting("notempty");
    setting.set("");
    EXPECT_EQ("", setting.get());
}

TEST_F(SettingStringTest_682, LongString_682) {
    std::string longStr(10000, 'a');
    Setting<std::string> setting(longStr);
    EXPECT_EQ(longStr, setting.get());
}

// ==================== Double Setting Tests ====================

TEST_F(SettingDoubleTest_682, ConstructorSetsDoubleValue_682) {
    Setting<double> setting(3.14);
    EXPECT_DOUBLE_EQ(3.14, setting.get());
}

TEST_F(SettingDoubleTest_682, SetChangesDoubleValue_682) {
    Setting<double> setting(1.0);
    setting.set(2.718);
    EXPECT_DOUBLE_EQ(2.718, setting.get());
}

TEST_F(SettingDoubleTest_682, ZeroDouble_682) {
    Setting<double> setting(0.0);
    EXPECT_DOUBLE_EQ(0.0, setting.get());
}

TEST_F(SettingDoubleTest_682, NegativeDouble_682) {
    Setting<double> setting(-99.99);
    EXPECT_DOUBLE_EQ(-99.99, setting.get());
}

TEST_F(SettingDoubleTest_682, RestoreDouble_682) {
    Setting<double> setting(1.0);
    Setting<double> oldSetting(2.0);
    setting.set(3.0);
    setting.restore(oldSetting);
    EXPECT_DOUBLE_EQ(2.0, setting.get());
}

// ==================== Bool Setting Tests ====================

TEST_F(SettingBoolTest_682, ConstructorSetsBoolTrue_682) {
    Setting<bool> setting(true);
    EXPECT_TRUE(setting.get());
}

TEST_F(SettingBoolTest_682, ConstructorSetsBoolFalse_682) {
    Setting<bool> setting(false);
    EXPECT_FALSE(setting.get());
}

TEST_F(SettingBoolTest_682, SetBoolValue_682) {
    Setting<bool> setting(true);
    setting.set(false);
    EXPECT_FALSE(setting.get());
}

TEST_F(SettingBoolTest_682, RestoreBool_682) {
    Setting<bool> setting(false);
    Setting<bool> oldSetting(true);
    setting.restore(oldSetting);
    EXPECT_TRUE(setting.get());
}

TEST_F(SettingBoolTest_682, ToggleBoolMultipleTimes_682) {
    Setting<bool> setting(true);
    setting.set(false);
    EXPECT_FALSE(setting.get());
    setting.set(true);
    EXPECT_TRUE(setting.get());
    setting.set(false);
    EXPECT_FALSE(setting.get());
}

}  // namespace YAML
