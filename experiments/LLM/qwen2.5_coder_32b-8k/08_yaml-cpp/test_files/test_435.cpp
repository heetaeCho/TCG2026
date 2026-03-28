#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "setting.h"

#include <memory>



using namespace YAML;



// Mock class for SettingChangeBase to verify interactions

class MockSettingChangeBase : public SettingChangeBase {

public:

    MOCK_METHOD(void, apply, (), (override));

};



// Test fixture for Setting tests

template <typename T>

class SettingTest : public ::testing::Test {

protected:

    Setting<T> setting;

    std::unique_ptr<MockSettingChangeBase> mockSettingChange;



    SettingTest() : setting(T()), mockSettingChange(std::make_unique<MockSettingChangeBase>()) {}

};



using TestTypes = ::testing::Types<int, double, std::string>;

TYPED_TEST_SUITE(SettingTest, TestTypes);



// Normal operation tests

TYPED_TEST(SettingTest, GetInitialValue_435) {

    EXPECT_EQ(this->setting.get(), TypeParam());

}



TYPED_TEST(SettingTest, SetNewValueAndGet_435) {

    const TypeParam newValue = this->getRandomValue();

    auto change = this->setting.set(newValue);

    EXPECT_EQ(this->setting.get(), newValue);

}



// Boundary conditions tests

TYPED_TEST(SettingTest, RestorePreviousValue_435) {

    const TypeParam originalValue = this->setting.get();

    const TypeParam newValue = this->getRandomValue();

    Setting<TypeParam> oldSetting(newValue);

    this->setting.set(newValue);

    this->setting.restore(oldSetting);

    EXPECT_EQ(this->setting.get(), originalValue);

}



// Exceptional or error cases tests

TYPED_TEST(SettingTest, SetSameValueNoChange_435) {

    const TypeParam initialValue = this->setting.get();

    auto change = this->setting.set(initialValue);

    EXPECT_EQ(change, nullptr);

    EXPECT_EQ(this->setting.get(), initialValue);

}



// Verification of external interactions

TYPED_TEST(SettingTest, SetInvokesApplyOnChange_435) {

    const TypeParam newValue = this->getRandomValue();

    EXPECT_CALL(*this->mockSettingChange, apply()).Times(1);

    auto change = this->setting.set(newValue);

    if (change) {

        change->apply();

    }

}



// Helper method to generate random values for testing

template <typename T>

T SettingTest<T>::getRandomValue() {

    if constexpr (std::is_same_v<T, int>) {

        return 42;

    } else if constexpr (std::is_same_v<T, double>) {

        return 3.14;

    } else if constexpr (std::is_same_v<T, std::string>) {

        return "test";

    }

    return T();

}
