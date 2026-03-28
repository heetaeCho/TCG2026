#include <gtest/gtest.h>
#include <memory>
#include "setting.h"

namespace YAML {

// Test fixture for Setting with int type
class SettingTest_438 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction and get
TEST_F(SettingTest_438, DefaultConstructionInt_438) {
    Setting<int> setting;
    EXPECT_EQ(setting.get(), int());
}

// Test construction with value
TEST_F(SettingTest_438, ValueConstructionInt_438) {
    Setting<int> setting(42);
    EXPECT_EQ(setting.get(), 42);
}

// Test set changes value
TEST_F(SettingTest_438, SetChangesValue_438) {
    Setting<int> setting(10);
    auto change = setting.set(20);
    EXPECT_EQ(setting.get(), 20);
}

// Test set returns non-null unique_ptr
TEST_F(SettingTest_438, SetReturnsNonNullChange_438) {
    Setting<int> setting(10);
    auto change = setting.set(20);
    EXPECT_NE(change, nullptr);
}

// Test multiple sets
TEST_F(SettingTest_438, MultipleSetsCascade_438) {
    Setting<int> setting(0);
    auto change1 = setting.set(1);
    EXPECT_EQ(setting.get(), 1);
    auto change2 = setting.set(2);
    EXPECT_EQ(setting.get(), 2);
    auto change3 = setting.set(3);
    EXPECT_EQ(setting.get(), 3);
}

// Test set with same value
TEST_F(SettingTest_438, SetSameValue_438) {
    Setting<int> setting(42);
    auto change = setting.set(42);
    EXPECT_EQ(setting.get(), 42);
    EXPECT_NE(change, nullptr);
}

// Test with string type - default construction
TEST_F(SettingTest_438, DefaultConstructionString_438) {
    Setting<std::string> setting;
    EXPECT_EQ(setting.get(), std::string());
}

// Test with string type - value construction
TEST_F(SettingTest_438, ValueConstructionString_438) {
    Setting<std::string> setting("hello");
    EXPECT_EQ(setting.get(), "hello");
}

// Test with string type - set
TEST_F(SettingTest_438, SetStringValue_438) {
    Setting<std::string> setting("hello");
    auto change = setting.set(std::string("world"));
    EXPECT_EQ(setting.get(), "world");
    EXPECT_NE(change, nullptr);
}

// Test with bool type
TEST_F(SettingTest_438, BoolSetting_438) {
    Setting<bool> setting(false);
    EXPECT_EQ(setting.get(), false);
    auto change = setting.set(true);
    EXPECT_EQ(setting.get(), true);
    EXPECT_NE(change, nullptr);
}

// Test with double type
TEST_F(SettingTest_438, DoubleSetting_438) {
    Setting<double> setting(3.14);
    EXPECT_DOUBLE_EQ(setting.get(), 3.14);
    auto change = setting.set(2.71);
    EXPECT_DOUBLE_EQ(setting.get(), 2.71);
}

// Test restore functionality
TEST_F(SettingTest_438, RestoreFromOldSetting_438) {
    Setting<int> setting(100);
    Setting<int> oldSetting(50);
    setting.restore(oldSetting);
    EXPECT_EQ(setting.get(), oldSetting.get());
}

// Test restore after set
TEST_F(SettingTest_438, RestoreAfterSet_438) {
    Setting<int> original(10);
    Setting<int> setting(10);
    auto change = setting.set(99);
    EXPECT_EQ(setting.get(), 99);
    setting.restore(original);
    EXPECT_EQ(setting.get(), 10);
}

// Test boundary: set with zero
TEST_F(SettingTest_438, SetZeroValue_438) {
    Setting<int> setting(999);
    auto change = setting.set(0);
    EXPECT_EQ(setting.get(), 0);
}

// Test boundary: set with negative value
TEST_F(SettingTest_438, SetNegativeValue_438) {
    Setting<int> setting(0);
    auto change = setting.set(-1);
    EXPECT_EQ(setting.get(), -1);
}

// Test boundary: set with max int
TEST_F(SettingTest_438, SetMaxIntValue_438) {
    Setting<int> setting(0);
    auto change = setting.set(std::numeric_limits<int>::max());
    EXPECT_EQ(setting.get(), std::numeric_limits<int>::max());
}

// Test boundary: set with min int
TEST_F(SettingTest_438, SetMinIntValue_438) {
    Setting<int> setting(0);
    auto change = setting.set(std::numeric_limits<int>::min());
    EXPECT_EQ(setting.get(), std::numeric_limits<int>::min());
}

// Test empty string
TEST_F(SettingTest_438, SetEmptyString_438) {
    Setting<std::string> setting("non-empty");
    auto change = setting.set(std::string(""));
    EXPECT_EQ(setting.get(), "");
}

// Test restore with self
TEST_F(SettingTest_438, RestoreWithSelf_438) {
    Setting<int> setting(42);
    setting.restore(setting);
    EXPECT_EQ(setting.get(), 42);
}

// Test that each set returns a unique change object
TEST_F(SettingTest_438, EachSetReturnsUniqueChange_438) {
    Setting<int> setting(0);
    auto change1 = setting.set(1);
    auto change2 = setting.set(2);
    EXPECT_NE(change1, nullptr);
    EXPECT_NE(change2, nullptr);
    EXPECT_NE(change1.get(), change2.get());
}

}  // namespace YAML
