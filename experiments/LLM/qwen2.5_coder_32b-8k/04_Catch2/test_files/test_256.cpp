#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"



using namespace Catch;

using ::testing::Return;



class MockIConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(someConfigMethod, int());

};



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD0(captureSomething, void());

};



class ContextTest_256 : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset the context for each test

        Context::cleanUpContext();

    }



    void TearDown() override {

        // Ensure no context is left hanging after a test

        Context::cleanUpContext();

    }

};



TEST_F(ContextTest_256, GetCurrentContextCreatesNewContext_256) {

    const Context& context = getCurrentContext();

    EXPECT_NE(&context, nullptr);

}



TEST_F(ContextTest_256, GetResultCaptureInitiallyNull_256) {

    const Context& context = getCurrentContext();

    EXPECT_EQ(context.getResultCapture(), nullptr);

}



TEST_F(ContextTest_256, SetAndGetConfig_256) {

    MockIConfig mockConfig;

    Context& mutableContext = getCurrentMutableContext();

    mutableContext.setConfig(&mockConfig);



    const Context& context = getCurrentContext();

    EXPECT_EQ(context.getConfig(), &mockConfig);

}



TEST_F(ContextTest_256, SetAndGetResultCapture_256) {

    MockIResultCapture mockResult;

    Context& mutableContext = getCurrentMutableContext();

    mutableContext.setResultCapture(&mockResult);



    const Context& context = getCurrentContext();

    EXPECT_EQ(context.getResultCapture(), &mockResult);

}



TEST_F(ContextTest_256, CleanUpContextSetsConfigToNull_256) {

    MockIConfig mockConfig;

    Context& mutableContext = getCurrentMutableContext();

    mutableContext.setConfig(&mockConfig);



    Context::cleanUpContext();

    const Context& context = getCurrentContext();

    EXPECT_EQ(context.getConfig(), nullptr);

}



TEST_F(ContextTest_256, CleanUpContextSetsResultCaptureToNull_256) {

    MockIResultCapture mockResult;

    Context& mutableContext = getCurrentMutableContext();

    mutableContext.setResultCapture(&mockResult);



    Context::cleanUpContext();

    const Context& context = getCurrentContext();

    EXPECT_EQ(context.getResultCapture(), nullptr);

}
