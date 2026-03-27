#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "setting.h"



using namespace YAML;

using ::testing::NiceMock;

using ::testing::_;



class MockSettingChangeBase : public SettingChangeBase {

public:

    MOCK_METHOD(void, pop, (), (override));

};



class SettingChangesTest_442 : public ::testing::Test {

protected:

    NiceMock<MockSettingChangeBase> mockSettingChange1;

    NiceMock<MockSettingChangeBase> mockSettingChange2;

    SettingChanges settingChanges;



    void SetUp() override {

        // Set up any common state before each test

    }

};



TEST_F(SettingChangesTest_442, RestoreNoSettings_442) {

    // Test that restore does nothing when no settings are pushed

    settingChanges.restore();

}



TEST_F(SettingChangesTest_442, RestoreOneSetting_442) {

    // Test that restore calls pop on a single pushed setting

    EXPECT_CALL(mockSettingChange1, pop()).Times(1);

    settingChanges.push(std::make_unique<MockSettingChangeBase>(mockSettingChange1));

    settingChanges.restore();

}



TEST_F(SettingChangesTest_442, RestoreMultipleSettings_442) {

    // Test that restore calls pop on multiple pushed settings in reverse order

    EXPECT_CALL(mockSettingChange2, pop()).Times(1);

    EXPECT_CALL(mockSettingChange1, pop()).Times(1);

    settingChanges.push(std::make_unique<MockSettingChangeBase>(mockSettingChange1));

    settingChanges.push(std::make_unique<MockSettingChangeBase>(mockSettingChange2));

    settingChanges.restore();

}



TEST_F(SettingChangesTest_442, ClearNoSettings_442) {

    // Test that clear does nothing when no settings are pushed

    settingChanges.clear();

}



TEST_F(SettingChangesTest_442, ClearOneSetting_442) {

    // Test that clear removes a single pushed setting without calling pop

    EXPECT_CALL(mockSettingChange1, pop()).Times(0);

    settingChanges.push(std::make_unique<MockSettingChangeBase>(mockSettingChange1));

    settingChanges.clear();

}



TEST_F(SettingChangesTest_442, ClearMultipleSettings_442) {

    // Test that clear removes multiple pushed settings without calling pop

    EXPECT_CALL(mockSettingChange1, pop()).Times(0);

    EXPECT_CALL(mockSettingChange2, pop()).Times(0);

    settingChanges.push(std::make_unique<MockSettingChangeBase>(mockSettingChange1));

    settingChanges.push(std::make_unique<MockSettingChangeBase>(mockSettingChange2));

    settingChanges.clear();

}



TEST_F(SettingChangesTest_442, MoveConstructorNoSettings_442) {

    // Test that move constructor works with no settings

    SettingChanges newSettingChanges = std::move(settingChanges);

    newSettingChanges.restore();  // Should do nothing

}



TEST_F(SettingChangesTest_442, MoveConstructorWithSettings_442) {

    // Test that move constructor transfers ownership of settings and restore works correctly

    settingChanges.push(std::make_unique<MockSettingChangeBase>(mockSettingChange1));

    EXPECT_CALL(mockSettingChange1, pop()).Times(1);

    SettingChanges newSettingChanges = std::move(settingChanges);

    newSettingChanges.restore();

}



TEST_F(SettingChangesTest_442, MoveAssignmentNoSettings_442) {

    // Test that move assignment works with no settings

    SettingChanges other;

    other = std::move(settingChanges);

    other.restore();  // Should do nothing

}



TEST_F(SettingChangesTest_442, MoveAssignmentWithSettings_442) {

    // Test that move assignment transfers ownership of settings and restore works correctly

    settingChanges.push(std::make_unique<MockSettingChangeBase>(mockSettingChange1));

    SettingChanges other;

    EXPECT_CALL(mockSettingChange1, pop()).Times(1);

    other = std::move(settingChanges);

    other.restore();

}
