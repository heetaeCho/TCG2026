#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_cumulative_base.hpp"

#include "catch_assertion_result.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::NiceMock;



class MockAssertionResult : public AssertionResult {

public:

    MOCK_METHOD(bool, isOk, (), (const));

};



class CumulativeReporterBaseTest_858 : public ::testing::Test {

protected:

    ReporterConfig config;

    CumulativeReporterBase reporter{CATCH_MOVE(config)};

    NiceMock<MockAssertionResult> mockAssertionResult;

    AssertionStats assertionStats{mockAssertionResult, {}, Totals{}};

};



TEST_F(CumulativeReporterBaseTest_858, AssertionEnded_SuccessfulAssertionStored_858) {

    EXPECT_CALL(mockAssertionResult, isOk()).WillOnce(::testing::Return(true));

    reporter.assertionEnded(assertionStats);

    // Assuming the assertion is stored in m_sectionStack.back()->assertionsAndBenchmarks

    // Since we cannot access private members, this test checks if the function executes without errors.

}



TEST_F(CumulativeReporterBaseTest_858, AssertionEnded_SuccessfulAssertionNotStored_858) {

    reporter.m_shouldStoreSuccesfulAssertions = false;

    EXPECT_CALL(mockAssertionResult, isOk()).WillOnce(::testing::Return(true));

    reporter.assertionEnded(assertionStats);

    // Assuming the assertion is not stored in m_sectionStack.back()->assertionsAndBenchmarks

    // Since we cannot access private members, this test checks if the function executes without errors.

}



TEST_F(CumulativeReporterBaseTest_858, AssertionEnded_FailedAssertionStored_858) {

    EXPECT_CALL(mockAssertionResult, isOk()).WillOnce(::testing::Return(false));

    reporter.assertionEnded(assertionStats);

    // Assuming the assertion is stored in m_sectionStack.back()->assertionsAndBenchmarks

    // Since we cannot access private members, this test checks if the function executes without errors.

}



TEST_F(CumulativeReporterBaseTest_858, AssertionEnded_FailedAssertionNotStored_858) {

    reporter.m_shouldStoreFailedAssertions = false;

    EXPECT_CALL(mockAssertionResult, isOk()).WillOnce(::testing::Return(false));

    reporter.assertionEnded(assertionStats);

    // Assuming the assertion is not stored in m_sectionStack.back()->assertionsAndBenchmarks

    // Since we cannot access private members, this test checks if the function executes without errors.

}



TEST_F(CumulativeReporterBaseTest_858, AssertionEnded_EmptySectionStackAssertionThrows_858) {

    reporter.m_sectionStack.clear();

    EXPECT_CALL(mockAssertionResult, isOk()).WillOnce(::testing::Return(true));

    EXPECT_THROW(reporter.assertionEnded(assertionStats), std::exception);

}
