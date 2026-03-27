#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "setting.h"



using namespace YAML;



class SettingTest_438 : public ::testing::Test {

protected:

    Setting<int> intSetting;

    Setting<std::string> stringSetting;

};



TEST_F(SettingTest_438, SetAndGet_NormalOperation_438) {

    intSetting.set(42);

    EXPECT_EQ(intSetting.get(), 42);



    stringSetting.set("test");

    EXPECT_EQ(stringSetting.get(), "test");

}



TEST_F(SettingTest_438, Restore_RevertsToPreviousValue_438) {

    int initial = intSetting.get();

    intSetting.set(100);

    intSetting.restore(intSetting);

    EXPECT_EQ(intSetting.get(), initial);



    std::string initialStr = stringSetting.get();

    stringSetting.set("new value");

    stringSetting.restore(stringSetting);

    EXPECT_EQ(stringSetting.get(), initialStr);

}



TEST_F(SettingTest_438, Set_ReturnsUniquePtrToChange_438) {

    auto change = intSetting.set(50);

    EXPECT_NE(change, nullptr);



    auto strChange = stringSetting.set("another test");

    EXPECT_NE(strChange, nullptr);

}



TEST_F(SettingTest_438, BoundaryConditions_EmptyString_438) {

    stringSetting.set("");

    EXPECT_EQ(stringSetting.get(), "");

}



TEST_F(SettingTest_438, BoundaryConditions_ZeroValue_438) {

    intSetting.set(0);

    EXPECT_EQ(intSetting.get(), 0);

}
