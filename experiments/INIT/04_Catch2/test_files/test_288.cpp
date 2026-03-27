// File: catch_cleanup_tests_288.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>

// --- Test-time observability (not re-implementing internal logic) ---
namespace {
    int g_cleanupSingletons_calls = 0;
    int g_cleanUpContext_calls   = 0;
    std::vector<std::string> g_call_order;

    void ResetObservers() {
        g_cleanupSingletons_calls = 0;
        g_cleanUpContext_calls = 0;
        g_call_order.clear();
    }
}

// --- Link-time test doubles for external collaborators ---
namespace Catch {
    // These are collaborators that Catch::cleanUp relies on.
    // We provide test doubles to observe interactions.
    void cleanupSingletons() {
        ++g_cleanupSingletons_calls;
        g_call_order.emplace_back("cleanupSingletons");
    }
    void cleanUpContext() {
        ++g_cleanUpContext_calls;
        g_call_order.emplace_back("cleanUpContext");
    }

    // Forward declare the function under test (defined in production code).
    void cleanUp();
}

// --- Test fixture ---
class CatchCleanUpTest_288 : public ::testing::Test {
protected:
    void SetUp() override { ResetObservers(); }
};

// [Behavior] cleanUp should invoke its external collaborators in order.
TEST_F(CatchCleanUpTest_288, CallsDependenciesInOrder_288) {
    // Act
    Catch::cleanUp();

    // Assert: each collaborator called exactly once
    EXPECT_EQ(g_cleanupSingletons_calls, 1);
    EXPECT_EQ(g_cleanUpContext_calls, 1);

    // Assert: order is cleanupSingletons -> cleanUpContext
    ASSERT_EQ(g_call_order.size(), 2u);
    EXPECT_EQ(g_call_order[0], "cleanupSingletons");
    EXPECT_EQ(g_call_order[1], "cleanUpContext");
}

// [Behavior] cleanUp can be called multiple times; interactions accumulate consistently.
TEST_F(CatchCleanUpTest_288, MultipleCallsAccumulate_288) {
    // Act
    Catch::cleanUp();
    Catch::cleanUp();

    // Assert: calls accumulate (no assumptions about internal state; only interactions)
    EXPECT_EQ(g_cleanupSingletons_calls, 2);
    EXPECT_EQ(g_cleanUpContext_calls, 2);

    // Assert: order over two invocations is preserved per call
    ASSERT_EQ(g_call_order.size(), 4u);
    EXPECT_EQ(g_call_order[0], "cleanupSingletons");
    EXPECT_EQ(g_call_order[1], "cleanUpContext");
    EXPECT_EQ(g_call_order[2], "cleanupSingletons");
    EXPECT_EQ(g_call_order[3], "cleanUpContext");
}
