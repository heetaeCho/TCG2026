#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using namespace testing;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, assertionStarting, (const AssertionInfo &assertionInfo), (override));

};



class RunContextTest_495 : public Test {

protected:

    NiceMock<MockIEventListener> mockReporter;

    std::unique_ptr<IEventListenerPtr> reporter = std::make_unique<IEventListenerPtr>(&mockReporter);

    const IConfig* config = nullptr; // Assuming a valid config object is provided by the actual context

    RunContext runContext{config, CATCH_MOVE(*reporter)};

};



TEST_F(RunContextTest_495, NotifyAssertionStarted_CallsAssertionStartingOnReporter_495) {

    AssertionInfo info;

    EXPECT_CALL(mockReporter, assertionStarting(info)).Times(1);

    runContext.notifyAssertionStarted(info);

}



TEST_F(RunContextTest_495, NotifyAssertionStarted_NoCrashWithNullMacroName_495) {

    AssertionInfo info;

    info.macroName = StringRef();

    EXPECT_CALL(mockReporter, assertionStarting(info)).Times(1);

    runContext.notifyAssertionStarted(info);

}



TEST_F(RunContextTest_495, NotifyAssertionStarted_NoCrashWithEmptyCapturedExpression_495) {

    AssertionInfo info;

    info.capturedExpression = StringRef();

    EXPECT_CALL(mockReporter, assertionStarting(info)).Times(1);

    runContext.notifyAssertionStarted(info);

}
