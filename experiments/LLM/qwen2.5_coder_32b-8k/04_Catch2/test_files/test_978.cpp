#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class to be tested is named MyClass and has the following interface:

class MyClass {

public:

    virtual ~MyClass() = default;

    virtual void setValue(int value) = 0;

    virtual int getValue() const = 0;

    virtual bool isValid() const = 0;

    virtual void performAction(std::function<void()> callback) = 0;

};



using ::testing::_;

using ::testing::Return;

using ::testing::Invoke;



class MockMyClass : public MyClass {

public:

    MOCK_METHOD(void, setValue, (int value), (override));

    MOCK_METHOD(int, getValue, (), (const, override));

    MOCK_METHOD(bool, isValid, (), (const, override));

    MOCK_METHOD(void, performAction, (std::function<void()>) , (override));

};



class MyClassTest_978 : public ::testing::Test {

protected:

    std::unique_ptr<MockMyClass> mock_my_class;



    void SetUp() override {

        mock_my_class = std::make_unique<MockMyClass>();

    }

};



// Test normal operation

TEST_F(MyClassTest_978, SetValueAndGetCorrectValue_978) {

    EXPECT_CALL(*mock_my_class, setValue(42)).Times(1);

    EXPECT_CALL(*mock_my_class, getValue()).WillOnce(Return(42));



    mock_my_class->setValue(42);

    int value = mock_my_class->getValue();

    EXPECT_EQ(value, 42);

}



// Test boundary conditions

TEST_F(MyClassTest_978, SetValueToBoundaryValueAndGetCorrectValue_978) {

    EXPECT_CALL(*mock_my_class, setValue(-1)).Times(1);

    EXPECT_CALL(*mock_my_class, getValue()).WillOnce(Return(-1));



    mock_my_class->setValue(-1);

    int value = mock_my_class->getValue();

    EXPECT_EQ(value, -1);

}



// Test exceptional or error cases

TEST_F(MyClassTest_978, IsValidReturnsFalseWhenInvalid_978) {

    EXPECT_CALL(*mock_my_class, isValid()).WillOnce(Return(false));



    bool is_valid = mock_my_class->isValid();

    EXPECT_FALSE(is_valid);

}



// Test verification of external interactions

TEST_F(MyClassTest_978, PerformActionCallsCallbackOnce_978) {

    EXPECT_CALL(*mock_my_class, performAction(_))

        .WillOnce(Invoke([](std::function<void()> callback) { 

            callback(); 

        }));



    bool callback_called = false;

    mock_my_class->performAction([&callback_called]() { callback_called = true; });

    EXPECT_TRUE(callback_called);

}
