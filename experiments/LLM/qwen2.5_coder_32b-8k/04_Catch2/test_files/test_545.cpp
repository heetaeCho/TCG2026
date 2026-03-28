#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_output_redirect.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class MockOutputRedirect : public OutputRedirect {

public:

    MOCK_METHOD(void, activateImpl, (), (override));

    MOCK_METHOD(void, deactivateImpl, (), (override));

    MOCK_METHOD(std::string, getStdout, (), (const, override));

    MOCK_METHOD(std::string, getStderr, (), (const, override));

    MOCK_METHOD(void, clearBuffers, (), (override));

    MOCK_METHOD(bool, isActive, (), (const, override));

};



class RedirectGuardTest : public ::testing::Test {

protected:

    MockOutputRedirect mockRedirect;

};



TEST_F(RedirectGuardTest_545, ConstructionWithActivation_545) {

    EXPECT_CALL(mockRedirect, isActive()).WillOnce(Return(false));

    EXPECT_CALL(mockRedirect, activateImpl());



    RedirectGuard guard(true, mockRedirect);

}



TEST_F(RedirectGuardTest_545, ConstructionWithoutActivation_545) {

    EXPECT_CALL(mockRedirect, isActive()).WillOnce(Return(true));

    EXPECT_CALL(mockRedirect, deactivateImpl());



    RedirectGuard guard(false, mockRedirect);

}



TEST_F(RedirectGuardTest_545, MoveConstructorDoesNotActivateOrDeactivate_545) {

    EXPECT_CALL(mockRedirect, activateImpl()).Times(0);

    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(0);



    RedirectGuard original(true, mockRedirect);

    RedirectGuard moved(std::move(original));

}



TEST_F(RedirectGuardTest_545, MoveAssignmentDoesNotActivateOrDeactivate_545) {

    EXPECT_CALL(mockRedirect, activateImpl()).Times(0);

    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(0);



    RedirectGuard original(true, mockRedirect);

    RedirectGuard target(false, mockRedirect);

    target = std::move(original);

}



TEST_F(RedirectGuardTest_545, DestructorReactivatesIfWasActiveBeforeConstruction_545) {

    EXPECT_CALL(mockRedirect, isActive()).WillOnce(Return(false));

    EXPECT_CALL(mockRedirect, activateImpl());



    RedirectGuard guard(true, mockRedirect);

    guard.~RedirectGuard();

}



TEST_F(RedirectGuardTest_545, DestructorDeactivatesIfWasNotActiveBeforeConstruction_545) {

    EXPECT_CALL(mockRedirect, isActive()).WillOnce(Return(true));

    EXPECT_CALL(mockRedirect, deactivateImpl());



    RedirectGuard guard(false, mockRedirect);

    guard.~RedirectGuard();

}



TEST_F(RedirectGuardTest_545, NoOpIfAlreadyInDesiredState_545) {

    EXPECT_CALL(mockRedirect, isActive()).WillOnce(Return(true));



    RedirectGuard guard(true, mockRedirect); // Already active, should not activate again

}



TEST_F(RedirectGuardTest_545, NoOpIfAlreadyInDesiredState2_545) {

    EXPECT_CALL(mockRedirect, isActive()).WillOnce(Return(false));



    RedirectGuard guard(false, mockRedirect); // Already deactivated, should not deactivate again

}
