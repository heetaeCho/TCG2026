#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "setting.h"



using namespace YAML;



// Mock class for SettingChangeBase to verify interactions

class MockSettingChangeBase : public SettingChangeBase {

public:

    MOCK_METHOD(void, apply, (), (override));

};



template<typename T>

class SettingTest : public ::testing::Test {

protected:

    Setting<T> setting;

    T initialValue = T();

    T newValue = T();



    SettingTest() : setting(initialValue) {}

};



using TestingTypes = ::testing::Types<int, std::string, double>;

TYPED_TEST_SUITE(SettingTest, TestingTypes);



// Test normal operation of set and get

TYPED_TEST(SettingTest, SetAndGet_NormalOperation_682) {

    this->setting.set(this->newValue);

    EXPECT_EQ(this->setting.get(), this->newValue);

}



// Test boundary condition with default value

TYPED_TEST(SettingTest, Get_DefaultValue_682) {

    EXPECT_EQ(this->setting.get(), this->initialValue);

}



// Test restore functionality

TYPED_TEST(SettingTest, Restore_RevertsToPreviousValue_682) {

    Setting<TypeParam> oldSetting = this->setting;

    this->setting.set(this->newValue);

    this->setting.restore(oldSetting);

    EXPECT_EQ(this->setting.get(), this->initialValue);

}



// Test set with same value does not change state

TYPED_TEST(SettingTest, Set_SameValue_NoChange_682) {

    this->setting.set(this->initialValue);

    EXPECT_EQ(this->setting.get(), this->initialValue);

}
