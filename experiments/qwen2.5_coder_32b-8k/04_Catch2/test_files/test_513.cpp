#include <gtest/gtest.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/catch_totals.hpp"



using namespace Catch;



class RunContextTest_513 : public ::testing::Test {

protected:

    class MockEventListener : public IEventListener {

    public:

        MOCK_METHOD(void, assertionPassed, (), (override));

        MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));

        // Add other necessary mocks if needed

    };



    std::shared_ptr<MockEventListener> mockListener = std::make_shared<MockEventListener>();

    RunContext runContext{nullptr, IEventListenerPtr(mockListener)};

};



TEST_F(RunContextTest_513, AssertionPassed_IncreasesAssertionsCount_513) {

    Totals initialTotals = runContext.m_totals;

    

    runContext.assertionPassed();



    EXPECT_EQ(runContext.m_totals.assertions.passed, initialTotals.assertions.passed + 1);

}



TEST_F(RunContextTest_513, AssertionPassed_ResetsLastAssertionInfo_513) {

    // Assuming there's a way to set m_lastAssertionInfo for testing

    runContext.m_lastAssertionInfo = AssertionInfo{};

    runContext.m_lastAssertionInfo.expression = "some_expression";



    runContext.assertionPassed();



    EXPECT_TRUE(runContext.m_lastAssertionInfo.expression.empty());

}



TEST_F(RunContextTest_513, AssertionPassed_ClearsMessageScopes_513) {

    ScopedMessage scopedMessage;

    runContext.m_messageScopes.push_back(scopedMessage);



    runContext.assertionPassed();



    EXPECT_TRUE(runContext.m_messageScopes.empty());

}



TEST_F(RunContextTest_513, LastAssertionPassed_ReturnsTrue_AfterAssertionPassed_513) {

    runContext.assertionPassed();



    EXPECT_TRUE(runContext.lastAssertionPassed());

}
