#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/internal/catch_test_case_tracker.hpp"

#include "catch2/catch_section_info.hpp"



using namespace Catch;



class MockITracker : public ITracker {

public:

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(bool, isComplete, (), (const, override));

    MOCK_METHOD(bool, isOpen, (), (const, override));

    MOCK_METHOD(bool, hasStarted, (), (const, override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr&& child), (override));

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef & nameAndLocation), (override));

    MOCK_METHOD(void, openChild, (), (override));

    MOCK_METHOD(bool, isSectionTracker, (), (const, override));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const, override));

    MOCK_CONST_METHOD0(nameAndLocation, NameAndLocation&());

    MOCK_CONST_METHOD0(parent, ITracker*());

    MOCK_CONST_METHOD0(isSuccessfullyCompleted, bool());

    MOCK_CONST_METHOD0(hasChildren, bool());

};



class RunContextTest : public ::testing::Test {

protected:

    MockITracker tracker1;

    MockITracker tracker2;

    std::vector<ITracker*> m_activeSections;

    std::vector<SectionEndInfo> m_unfinishedSections;



    void SetUp() override {

        m_activeSections.push_back(&tracker1);

        m_activeSections.push_back(&tracker2);



        RunContext::m_activeSections = m_activeSections;

        RunContext::m_unfinishedSections = m_unfinishedSections;

    }



    void TearDown() override {

        m_activeSections.clear();

        m_unfinishedSections.clear();



        RunContext::m_activeSections.clear();

        RunContext::m_unfinishedSections.clear();

    }

};



TEST_F(RunContextTest, SectionEndedEarly_NoUnfinishedSections_500) {

    SectionEndInfo endInfo;

    EXPECT_CALL(tracker2, fail()).Times(1);

    EXPECT_CALL(tracker2, close()).Times(0);



    RunContext::sectionEndedEarly(std::move(endInfo));



    ASSERT_EQ(RunContext::m_activeSections.size(), 1u);

    ASSERT_EQ(RunContext::m_unfinishedSections.size(), 1u);

}



TEST_F(RunContextTest, SectionEndedEarly_WithUnfinishedSections_500) {

    m_unfinishedSections.push_back(SectionEndInfo());



    SectionEndInfo endInfo;

    EXPECT_CALL(tracker2, close()).Times(1);

    EXPECT_CALL(tracker2, fail()).Times(0);



    RunContext::sectionEndedEarly(std::move(endInfo));



    ASSERT_EQ(RunContext::m_activeSections.size(), 1u);

    ASSERT_EQ(RunContext::m_unfinishedSections.size(), 2u);

}



TEST_F(RunContextTest, SectionEndedEarly_EmptyActiveSections_500) {

    m_activeSections.clear();

    RunContext::m_activeSections = m_activeSections;



    SectionEndInfo endInfo;

    EXPECT_CALL(tracker1, close()).Times(0);

    EXPECT_CALL(tracker1, fail()).Times(0);



    RunContext::sectionEndedEarly(std::move(endInfo));



    ASSERT_EQ(RunContext::m_activeSections.size(), 0u);

    ASSERT_EQ(RunContext::m_unfinishedSections.size(), 1u);

}
