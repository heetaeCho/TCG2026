#include <gtest/gtest.h>
#include <memory>

// Include the actual header
#include "setting.h"

namespace YAML {

// Test fixture for Setting with int type
class SettingIntTest_435 : public ::testing::Test {
protected:
    Setting<int> setting;
};

// Test fixture for Setting with string type
class SettingStringTest_435 : public ::testing::Test {
protected:
    Setting<std::string> setting;
};

// Test fixture for Setting with double type
class SettingDoubleTest_435 : public ::testing::Test {
protected:
    Setting<double> setting;
};

// Test fixture for Setting with bool type
class SettingBoolTest_435 : public ::testing::Test {
protected:
    Setting<bool> setting;
};

// ==================== Default Construction Tests ====================

TEST_F(SettingIntTest_435, DefaultConstructionReturnsDefaultInt_435) {
    EXPECT_EQ(setting.get(), int());
}

TEST_F(SettingStringTest_435, DefaultConstructionReturnsDefaultString_435) {
    EXPECT_EQ(setting.get(), std::string());
}

TEST_F(SettingDoubleTest_435, DefaultConstructionReturnsDefaultDouble_435) {
    EXPECT_DOUBLE_EQ(setting.get(), double());
}

TEST_F(SettingBoolTest_435, DefaultConstructionReturnsDefaultBool_435) {
    EXPECT_EQ(setting.get(), bool());
}

// ==================== Value Construction Tests ====================

TEST(SettingValueConstruction_435, IntValueConstruction_435) {
    Setting<int> setting(42);
    EXPECT_EQ(setting.get(), 42);
}

TEST(SettingValueConstruction_435, StringValueConstruction_435) {
    Setting<std::string> setting("hello");
    EXPECT_EQ(setting.get(), "hello");
}

TEST(SettingValueConstruction_435, DoubleValueConstruction_435) {
    Setting<double> setting(3.14);
    EXPECT_DOUBLE_EQ(setting.get(), 3.14);
}

TEST(SettingValueConstruction_435, BoolValueConstruction_435) {
    Setting<bool> setting(true);
    EXPECT_EQ(setting.get(), true);
}

// ==================== Set Tests ====================

TEST_F(SettingIntTest_435, SetChangesValue_435) {
    auto change = setting.set(100);
    EXPECT_EQ(setting.get(), 100);
}

TEST_F(SettingIntTest_435, SetReturnsNonNull_435) {
    auto change = setting.set(100);
    EXPECT_NE(change, nullptr);
}

TEST_F(SettingStringTest_435, SetChangesStringValue_435) {
    auto change = setting.set("world");
    EXPECT_EQ(setting.get(), "world");
}

TEST_F(SettingDoubleTest_435, SetChangesDoubleValue_435) {
    auto change = setting.set(2.718);
    EXPECT_DOUBLE_EQ(setting.get(), 2.718);
}

TEST_F(SettingBoolTest_435, SetChangesBoolValue_435) {
    auto change = setting.set(true);
    EXPECT_EQ(setting.get(), true);
}

TEST_F(SettingIntTest_435, SetMultipleTimesUpdatesValue_435) {
    auto change1 = setting.set(10);
    EXPECT_EQ(setting.get(), 10);
    auto change2 = setting.set(20);
    EXPECT_EQ(setting.get(), 20);
    auto change3 = setting.set(30);
    EXPECT_EQ(setting.get(), 30);
}

TEST_F(SettingIntTest_435, SetToSameValueKeepsValue_435) {
    auto change1 = setting.set(42);
    EXPECT_EQ(setting.get(), 42);
    auto change2 = setting.set(42);
    EXPECT_EQ(setting.get(), 42);
}

// ==================== Restore Tests ====================

TEST_F(SettingIntTest_435, RestoreFromOldSetting_435) {
    Setting<int> oldSetting(99);
    setting.set(50);
    EXPECT_EQ(setting.get(), 50);
    setting.restore(oldSetting);
    EXPECT_EQ(setting.get(), 99);
}

TEST_F(SettingStringTest_435, RestoreFromOldStringSetting_435) {
    Setting<std::string> oldSetting("original");
    setting.set("modified");
    EXPECT_EQ(setting.get(), "modified");
    setting.restore(oldSetting);
    EXPECT_EQ(setting.get(), "original");
}

TEST_F(SettingIntTest_435, RestoreFromDefaultSetting_435) {
    setting.set(123);
    EXPECT_EQ(setting.get(), 123);
    Setting<int> defaultSetting;
    setting.restore(defaultSetting);
    EXPECT_EQ(setting.get(), int());
}

TEST_F(SettingIntTest_435, RestoreDoesNotAffectSource_435) {
    Setting<int> oldSetting(77);
    setting.set(50);
    setting.restore(oldSetting);
    EXPECT_EQ(oldSetting.get(), 77);
    EXPECT_EQ(setting.get(), 77);
}

// ==================== Boundary Condition Tests ====================

TEST(SettingBoundary_435, IntMaxValue_435) {
    Setting<int> setting;
    auto change = setting.set(std::numeric_limits<int>::max());
    EXPECT_EQ(setting.get(), std::numeric_limits<int>::max());
}

TEST(SettingBoundary_435, IntMinValue_435) {
    Setting<int> setting;
    auto change = setting.set(std::numeric_limits<int>::min());
    EXPECT_EQ(setting.get(), std::numeric_limits<int>::min());
}

TEST(SettingBoundary_435, IntZeroValue_435) {
    Setting<int> setting(42);
    auto change = setting.set(0);
    EXPECT_EQ(setting.get(), 0);
}

TEST(SettingBoundary_435, NegativeIntValue_435) {
    Setting<int> setting;
    auto change = setting.set(-1);
    EXPECT_EQ(setting.get(), -1);
}

TEST(SettingBoundary_435, EmptyString_435) {
    Setting<std::string> setting("nonempty");
    auto change = setting.set("");
    EXPECT_EQ(setting.get(), "");
}

TEST(SettingBoundary_435, LargeString_435) {
    std::string large(10000, 'x');
    Setting<std::string> setting;
    auto change = setting.set(large);
    EXPECT_EQ(setting.get(), large);
}

// ==================== Get Consistency Tests ====================

TEST_F(SettingIntTest_435, GetIsConsistentOnMultipleCalls_435) {
    setting.set(55);
    EXPECT_EQ(setting.get(), 55);
    EXPECT_EQ(setting.get(), 55);
    EXPECT_EQ(setting.get(), 55);
}

TEST(SettingGetConst_435, GetWorksOnConstSetting_435) {
    const Setting<int> setting(42);
    EXPECT_EQ(setting.get(), 42);
}

// ==================== Restore After Multiple Sets ====================

TEST_F(SettingIntTest_435, RestoreAfterMultipleSets_435) {
    Setting<int> original(5);
    setting.set(10);
    setting.set(20);
    setting.set(30);
    setting.restore(original);
    EXPECT_EQ(setting.get(), 5);
}

TEST_F(SettingIntTest_435, MultipleRestores_435) {
    Setting<int> first(1);
    Setting<int> second(2);
    setting.set(100);
    setting.restore(first);
    EXPECT_EQ(setting.get(), 1);
    setting.restore(second);
    EXPECT_EQ(setting.get(), 2);
}

}  // namespace YAML
