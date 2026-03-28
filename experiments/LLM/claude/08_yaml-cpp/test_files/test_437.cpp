#include <gtest/gtest.h>
#include "setting.h"

// We need to understand Setting<T> to test SettingChange<T>.
// Based on the interface, Setting<T> must have:
// - A copy constructor (used in m_oldSetting(*pSetting))
// - A restore() method
// Since we're testing SettingChange as a black box, we work with the actual Setting type.

namespace YAML {

// If Setting is not directly accessible, we create a minimal compatible one for testing.
// Based on the known interface, Setting<T> should support copy and restore.

// Test fixture
class SettingChangeTest_437 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that SettingChange can be constructed with a Setting pointer
TEST_F(SettingChangeTest_437, ConstructionSavesCurrentState_437) {
    Setting<bool> setting(false);
    // The setting starts as false
    EXPECT_FALSE(setting.get());
    
    // Create a SettingChange which should save the current state
    auto change = std::make_unique<SettingChange<bool>>(&setting);
    
    // Modify the setting
    setting.set(true);
    EXPECT_TRUE(setting.get());
    
    // Pop should restore to original value
    change->pop();
    EXPECT_FALSE(setting.get());
}

// Test that pop restores the old setting value for int type
TEST_F(SettingChangeTest_437, PopRestoresOldIntSetting_437) {
    Setting<int> setting(42);
    
    auto change = std::make_unique<SettingChange<int>>(&setting);
    
    setting.set(100);
    EXPECT_EQ(setting.get(), 100);
    
    change->pop();
    EXPECT_EQ(setting.get(), 42);
}

// Test that multiple pops restore to the same saved state
TEST_F(SettingChangeTest_437, MultiplePopRestoresSameState_437) {
    Setting<bool> setting(true);
    
    auto change = std::make_unique<SettingChange<bool>>(&setting);
    
    setting.set(false);
    change->pop();
    EXPECT_TRUE(setting.get());
    
    // Pop again should still restore to the same saved state
    setting.set(false);
    change->pop();
    EXPECT_TRUE(setting.get());
}

// Test nested SettingChanges - stack-like behavior
TEST_F(SettingChangeTest_437, NestedSettingChangesRestoreCorrectly_437) {
    Setting<int> setting(1);
    
    auto change1 = std::make_unique<SettingChange<int>>(&setting);
    setting.set(2);
    
    auto change2 = std::make_unique<SettingChange<int>>(&setting);
    setting.set(3);
    EXPECT_EQ(setting.get(), 3);
    
    // Pop change2 should restore to 2
    change2->pop();
    EXPECT_EQ(setting.get(), 2);
    
    // Pop change1 should restore to 1
    change1->pop();
    EXPECT_EQ(setting.get(), 1);
}

// Test that copy constructor is deleted
TEST_F(SettingChangeTest_437, CopyConstructorIsDeleted_437) {
    EXPECT_FALSE(std::is_copy_constructible<SettingChange<bool>>::value);
}

// Test that move constructor is deleted
TEST_F(SettingChangeTest_437, MoveConstructorIsDeleted_437) {
    EXPECT_FALSE(std::is_move_constructible<SettingChange<bool>>::value);
}

// Test that copy assignment is deleted
TEST_F(SettingChangeTest_437, CopyAssignmentIsDeleted_437) {
    EXPECT_FALSE(std::is_copy_assignable<SettingChange<bool>>::value);
}

// Test that move assignment is deleted
TEST_F(SettingChangeTest_437, MoveAssignmentIsDeleted_437) {
    EXPECT_FALSE(std::is_move_assignable<SettingChange<bool>>::value);
}

// Test that SettingChange inherits from SettingChangeBase (polymorphism)
TEST_F(SettingChangeTest_437, IsBaseOfSettingChangeBase_437) {
    EXPECT_TRUE((std::is_base_of<SettingChangeBase, SettingChange<int>>::value));
}

// Test pop with setting unchanged from original
TEST_F(SettingChangeTest_437, PopWithUnchangedSetting_437) {
    Setting<int> setting(5);
    
    auto change = std::make_unique<SettingChange<int>>(&setting);
    // Don't change the setting
    
    change->pop();
    EXPECT_EQ(setting.get(), 5);
}

}  // namespace YAML
