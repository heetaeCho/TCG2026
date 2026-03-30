#include <gtest/gtest.h>

#include "catch2/internal/catch_fatal_condition_handler.hpp"



using namespace Catch;



class FatalConditionHandlerTest : public ::testing::Test {

protected:

    FatalConditionHandler handler;

};



TEST_F(FatalConditionHandlerTest_435, EngageSetsStartedFlag_435) {

    handler.engage();

}



TEST_F(FatalConditionHandlerTest_435, DisengageResetsStartedFlag_435) {

    handler.engage();

    handler.disengage();

}



TEST_F(FatalConditionHandlerTest_435, DestructorCallsDisengage_435) {

    FatalConditionHandler* handlerPtr = new FatalConditionHandler();

    handlerPtr->engage();

    delete handlerPtr;  // Destructor should call disengage

}



TEST_F(FatalConditionHandlerTest_435, GuardConstructorEngagesHandler_435) {

    FatalConditionHandlerGuard guard(&handler);

    handler.disengage();  // To ensure no exception on destruction of guard

}



TEST_F(FatalConditionHandlerTest_435, GuardDestructorDisengagesHandler_435) {

    handler.engage();

    {

        FatalConditionHandlerGuard guard(&handler);

    }  // Destructor should call disengage

}
