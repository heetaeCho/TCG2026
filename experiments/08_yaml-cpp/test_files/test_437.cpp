#include <gtest/gtest.h>

#include "setting.h"

#include <gmock/gmock.h>



// Mock class for Setting<T>

template <typename T>

class MockSetting : public YAML::Setting<T> {

public:

    MOCK_METHOD(void, restore, (const YAML::Setting<T>&), (override));

};



using ::testing::_;



namespace YAML {



TEST_F(WriteBatchTest_437, PopRestoresOriginalSetting_437) {

    // Arrange

    MockSetting<int> mockSetting;

    SettingChange<int> settingChange(&mockSetting);



    EXPECT_CALL(mockSetting, restore(_)).Times(1);



    // Act

    settingChange.pop();

}



TEST_F(WriteBatchTest_437, PopDoesNotThrowException_437) {

    // Arrange

    MockSetting<int> mockSetting;

    SettingChange<int> settingChange(&mockSetting);



    EXPECT_CALL(mockSetting, restore(_)).WillOnce([](const YAML::Setting<int>&){});



    // Act & Assert

    ASSERT_NO_THROW(settingChange.pop());

}



}  // namespace YAML
