#include <gtest/gtest.h>
#include <memory>

// Include the actual header
#include "setting.h"

namespace YAML {

// We need to know about SettingChangeBase for the set() return type
// It should be defined somewhere in the yaml-cpp codebase

class SettingTest_436 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction and get for int
TEST_F(SettingTest_436, DefaultConstructionInt_436) {
    Setting<int> setting;
    int val = setting.get();
    // Default constructed int should be 0 (value-initialized)
    EXPECT_EQ(val, 0);
}

// Test default construction and get for bool
TEST_F(SettingTest_436, DefaultConstructionBool_436) {
    Setting<bool> setting;
    bool val = setting.get();
    EXPECT_EQ(val, false);
}

// Test parameterized construction for int
TEST_F(SettingTest_436, ParameterizedConstructionInt_436) {
    Setting<int> setting(42);
    EXPECT_EQ(setting.get(), 42);
}

// Test parameterized construction for bool
TEST_F(SettingTest_436, ParameterizedConstructionBool_436) {
    Setting<bool> setting(true);
    EXPECT_EQ(setting.get(), true);
}

// Test parameterized construction for string
TEST_F(SettingTest_436, ParameterizedConstructionString_436) {
    Setting<std::string> setting("hello");
    EXPECT_EQ(setting.get(), "hello");
}

// Test set changes the value
TEST_F(SettingTest_436, SetChangesValue_436) {
    Setting<int> setting(10);
    EXPECT_EQ(setting.get(), 10);
    auto change = setting.set(20);
    EXPECT_EQ(setting.get(), 20);
}

// Test set returns non-null unique_ptr
TEST_F(SettingTest_436, SetReturnsNonNull_436) {
    Setting<int> setting(10);
    auto change = setting.set(20);
    EXPECT_NE(change, nullptr);
}

// Test set with same value
TEST_F(SettingTest_436, SetSameValue_436) {
    Setting<int> setting(10);
    auto change = setting.set(10);
    EXPECT_EQ(setting.get(), 10);
}

// Test restore from another setting
TEST_F(SettingTest_436, RestoreFromOtherSetting_436) {
    Setting<int> setting1(100);
    Setting<int> setting2(200);
    
    setting1.restore(setting2);
    EXPECT_EQ(setting1.get(), 200);
}

// Test restore preserves the source setting
TEST_F(SettingTest_436, RestorePreservesSource_436) {
    Setting<int> setting1(100);
    Setting<int> setting2(200);
    
    setting1.restore(setting2);
    EXPECT_EQ(setting2.get(), 200);
}

// Test restore with default-constructed setting
TEST_F(SettingTest_436, RestoreFromDefaultSetting_436) {
    Setting<int> setting1(42);
    Setting<int> defaultSetting;
    
    setting1.restore(defaultSetting);
    EXPECT_EQ(setting1.get(), 0);
}

// Test multiple sets
TEST_F(SettingTest_436, MultipleSetCalls_436) {
    Setting<int> setting(0);
    auto c1 = setting.set(1);
    EXPECT_EQ(setting.get(), 1);
    auto c2 = setting.set(2);
    EXPECT_EQ(setting.get(), 2);
    auto c3 = setting.set(3);
    EXPECT_EQ(setting.get(), 3);
}

// Test set with negative values
TEST_F(SettingTest_436, SetNegativeValue_436) {
    Setting<int> setting(0);
    auto change = setting.set(-100);
    EXPECT_EQ(setting.get(), -100);
}

// Test set with boundary int values
TEST_F(SettingTest_436, SetMaxIntValue_436) {
    Setting<int> setting(0);
    auto change = setting.set(std::numeric_limits<int>::max());
    EXPECT_EQ(setting.get(), std::numeric_limits<int>::max());
}

TEST_F(SettingTest_436, SetMinIntValue_436) {
    Setting<int> setting(0);
    auto change = setting.set(std::numeric_limits<int>::min());
    EXPECT_EQ(setting.get(), std::numeric_limits<int>::min());
}

// Test with double type
TEST_F(SettingTest_436, DoubleTypeSetting_436) {
    Setting<double> setting(3.14);
    EXPECT_DOUBLE_EQ(setting.get(), 3.14);
    auto change = setting.set(2.718);
    EXPECT_DOUBLE_EQ(setting.get(), 2.718);
}

// Test restore after set
TEST_F(SettingTest_436, RestoreAfterSet_436) {
    Setting<int> original(10);
    Setting<int> modified(10);
    
    auto change = modified.set(99);
    EXPECT_EQ(modified.get(), 99);
    
    modified.restore(original);
    EXPECT_EQ(modified.get(), 10);
}

// Test string setting set
TEST_F(SettingTest_436, StringSettingSet_436) {
    Setting<std::string> setting("initial");
    auto change = setting.set("modified");
    EXPECT_EQ(setting.get(), "modified");
}

// Test string setting restore
TEST_F(SettingTest_436, StringSettingRestore_436) {
    Setting<std::string> setting1("first");
    Setting<std::string> setting2("second");
    
    setting1.restore(setting2);
    EXPECT_EQ(setting1.get(), "second");
}

// Test empty string
TEST_F(SettingTest_436, EmptyStringSetting_436) {
    Setting<std::string> setting("");
    EXPECT_EQ(setting.get(), "");
    auto change = setting.set("non-empty");
    EXPECT_EQ(setting.get(), "non-empty");
}

// Test restore self (setting restores from itself)
TEST_F(SettingTest_436, RestoreSelf_436) {
    Setting<int> setting(42);
    setting.restore(setting);
    EXPECT_EQ(setting.get(), 42);
}

}  // namespace YAML
