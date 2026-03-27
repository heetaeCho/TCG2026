#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_automake.hpp"

#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"



using namespace Catch;



class AutomakeReporterTest : public ::testing::Test {

protected:

    ReporterConfig config;

    AutomakeReporter* reporter;



    void SetUp() override {

        reporter = new AutomakeReporter(CATCH_MOVE(config));

    }



    void TearDown() override {

        delete reporter;

    }

};



TEST_F(AutomakeReporterTest_564, GetDescriptionReturnsCorrectString_564) {

    EXPECT_EQ("Reports test results in the format of Automake .trs files", AutomakeReporter::getDescription());

}



// Assuming testCaseEnded and skipTest have observable effects through external collaborators or callbacks.

// Mocking an external collaborator would be needed to verify interactions. Here, we assume such a mock is provided.



class MockStreamingReporterBase : public StreamingReporterBase {

public:

    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats& _testCaseStats), (override));

    MOCK_METHOD(void, skipTest, (const TestCaseInfo& testInfo), (override));



protected:

    MockStreamingReporterBase(ReporterConfig&& _config) : StreamingReporterBase(CATCH_MOVE(_config)) {}

};



class AutomakeReporterWithMock : public AutomakeReporter {

public:

    AutomakeReporterWithMock(MockStreamingReporterBase* mock)

        : AutomakeReporter(*static_cast<ReporterConfig*>(&mock->getRunner())), mock(mock) {}



protected:

    MockStreamingReporterBase* mock;

};



TEST_F(AutomakeReporterTest_564, TestCaseEndedInvokesBaseMethod_564) {

    MockStreamingReporterBase mock(config);

    EXPECT_CALL(mock, testCaseEnded(::testing::_)).Times(1);



    AutomakeReporterWithMock reporter(&mock);

    TestCaseStats testCaseStats; // Assuming this can be default-constructed

    reporter.testCaseEnded(testCaseStats);

}



TEST_F(AutomakeReporterTest_564, SkipTestInvokesBaseMethod_564) {

    MockStreamingReporterBase mock(config);

    EXPECT_CALL(mock, skipTest(::testing::_)).Times(1);



    AutomakeReporterWithMock reporter(&mock);

    TestCaseInfo testInfo; // Assuming this can be default-constructed

    reporter.skipTest(testInfo);

}
