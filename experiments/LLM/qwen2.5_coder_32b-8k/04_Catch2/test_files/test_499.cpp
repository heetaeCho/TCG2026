#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, sectionEnded, (const SectionStats &sectionStats), (override));

};



class RunContextTest_499 : public ::testing::Test {

protected:

    MockIEventListener mockReporter;

    Totals m_totals;

    std::vector<ITracker*> m_activeSections;

    std::unique_ptr<OutputRedirect> m_outputRedirect;



    RunContext* runContext;



    void SetUp() override {

        auto reporterPtr = IEventListenerPtr(&mockReporter, [](IEventListener*){});

        runContext = new RunContext(nullptr, CATCH_MOVE(reporterPtr));

    }



    void TearDown() override {

        delete runContext;

    }

};



TEST_F(RunContextTest_499, SectionEnded_ReportSectionStats_499) {

    SectionEndInfo endInfo{};

    Counts assertions{10};

    endInfo.prevAssertions = m_totals.assertions - assertions;

    endInfo.sectionInfo.name = "SampleSection";

    endInfo.durationInSeconds = 2.5;



    EXPECT_CALL(mockReporter, sectionEnded(_))

        .WillOnce([](const SectionStats &sectionStats) {

            EXPECT_EQ(sectionStats.sectionInfo.name, "SampleSection");

            EXPECT_EQ(sectionStats.assertions.total(), 10);

            EXPECT_EQ(sectionStats.durationInSeconds, 2.5);

            EXPECT_FALSE(sectionStats.missingAssertions);

        });



    runContext->sectionEnded(CATCH_MOVE(endInfo));

}



TEST_F(RunContextTest_499, SectionEnded_NoActiveSections_499) {

    SectionEndInfo endInfo{};

    Counts assertions{10};

    endInfo.prevAssertions = m_totals.assertions - assertions;

    endInfo.sectionInfo.name = "SampleSection";

    endInfo.durationInSeconds = 2.5;



    EXPECT_CALL(mockReporter, sectionEnded(_))

        .WillOnce([](const SectionStats &sectionStats) {

            EXPECT_EQ(sectionStats.sectionInfo.name, "SampleSection");

            EXPECT_EQ(sectionStats.assertions.total(), 10);

            EXPECT_EQ(sectionStats.durationInSeconds, 2.5);

            EXPECT_FALSE(sectionStats.missingAssertions);

        });



    runContext->m_activeSections.clear();

    runContext->sectionEnded(CATCH_MOVE(endInfo));

}



TEST_F(RunContextTest_499, SectionEnded_MissingAssertions_499) {

    SectionEndInfo endInfo{};

    Counts assertions{0};

    endInfo.prevAssertions = m_totals.assertions - assertions;

    endInfo.sectionInfo.name = "SampleSection";

    endInfo.durationInSeconds = 2.5;



    EXPECT_CALL(mockReporter, sectionEnded(_))

        .WillOnce([](const SectionStats &sectionStats) {

            EXPECT_EQ(sectionStats.sectionInfo.name, "SampleSection");

            EXPECT_EQ(sectionStats.assertions.total(), 0);

            EXPECT_EQ(sectionStats.durationInSeconds, 2.5);

            EXPECT_TRUE(sectionStats.missingAssertions);

        });



    runContext->m_activeSections.clear();

    runContext->sectionEnded(CATCH_MOVE(endInfo));

}



TEST_F(RunContextTest_499, SectionEnded_ClearMessages_499) {

    SectionEndInfo endInfo{};

    Counts assertions{5};

    endInfo.prevAssertions = m_totals.assertions - assertions;

    endInfo.sectionInfo.name = "SampleSection";

    endInfo.durationInSeconds = 2.5;



    runContext->m_messages.emplace_back("Message1");

    runContext->m_messages.emplace_back("Message2");



    EXPECT_CALL(mockReporter, sectionEnded(_));



    runContext->sectionEnded(CATCH_MOVE(endInfo));

    EXPECT_TRUE(runContext->m_messages.empty());

}



TEST_F(RunContextTest_499, SectionEnded_ClearMessageScopes_499) {

    SectionEndInfo endInfo{};

    Counts assertions{5};

    endInfo.prevAssertions = m_totals.assertions - assertions;

    endInfo.sectionInfo.name = "SampleSection";

    endInfo.durationInSeconds = 2.5;



    runContext->m_messageScopes.emplace_back(MessageInfo{"Tag", "Scope1"});

    runContext->m_messageScopes.emplace_back(MessageInfo{"Tag", "Scope2"});



    EXPECT_CALL(mockReporter, sectionEnded(_));



    runContext->sectionEnded(CATCH_MOVE(endInfo));

    EXPECT_TRUE(runContext->m_messageScopes.empty());

}
