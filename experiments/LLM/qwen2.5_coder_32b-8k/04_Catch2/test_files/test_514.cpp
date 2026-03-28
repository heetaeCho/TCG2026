#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_run_context.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class MockIConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(abortAfter, int());

};



class RunContextTest_514 : public ::testing::Test {

protected:

    MockIConfig mockConfig;

    std::shared_ptr<IEventListener> mockReporter = nullptr; // Assuming a default constructor for IEventListenerPtr

    RunContext runContext;



    RunContextTest_514() : runContext(&mockConfig, std::move(mockReporter)) {}

};



TEST_F(RunContextTest_514, AbortingReturnsFalseWhenNoFailures_514) {

    EXPECT_CALL(mockConfig, abortAfter()).WillOnce(Return(0));



    Totals totals;

    totals.assertions.failed = 0;



    runContext.m_totals = totals;



    EXPECT_FALSE(runContext.aborting());

}



TEST_F(RunContextTest_514, AbortingReturnsFalseWhenFailuresBelowThreshold_514) {

    EXPECT_CALL(mockConfig, abortAfter()).WillOnce(Return(5));



    Totals totals;

    totals.assertions.failed = 3;



    runContext.m_totals = totals;



    EXPECT_FALSE(runContext.aborting());

}



TEST_F(RunContextTest_514, AbortingReturnsTrueWhenFailuresMeetThreshold_514) {

    EXPECT_CALL(mockConfig, abortAfter()).WillOnce(Return(3));



    Totals totals;

    totals.assertions.failed = 3;



    runContext.m_totals = totals;



    EXPECT_TRUE(runContext.aborting());

}



TEST_F(RunContextTest_514, AbortingReturnsTrueWhenFailuresExceedThreshold_514) {

    EXPECT_CALL(mockConfig, abortAfter()).WillOnce(Return(2));



    Totals totals;

    totals.assertions.failed = 3;



    runContext.m_totals = totals;



    EXPECT_TRUE(runContext.aborting());

}



TEST_F(RunContextTest_514, AbortingWithNegativeThresholdNeverAborts_514) {

    EXPECT_CALL(mockConfig, abortAfter()).WillOnce(Return(-1));



    Totals totals;

    totals.assertions.failed = 10;



    runContext.m_totals = totals;



    EXPECT_FALSE(runContext.aborting());

}
