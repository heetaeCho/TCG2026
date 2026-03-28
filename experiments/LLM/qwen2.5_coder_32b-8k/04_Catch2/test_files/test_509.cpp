#include <gtest/gtest.h>

#include "catch2/internal/catch_run_context.hpp"



using namespace Catch;



class RunContextTest_509 : public ::testing::Test {

protected:

    struct MockConfig : IConfig {

        std::string name() const override { return "MockTest"; }

        // Add other necessary overrides if needed

    };



    struct MockEventListener : IEventListener {};



    MockConfig mockConfig;

    Detail::unique_ptr<MockEventListener> mockListener = Detail::make_unique<MockEventListener>();

    RunContext runContext{&mockConfig, CATCH_MOVE(mockListener)};



    AssertionResult mockAssertionResult{};

};



TEST_F(RunContextTest_509, getLastResult_ReturnsNullptrWhenNoAssertions_509) {

    const AssertionResult* result = runContext.getLastResult();

    EXPECT_EQ(result, nullptr);

}



// Assuming there's a way to set the last assertion result for testing purposes

// This test assumes that we can mock or inject an assertion result into RunContext for testing

TEST_F(RunContextTest_509, getLastResult_ReturnsLastAssertionResult_509) {

    // Simulate setting the last assertion result (this is a hypothetical setup)

    runContext.assertionEnded(AssertionResult{});

    const AssertionResult* result = runContext.getLastResult();

    EXPECT_NE(result, nullptr);

}



TEST_F(RunContextTest_509, getLastResult_ReturnsSameInstanceAfterMultipleCalls_509) {

    // Simulate setting the last assertion result (this is a hypothetical setup)

    runContext.assertionEnded(AssertionResult{});

    const AssertionResult* result1 = runContext.getLastResult();

    const AssertionResult* result2 = runContext.getLastResult();

    EXPECT_EQ(result1, result2);

}
