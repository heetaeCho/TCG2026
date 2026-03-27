#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "setting.h"

#include <memory>



using namespace YAML;

using ::testing::NiceMock;



class MockSettingChangeBase : public SettingChangeBase {

public:

    MOCK_METHOD(void, apply, (), (override));

};



class SettingChangesTest_443 : public ::testing::Test {

protected:

    SettingChanges settingChanges;

    std::unique_ptr<MockSettingChangeBase> mockSettingChange1 = std::make_unique<NiceMock<MockSettingChangeBase>>();

    std::unique_ptr<MockSettingChangeBase> mockSettingChange2 = std::make_unique<NiceMock<MockSettingChangeBase>>();

};



TEST_F(SettingChangesTest_443, PushIncreasesCount_443) {

    size_t initialSize = settingChanges.m_settingChanges.size();

    settingChanges.push(std::move(mockSettingChange1));

    EXPECT_EQ(settingChanges.m_settingChanges.size(), initialSize + 1);

}



TEST_F(SettingChangesTest_443, ClearRemovesAllEntries_443) {

    settingChanges.push(std::move(mockSettingChange1));

    settingChanges.push(std::move(mockSettingChange2));

    settingChanges.clear();

    EXPECT_EQ(settingChanges.m_settingChanges.size(), 0);

}



TEST_F(SettingChangesTest_443, RestoreCallsApplyOnAllEntries_443) {

    settingChanges.push(std::make_unique<NiceMock<MockSettingChangeBase>>());

    settingChanges.push(std::make_unique<NiceMock<MockSettingChangeBase>>());



    EXPECT_CALL(*mockSettingChange1, apply()).Times(1);

    EXPECT_CALL(*mockSettingChange2, apply()).Times(1);



    settingChanges.restore();

}
