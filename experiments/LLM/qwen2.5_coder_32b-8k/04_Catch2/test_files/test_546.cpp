#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock OutputRedirect class to verify interactions

class MockOutputRedirect {

public:

    MOCK_METHOD(bool, isActive, (), (const));

};



using namespace Catch;



// Test fixture for RedirectGuard tests

class RedirectGuardTest_546 : public ::testing::Test {

protected:

    NiceMock<MockOutputRedirect> mock_redirect;

    bool activate = true;



    void SetUp() override {

        // Setup any initial state if necessary

    }



    void TearDown() override {

        // Cleanup any resources if necessary

    }

};



// Test normal operation with activation

TEST_F(RedirectGuardTest_546, Constructor_ActivatesWhenTrue_546) {

    EXPECT_CALL(mock_redirect, isActive()).WillOnce(::testing::Return(false));

    RedirectGuard guard(activate, mock_redirect);

}



// Test normal operation without activation

TEST_F(RedirectGuardTest_546, Constructor_DoesNotActivateWhenFalse_546) {

    activate = false;

    EXPECT_CALL(mock_redirect, isActive()).WillOnce(::testing::Return(true));

    RedirectGuard guard(activate, mock_redirect);

}



// Test move constructor

TEST_F(RedirectGuardTest_546, MoveConstructor_TransfersState_546) {

    EXPECT_CALL(mock_redirect, isActive()).WillOnce(::testing::Return(false));

    RedirectGuard original(activate, mock_redirect);

    RedirectGuard moved(std::move(original));

}



// Test move assignment operator

TEST_F(RedirectGuardTest_546, MoveAssignment_TransfersState_546) {

    EXPECT_CALL(mock_redirect, isActive()).WillOnce(::testing::Return(false));

    RedirectGuard original(activate, mock_redirect);

    RedirectGuard guard;

    guard = std::move(original);

}



// Test destruction does not throw if no exception on move

TEST_F(RedirectGuardTest_546, Destructor_NoExceptionOnMove_546) {

    EXPECT_CALL(mock_redirect, isActive()).WillOnce(::testing::Return(false));

    RedirectGuard original(activate, mock_redirect);

    RedirectGuard moved(std::move(original));

}



// Test destruction throws if exception on move

TEST_F(RedirectGuardTest_546, Destructor_ExceptionOnMove_546) {

    EXPECT_CALL(mock_redirect, isActive()).WillOnce(::testing::Return(false));

    RedirectGuard original(activate, mock_redirect);

    ON_CALL(mock_redirect, isActive()).WillByDefault(::testing::Throw(std::runtime_error("Mock Exception")));

    EXPECT_THROW(RedirectGuard moved(std::move(original)), std::runtime_error);

}
