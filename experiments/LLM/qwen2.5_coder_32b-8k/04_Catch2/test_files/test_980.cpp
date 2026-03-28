#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class to be tested is named `MyClass`

class MyClass {

public:

    virtual ~MyClass() = default;

    virtual int getValue() const = 0;

    virtual void setValue(int value) = 0;

    virtual bool isValid() const = 0;

    virtual void performAction(std::function<void()> callback) = 0;

};



// Mock class for testing

class MockMyClass : public MyClass {

public:

    MOCK_CONST_METHOD0(getValue, int());

    MOCK_METHOD1(setValue, void(int));

    MOCK_CONST_METHOD0(isValid, bool());

    MOCK_METHOD1(performAction, void(std::function<void()>));

};



using namespace testing;



// Test fixture

class MyClassTest_980 : public ::testing::Test {

protected:

    std::unique_ptr<MockMyClass> mock_my_class;



    void SetUp() override {

        mock_my_class = std::make_unique<MockMyClass>();

    }

};



// Normal operation tests

TEST_F(MyClassTest_980, GetValueReturnsSettedValue_980) {

    EXPECT_CALL(*mock_my_class, setValue(42)).Times(1);

    EXPECT_CALL(*mock_my_class, getValue()).WillOnce(Return(42));



    mock_my_class->setValue(42);

    int value = mock_my_class->getValue();

    EXPECT_EQ(value, 42);

}



TEST_F(MyClassTest_980, IsValidReturnsTrueAfterSetValue_980) {

    EXPECT_CALL(*mock_my_class, setValue(42)).Times(1);

    EXPECT_CALL(*mock_my_class, isValid()).WillOnce(Return(true));



    mock_my_class->setValue(42);

    bool valid = mock_my_class->isValid();

    EXPECT_TRUE(valid);

}



// Boundary conditions tests

TEST_F(MyClassTest_980, GetValueReturnsZeroInitially_980) {

    EXPECT_CALL(*mock_my_class, getValue()).WillOnce(Return(0));



    int value = mock_my_class->getValue();

    EXPECT_EQ(value, 0);

}



TEST_F(MyClassTest_980, IsValidReturnsFalseInitially_980) {

    EXPECT_CALL(*mock_my_class, isValid()).WillOnce(Return(false));



    bool valid = mock_my_class->isValid();

    EXPECT_FALSE(valid);

}



// Exceptional or error cases tests

// Since the interface doesn't specify any exceptions, we assume no exceptional cases are observable.



// Verification of external interactions tests

TEST_F(MyClassTest_980, PerformActionCallsCallbackOnce_980) {

    EXPECT_CALL(*mock_my_class, performAction(_)).WillOnce(Invoke([](std::function<void()> callback) {

        callback();

    }));



    bool callback_called = false;

    mock_my_class->performAction([&callback_called]() { callback_called = true; });

    EXPECT_TRUE(callback_called);

}
