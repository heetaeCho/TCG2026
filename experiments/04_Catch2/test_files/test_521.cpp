#include <gtest/gtest.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/internal/catch_context.hpp"



namespace Catch {

    class MockIResultCapture : public IResultCapture {

    public:

        MOCK_METHOD(void, resultStarted, (const TestCaseInfo&), (override));

        MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));

        MOCK_METHOD(void, assertionEnded, (const AssertionInfo&, const AssertionResult&), (override));

        MOCK_METHOD(void, testEnded, (const TestCaseStats&), (override));

    };



    class ContextTest : public ::testing::Test {

    protected:

        MockIResultCapture mockResultCapture;

        Context context;



        void SetUp() override {

            context.setResultCapture(&mockResultCapture);

        }



        void TearDown() override {

            context.cleanUpContext();

        }

    };

}



using namespace Catch;



TEST_F(ContextTest_521, GetResultCapture_ReturnsSetInstance_521) {

    EXPECT_EQ(context.getResultCapture(), &mockResultCapture);

}



TEST_F(ContextTest_521, SetAndGetConfig_WorkAsExpected_521) {

    const IConfig* mockConfig = reinterpret_cast<const IConfig*>(0x12345678);

    context.setConfig(mockConfig);

    EXPECT_EQ(context.getConfig(), mockConfig);

}



TEST_F(ContextTest_521, CleanUpContext_SetsResultCaptureToNullptr_521) {

    context.cleanUpContext();

    EXPECT_EQ(context.getResultCapture(), nullptr);

}



TEST_F(ContextTest_521, SetAndGetResultCapture_WorkAsExpected_521) {

    MockIResultCapture anotherMockResultCapture;

    context.setResultCapture(&anotherMockResultCapture);

    EXPECT_EQ(context.getResultCapture(), &anotherMockResultCapture);

}
