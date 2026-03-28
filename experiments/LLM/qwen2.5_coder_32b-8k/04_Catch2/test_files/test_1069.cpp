#include <gtest/gtest.h>

#include "catch2/internal/catch_fatal_condition_handler.hpp"



using namespace Catch;



class FatalConditionHandlerTest_1069 : public ::testing::Test {

protected:

    void SetUp() override {

        mockFatalConditionHandler = std::make_unique<MockFatalConditionHandler>();

    }



    void TearDown() override {

        mockFatalConditionHandler.reset();

    }



    class MockFatalConditionHandler : public FatalConditionHandler {

    public:

        MOCK_METHOD(void, engage, (), (override));

        MOCK_METHOD(void, disengage, (), (noexcept, override));

    };



    std::unique_ptr<MockFatalConditionHandler> mockFatalConditionHandler;

};



TEST_F(FatalConditionHandlerTest_1069, EngageIsCalledOnConstruction_1069) {

    EXPECT_CALL(*mockFatalConditionHandler, engage()).Times(1);

    FatalConditionHandlerGuard guard(mockFatalConditionHandler.get());

}



TEST_F(FatalConditionHandlerTest_1069, DisengageIsCalledOnDestruction_1069) {

    EXPECT_CALL(*mockFatalConditionHandler, disengage()).Times(1);

    {

        FatalConditionHandlerGuard guard(mockFatalConditionHandler.get());

    }

}



TEST_F(FatalConditionHandlerTest_1069, EngageAndDisengageAreCalledOncePerGuard_1069) {

    EXPECT_CALL(*mockFatalConditionHandler, engage()).Times(1);

    EXPECT_CALL(*mockFatalConditionHandler, disengage()).Times(1);

    FatalConditionHandlerGuard guard(mockFatalConditionHandler.get());

}



TEST_F(FatalConditionHandlerTest_1069, MultipleGuardsInvokeEngageAndDisengageMultipleTimes_1069) {

    EXPECT_CALL(*mockFatalConditionHandler, engage()).Times(2);

    EXPECT_CALL(*mockFatalConditionHandler, disengage()).Times(2);



    {

        FatalConditionHandlerGuard guard1(mockFatalConditionHandler.get());

        {

            FatalConditionHandlerGuard guard2(mockFatalConditionHandler.get());

        }

    }

}
