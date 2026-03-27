#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_output_redirect.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockOutputRedirect : public OutputRedirect {

public:

    MOCK_METHOD(void, activateImpl, (), (override));

    MOCK_METHOD(void, deactivateImpl, (), (override));

    MOCK_METHOD(std::string, getStdout, (), (const, override));

    MOCK_METHOD(std::string, getStderr, (), (const, override));

    MOCK_METHOD(void, clearBuffers, (), (override));

    MOCK_METHOD(bool, isActive, (), (const, override));

};



class RedirectGuardTest_1079 : public ::testing::Test {

protected:

    MockOutputRedirect mock_output_redirect;

    bool activate = true;



    void SetUp() override {

        // Reset the mock before each test

        testing::Mock::VerifyAndClearExpectations(&mock_output_redirect);

        testing::Mock::ResetCalls(&mock_output_redirect);

    }

};



TEST_F(RedirectGuardTest_1079, ActivateWhenInactive_1079) {

    EXPECT_CALL(mock_output_redirect, isActive()).WillOnce(Return(false));

    EXPECT_CALL(mock_output_redirect, activateImpl());



    RedirectGuard guard(true, mock_output_redirect);

}



TEST_F(RedirectGuardTest_1079, DeactivateWhenActive_1079) {

    EXPECT_CALL(mock_output_redirect, isActive()).WillOnce(Return(true));

    EXPECT_CALL(mock_output_redirect, deactivateImpl());



    RedirectGuard guard(false, mock_output_redirect);

}



TEST_F(RedirectGuardTest_1079, NoChangeWhenAlreadyActive_1079) {

    EXPECT_CALL(mock_output_redirect, isActive()).WillOnce(Return(true));



    RedirectGuard guard(true, mock_output_redirect);

}



TEST_F(RedirectGuardTest_1079, NoChangeWhenAlreadyInactive_1079) {

    EXPECT_CALL(mock_output_redirect, isActive()).WillOnce(Return(false));



    RedirectGuard guard(false, mock_output_redirect);

}



TEST_F(RedirectGuardTest_1079, MoveConstructorPreservesState_1079) {

    EXPECT_CALL(mock_output_redirect, isActive()).WillOnce(Return(true));

    RedirectGuard original_guard(false, mock_output_redirect);



    RedirectGuard moved_guard(std::move(original_guard));



    // Ensure the moved guard has the correct state

    EXPECT_EQ(moved_guard.m_activate, false);

}



TEST_F(RedirectGuardTest_1079, MoveAssignmentPreservesState_1079) {

    EXPECT_CALL(mock_output_redirect, isActive()).WillOnce(Return(true));

    RedirectGuard original_guard(false, mock_output_redirect);



    RedirectGuard guard(true, mock_output_redirect);

    guard = std::move(original_guard);



    // Ensure the moved guard has the correct state

    EXPECT_EQ(guard.m_activate, false);

}
