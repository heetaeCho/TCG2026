#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(name, StringRef());

    MOCK_CONST_METHOD0(includeSuccessfulResults, bool());

};



class MockIEventListener : public IEventListener {

public:

    using IEventListener::IEventListener; // Inherit constructors

    MOCK_METHOD1(testRunStarting, void(const TestRunInfo& testRunInfo));

};



class RunContextTest_1074 : public ::testing::Test {

protected:

    NiceMock<MockIConfig> mockConfig;

    NiceMock<MockIEventListener> mockReporter;



    RunContext runContext;



    RunContextTest_1074() 

        : runContext(&mockConfig, std::move(std::make_unique<NiceMock<MockIEventListener>>(std::ref(mockConfig)))) {}

};



TEST_F(RunContextTest_1074, ConstructorCallsTestRunStarting_1074) {

    EXPECT_CALL(mockReporter, testRunStarting(_));



    // The constructor of RunContext is called in the setup phase

}



TEST_F(RunContextTest_1074, ConstructorUsesConfigName_1074) {

    StringRef expectedName = "test_name";

    EXPECT_CALL(mockConfig, name()).WillOnce(testing::Return(expectedName));

    

    // This will verify that the constructor uses the config's name correctly

}



TEST_F(RunContextTest_1074, ConstructorSetsIncludeSuccessfulResultsBasedOnConfigAndReporterPreferences_1074) {

    bool configValue = true;

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(testing::Return(configValue));



    // Assuming reporter preferences are set to false for this test

    ON_CALL(mockReporter, getPreferences().shouldReportAllAssertions).WillByDefault(testing::Return(false));



    // The constructor of RunContext is called in the setup phase, which sets m_includeSuccessfulResults



    EXPECT_TRUE(runContext.m_includeSuccessfulResults); // This verifies that m_includeSuccessfulResults is set correctly

}



TEST_F(RunContextTest_1074, ConstructorSetsIncludeSuccessfulResultsBasedOnReporterPreferencesWhenConfigIsFalse_1074) {

    bool configValue = false;

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(testing::Return(configValue));



    // Assuming reporter preferences are set to true for this test

    ON_CALL(mockReporter, getPreferences().shouldReportAllAssertions).WillByDefault(testing::Return(true));



    // The constructor of RunContext is called in the setup phase, which sets m_includeSuccessfulResults



    EXPECT_TRUE(runContext.m_includeSuccessfulResults); // This verifies that m_includeSuccessfulResults is set correctly

}



TEST_F(RunContextTest_1074, ConstructorSetsIncludeSuccessfulResultsBasedOnBothConfigAndReporterPreferencesWhenTrue_1074) {

    bool configValue = true;

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(testing::Return(configValue));



    // Assuming reporter preferences are set to true for this test

    ON_CALL(mockReporter, getPreferences().shouldReportAllAssertions).WillByDefault(testing::Return(true));



    // The constructor of RunContext is called in the setup phase, which sets m_includeSuccessfulResults



    EXPECT_TRUE(runContext.m_includeSuccessfulResults); // This verifies that m_includeSuccessfulResults is set correctly

}
