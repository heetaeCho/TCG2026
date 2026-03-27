#include <gtest/gtest.h>

#include "catch2/internal/catch_output_redirect.hpp"



using namespace Catch;



// Mock class for OutputRedirect to verify interactions

class MockOutputRedirect : public OutputRedirect {

public:

    MOCK_METHOD(bool, isActive, (), (override));

};



TEST_F(RedirectGuardTest_1080, ConstructorActivateTrue_1080) {

    MockOutputRedirect mockOutput;

    EXPECT_CALL(mockOutput, isActive()).WillOnce(testing::Return(false));



    RedirectGuard guard(true, mockOutput);

}



TEST_F(RedirectGuardTest_1080, ConstructorActivateFalse_1080) {

    MockOutputRedirect mockOutput;

    EXPECT_CALL(mockOutput, isActive()).WillOnce(testing::Return(false));



    RedirectGuard guard(false, mockOutput);

}



TEST_F(RedirectGuardTest_1080, MoveConstructor_1080) {

    MockOutputRedirect mockOutput;

    RedirectGuard original(true, mockOutput);



    RedirectGuard moved(std::move(original));

}



TEST_F(RedirectGuardTest_1080, DeletedCopyConstructor_1080) {

    MockOutputRedirect mockOutput;

    RedirectGuard guard(true, mockOutput);



    // This should not compile if the copy constructor is deleted

    // RedirectGuard copied(guard);

}



TEST_F(RedirectGuardTest_1080, MoveAssignmentOperator_1080) {

    MockOutputRedirect mockOutput;

    RedirectGuard original(true, mockOutput);

    RedirectGuard target(false, mockOutput);



    target = std::move(original);

}



TEST_F(RedirectGuardTest_1080, DeletedCopyAssignmentOperator_1080) {

    MockOutputRedirect mockOutput;

    RedirectGuard guard(true, mockOutput);

    RedirectGuard target(false, mockOutput);



    // This should not compile if the copy assignment operator is deleted

    // target = guard;

}



TEST_F(RedirectGuardTest_1080, Destructor_1080) {

    MockOutputRedirect mockOutput;

    RedirectGuard* guard = new RedirectGuard(true, mockOutput);



    delete guard;

}
