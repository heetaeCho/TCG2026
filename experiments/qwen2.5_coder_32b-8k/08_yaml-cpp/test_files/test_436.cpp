#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "./TestProjects/yaml-cpp/src/setting.h"



using namespace YAML;



namespace {



class MockSettingChangeBase : public SettingChangeBase {

public:

    MOCK_METHOD(void, apply, (), (override));

};



template <typename T>

class SettingTest : public ::testing::Test {

protected:

    Setting<T> setting;

    Setting<T> oldSetting;

    std::unique_ptr<MockSettingChangeBase> mockSettingChange;



    void SetUp() override {

        mockSettingChange = std::make_unique<MockSettingChangeBase>();

    }

};



using TestTypes = ::testing::Types<int, double, std::string>;

TYPED_TEST_SUITE(SettingTest, TestTypes);



TYPED_TEST(SettingTest_436, SetAndGet_NormalOperation_436) {

    TypeParam newValue = TypeParam();

    this->setting.set(newValue);

    EXPECT_EQ(this->setting.get(), newValue);

}



TYPED_TEST(SettingTest_436, Restore_OldValueRestored_436) {

    TypeParam originalValue = TypeParam();

    TypeParam oldValue = TypeParam();



    this->setting.set(originalValue);

    this->oldSetting.set(oldValue);



    this->setting.restore(this->oldSetting);

    EXPECT_EQ(this->setting.get(), oldValue);

}



TYPED_TEST(SettingTest_436, Set_ReturnsUniquePtrToSettingChangeBase_436) {

    TypeParam newValue = TypeParam();

    auto result = this->setting.set(newValue);

    EXPECT_NE(result, nullptr);

}



TYPED_TEST(SettingTest_436, Get_DefaultConstructedValue_ReturnsDefaultValue_436) {

    TypeParam expectedDefault;

    EXPECT_EQ(this->setting.get(), expectedDefault);

}



}  // namespace
