#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_multi.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));

};



class MultiReporterTest_803 : public ::testing::Test {

protected:

    MultiReporter multi_reporter_;

    NiceMock<MockEventListener> mock_listener1_;

    NiceMock<MockEventListener> mock_listener2_;



    void SetUp() override {

        multi_reporter_.addListener(IEventListenerPtr(&mock_listener1_));

        multi_reporter_.addListener(IEventListenerPtr(&mock_listener2_));

    }

};



TEST_F(MultiReporterTest_803, TestCaseEndedForMultipleListeners_803) {

    TestCaseStats test_case_stats(TestCaseInfo("test_name", "description"), Totals(), "", "", false);

    

    EXPECT_CALL(mock_listener1_, testCaseEnded(_));

    EXPECT_CALL(mock_listener2_, testCaseEnded(_));



    multi_reporter_.testCaseEnded(test_case_stats);

}



TEST_F(MultiReporterTest_803, TestCaseEndedNoListeners_803) {

    MultiReporter empty_reporter;

    TestCaseStats test_case_stats(TestCaseInfo("test_name", "description"), Totals(), "", "", false);



    EXPECT_CALL(mock_listener1_, testCaseEnded(_)).Times(0);

    EXPECT_CALL(mock_listener2_, testCaseEnded(_)).Times(0);



    empty_reporter.testCaseEnded(test_case_stats);

}



TEST_F(MultiReporterTest_803, TestCaseEndedBoundaryConditions_803) {

    TestCaseStats test_case_stats(TestCaseInfo("", ""), Totals(), std::string(1000000, 'a'), std::string(1000000, 'b'), true);

    

    EXPECT_CALL(mock_listener1_, testCaseEnded(_));

    EXPECT_CALL(mock_listener2_, testCaseEnded(_));



    multi_reporter_.testCaseEnded(test_case_stats);

}
