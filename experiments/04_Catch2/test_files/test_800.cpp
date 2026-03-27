#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_multi.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;

using namespace testing;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, assertionEnded, (const AssertionStats &assertionStats), (override));

};



class MultiReporterTest_800 : public Test {

protected:

    std::shared_ptr<IConfig> mockConfig = std::make_shared<StrictMock<MockIConfig>>();

    MultiReporter multiReporter{mockConfig.get()};

    NiceMock<MockEventListener> listener1;

    NiceMock<MockEventListener> listener2;



    void SetUp() override {

        multiReporter.addListener(std::make_unique<MockEventListener>(listener1));

        multiReporter.addReporter(std::make_unique<MockEventListener>(listener2));

    }

};



TEST_F(MultiReporterTest_800, AssertionEnded_DefaultReporting_800) {

    AssertionResult result(AssertionInfo{}, AssertionResultData{});

    AssertionStats stats(result, {}, Totals{});



    EXPECT_CALL(listener1, assertionEnded(_)).Times(1);

    EXPECT_CALL(listener2, assertionEnded(_)).Times(1);



    multiReporter.assertionEnded(stats);

}



TEST_F(MultiReporterTest_800, AssertionEnded_SuccessfulResultNotReportedWhenConfigExcludes_800) {

    AssertionResult result(AssertionInfo{}, AssertionResultData{});

    result.m_resultData.resultType = ResultWas::Ok;

    AssertionStats stats(result, {}, Totals{});



    EXPECT_CALL(*mockConfig, includeSuccessfulResults()).WillOnce(Return(false));

    EXPECT_CALL(listener1, assertionEnded(_)).Times(0);

    EXPECT_CALL(listener2, assertionEnded(_)).Times(0);



    multiReporter.assertionEnded(stats);

}



TEST_F(MultiReporterTest_800, AssertionEnded_SuccessfulResultReportedWhenConfigIncludes_800) {

    AssertionResult result(AssertionInfo{}, AssertionResultData{});

    result.m_resultData.resultType = ResultWas::Ok;

    AssertionStats stats(result, {}, Totals{});



    EXPECT_CALL(*mockConfig, includeSuccessfulResults()).WillOnce(Return(true));

    EXPECT_CALL(listener1, assertionEnded(_)).Times(1);

    EXPECT_CALL(listener2, assertionEnded(_)).Times(1);



    multiReporter.assertionEnded(stats);

}



TEST_F(MultiReporterTest_800, AssertionEnded_ReportAllAssertionsEnabledInPreferences_800) {

    AssertionResult result(AssertionInfo{}, AssertionResultData{});

    result.m_resultData.resultType = ResultWas::Ok;

    AssertionStats stats(result, {}, Totals{});



    EXPECT_CALL(*mockConfig, includeSuccessfulResults()).WillOnce(Return(false));

    EXPECT_CALL(listener1, assertionEnded(_)).Times(1);

    EXPECT_CALL(listener2, assertionEnded(_)).Times(1);



    ReporterPreferences preferences;

    preferences.shouldReportAllAssertions = true;



    listener1.m_preferences = preferences;

    listener2.m_preferences = preferences;



    multiReporter.assertionEnded(stats);

}



TEST_F(MultiReporterTest_800, AssertionEnded_ReportAllAssertionsDisabledInPreferences_800) {

    AssertionResult result(AssertionInfo{}, AssertionResultData{});

    result.m_resultData.resultType = ResultWas::Ok;

    AssertionStats stats(result, {}, Totals{});



    EXPECT_CALL(*mockConfig, includeSuccessfulResults()).WillOnce(Return(false));

    EXPECT_CALL(listener1, assertionEnded(_)).Times(0);

    EXPECT_CALL(listener2, assertionEnded(_)).Times(0);



    ReporterPreferences preferences;

    preferences.shouldReportAllAssertions = false;



    listener1.m_preferences = preferences;

    listener2.m_preferences = preferences;



    multiReporter.assertionEnded(stats);

}
