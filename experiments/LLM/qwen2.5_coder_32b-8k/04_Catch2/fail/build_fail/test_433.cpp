#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_fatal_condition_handler.hpp"



using namespace Catch;



// Mock class for engage_platform and disengage_platform if needed

class MockFatalConditionHandler : public FatalConditionHandler {

public:

    MOCK_METHOD(void, engage_platform, (), (override));

    MOCK_METHOD(void, disengage_platform, (), (override, noexcept));

};



TEST_F(MockFatalConditionHandlerTest_433, EngageSetsStartedToTrue_433) {

    MockFatalConditionHandler handler;

    EXPECT_CALL(handler, engage_platform()).Times(1);

    

    handler.engage();

    

    // Since m_started is private, we can't directly assert its value.

    // Instead, we rely on the fact that engage should call engage_platform once.

}



TEST_F(MockFatalConditionHandlerTest_433, EngageThrowsOnSecondCall_433) {

    MockFatalConditionHandler handler;

    EXPECT_CALL(handler, engage_platform()).Times(1);

    

    handler.engage();

    

    // Second call to engage should assert and throw

    ASSERT_DEATH({ handler.engage(); }, "Handler cannot be installed twice.");

}



TEST_F(MockFatalConditionHandlerTest_433, DisengageCallsDisengagePlatform_433) {

    MockFatalConditionHandler handler;

    EXPECT_CALL(handler, engage_platform()).Times(1);

    EXPECT_CALL(handler, disengage_platform()).Times(1);



    handler.engage();

    handler.disengage();

}



TEST_F(MockFatalConditionHandlerTest_433, DisengageNoThrowOnMultipleCalls_433) {

    MockFatalConditionHandler handler;

    EXPECT_CALL(handler, engage_platform()).Times(1);

    EXPECT_CALL(handler, disengage_platform()).Times(2);



    handler.engage();

    handler.disengage(); // First call

    handler.disengage(); // Second call should not throw

}
