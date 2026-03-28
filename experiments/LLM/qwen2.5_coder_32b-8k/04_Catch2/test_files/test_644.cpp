#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"



namespace Catch {

    class MockIConfig : public IConfig {

        MOCK_METHOD0(someMethod, int()); // Example method to mock if needed

    };



    class MockIResultCapture : public IResultCapture {

        MOCK_METHOD0(someMethod, void()); // Example method to mock if needed

    };

}



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class ContextTest_644 : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset context for each test

        getCurrentMutableContext().cleanUpContext();

    }



    void TearDown() override {

        // Clean up after tests

        getCurrentMutableContext().cleanUpContext();

    }

};



TEST_F(ContextTest_644, GetCurrentMutableContext_ReturnsSameInstance_644) {

    Context& context1 = getCurrentMutableContext();

    Context& context2 = getCurrentMutableContext();

    EXPECT_EQ(&context1, &context2);

}



TEST_F(ContextTest_644, SetAndGetConfig_WorkAsExpected_644) {

    MockIConfig mockConfig;

    getCurrentMutableContext().setConfig(&mockConfig);

    EXPECT_EQ(getCurrentMutableContext().getConfig(), &mockConfig);

}



TEST_F(ContextTest_644, SetAndGetResultCapture_WorkAsExpected_644) {

    MockIResultCapture mockResultCapture;

    getCurrentMutableContext().setResultCapture(&mockResultCapture);

    EXPECT_EQ(getCurrentMutableContext().getResultCapture(), &mockResultCapture);

}



TEST_F(ContextTest_644, CleanUpContext_ResetsConfigAndResultCapture_644) {

    MockIConfig mockConfig;

    MockIResultCapture mockResultCapture;



    getCurrentMutableContext().setConfig(&mockConfig);

    getCurrentMutableContext().setResultCapture(&mockResultCapture);



    getCurrentMutableContext().cleanUpContext();



    EXPECT_EQ(getCurrentMutableContext().getConfig(), nullptr);

    EXPECT_EQ(getCurrentMutableContext().getResultCapture(), nullptr);

}



TEST_F(ContextTest_644, GetCurrentContext_ReturnsConstInstance_644) {

    const Context& context = getCurrentMutableContext();

    EXPECT_NE(&context, nullptr);

}
