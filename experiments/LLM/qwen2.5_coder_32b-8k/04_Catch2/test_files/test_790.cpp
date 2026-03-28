#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace ::testing;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef arg), (override));

};



class MultiReporterTest : public Test {

protected:

    NiceMock<MockIEventListener> mockListener1;

    NiceMock<MockIEventListener> mockListener2;

    MultiReporter multiReporter;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(new MockIEventListener(mockListener1)));

        multiReporter.addReporter(IEventListenerPtr(new MockIEventListener(mockListener2)));

    }

};



TEST_F(MultiReporterTest_790, ReportInvalidTestSpec_CallsAllListeners_NormalOperation_790) {

    StringRef testArg("invalid_test_spec");

    EXPECT_CALL(mockListener1, reportInvalidTestSpec(testArg));

    EXPECT_CALL(mockListener2, reportInvalidTestSpec(testArg));



    multiReporter.reportInvalidTestSpec(testArg);

}



TEST_F(MultiReporterTest_790, ReportInvalidTestSpec_HandlesEmptyString_BoundaryCondition_790) {

    StringRef testArg("");

    EXPECT_CALL(mockListener1, reportInvalidTestSpec(testArg));

    EXPECT_CALL(mockListener2, reportInvalidTestSpec(testArg));



    multiReporter.reportInvalidTestSpec(testArg);

}



TEST_F(MultiReporterTest_790, ReportInvalidTestSpec_HandlesLongString_BoundaryCondition_790) {

    std::string longString(1000, 'a');

    StringRef testArg(longString.c_str());

    EXPECT_CALL(mockListener1, reportInvalidTestSpec(testArg));

    EXPECT_CALL(mockListener2, reportInvalidTestSpec(testArg));



    multiReporter.reportInvalidTestSpec(testArg);

}
